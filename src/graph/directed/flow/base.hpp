#pragma once

/**
 * @file base.hpp
 * @brief Flow Graph
 * @date 2021-01-15
 *
 *
 */

#include <cassert>
#include <numeric>
#include <vector>

namespace workspace {

template <class Cap, class Cost = void> class flow_graph {
 protected:
  class adjacency_impl;

 public:
  using container_type = std::vector<adjacency_impl>;
  using size_type = typename container_type::size_type;

  class unweighted_edge {
   public:
    size_type src, dst;
    Cap cap;

    unweighted_edge() = default;

    unweighted_edge(size_type src, size_type dst, const Cap &cap)
        : src(src), dst(dst), cap(cap) {
      assert(!(cap < static_cast<Cap>(0)));
    }

    template <class Os>
    friend Os &operator<<(Os &__os, unweighted_edge const &__e) {
      return __os << __e.src << " " << __e.dst << " " << __e.cap;
    }

   protected:
    unweighted_edge make_rev() { return {dst, src, 0}; }
  };

  class weighted_edge : public unweighted_edge {
   public:
    Cost cost;

    weighted_edge() = default;

    weighted_edge(size_type src, size_type dst, const Cap &cap,
                  const Cost &cost)
        : unweighted_edge(src, dst, cap), cost(cost) {}

    template <class Os>
    friend Os &operator<<(Os &__os, weighted_edge const &__e) {
      return __os << static_cast<unweighted_edge>(__e) << " " << __e.cost;
    }

   protected:
    weighted_edge make_rev() {
      return {unweighted_edge::dst, unweighted_edge::src, 0, -cost};
    }
  };

  using edge = typename std::conditional<std::is_void<Cost>::value,
                                         unweighted_edge, weighted_edge>::type;

 protected:
  struct edge_impl : edge {
    bool aux = false;
    edge_impl *rev = nullptr;

    edge_impl() = default;

    edge_impl(const edge_impl &__e) = default;

    edge_impl(const edge &__e) : edge(__e) {}

    void flow(const Cap &f) { edge::cap -= f, rev->cap += f; }

    edge_impl rev_cp() {
      edge_impl __e;
      if (rev)
        __e = *rev;
      else {
        __e = edge::make_rev();
        __e.aux = true;
      }
      __e.rev = this;
      return __e;
    }
  };

 public:
  class adjacency {
   public:
    using value_type = edge;
    using reference = edge &;
    using const_reference = edge const &;
    using pointer = edge *;
    using const_pointer = const edge *;

    class const_iterator {
     public:
      const edge_impl *__p;

      bool operator!=(const_iterator const &__x) const {
        return __p != __x.__p;
      }

      const_iterator &operator++() {
        do
          ++__p;
        while (__p->rev && __p->aux);
        return *this;
      }

      const_pointer operator->() const { return __p; }

      const_reference operator*() const { return *__p; }
    };

    adjacency()
        : first(new edge_impl[2]), last(first + 1), __s(first), __t(first) {}

    ~adjacency() { delete[] first; }

    const_reference operator[](size_type i) const {
      assert(i < size());
      return *(first + i);
    }

    size_type size() const { return __t - first; }

    auto begin() const { return const_iterator{__s}; }
    auto end() const { return const_iterator{__t}; }

    /**
     * @brief Construct a new adjacency object
     *
     * @param __x Rvalue reference to another object
     */
    adjacency(adjacency &&__x) : first(nullptr) { operator=(std::move(__x)); }

    /**
     * @brief Assignment operator.
     *
     * @param __x Rvalue reference to another object
     * @return Reference to this object.
     */
    adjacency &operator=(adjacency &&__x) {
      std::swap(first, __x.first);
      last = __x.last;
      __s = __x.__s;
      __t = __x.__t;
      return *this;
    }

   protected:
    edge_impl *first, *last, *__s, *__t;
  };

  using value_type = adjacency;
  using reference = adjacency &;
  using const_reference = adjacency const &;

 protected:
  class adjacency_impl : public adjacency {
   public:
    using base = adjacency;
    using base::__s;
    using base::__t;
    using base::first;
    using base::last;

    template <class... Args> auto emplace(Args &&... args) {
      if (__t == last) {
        size_type __n(last - first);
        edge_impl *loc = new edge_impl[__n << 1 | 1];
        __s += loc - first;
        __t = loc;
        for (edge_impl *__p{first}; __p != last; ++__p, ++__t)
          __p->rev->rev = __t, *__t = *__p;
        delete[] first;
        first = loc;
        last = __t + __n;
      }
      *__t = edge_impl(args...);
      if (__s->aux) ++__s;
      return __t++;
    }

    using iterator = edge_impl *;
    auto begin() const { return first; }
    auto end() const { return __t; }
  };

 public:
  /**
   * @brief Construct a new flow graph object
   *
   * @param __n Number of vertices
   */
  flow_graph(size_type __n = 0) : graph(__n) {}

  /**
   * @brief Construct a new flow graph object
   *
   * @param __x Const reference to another object
   */
  flow_graph(const flow_graph &__x) : graph(__x.size()) {
    for (auto &&__adj : __x)
      for (auto &&__e : __adj) _add_edge(__e);
  }

  /**
   * @brief Assignment operator.
   *
   * @param __x Rvalue reference to another object
   * @return Reference to this object.
   */
  flow_graph &operator=(flow_graph &&__x) {
    graph.swap(__x.graph);
    return *this;
  }

  /**
   * @return Number of nodes.
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

  class const_iterator : public container_type::const_iterator {
   public:
    using base = typename container_type::const_iterator;
    using const_reference = const adjacency &;
    using const_pointer = const adjacency *;

    const_iterator(base const &__i) : base(__i) {}

    const_pointer operator->() const { return base::operator->(); }

    const_reference operator*() const { return base::operator*(); }
  };

  auto begin() const { return const_iterator{graph.begin()}; }
  auto end() const { return const_iterator{graph.end()}; }

  size_type add_node() { return add_nodes(1).front(); }

  virtual std::vector<size_type> add_nodes(size_type __n) {
    std::vector<size_type> __nds(__n);
    std::iota(__nds.begin(), __nds.end(), graph.size());
    __n += graph.size();
    if (__n > graph.capacity()) {
      flow_graph __x(__n);
      for (auto &&adj : graph)
        for (auto &&__e : adj)
          if (!__e.aux) __x._add_edge(__e);
      graph.swap(__x.graph);
    } else
      graph.resize(__n);
    return __nds;
  }

  template <class... Args> const edge &add_edge(Args &&... args) {
    return *_add_edge(edge(args...));
  }

 protected:
  template <class... Args> edge_impl *_add_edge(Args &&... args) {
    edge_impl __e(args...);
    assert(__e.src < size());
    assert(__e.dst < size());
    auto __p = graph[__e.src].emplace(__e);
    __p->rev = graph[__e.dst].emplace(__p->rev_cp());
    return __p;
  }

  constexpr static size_type nil = -1;
  container_type graph;

  template <class Os> friend Os &operator<<(Os &__os, flow_graph const &__g) {
    for (const auto &adj : __g)
      for (const auto &e : adj) __os << e << "\n";
    return __os;
  }
};

}  // namespace workspace
