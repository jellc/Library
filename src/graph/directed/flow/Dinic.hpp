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
template <class Cap = int> class Dinic : public flow_graph<Cap, bool> {
  using base = flow_graph<Cap, bool>;
  using base::add_edge;
  using base::graph;
  using base::nil;

 public:
  using edge = typename base::edge;
  using size_type = typename base::size_type;

 protected:
  std::vector<size_type> level;
  std::vector<edge *> itr;

  Cap dfs(size_type src, size_type dst, Cap bound) {
    if (src == dst || bound == 0) return bound;
    Cap flow(0);
    for (edge *&e{itr[dst]}; e != graph[dst].end(); ++e)
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
   * @param n Number of nodes.
   */
  Dinic(size_type n = 0) : base::flow_graph(n), level(n, nil), itr(n) {}

  Dinic(const Dinic &other)
      : base::flow_graph(other), level(other.level), itr(other.itr) {}

  Dinic &operator=(const Dinic &rhs) {
    if (this != &rhs) base::operator=(rhs), level = rhs.level, itr = rhs.itr;
    return *this;
  }

  /**
   * @brief Add an edge to the graph.
   *
   * @param src Source
   * @param dst Destination
   * @param cap Capacity
   * @return Reference to the edge.
   */
  typename base::adjacency::reference add_edge(size_type src, size_type dst,
                                               Cap cap) {
    return add_edge(src, dst, cap, false);
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
  Cap max_flow(size_type src, size_type dst) {
    assert(src < base::size());
    assert(dst < base::size());
    Cap flow(0), bound(0);
    for (const edge &e : graph[src]) bound += e.cap;
    for (std::vector<size_type> que(base::size());;
         std::fill(level.begin(), level.end(), nil)) {
      level[que.front() = src] = 0;
      for (auto ql{que.begin()}, qr{std::next(ql)};
           level[dst] == nil && ql != qr; ++ql)
        for (const edge &e : graph[*ql])
          if (static_cast<Cap>(0) < e.cap && level[e.dst] == nil)
            level[ *qr++ = e.dst] = level[*ql] + 1;
      if (level[dst] == nil) break;
      for (size_type node{}; node != base::size(); ++node)
        itr[node] = graph[node].begin();
      flow += dfs(src, dst, bound);
    }
    return flow;
  }
};

}  // namespace workspace
