// verified at https://judge.yosupo.jp/submission/3400
#ifndef union_find_hpp
#define union_find_hpp

#include <cassert>
#include <vector>

class union_find
{
    std::vector<int> link;

public:
    explicit union_find(const unsigned n = 0) : link(n, -1) {}

    unsigned find(unsigned x)
    {
        assert(x < size());
        return link[x] < 0 ? x : (link[x] = find(link[x]));
    }

    unsigned size() const { return link.size(); }

    unsigned size(const unsigned x)
    {
        assert(x < size());
        return -link[find(x)];
    }

    bool same(const unsigned x, const unsigned y)
    {
        assert(x < size() && y < size());
        return find(x) == find(y);
    }

    bool unite(unsigned x, unsigned y)
    {
        assert(x < size() && y < size());
        x = find(x), y = find(y);
        if(x == y) return false;
        if(link[x] > link[y]) std::swap(x, y);
        link[x] += link[y];
        link[y] = x;
        return true;
    }
}; // class union_find

#endif // union_find_hpp