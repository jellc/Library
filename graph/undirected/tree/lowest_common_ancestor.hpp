#include <cassert>
#include <vector>

// query: O(1)
// build: O(nlog(n))
class lowest_common_ancestor
{
    std::vector<std::vector<size_t>> tree, tab;
    std::vector<size_t> idx;

    void tour(size_t node, size_t pre)
    {
        idx[node] = tab[0].size();
        tab[0].emplace_back(node);
        for(size_t to : tree[node])
        {
            if(to != pre)
            {
                tour(to, node);
                tab[0].emplace_back(node);
            }
        }
    }

    void make_table()
    {
        const size_t len = tab[0].size();
        for(size_t w = 2; w < len; w <<= 1)
        {
            std::vector<size_t> &crt(tab.back()), nxt(crt);
            for(size_t i = 0, j = w >> 1; j != len; ++i, ++j) if(idx[crt[i]] > idx[crt[j]]) nxt[i] = crt[j];
            tab.emplace_back(nxt);
        }
    }

public:
    lowest_common_ancestor(size_t n) : tree(n), tab(1), idx(n) {}

    size_t size() const { return tree.size(); }

    void add_edge(size_t u, size_t v)
    {
        assert(u < size()); assert(v < size());
        tree[u].emplace_back(v);
        tree[v].emplace_back(u);
    }

    void make(size_t root)
    {
        assert(root < size());
        tour(root, root);
        make_table();
    }

    size_t query(size_t u, size_t v) const
    {
        assert(u < size()); assert(v < size());
        if(u == v) return u;
        if(idx[u] > idx[v]) std::swap(u, v);
        u = idx[u], v = idx[v];
        size_t h = std::__lg(v - u);
        return std::min(tab[h][u], tab[h][v - (1 << h)]);
    }
}; // class lowest_common_ancestor