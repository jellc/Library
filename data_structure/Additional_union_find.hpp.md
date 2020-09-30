---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"data_structure/Additional_union_find.hpp\"\n// #line 2 \"\
    Additional_union_find.hpp\"\n#ifndef Additional_union_find_hpp\n#define Additional_union_find_hpp\n\
    #include <cassert>\n#include <functional>\n#include <vector>\n\ntemplate <class\
    \ T>\nclass additional_union_find\n{\n    size_t n;\n    std::vector<int> link;\n\
    \    T *const dat;\n    const std::function<void(T&, T&)> merge;\n\npublic:\n\
    \    additional_union_find(const size_t _n, const std::function<void(T&, T&)>\
    \ &f) : n(_n), link(n, -1), dat(new T[n]()), merge(f) {}\n    additional_union_find(const\
    \ size_t _n, const T &x, const std::function<void(T&, T&)> &f) : n(_n), link(n,\
    \ -1), dat(new T[n](x)), merge(f) {}\n    ~additional_union_find() { delete[]\
    \ dat; }\n\n    size_t find(const size_t x) { assert(x < n); return link[x] <\
    \ 0 ? x : (link[x] = find(link[x])); }\n\n    size_t size() const { return n;\
    \ }\n    size_t size(const size_t x) { return -link[find(x)]; }\n\n    bool same(const\
    \ size_t x, const size_t y) { return find(x) == find(y); }\n\n    bool unite(size_t\
    \ x, size_t y)\n    {\n        if((x = find(x)) == (y = find(y))) return false;\n\
    \        if(link[x] > link[y]) std::swap(x, y);\n        link[x] += link[y], link[y]\
    \ = x;\n        merge(dat[x], dat[y]);\n        return true;\n    }\n\n    T &operator[](const\
    \ size_t x) { return dat[find(x)]; }\n}; // class additional_union_find\n\n#endif\n"
  code: "// #line 2 \"Additional_union_find.hpp\"\n#ifndef Additional_union_find_hpp\n\
    #define Additional_union_find_hpp\n#include <cassert>\n#include <functional>\n\
    #include <vector>\n\ntemplate <class T>\nclass additional_union_find\n{\n    size_t\
    \ n;\n    std::vector<int> link;\n    T *const dat;\n    const std::function<void(T&,\
    \ T&)> merge;\n\npublic:\n    additional_union_find(const size_t _n, const std::function<void(T&,\
    \ T&)> &f) : n(_n), link(n, -1), dat(new T[n]()), merge(f) {}\n    additional_union_find(const\
    \ size_t _n, const T &x, const std::function<void(T&, T&)> &f) : n(_n), link(n,\
    \ -1), dat(new T[n](x)), merge(f) {}\n    ~additional_union_find() { delete[]\
    \ dat; }\n\n    size_t find(const size_t x) { assert(x < n); return link[x] <\
    \ 0 ? x : (link[x] = find(link[x])); }\n\n    size_t size() const { return n;\
    \ }\n    size_t size(const size_t x) { return -link[find(x)]; }\n\n    bool same(const\
    \ size_t x, const size_t y) { return find(x) == find(y); }\n\n    bool unite(size_t\
    \ x, size_t y)\n    {\n        if((x = find(x)) == (y = find(y))) return false;\n\
    \        if(link[x] > link[y]) std::swap(x, y);\n        link[x] += link[y], link[y]\
    \ = x;\n        merge(dat[x], dat[y]);\n        return true;\n    }\n\n    T &operator[](const\
    \ size_t x) { return dat[find(x)]; }\n}; // class additional_union_find\n\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/Additional_union_find.hpp
  requiredBy: []
  timestamp: '2020-01-15 19:06:22+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: data_structure/Additional_union_find.hpp
layout: document
redirect_from:
- /library/data_structure/Additional_union_find.hpp
- /library/data_structure/Additional_union_find.hpp.html
title: data_structure/Additional_union_find.hpp
---
