#include <bits/stdc++.h>

class Strongly_connected_components
{
    const size_t V;
    std::vector<std::vector<size_t>> adj, mbr;
    std::vector<size_t> comp, low;
    size_t n;
    bool is_built;

  public:
    Strongly_connected_components(size_t _V)
        : V(_V), adj(V), comp(V), low(V), is_built()
    {}

    // add an edge from the vertex s to the vertex t.
    void add_edge(size_t s, size_t t)
    {
        adj[s].emplace_back(t);
        is_built = false;
    }

    // the number of the components.
    size_t count()
    {
        if(not is_built) build();
        return n;
    }

    // the number of vertices in the i-th component.
    size_t size(size_t i)
    {
        if(not is_built) build();
        return mbr[i].size();
    }

    // vertices in the i-th component.
    const std::vector<size_t> &component(size_t i)
    {
        if(not is_built) build();
        return mbr[i];
    }

    // the component which the vertex v belongs to.
    size_t operator[](size_t v)
    {
        if(not is_built) build();
        return comp[v];
    }

    // the directed acyclic graph consisting of the components.
    std::vector<std::vector<size_t>> make_dag()
    {
        if(not is_built) build();
        std::vector<std::vector<size_t>> ret(n);
        for(size_t i = 0; i < n; ++i)
        {
            std::unordered_set<size_t> uni;
            for(size_t s : mbr[i])
            {
                for(size_t t : adj[s])
                {
                    if(comp[t] != i) uni.emplace(comp[t]);
                }
            }
            ret[i] = std::vector<size_t>(uni.begin(), uni.end());
        }
        return ret;
    }

  protected:
    void build()
    {
        is_built = true, n = 0;
        fill(low.begin(), low.end(), -1);
        fill(comp.begin(), comp.end(), -1);
        std::vector<size_t> stack(V);
        auto itr = stack.begin();
        for(size_t v = 0, c = 0; v < V; ++v)
            affix(v, c, itr);
        mbr.resize(n);
        for(size_t v = 0; v < V; ++v)
        {
            comp[v] = n - 1 - comp[v];
            mbr[comp[v]].emplace_back(v);
        }
    }

    size_t affix(size_t v, size_t &c, std::vector<size_t>::iterator &itr)
    {
        if(~low[v]) return ~comp[v] ? -1 : low[v];
        size_t idx = c++;
        low[v] = idx;
        *itr++ = v;
        for(int u : adj[v])
        {
            low[v] = std::min(low[v], affix(u, c, itr));
        }
        if(low[v] == idx)
        {
            do
            {
                comp[*--itr] = n;
            } while(*itr != v);
            ++n;
        }
        return low[v];
    }
};