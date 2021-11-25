#pragma once

/**
 * @file base.hpp
 * @brief Flow Graph
 */

#include <cassert>
#include <numeric>
#include <tuple>
#include <vector>

namespace workspace {

template <class _Cap, class _Cost = void> class flow_graph {
 protected:
  class adjacency_impl;

 public:
  using container_type = std::vector<adjacency_impl>;
  using size_type = typename container_type::size_type;

  class unweighted_edge {
   public:
    size_type tail;  // Source
    size_type head;  // Destination
    _Cap capacity;   // Capacity
    _Cap flow;       // Flow

    unweighted_edge(size_type __s, size_type __d, const _Cap &__u = 1)
        : tail(__s), head(__d), capacity(__u), flow(0) {
      assert(!(capacity < static_cast<_Cap>(0))),
          assert(!(flow < static_cast<_Cap>(0)));
    }

    // tail, head, capacity, flow
    template <class _Os>
    friend _Os &operator<<(_Os &__os, const unweighted_edge &__e) {
      return __os << __e.tail << ' ' << __e.head << ' ' << __e.capacity << ' '
                  << __e.flow;
    }

   protected:
    unweighted_edge() = default;

    unweighted_edge(size_type __s, size_type __d, const _Cap &__u,
                    const _Cap &__f)
        : tail(__s), head(__d), capacity(__u), flow(__f) {}

    unweighted_edge make_rev() const { return {head, tail, flow, capacity}; }
  };

  class weighted_edge : public unweighted_edge {
   public:
    _Cost cost;  // _Cost

    weighted_edge(const unweighted_edge &__e, const _Cost &__c = 0)
        : unweighted_edge(__e), cost(__c) {}

    weighted_edge(size_type __s, size_type __d, const _Cap &__u = 1,
                  const _Cost &__c = 0)
        : unweighted_edge(__s, __d, __u), cost(__c) {}

    // tail, head, capacity, flow, cost
    template <class _Os>
    friend _Os &operator<<(_Os &__os, const weighted_edge &__e) {
      return __os << static_cast<unweighted_edge>(__e) << ' ' << __e.cost;
    }

   protected:
    weighted_edge() = default;

    weighted_edge make_rev() const {
      return {unweighted_edge::make_rev(), -cost};
    }
  };

  using edge = std::conditional_t<std::is_void<_Cost>::value, unweighted_edge,
                                  weighted_edge>;

 protected:
  struct edge_impl : edge {
    bool aux = false;
    edge_impl *rev = nullptr;

    edge_impl() = default;

    edge_impl(const edge &__e) : edge(__e) {}
    edge_impl(edge &&__e) : edge(__e) {}

    void push(_Cap __f) {
      edge::capacity -= __f;
      edge::flow += __f;
      if (rev) {
        rev->capacity += __f;
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

      bool operator!=(const iterator &__x) const { return __p != __x.__p; }

      bool operator==(const iterator &__x) const { return __p == __x.__p; }

      iterator &operator++() {
        do ++__p;
        while (__p->rev && __p->aux);
        return *this;
      }

      iterator operator++(int) {
        auto __cp = *this;
        do ++__p;
        while (__p->rev && __p->aux);
        return __cp;
      }

      iterator &operator--() {
        do --__p;
        while (__p->aux);
        return *this;
      }

      iterator operator--(int) {
        auto __cp = *this;
        do --__p;
        while (__p->aux);
        return __cp;
      }

      pointer operator->() const { return __p; }

      reference operator*() const { return *__p; }
    };

    class const_iterator {
      const edge_impl *__p;

     public:
      const_iterator(const edge_impl *__p = nullptr) : __p(__p) {}

      bool operator!=(const const_iterator &__x) const {
        return __p != __x.__p;
      }

      bool operator==(const const_iterator &__x) const {
        return __p == __x.__p;
      }

      const_iterator &operator++() {
        do ++__p;
        while (__p->rev && __p->aux);
        return *this;
      }

      const_iterator operator++(int) {
        auto __cp = *this;
        do ++__p;
        while (__p->rev && __p->aux);
        return __cp;
      }

      const_iterator &operator--() {
        do --__p;
        while (__p->aux);
        return *this;
      }

      const_iterator operator--(int) {
        auto __cp = *this;
        do --__p;
        while (__p->aux);
        return __cp;
      }

      const_pointer operator->() const { return __p; }

      const_reference operator*() const { return *__p; }
    };

    adjacency()
        : first(new edge_impl[2]), last(first + 1), __s(first), __t(first) {}

    ~adjacency() { delete[] first; }

    const_reference operator[](size_type __i) const {
      assert(__i < size());
      return *(first + __i);
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
      delete[] first;
      first = __x.first, __x.first = nullptr;
      last = __x.last, __s = __x.__s, __t = __x.__t;
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
    using _Base = adjacency;
    using _Base::__s;
    using _Base::__t;
    using _Base::first;
    using _Base::last;

    using iterator = edge_impl *;

    iterator push(const edge_impl &__e) {
      realloc();
      *__t = __e;
      if (__s->aux) ++__s;
      return __t++;
    }

    iterator push(edge_impl &&__e) {
      realloc();
      *__t = std::move(__e);
      if (__s->aux) ++__s;
      return __t++;
    }

    iterator begin() const { return first; }

    iterator end() const { return __t; }

    void realloc() {
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
    }
  };

  // Only member variable.
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
   * @return Whether the graph is empty.
   */
  bool empty() const { return graph.empty(); }

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
    using _Base = typename container_type::iterator;

   public:
    using reference = adjacency &;
    using pointer = adjacency *;

    iterator(const _Base &__i) : _Base(__i) {}

    pointer operator->() const { return _Base::operator->(); }

    reference operator*() const { return _Base::operator*(); }
  };

  class const_iterator : public container_type::const_iterator {
    using _Base = typename container_type::const_iterator;

   public:
    using const_reference = const adjacency &;
    using const_pointer = const adjacency *;

    const_iterator(const _Base &__i) : _Base(__i) {}

    const_pointer operator->() const { return _Base::operator->(); }

    const_reference operator*() const { return _Base::operator*(); }
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
  std::vector<size_type> add_nodes(size_type __n) noexcept {
    std::vector<size_type> __nodes(__n);
    std::iota(__nodes.begin(), __nodes.end(), graph.size());
    graph.resize(graph.size() + __n);
    return __nodes;
  }

  /**
   * @brief Add a directed edge to the graph.
   *
   * @return Reference to the edge.
   */
  template <class... _Args>
  typename std::enable_if<std::is_constructible<edge, _Args...>::value,
                          edge &>::type
  add_edge(_Args &&...__args) {
    edge_impl __e = edge(std::forward<_Args>(__args)...);
    assert(__e.tail < size()), assert(__e.head < size());
    edge_impl *__p = graph[__e.tail].push(std::move(__e));
    // Careful with a self loop.
    if (__p->tail != __p->head)
      __p->rev = graph[__p->head].push(__p->make_rev());
    return *__p;
  }

  /**
   * @brief Add an undirected edge to the graph. Its cost must be non-negative.
   *
   * @return Reference to the edge.
   */
  template <class... _Args> edge &add_undirected_edge(_Args &&...__args) {
    edge_impl __e = edge(std::forward<_Args>(__args)...);
    assert(__e.tail < size()), assert(__e.head < size());
    __e.flow += __e.capacity;
    edge_impl *__p = graph[__e.tail].push(std::move(__e));
    // Careful with a self loop.
    if (__p->tail != __p->head) {
      edge_impl __r = __p->make_rev();
      __r.aux = false;
      __p->rev = graph[__p->head].push(std::move(__r));
    }
    return *__p;
  }

  template <class _Os>
  friend _Os &operator<<(_Os &__os, flow_graph const &__g) {
    for (const auto &__adj : __g)
      for (const auto &__e : __adj) __os << __e << "\n";
    return __os;
  }
};

}  // namespace workspace
