---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/directed/flow/base.hpp
    title: graph/directed/flow/base.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/library-checker/assignment.test.cpp
    title: test/library-checker/assignment.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/aors_score.test.cpp
    title: test/aizu-online-judge/aors_score.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 2 \"graph/directed/flow/min_cost_flow.hpp\"\n#include <algorithm>\n\
    #include <queue>\n\n#line 2 \"graph/directed/flow/base.hpp\"\n#include <cassert>\n\
    #include <vector>\n// the base class of flow algorithms.\ntemplate <class cap_t,\
    \ class cost_t> struct flow_base {\n  struct edge_t {\n    size_t src, dst;\n\
    \    cap_t cap;\n    cost_t cost;\n    edge_t *rev;\n    edge_t() = default;\n\
    \    edge_t(size_t src, size_t dst, const cap_t &cap, edge_t *rev)\n        :\
    \ src(src), dst(dst), cap(cap), rev(rev) {}\n    edge_t(size_t src, size_t dst,\
    \ const cap_t &cap, const cost_t &cost,\n           edge_t *rev)\n        : src(src),\
    \ dst(dst), cap(cap), cost(cost), rev(rev) {}\n    void flow(const cap_t &f) {\
    \ cap -= f, rev->cap += f; }\n    bool avbl() const { return static_cast<cap_t>(0)\
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
    \ = adjs[dst].emplace(dst, src, rev->cap, -cost, ptr);\n          rev->src = -1;\n\
    \        } else {\n          rev->rev->src = node;\n        }\n  }\n\n  flow_base\
    \ &operator=(const flow_base &rhs) {\n    if (this != &rhs) adjs.swap(flow_base(rhs).adjs);\n\
    \    return *this;\n  }\n\n  size_t size() const { return adjs.size(); }\n\n \
    \ adj_type &operator[](size_t node) {\n    assert(node < size());\n    return\
    \ adjs[node];\n  }\n  const adj_type &operator[](size_t node) const {\n    assert(node\
    \ < size());\n    return adjs[node];\n  }\n\n  virtual void add_edge(size_t src,\
    \ size_t dst, const cap_t &cap,\n                        const cost_t &cost) {\n\
    \    assert(src < size());\n    assert(dst < size());\n    assert(!(cap < static_cast<cap_t>(0)));\n\
    \    if (!(static_cast<cap_t>(0) < cap) || src == dst) return;\n    edge_t *ptr\
    \ = adjs[src].emplace(src, dst, cap, cost, nullptr);\n    ptr->rev = adjs[dst].emplace(dst,\
    \ src, 0, -cost, ptr);\n  }\n\n protected:\n  constexpr static size_t nil = -1;\n\
    \  std::vector<adj_type> adjs;\n};  // class flow_base\n#line 6 \"graph/directed/flow/min_cost_flow.hpp\"\
    \n// Successive shortest paths algorithm.\ntemplate <class cap_t, class cost_t>\n\
    class min_cost_flow : public flow_base<cap_t, cost_t> {\n  using base = flow_base<cap_t,\
    \ cost_t>;\n  using edge_t = typename base::edge_t;\n  using base::adjs;\n  using\
    \ base::nil;\n\n  cost_t min_cost, total_cost;\n  std::vector<cap_t> supp;\n \
    \ std::vector<cost_t> ptnl;\n\n  void copy_member(const min_cost_flow &other)\
    \ {\n    min_cost = other.min_cost;\n    total_cost = other.total_cost;\n    supp\
    \ = other.supp;\n    ptnl = other.ptnl;\n  }\n\n  void Dijkstra(std::vector<edge_t\
    \ *> &last) {\n    const cost_t infty(total_cost + 1);\n    std::vector<cost_t>\
    \ nptnl(size(), infty);\n    /*/ // O((V + E)logV)\n    struct node_t\n    {\n\
    \        size_t id; cost_t dist;\n        node_t(size_t id, cost_t dist) : id(id),\
    \ dist(dist) {}\n        bool operator<(const node_t &rhs) const { return rhs.dist\
    \ < dist; }\n    };\n    std::priority_queue<node_t> que;\n    for(size_t src{};\
    \ src != size(); ++src)\n    {\n        if(supp[src] > static_cast<cap_t>(0))\n\
    \        {\n            nptnl[src] = 0;\n            for(edge_t &e : adjs[src])\n\
    \            {\n                if(supp[e.dst] > static_cast<cap_t>(0)) continue;\n\
    \                if(e.avbl() && nptnl[e.dst] > e.cost)\n                {\n  \
    \                  que.emplace(e.dst, (nptnl[e.dst] = e.cost) - ptnl[e.dst]);\n\
    \                    last[e.dst] = &e;\n                }\n            }\n   \
    \     }\n    }\n    while(!que.empty())\n    {\n        auto [src, ndist] = que.top();\n\
    \        que.pop();\n        if(ndist + ptnl[src] != nptnl[src]) continue;\n \
    \       for(edge_t &e : adjs[src])\n        {\n            if(e.avbl() && nptnl[e.dst]\
    \ > nptnl[src] + e.cost)\n            {\n                que.emplace(e.dst, (nptnl[e.dst]\
    \ = nptnl[src] + e.cost) -\n    ptnl[e.dst]); last[e.dst] = &e;\n            }\n\
    \        }\n    }\n    /*/ // O(V^2)\n    std::vector<bool> used(size());\n  \
    \  for (size_t src{}; src != size(); ++src) {\n      if (static_cast<cap_t>(0)\
    \ < supp[src]) {\n        used[src] = true;\n        nptnl[src] = 0;\n       \
    \ for (edge_t &e : adjs[src]) {\n          if (static_cast<cap_t>(0) < supp[e.dst])\
    \ continue;\n          if (e.avbl() && nptnl[e.dst] > e.cost) {\n            nptnl[e.dst]\
    \ = e.cost;\n            last[e.dst] = &e;\n          }\n        }\n      }\n\
    \    }\n    for (;;) {\n      size_t src(nil);\n      cost_t sp{infty};\n    \
    \  for (size_t node{}; node != size(); ++node) {\n        if (used[node] || nptnl[node]\
    \ == infty) continue;\n        cost_t dist{nptnl[node] - ptnl[node]};\n      \
    \  if (sp > dist) {\n          sp = dist;\n          src = node;\n        }\n\
    \      }\n      if (src == nil) break;\n      used[src] = true;\n      for (edge_t\
    \ &e : adjs[src]) {\n        if (e.avbl() && nptnl[e.dst] > nptnl[src] + e.cost)\
    \ {\n          nptnl[e.dst] = nptnl[src] + e.cost;\n          last[e.dst] = &e;\n\
    \        }\n      }\n    }\n    //*/\n    ptnl.swap(nptnl);\n  }\n\n public:\n\
    \  using base::size;\n\n  min_cost_flow(size_t n = 0)\n      : base::flow_base(n),\
    \ min_cost(0), total_cost(0), supp(n), ptnl(n) {}\n\n  min_cost_flow(const min_cost_flow\
    \ &other) : base::flow_base(other) {\n    copy_member(other);\n  }\n\n  min_cost_flow\
    \ &operator=(const min_cost_flow &other) {\n    base::operator=(other);\n    copy_member(other);\n\
    \    return *this;\n  }\n\n  void add_edge(size_t src, size_t dst, const cap_t\
    \ &cap, const cost_t &cost) {\n    assert(src != dst);\n    if (cost < static_cast<cost_t>(0))\
    \ {\n      supp[src] -= cap;\n      supp[dst] += cap;\n      min_cost += cap *\
    \ cost;\n      total_cost -= cap * cost;\n      base::add_edge(dst, src, cap,\
    \ -cost);\n    } else {\n      total_cost += cap * cost;\n      base::add_edge(src,\
    \ dst, cap, cost);\n    }\n  }\n\n  void add_edge(size_t src, size_t dst, const\
    \ cap_t &lower, const cap_t &upper,\n                const cost_t &cost) {\n \
    \   assert(!(upper < lower));\n    supp[src] -= lower;\n    supp[dst] += lower;\n\
    \    min_cost += lower * cost;\n    add_edge(src, dst, upper - lower, cost);\n\
    \  }\n\n  void supply(size_t node, const cap_t &vol) {\n    assert(node < size());\n\
    \    supp[node] += vol;\n  }\n\n  bool flow() {\n    for (bool aug = true; aug;)\
    \ {\n      aug = false;\n      std::vector<edge_t *> last(size());\n      Dijkstra(last);\n\
    \      std::vector<bool> shut(size());\n      for (size_t dst{}; dst != size();\
    \ ++dst) {\n        if (supp[dst] < static_cast<cap_t>(0) and last[dst]) {\n \
    \         cap_t resid{-supp[dst]};\n          size_t src{dst}, block(nil);\n \
    \         while (last[src] && !shut[src]) {\n            if (!(resid < last[src]->cap))\
    \ resid = last[block = src]->cap;\n            src = last[src]->src;\n       \
    \   }\n          if (shut[src])\n            block = src;\n          else {\n\
    \            if (!(resid < supp[src])) {\n              resid = supp[src];\n \
    \             block = src;\n            }\n            for (edge_t *e{last[dst]};\
    \ e; e = last[e->src]) {\n              e->cap -= resid;\n              e->rev->cap\
    \ += resid;\n            }\n            supp[src] -= resid;\n            supp[dst]\
    \ += resid;\n            min_cost += ptnl[dst] * resid;\n            aug = true;\n\
    \          }\n          if (~block) {\n            for (size_t node{dst};; node\
    \ = last[node]->src) {\n              shut[node] = true;\n              if (node\
    \ == block) break;\n            }\n          }\n        }\n      }\n    }\n  \
    \  return std::none_of(begin(supp), end(supp),\n                        [](const\
    \ cap_t &s) { return s < 0 || 0 < s; });\n  }\n\n  cost_t optimal() {\n    assert(flow());\n\
    \    return min_cost;\n  }\n};  // class min_cost_flow\n"
  code: "#pragma once\n#include <algorithm>\n#include <queue>\n\n#include \"base.hpp\"\
    \n// Successive shortest paths algorithm.\ntemplate <class cap_t, class cost_t>\n\
    class min_cost_flow : public flow_base<cap_t, cost_t> {\n  using base = flow_base<cap_t,\
    \ cost_t>;\n  using edge_t = typename base::edge_t;\n  using base::adjs;\n  using\
    \ base::nil;\n\n  cost_t min_cost, total_cost;\n  std::vector<cap_t> supp;\n \
    \ std::vector<cost_t> ptnl;\n\n  void copy_member(const min_cost_flow &other)\
    \ {\n    min_cost = other.min_cost;\n    total_cost = other.total_cost;\n    supp\
    \ = other.supp;\n    ptnl = other.ptnl;\n  }\n\n  void Dijkstra(std::vector<edge_t\
    \ *> &last) {\n    const cost_t infty(total_cost + 1);\n    std::vector<cost_t>\
    \ nptnl(size(), infty);\n    /*/ // O((V + E)logV)\n    struct node_t\n    {\n\
    \        size_t id; cost_t dist;\n        node_t(size_t id, cost_t dist) : id(id),\
    \ dist(dist) {}\n        bool operator<(const node_t &rhs) const { return rhs.dist\
    \ < dist; }\n    };\n    std::priority_queue<node_t> que;\n    for(size_t src{};\
    \ src != size(); ++src)\n    {\n        if(supp[src] > static_cast<cap_t>(0))\n\
    \        {\n            nptnl[src] = 0;\n            for(edge_t &e : adjs[src])\n\
    \            {\n                if(supp[e.dst] > static_cast<cap_t>(0)) continue;\n\
    \                if(e.avbl() && nptnl[e.dst] > e.cost)\n                {\n  \
    \                  que.emplace(e.dst, (nptnl[e.dst] = e.cost) - ptnl[e.dst]);\n\
    \                    last[e.dst] = &e;\n                }\n            }\n   \
    \     }\n    }\n    while(!que.empty())\n    {\n        auto [src, ndist] = que.top();\n\
    \        que.pop();\n        if(ndist + ptnl[src] != nptnl[src]) continue;\n \
    \       for(edge_t &e : adjs[src])\n        {\n            if(e.avbl() && nptnl[e.dst]\
    \ > nptnl[src] + e.cost)\n            {\n                que.emplace(e.dst, (nptnl[e.dst]\
    \ = nptnl[src] + e.cost) -\n    ptnl[e.dst]); last[e.dst] = &e;\n            }\n\
    \        }\n    }\n    /*/ // O(V^2)\n    std::vector<bool> used(size());\n  \
    \  for (size_t src{}; src != size(); ++src) {\n      if (static_cast<cap_t>(0)\
    \ < supp[src]) {\n        used[src] = true;\n        nptnl[src] = 0;\n       \
    \ for (edge_t &e : adjs[src]) {\n          if (static_cast<cap_t>(0) < supp[e.dst])\
    \ continue;\n          if (e.avbl() && nptnl[e.dst] > e.cost) {\n            nptnl[e.dst]\
    \ = e.cost;\n            last[e.dst] = &e;\n          }\n        }\n      }\n\
    \    }\n    for (;;) {\n      size_t src(nil);\n      cost_t sp{infty};\n    \
    \  for (size_t node{}; node != size(); ++node) {\n        if (used[node] || nptnl[node]\
    \ == infty) continue;\n        cost_t dist{nptnl[node] - ptnl[node]};\n      \
    \  if (sp > dist) {\n          sp = dist;\n          src = node;\n        }\n\
    \      }\n      if (src == nil) break;\n      used[src] = true;\n      for (edge_t\
    \ &e : adjs[src]) {\n        if (e.avbl() && nptnl[e.dst] > nptnl[src] + e.cost)\
    \ {\n          nptnl[e.dst] = nptnl[src] + e.cost;\n          last[e.dst] = &e;\n\
    \        }\n      }\n    }\n    //*/\n    ptnl.swap(nptnl);\n  }\n\n public:\n\
    \  using base::size;\n\n  min_cost_flow(size_t n = 0)\n      : base::flow_base(n),\
    \ min_cost(0), total_cost(0), supp(n), ptnl(n) {}\n\n  min_cost_flow(const min_cost_flow\
    \ &other) : base::flow_base(other) {\n    copy_member(other);\n  }\n\n  min_cost_flow\
    \ &operator=(const min_cost_flow &other) {\n    base::operator=(other);\n    copy_member(other);\n\
    \    return *this;\n  }\n\n  void add_edge(size_t src, size_t dst, const cap_t\
    \ &cap, const cost_t &cost) {\n    assert(src != dst);\n    if (cost < static_cast<cost_t>(0))\
    \ {\n      supp[src] -= cap;\n      supp[dst] += cap;\n      min_cost += cap *\
    \ cost;\n      total_cost -= cap * cost;\n      base::add_edge(dst, src, cap,\
    \ -cost);\n    } else {\n      total_cost += cap * cost;\n      base::add_edge(src,\
    \ dst, cap, cost);\n    }\n  }\n\n  void add_edge(size_t src, size_t dst, const\
    \ cap_t &lower, const cap_t &upper,\n                const cost_t &cost) {\n \
    \   assert(!(upper < lower));\n    supp[src] -= lower;\n    supp[dst] += lower;\n\
    \    min_cost += lower * cost;\n    add_edge(src, dst, upper - lower, cost);\n\
    \  }\n\n  void supply(size_t node, const cap_t &vol) {\n    assert(node < size());\n\
    \    supp[node] += vol;\n  }\n\n  bool flow() {\n    for (bool aug = true; aug;)\
    \ {\n      aug = false;\n      std::vector<edge_t *> last(size());\n      Dijkstra(last);\n\
    \      std::vector<bool> shut(size());\n      for (size_t dst{}; dst != size();\
    \ ++dst) {\n        if (supp[dst] < static_cast<cap_t>(0) and last[dst]) {\n \
    \         cap_t resid{-supp[dst]};\n          size_t src{dst}, block(nil);\n \
    \         while (last[src] && !shut[src]) {\n            if (!(resid < last[src]->cap))\
    \ resid = last[block = src]->cap;\n            src = last[src]->src;\n       \
    \   }\n          if (shut[src])\n            block = src;\n          else {\n\
    \            if (!(resid < supp[src])) {\n              resid = supp[src];\n \
    \             block = src;\n            }\n            for (edge_t *e{last[dst]};\
    \ e; e = last[e->src]) {\n              e->cap -= resid;\n              e->rev->cap\
    \ += resid;\n            }\n            supp[src] -= resid;\n            supp[dst]\
    \ += resid;\n            min_cost += ptnl[dst] * resid;\n            aug = true;\n\
    \          }\n          if (~block) {\n            for (size_t node{dst};; node\
    \ = last[node]->src) {\n              shut[node] = true;\n              if (node\
    \ == block) break;\n            }\n          }\n        }\n      }\n    }\n  \
    \  return std::none_of(begin(supp), end(supp),\n                        [](const\
    \ cap_t &s) { return s < 0 || 0 < s; });\n  }\n\n  cost_t optimal() {\n    assert(flow());\n\
    \    return min_cost;\n  }\n};  // class min_cost_flow\n"
  dependsOn:
  - graph/directed/flow/base.hpp
  isVerificationFile: false
  path: graph/directed/flow/min_cost_flow.hpp
  requiredBy: []
  timestamp: '2020-09-18 02:10:10+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/assignment.test.cpp
  - test/aizu-online-judge/aors_score.test.cpp
documentation_of: graph/directed/flow/min_cost_flow.hpp
layout: document
redirect_from:
- /library/graph/directed/flow/min_cost_flow.hpp
- /library/graph/directed/flow/min_cost_flow.hpp.html
title: graph/directed/flow/min_cost_flow.hpp
---
