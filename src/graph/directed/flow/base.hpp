#pragma once

/**
 * @file base.hpp
 * @brief Flow Graph
 * @date 2021-01-15
 *
 *
 */

#include <cassert>
#include <vector>

namespace workspace {

template <class Cap, class Cost> class flow_graph {
 protected:
  class adjacency;

 public:
  using value_type = adjacency;
  using reference = adjacency &;
  using const_reference = adjacency const &;
  using container_type = std::vector<value_type>;
  using size_type = typename container_type::size_type;

 protected:
  /**
   * @brief Edge of flow graph.
   *
   */
  class edge {
   public:
    size_type src, dst;
    Cap cap;
    Cost cost;
    edge *rev;

    edge() = default;

    edge(size_type src, size_type dst, const Cap &cap, edge *rev)
        : src(src), dst(dst), cap(cap), rev(rev) {}

    edge(size_type src, size_type dst, const Cap &cap, const Cost &cost,
         edge *rev)
        : src(src), dst(dst), cap(cap), cost(cost), rev(rev) {}

    const Cap &flow(const Cap &f = 0) { return cap -= f, rev->cap += f; }
  };

  class adjacency {
    edge *first, *iter, *last;

   public:
    using value_type = edge;
    using reference = edge &;
    using const_reference = edge const &;
    using pointer = edge *;
    using const_pointer = const edge *;

    adjacency() : first(new edge[1]), iter(first), last(first + 1) {}
    ~adjacency() { delete[] first; }

    template <class... Args> pointer emplace(Args &&... args) {
      if (iter == last) {
        size_type len(last - first);
        edge *nfst = iter = new edge[len << 1];
        for (edge *p{first}; p != last; ++p, ++iter)
          p->rev->rev = iter, *iter = *p;
        delete[] first;
        first = nfst;
        last = iter + len;
      }
      *iter = edge(args...);
      return iter++;
    }

    reference operator[](size_type i) {
      assert(i < size());
      return *(first + i);
    }

    const_reference operator[](size_type i) const {
      assert(i < size());
      return *(first + i);
    }

    size_type size() const { return iter - first; }

    pointer begin() { return first; }
    const_pointer begin() const { return first; }

    pointer end() { return iter; }
    const_pointer end() const { return iter; }
  };

 public:
  /**
   * @brief Construct a new flow base object
   *
   * @param n Number of vertices
   */
  flow_graph(size_type n = 0) : graph(n) {}

  flow_graph(const flow_graph &other) : graph(other.size()) {
    for (size_type node{}; node != size(); ++node)
      for (const auto &[src, dst, cap, cost, rev] : other[node])
        if (src == node) {
          edge *ptr = graph[src].emplace(src, dst, cap, cost, nullptr);
          ptr->rev = graph[dst].emplace(dst, src, rev->cap, -cost, ptr);
          rev->src = nil;
        } else {
          rev->rev->src = node;
        }
  }

  flow_graph &operator=(const flow_graph &rhs) {
    if (this != &rhs) graph.swap(flow_graph(rhs).graph);
    return *this;
  }

  /**
   * @return Number of vertices.
   */
  size_type size() const { return graph.size(); }

  reference operator[](size_type node) {
    assert(node < size());
    return graph[node];
  }

  const_reference &operator[](size_type node) const {
    assert(node < size());
    return graph[node];
  }

  typename container_type::iterator begin() { return graph.begin(); }

  typename container_type::iterator end() { return graph.end(); }

  typename container_type::const_iterator begin() const {
    return graph.begin();
  }

  typename container_type::const_iterator end() const { return graph.end(); }

  virtual typename adjacency::pointer add_edge(size_type src, size_type dst,
                                               const Cap &cap,
                                               const Cost &cost) {
    assert(src < size());
    assert(dst < size());
    assert(!(cap < static_cast<Cap>(0)));
    if (!(static_cast<Cap>(0) < cap) || src == dst) return nullptr;
    auto ptr = graph[src].emplace(src, dst, cap, cost, nullptr);
    ptr->rev = graph[dst].emplace(dst, src, 0, -cost, ptr);
    return ptr;
  }

 protected:
  constexpr static size_type nil = -1;
  container_type graph;
};

}  // namespace workspace
