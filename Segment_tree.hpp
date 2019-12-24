
#ifndef SEGMENT_TREE_HPP
#define SEGMENT_TREE_HPP
template <class Monoid>
class segment_tree
{
    class uniqueue
    {
        size_t *const que, *qbegin, *qend;
        bool *const inque;
      public:
        uniqueue(size_t n) : que(new size_t[n]), qbegin(que), qend(que), inque(new bool[n]{}) {}
        ~uniqueue() { delete[] que; delete[] inque; }
      	void clear() { qbegin = qend = que; }
        bool empty() const { return qbegin == qend; }
        bool push(size_t x)
        {
            if(inque[x]) return false;
            return inque[*qend++ = x] = true;
        }
        size_t pop()
        {
            const size_t res{*qbegin++};
            return inque[res] = false, res;
        }
    }; // class uniqueue

    using value_type = typename Monoid::value_type;
    Monoid *const monoid_ptr, &monoid;
    const size_t orig_n, ext_n;
    std::vector<value_type> data;
    uniqueue que;

    void rebuild()
    {
        while(!que.empty())
        {
            const size_t f = que.pop(), p = f >> 1;
            if(p && que.push(p)) data[p] = monoid(data[f], data[f ^ 1]);
        }
        que.clear();
    }

    void left_bound(size_t idx, const std::function<bool(const value_type &)> &pred,
                    size_t k, size_t l, size_t r, value_type &now, size_t &res)
    {
        if(idx <= l || r < res) return;
        if(r <= idx)
        {
            const value_type nxt = monoid(data[k], now);
            if(pred(nxt))
            {
                res = l, now = nxt;
                return;
            }
        }
        if(r - l > 1)
        {
            left_bound(idx, pred, k << 1 ^ 1, (l + r) >> 1, r, now, res);
            left_bound(idx, pred, k << 1, l, (l + r) >> 1, now, res);
        }
    }

    void right_bound(size_t idx, const std::function<bool(const value_type &)> &pred,
                     size_t k, size_t l, size_t r, value_type &now, size_t &res)
    {
        if(idx >= r || l > res) return;
        if(l >= idx)
        {
            const value_type nxt = monoid(now, data[k]);
            if(pred(nxt))
            {
                res = r, now = nxt;
                return;
            }
        }
        if(r - l > 1)
        {
            right_bound(idx, pred, k << 1, l, (l + r) >> 1, now, res);
            right_bound(idx, pred, k << 1 ^ 1, (l + r) >> 1, r, now, res);
        }
    }

  public:
    segment_tree(size_t n) : monoid_ptr{new Monoid}, monoid{*monoid_ptr}, orig_n{n}, ext_n(n > 1 ? 1 << (32 - __builtin_clz(n - 1)) : 1), data(ext_n << 1, monoid.identity()), que(ext_n << 1) {}
    segment_tree(size_t n, Monoid &_monoid) : monoid_ptr{}, monoid{_monoid}, orig_n{n}, ext_n(n > 1 ? 1 << (32 - __builtin_clz(n - 1)) : 1), data(ext_n << 1, monoid.identity()), que(ext_n << 1) {}
    ~segment_tree() { if(monoid_ptr) delete monoid_ptr; }

    void build(value_type *__first, value_type *__last)
    {
        std::copy(__first, __last, &data[ext_n]);
        for(size_t i = ext_n; i; --i) data[i] = monoid(data[i * 2], data[i * 2 + 1]);
        que.clear();
    }

    template <class iterator>
    void build(iterator __first, iterator __last)
    {
        static_assert(std::is_same<typename std::iterator_traits<iterator>::value_type, value_type>::value, "iterator's value_type should be equal to Monoid's");
        std::copy(__first, __last, &data[ext_n]);
        for(size_t i = ext_n - 1; i; --i) data[i] = monoid(data[i * 2], data[i * 2 + 1]);
        que.clear();
    }

    value_type fold(size_t l, size_t r)
    {
        rebuild();
        value_type leftval = monoid.identity(), rightval = monoid.identity();
        l += ext_n, r += ext_n;
        while(l < r)
        {
            if(l & 1) leftval = monoid(leftval, data[l++]);
            if(r & 1) rightval = monoid(rightval, data[--r]);
            l >>= 1, r >>= 1;
        }
        return monoid(leftval, rightval);
    }

    value_type &operator[](size_t i) { return que.push(i += ext_n), data[i]; }

    // minimum l where range [l, idx) meets the condition.
    size_t left_bound(size_t i, const std::function<bool(const value_type &)> &pred)
    {
        assert(i <= orig_n), rebuild();
        size_t res = i;
        value_type now = monoid.identity();
        left_bound(i, pred, 1, 0, ext_n, now, res);
        return res;
    }

    // maximum r where range [idx, r) meets the condition.
    size_t right_bound(size_t i, const std::function<bool(const value_type &)> &pred)
    {
        assert(i < orig_n), rebuild();
        size_t res = i;
        value_type now = monoid.identity();
        right_bound(i, pred, 1, 0, ext_n, now, res);
        return res < orig_n ? res : orig_n;
    }
}; // class segment_tree
#endif