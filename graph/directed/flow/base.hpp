#include <vector>

// Base class of flow algorithms
template <class cap_t, class cost_t>
struct flow_base
{
    struct edge_t
    {
        size_t src, dst;
        cap_t cap; cost_t cost;
        size_t rev;
        edge_t(size_t _src, size_t _dst, cap_t _cap, cost_t _cost, size_t _rev)
            : src(_src), dst(_dst), cap(_cap), cost(_cost), rev(_rev) {}
    }; // struct edge_t

protected:
    using adj_type = std::vector<std::vector<edge_t>>;
    adj_type adj;

public:
    flow_base(size_t _n = 0) : adj(_n) {}

    size_t size() const { return adj.size(); }
    typename decltype(adj)::reference operator[](size_t node) { assert(node < size()); return adj[node]; }
    typename decltype(adj)::const_reference operator[](size_t node) const { assert(node < size()); return adj[node]; }

    void add_edge(size_t src, size_t dst, cap_t cap, cost_t cost)
    {
        assert(src < size()); assert(dst < size());
        if(cap <= 0) return;
        adj[src].emplace_back(src, dst, cap, cost, adj[dst].size());
        adj[dst].emplace_back(dst, src, 0, -cost, adj[src].size() - 1);
    }
}; // struct flow_base
