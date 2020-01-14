// #line 2 "Union_find.hpp"
#ifndef Union_find_hpp
#define Union_find_hpp
#include <cassert>
#include <cstdint>
#include <numeric>
#include <vector>

class union_find
{
    const size_t n;
    std::vector<int> link;
    bool *const cyc, *const clr, *const flip;
    size_t comp, isol;
    bool bipart;

  public:
    explicit union_find(const size_t _n) : n(_n), link(n, -1), cyc(new bool[n]{}), clr(new bool[n]{}), flip(new bool[n]{}), comp(n), isol(n), bipart(true) {}
    ~union_find() { delete[] cyc; delete[] clr; delete[] flip; }

    size_t find(const size_t x)
    {
        assert(x < n);
        if(link[x] < 0) return x;
        const size_t r = find(link[x]);
        if(flip[link[x]]) clr[x] = !clr[x], flip[x] = !flip[x];
        return link[x] = r;
    }

    size_t size() const { return n; }
    size_t size(const size_t x) { return -link[find(x)]; }

    size_t count() const { return comp; }

    size_t isolated() const { return isol; }

    bool color(const size_t x) { return find(x), clr[x]; }

    bool cyclic(const size_t x) { return cyc[find(x)]; }

    bool same(const size_t x, const size_t y) { return find(x) == find(y); }

    bool bipartite() const { return bipart; }

    bool unite(size_t x, size_t y)
    {
        const size_t _x = find(x), _y = find(y);
        const bool f = clr[x] == clr[y];
        x = _x, y = _y;
        if(x == y)
        {
            bipart &= !f;
            cyc[x] = true;
            return false;
        }
        if(link[x] > link[y]) std::swap(x, y);
        if(link[x] == -1) --isol;
        if(link[y] == -1) --isol;
        link[x] += link[y], link[y] = x;
        cyc[x] = cyc[x] || cyc[y];
        if(f) clr[y] = !clr[y], flip[y] = !flip[y];
        --comp;
        return true;
    }
}; // class union_find

#endif