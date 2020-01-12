// verified at https://judge.yosupo.jp/submission/2855
#ifndef LAZY_SEGMENT_TREE_HPP
#define LAZY_SEGMENT_TREE_HPP

template <class Monoid, class Action>
class lazy_segment_tree
{
    using value_type = typename Monoid::value_type;
    using operand_type = typename Action::value_type;
    Monoid *const monoid_ptr, &monoid;
    Action *const action_ptr, &action;
    const size_t orig_n, ext_n;
    std::vector<value_type> data;
    std::vector<operand_type> lazy;

    size_t left_node(size_t node) const { return node << 1; }
    size_t right_node(size_t node) const { return node << 1 | 1; }
    void recalc(size_t node) { data[node] = monoid(data[node << 1], data[node << 1 | 1]); }

    void update(size_t begin, size_t end, const operand_type &operand, size_t node, size_t l, size_t r)
    {
        if(end <= l || r <= begin) return;
        if(begin <= l && r <= end)
        {
            action.act(data[node], operand);
            if(node < ext_n) action(lazy[node], operand);
        }
        else
        {
            update(0, ext_n, lazy[node], node << 1, l, (l + r) >> 1);
            update(0, ext_n, lazy[node], node << 1 | 1, (l + r) >> 1, r);
            lazy[node] = action.identity();
            update(begin, end, operand, node << 1, l, (l + r) >> 1);
            update(begin, end, operand, node << 1 | 1, (l + r) >> 1, r);
            recalc(node);
        }
    }

    void left_bound(size_t index, const std::function<bool(const value_type &)> &pred,
                    size_t node, size_t begin, size_t end, value_type &now, size_t &res)
    {
        if(index <= begin || end < res) return;
        if(end <= index)
        {
            const value_type nxt = monoid(data[node], now);
            if(pred(nxt))
            {
                res = begin, now = nxt;
                return;
            }
        }
        if(end - begin > 1)
        {
            // search from right child
            update(0, ext_n, lazy[node], node << 1 | 1, begin, end);
            left_bound(index, pred, node << 1 | 1, (begin + end) >> 1, end, now, res);
            update(0, ext_n, lazy[node], node << 1, begin, end);
            left_bound(index, pred, node << 1, begin, (begin + end) >> 1, now, res);
            lazy[node] = action.identity();
        }
    }

    void right_bound(size_t index, const std::function<bool(const value_type &)> &pred,
                    size_t node, size_t begin, size_t end, value_type &now, size_t &res)
    {
        if(index >= end || begin > res) return;
        if(begin >= index)
        {
            const value_type nxt = monoid(now, data[node]);
            if(pred(nxt))
            {
                res = end, now = nxt;
                return;
            }
        }
        if(end - begin > 1)
        {
            // search from left child
            update(0, ext_n, lazy[node], node << 1, begin, end);
            right_bound(index, pred, left_node(node), begin, (begin + end) >> 1, now, res);
            update(0, ext_n, lazy[node], node << 1 | 1, begin, end);
            right_bound(index, pred, right_node(node), (begin + end) >> 1, end, now, res);
            lazy[node] = action.identity();
        }
    }

  public:
    explicit lazy_segment_tree(size_t n) : monoid_ptr{new Monoid}, monoid{*monoid_ptr}, action_ptr{new Action}, action{*action_ptr}, orig_n{n}, ext_n(n > 1 ? 1 << (32 - __builtin_clz(n - 1)) : 1),
                                    data(ext_n << 1, monoid.identity()), lazy(ext_n, action.identity()) {}
    lazy_segment_tree(size_t n, Monoid &_monoid) : monoid_ptr{}, monoid{_monoid}, action_ptr{new Action}, action{*action_ptr}, orig_n{n}, ext_n(n > 1 ? 1 << (32 - __builtin_clz(n - 1)) : 1),
                                                    data(ext_n << 1, monoid.identity()), lazy(ext_n, action.identity()) {}
    lazy_segment_tree(size_t n, Action &_actor) : monoid_ptr{new Monoid}, monoid{*monoid_ptr}, action_ptr{}, action{_actor}, orig_n{n}, ext_n(n > 1 ? 1 << (32 - __builtin_clz(n - 1)) : 1),
                                                data(ext_n << 1, monoid.identity()), lazy(ext_n, action.identity()) {}
    lazy_segment_tree(size_t n, Monoid &_monoid, Action &_actor) : monoid_ptr{}, monoid{_monoid}, action_ptr{}, action{_actor}, orig_n{n}, ext_n(n > 1 ? 1 << (32 - __builtin_clz(n - 1)) : 1),
                                                                data(ext_n << 1, monoid.identity()), lazy(ext_n, action.identity()) {}
    ~lazy_segment_tree() { delete monoid_ptr; delete action_ptr; }

    // copy of value at index i.
    value_type operator[](size_t i) { return fold(i, i + 1); }

    void build(value_type *__first, value_type *__last)
    {
        std::copy(__first, __last, data.begin() + ext_n);
        for(size_t i = ext_n - 1; i; --i) recalc(i);
    }

    template <class iterator>
    void build(iterator __first, iterator __last)
    {
        static_assert(std::is_same<typename std::iterator_traits<iterator>::value_type, value_type>::value, "iterator's value_type should be equal to Monoid's");
        std::copy(__first, __last, data.begin() + ext_n);
        for(size_t i = ext_n - 1; i; --i) recalc(i);
    }

    void init(const value_type &x)
    {
        for(size_t i = 0; i != ext_n; ++i) data[i | ext_n] = x;
        for(size_t i = ext_n - 1; i; --i) recalc(i);
    }

    void update(size_t index, const operand_type &operand) { update(index, index + 1, operand); }

    void update(size_t begin, size_t end, const operand_type &operand)
    {
        assert(0 <= begin && end <= orig_n);
        update(begin, end, operand, 1, 0, ext_n);
    }

    value_type fold(size_t begin, size_t end)
    {
        assert(0 <= begin && end <= orig_n);
        value_type left_val{monoid.identity()}, right_val{monoid.identity()};
        size_t l{begin += ext_n}, r{end += ext_n};
        --end;
        while(end)
        {
            if(l < r)
            {
                if(l & 1) left_val = monoid(left_val, data[l++]);
                if(r & 1) right_val = monoid(data[--r], right_val);
                l >>= 1, r >>= 1;
            }
            action.act(left_val, lazy[begin >>= 1]);
            action.act(right_val, lazy[end >>= 1]);
        }
        return monoid(left_val, right_val);
    }

    // minimum l where range [l, index) meets the condition.
    size_t left_bound(size_t index, const std::function<bool(const value_type &)> &pred)
    {
        assert(index <= orig_n);
        size_t res = index;
        value_type now = monoid.identity();
        left_bound(index, pred, 1, 0, ext_n, now, res);
        return res;
    }

    // maximum r where range [index, r) meets the condition.
    size_t right_bound(size_t index, const std::function<bool(const value_type &)> &pred)
    {
        assert(index < orig_n);
        size_t res = index;
        value_type now = monoid.identity();
        right_bound(index, pred, 1, 0, ext_n, now, res);
        return res < orig_n ? res : orig_n;
    }
}; //class lazy_segment_tree

#endif