#include <bits/stdc++.h>

template <class cap_t, class cost_t>
struct Flow
{
    struct edge_t
    {
        size_t from, to; cap_t cap; cost_t cost; size_t rev;
        edge_t(size_t _from, size_t _to, cap_t _cap, cost_t _cost, size_t _rev)
            : from(_from), to(_to), cap(_cap), cost(_cost), rev(_rev)
        {}
    };

  protected:
    size_t V;
    std::vector<std::vector<edge_t>> adj;

  public:
    Flow(size_t _V) : V(_V), adj(_V) {}

    void add_edge(size_t from, size_t to, cap_t cap, cost_t cost = cost_t(0))
    {
        adj[from].emplace_back(from, to, cap, cost, adj[to].size());
        adj[to].emplace_back(to, from, 0, -cost, adj[from].size() - 1);
    }
};

template <class cap_t, class cost_t>
class Dinic : public Flow<cap_t, cost_t>
{
    using edge_t = typename Flow<cap_t, cost_t>::edge_t;
    using Flow<cap_t, cost_t>::V;
    using Flow<cap_t, cost_t>::adj;
    
    std::vector<size_t> level, itr, que;

    bool bfs(size_t s, size_t t)
    {
        fill(level.begin(), level.end(), ~0);
        auto lit = que.begin(), rit = que.begin();
        *rit++ = s;
        level[s] = 0;
        while(lit != rit)
        {
            size_t v = *lit++;
            for(const edge_t &e : adj[v])
            {
                if(e.cap > cap_t(0) && not ~level[e.to])
                {
                    level[e.to] = level[v] + 1;
                    *rit++ = e.to;
                }
            }
        }
        return ~level[t];
    }

    cap_t dfs(size_t v, size_t t, cap_t f)
    {
        if(v == t) return f;
        for(; itr[v] < adj[v].size(); ++itr[v])
        {
            edge_t &e = adj[v][itr[v]];
            if(e.cap > cap_t(0) && level[v] < level[e.to])
            {
                cap_t d = dfs(e.to, t, std::min(f, e.cap));
                if(d > cap_t(0))
                {
                    e.cap -= d;
                    adj[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

  public:
    Dinic(size_t V) : Flow<cap_t, cost_t>::Flow(V), level(V), itr(V), que(V) {}

    size_t size() const { return V; }

    std::vector<edge_t> &operator[](size_t v) { return adj[v]; }

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
    };

    cut_t min_cut(size_t s, size_t t)
    {
        while(bfs(s, t))
        {
            fill(itr.begin(), itr.end(), 0);
            while(dfs(s, t, std::numeric_limits<cap_t>::max()) > cap_t(0));
        }
        cut_t res(V);
        for(size_t v = 0; v != V; ++v) if(~level[v]) res.data[v] = 1;
        return res;
    }
};

template <class cap_t, class cost_t = cap_t>
struct Flow
{
    struct edge_t
    {
        int from, to; cap_t cap; cost_t cost; size_t rev;
        edge_t(int _from, int _to, cap_t _cap, cost_t _cost, size_t _rev)
            : from(_from), to(_to), cap(_cap), cost(_cost), rev(_rev)
        {}
    };

    size_t V;
    vector<vector<size_t>> adj;
    vector<edge_t> edge;
    bool neg_edge_exist;

    Flow(size_t _V)
        : V(_V), edge(), neg_edge_exist()
    {
        adj.resize(V);
    }

    void add_edge(int from, int to, cap_t cap, cost_t cost)
    {
        assert(cap >= 0);
        size_t pos = edge.size();
        size_t rpos = pos + 1;
        edge.emplace_back(from, to, cap, cost, rpos);
        adj[from].emplace_back(pos);
        edge.emplace_back(to, from, 0, -cost, pos);
        adj[to].emplace_back(rpos); 
        if(cost < 0) neg_edge_exist = true;
    }

    vector<cost_t> Dijkstra(int s)
    {
        vector<cost_t> dist(V, inf<cost_t>);
        priority_queue<pair<cost_t,int>, vector<pair<cost_t,int>>, greater<pair<cost_t,int>>> que;
        que.emplace(dist[s] = 0, s);
        while(!que.empty()) {
            auto p = que.top(); que.pop();
            int v = p.second;
            if(dist[v] < p.first) continue;
            for(size_t i : adj[v])
            {
                edge_t &e = edge[i];
                if(e.cap > 0 && dist[v] + e.cost < dist[e.to]) que.emplace(dist[e.to] = dist[v] + e.cost, e.to);
            } 
        }
        return dist;
    }

    struct Fold_Fulkerson_exe
    {
        vector<edge_t> &edge;
        vector<vector<size_t>> &adj;  
        vector<bool> used;

        Fold_Fulkerson_exe(Flow &_F) : edge(_F.edge), adj(_F.adj)
        {
            used.resize(_F.V);
        }

        cap_t dfs(int v, int t, cap_t f)
        {
            if(v == t) return f;
            used[v] = true;
            for(size_t i : adj[v]) {
                edge_t &e = edge[i];
                if(!used[e.to] && e.cap > 0) {
                    cap_t d = dfs(e.to,t,min(f,e.cap));
                    if(d > 0) {
                        e.cap -= d;
                        edge[e.rev].cap += d;
                        return d;
                    }
                }
            }
            return 0;
        }

        cap_t max_flow(int s, int t)
        {
            cap_t flow = 0,f;
            while(true) {
                fill(begin(used),end(used),false);
                if((f = dfs(s,t,numeric_limits<cap_t>::max())) > 0) flow += f;
                else break;
            }
            return flow;
        }
    };

    cap_t Fold_Fulkerson(int s, int t) { return Fold_Fulkerson_exe(*this).max_flow(s,t); }
    
    struct Dinic_exe
    {
        vector<edge_t> &edge;
        vector<vector<size_t>> &adj;
        vector<int> level, itr;

        Dinic_exe(Flow &_F) : edge(_F.edge), adj(_F.adj), level(_F.V), itr(_F.V) {}

        void bfs(int s)
        {
            fill(begin(level), end(level), -1);
            vector<int> que(level.size());
            size_t litr = 0, ritr = 0;
            que[ritr++] = s;
            while(litr != ritr)
            {
                int v = que[litr++];
                for(size_t i : adj[v])
                {
                    edge_t &e = edge[i];
                    if(e.cap > 0 && level[e.to] < 0)
                    {
                        level[e.to] = level[v] + 1;
                        que[ritr++] = e.to;
                    }
                } 
            }
        }

        cap_t dfs(int v, int t, cap_t f)
        {
            if(v == t) return f;
            for(int &i = itr[v]; i < (int)adj[v].size(); ++i)
            {
                edge_t &e = edge[adj[v][i]];
                if(e.cap > 0 && level[v] < level[e.to])
                {
                    cap_t d = dfs(e.to, t, min(f, e.cap));
                    if(d > 0)
                    {
                        e.cap -= d;
                        edge[e.rev].cap += d;
                        return d;
                    }
                }
            }
            return 0;
        }

        cap_t max_flow(int s, int t)
        {
            cap_t flow = 0, f;
            while(bfs(s), level[t] >= 0)
            {
                fill(begin(itr), end(itr), 0);
                while((f = dfs(s, t, numeric_limits<cap_t>::max())) > 0) flow += f;
            }
            return flow;
        }
    };

    cap_t Dinic(int s, int t) { return Dinic_exe(*this).max_flow(s, t); }

    struct Primal_Dual_exe
    {
        vector<edge_t> &edge;
        vector<vector<size_t>> &adj;
        size_t &V;
        vector<cost_t> dist, h;
        vector<int> prev_v;
        vector<edge_t*> prev_e;

        Primal_Dual_exe(Flow &_F)
            : edge(_F.edge), adj(_F.adj), V(_F.V)
        {
            dist.resize(_F.V), h.resize(_F.V), prev_v.resize(_F.V), prev_e.resize(_F.V);
        }

        bool Dijkstra(int s, int t)
        {
            priority_queue<pair<cost_t,int>, vector<pair<cost_t,int>>, greater<pair<cost_t,int>>> que;
            fill(begin(dist), end(dist), inf<cost_t>);
            que.emplace(dist[s] = 0, s);
            while(!que.empty())
            {
                cost_t _cost; int v;
                tie(_cost, v) = que.top();
                que.pop();
                if(_cost != dist[v]) continue;
                for(size_t i : adj[v])
                {
                    edge_t &e = edge[i];
                    if(e.cap > 0 && dist[v] + h[v] + e.cost < dist[e.to] + h[e.to])
                    {
                        que.emplace(dist[e.to] = dist[v] + h[v] - h[e.to] + e.cost, e.to);
                        prev_v[e.to] = v;
                        prev_e[e.to] = &e;
                    }
                }
            } 
            if(dist[t] >= inf<cost_t>) return false;
            for(size_t v = 0; v < V; ++v)
            {
                h[v] += dist[v];
                if(h[v] > inf<cost_t>) h[v] = inf<cost_t>;
            }
            return true;
        }

        cost_t min_cost_flow(int s, int t, cap_t f)
        {
            cost_t res = 0;
            fill(begin(h), end(h), 0);
            while(f > 0)
            {
                if(!Dijkstra(s, t)) return inf<cost_t>;
                cap_t d = f;
                for(int v = t; v != s; v = prev_v[v]) d = min(d, prev_e[v]->cap);
                f -= d;
                res += h[t] * d;
                for(int v = t; v != s; v = prev_v[v])
                {
                    prev_e[v]->cap -= d;
                    edge[prev_e[v]->rev].cap += d;
                }
            }
            return res;
        }
    };

    cost_t Primal_Dual(int s, int t, cap_t f)
    {
        cost_t corr = 0;
        if(neg_edge_exist)
        {
            int _s = V++;
            int _t = V++;
            adj.resize(V);
            add_edge(_s, s, f, 0);
            add_edge(t, _t, f, 0);
            s = _s, t = _t;
            vector<pair<int, cap_t>> s_addv, t_addv;
            for(edge_t &e : edge)
            {
                if(e.cap > 0 and e.cost <  0)
                {
                    f += e.cap;
                    s_addv.emplace_back(e.to, e.cap);
                    t_addv.emplace_back(e.from, e.cap);
                    corr += e.cost * e.cap;
                    edge[e.rev].cap += e.cap;
                    e.cap = 0;
                }
            }
            for(auto &p : s_addv) add_edge(s, p.first, p.second, 0);
            for(auto &p : t_addv) add_edge(p.first, t, p.second, 0);
            neg_edge_exist = false;
        }
        return Primal_Dual_exe(*this).min_cost_flow(s, t, f) + corr;
    } 
};


// template <class cost_t = int_fast64_t, class cap_t = int_fast64_t>
// struct Flow {
//     struct edge { int to; cost_t cost; cap_t cap; edge *rev; };
//     size_t V,E;
//     bool neg_edge_exist;
//     vector<vector<edge>> adj;

//     Flow(size_t _V) : V(_V),E(),neg_edge_exist() {
//         adj.resize(V * 2);
//         if(V <= 3e3) for(size_t v = 0; v != V * 2; ++v) adj[v].reserve(V * 2);
//     }

//     void add_edge(int from, int to, cost_t cost, cap_t cap) {
//         adj[from].emplace_back((edge){ to, cost, cap, nullptr });
//         adj[to].emplace_back((edge){ from, -cost, 0, nullptr });
//         adj[from].back().rev = &(adj[to].back());
//         adj[to].back().rev = &(adj[from].back());
//         ++E; if(cost < 0) neg_edge_exist = true;
//     }

//     vector<cost_t> Dijkstra(int s) {
//         vector<cost_t> dist(V,inf<cost_t>);
//         priority_queue<pair<cost_t,int>,vector<pair<cost_t,int>>,greater<pair<cost_t,int>>> que;
//         que.emplace(dist[s] = 0, s);
//         while(!que.empty()) {
//             auto p = que.top(); que.pop();
//             int v = p.second;
//             if(dist[v] < p.first) continue;
//             for(edge &e : adj[v]) {
//                 if(e.cap > 0 && dist[v] + e.cost < dist[e.to]) que.emplace(dist[e.to] = dist[v] + e.cost, e.to);
//             } 
//         }
//         return dist;
//     }

//     struct Fold_Fulkerson_exe {
//         Flow &F;
//         vector<bool> used;

//         Fold_Fulkerson_exe(Flow &_F) : F(_F) {
//             used.resize(F.V);
//         }

//         cap_t dfs(int v, int t, cap_t f) {
//             if(v == t) return f;
//             used[v] = true;
//             for(edge &e : F.adj[v]) {
//                 if(!used[e.to] && e.cap > 0) {
//                     cap_t d = dfs(e.to,t,min(f,e.cap));
//                     if(d > 0) {
//                         e.cap -= d;
//                         e.rev->cap += d;
//                         return d;
//                     }
//                 }
//             }
//             return 0;
//         }

//         cap_t max_flow(int s, int t) {
//             cap_t flow = 0,f;
//             while(true) {
//                 fill(begin(used),end(used),false);
//                 if((f = dfs(s,t,numeric_limits<cap_t>::max())) > 0) flow += f;
//                 else break;
//             }
//             return flow;
//         }
//     };

//     cap_t Fold_Fulkerson(int s, int t) { return Fold_Fulkerson_exe(*this).max_flow(s,t); }
    
//     struct Dinic_exe {
//         Flow &F;
//         vector<int> level,itr;

//         Dinic_exe(Flow &_F) : F(_F) {
//             level.resize(F.V), itr.resize(F.V);
//         }

//         void bfs(int s) {
//             fill(begin(level),end(level),-1);
//             queue<int> que;
//             level[s] = 0;
//             que.emplace(s);
//             while(!que.empty()) {
//                 int v = que.front(); que.pop();
//                 for(edge &e : F.adj[v]) {
//                     if(e.cap > 0 && level[e.to] < 0) {
//                         level[e.to] = level[v] + 1;
//                         que.emplace(e.to);
//                     }
//                 } 
//             }
//         }

//         cap_t dfs(int v, int t, cap_t f) {
//             if(v == t) return f;
//             for(int &i = itr[v]; i != F.adj[v].size(); ++i) {
//                 edge &e = F.adj[v][i];
//                 if(e.cap > 0 && level[v] < level[e.to]) {
//                     cap_t d = dfs(e.to, t, min(f,e.cap));
//                     if(d > 0) {
//                         e.cap -= d;
//                         e.rev->cap += d;
//                         return d;
//                     }
//                 }
//             }
//             return 0;
//         }

//         cap_t max_flow(int s, int t) {
//             cap_t flow = 0,f;
//             while(true) {
//                 bfs(s);
//                 if(level[t] < 0) return flow;
//                 fill(begin(itr),end(itr),0);
//                 while((f = dfs(s,t,numeric_limits<cap_t>())) > 0) flow += f;
//             }
//         }
//     };

//     cap_t Dinic(int s, int t) { return Dinic_exe(*this).max_flow(s,t); }

//     struct Primal_Dual_exe {
//         Flow &F;
//         vector<cost_t> dist,h;
//         vector<int> prev_v;
//         vector<edge*> prev_e;

//         Primal_Dual_exe(Flow &_F) : F(_F) {
//             dist.resize(F.V), h.resize(F.V), prev_v.resize(F.V), prev_e.resize(F.V);
//         }

//         bool Dijkstra(int s, int t) {
//             priority_queue<pair<cost_t,int>,vector<pair<cost_t,int>>,greater<pair<cost_t,int>>> que;
//             fill(begin(dist),end(dist),inf<cost_t>);
//             que.emplace(dist[s] = 0, s);
//             while(!que.empty()) {
//                 cost_t cs; int v;
//                 tie(cs,v) = que.top();
//                 que.pop();
//                 if(cs > dist[v]) continue;
//                 for(edge &e : F.adj[v]) {
//                     if(e.cap > 0 && dist[v] + h[v] + e.cost < dist[e.to] + h[e.to]) {
//                         que.emplace(dist[e.to] = dist[v] + h[v] - h[e.to] + e.cost, e.to);
//                         prev_v[e.to] = v;
//                         prev_e[e.to] = &e;
//                     }
//                 }
//             } 
//             if(dist[t] >= inf<cost_t>) return false;
//             for(int v = 0; v < F.V; ++v) h[v] += dist[v];
//             return true;
//         }

//         cost_t min_cost_flow(int s, int t, cap_t f) {
//             cost_t res = 0;
//             fill(begin(h),end(h),0);
//             while(f > 0) {
//                 if(!Dijkstra(s,t)) return inf<cost_t>;
//                 cap_t d = f;
//                 for(int v = t; v != s; v = prev_v[v]) d = min(d, prev_e[v]->cap);
//                 f -= d;
//                 res += d * h[t];
//                 for(int v = t; v != s; v = prev_v[v]) {
//                     prev_e[v]->cap -= d;
//                     prev_e[v]->rev->cap += d;
//                 }
//             }
//             return res;
//         }
//     };

//     cost_t Primal_Dual(int s, int t, cap_t f) {
//         cost_t corr = 0;
//         if(neg_edge_exist) {
//             neg_edge_exist = false;
//             int _s = V++;
//             int _t = V++;
//             add_edge(_s,s,0,f);
//             add_edge(t,_t,0,f);
//             s = _s, t = _t;
//             for(int v = 0; v < V; ++v) {
//                 for(edge &e : adj[v]) {
//                     if(e.cost < 0) {
//                         f += e.cap;
//                         add_edge(s,e.to,0,e.cap);
//                         add_edge(v,t,0,e.cap);
//                         corr += e.cap * e.cost;
//                         e.rev->cap += e.cap;
//                         e.cap = 0;
//                     }
//                 }
//             }
//         }
//         return Primal_Dual_exe(*this).min_cost_flow(s,t,f) + corr;
//     } 
// };



signed main() {}