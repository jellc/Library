#pragma once
#include <cassert>
#include <vector>
struct union_find
{
    union_find(const size_t &n = 0) : link(n, -1) {}

    size_t find(const size_t &x)
    {
        assert(x < size());
        return link[x] < 0 ? x : (link[x] = find(link[x]));
    }

    size_t size() const { return link.size(); }

    size_t size(const size_t &x)
    {
        assert(x < size());
        return -link[find(x)];
    }

    bool same(const size_t &x, const size_t &y)
    {
        assert(x < size() && y < size());
        return find(x) == find(y);
    }

    virtual bool unite(size_t x, size_t y)
    {
        assert(x < size() && y < size());
        x = find(x), y = find(y);
        if(x == y) return false;
        if(link[x] > link[y]) std::swap(x, y);
        link[x] += link[y];
        link[y] = x;
        return true;
    }

protected:
    std::vector<int> link;
}; // class union_find
