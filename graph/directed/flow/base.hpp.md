---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/directed/flow/Dinic.hpp
    title: graph/directed/flow/Dinic.hpp
  - icon: ':heavy_check_mark:'
    path: graph/directed/flow/min_cost_flow.hpp
    title: graph/directed/flow/min_cost_flow.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/aors_score.test.cpp
    title: test/aizu-online-judge/aors_score.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/assignment.test.cpp
    title: test/library-checker/assignment.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/bipartitematching.test.cpp
    title: test/library-checker/bipartitematching.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"graph/directed/flow/base.hpp\"\n#include <cassert>\n#include\
    \ <vector>\n// the base class of flow algorithms.\ntemplate <class cap_t, class\
    \ cost_t> struct flow_base {\n  struct edge_t {\n    size_t src, dst;\n    cap_t\
    \ cap;\n    cost_t cost;\n    edge_t *rev;\n    edge_t() = default;\n    edge_t(size_t\
    \ src, size_t dst, const cap_t &cap, edge_t *rev)\n        : src(src), dst(dst),\
    \ cap(cap), rev(rev) {}\n    edge_t(size_t src, size_t dst, const cap_t &cap,\
    \ const cost_t &cost,\n           edge_t *rev)\n        : src(src), dst(dst),\
    \ cap(cap), cost(cost), rev(rev) {}\n    const cap_t &flow(const cap_t &f = 0)\
    \ { return cap -= f, rev->cap += f; }\n    bool avbl() const { return static_cast<cap_t>(0)\
    \ < cap; }\n  };  // class edge_t\n\n  class adj_type {\n    edge_t *fst, *lst,\
    \ *clst;\n\n   public:\n    template <class... Args> edge_t *emplace(Args &&...\
    \ args) {\n      if (lst == clst) {\n        size_t len(clst - fst);\n       \
    \ edge_t *nfst = lst = new edge_t[len << 1];\n        for (edge_t *p{fst}; p !=\
    \ clst; ++p, ++lst)\n          p->rev->rev = lst, *lst = *p;\n        delete[]\
    \ fst;\n        fst = nfst;\n        clst = lst + len;\n      }\n      *lst =\
    \ edge_t(args...);\n      return lst++;\n    }\n    adj_type() : fst(new edge_t[1]),\
    \ lst(fst), clst(fst + 1) {}\n    ~adj_type() { delete[] fst; }\n    edge_t &operator[](size_t\
    \ i) {\n      assert(i < size());\n      return *(fst + i);\n    }\n    size_t\
    \ size() const { return lst - fst; }\n    edge_t *begin() const { return fst;\
    \ }\n    edge_t *end() const { return lst; }\n  };  // class adj_type\n\n  flow_base(size_t\
    \ n = 0) : adjs(n) {}\n\n  flow_base(const flow_base &other) : adjs(other.size())\
    \ {\n    for (size_t node{}; node != size(); ++node)\n      for (const auto &[src,\
    \ dst, cap, cost, rev] : other[node])\n        if (src == node) {\n          edge_t\
    \ *ptr = adjs[src].emplace(src, dst, cap, cost, nullptr);\n          ptr->rev\
    \ = adjs[dst].emplace(dst, src, rev->cap, -cost, ptr);\n          rev->src = nil;\n\
    \        } else {\n          rev->rev->src = node;\n        }\n  }\n\n  flow_base\
    \ &operator=(const flow_base &rhs) {\n    if (this != &rhs) adjs.swap(flow_base(rhs).adjs);\n\
    \    return *this;\n  }\n\n  size_t size() const { return adjs.size(); }\n\n \
    \ adj_type &operator[](size_t node) {\n    assert(node < size());\n    return\
    \ adjs[node];\n  }\n  const adj_type &operator[](size_t node) const {\n    assert(node\
    \ < size());\n    return adjs[node];\n  }\n\n  virtual edge_t *add_edge(size_t\
    \ src, size_t dst, const cap_t &cap,\n                           const cost_t\
    \ &cost) {\n    assert(src < size());\n    assert(dst < size());\n    assert(!(cap\
    \ < static_cast<cap_t>(0)));\n    if (!(static_cast<cap_t>(0) < cap) || src ==\
    \ dst) return nullptr;\n    edge_t *ptr = adjs[src].emplace(src, dst, cap, cost,\
    \ nullptr);\n    ptr->rev = adjs[dst].emplace(dst, src, 0, -cost, ptr);\n    return\
    \ ptr;\n  }\n\n protected:\n  constexpr static size_t nil = -1;\n  std::vector<adj_type>\
    \ adjs;\n};  // class flow_base\n"
  code: "#pragma once\n#include <cassert>\n#include <vector>\n// the base class of\
    \ flow algorithms.\ntemplate <class cap_t, class cost_t> struct flow_base {\n\
    \  struct edge_t {\n    size_t src, dst;\n    cap_t cap;\n    cost_t cost;\n \
    \   edge_t *rev;\n    edge_t() = default;\n    edge_t(size_t src, size_t dst,\
    \ const cap_t &cap, edge_t *rev)\n        : src(src), dst(dst), cap(cap), rev(rev)\
    \ {}\n    edge_t(size_t src, size_t dst, const cap_t &cap, const cost_t &cost,\n\
    \           edge_t *rev)\n        : src(src), dst(dst), cap(cap), cost(cost),\
    \ rev(rev) {}\n    const cap_t &flow(const cap_t &f = 0) { return cap -= f, rev->cap\
    \ += f; }\n    bool avbl() const { return static_cast<cap_t>(0) < cap; }\n  };\
    \  // class edge_t\n\n  class adj_type {\n    edge_t *fst, *lst, *clst;\n\n  \
    \ public:\n    template <class... Args> edge_t *emplace(Args &&... args) {\n \
    \     if (lst == clst) {\n        size_t len(clst - fst);\n        edge_t *nfst\
    \ = lst = new edge_t[len << 1];\n        for (edge_t *p{fst}; p != clst; ++p,\
    \ ++lst)\n          p->rev->rev = lst, *lst = *p;\n        delete[] fst;\n   \
    \     fst = nfst;\n        clst = lst + len;\n      }\n      *lst = edge_t(args...);\n\
    \      return lst++;\n    }\n    adj_type() : fst(new edge_t[1]), lst(fst), clst(fst\
    \ + 1) {}\n    ~adj_type() { delete[] fst; }\n    edge_t &operator[](size_t i)\
    \ {\n      assert(i < size());\n      return *(fst + i);\n    }\n    size_t size()\
    \ const { return lst - fst; }\n    edge_t *begin() const { return fst; }\n   \
    \ edge_t *end() const { return lst; }\n  };  // class adj_type\n\n  flow_base(size_t\
    \ n = 0) : adjs(n) {}\n\n  flow_base(const flow_base &other) : adjs(other.size())\
    \ {\n    for (size_t node{}; node != size(); ++node)\n      for (const auto &[src,\
    \ dst, cap, cost, rev] : other[node])\n        if (src == node) {\n          edge_t\
    \ *ptr = adjs[src].emplace(src, dst, cap, cost, nullptr);\n          ptr->rev\
    \ = adjs[dst].emplace(dst, src, rev->cap, -cost, ptr);\n          rev->src = nil;\n\
    \        } else {\n          rev->rev->src = node;\n        }\n  }\n\n  flow_base\
    \ &operator=(const flow_base &rhs) {\n    if (this != &rhs) adjs.swap(flow_base(rhs).adjs);\n\
    \    return *this;\n  }\n\n  size_t size() const { return adjs.size(); }\n\n \
    \ adj_type &operator[](size_t node) {\n    assert(node < size());\n    return\
    \ adjs[node];\n  }\n  const adj_type &operator[](size_t node) const {\n    assert(node\
    \ < size());\n    return adjs[node];\n  }\n\n  virtual edge_t *add_edge(size_t\
    \ src, size_t dst, const cap_t &cap,\n                           const cost_t\
    \ &cost) {\n    assert(src < size());\n    assert(dst < size());\n    assert(!(cap\
    \ < static_cast<cap_t>(0)));\n    if (!(static_cast<cap_t>(0) < cap) || src ==\
    \ dst) return nullptr;\n    edge_t *ptr = adjs[src].emplace(src, dst, cap, cost,\
    \ nullptr);\n    ptr->rev = adjs[dst].emplace(dst, src, 0, -cost, ptr);\n    return\
    \ ptr;\n  }\n\n protected:\n  constexpr static size_t nil = -1;\n  std::vector<adj_type>\
    \ adjs;\n};  // class flow_base\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/directed/flow/base.hpp
  requiredBy:
  - graph/directed/flow/min_cost_flow.hpp
  - graph/directed/flow/Dinic.hpp
  timestamp: '2020-09-19 20:49:19+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/bipartitematching.test.cpp
  - test/library-checker/assignment.test.cpp
  - test/aizu-online-judge/aors_score.test.cpp
documentation_of: graph/directed/flow/base.hpp
layout: document
redirect_from:
- /library/graph/directed/flow/base.hpp
- /library/graph/directed/flow/base.hpp.html
title: graph/directed/flow/base.hpp
---
