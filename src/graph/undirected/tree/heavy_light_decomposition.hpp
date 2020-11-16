#pragma once

/*
 * @file heavy_light_decomposition.hpp
 * @brief Heavy Light Decomposition
 */

#include <cassert>
#include <numeric>
#include <vector>

class heavy_light_decomposition {
  std::vector<std::vector<size_t>> tree;
  std::vector<size_t> sorted, in, out, head;

  size_t sort_children(size_t node, size_t prev) {
    size_t sum = 0, max_size = 0;
    for (size_t &to : tree[node]) {
      if (to == prev) continue;
      size_t child_size = sort_children(to, node);
      sum += child_size;
      if (max_size < child_size) {
        max_size = child_size;
        std::swap(tree[node].front(), to);
      }
    }
    return sum + 1;
  }

  void traverse(size_t node, size_t prev) {
    in[node] = sorted.size();
    sorted.emplace_back(node);
    if (tree[node].front() != prev) {
      for (const size_t to : tree[node])
        if (to != prev) head[to] = node + size();
      head[tree[node].front()] = head[node] < size() ? head[node] : node;
      for (const size_t to : tree[node])
        if (to != prev) traverse(to, node);
    }
    out[node] = sorted.size();
  }

  bool made() const { return !sorted.empty(); }

 public:
  using interval = std::pair<size_t, size_t>;

  heavy_light_decomposition(size_t n = 0) : tree(n), in(n), out(n), head(n) {}

  /*
   * @fn size
   * @return The size of the tree.
   */
  size_t size() const { return tree.size(); }

  /*
   * @fn size
   * @param node The root of the subtree
   * @return The size of the subtree.
   */
  size_t size(size_t node) const {
    assert(made());
    return out[node] - in[node];
  }

  void add_edge(size_t u, size_t v) {
    assert(u < size());
    assert(v < size());
    tree[u].emplace_back(v);
    tree[v].emplace_back(u);
  }

  const decltype(tree) &graph() const { return tree; }

  /*
   * @fn make
   * @brief Run HLD with given root in linear time.
   * @param root The root node.
   */
  void make(size_t root) {
    sorted.clear();
    sort_children(root, root);
    traverse(root, root);
  }

  size_t prev_node(size_t node) const {
    assert(made());
    assert(in[node]);
    return sorted[in[node] - 1];
  }

  size_t next_node(size_t node) const {
    assert(made());
    assert(in[node] + 1 < size());
    return sorted[in[node] + 1];
  }

  size_t index(size_t node) const {
    assert(made());
    return in[node];
  }

  size_t node(size_t index) const {
    assert(made());
    return sorted[index];
  }

  /*
   * @fn root
   * @return The current root of the tree.
   */
  size_t root() const {
    assert(made());
    return sorted.front();
  }

  /*
   * @fn subtree
   * @param root The root of the subtree.
   * @return The interval representing the subtree.
   */
  interval subtree(size_t root) const {
    assert(made());
    return {in[root], out[root]};
  }

  size_t parent(size_t node) const {
    assert(made());
    return head[node] < size() ? prev_node(node) : head[node] - size();
  }

  size_t top(size_t node) const {
    assert(made());
    return head[node] < size() ? head[node] : node;
  }

  /*
   * @fn lca
   * @brief Get LCA in O(log(size)) time.
   * @param u 1st node
   * @param v 2nd node
   * @return Lowest Common Ancestor of the two.
   */
  size_t lca(size_t u, size_t v) {
    assert(made());
    if (in[v] < in[u]) std::swap(u, v);
    if (in[v] < out[u]) return u;
    while (in[u] < in[v]) v = parent(top(v));
    return v;
  }

  // O(log(n))
  std::pair<std::vector<interval>, std::vector<interval>> path_decomposition(
      size_t u, size_t v) const {
    assert(made());
    if (in[v] < in[u]) std::swap(u, v);
    std::vector<interval> left, right;
    size_t utop = top(u), vtop = top(v);
    while (utop != vtop) {
      left.emplace_back(in[vtop], in[v] + 1);
      vtop = top(v = parent(vtop));
      if (in[v] < in[u]) {
        std::swap(u, v);
        std::swap(utop, vtop);
        std::swap(left, right);
      }
    }
    left.emplace_back(in[u], in[v] + 1);
    return std::make_pair(left, right);
  }

  // O(log(n))
  std::vector<interval> path_decomposition(size_t node) const {
    assert(made());
    auto [left, right] = path_decomposition(root(), node);
    assert(left.size() == 1);
    right.insert(right.begin(), left.front());
    return right;
  }
};
