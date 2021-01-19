#pragma once

/**
 * @file Dinic.hpp
 * @brief Dinic's Algorithm
 * @date 2021-01-15
 *
 *
 */

#include "base.hpp"

namespace workspace {

/**
 * @brief Compute the maximum flow.
 *
 * @tparam Cap Capacity type
 */
template <class Cap> class Dinic : public flow_graph<Cap> {
  using base = flow_graph<Cap>;
  using base::nil;

 public:
  using size_type = typename base::size_type;

 protected:
  std::vector<size_type> level;
  std::vector<typename base::container_type::value_type::iterator> iter;

  Cap dfs(size_type src, size_type dst, Cap bound) {
    if (src == dst || bound == 0) return bound;
    Cap flow(0);
    for (auto &e{iter[dst]}; e != base::graph[dst].end(); ++e)
      if (static_cast<Cap>(0) < e->rev->cap && level[e->dst] < level[dst])
        if (Cap achv = dfs(src, e->dst, std::min(bound, e->rev->cap));
            achv > 0) {
          e->rev->flow(achv);
          flow += achv, bound -= achv;
          if (bound == 0) break;
        }
    return flow;
  }

 public:
  /**
   * @brief Construct a new Dinic object
   *
   * @param __n Number of nodes
   */
  Dinic(size_type __n = 0)
      : base::flow_graph(__n), level(__n, nil), iter(__n) {}

  std::vector<size_type> add_nodes(size_type __n) override {
    auto __nds = base::add_nodes(__n);
    level.resize(base::size(), nil);
    iter.resize(base::size());
    return __nds;
  }

  /**
   * @brief Add an edge to the graph.
   *
   * @param src Source
   * @param dst Destination
   * @param cap Capacity(defalut: 1)
   * @return Reference to the edge.
   */
  typename base::edge const &add_edge(size_type src, size_type dst,
                                      const Cap &cap = 1) {
    return *base::_add_edge(src, dst, cap);
  }

  // void add_undirected_edge(size_type src, size_type dst, Cap cap) {
  //   base::add_undirected_edge(src, dst, cap, false);
  // }

  /**
   * @brief Run Dinic's algorithm.
   *
   * @param src Source
   * @param dst Destination
   * @return Maximum flow.
   */
  Cap flow(size_type src, size_type dst) {
    assert(src < base::size());
    assert(dst < base::size());
    Cap flow(0), bound(0);
    for (const auto &e : base::graph[src]) bound += e.cap;
    for (std::vector<size_type> que(base::size());;
         std::fill(level.begin(), level.end(), nil)) {
      level[que.front() = src] = 0;
      for (auto ql{que.begin()}, qr{std::next(ql)};
           level[dst] == nil && ql != qr; ++ql)
        for (const auto &e : base::graph[*ql])
          if (static_cast<Cap>(0) < e.cap && level[e.dst] == nil)
            level[ *qr++ = e.dst] = level[*ql] + 1;
      if (level[dst] == nil) break;
      for (size_type node{}; node != base::size(); ++node)
        iter[node] = base::graph[node].begin();
      flow += dfs(src, dst, bound);
    }
    return flow;
  }
};

}  // namespace workspace
