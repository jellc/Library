#include <queue>

// Computing the maximum flow
// depends on base.hpp
template <class cap_t>
class Dinic : public flow_base<cap_t, bool>
{
    using base = flow_base<cap_t, bool>;
    std::vector<size_t> level, itr;
    cap_t max_cap;

    bool bfs(size_t src, size_t dst)
    {
        fill(level.begin(), level.end(), -1);
        std::queue<size_t> que;
        que.emplace(src);
        level[src] = 0;
        while(!que.empty())
        {
            size_t node = que.front(); que.pop();
            for(const auto &e : base::adj[node])
            {
                if(e.cap > 0 && level[e.dst] == size_t(-1))
                {
                    level[e.dst] = level[node] + 1;
                    que.emplace(e.dst);
                }
            }
        }
        return ~level[dst];
    }

    cap_t dfs(size_t node, size_t dst, cap_t f)
    {
        if(node == dst) return f;
        cap_t res(0);
        while(itr[node] < base::adj[node].size())
        {
            auto &e = base::adj[node][itr[node]];
            if(e.cap > 0 && level[node] < level[e.dst])
            {
                cap_t d = dfs(e.dst, dst, std::min(f, e.cap));
                e.cap -= d;
                base::adj[e.dst][e.rev].cap += d;
                res += d;
                if((f -= d) == 0) break;
            }
            ++itr[node];
        }
        return res;
    }

public:
    Dinic(size_t _n = 0) : base::flow_base(_n), level(_n), itr(_n), max_cap(0) {}

    void add_edge(size_t src, size_t dst, cap_t cap)
    {
        max_cap = std::max(max_cap, cap);
        base::add_edge(src, dst, cap, 0);
    }

    cap_t max_flow(size_t src, size_t dst)
    {
        cap_t flow(0);
        while(bfs(src, dst))
        {
            fill(itr.begin(), itr.end(), 0);
            cap_t resid; while((resid = dfs(src, dst, max_cap)) > 0) flow += resid;
        }
        return flow;
    }

    std::vector<bool> min_cut(size_t src, size_t dst)
    {
        while(bfs(src, dst))
        {
            fill(itr.begin(), itr.end(), 0);
            while(dfs(src, dst, max_cap) > 0);
        }
        std::vector<bool> res(base::size());
        for(size_t node = base::size(); node--; ) if(~level[node]) res[node] = true;
        return res;
    }
}; // class Dinic