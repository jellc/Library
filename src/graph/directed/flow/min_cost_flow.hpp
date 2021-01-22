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

namespace workspace {

/**
 * @brief Successive Shortest Path Algorithm.
 *
 * @tparam Cap Capacity type
 * @tparam Cost Cost type
 * @tparam Density_tag Whether the graph is dense
 */
template <class Cap, class Cost = Cap, bool Density_tag = false>
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
  min_cost_flow(size_type __n = 0)
      : base::flow_graph(__n), current(0), b(__n), p(__n) {}

  std::vector<size_type> add_nodes(size_type __n) override {
    auto __nds = base::add_nodes(__n);
    b.resize(size());
    p.resize(size());
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
    current += __l * __c;
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
   * @return Balance of the graph.
   */
  const auto &balance() const { return b; }

  /**
   * @param node Node
   * @return Balance of the node.
   */
  Cap balance(size_type node) const { return b[node]; }

  /**
   * @return Potential of the graph.
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
   * @brief Run Successive Shortest Path Algorithm.
   *
   * @return Whether a balanced flow exists.
   */
  bool run() {
    // Saturate negative edges.
    for (auto &&__adj : base::graph)
      for (auto &&__e : __adj)
        if (__e.cost < static_cast<Cost>(0) && static_cast<Cap>(0) < __e.cap) {
          b[__e.src] -= __e.cap;
          b[__e.dst] += __e.cap;
          current += __e.cost * __e.cap;
          __e.aug(__e.cap);
        }

    for (bool aug = true; aug;) {
      aug = false;
      std::vector<edge_impl *> last(size());
      dual(last);
      std::vector<bool> shut(size());
      for (size_type dst{}; dst != size(); ++dst) {
        if (b[dst] < static_cast<Cap>(0) && last[dst]) {
          Cap resid{-b[dst]};
          size_type src{dst}, block{nil};
          while (last[src] && !shut[src]) {
            if (!(resid < last[src]->cap)) resid = last[block = src]->cap;
            src = last[src]->src;
          }
          if (shut[src])
            block = src;
          else {
            if (!(resid < b[src])) resid = b[block = src];
            for (edge_impl *e{last[dst]}; e; e = last[e->src]) e->aug(resid);
            b[src] -= resid;
            b[dst] += resid;
            current += p[dst] * resid;
            aug = true;
          }
          if (block != nil)
            for (size_type node{dst};; node = last[node]->src) {
              shut[node] = true;
              if (node == block) break;
            }
        }
      }
    }

    return std::none_of(begin(b), end(b), [](const Cap &s) {
      return s < static_cast<Cap>(0) || static_cast<Cap>(0) < s;
    });
  }

 protected:
  constexpr static size_type nil = -1;

  Cost current;
  std::vector<Cap> b;
  std::vector<Cost> p;

  // internal
  void dual(std::vector<edge_impl *> &last) {
    constexpr Cost infty = std::numeric_limits<Cost>::max();
    std::vector<Cost> newp(size(), infty);

    if constexpr (Density_tag) {  // O(V^2)
      std::vector<bool> used(size());

      for (size_type src{}; src != size(); ++src)
        if (static_cast<Cap>(0) < b[src]) {
          used[src] = true;
          newp[src] = 0;

          for (auto &e : base::graph[src])
            if (static_cast<Cap>(0) < e.cap && e.cost < newp[e.dst])
              newp[e.dst] = e.cost, last[e.dst] = &e;
        }

      for (;;) {
        size_type src{nil};
        Cost sp{infty};

        for (size_type node{}; node != size(); ++node) {
          if (used[node] || newp[node] == infty) continue;
          if (Cost __d = newp[node] - p[node]; __d < sp) sp = __d, src = node;
        }

        if (src == nil) break;
        used[src] = true;

        for (auto &e : base::graph[src])
          if (Cost __d = newp[src] + e.cost;
              static_cast<Cap>(0) < e.cap && __d < newp[e.dst]) {
            newp[e.dst] = __d;
            last[e.dst] = &e;
          }
      }
    }

    else {  // O((V + E)logV)
      struct sp_node {
        size_type id;
        Cost __d;
        sp_node(size_type id, Cost __d) : id(id), __d(__d) {}
        bool operator<(const sp_node &rhs) const { return rhs.__d < __d; }
      };

      std::priority_queue<sp_node> __q;
      for (size_type src{}; src != size(); ++src)
        if (static_cast<Cap>(0) < b[src]) {
          newp[src] = 0;
          for (auto &e : base::graph[src])
            if (static_cast<Cap>(0) < e.cap && e.cost < newp[e.dst]) {
              __q.emplace(e.dst, (newp[e.dst] = e.cost) - p[e.dst]);
              last[e.dst] = &e;
            }
        }

      while (!__q.empty()) {
        auto [src, __d] = __q.top();
        __q.pop();
        if (__d + p[src] != newp[src]) continue;
        for (auto &e : base::graph[src])
          if (auto __d = newp[src] + e.cost;
              static_cast<Cap>(0) < e.cap && __d < newp[e.dst]) {
            __q.emplace(e.dst, (newp[e.dst] = __d) - p[e.dst]);
            last[e.dst] = &e;
          }
      }
    }

    p = std::move(newp);
  }
};

/**
 * @brief Successive Shortest Path Algorithm.
 *
 * @tparam Cap Capacity type
 * @tparam Gain Gain type
 * @tparam Density_tag Whether the graph is dense
 */
template <class Cap, class Gain = Cap, bool Density_tag = false>
class max_gain_flow : public min_cost_flow<Cap, Gain, Density_tag> {
  using base = min_cost_flow<Cap, Gain, Density_tag>;
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
    return add_edge(std::tuple{std::forward<Args>(__args)...});
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
