#pragma once

/**
 * @file forest.h
 * @brief Forest
 */

#include <algorithm>

#include "graph.h"

namespace workspace {

template <class _Attr = _graph_impl::null,
          class _List = std::vector<edge<_Attr>>>
class forest : public graph<_Attr, _List> {
  using base_type = graph<_Attr, _List>;

 public:
  using typename base_type::edge_type;
  using typename base_type::node_type;
  using typename base_type::size_type;

  forest(size_type __n = 0) noexcept : base_type(__n) {}

  /**
   * @brief Diameter of a tree.
   * @param __v Vertex in the connected component.
   */
  auto diameter(node_type __v = 0) const noexcept {
    std::vector<edge_type> __diam;
    auto __dist = base_type::bellman_ford(__v);

    if (!__dist.empty())
      for (__dist = base_type::bellman_ford(
               std::max_element(__dist.begin(), __dist.end())->head),
          __v = std::max_element(__dist.begin(), __dist.end())->head;
           !__dist.empty(); __dist.pop_back())
        if (__dist.back().head == __v) {
          if (!__diam.empty()) __diam.back().weight -= __dist.back().weight;
          __v = __dist.back().tail,
          __diam.emplace_back(std::move(__dist.back()));
        }

    std::reverse(__diam.begin(), __diam.end());
    return __diam;
  }
};

template <class _Weight, class _Attr = _graph_impl::null,
          class _List = std::vector<weighted_edge<_Weight, _Attr>>>
class weighted_forest : public forest<_Attr, _List> {
  using forest<_Attr, _List>::forest;
};

}  // namespace workspace
