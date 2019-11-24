template <class Monoid, class act_t>
class Segment_tree
{
    const size_t n, N;
    std::vector<Monoid> data;
    using opr_t = std::function<Monoid(const Monoid &, const Monoid &)>;
    using update_opr_t = std::function<void(Monoid &, const act_t &)>;
    const opr_t opr;
    const update_opr_t update_opr;
    const Monoid identity;

  public:
    Segment_tree(size_t _n, const Monoid &_identity, const opr_t &_opr,
                          const update_opr_t &_update_opr)
        : n(_n), N(n > 1 ? 1 << (32 - __builtin_clz(n - 1)) : 1), data(N << 1, _identity),
          opr(_opr), update_opr(_update_opr), identity(_identity)
    {}

    Monoid operator[](size_t i) { return data[i + N]; }

    template <class P> void build(P s, P t)
    {
        for(size_t i = N; s != t; ++s, ++i) data[i] = *s;
        for(size_t i = N - 1; i; --i) data[i] = opr(data[left(i)], data[right(i)]);
    }

    template <template <class, class> class A> void build(A<Monoid, std::allocator<Monoid>> &v) { build(std::begin(v), std::end(v)); }

    void init(const Monoid &x)
    {
        for(size_t i = 0; i < N; ++i) data[i + N] = x;
        for(size_t i = N - 1; i; --i) data[i] = opr(data[left(i)], data[right(i)]);
    }

    void update(size_t idx, const act_t &actor)
    {
        update_opr(data[idx += N], actor);
        while(idx >>= 1) data[idx] = opr(data[idx * 2], data[idx * 2 + 1]);
    }

    // operation result of range [a, b).
    Monoid query(size_t a, size_t b) const
    {
        Monoid lft = identity, rgt = identity;
        a += N, b += N;
        while(a < b)
        {
            if(a & 1) lft = opr(lft, data[a++]);
            if(b & 1) rgt = opr(data[--b], rgt);
            a >>= 1, b >>= 1;
        }
        return opr(lft, rgt);
    }

    // maximum r where range [idx, r) meets the condition.
    size_t right_bound(size_t idx, const std::function<bool(const Monoid &)> &f)
    {
        assert(idx < n);
        size_t ret = idx;
        Monoid now = identity;
        right_bound(idx, f, 1, 0, N, now, ret);
        return std::min(ret, n);
    }

    // minimum l where range [l, idx) meets the condition.
    size_t left_bound(size_t idx, const std::function<bool(const Monoid &)> &f)
    {
        assert(idx <= n);
        size_t ret = idx;
        Monoid now = identity;
        left_bound(idx, f, 1, 0, N, now, ret);
        return ret;
    }

  private:
    size_t left(const size_t k) const { return k * 2; }
    size_t right(const size_t k) const { return left(k) ^ 1; }
    size_t parent(const size_t k) const { return k >> 1; }
    size_t sibling(const size_t k) const { return k ^ 1; }

    void right_bound(size_t idx, const std::function<bool(const Monoid &)> &f,
                     size_t k, size_t l, size_t r, Monoid &now, size_t &pos)
    {
        if(idx >= r || l > pos) return;
        const size_t mid = (l + r) / 2;
        if(l >= idx)
        {
            Monoid nxt = opr(now, data[k]);
            if(f(nxt))
            {
                pos = r;
                now = nxt;
                return;
            }
        }
        if(r - l > 1)
        {
            right_bound(idx, f, left(k), l, mid, now, pos);
            right_bound(idx, f, right(k), mid, r, now, pos);
        }
    }

    void left_bound(size_t idx, const std::function<bool(const Monoid &)> &f,
                    size_t k, size_t l, size_t r, Monoid &now, size_t &pos)
    {
        if(idx <= l || r < pos) return;
        const size_t mid = (l + r) / 2;
        if(r <= idx)
        {
            Monoid nxt = opr(data[k], now);
            if(f(nxt))
            {
                pos = l;
                now = nxt;
                return;
            }
        }
        if(r - l > 1)
        {
            left_bound(idx, f, right(k), mid, r, now, pos);
            left_bound(idx, f, left(k), l, mid, now, pos);
        }
    }
}; // class Segment_tree

template <class Monoid, class act_t>
class Lazy_segment_tree
{
    const size_t n, N;
    std::vector<Monoid> data;
    std::vector<act_t> lazy;
    bool *const flag;

    using opr_t = std::function<Monoid(const Monoid&, const Monoid&)>;
    using lazy_opr_t = std::function<void(act_t&, const act_t&)>;
    using update_opr_t = std::function<void(Monoid&, const act_t&)>;
    const opr_t opr;
    const lazy_opr_t lazy_opr;
    const update_opr_t update_opr;
    const Monoid identity;
    const act_t lazy_identity;

  public:
    Lazy_segment_tree(size_t _n, const Monoid &_identity, const act_t &_lazy_identity, const opr_t &_opr, const lazy_opr_t &_lazy_opr, const update_opr_t &_update_opr)
        : n(_n), N(n > 1 ? 1 << (32 - __builtin_clz(n - 1)) : 1),
          data(N << 1, _identity), lazy(N << 1, _lazy_identity), flag(new bool[N << 1]),
          opr(_opr), lazy_opr(_lazy_opr), update_opr(_update_opr), identity(_identity), lazy_identity(_lazy_identity)
    {}

    ~Lazy_segment_tree() { delete[] flag; }

    Monoid operator[](size_t i) { return query(i, i + 1); }

    template <class P> void build(P s, P t)
    {
        for(size_t i = N; s != t; ++s, ++i) data[i] = *s;
        for(size_t i = N - 1; i; --i) data[i] = opr(data[left(i)], data[right(i)]);
    }

    template <template <class, class> class A> void build(A<Monoid, std::allocator<Monoid>> &v) { build(std::begin(v), std::end(v)); }

    void init(const Monoid &x)
    {
        for(size_t i = 0; i < N; ++i) data[i + N] = x;
        for(size_t i = N - 1; i; --i) data[i] = opr(data[left(i)], data[right(i)]);
    }

    void update(size_t a, const act_t &actor) { update(a, a + 1, actor); }

    void update(size_t a, size_t b, const act_t &actor) { update(a, b, actor, 1, 0, N); }

    Monoid query(size_t a, size_t b) { return query(a, b, 1, 0, N); }

    size_t right_bound(size_t idx, const std::function<bool(const Monoid &)> &f)
    {
        assert(idx < n);
        size_t ret = idx;
        Monoid now = identity;
        right_bound(idx, f, 1, 0, N, now, ret);
        return std::min(ret, n);
    }

    size_t left_bound(size_t idx, const std::function<bool(const Monoid &)> &f)
    {
        assert(idx <= n);
        size_t ret = idx;
        Monoid now = identity;
        left_bound(idx, f, 1, 0, N, now, ret);
        return ret;
    }

  private:
    size_t left(const size_t k) const { return k * 2; }
    size_t right(const size_t k) const { return left(k) ^ 1; }
    size_t parent(const size_t k) const { return k >> 1; }
    size_t sibling(const size_t k) const { return k ^ 1; }

    void eval(size_t k, size_t l, size_t r)
    {
        if(!flag[k]) return;
        update_opr(data[k], lazy[k]);
        if(r - l > 1)
        {
            lazy_opr(lazy[left(k)], lazy[k]);
            lazy_opr(lazy[right(k)], lazy[k]);
            flag[left(k)] = flag[right(k)] = true;
        }
        lazy[k] = lazy_identity, flag[k] = false;
    }

    void update(size_t a, size_t b, const act_t &actor, size_t k, size_t l, size_t r)
    {
        eval(k, l, r);
        if(b <= l || r <= a) return;
        if(a <= l && r <= b) lazy_opr(lazy[k], actor), flag[k] = true, eval(k, l, r);
        else
        {
            update(a, b, actor, left(k), l, (l + r) >> 1);
            update(a, b, actor, right(k), (l + r) >> 1, r);
            data[k] = opr(data[left(k)], data[right(k)]);
        }
    }

    Monoid query(size_t a, size_t b, size_t k, size_t l, size_t r)
    {
        if(b <= l || r <= a) return identity;
        eval(k, l, r);
        if(a <= l && r <= b) return data[k];
        return opr(query(a, b, left(k), l, (l + r) >> 1), query(a, b, right(k), (l + r) >> 1, r));
    }

    void right_bound(size_t idx, const std::function<bool(const Monoid &)> &f,
                     size_t k, size_t l, size_t r, Monoid &now, size_t &pos)
    {
        if(idx >= r || l > pos) return;
        eval(k, l, r);
        const size_t mid = (l + r) >> 1;
        if(l >= idx)
        {
            Monoid nxt = opr(now, data[k]);
            if(f(nxt))
            {
                pos = r;
                now = nxt;
                return;
            }
        }
        if(r - l > 1)
        {
            right_bound(idx, f, left(k), l, mid, now, pos);
            right_bound(idx, f, right(k), mid, r, now, pos);
        }
    }

    void left_bound(size_t idx, const std::function<bool(const Monoid &)> &f,
                    size_t k, size_t l, size_t r, Monoid &now, size_t &pos)
    {
        if(idx <= l || r < pos) return;
        eval(k, l, r);
        const size_t mid = (l + r) >> 1;
        if(r <= idx)
        {
            Monoid nxt = opr(data[k], now);
            if(f(nxt))
            {
                pos = l;
                now = nxt;
                return;
            }
        }
        if(r - l > 1)
        {
            left_bound(idx, f, right(k), mid, r, now, pos);
            left_bound(idx, f, left(k), l, mid, now, pos);
        }
    }
}; //class Lazy_segment_tree

namespace typical_binary_opr
{
    template <class T>
    void subst(T &x, T y)
    {
        x = y;
    }
    template <class T>
    void add(T &x, T y)
    {
        x += y;
    }
    template <class T>
    T minf(T x, T y)
    {
        return std::min(x, y);
    }
    template <class T>
    T maxf(T x, T y)
    {
        return std::max(x, y);
    }
} // namespace typical_binary_opr
using namespace typical_binary_opr;