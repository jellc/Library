#pragma once

/**
 * @file Dinic.hpp
 * @brief Dinic's Algorithm
 */

#include <limits>

#include "base.hpp"

namespace workspace {

/**
 * @brief Compute the maximum flow.
 *
 * @tparam _Cap Capacity type
 */
template <class _Cap> class Dinic : public flow_graph<_Cap> {
  using base = flow_graph<_Cap>;

 public:
  using size_type = typename base::size_type;

 protected:
  constexpr static size_type nil = -1;

  std::vector<size_type> level;
  std::vector<typename base::container_type::value_type::iterator> iter;

  _Cap dfs(size_type __src, size_type __dst, _Cap __bound) {
    if (__src == __dst) return __bound;

    _Cap __flow(0);

    for (auto &__e{iter[__dst]}; __e != base::graph[__dst].end(); ++__e)
      if (static_cast<_Cap>(0) < __e->flow && level[__e->dst] < level[__dst])
        if (_Cap achv = dfs(__src, __e->dst, std::min(__bound, __e->flow));
            static_cast<_Cap>(0) < achv) {
          __e->push(-achv);
          __flow += achv, __bound -= achv;
          if (__bound == static_cast<_Cap>(0)) break;
        }

    return __flow;
  }

 public:
  /**
   * @brief Construct a new Dinic object.
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
   * @param __src Source
   * @param __dst Destination
   * @return Maximum flow.
   */
  _Cap run(size_type __src, size_type __dst) {
    assert(__src < base::size());
    assert(__dst < base::size());
    assert(__src != __dst);

    _Cap __flow = 0, __bound = std::numeric_limits<_Cap>::max();

    for (std::vector<size_type> __q(base::size());;
         std::fill(level.begin(), level.end(), nil)) {
      level[__q.front() = __src] = 0;

      for (auto __ql{__q.begin()}, __qr{std::next(__ql)};
           level[__dst] == nil && __ql != __qr; ++__ql)
        for (const auto &__e : base::graph[*__ql])
          if (static_cast<_Cap>(0) < __e.cap && level[__e.dst] == nil)
            level[ *__qr++ = __e.dst] = level[*__ql] + 1;

      if (level[__dst] == nil) break;

      for (size_type __x{}; __x != base::size(); ++__x)
        iter[__x] = base::graph[__x].begin();

      __flow += dfs(__src, __dst, __bound);
    }

    return __flow;
  }
};

}  // namespace workspace
