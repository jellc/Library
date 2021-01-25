#pragma once

/**
 * @file min_cost_flow.hpp
 * @brief Minimum Cost Flow
 * @date 2021-01-15
 *
 *
 */

#include <algorithm>
#include <optional>
#include <queue>

#include "base.hpp"
#include "lib/limits"

namespace workspace {

/**
 * @brief Capacity Scaling Algorithm.
 *
 * @tparam Cap Capacity type
 * @tparam Cost Cost type
 */
template <class Cap, class Cost = Cap>
class min_cost_flow : public flow_graph<Cap, Cost> {
  using base = flow_graph<Cap, Cost>;
  using edge_impl = typename base::edge_impl;

 public:
  using edge = typename base::edge;
  using size_type = typename base::size_type;
  using base::size;

  /**
   * @brief Construct a new min_cost_flow object
   *
   * @param __n Number of vertices
   */
  min_cost_flow(size_type __n = 0) : base::flow_graph(__n), b(__n) {}

  std::vector<size_type> add_nodes(size_type __n) override {
    auto __nds = base::add_nodes(__n);
    b.resize(size());
    return __nds;
  }

  using base::add_edge;

  /**
   * @brief Add a directed edge to the graph.
   *
   * @param __s Source
   * @param __d Destination
   * @param __l Lower bound of flow
   * @param __u Upper bound of flow
   * @param __c Cost
   * @return Reference to the edge.
   */
  edge &add_edge(size_type __s, size_type __d, const Cap &__l, const Cap &__u,
                 const Cost &__c) {
    assert(!(__u < __l));
    b[__s] -= __l;
    b[__d] += __l;
    auto &__e = base::add_edge(__s, __d, __u - __l, __c);
    __e.flow = __l;
    return __e;
  }

  /**
   * @brief Add an undirected edge to the graph.
   *
   * @return Reference to the edge.
   */
  template <class... Args> edge &add_undirected_edge(Args &&... __args) {
    auto &__e = static_cast<edge_impl &>(
        base::add_undirected_edge(std::forward<Args>(__args)...));
    assert(!(__e.cost < 0));
    __e.rev->cost = __e.cost;
    return __e;
  }

  /**
   * @brief Increase the balance of a node.
   *
   * @param node
   * @param vol Default: 1
   */
  void supply(size_type node, const Cap &vol = 1) {
    assert(node < size());
    b[node] += vol;
  }

  /**
   * @brief Decrease the balance of a node.
   *
   * @param node
   * @param vol Default: 1
   */
  void demand(size_type node, const Cap &vol = 1) {
    assert(node < size());
    b[node] -= vol;
  }

  /**
   * @return Balance.
   */
  const auto &balance() const { return b; }

  /**
   * @param node Node
   * @return Balance of the node.
   */
  Cap balance(size_type node) const { return b[node]; }

  /**
   * @return Potential. The dual solution.
   */
  const auto &potential() const { return p; }

  /**
   * @param node Node
   * @return Potential of the node.
   */
  Cost potential(size_type node) const { return p[node]; }

  /**
   * @return Cost of current flow.
   */
  Cost cost() const { return current; }

  /**
   * @brief Run Capacity Scaling Algorithm.
   *
   * @return Whether a balanced flow exists.
   */
  bool run() {
    p.resize(b.size());

    Cap delta = 0;
    for (auto &&__adj : base::graph)
      for (auto &&__e : __adj) delta = std::max(delta, __e.cap);
    if (delta == static_cast<Cap>(0))
      return std::none_of(b.begin(), b.end(),
                          [](Cap __x) { return __x != static_cast<Cap>(0); });

    parent.resize(b.size());

    while (static_cast<Cap>(0) < delta) {
      delta /= 2;

      for (auto &&__adj : base::graph)
        for (auto &&__e : __adj)
          if (delta < __e.cap && __e.cost < p[__e.dst] - p[__e.src]) {
            b[__e.src] -= __e.cap;
            b[__e.dst] += __e.cap;
            __e.push(__e.cap);
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
    for (auto &&adj : base::graph)
      for (auto &&__e : adj)
        if (!__e.aux) current += __e.cost * __e.flow;

    return sources.empty() && sinks.empty();
  }

 protected:
  // Cost of flow.
  Cost current{};

  // Balance
  std::vector<Cap> b;

  // The dual solution.
  std::vector<Cost> p;

  std::vector<edge_impl *> parent;
  std::vector<size_type> sources, sinks;

  // Augment along the dual solution.
  void primal(Cap delta) {
    for (auto __t : sinks)
      if (parent[__t]) {
        auto __f = -b[__t];
        auto __s = __t;
        while (parent[__s])
          __f = std::min(__f, parent[__s]->cap), __s = parent[__s]->src;
        if (delta < b[__s]) {
          __f = std::min(__f, b[__s]);
          b[__s] -= __f;
          b[__t] += __f;
          for (auto *__p = parent[__t]; __p; __p = parent[__p->src]) {
            __p->push(__f);
            parent[__p->dst] = nullptr;
          }
        }
      }
  }

  // Improve the dual solution.
  bool dual(Cap delta) {
    std::fill(parent.begin(), parent.end(), nullptr);
    size_type reachable = 0;

    struct state {
      size_type __v;
      Cost __d;
      state(size_type __v, Cost __d) : __v(__v), __d(__d) {}
      bool operator<(const state &__x) const { return __x.__d < __d; }
    };

    std::priority_queue<state> __q;
    decltype(p) __nx(p.size(), std::numeric_limits<Cost>::max());
    Cost __ld = 0;

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
      for (auto &__e : base::graph[__v])
        if (delta < __e.cap && (__d = __nx[__v] + __e.cost) < __nx[__e.dst]) {
          __q.emplace(__e.dst, (__nx[__e.dst] = __d) - p[__e.dst]);
          parent[__e.dst] = &__e;
        }
    }

    for (size_type __v = 0; __v != p.size(); ++__v)
      p[__v] = std::min(__nx[__v], p[__v] += __ld);

    return reachable;
  }

};  // namespace workspace

/**
 * @brief Capacity Scaling Algorithm.
 *
 * @tparam Cap Capacity type
 * @tparam Gain Gain type
 */
template <class Cap, class Gain = Cap>
class max_gain_flow : public min_cost_flow<Cap, Gain> {
  using base = min_cost_flow<Cap, Gain>;
  using base::cost;

 public:
  using base::min_cost_flow;
  using edge = typename base::edge;

  /**
   * @brief Add a directed edge to the graph. The default capacity is 1.
   *
   * @return Reference to the edge.
   */
  template <class... Args> decltype(auto) add_edge(Args &&... __args) {
    return add_edge(std::tuple<Args...>{std::forward<Args>(__args)...});
  }

  /**
   * @brief Add a directed edge to the graph. The default capacity is 1.
   *
   * @return Reference to the edge.
   */
  template <class Tp>
  typename std::enable_if<
      (std::tuple_size<typename std::decay<Tp>::type>::value >= 0),
      const edge &>::type
  add_edge(Tp __t) {
    std::get<std::tuple_size<decltype(__t)>::value - 1>(__t) *=
        -1;  // Flip the sign of cost.
    return base::add_edge(std::move(__t));
  }

  /**
   * @return Gain of current flow.
   */
  Gain gain() const { return -cost(); }
};

}  // namespace workspace
