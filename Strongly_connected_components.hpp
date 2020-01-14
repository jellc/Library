// #line 2 "Strongly_connected_components.hpp"
#ifndef Strongly_connected_components_hpp
#define Strongly_connected_components_hpp
#include <vector>

class Strongly_connected_components
{
    const size_t V;
    std::vector<std::vector<size_t>> adj, mem;
    std::vector<size_t> comp, low;
    size_t n;
    bool is_built;

  public:
    Strongly_connected_components(size_t _V) : V(_V), adj(V), comp(V), low(V), is_built() {}

    // add an edge from the vertex s to the vertex t.
    void add_edge(size_t s, size_t t) { adj[s].emplace_back(t); is_built = false; }

    // the number of the components.
    size_t count() { return build(), n; }

    // the number of vertices in the i-th component.
    size_t size(size_t i) { return build(), mem[i].size(); }

    // vertices in the i-th component.
    const std::vector<size_t> &component(size_t i) { return build(), mem[i]; }

    // the component which the vertex v belongs to.
    size_t operator[](size_t v) { return build(), comp[v]; }

    // the directed acyclic graph consisting of the components.
    std::vector<std::vector<size_t>> make_dag()
    {
        build();
        std::vector<std::vector<size_t>> res(n);
        bool *apr = new bool[V]{};
        size_t *stack_ptr = new size_t[V];
        for(size_t i = 0; i != n; ++i)
        {
            size_t *itr = stack_ptr;
            for(size_t s : mem[i]) for(size_t t : adj[s]) if(!apr[comp[t]]) apr[comp[t]] = true, *itr++ = comp[t];
            res[i].resize(itr - stack_ptr);
            while(itr != stack_ptr) apr[res[i][--itr - stack_ptr] = *itr] = false;
        }
        delete[] apr, stack_ptr;
        return res;
    }

  protected:
    void build()
    {
        if(is_built) return;
        is_built = true, n = 0;
        fill(low.begin(), low.end(), -1);
        fill(comp.begin(), comp.end(), -1);
        size_t *itr = new size_t[V];
        for(size_t v = 0, c = 0; v != V; ++v) affix(v, c, itr);
        delete[] itr; mem.resize(n);
        for(size_t v = 0; v != V; ++v) mem[comp[v] = n - 1 - comp[v]].emplace_back(v);
    }

    size_t affix(size_t v, size_t &c, size_t* &itr)
    {
        if(~low[v]) return ~comp[v] ? -1 : low[v];
        size_t idx = c++; low[v] = idx; *itr++ = v;
        for(int u : adj[v]) low[v] = std::min(low[v], affix(u, c, itr));
        if(low[v] == idx) { do { comp[*--itr] = n; } while(*itr != v); ++n; }
        return low[v];
    }
}; // class Strongly_connected_components

#endif