template <class Abel>
// Abel must be an abelian group.
struct Fenwick_tree
{
    using ary_t = vector<Abel>;

    const std::size_t n;
    const Abel identity;
    ary_t data;

    explicit Fenwick_tree(std::size_t _n, Abel _identity = Abel())
        : n(_n), identity(_identity)
    {
        data.assign(n + 1, identity);
    }

    void inc(std::size_t i, Abel x)
    {
        for(++i; i <= n; i += i & -i)
        {
            data[i] += x;
        }
    }

    void subs(std::size_t i, Abel x)
    {
        inc(i, x - (*this)[i]);
    }

    // sum of range [0, i).
    Abel sum(std::size_t i) const
    {
        Abel ret = identity;
        for(; i; i &= (i - 1))
        {
            ret += data[i];
        }
        return ret;
    }

    // sum of range [l, r).
    Abel sum(std::size_t l, std::size_t r) const
    {
        return sum(r) - sum(l);
    }

    Abel operator[](std::size_t i) const
    {
        return sum(i + 1) - sum(i);
    }

    // maximum i where range [0, i) meets the condition.
    std::size_t bound(const std::function<bool(Abel)> &f)
    {
        Abel now = identity;
        std::size_t l = 0, r = n + 1;
        std::size_t bit = 1;
        while(bit <= n)
            bit <<= 1;
        while(r - l > 1)
        {
            while(bit >= r - l)
                bit >>= 1;
            if(f(now + data[l + bit]))
            {
                now += data[l + bit];
                l += bit;
            }
            else
            {
                r = l + bit;
            }
        }
        return l;
    }
};

template <class Abel>
// class Abel must be an abelian group.
struct Dynamic_fenwick_tree
{
    const std::size_t n;
    const Abel identity;
    std::unordered_map<std::size_t, Abel> data;

    explicit Dynamic_fenwick_tree(std::size_t _n, Abel _identity = Abel())
        : n(_n), identity(_identity)
    {}

    void inc(std::size_t i, Abel x)
    {
        for(++i; i <= n; i += i & -i)
        {
            data[i] += x;
        }
    }

    void subs(std::size_t i, Abel x)
    {
        inc(i, x - (*this)[i]);
    }

    // sum of range [0, i).
    Abel sum(std::size_t i)
    {
        Abel ret = identity;
        for(; i; i &= i - 1)
        {
            ret += data[i];
        }
        return ret;
    }

    // sum of range [l, r).
    Abel sum(std::size_t l, std::size_t r)
    {
        return l < r ? sum(r) - sum(l) : identity;
    }

    Abel operator[](std::size_t i)
    {
        return sum(i + 1) - sum(i);
    }

    // maximum i where range [0, i) meets the condition.
    std::size_t bound(const std::function<bool(Abel)> &f)
    {
        Abel now = identity;
        std::size_t l = 0, r = n + 1;
        std::size_t bit = 1;
        while(bit <= n)
            bit <<= 1;
        while(r - l > 1)
        {
            while(bit >= r - l)
                bit >>= 1;
            if(f(now + data[l + bit]))
            {
                now += data[l + bit];
                l += bit;
            }
            else
            {
                r = l + bit;
            }
        }
        return l;
    }
};

#include <bits/stdc++.h>
template <class Abel, typename index_t = int_fast64_t>
// class Abel must be an abelian group.
struct Bidirectional_fenwick_tree
{
    std::unordered_map<uint_fast64_t, Abel> p_dat, n_dat;
    const index_t inf;
    const Abel identity;

    explicit Bidirectional_fenwick_tree(
        const index_t _inf = std::numeric_limits<index_t>::max(),
        const Abel &_identity = Abel())
        : inf(_inf), identity(_identity)
    {}

    void inc(index_t i, Abel x)
    {
        if(i >= 0)
        {
            for(++i; i <= inf; i += i & -i)
            {
                p_dat[i] += x;
            }
        }
        else
        {
            for(i = -i; i <= inf; i += i & -i)
            {
                n_dat[i] += x;
            }
        }
    }

    // sum of range [l, r) if l < r, otherwise identity.
    Abel sum(index_t l, index_t r)
    {
        Abel res = identity;
        res += l >= 0 ? -sum(l) : sum(l);
        res += r >= 0 ? sum(r) : -sum(r);
        return l < r ? res : identity;
    }

    // sum of range [0, i) for i >= 0, [i, 0) for i < 0.
    Abel sum(index_t i)
    {
        Abel res = 0;
        if(i >= 0)
        {
            for(; i; i &= i - 1)
            {
                res += p_dat[i];
            }
        }
        else
        {
            for(i = -i; i; i &= i - 1)
            {
                res += n_dat[i];
            }
        }
        return res;
    }
};