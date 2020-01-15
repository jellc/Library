// #line 2 "potentialized_union_find.hpp"
// verified at https://atcoder.jp/contests/abc087/submissions/9511701
#ifndef Potentialized_union_find_hpp
#define Potentialized_union_find_hpp
#include <cassert>
#include <cstddef>
#include <vector>

template <class Abelian>
class potentialized_union_find
{
    size_t n;
    std::vector<int> link;
    std::vector<Abelian> diff_weight;

public:
    explicit potentialized_union_find(size_t _n) : n(_n), link(n, -1), diff_weight(n) {}

    size_t find(const size_t x)
    {
        assert(x < n);
        if(link[x] < 0) return x;
        const size_t root = find(link[x]);
        diff_weight[x] += diff_weight[link[x]];
        return link[x] = root;
    }

    size_t size() const { return n; }
    size_t size(const size_t x) { return -link[find(x)]; }

    Abelian weight(size_t x) { return find(x), diff_weight[x]; }

    Abelian diff(size_t x, size_t y) { return weight(y) - weight(x); }

    bool same(const size_t x, const size_t y) { return find(x) == find(y); }

    bool unite(size_t x, size_t y, Abelian w)
    {
        w += weight(x) - weight(y);
        x = find(x), y = find(y);
        if(x == y) return false;
        if(link[x] > link[y]) std::swap(x, y), w = -w;
        link[x] += link[y], link[y] = x;
        diff_weight[y] = w;
        return true;
    }
}; // class potentialized_union_find

#endif