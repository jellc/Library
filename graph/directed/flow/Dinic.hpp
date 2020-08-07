#pragma once
#include "base.hpp"
// compute the maximum flow.
template <class cap_t = int>
class Dinic : public flow_base<cap_t, bool>
{
    using base = flow_base<cap_t, bool>;
    using edge_t = typename base::edge_t;
    using base::adjs;

    std::vector<size_t> level;
    std::vector<edge_t*> itr;
    constexpr static size_t level_infty = -1;

    cap_t dfs(const size_t &src, const size_t &dst, cap_t bound)
    {
        if(src == dst || bound == 0) return bound;
        cap_t flow(0);
        for(edge_t* &e{itr[dst]}; e != adjs[dst].end(); ++e)
            if(e->rev->avbl() && level[e->dst] < level[dst])
                if(cap_t achv = dfs(src, e->dst, std::min(bound, e->rev->cap)); achv > 0)
                {
                    e->rev->flow(achv);
                    flow += achv, bound -= achv;
                    if(bound == 0) break;
                }
        return flow;
    }

public:
    using base::size;

    Dinic(size_t n = 0) : base::flow_base(n), level(n, level_infty), itr(n) {}

    Dinic(const Dinic &other) : base::flow_base(other), level(other.level), itr(other.itr)  {}

    Dinic &operator=(const Dinic &rhs)
    {
        if(this != &rhs) base::operator=(rhs), level = rhs.level, itr = rhs.itr;
        return *this;
    }

    void add_edge(size_t src, size_t dst, cap_t cap) { base::add_edge(src, dst, cap, false); }

    void add_undirected_edge(size_t src, size_t dst, cap_t cap) { base::add_undirected_edge(src, dst, cap, false); }

    cap_t max_flow(size_t src, size_t dst)
    {
        assert(src < size()); assert(dst < size());
        cap_t flow(0), bound(0);
        for(const edge_t &e : adjs[src]) bound += e.cap;
        for(std::vector<size_t> que(size()); ; std::fill(level.begin(), level.end(), level_infty))
        {
            level[que.front() = src] = 0;
            for(auto ql{que.begin()}, qr{std::next(ql)}; level[dst] == level_infty && ql != qr; ++ql)
                for(const edge_t &e : adjs[*ql])
                    if(e.avbl() && level[e.dst] == level_infty)
                        level[*qr++ = e.dst] = level[*ql] + 1;
            if(level[dst] == level_infty) break;
            for(size_t node{}; node != size(); ++node) itr[node] = adjs[node].begin();
            flow += dfs(src, dst, bound);
        }
        return flow;
    }
}; // class Dinic
