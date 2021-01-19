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
 * @tparam Density_tag Whether the graph is dense.
 */
template <class Cap, class Cost = Cap, bool Density_tag = false>
class min_cost_flow : public flow_graph<Cap, Cost> {
  using base = flow_graph<Cap, Cost>;
  using edge_impl = typename base::edge_impl;
  using base::nil;

 public:
  using size_type = typename base::size_type;
  using base::size;

  /**
   * @brief Construct a new min_cost_flow object
   *
   * @param __n Number of vertices
   */
  min_cost_flow(size_type __n = 0)
      : base::flow_graph(__n), current(0), abs_sum(0), b(__n), p(__n) {}

  std::vector<size_type> add_nodes(size_type __n) override {
    auto __nds = base::add_nodes(__n);
    b.resize(size());
    p.resize(size());
    return __nds;
  }

  /**
   * @brief Add an edge with a unit capacity to the graph.
   *
   * @param src Source
   * @param dst Destination
   * @param cost Cost
   * @return Reference to the edge.
   */
  auto &add_edge(size_type src, size_type dst, const Cost &cost) {
    return add_edge(src, dst, 1, cost);
  }

  /**
   * @brief Add an edge to the graph.
   *
   * @param src Source
   * @param dst Destination
   * @param cap Capacity
   * @param cost Cost
   * @return Reference to the edge.
   */
  typename base::edge const &add_edge(size_type src, size_type dst,
                                      const Cap &cap, const Cost &cost) {
    edge_impl *__p = base::_add_edge(typename base::edge(src, dst, cap, cost));
    if (cost < static_cast<Cost>(0)) {
      __p->flow(cap);
      b[src] -= cap;
      b[dst] += cap;
      current += cap * cost;
      abs_sum -= cap * cost;
    } else
      abs_sum += cap * cost;
    return *__p;
  }

  /**
   * @brief Add an edge to the graph.
   *
   * @param src Source
   * @param dst Destination
   * @param lower Lower bound of flow
   * @param upper Upper bound of flow
   * @param cost Cost
   * @return Reference to the edge.
   */
  auto &add_edge(size_type src, size_type dst, const Cap &lower,
                 const Cap &upper, const Cost &cost) {
    assert(!(upper < lower));
    b[src] -= lower;
    b[dst] += lower;
    current += lower * cost;
    return add_edge(src, dst, upper - lower, cost);
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
   * @param node
   * @return Balance of the node
   */
  Cap balance(size_type node) { return b[node]; }

  /**
   * @return Cost of current flow.
   */
  Cost cost() const { return current; }

  /**
   * @brief Run Successive Shortest Path Algorithm.
   *
   * @return Whether a balanced flow exists.
   */
  bool flow() {
    for (bool aug = true; aug;) {
      aug = false;
      std::vector<edge_impl *> last(size());
      Dijkstra(last);
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
            for (edge_impl *e{last[dst]}; e; e = last[e->src]) {
              e->cap -= resid;
              e->rev->cap += resid;
            }
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
  Cost current, abs_sum;
  std::vector<Cap> b;
  std::vector<Cost> p;

  void Dijkstra(std::vector<edge_impl *> &last) {
    const Cost infty(abs_sum + 1);
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
        if (b[src] > static_cast<Cap>(0)) {
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

    p.swap(newp);
  }
};

template <class Cap, class Gain = Cap, bool Density_tag = false>
class max_gain_flow : public min_cost_flow<Cap, Gain, Density_tag> {
  using base = min_cost_flow<Cap, Gain, Density_tag>;
  using base::cost;

 public:
  using base::min_cost_flow;
  using size_type = typename base::size_type;

  /**
   * @brief Add an edge with a unit capacity to the graph.
   *
   * @param src Source
   * @param dst Destination
   * @param gain Gain
   * @return Reference to the edge.
   */
  auto &add_edge(size_type src, size_type dst, const Gain &gain) {
    return add_edge(src, dst, 1, gain);
  }

  /**
   * @brief Add an edge to the graph.
   *
   * @param src Source
   * @param dst Destination
   * @param cap Capacity
   * @param gain Gain
   * @return Reference to the edge.
   */
  auto &add_edge(size_type src, size_type dst, const Cap &cap,
                 const Gain &gain) {
    return base::add_edge(src, dst, cap, -gain);
  }

  /**
   * @brief Add an edge to the graph.
   *
   * @param src Source
   * @param dst Destination
   * @param lower Lower bound of flow
   * @param upper Upper bound of flow
   * @param gain Gain
   * @return Reference to the edge.
   */
  auto &add_edge(size_type src, size_type dst, const Cap &lower,
                 const Cap &upper, const Gain &gain) {
    return base::add_edge(src, dst, lower, upper, -gain);
  }

  /**
   * @return Gain of current flow.
   */
  Gain gain() const { return -base::current; }
};

}  // namespace workspace
