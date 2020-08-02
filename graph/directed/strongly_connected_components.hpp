#ifndef strongly_connected_components_hpp
#define strongly_connected_components_hpp

#include <cassert>
#include <vector>

class strongly_connected_components
{
    std::vector<std::vector<size_t>> graph, memb;
    std::vector<size_t> comp, low;
    size_t cnt;
    bool made;

public:
    strongly_connected_components(size_t n) : graph(n), comp(n), low(n), made() {}

    // add an edge from the vertex s to the vertex t.
    void add_edge(size_t src, size_t dst)
    {
        assert(src < size()); assert(dst < size());
        graph[src].emplace_back(dst);
        made = false;
    }

    // the number of the components.
    size_t count() { make(); return cnt; }

    size_t size() const { return graph.size(); }

    // the number of vertices in the i-th component.
    size_t size(size_t i) { make(); return memb[i].size(); }

    // vertices in the i-th component.
    const std::vector<size_t> &component(size_t i) { make(); return memb[i]; }

    // the component which the vertex v belongs to.
    size_t operator[](size_t v) { make(); return comp[v]; }

    // the directed acyclic graph consisting of the components.
    std::vector<std::vector<size_t>> make_dag()
    {
        make();
        std::vector<std::vector<size_t>> res(cnt);
        bool *apr = new bool[size()]{};
        size_t *stack_ptr = new size_t[size()];
        for(size_t i = 0; i != cnt; ++i)
        {
            size_t *itr = stack_ptr;
            for(size_t s : memb[i]) for(size_t t : graph[s]) if(!apr[comp[t]]) apr[comp[t]] = true, *itr++ = comp[t];
            res[i].resize(itr - stack_ptr);
            while(itr != stack_ptr) apr[res[i][--itr - stack_ptr] = *itr] = false;
        }
        delete[] apr; delete[] stack_ptr;
        return res;
    }

protected:
    void make()
    {
        if(made) return;
        made = true, cnt = 0;
        fill(low.begin(), low.end(), -1);
        fill(comp.begin(), comp.end(), -1);
        size_t *itr = new size_t[size()];
        for(size_t v = 0, c = 0; v != size(); ++v) affix(v, c, itr);
        delete[] itr; memb.resize(cnt);
        for(size_t v = 0; v != size(); ++v) memb[comp[v] = cnt - 1 - comp[v]].emplace_back(v);
    }

    size_t affix(size_t v, size_t &c, size_t* &itr)
    {
        if(~low[v]) return ~comp[v] ? -1 : low[v];
        size_t idx = c++; low[v] = idx; *itr++ = v;
        for(int u : graph[v]) low[v] = std::min(low[v], affix(u, c, itr));
        if(low[v] == idx) { do { comp[*--itr] = cnt; } while(*itr != v); ++cnt; }
        return low[v];
    }
}; // class strongly_connected_components

#endif // strongly_connected_components_hpp
