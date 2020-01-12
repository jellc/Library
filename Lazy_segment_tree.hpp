#ifndef LAZY_SEGMENT_TREE_HPP
#define LAZY_SEGMENT_TREE_HPP
template <class Monoid, class Actor>
class lazy_segment_tree
{
    using value_type = typename Monoid::value_type;
    using actor_value_type = typename Actor::value_type;
    Monoid *const monoid_ptr, &monoid;
    Actor *const actor_ptr, &actor;
    const size_t orig_n, ext_n;
    std::vector<value_type> data;
    std::vector<actor_value_type> lazy;
    bool *const flag;

    void eval(size_t k, size_t l, size_t r)
    {
        if(!flag[k]) return;
        actor.act(data[k], lazy[k]);
        if(r - l > 1)
        {
            actor(lazy[k << 1], lazy[k]);
            actor(lazy[k << 1 ^ 1], lazy[k]);
            flag[k << 1] = flag[k << 1 ^ 1] = true;
        }
        lazy[k] = actor.identity(), flag[k] = false;
    }

    void update(size_t a, size_t b, const actor_value_type &x, size_t k, size_t l, size_t r)
    {
        eval(k, l, r);
        if(b <= l || r <= a) return;
        if(a <= l && r <= b)
        {
            actor(lazy[k], x);
            flag[k] = true;
            eval(k, l, r);
        }
        else
        {
            update(a, b, x, k << 1, l, (l + r) >> 1);
            update(a, b, x, k << 1 ^ 1, (l + r) >> 1, r);
            data[k] = monoid(data[k << 1], data[k << 1 ^ 1]);
        }
    }

    value_type fold(size_t a, size_t b, size_t k, size_t l, size_t r)
    {
        if(b <= l || r <= a) return monoid.identity();
        eval(k, l, r);
        if(a <= l && r <= b) return data[k];
        return monoid(fold(a, b, k << 1, l, (l + r) >> 1), fold(a, b, k << 1 ^ 1, (l + r) >> 1, r));
    }

    void left_bound(size_t idx, const std::function<bool(const value_type &)> &pred,
                    size_t k, size_t l, size_t r, value_type &now, size_t &res)
    {
        if(idx <= l || r < res) return;
        eval(k, l, r);
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
        eval(k, l, r);
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
    lazy_segment_tree(size_t n) : monoid_ptr{new Monoid}, monoid{*monoid_ptr}, actor_ptr{new Actor}, actor{*actor_ptr}, orig_n{n}, ext_n(n > 1 ? 1 << (32 - __builtin_clz(n - 1)) : 1),
                                    data(ext_n << 1, monoid.identity()), lazy(ext_n << 1, actor.identity()), flag(new bool[ext_n << 1]) {}
    lazy_segment_tree(size_t n, Monoid &_monoid) : monoid_ptr{}, monoid{_monoid}, actor_ptr{new Actor}, actor{*actor_ptr}, orig_n{n}, ext_n(n > 1 ? 1 << (32 - __builtin_clz(n - 1)) : 1),
                                                    data(ext_n << 1, monoid.identity()), lazy(ext_n << 1, actor.identity()), flag(new bool[ext_n << 1]) {}
    lazy_segment_tree(size_t n, Actor &_actor) : monoid_ptr{new Monoid}, monoid{*monoid_ptr}, actor_ptr{}, actor{_actor}, orig_n{n}, ext_n(n > 1 ? 1 << (32 - __builtin_clz(n - 1)) : 1),
                                                data(ext_n << 1, monoid.identity()), lazy(ext_n << 1, actor.identity()), flag(new bool[ext_n << 1]) {}
    lazy_segment_tree(size_t n, Monoid &_monoid, Actor &_actor) : monoid_ptr{}, monoid{_monoid}, actor_ptr{}, actor{_actor}, orig_n{n}, ext_n(n > 1 ? 1 << (32 - __builtin_clz(n - 1)) : 1),
                                                                data(ext_n << 1, monoid.identity()), lazy(ext_n << 1, actor.identity()), flag(new bool[ext_n << 1]) {}
    ~lazy_segment_tree() { if(monoid_ptr) delete monoid_ptr; if(actor_ptr) delete actor_ptr; delete[] flag; }

    // copy of value at index i.
    value_type operator[](size_t i) { return fold(i, i + 1); }

    void build(value_type *__first, value_type *__last)
    {
        std::copy(__first, __last, &data[ext_n]);
        for(size_t i = ext_n; i; --i) data[i] = monoid(data[i << 1], data[i << 1 ^ 1]);
    }

    template <class iterator>
    void build(iterator __first, iterator __last)
    {
        static_assert(std::is_same<typename std::iterator_traits<iterator>::value_type, value_type>::value, "iterator's value_type should be equal to Monoid's");
        std::copy(__first, __last, &data[ext_n]);
        for(size_t i = ext_n - 1; i; --i) data[i] = monoid(data[i << 1], data[i << 1 ^ 1]);
    }

    void init(const value_type &x)
    {
        for(size_t i = 0; i != ext_n; ++i) data[i | ext_n] = x;
        for(size_t i = ext_n - 1; i; --i) data[i] = monoid(data[i << 1], data[i << 1 ^ 1]);
    }

    void update(size_t a, const actor_value_type &x) { update(a, a + 1, x); }

    void update(size_t a, size_t b, const actor_value_type &x) { update(a, b, x, 1, 0, ext_n); }

    value_type fold(size_t a, size_t b) { return fold(a, b, 1, 0, ext_n); }

    // minimum l where range [l, idx) meets the condition.
    size_t left_bound(size_t i, const std::function<bool(const value_type &)> &pred)
    {
        assert(i <= orig_n);
        size_t res = i;
        value_type now = monoid.identity();
        left_bound(i, pred, 1, 0, ext_n, now, res);
        return res;
    }

    // maximum r where range [idx, r) meets the condition.
    size_t right_bound(size_t i, const std::function<bool(const value_type &)> &pred)
    {
        assert(i < orig_n);
        size_t res = i;
        value_type now = monoid.identity();
        right_bound(i, pred, 1, 0, ext_n, now, res);
        return res < orig_n ? res : orig_n;
    }
}; //class lazy_segment_tree
#endif
