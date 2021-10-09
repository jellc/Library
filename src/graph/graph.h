#pragma once

/**
 * @file graph.h
 * @brief Graph
 */

#include "base.h"

namespace workspace {

template <class _Attr = _graph_impl::null,
          class _List = std::vector<edge<_Attr>>>
class graph : public graph_base<_Attr, _List> {
  using base_type = graph_base<_Attr, _List>;

 public:
  using typename base_type::edge_type;
  using typename base_type::node_type;
  using typename base_type::size_type;

  graph(size_type __n = 0) noexcept : base_type(__n) {}

  template <class... _Args>
  decltype(auto) add_edge(node_type __u, node_type __v,
                          _Args &&...__args) noexcept {
    base_type::add_edge(__v, __u, __args...);
    return base_type::add_edge(__u, __v, std::forward<_Args>(__args)...);
  }

  /**
   * @brief Prim's algorithm.
   * @param __r Starting vertex. Defalut: 0.
   * @return Edges of a minimum spanning tree (of the connected component).
   */
  decltype(auto) prim(node_type __r = 0) const noexcept {
    node_type __a[]{__r};
    return prim(__a, __a + 1);
  }

  /**
   * @brief Prim's algorithm.
   * @param __r Starting vertices. Defalut: 0.
   * @return Edges of a minimum spanning tree (of the connected component).
   */
  template <class _Iterator>
  decltype(auto) prim(_Iterator __first, _Iterator __last) const noexcept {
    return base_type::template search<std::priority_queue<
        edge_type, std::vector<edge_type>, std::greater<edge_type>>>(__first,
                                                                     __last);
  }
};

template <class _Weight, class _Attr = _graph_impl::null,
          class _List = std::vector<weighted_edge<_Weight, _Attr>>>
class weighted_graph : public graph<_Attr, _List> {
  using graph<_Attr, _List>::graph;
};

}  // namespace workspace
