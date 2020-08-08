#pragma once
#include <cassert>
#include <vector>
// the base class of flow algorithms.
template <class cap_t, class cost_t>
struct flow_base
{
    struct edge_t
    {
        size_t src, dst; cap_t cap; cost_t cost; edge_t *rev;
        edge_t() = default;
        edge_t(size_t src, size_t dst, cap_t cap, edge_t *rev) : src(src), dst(dst), cap(cap), rev(rev) {}
        edge_t(size_t src, size_t dst, cap_t cap, cost_t cost, edge_t *rev) : src(src), dst(dst), cap(cap), cost(cost), rev(rev) {}
        void flow(cap_t f) { cap -= f, rev->cap += f; }
        bool avbl() const { return cap > 0; }
    }; // class edge_t

    class adj_type
    {
        edge_t *fst, *lst, *clst;
    public:
        template <class ...Args>
        edge_t *emplace(Args&& ...args)
        {
            if(lst == clst)
            {
                size_t len(clst - fst);
                edge_t *nfst = lst = new edge_t[len << 1];
                for(edge_t *p{fst}; p != clst; ++p, ++lst) p->rev->rev = lst, *lst = *p;
                delete[] fst; fst = nfst;
                clst = lst + len;
            }
            *lst = edge_t(args...);
            return lst++;
        }
        adj_type() : fst(new edge_t[1]), lst(fst), clst(fst + 1) {}
        ~adj_type() { delete[] fst; }
        edge_t &operator[](size_t i) { assert(i < size()); return *(fst + i); }
        size_t size() const { return lst - fst; }
        edge_t *begin() const { return fst; }
        edge_t *end() const { return lst; }
    }; // class adj_type

    flow_base(size_t n = 0) : adjs(n) {}

    flow_base(const flow_base& other) : adjs(other.size())
    {
        for(size_t node{}; node != size(); ++node)
            for(const auto &[src, dst, cap, cost, rev] : other[node])
                if(src == node)
                {
                    edge_t *ptr = adjs[src].emplace(src, dst, cap, cost, nullptr);
                    ptr->rev = adjs[dst].emplace(dst, src, rev->cap, -cost, ptr);
                    rev->src = -1;
                }
                else rev->rev->src = node;
    }

    flow_base &operator=(const flow_base &rhs)
    {
        if(this != &rhs) std::swap(adjs, flow_base(rhs).adjs);
        return *this;
    }

    size_t size() const { return adjs.size(); }

    adj_type &operator[](size_t node) { assert(node < size()); return adjs[node]; }
    const adj_type &operator[](size_t node) const { assert(node < size()); return adjs[node]; }

    void add_edge(size_t src, size_t dst, cap_t cap, cost_t cost)
    {
        assert(src < size()); assert(dst < size());
        if(!(cap > 0) || src == dst) return;
        edge_t *ptr = adjs[src].emplace(src, dst, cap, cost, nullptr);
        ptr->rev = adjs[dst].emplace(dst, src, 0, -cost, ptr);
    }

protected:
    std::vector<adj_type> adjs;
}; // class flow_base
