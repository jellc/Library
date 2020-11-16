#include <cassert>
#include <vector>

class centroid_decomposition
{
    std::vector<std::vector<size_t>> tree, sub;
    std::vector<size_t> siz;
    std::vector<bool> chkd;

    bool dfs(size_t nod, size_t pre, size_t all, size_t rot)
    {
        siz[nod] = 1;
        bool cent = true;
        for(size_t to : tree[nod])
        {
            if(to == pre || chkd[to]) continue;
            if(dfs(to, nod, all, rot)) return true;
            siz[nod] += siz[to];
            if(siz[to] > all / 2) cent = false;
        }
        if(all - siz[nod] > all / 2) cent = false;
        if(!cent) return false;
        chkd[nod] = true;
        if(~rot) sub[rot].emplace_back(nod);
        else root = nod;
        for(size_t to : tree[nod])
        {
            if(chkd[to]) continue;
            if(to == pre) assert(dfs(to, nod, all - siz[nod], nod));
            else assert(dfs(to, nod, siz[to], nod));
        }
        return true;
    }

public:
    size_t root;

    centroid_decomposition(size_t _n = 0) : tree(_n), sub(_n), siz(_n), chkd(_n) {}

    size_t size() const { return tree.size(); }

    void add_edge(size_t u, size_t v)
    {
        assert(u < size()); assert(v < size());
        tree[u].emplace_back(v);
        tree[v].emplace_back(u);
    }

    size_t make() { assert(dfs(0, 0, size(), -1)); return root; }

    decltype(sub)::const_reference operator[](size_t nod) const { return sub[nod]; }
}; // class centroid_decomposition
