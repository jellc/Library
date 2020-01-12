// verified at https://judge.yosupo.jp/submission/2862
#ifndef LAZY_SEGMENT_TREE_HPP
#define LAZY_SEGMENT_TREE_HPP

template <class Monoid, class Action>
class lazy_segment_tree
{
    using value_type = typename Monoid::value_type;
    using operand_type = typename Action::value_type;
    Monoid *const monoid_ptr, &monoid;
    Action *const action_ptr, &action;
    const size_t orig_n, height, ext_n;
    std::vector<value_type> data;
    std::vector<operand_type> lazy;

    void recalc(size_t node) { data[node] = monoid(data[node << 1], data[node << 1 | 1]); }

    void apply(size_t index, const operand_type &operand)
    {
        action.act(data[index], operand);
        if(index < ext_n) action(lazy[index], operand);
    }

    void push(size_t index)
    {
        apply(index << 1, lazy[index]);
        apply(index << 1 | 1, lazy[index]);
        lazy[index] = action.identity();
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
            push(node);
            // search from right child
            left_bound(index, pred, node << 1 | 1, (begin + end) >> 1, end, now, res);
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
            push(node);
            // search from left child
            right_bound(index, pred, node << 1, begin, (begin + end) >> 1, now, res);
            right_bound(index, pred, node << 1 | 1, (begin + end) >> 1, end, now, res);
            lazy[node] = action.identity();
        }
    }

  public:
    explicit lazy_segment_tree(size_t n) : monoid_ptr{new Monoid}, monoid{*monoid_ptr}, action_ptr{new Action}, action{*action_ptr},
                                            orig_n{n}, height(n > 1 ? 32 - __builtin_clz(n - 1) : 0), ext_n(1 << height),
                                            data(ext_n << 1, monoid.identity()), lazy(ext_n, action.identity()) {}
    lazy_segment_tree(size_t n, Monoid &_monoid) : monoid_ptr{}, monoid{_monoid}, action_ptr{new Action}, action{*action_ptr},
                                                    orig_n{n}, height(n > 1 ? 32 - __builtin_clz(n - 1) : 0), ext_n(1 << height),
                                                    data(ext_n << 1, monoid.identity()), lazy(ext_n, action.identity()) {}
    lazy_segment_tree(size_t n, Action &_actor) : monoid_ptr{new Monoid}, monoid{*monoid_ptr}, action_ptr{}, action{_actor},
                                                    orig_n{n}, height(n > 1 ? 32 - __builtin_clz(n - 1) : 0), ext_n(1 << height),
                                                    data(ext_n << 1, monoid.identity()), lazy(ext_n, action.identity()) {}
    lazy_segment_tree(size_t n, Monoid &_monoid, Action &_actor) : monoid_ptr{}, monoid{_monoid}, action_ptr{}, action{_actor},
                                                                    orig_n{n}, height(n > 1 ? 32 - __builtin_clz(n - 1) : 0), ext_n(1 << height),
                                                                    data(ext_n << 1, monoid.identity()), lazy(ext_n, action.identity()) {}
    ~lazy_segment_tree() { delete monoid_ptr; delete action_ptr; }

    // copy of the element at position i.
    value_type operator[](size_t i) { return fold(i, i + 1); }

    void build(value_type *__first, value_type *__last)
    {
        assert((size_t)std::distance(__first, __last) <= ext_n);
        std::copy(__first, __last, data.begin() + ext_n);
        for(size_t i = ext_n - 1; i; --i) recalc(i);
    }

    template <class iterator>
    void build(iterator __first, iterator __last)
    {
        static_assert(std::is_same<typename std::iterator_traits<iterator>::value_type, value_type>::value, "iterator's value_type should be equal to Monoid's");
        assert((size_t)std::distance(__first, __last) <= ext_n);
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
        begin += ext_n, end += ext_n - 1;
        for(size_t i = height; i; --i) push(begin >> i), push(end >> i);
        for(size_t l = begin, r = end + 1; end; l >>= 1, r >>= 1)
        {
            if(l < r)
            {
                if(l & 1) apply(l++, operand);
                if(r & 1) apply(--r, operand);
            }
            if(begin >>= 1, end >>= 1)
            {
                recalc(begin), recalc(end);
            }
        }
    }

    value_type fold(size_t begin, size_t end)
    {
        assert(0 <= begin && end <= orig_n);
        begin += ext_n, end += ext_n - 1;
        value_type left_val{monoid.identity()}, right_val{monoid.identity()};
        for(size_t l = begin, r = end + 1; end; l >>= 1, r >>= 1)
        {
            if(l < r)
            {
                if(l & 1) left_val = monoid(left_val, data[l++]);
                if(r & 1) right_val = monoid(data[--r], right_val);
            }
            if(begin >>= 1, end >>= 1)
            {
                action.act(left_val, lazy[begin]);
                action.act(right_val, lazy[end]);
            }
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