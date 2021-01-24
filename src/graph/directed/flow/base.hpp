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
#include <tuple>
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
    size_type src;  // Source
    size_type dst;  // Destination
    Cap cap;        // Capacity
    Cap flow = 0;   // Flow

    unweighted_edge(size_type __s, size_type __d, const Cap &__u = 1)
        : src(__s), dst(__d), cap(__u) {
      assert(!(cap < static_cast<Cap>(0)));
    }

    /**
     * @brief Source, Destination, Capacity, Flow
     */
    template <class Os>
    friend Os &operator<<(Os &__os, unweighted_edge const &__e) {
      return __os << __e.src << ' ' << __e.dst << ' ' << __e.cap << ' '
                  << __e.flow;
    }

   protected:
    unweighted_edge() = default;

    unweighted_edge(size_type __s, size_type __d, const Cap &__u,
                    const Cap &__f)
        : src(__s), dst(__d), cap(__u), flow(__f) {}

    unweighted_edge make_rev() const { return {dst, src, flow, cap}; }
  };

  class weighted_edge : public unweighted_edge {
   public:
    Cost cost;  // Cost

    weighted_edge(const unweighted_edge &__e, const Cost &__c = 0)
        : unweighted_edge(__e), cost(__c) {}

    weighted_edge(size_type __s, size_type __d, const Cap &__u = 1,
                  const Cost &__c = 0)
        : unweighted_edge(__s, __d, __u), cost(__c) {}

    /**
     * @brief Source, Destination, Capacity, Flow, Cost
     */
    template <class Os>
    friend Os &operator<<(Os &__os, weighted_edge const &__e) {
      return __os << static_cast<unweighted_edge>(__e) << ' ' << __e.cost;
    }

   protected:
    weighted_edge() = default;

    weighted_edge make_rev() const {
      return {unweighted_edge::make_rev(), -cost};
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
    edge_impl &operator=(const edge_impl &__e) = default;

    edge_impl(edge_impl &&__e) = default;
    edge_impl &operator=(edge_impl &&__e) = default;

    edge_impl(const edge &__e) : edge(__e) {}
    edge_impl(edge &&__e) : edge(__e) {}

    void aug(Cap __f) {
      edge::cap -= __f;
      edge::flow += __f;
      if (rev) {
        rev->cap += __f;
        rev->flow -= __f;
      }
    }

    edge_impl make_rev() {
      edge_impl __e = edge::make_rev();
      __e.aux = true;
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

    class iterator {
      edge_impl *__p;

     public:
      iterator(edge_impl *__p = nullptr) : __p(__p) {}

      bool operator!=(iterator const &__x) const { return __p != __x.__p; }

      iterator &operator++() {
        do
          ++__p;
        while (__p->rev && __p->aux);
        return *this;
      }

      pointer operator->() const { return __p; }

      reference operator*() const { return *__p; }
    };

    class const_iterator {
      const edge_impl *__p;

     public:
      const_iterator(const edge_impl *__p = nullptr) : __p(__p) {}

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

    auto begin() { return iterator{__s}; }
    auto begin() const { return const_iterator{__s}; }

    auto end() { return iterator{__t}; }
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

    using iterator = edge_impl *;

    iterator _push(edge_impl &&__e) {
      if (__t == last) {
        size_type __n(last - first);
        iterator loc = new edge_impl[__n << 1 | 1];
        __s += loc - first;
        __t = loc;
        for (iterator __p{first}; __p != last; ++__p, ++__t) {
          *__t = *__p;
          if (__p->rev) __p->rev->rev = __t;
        }
        delete[] first;
        first = loc;
        last = __t + __n;
      }
      *__t = std::move(__e);
      if (__s->aux) ++__s;
      return __t++;
    }

    iterator begin() const { return first; }

    iterator end() const { return __t; }
  };

  /**
   * @brief The only member variable.
   */
  container_type graph;

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
      for (auto &&__e : __adj) add_edge(__e);
  }

  /**
   * @brief Construct a new flow graph object
   *
   * @param __x Rvalue reference to another object
   */
  flow_graph(flow_graph &&__x) : graph(std::move(__x.graph)) {}

  /**
   * @brief Assignment operator.
   *
   * @param __x Const reference to another object
   * @return Reference to this object.
   */
  flow_graph &operator=(const flow_graph &__x) {
    return operator=(std::move(flow_graph{__x}));
  }

  /**
   * @brief Assignment operator.
   *
   * @param __x Rvalue reference to another object
   * @return Reference to this object.
   */
  flow_graph &operator=(flow_graph &&__x) {
    graph = std::move(__x.graph);
    return *this;
  }

  /**
   * @return Number of nodes.
   */
  size_type size() const { return graph.size(); }

  /**
   * @param node Node
   * @return Referece to the adjacency list of the node.
   */
  reference operator[](size_type node) {
    assert(node < size());
    return graph[node];
  }

  /**
   * @param node Node
   * @return Const referece to the adjacency list of the node.
   */
  const_reference operator[](size_type node) const {
    assert(node < size());
    return graph[node];
  }

  class iterator : public container_type::iterator {
    using base = typename container_type::iterator;

   public:
    using reference = adjacency &;
    using pointer = adjacency *;

    iterator(base const &__i) : base(__i) {}

    pointer operator->() const { return base::operator->(); }

    reference operator*() const { return base::operator*(); }
  };

  class const_iterator : public container_type::const_iterator {
    using base = typename container_type::const_iterator;

   public:
    using const_reference = const adjacency &;
    using const_pointer = const adjacency *;

    const_iterator(base const &__i) : base(__i) {}

    const_pointer operator->() const { return base::operator->(); }

    const_reference operator*() const { return base::operator*(); }
  };

  auto begin() { return iterator{graph.begin()}; }
  auto begin() const { return const_iterator{graph.begin()}; }

  auto end() { return iterator{graph.end()}; }
  auto end() const { return const_iterator{graph.end()}; }

  /**
   * @brief Add a node to the graph.
   *
   * @return Index of the node.
   */
  size_type add_node() { return add_nodes(1).front(); }

  /**
   * @brief Add some nodes to the graph.
   *
   * @param __n Number of nodes added
   * @return List of indices of the nodes.
   */
  virtual std::vector<size_type> add_nodes(size_type __n) {
    std::vector<size_type> __nds(__n);
    std::iota(__nds.begin(), __nds.end(), graph.size());
    __n += graph.size();
    if (__n > graph.capacity()) {
      flow_graph __x(__n);
      for (auto &&adj : graph)
        for (auto &&__e : adj)
          if (!__e.aux) __x.add_edge(__e);
      graph = std::move(__x.graph);
    } else
      graph.resize(__n);
    return __nds;
  }

  /**
   * @brief Add a directed edge to the graph.
   *
   * @return Reference to the edge.
   */
  template <class... Args>
  typename std::enable_if<std::is_constructible<edge, Args...>::value,
                          edge &>::type
  add_edge(Args &&... __args) {
    edge_impl __e = edge(std::forward<Args>(__args)...);
    assert(__e.src < size());
    assert(__e.dst < size());
    edge_impl *__p = graph[__e.src]._push(std::move(__e));
    // Careful with a self loop.
    if (__e.src != __e.dst) __p->rev = graph[__e.dst]._push(__p->make_rev());
    return *__p;
  }

  /**
   * @brief Add a directed edge to the graph.
   *
   * @return Reference to the edge.
   */
  template <class Tp>
  typename std::enable_if<
      (std::tuple_size<typename std::decay<Tp>::type>::value >= 0),
      edge &>::type
  add_edge(Tp &&__t) {
    return _unpack_directed(std::forward<Tp>(__t));
  }

  /**
   * @brief Add an undirected edge to the graph. Its cost must be non-negative.
   *
   * @return Reference to the edge.
   */
  template <class... Args> edge &add_undirected_edge(Args &&... __args) {
    edge_impl __e = edge(std::forward<Args>(__args)...);
    assert(__e.src < size());
    assert(__e.dst < size());
    (__e.flow += __e.flow) += __e.cap;
    edge_impl *__p = graph[__e.src]._push(std::move(__e));
    // Careful with a self loop.
    if (__e.src != __e.dst) {
      edge_impl __r = __p->make_rev();
      __r.aux = false;
      __p->rev = graph[__e.dst]._push(std::move(__r));
    }
    return *__p;
  }

  /**
   * @brief Add an undirected edge to the graph. Its cost must be non-negative.
   *
   * @return Reference to the edge.
   */
  template <class Tp>
  typename std::enable_if<
      (std::tuple_size<typename std::decay<Tp>::type>::value >= 0),
      edge &>::type
  add_undirected_edge(Tp &&__t) {
    return _unpack_undirected(std::forward<Tp>(__t));
  }

 protected:
  // internal
  template <class Tp, size_t N = 0, class... Args>
  decltype(auto) _unpack_directed(Tp &&__t, Args &&... __args) {
    if constexpr (N == std::tuple_size<typename std::decay<Tp>::type>::value)
      return add_edge(std::forward<Args>(__args)...);
    else
      return _unpack_directed<Tp, N + 1>(std::forward<Tp>(__t),
                                         std::forward<Args>(__args)...,
                                         std::get<N>(__t));
  }

  // internal
  template <class Tp, size_t N = 0, class... Args>
  decltype(auto) _unpack_undirected(Tp &&__t, Args &&... __args) {
    if constexpr (N == std::tuple_size<typename std::decay<Tp>::type>::value)
      return add_undirected_edge(std::forward<Args>(__args)...);
    else
      return _unpack_undirected<Tp, N + 1>(std::forward<Tp>(__t),
                                           std::forward<Args>(__args)...,
                                           std::get<N>(__t));
  }

  template <class Os> friend Os &operator<<(Os &__os, flow_graph const &__g) {
    for (const auto &adj : __g)
      for (const auto &e : adj) __os << e << "\n";
    return __os;
  }
};

}  // namespace workspace
