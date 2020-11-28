---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"variant/flow/Dinic.hpp\"\n#include <cassert>\n#include <vector>\n\
    // compute the maximum flow.\ntemplate <class cap_t = int>\nstruct Dinic\n{\n\
    \    struct edge_t\n    {\n        size_t src, dst;\n        cap_t cap; size_t\
    \ rev;\n        edge_t(size_t src, size_t dst, cap_t cap, size_t rev) : src(src),\
    \ dst(dst), cap(cap), rev(rev) {}\n    };\n\n    using adj_type = std::vector<edge_t>;\n\
    \n    Dinic(size_t n = 0) : adjs(n), level(n), itr(n) {}\n\n    size_t size()\
    \ const { return adjs.size(); }\n\n    adj_type &operator[](size_t node) { assert(node\
    \ < size()); return adjs[node]; }\n    const adj_type &operator[](size_t node)\
    \ const { assert(node < size()); return adjs[node]; }\n\n    void add_edge(size_t\
    \ src, size_t dst, cap_t cap)\n    {\n        assert(src < size()); assert(dst\
    \ < size());\n        if(!(cap > 0) || src == dst) return;\n        adjs[src].emplace_back(src,\
    \ dst, cap, adjs[dst].size());\n        adjs[dst].emplace_back(dst, src, 0, adjs[src].size()\
    \ - 1);\n    }\n\n    void add_undirected_edge(size_t src, size_t dst, cap_t cap)\n\
    \    {\n        assert(src < size()); assert(dst < size());\n        if(!(cap\
    \ > 0) || src == dst) return;\n        adjs[src].emplace_back(src, dst, cap, adjs[dst].size());\n\
    \        adjs[dst].emplace_back(dst, src, cap, adjs[src].size() - 1);\n    }\n\
    \n    cap_t max_flow(size_t src, size_t dst)\n    {\n        assert(src < size());\
    \ assert(dst < size());\n        cap_t flow(0), bound(0);\n        for(const edge_t\
    \ &e : adjs[src]) bound += e.cap;\n        for(std::vector<size_t> que(size());\
    \ ; std::fill(itr.begin(), itr.end(), 0))\n        {\n            std::fill(level.begin(),\
    \ level.end(), level_infty);\n            level[que.front() = src] = 0;\n    \
    \        for(auto ql{que.begin()}, qr{std::next(ql)}; level[dst] == level_infty\
    \ && ql != qr; ++ql)\n            {\n                for(const edge_t &e : adjs[*ql])\n\
    \                    if(e.cap > 0 && level[e.dst] == level_infty)\n          \
    \              level[*qr++ = e.dst] = level[*ql] + 1;\n            }\n       \
    \     if(level[dst] == level_infty) break;\n            flow += dfs(src, dst,\
    \ bound);\n        }\n        return flow;\n    }\n\nprotected:\n    std::vector<adj_type>\
    \ adjs;\n    std::vector<size_t> level, itr;\n    constexpr static size_t level_infty\
    \ = -1;\n\n    cap_t dfs(const size_t &src, const size_t &dst, cap_t bound)\n\
    \    {\n        if(src == dst || bound == 0) return bound;\n        cap_t flow(0);\n\
    \        for(size_t &i{itr[dst]}; i != adjs[dst].size(); ++i)\n        {\n   \
    \         auto &e = adjs[dst][i], &re = adjs[e.dst][e.rev];\n            if(re.cap\
    \ > 0 && level[e.dst] < level[dst])\n            {\n                if(cap_t achv\
    \ = dfs(src, e.dst, std::min(bound, re.cap)); achv > 0)\n                {\n \
    \                   e.cap += achv, re.cap -= achv;\n                    flow +=\
    \ achv, bound -= achv;\n                    if(bound == 0) break;\n          \
    \      }\n            }\n        }\n        return flow;\n    }\n}; // struct\
    \ Dinic\n"
  code: "#include <cassert>\n#include <vector>\n// compute the maximum flow.\ntemplate\
    \ <class cap_t = int>\nstruct Dinic\n{\n    struct edge_t\n    {\n        size_t\
    \ src, dst;\n        cap_t cap; size_t rev;\n        edge_t(size_t src, size_t\
    \ dst, cap_t cap, size_t rev) : src(src), dst(dst), cap(cap), rev(rev) {}\n  \
    \  };\n\n    using adj_type = std::vector<edge_t>;\n\n    Dinic(size_t n = 0)\
    \ : adjs(n), level(n), itr(n) {}\n\n    size_t size() const { return adjs.size();\
    \ }\n\n    adj_type &operator[](size_t node) { assert(node < size()); return adjs[node];\
    \ }\n    const adj_type &operator[](size_t node) const { assert(node < size());\
    \ return adjs[node]; }\n\n    void add_edge(size_t src, size_t dst, cap_t cap)\n\
    \    {\n        assert(src < size()); assert(dst < size());\n        if(!(cap\
    \ > 0) || src == dst) return;\n        adjs[src].emplace_back(src, dst, cap, adjs[dst].size());\n\
    \        adjs[dst].emplace_back(dst, src, 0, adjs[src].size() - 1);\n    }\n\n\
    \    void add_undirected_edge(size_t src, size_t dst, cap_t cap)\n    {\n    \
    \    assert(src < size()); assert(dst < size());\n        if(!(cap > 0) || src\
    \ == dst) return;\n        adjs[src].emplace_back(src, dst, cap, adjs[dst].size());\n\
    \        adjs[dst].emplace_back(dst, src, cap, adjs[src].size() - 1);\n    }\n\
    \n    cap_t max_flow(size_t src, size_t dst)\n    {\n        assert(src < size());\
    \ assert(dst < size());\n        cap_t flow(0), bound(0);\n        for(const edge_t\
    \ &e : adjs[src]) bound += e.cap;\n        for(std::vector<size_t> que(size());\
    \ ; std::fill(itr.begin(), itr.end(), 0))\n        {\n            std::fill(level.begin(),\
    \ level.end(), level_infty);\n            level[que.front() = src] = 0;\n    \
    \        for(auto ql{que.begin()}, qr{std::next(ql)}; level[dst] == level_infty\
    \ && ql != qr; ++ql)\n            {\n                for(const edge_t &e : adjs[*ql])\n\
    \                    if(e.cap > 0 && level[e.dst] == level_infty)\n          \
    \              level[*qr++ = e.dst] = level[*ql] + 1;\n            }\n       \
    \     if(level[dst] == level_infty) break;\n            flow += dfs(src, dst,\
    \ bound);\n        }\n        return flow;\n    }\n\nprotected:\n    std::vector<adj_type>\
    \ adjs;\n    std::vector<size_t> level, itr;\n    constexpr static size_t level_infty\
    \ = -1;\n\n    cap_t dfs(const size_t &src, const size_t &dst, cap_t bound)\n\
    \    {\n        if(src == dst || bound == 0) return bound;\n        cap_t flow(0);\n\
    \        for(size_t &i{itr[dst]}; i != adjs[dst].size(); ++i)\n        {\n   \
    \         auto &e = adjs[dst][i], &re = adjs[e.dst][e.rev];\n            if(re.cap\
    \ > 0 && level[e.dst] < level[dst])\n            {\n                if(cap_t achv\
    \ = dfs(src, e.dst, std::min(bound, re.cap)); achv > 0)\n                {\n \
    \                   e.cap += achv, re.cap -= achv;\n                    flow +=\
    \ achv, bound -= achv;\n                    if(bound == 0) break;\n          \
    \      }\n            }\n        }\n        return flow;\n    }\n}; // struct\
    \ Dinic\n"
  dependsOn: []
  isVerificationFile: false
  path: variant/flow/Dinic.hpp
  requiredBy: []
  timestamp: '2020-11-28 14:35:40+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: variant/flow/Dinic.hpp
layout: document
redirect_from:
- /library/variant/flow/Dinic.hpp
- /library/variant/flow/Dinic.hpp.html
title: variant/flow/Dinic.hpp
---
