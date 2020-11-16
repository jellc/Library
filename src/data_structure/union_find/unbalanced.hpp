#pragma once
#include "basic.hpp"
struct union_find_unbalanced : union_find
{
    using union_find::union_find;
    
    bool unite(size_t x, size_t y) override
    {
        assert(x < size() && y < size());
        x = find(x), y = find(y);
        if(x == y) return false;
        link[x] += link[y];
        link[y] = x;
        return true;
    }
}; // class union_find_unbalanced
