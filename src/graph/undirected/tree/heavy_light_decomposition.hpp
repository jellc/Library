#pragma once
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

 public:
  using interval = std::pair<size_t, size_t>;

  heavy_light_decomposition(size_t n) : tree(n), in(n), out(n), head(n) {}

  size_t size() const { return tree.size(); }

  size_t size(size_t node) const { return out[node] - in[node]; }

  void add_edge(size_t u, size_t v) {
    assert(u < size());
    assert(v < size());
    tree[u].emplace_back(v);
    tree[v].emplace_back(u);
  }

  const decltype(tree) &graph() const { return tree; }

  // O(n)
  void make(size_t root) {
    sorted.clear();
    sort_children(root, root);
    traverse(root, root);
  }

  size_t prev_node(size_t node) const {
    assert(in[node]);
    return sorted[in[node] - 1];
  }

  size_t next_node(size_t node) const {
    assert(in[node] + 1 < size());
    return sorted[in[node] + 1];
  }

  size_t index(size_t node) const { return in[node]; }

  size_t node(size_t index) const { return sorted[index]; }

  size_t root() const { return sorted.front(); }

  interval subtree(size_t root) const { return {in[root], out[root]}; }

  size_t parent(size_t node) const {
    return head[node] < size() ? prev_node(node) : head[node] - size();
  }

  size_t top(size_t node) const {
    return head[node] < size() ? head[node] : node;
  }

  // O(log(n))
  size_t lca(size_t u, size_t v) {
    if (in[v] < in[u]) std::swap(u, v);
    if (in[v] < out[u]) return u;
    while (in[u] < in[v]) v = parent(top(v));
    return v;
  }

  // O(log(n))
  std::pair<std::vector<interval>, std::vector<interval>> path_decomposition(
      size_t u, size_t v) const {
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
    auto [left, right] = path_decomposition(root(), node);
    assert(left.size() == 1);
    right.insert(right.begin(), left.front());
    return right;
  }
};
