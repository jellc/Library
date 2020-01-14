// #line 2 "Additional_union_find.hpp"
#ifndef Additional_union_find_hpp
#define Additional_union_find_hpp
#include <cassert>
#include <functional>
#include <vector>

template <class T>
class additional_union_find
{
    size_t n;
    std::vector<int> link;
    T *const dat;
    const std::function<void(T&, T&)> merge;

public:
    additional_union_find(const size_t _n, const std::function<void(T&, T&)> &f) : n(_n), link(n, -1), dat(new T[n]()), merge(f) {}
    additional_union_find(const size_t _n, const T &x, const std::function<void(T&, T&)> &f) : n(_n), link(n, -1), dat(new T[n](x)), merge(f) {}
    ~additional_union_find() { delete[] dat; }

    size_t find(const size_t x) { assert(x < n); return link[x] < 0 ? x : (link[x] = find(link[x])); }

    size_t size() const { return n; }
    size_t size(const size_t x) { return -link[find(x)]; }

    bool same(const size_t x, const size_t y) { return find(x) == find(y); }

    bool unite(size_t x, size_t y)
    {
        if((x = find(x)) == (y = find(y))) return false;
        if(link[x] > link[y]) std::swap(x, y);
        link[x] += link[y], link[y] = x;
        merge(dat[x], dat[y]);
        return true;
    }

    T &operator[](const size_t x) { return dat[find(x)]; }
}; // class additional_union_find

#endif