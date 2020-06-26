#include <queue>

// Computing the maximum flow
// depends on base.hpp
template <class cap_t>
class Dinic : public flow_base<cap_t, bool>
{
    using base = flow_base<cap_t, bool>;
    using itr_type = typename base::adj_type::iterator;
    using base::adjs;

    std::vector<size_t> level;
    cap_t max_cap;

    bool bfs(size_t src, size_t dst)
    {
        fill(level.begin(), level.end(), -1);
        std::queue<size_t> que;
        que.emplace(src);
        level[src] = 0;
        while(!que.empty())
        {
            size_t node{que.front()};
            que.pop();
            for(const auto &e : adjs[node])
            {
                if(e.avbl() && level[e.dst] == size_t(-1))
                {
                    level[e.dst] = level[node] + 1;
                    que.emplace(e.dst);
                }
            }
        }
        return ~level[dst];
    }

    cap_t dfs(size_t node, size_t dst, cap_t bound, std::vector<itr_type> &itr)
    {
        if(node == dst) return bound;
        cap_t flow(0);
        for(itr_type &e{itr[node]}; e != adjs[node].end(); ++e)
        {
            if(e->avbl() && level[node] < level[e->dst])
            {
                cap_t achv = dfs(e->dst, dst, std::min(bound, e->cap), itr);
                e->cap -= achv, e->rev->cap += achv;
                flow += achv, bound -= achv;
                if(bound == 0) break;
            }
        }
        return flow;
    }

public:
    using base::size;

    Dinic(size_t _n = 0) : base::flow_base(_n), level(_n), max_cap(0) {}

    Dinic(const Dinic &other) : base::flow_base(other), level(other.level), max_cap(other.max_cap) {}

    Dinic &operator=(const Dinic &other)
    {
        base::operator=(other);
        level = other.level;
        max_cap = other.max_cap;
        return *this;
    }

    void add_edge(size_t src, size_t dst, cap_t cap)
    {
        max_cap = std::max(max_cap, cap);
        base::add_edge(src, dst, cap, 0);
    }

    cap_t max_flow(size_t src, size_t dst)
    {
        assert(src < size()); assert(dst < size());
        cap_t flow(0);
        std::vector<itr_type> itr(size());
        while(bfs(src, dst))
        {
            for(size_t node{0}; node != size(); ++node) itr[node] = adjs[node].begin();
            cap_t resid; while((resid = dfs(src, dst, max_cap, itr)) > 0) flow += resid;
        }
        return flow;
    }

    std::vector<bool> min_cut(size_t src, size_t dst)
    {
        max_flow(src, dst);
        std::vector<bool> res(size());
        for(size_t node{}; node != size(); ++node) res[node] = ~level[node];
        return res;
    }
}; // class Dinic
