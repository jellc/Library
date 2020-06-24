template <class cap_t, class cost_t>
class min_cost_flow : public flow_base<cap_t, cost_t>
{
    using base = flow_base<cap_t, cost_t>;
    using edge_t = typename base::edge_t;
    using base::adjs;

    cost_t min_cost, total_cost;
    std::vector<cap_t> supp;
    std::vector<cost_t> ptnl;

    void copy_member(const min_cost_flow &other)
    {
        min_cost = other.min_cost;
        total_cost = other.total_cost;
        supp = other.supp;
        ptnl = other.ptnl;
    }

    void Dijkstra(std::vector<edge_t*> &last)
    {
        const cost_t infty(total_cost + 1);
        std::vector<cost_t> dist(size(), infty);
        //*/ // O((V + E)logV)
        std::priority_queue<std::pair<cost_t, size_t>> que;
        for(size_t node{}; node != size(); ++node)
        {
            if(supp[node] > static_cast<cap_t>(0))
            {
                dist[node] = 0;
                que.emplace(0, node);
            }
        }
        while(!que.empty())
        {
            auto [nsp, node] = que.top();
            que.pop();
            if(-nsp != dist[node]) continue;
            ptnl[node] -= nsp;
            if(ptnl[node] > infty) ptnl[node] = infty;
            dist[node] = -1;
            for(edge_t &e : adjs[node])
            {
                if(dist[e.dst] == static_cast<cost_t>(-1) || e.cap == static_cast<cap_t>(0)) continue;
                if(dist[e.dst] + ptnl[e.dst] > ptnl[node] + e.cost)
                {
                    dist[e.dst] = ptnl[node] + e.cost - ptnl[e.dst];
                    last[e.dst] = &e;
                    que.emplace(-dist[e.dst], e.dst);
                }
            }
        }
        /*/ // O(V^2)
        size_t src(-1);
        for(size_t node{}; node != size(); ++node)
        {
            if(supp[node] > static_cast<cap_t>(0))
            {
                dist[node] = 0;
                src = node;
            }
        }
        while(~src)
        {
            ptnl[src] += dist[src];
            dist[src] = -1;
            for(edge_t &e : adjs[src])
            {
                if(dist[e.dst] == static_cast<cost_t>(-1) || e.cap == static_cast<cap_t>(0)) continue;
                if(dist[e.dst] + ptnl[e.dst] > ptnl[src] + e.cost)
                {
                    dist[e.dst] = ptnl[src] + e.cost - ptnl[e.dst];
                    last[e.dst] = &e;
                }
            }
            src = -1;
            cost_t nsp{infty};
            for(size_t node{}; node != size(); ++node)
            {
                if(dist[node] == static_cast<cost_t>(-1)) continue;
                if(nsp > dist[node])
                {
                    nsp = dist[node];
                    src = node;
                }
            }
        }
        //*/
    }

public:
    using base::size;

    min_cost_flow(size_t _n = 0) : base::flow_base(_n), min_cost(0), total_cost(0), supp(_n), ptnl(_n)  {}

    min_cost_flow(const min_cost_flow &other) : base::flow_base(other)
    {
        copy_member(other);
    }

    min_cost_flow &operator=(const min_cost_flow &other)
    {
        base::operator=(other);
        copy_member(other);
        return *this;
    }

    void add_edge(size_t src, size_t dst, cap_t cap, cost_t cost)
    {
        assert(src != dst);
        if(cost < static_cast<cost_t>(0))
        {
            supp[src] -= cap;
            supp[dst] += cap;
            min_cost += cap * cost;
            total_cost -= cap * cost;
            base::add_edge(dst, src, cap, -cost);
        }
        else
        {
            total_cost += cap * cost;
            base::add_edge(src, dst, cap, cost);
        }
    }

    void supply(size_t node, cap_t vol) { assert(node < size()); supp[node] += vol; }

    bool flow()
    {
        for(bool aug = true; aug; )
        {
            aug = false;
            std::vector<edge_t*> last(size());
            Dijkstra(last);
            std::vector<bool> shut(size());
            for(size_t dst{}; dst != size(); ++dst)
            {
                if(supp[dst] < static_cast<cap_t>(0) and last[dst])
                {
                    cap_t resid{-supp[dst]};
                    size_t src{dst}, block(-1);
                    while(last[src] && !shut[src])
                    {
                        if(resid >= last[src]->cap) resid = last[block = src]->cap;
                        src = last[src]->src;
                    }
                    if(shut[src]) block = src;
                    else
                    {
                        if(resid >= supp[src])
                        {
                            resid = supp[src];
                            block = src;
                        }
                        for(edge_t *e{last[dst]}; e; e = last[e->src])
                        {
                            e->cap -= resid;
                            e->rev->cap += resid;
                        }
                        supp[src] -= resid;
                        supp[dst] += resid;
                        min_cost += ptnl[dst] * resid;
                        aug = true;
                    }
                    if(~block)
                    {
                        for(size_t node{dst}; node != block; node = last[node]->src) shut[node] = true;
                        shut[block] = true;
                    }
                }
            }
        }
        for(cap_t s : supp) if(s > static_cast<cap_t>(0)) return false;
        return true;
    }

    cost_t optimal() { assert(flow()); return min_cost; }
}; // class min_cost_flow
