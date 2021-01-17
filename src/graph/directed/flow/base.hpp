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

template <class Cap, class Cost = void> class flow_graph {
 public:
  class adjacency;
  using value_type = adjacency;
  using reference = adjacency &;
  using const_reference = adjacency const &;
  using container_type = std::vector<value_type>;
  using size_type = typename container_type::size_type;

  class unweighted_edge {
   public:
    size_type src, dst;
    Cap cap;
    unweighted_edge *rev;

    unweighted_edge() = default;

    unweighted_edge(size_type src, size_type dst, const Cap &cap,
                    unweighted_edge *rev)
        : src(src), dst(dst), cap(cap), rev(rev) {
      assert(!(cap < static_cast<Cap>(0)));
    }

    const Cap &flow(const Cap &f = 0) { return cap -= f, rev->cap += f; }

    unweighted_edge make_rev() { return {dst, src, 0, this}; }
  };

  class weighted_edge : public unweighted_edge {
   public:
    Cost cost;

    weighted_edge() = default;

    weighted_edge(size_type src, size_type dst, const Cap &cap,
                  const Cost &cost, weighted_edge *rev)
        : unweighted_edge(src, dst, cap, rev), cost(cost) {}

    weighted_edge make_rev() {
      return {unweighted_edge::dst, unweighted_edge::src, 0, -cost, this};
    }
  };

  using edge = typename std::conditional<std::is_void<Cost>::value,
                                         unweighted_edge, weighted_edge>::type;

  class adjacency {
   public:
    using value_type = edge;
    using reference = edge &;
    using const_reference = edge const &;
    using pointer = edge *;
    using const_pointer = const edge *;

    adjacency() : first(new edge[1]), iter(first), last(first + 1) {}
    ~adjacency() { delete[] first; }

    template <class... Args> reference emplace(Args &&... args) {
      if (iter == last) {
        size_type len(last - first);
        edge *nfst = iter = new edge[len << 1];
        for (edge *p{first}; p != last; ++p, ++iter)
          p->rev->rev = iter, *iter = *p;
        delete[] first;
        first = nfst;
        last = iter + len;
      }
      return *iter++ = edge(args...);
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

   protected:
    pointer first, iter, last;
  };

  /**
   * @brief Construct a new flow base object
   *
   * @param n Number of vertices
   */
  flow_graph(size_type n = 0) : graph(n) {}

  flow_graph(const flow_graph &other) : graph(other.size()) {
    for (size_type node = 0; node != size(); ++node)
      for (edge cp : other[node])
        if (cp.src == node) {
          edge rcp = *cp.rev;
          cp.rev->src = nil;
          edge &ref = graph[node].emplace(cp);
          rcp.rev = &ref;
          ref.rev = &graph[cp.dst].emplace(rcp);
        } else
          cp.rev->rev->src = node;
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

  template <class... Args>
  typename adjacency::reference add_edge(size_type src, size_type dst,
                                         Args &&... args) {
    assert(src < size());
    assert(dst < size());
    auto &ref = graph[src].emplace(src, dst, args..., nullptr);
    ref.rev = &graph[dst].emplace(ref.make_rev());
    return ref;
  }

 protected:
  constexpr static size_type nil = -1;
  container_type graph;
};

}  // namespace workspace
