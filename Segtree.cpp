#include <bits/stdc++.h>
using namespace std;



template <class Monoid, class act_t>
struct Segtree {
    vector<Monoid> data;
    const size_t n, N;

    using opr_t = function<Monoid(const Monoid&, const Monoid&)>;
    using update_opr_t = function<void(Monoid&, const act_t&)>;
    const opr_t opr;
    const update_opr_t update_opr;
    const Monoid identity;

    constexpr size_t adjust_size(const int32_t n) {
        size_t d = 0; 
        for(size_t i = 0; i < 30; ++i) if(n >> i & 1) d = i; 
        return 1 << (d + 1);
    }

    constexpr size_t left(const size_t k) { return k * 2; }

    constexpr size_t right(const size_t k) { return left(k) ^ 1; }

    constexpr size_t parent(const size_t k) { return k >> 1; }

    constexpr size_t sibling(const size_t k) { return k ^ 1; }

    Segtree(size_t _n, const Monoid &_identity, const opr_t &_opr, const update_opr_t &_update_opr)
        : n(_n), N(adjust_size(_n)), opr(_opr), update_opr(_update_opr), identity(_identity)
    {
        data.assign(N << 1, identity);
    }

    const Monoid& operator[](size_t i) { return data[i + N]; }

    template <class P> void copy(P s, P t) {
        for(size_t i = N; s != t; ++s, ++i) data[i] = *s;
        for(size_t i = N - 1; i; --i) data[i] = opr(data[left(i)], data[right(i)]);
    }

    template <class A> void copy(const A &v) { copy(begin(v), end(v)); }

    void init(const Monoid &x) {
        for(size_t i = 0; i < N; ++i) data[i + N] = x;
        for(size_t i = N - 1; i; --i) data[i] = opr(data[left(i)], data[right(i)]);
    }

    void update(size_t idx, act_t val) {
        update_opr(data[idx += N], val);
        while(idx >>= 1) data[idx] = opr(data[idx * 2], data[idx * 2 + 1]);
    }

    Monoid query(size_t a, size_t b, bool is_first = true) const {
        if(a >= b) return identity;
        if(is_first) a += N, b += N;
        Monoid left = a & 1 ? data[a++] : identity;
        Monoid right = b & 1 ? data[--b] : identity;
        return opr(opr(left, query(a >> 1, b >> 1, false)), right);
    }

    size_t rightbound(size_t idx, const function<bool(const Monoid&)> &judge) {
        assert(idx < n);
        size_t ret = idx;
        Monoid now = identity;
        rightbound(idx, judge, 1, 0, N, now, ret);
        return min(ret, n);
    }

    void rightbound(size_t idx, const function<bool(const Monoid&)> &judge, size_t k, size_t l, size_t r, Monoid &now, size_t &pos) {
        if(idx >= r || l > pos) return;
        const size_t mid = (l + r) / 2;
        if(l >= idx) {
            Monoid nxt = opr(now, data[k]);
            if(judge(nxt)) {
                pos = r; now = nxt;
                return;
            }
        }
        if(r - l > 1) {
            rightbound(idx, judge, left(k), l, mid, now, pos);
            rightbound(idx, judge, right(k), mid, r, now, pos);
        }
    }

    size_t leftbound(size_t idx, const function<bool(const Monoid&)> &judge) {
        assert(idx <= n);
        size_t ret = idx;
        Monoid now = identity;
        leftbound(idx, judge, 1, 0, N, now, ret);
        return ret;
    }

    void leftbound(size_t idx, const function<bool(const Monoid&)> &judge, size_t k, size_t l, size_t r, Monoid &now, size_t &pos) {
        if(idx <= l || r < pos) return;
        const size_t mid = (l + r) / 2;
        if(r <= idx) {
            Monoid nxt = opr(data[k], now);
            if(judge(nxt)) {
                pos = l; now = nxt;
                return;
            }
        }
        if(r - l > 1) {
            leftbound(idx, judge, right(k), mid, r, now, pos);
            leftbound(idx, judge, left(k), l, mid, now, pos);
        }
    }
};



template <class Monoid, class act_t>
struct LazySegtree {
    const size_t n, N;
    vector<Monoid> data;
    vector<act_t> lazy;
    vector<bool> lazyflag;

    using opr_t = function<Monoid(const Monoid&, const Monoid&)>;
    using lazy_opr_t = function<void(act_t&, const act_t&, size_t)>;
    using update_opr_t = function<void(Monoid&, const act_t&, size_t)>;
    const opr_t opr;
    const lazy_opr_t lazy_opr;
    const update_opr_t update_opr;
    const Monoid identity, lazy_identity;

    constexpr size_t adjust_size(const size_t n) {
        size_t d = 0; 
        for(size_t i = 0; i < 30; ++i) if(n >> i & 1) d = i; 
        return 1 << (d + 1);
    }

    constexpr size_t left(const size_t k) { return k * 2; }

    constexpr size_t right(const size_t k) { return left(k) ^ 1; }

    constexpr size_t parent(const size_t k) { return k >> 1; }

    constexpr size_t sibling(const size_t k) { return k ^ 1; }

    LazySegtree(size_t _n, const Monoid &_identity, const Monoid &_lazy_identity, const opr_t &_opr, const lazy_opr_t &_lazy_opr, const update_opr_t &_update_opr)
        : n(_n), N(adjust_size(_n)), opr(_opr), lazy_opr(_lazy_opr), update_opr(_update_opr), identity(_identity), lazy_identity(_lazy_identity)
    {
        data.assign(N << 1, identity);
        lazy.assign(N << 1, lazy_identity);
        lazyflag.assign(N << 1, false);
    }

    const Monoid& operator[](size_t i) { return query(i, i + 1); }

    template <class P> void copy(P s, P t) {
        for(size_t i = N; s != t; ++s, ++i) data[i] = *s;
        for(size_t i = N - 1; i; --i) data[i] = opr(data[left(i)], data[right(i)]);
    }

    template <class A> void copy(A &v) { copy(begin(v), end(v)); }

    void init(const Monoid &x) {
        for(size_t i = 0; i < N; ++i) data[i + N] = x;
        for(size_t i = N - 1; i; --i) data[i] = opr(data[left(i)], data[right(i)]);
    }

    void eval(size_t k, size_t l, size_t r) {
        if(!lazyflag[k]) return;
        update_opr(data[k], lazy[k], r - l);
        if(r - l > 1) {
            lazy_opr(lazy[left(k)], lazy[k], (r - l) / 2);
            lazy_opr(lazy[right(k)], lazy[k], (r - l) / 2);
            lazyflag[left(k)] = lazyflag[right(k)] = true;
        }
        lazy[k] = lazy_identity;
        lazyflag[k] = false;
    }

    void update(size_t a, size_t b, const act_t &actor) { update(a, b, actor, 1, 0, N); }

    void update(size_t a, size_t b, const act_t &actor, size_t k, size_t l, size_t r) {
        eval(k, l, r);
        if(b <= l || r <= a) return;
        if(a <= l && r <= b) {
            lazy_opr(lazy[k], actor, r - l);
            lazyflag[k] = true;
            eval(k, l, r);
        } else {
            update(a, b, actor, left(k), l, (l + r) / 2);
            update(a, b, actor, right(k), (l + r) / 2, r);
            data[k] = opr(data[left(k)], data[right(k)]);
        }
    }

    Monoid query(size_t a, size_t b) { return query(a, b, 1, 0, N); }

    Monoid query(size_t a, size_t b, size_t k, size_t l, size_t r) {
        if(b <= l || r <= a) return identity;
        eval(k, l, r);
        if(a <= l && r <= b) return data[k];
        return opr(query(a, b, left(k), l, (l + r) / 2), query(a, b, right(k), (l + r) / 2, r));
    }

    size_t rightbound(size_t idx, const function<bool(const Monoid&)> &judge) {
        assert(idx < n);
        size_t ret = idx;
        Monoid now = identity;
        rightbound(idx, judge, 1, 0, N, now, ret);
        return min(ret, n);
    }

    void rightbound(size_t idx, const function<bool(const Monoid&)> &judge, size_t k, size_t l, size_t r, Monoid &now, size_t &pos) {
        if(idx >= r || l > pos) return;
        eval(k, l, r);
        const size_t mid = (l + r) / 2;
        if(l >= idx) {
            Monoid nxt = opr(now, data[k]);
            if(judge(nxt)) {
                pos = r; now = nxt;
                return;
            }
        }
        if(r - l > 1) {
            rightbound(idx, judge, left(k), l, mid, now, pos);
            rightbound(idx, judge, right(k), mid, r, now, pos);
        }
    }

    size_t leftbound(size_t idx, const function<bool(const Monoid&)> &judge) {
        assert(idx <= n);
        size_t ret = idx;
        Monoid now = identity;
        leftbound(idx, judge, 1, 0, N, now, ret);
        return ret;
    }

    void leftbound(size_t idx, const function<bool(const Monoid&)> &judge, size_t k, size_t l, size_t r, Monoid &now, size_t &pos) {
        if(idx <= l || r < pos) return;
        eval(k, l, r);
        const size_t mid = (l + r) / 2;
        if(r <= idx) {
            Monoid nxt = opr(data[k], now);
            if(judge(nxt)) {
                pos = l; now = nxt;
                return;
            }
        }
        if(r - l > 1) {
            leftbound(idx, judge, right(k), mid, r, now, pos);
            leftbound(idx, judge, left(k), l, mid, now, pos);
        }
    }
};


