#pragma once

/**
 * @file Dinic.hpp
 * @brief Dinic's Algorithm
 * @date 2021-01-15
 *
 *
 */

#include <limits>

#include "base.hpp"

namespace workspace {

/**
 * @brief Compute the maximum flow.
 *
 * @tparam Cap Capacity type
 */
template <class Cap> class Dinic : public flow_graph<Cap> {
  using base = flow_graph<Cap>;

 public:
  using size_type = typename base::size_type;

 protected:
  constexpr static size_type nil = -1;

  std::vector<size_type> level;
  std::vector<typename base::container_type::value_type::iterator> iter;

  Cap dfs(size_type __s, size_type __d, Cap bound) {
    if (__s == __d) return bound;
    Cap flow(0);
    for (auto &e{iter[__d]}; e != base::graph[__d].end(); ++e)
      if (static_cast<Cap>(0) < e->flow && level[e->dst] < level[__d])
        if (Cap achv = dfs(__s, e->dst, std::min(bound, e->flow));
            static_cast<Cap>(0) < achv) {
          e->aug(-achv);
          flow += achv, bound -= achv;
          if (bound == static_cast<Cap>(0)) break;
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

  /**
   * @brief Add some nodes to the graph.
   *
   * @param __n Number of nodes added
   * @return List of indices of the nodes.
   */
  std::vector<size_type> add_nodes(size_type __n) override {
    auto __nds = base::add_nodes(__n);
    level.resize(base::size(), nil);
    iter.resize(base::size());
    return __nds;
  }

  /**
   * @brief Run Dinic's algorithm.
   *
   * @param __s Source
   * @param __d Destination
   * @return Maximum flow.
   */
  Cap run(size_type __s, size_type __d) {
    assert(__s < base::size());
    assert(__d < base::size());
    assert(__s != __d);
    Cap flow = 0, bound = std::numeric_limits<Cap>::max();
    for (std::vector<size_type> que(base::size());;
         std::fill(level.begin(), level.end(), nil)) {
      level[que.front() = __s] = 0;
      for (auto ql{que.begin()}, qr{std::next(ql)};
           level[__d] == nil && ql != qr; ++ql)
        for (const auto &e : base::graph[*ql])
          if (static_cast<Cap>(0) < e.cap && level[e.dst] == nil)
            level[ *qr++ = e.dst] = level[*ql] + 1;
      if (level[__d] == nil) break;
      for (size_type node{}; node != base::size(); ++node)
        iter[node] = base::graph[node].begin();
      flow += dfs(__s, __d, bound);
    }
    return flow;
  }
};

}  // namespace workspace
