template <class Monoid, class act_t>
class Segment_tree
{
    std::vector<Monoid> data;

  public:
    const std::size_t n, N;

    using opr_t = std::function<Monoid(const Monoid &, const Monoid &)>;
    using update_opr_t = std::function<void(Monoid &, const act_t &)>;
    const opr_t opr;
    const update_opr_t update_opr;
    const Monoid identity;

    explicit Segment_tree(std::size_t _n, const Monoid &_identity, const opr_t &_opr,
                 const update_opr_t &_update_opr)
        : n(_n), N(_n > 1 ? 1 << (32 - __builtin_clz(_n - 1)) : 1), opr(_opr),
          update_opr(_update_opr), identity(_identity)
    {
        data.assign(N << 1, identity);
    }

    Monoid operator[](std::size_t i)
    {
        return data[i + N];
    }

    template <class P>
    void copy(P s, P t)
    {
        for(std::size_t i = N; s != t; ++s, ++i)
            data[i] = *s;
        for(std::size_t i = N - 1; i; --i)
            data[i] = opr(data[left(i)], data[right(i)]);
    }

    template <class A>
    void copy(const A &v)
    {
        copy(begin(v), end(v));
    }

    void init(const Monoid &x)
    {
        for(std::size_t i = 0; i < N; ++i)
            data[i + N] = x;
        for(std::size_t i = N - 1; i; --i)
            data[i] = opr(data[left(i)], data[right(i)]);
    }

    void update(std::size_t idx, const act_t &actor)
    {
        update_opr(data[idx += N], actor);
        while(idx >>= 1)
            data[idx] = opr(data[idx * 2], data[idx * 2 + 1]);
    }

    // operation result of range [a, b).
    Monoid query(std::size_t a, std::size_t b) const
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
    std::size_t right_bound(std::size_t idx,
                            const std::function<bool(const Monoid &)> &f)
    {
        assert(idx < n);
        std::size_t ret = idx;
        Monoid now = identity;
        right_bound(idx, f, 1, 0, N, now, ret);
        return std::min(ret, n);
    }

    // minimum l where range [l, idx) meets the condition.
    std::size_t left_bound(std::size_t idx,
                           const std::function<bool(const Monoid &)> &f)
    {
        assert(idx <= n);
        std::size_t ret = idx;
        Monoid now = identity;
        left_bound(idx, f, 1, 0, N, now, ret);
        return ret;
    }

  private:
    constexpr std::size_t left(const std::size_t k)
    {
        return k * 2;
    }

    constexpr std::size_t right(const std::size_t k)
    {
        return left(k) ^ 1;
    }

    constexpr std::size_t parent(const std::size_t k)
    {
        return k >> 1;
    }

    constexpr std::size_t sibling(const std::size_t k)
    {
        return k ^ 1;
    }

    void right_bound(std::size_t idx,
                     const std::function<bool(const Monoid &)> &f,
                     std::size_t k, std::size_t l, std::size_t r, Monoid &now,
                     std::size_t &pos)
    {
        if(idx >= r || l > pos) return;
        const std::size_t mid = (l + r) / 2;
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

    void left_bound(std::size_t idx,
                    const std::function<bool(const Monoid &)> &f, std::size_t k,
                    std::size_t l, std::size_t r, Monoid &now, std::size_t &pos)
    {
        if(idx <= l || r < pos) return;
        const std::size_t mid = (l + r) / 2;
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
};

template <class Monoid, class act_t>
class Lazy_segment_tree
{
    std::vector<Monoid> data;
    std::vector<act_t> lazy;
    std::vector<bool> lazyflag;

  public:
    const std::size_t n, N;

    using opr_t = std::function<Monoid(const Monoid &, const Monoid &)>;
    using lazy_opr_t = std::function<void(act_t &, const act_t &, std::size_t)>;
    using update_opr_t =
        std::function<void(Monoid &, const act_t &, std::size_t)>;
    const opr_t opr;
    const lazy_opr_t lazy_opr;
    const update_opr_t update_opr;
    const Monoid identity, lazy_identity;

    explicit Lazy_segment_tree(std::size_t _n, const Monoid &_identity,
                      const Monoid &_lazy_identity, const opr_t &_opr,
                      const lazy_opr_t &_lazy_opr,
                      const update_opr_t &_update_opr)
        : n(_n), N(_n > 1 ? 1 << (32 - __builtin_clz(_n - 1)) : 1), opr(_opr),
          lazy_opr(_lazy_opr), update_opr(_update_opr), identity(_identity),
          lazy_identity(_lazy_identity)
    {
        data.assign(N << 1, identity);
        lazy.assign(N << 1, lazy_identity);
        lazyflag.assign(N << 1, false);
    }

    Monoid operator[](std::size_t i)
    {
        return query(i, i + 1);
    }

    template <class P>
    void copy(P s, P t)
    {
        for(std::size_t i = N; s != t; ++s, ++i)
            data[i] = *s;
        for(std::size_t i = N - 1; i; --i)
            data[i] = opr(data[left(i)], data[right(i)]);
    }

    template <class A>
    void copy(A &v)
    {
        copy(begin(v), end(v));
    }

    void init(const Monoid &x)
    {
        for(std::size_t i = 0; i < N; ++i)
            data[i + N] = x;
        for(std::size_t i = N - 1; i; --i)
            data[i] = opr(data[left(i)], data[right(i)]);
    }

    void update(std::size_t a, const act_t &actor)
    {
        update(a, a + 1, actor);
    }

    void update(std::size_t a, std::size_t b, const act_t &actor)
    {
        update(a, b, actor, 1, 0, N);
    }

    Monoid query(std::size_t a, std::size_t b)
    {
        return query(a, b, 1, 0, N);
    }

    std::size_t right_bound(std::size_t idx,
                            const std::function<bool(const Monoid &)> &f)
    {
        assert(idx < n);
        std::size_t ret = idx;
        Monoid now = identity;
        right_bound(idx, f, 1, 0, N, now, ret);
        return std::min(ret, n);
    }

    std::size_t left_bound(std::size_t idx,
                           const std::function<bool(const Monoid &)> &f)
    {
        assert(idx <= n);
        std::size_t ret = idx;
        Monoid now = identity;
        left_bound(idx, f, 1, 0, N, now, ret);
        return ret;
    }

  private:
    constexpr std::size_t left(const std::size_t k)
    {
        return k * 2;
    }

    constexpr std::size_t right(const std::size_t k)
    {
        return left(k) ^ 1;
    }

    constexpr std::size_t parent(const std::size_t k)
    {
        return k >> 1;
    }

    constexpr std::size_t sibling(const std::size_t k)
    {
        return k ^ 1;
    }

    void eval(std::size_t k, std::size_t l, std::size_t r)
    {
        if(!lazyflag[k]) return;
        update_opr(data[k], lazy[k], r - l);
        if(r - l > 1)
        {
            lazy_opr(lazy[left(k)], lazy[k], (r - l) / 2);
            lazy_opr(lazy[right(k)], lazy[k], (r - l) / 2);
            lazyflag[left(k)] = lazyflag[right(k)] = true;
        }
        lazy[k] = lazy_identity;
        lazyflag[k] = false;
    }

    void update(std::size_t a, std::size_t b, const act_t &actor, std::size_t k,
                std::size_t l, std::size_t r)
    {
        eval(k, l, r);
        if(b <= l || r <= a) return;
        if(a <= l && r <= b)
        {
            lazy_opr(lazy[k], actor, r - l);
            lazyflag[k] = true;
            eval(k, l, r);
        }
        else
        {
            update(a, b, actor, left(k), l, (l + r) / 2);
            update(a, b, actor, right(k), (l + r) / 2, r);
            data[k] = opr(data[left(k)], data[right(k)]);
        }
    }

    Monoid query(std::size_t a, std::size_t b, std::size_t k, std::size_t l,
                 std::size_t r)
    {
        if(b <= l || r <= a) return identity;
        eval(k, l, r);
        if(a <= l && r <= b) return data[k];
        return opr(query(a, b, left(k), l, (l + r) / 2),
                   query(a, b, right(k), (l + r) / 2, r));
    }

    void right_bound(std::size_t idx,
                     const std::function<bool(const Monoid &)> &f,
                     std::size_t k, std::size_t l, std::size_t r, Monoid &now,
                     std::size_t &pos)
    {
        if(idx >= r || l > pos) return;
        eval(k, l, r);
        const std::size_t mid = (l + r) / 2;
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

    void left_bound(std::size_t idx,
                    const std::function<bool(const Monoid &)> &f, std::size_t k,
                    std::size_t l, std::size_t r, Monoid &now, std::size_t &pos)
    {
        if(idx <= l || r < pos) return;
        eval(k, l, r);
        const std::size_t mid = (l + r) / 2;
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
};