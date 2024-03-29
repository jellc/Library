#pragma once

/**
 * @file min_cost_flow.hpp
 * @brief Minimum Cost Flow
 */

#include <algorithm>
#include <queue>

#include "base.hpp"
#include "lib/limits"

namespace workspace {

/**
 * @brief Capacity Scaling Algorithm.
 *
 * @tparam _Cap Capacity type
 * @tparam _Cost Cost type
 */
template <class _Cap, class _Cost = _Cap>
class min_cost_flow : public flow_graph<_Cap, _Cost> {
  using _Base = flow_graph<_Cap, _Cost>;
  using typename _Base::edge_impl;

 public:
  using _Base::_Base;
  using _Base::add_edge;
  using typename _Base::edge;
  using typename _Base::size_type;

  /**
   * @brief Add a directed edge to the graph.
   *
   * @param __s Source
   * @param __d Destination
   * @param __l Lower bound of flow
   * @param __u Upper bound of flow
   * @param __c _Cost
   * @return Reference to the edge.
   */
  edge &add_edge(size_type __s, size_type __d, _Cap __l, _Cap __u, _Cost __c) {
    assert(!(__u < __l));
    b.resize(_Base::size());
    b[__s] -= __l, b[__d] += __l;
    auto &__e = _Base::add_edge(__s, __d, __u - __l, __c);
    __e.flow = __l;
    return __e;
  }

  /**
   * @brief Add an undirected edge to the graph.
   *
   * @return Reference to the edge.
   */
  template <class... _Args> edge &add_undirected_edge(_Args &&...__args) {
    auto &__e = static_cast<edge_impl &>(
        _Base::add_undirected_edge(std::forward<_Args>(__args)...));
    assert(!(__e.cost < 0));
    __e.rev->cost = __e.cost;
    return __e;
  }

  /**
   * @brief Increase the balance of a node.
   *
   * @param node
   * @param __f Default: 1
   */
  void supply(size_type node, _Cap __f = 1) {
    assert(node < _Base::size());
    b.resize(_Base::size());
    b[node] += __f;
  }

  /**
   * @brief Decrease the balance of a node.
   *
   * @param node
   * @param __f Default: 1
   */
  void demand(size_type node, _Cap __f = 1) {
    assert(node < _Base::size());
    b.resize(_Base::size());
    b[node] -= __f;
  }

  /**
   * @return Balance.
   */
  const auto &balance() const { return b; }

  /**
   * @param node Node
   * @return Balance of the node.
   */
  _Cap balance(size_type node) const { return b[node]; }

  /**
   * @return Potential. The dual solution.
   */
  const auto &potential() const { return p; }

  /**
   * @param node Node
   * @return Potential of the node.
   */
  _Cost potential(size_type node) const { return p[node]; }

  /**
   * @return _Cost of current flow.
   */
  _Cost cost() const { return current; }

  /**
   * @brief Run Capacity Scaling Algorithm.
   *
   * @return Whether a balanced flow exists.
   */
  bool run() {
    b.resize(_Base::size());
    p.resize(b.size());

    _Cap delta = 0;
    for (auto &&__adj : _Base::graph)
      for (auto &&__e : __adj) delta = std::max(delta, __e.capacity);

    if (delta == static_cast<_Cap>(0))
      if (std::any_of(b.begin(), b.end(),
                      [](_Cap __x) { return __x != static_cast<_Cap>(0); }))
        return false;

    parent.resize(b.size());

    while (static_cast<_Cap>(0) < delta) {
      delta /= 2;

      for (auto &&__adj : _Base::graph)
        for (auto &&__e : __adj)
          if (delta < __e.capacity && __e.cost < p[__e.head] - p[__e.tail]) {
            b[__e.tail] -= __e.capacity;
            b[__e.head] += __e.capacity;
            __e.push(__e.capacity);
          }

      sources.clear();
      sinks.clear();
      for (size_type __v = 0; __v != b.size(); ++__v)
        if (delta < b[__v])
          sources.emplace_back(__v);
        else if (b[__v] < -delta)
          sinks.emplace_back(__v);

      while (dual(delta)) {
        primal(delta);
        sources.erase(
            std::remove_if(sources.begin(), sources.end(),
                           [&](auto __v) { return !(delta < b[__v]); }),
            sources.end());
        sinks.erase(
            std::remove_if(sinks.begin(), sinks.end(),
                           [&](auto __v) { return !(b[__v] < -delta); }),
            sinks.end());
      }
    }

    current = 0;
    for (auto &&__adj : _Base::graph)
      for (auto &&__e : __adj)
        if (!__e.aux) current += __e.cost * __e.flow;

    return sources.empty() && sinks.empty();
  }

 protected:
  // _Cost of flow.
  _Cost current{};

  // Balance
  std::vector<_Cap> b;

  // The dual solution.
  std::vector<_Cost> p;

  std::vector<edge_impl *> parent;
  std::vector<size_type> sources, sinks;

  // Augment along the dual solution.
  void primal(_Cap delta) {
    for (auto __t : sinks)
      if (parent[__t]) {
        auto __f = -b[__t];
        auto __s = __t;
        while (parent[__s])
          __f = std::min(__f, parent[__s]->capacity), __s = parent[__s]->tail;
        if (delta < b[__s]) {
          __f = std::min(__f, b[__s]);
          b[__s] -= __f;
          b[__t] += __f;
          for (auto *__p = parent[__t]; __p; __p = parent[__p->tail]) {
            __p->push(__f);
            parent[__p->head] = nullptr;
          }
        }
      }
  }

  // Improve the dual solution.
  bool dual(_Cap delta) {
    std::fill(parent.begin(), parent.end(), nullptr);
    size_type reachable = 0;

    struct state {
      size_type __v;
      _Cost __d;
      state(size_type __v, _Cost __d) : __v(__v), __d(__d) {}
      bool operator<(const state &__x) const { return __x.__d < __d; }
    };

    std::priority_queue<state> __q;
    decltype(p) __nx(p.size(), numeric_limits<_Cost>::max());
    _Cost __ld = 0;

    for (auto __v : sources) {
      __nx[__v] = p[__v];
      __q.emplace(__v, 0);
    }

    while (!__q.empty()) {
      auto [__v, __d] = __q.top();
      __q.pop();
      if (__d + p[__v] != __nx[__v]) continue;
      __ld = __d;
      if (b[__v] < -delta && ++reachable == sinks.size()) break;
      for (auto &__e : _Base::graph[__v])
        if (delta < __e.capacity &&
            (__d = __nx[__v] + __e.cost) < __nx[__e.head]) {
          __q.emplace(__e.head, (__nx[__e.head] = __d) - p[__e.head]);
          parent[__e.head] = &__e;
        }
    }

    for (size_type __v = 0; __v != p.size(); ++__v)
      p[__v] = std::min(__nx[__v], p[__v] += __ld);

    return reachable;
  }
};

}  // namespace workspace
