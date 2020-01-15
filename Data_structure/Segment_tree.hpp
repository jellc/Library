// #line 2 "Segment_tree.hpp"
// verified at https://judge.yosupo.jp/submission/2903
#ifndef Segment_tree_hpp
#define Segment_tree_hpp

template <class Monoid>
class segment_tree
{
    class unique_queue
    {
        size_t *const que, *qbegin, *qend;
        bool *const inque;
    public:
        unique_queue(size_t n) : que(new size_t[n]), qbegin(que), qend(que), inque(new bool[n]{}) {}
        ~unique_queue() { delete[] que; delete[] inque; }
        void clear() { qbegin = qend = que; }
        bool empty() const { return qbegin == qend; }
        bool push(size_t x)
        {
            if(inque[x]) return false;
            return inque[*qend++ = x] = true;
        }
        size_t pop() { return inque[*qbegin] = false, *qbegin++; }
    }; // class unique_queue

    using value_type = typename Monoid::value_type;
    Monoid *const monoid_ptr, &monoid;
    const size_t orig_n, height, ext_n;
    value_type *const data;
    unique_queue que;

    void recalc(size_t node) { data[node] = monoid(data[node << 1], data[node << 1 | 1]); }

    void rebuild()
    {
        while(!que.empty())
        {
            const size_t f = que.pop(), p = f >> 1;
            if(p && que.push(p)) recalc(p);
        }
        que.clear();
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
        if(node < ext_n)
        {
            // search the right child first
            left_bound(index, pred, node << 1 | 1, (begin + end) >> 1, end, now, res);
            left_bound(index, pred, node << 1, begin, (begin + end) >> 1, now, res);
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
        if(node < ext_n)
        {
            // search the left child first
            right_bound(index, pred, node << 1, begin, (begin + end) >> 1, now, res);
            right_bound(index, pred, node << 1 | 1, (begin + end) >> 1, end, now, res);
        }
    }

    segment_tree(size_t n, Monoid *const _monoid_ptr, bool new_ptr)
        : monoid_ptr(new_ptr ? _monoid_ptr : nullptr), monoid(*_monoid_ptr),
            orig_n{n}, height(orig_n > 1 ? 32 - __builtin_clz(orig_n - 1) : 0), ext_n{1u << height},
            data(new value_type[ext_n << 1]), que(ext_n << 1)
    {
        std::fill_n(data, ext_n << 1, monoid.identity());
    }

    segment_tree(size_t n, const value_type &val, Monoid *const _monoid_ptr, bool new_ptr)
        : monoid_ptr(new_ptr ? _monoid_ptr : nullptr), monoid(*_monoid_ptr),
            orig_n{n}, height(orig_n > 1 ? 32 - __builtin_clz(orig_n - 1) : 0), ext_n{1u << height},
            data(new value_type[ext_n << 1]), que(ext_n << 1)
    {
        std::fill_n(data + ext_n, ext_n, val);
        for(size_t i = ext_n - 1; i; --i) recalc(i);
    }

    template <class iter_type>
    segment_tree(iter_type __first, iter_type __last, Monoid *const _monoid_ptr, bool new_ptr)
        : monoid_ptr(new_ptr ? _monoid_ptr : nullptr), monoid(*_monoid_ptr),
            orig_n(std::distance(__first, __last)), height(orig_n > 1 ? 32 - __builtin_clz(orig_n - 1) : 0), ext_n{1u << height},
            data(new value_type[ext_n << 1]), que(ext_n << 1)
    {
        static_assert(std::same<typename std::iterator_traits<iter_type>::value_type, value_type>::value, "iterator's value_type should be equal to Monoid's");
        std::fill(std::copy(__first, __last, data + ext_n), data + (ext_n << 1), monoid.identity());
        for(size_t i = ext_n - 1; i; --i) recalc(i);
    }

public:
    explicit segment_tree(size_t n) : segment_tree(n, new Monoid, true) {}
    segment_tree(size_t n, Monoid &_monoid) : segment_tree(n, &_monoid, false) {}

    segment_tree(size_t n, const value_type &val) : segment_tree(n, val, new Monoid, true) {}
    segment_tree(size_t n, const value_type &val, Monoid &_monoid) : segment_tree(n, val, &_monoid, false) {}

    template <class iter_type, class = typename std::iterator_traits<iter_type>::value_type>
    segment_tree(const iter_type __first, const iter_type __last) : segment_tree(__first, __last, new Monoid, true) {}
    template <class iter_type, class = typename std::iterator_traits<iter_type>::value_type>
    segment_tree(const iter_type __first, const iter_type __last, Monoid &_monoid) : segment_tree(__first, __last, &_monoid, false) {}

    ~segment_tree() { delete monoid_ptr; delete[] data; }

    // reference to the element at position i.
    value_type &operator[](size_t i)
    {
        assert(i < orig_n);
        que.push(i |= ext_n);
        return data[i];
    }

    value_type fold(size_t begin, size_t end)
    {
        assert(end <= orig_n), rebuild();
        value_type leftval = monoid.identity(), rightval = monoid.identity();
        begin += ext_n, end += ext_n;
        while(begin < end)
        {
            if(begin & 1) leftval = monoid(leftval, data[begin++]);
            if(end & 1) rightval = monoid(rightval, data[--end]);
            begin >>= 1, end >>= 1;
        }
        return monoid(leftval, rightval);
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
}; // class segment_tree

#endif // Segment_tree_hpp