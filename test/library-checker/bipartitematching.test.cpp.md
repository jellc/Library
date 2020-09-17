---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/directed/flow/Dinic.hpp
    title: graph/directed/flow/Dinic.hpp
  - icon: ':heavy_check_mark:'
    path: graph/directed/flow/base.hpp
    title: graph/directed/flow/base.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/bipartitematching
    links:
    - https://judge.yosupo.jp/problem/bipartitematching
  bundledCode: "#line 1 \"test/library-checker/bipartitematching.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/bipartitematching\"\n#line 2 \"graph/directed/flow/base.hpp\"\
    \n#include <cassert>\n#include <vector>\n// the base class of flow algorithms.\n\
    template <class cap_t, class cost_t> struct flow_base {\n  struct edge_t {\n \
    \   size_t src, dst;\n    cap_t cap;\n    cost_t cost;\n    edge_t *rev;\n   \
    \ edge_t() = default;\n    edge_t(size_t src, size_t dst, cap_t cap, edge_t *rev)\n\
    \        : src(src), dst(dst), cap(cap), rev(rev) {}\n    edge_t(size_t src, size_t\
    \ dst, cap_t cap, cost_t cost, edge_t *rev)\n        : src(src), dst(dst), cap(cap),\
    \ cost(cost), rev(rev) {}\n    void flow(cap_t f) { cap -= f, rev->cap += f; }\n\
    \    bool avbl() const { return cap > 0; }\n  };  // class edge_t\n\n  class adj_type\
    \ {\n    edge_t *fst, *lst, *clst;\n\n   public:\n    template <class... Args>\
    \ edge_t *emplace(Args &&... args) {\n      if (lst == clst) {\n        size_t\
    \ len(clst - fst);\n        edge_t *nfst = lst = new edge_t[len << 1];\n     \
    \   for (edge_t *p{fst}; p != clst; ++p, ++lst)\n          p->rev->rev = lst,\
    \ *lst = *p;\n        delete[] fst;\n        fst = nfst;\n        clst = lst +\
    \ len;\n      }\n      *lst = edge_t(args...);\n      return lst++;\n    }\n \
    \   adj_type() : fst(new edge_t[1]), lst(fst), clst(fst + 1) {}\n    ~adj_type()\
    \ { delete[] fst; }\n    edge_t &operator[](size_t i) {\n      assert(i < size());\n\
    \      return *(fst + i);\n    }\n    size_t size() const { return lst - fst;\
    \ }\n    edge_t *begin() const { return fst; }\n    edge_t *end() const { return\
    \ lst; }\n  };  // class adj_type\n\n  flow_base(size_t n = 0) : adjs(n) {}\n\n\
    \  flow_base(const flow_base &other) : adjs(other.size()) {\n    for (size_t node{};\
    \ node != size(); ++node)\n      for (const auto &[src, dst, cap, cost, rev] :\
    \ other[node])\n        if (src == node) {\n          edge_t *ptr = adjs[src].emplace(src,\
    \ dst, cap, cost, nullptr);\n          ptr->rev = adjs[dst].emplace(dst, src,\
    \ rev->cap, -cost, ptr);\n          rev->src = -1;\n        } else {\n       \
    \   rev->rev->src = node;\n        }\n  }\n\n  flow_base &operator=(const flow_base\
    \ &rhs) {\n    if (this != &rhs) adjs.swap(flow_base(rhs).adjs);\n    return *this;\n\
    \  }\n\n  size_t size() const { return adjs.size(); }\n\n  adj_type &operator[](size_t\
    \ node) {\n    assert(node < size());\n    return adjs[node];\n  }\n  const adj_type\
    \ &operator[](size_t node) const {\n    assert(node < size());\n    return adjs[node];\n\
    \  }\n\n  virtual void add_edge(size_t src, size_t dst, cap_t cap, cost_t cost)\
    \ {\n    assert(src < size());\n    assert(dst < size());\n    if (!(cap > 0)\
    \ || src == dst) return;\n    edge_t *ptr = adjs[src].emplace(src, dst, cap, cost,\
    \ nullptr);\n    ptr->rev = adjs[dst].emplace(dst, src, 0, -cost, ptr);\n  }\n\
    \n protected:\n  std::vector<adj_type> adjs;\n};  // class flow_base\n#line 3\
    \ \"graph/directed/flow/Dinic.hpp\"\n// compute the maximum flow.\ntemplate <class\
    \ cap_t = int>\nclass Dinic : public flow_base<cap_t, bool>\n{\n    using base\
    \ = flow_base<cap_t, bool>;\n    using edge_t = typename base::edge_t;\n    using\
    \ base::adjs;\n\n    std::vector<size_t> level;\n    std::vector<edge_t*> itr;\n\
    \    constexpr static size_t level_infty = -1;\n\n    cap_t dfs(const size_t &src,\
    \ const size_t &dst, cap_t bound)\n    {\n        if(src == dst || bound == 0)\
    \ return bound;\n        cap_t flow(0);\n        for(edge_t* &e{itr[dst]}; e !=\
    \ adjs[dst].end(); ++e)\n            if(e->rev->avbl() && level[e->dst] < level[dst])\n\
    \                if(cap_t achv = dfs(src, e->dst, std::min(bound, e->rev->cap));\
    \ achv > 0)\n                {\n                    e->rev->flow(achv);\n    \
    \                flow += achv, bound -= achv;\n                    if(bound ==\
    \ 0) break;\n                }\n        return flow;\n    }\n\npublic:\n    using\
    \ base::size;\n\n    Dinic(size_t n = 0) : base::flow_base(n), level(n, level_infty),\
    \ itr(n) {}\n\n    Dinic(const Dinic &other) : base::flow_base(other), level(other.level),\
    \ itr(other.itr)  {}\n\n    Dinic &operator=(const Dinic &rhs)\n    {\n      \
    \  if(this != &rhs) base::operator=(rhs), level = rhs.level, itr = rhs.itr;\n\
    \        return *this;\n    }\n\n    void add_edge(size_t src, size_t dst, cap_t\
    \ cap) { base::add_edge(src, dst, cap, false); }\n\n    void add_undirected_edge(size_t\
    \ src, size_t dst, cap_t cap) { base::add_undirected_edge(src, dst, cap, false);\
    \ }\n\n    cap_t max_flow(size_t src, size_t dst)\n    {\n        assert(src <\
    \ size()); assert(dst < size());\n        cap_t flow(0), bound(0);\n        for(const\
    \ edge_t &e : adjs[src]) bound += e.cap;\n        for(std::vector<size_t> que(size());\
    \ ; std::fill(level.begin(), level.end(), level_infty))\n        {\n         \
    \   level[que.front() = src] = 0;\n            for(auto ql{que.begin()}, qr{std::next(ql)};\
    \ level[dst] == level_infty && ql != qr; ++ql)\n                for(const edge_t\
    \ &e : adjs[*ql])\n                    if(e.avbl() && level[e.dst] == level_infty)\n\
    \                        level[*qr++ = e.dst] = level[*ql] + 1;\n            if(level[dst]\
    \ == level_infty) break;\n            for(size_t node{}; node != size(); ++node)\
    \ itr[node] = adjs[node].begin();\n            flow += dfs(src, dst, bound);\n\
    \        }\n        return flow;\n    }\n}; // class Dinic\n#line 3 \"test/library-checker/bipartitematching.test.cpp\"\
    \n#include <cstdio>\n\nint main()\n{\n    int l,r,m; scanf(\"%d%d%d\",&l,&r,&m);\n\
    \    Dinic<int> dinic(l+r+2);\n    const int s=l+r,t=s+1;\n\n    for(int i = 0,a,b;\
    \ i < m; ++i)\n    {\n        scanf(\"%d%d\",&a,&b);\n        dinic.add_edge(a,b+l,1);\n\
    \    }\n    for(int i = 0; i < l; ++i)\n    {\n        dinic.add_edge(s,i,1);\n\
    \    }\n    for(int i = 0; i < r; ++i)\n    {\n        dinic.add_edge(i+l,t,1);\n\
    \    }\n\n    printf(\"%d\\n\",dinic.max_flow(s,t));\n\n    for(int i = 0; i <\
    \ l; ++i)\n    {\n        for(const auto &e: dinic[i])\n        {\n          \
    \  if(!e.cap and e.dst<l+r)\n            {\n                printf(\"%d %d\\n\"\
    , i, e.dst-l);\n            }\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/bipartitematching\"\n#include\
    \ \"graph/directed/flow/Dinic.hpp\"\n#include <cstdio>\n\nint main()\n{\n    int\
    \ l,r,m; scanf(\"%d%d%d\",&l,&r,&m);\n    Dinic<int> dinic(l+r+2);\n    const\
    \ int s=l+r,t=s+1;\n\n    for(int i = 0,a,b; i < m; ++i)\n    {\n        scanf(\"\
    %d%d\",&a,&b);\n        dinic.add_edge(a,b+l,1);\n    }\n    for(int i = 0; i\
    \ < l; ++i)\n    {\n        dinic.add_edge(s,i,1);\n    }\n    for(int i = 0;\
    \ i < r; ++i)\n    {\n        dinic.add_edge(i+l,t,1);\n    }\n\n    printf(\"\
    %d\\n\",dinic.max_flow(s,t));\n\n    for(int i = 0; i < l; ++i)\n    {\n     \
    \   for(const auto &e: dinic[i])\n        {\n            if(!e.cap and e.dst<l+r)\n\
    \            {\n                printf(\"%d %d\\n\", i, e.dst-l);\n          \
    \  }\n        }\n    }\n}\n"
  dependsOn:
  - graph/directed/flow/Dinic.hpp
  - graph/directed/flow/base.hpp
  isVerificationFile: true
  path: test/library-checker/bipartitematching.test.cpp
  requiredBy: []
  timestamp: '2020-09-04 04:48:51+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/library-checker/bipartitematching.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/bipartitematching.test.cpp
- /verify/test/library-checker/bipartitematching.test.cpp.html
title: test/library-checker/bipartitematching.test.cpp
---