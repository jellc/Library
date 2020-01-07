// Base class
template <class cap_t, class cost_t>
struct Flow
{
    struct edge_t
    {
        size_t from, to; cap_t cap; cost_t cost; size_t rev;
        edge_t(size_t _from, size_t _to, cap_t _cap, cost_t _cost, size_t _rev) : from(_from), to(_to), cap(_cap), cost(_cost), rev(_rev) {}
    }; // struct edge_t

  protected:
    size_t V;
    std::vector<std::vector<edge_t>> adj;

  public:
    Flow(size_t _V) : V(_V), adj(_V) {}

    size_t size() const { return V; }
    std::vector<edge_t> &operator[](size_t v) { return adj[v]; }

    void add_edge(size_t from, size_t to, cap_t cap, cost_t cost)
    {
        adj[from].emplace_back(from, to, cap, cost, adj[to].size());
        adj[to].emplace_back(to, from, 0, -cost, adj[from].size() - 1);
    }
}; // struct Flow


template <class cap_t>
class Dinic : public Flow<cap_t, cap_t>
{
    using Base = Flow<cap_t, cap_t>;

    std::vector<size_t> level, itr;

    bool bfs(size_t s, size_t t)
    {
        fill(level.begin(), level.end(), ~0);
        std::queue<size_t> que;
        que.emplace(s);
        level[s] = 0;
        while(!que.empty())
        {
            size_t v = que.front(); que.pop();
            for(const typename Base::edge_t &e : Base::adj[v])
            {
                if(e.cap > cap_t(0) && not ~level[e.to])
                {
                    level[e.to] = level[v] + 1;
                    que.emplace(e.to);
                }
            }
        }
        return ~level[t];
    }

    cap_t dfs(size_t v, size_t t, cap_t f)
    {
        if(v == t) return f;
        cap_t res(0);
        while(itr[v] < Base::adj[v].size())
        {
            typename Base::edge_t &e = Base::adj[v][itr[v]];
            if(e.cap > cap_t(0) && level[v] < level[e.to])
            {
                cap_t d = dfs(e.to, t, std::min(f, e.cap));
                e.cap -= d;
                Base::adj[e.to][e.rev].cap += d;
                res += d;
                if((f -= d) == cap_t(0)) break;
            }
            ++itr[v];
        }
        return res;
    }

  public:
    Dinic(size_t V) : Base::Flow(V), level(V), itr(V) {}

    void add_edge(size_t s, size_t t, cap_t cap) { Base::add_edge(s, t, cap, 0); }

    cap_t max_flow(size_t s, size_t t)
    {
        cap_t res = 0, f;
        while(bfs(s, t))
        {
            fill(itr.begin(), itr.end(), 0);
            while((f = dfs(s, t, std::numeric_limits<cap_t>::max())) > cap_t(0)) res += f;
        }
        return res;
    }

    class cut_t
    {
        size_t V; bool* const data;
        friend class Dinic;
      public:
        cut_t(size_t _V) : V(_V), data(new bool[V]()) {}
        ~cut_t() { delete[] data; }

        size_t size() const { return V; }
        bool &operator[](size_t v) const { return data[v]; }
        bool *begin() const { return data; }
        bool *end() const { return data + V; }
        friend std::ostream &operator<<(std::ostream &s, const cut_t &cut)
        {
            bool is_front = true;
            for(bool b : cut)
            {
                if(is_front) is_front = false;
                else s << ' ';
                s << b;
            }
            return s;
        }
    }; // class cut_t

    cut_t min_cut(size_t s, size_t t)
    {
        while(bfs(s, t))
        {
            fill(itr.begin(), itr.end(), 0);
            while(dfs(s, t, std::numeric_limits<cap_t>::max()) > cap_t(0));
        }
        cut_t res(Base::V);
        for(size_t v = 0; v != Base::V; ++v) if(~level[v]) res.data[v] = 1;
        return res;
    }
}; // class Dinic