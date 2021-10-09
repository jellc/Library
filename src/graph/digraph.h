#pragma once

/**
 * @file digraph.h
 * @brief Digraph
 */

#include "base.h"

namespace workspace {

template <class _Attr = _graph_impl::null,
          class _List = std::vector<edge<_Attr>>>
class digraph : public graph_base<_Attr, _List> {
 public:
  using base_type = graph_base<_Attr, _List>;

  using typename base_type::edge_type;
  using typename base_type::node_type;
  using typename base_type::size_type;

  using base_type::size;
  using base_type::operator[];

  digraph(size_type __n = 0) : base_type(__n) {}

  auto scc() const noexcept;
};

template <class _Weight, class _Attr = _graph_impl::null,
          class _List = std::vector<weighted_edge<_Weight, _Attr>>>
using weighted_digraph = digraph<_Attr, _List>;

}  // namespace workspace
