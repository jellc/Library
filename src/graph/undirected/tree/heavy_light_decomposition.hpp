#pragma once

/**
 * @file heavy_light_decomposition.hpp
 * @brief Heavy-Light Decomposition
 */

#include <cassert>
#include <numeric>
#include <vector>

class heavy_light_decomposition {
  constexpr static size_t __nil = -1;

  std::vector<std::vector<size_t>> __tree;
  std::vector<size_t> __sorted, __in, __out, __head, __depth;

  size_t sort_children(size_t node, size_t prev) {
    size_t sum = 1, max_size = 0;

    for (size_t &to : __tree[node]) {
      if (to == prev) continue;
      __depth[to] = __depth[node] + 1;
      size_t child_size = sort_children(to, node);
      sum += child_size;
      if (max_size < child_size) {
        max_size = child_size;
        std::swap(__tree[node].front(), to);
      }
    }

    return sum;
  }

  void traverse(size_t node, size_t prev) {
    __in[node] = __sorted.size();
    __sorted.emplace_back(node);

    if (!__tree[node].empty() && __tree[node].front() != prev) {
      for (const size_t to : __tree[node])
        if (to != prev) __head[to] = node + size();
      __head[__tree[node].front()] =
          __head[node] < size() ? __head[node] : node;
      for (const size_t to : __tree[node])
        if (to != prev) traverse(to, node);
    }

    __out[node] = __sorted.size();
  }

  bool made() const { return !__sorted.empty(); }

 public:
  using interval = std::pair<size_t, size_t>;

  heavy_light_decomposition() = default;

  heavy_light_decomposition(size_t __n) : __tree(__n) {}

  /**
   * @return The size of the __tree.
   */
  size_t size() const { return __tree.size(); }

  /**
   * @param node The root of the subtree
   * @return The size of the subtree.
   */
  size_t size(size_t node) const {
    assert(made());
    return __out[node] - __in[node];
  }

  void add_edge(size_t __u, size_t __v) {
    assert(__u < size());
    assert(__v < size());
    __tree[__u].emplace_back(__v);
    __tree[__v].emplace_back(__u);
  }

  const decltype(__tree) &tree() const { return __tree; }

  /**
   * @brief Run HLD with given root __in linear time.
   * @param root The root node.
   */
  void make(size_t __root) {
    __sorted.clear(), __in.resize(size()), __out.resize(size()),
        __head.resize(size()), __depth.resize(size());
    __head[__root] = __root + size(), __depth[__root] = 0;
    sort_children(__root, __nil);
    traverse(__root, __root);
  }

  size_t prev_node(size_t node) const {
    assert(made());
    return __in[node] ? __sorted[__in[node] - 1] : __nil;
  }

  size_t next_node(size_t node) const {
    assert(made());
    return __in[node] + 1 < size() ? __sorted[__in[node] + 1] : __nil;
  }

  size_t index(size_t node) const {
    assert(made());
    return __in[node];
  }

  size_t node(size_t __i) const {
    assert(made());
    return __sorted[__i];
  }

  /**
   * @return The current root of the __tree.
   */
  size_t root() const {
    assert(made());
    return __sorted.front();
  }

  /**
   * @param root The root of the subtree.
   * @return The interval representing the subtree.
   */
  interval subtree(size_t __v) const {
    assert(made());
    return {__in[__v], __out[__v]};
  }

  /**
   * @param __v
   * @return Return v if v is the root.
   */
  size_t parent(size_t __v) const {
    assert(made());
    return __head[__v] < size() ? prev_node(__v) : __head[__v] - size();
  }

  size_t top(size_t __v) const {
    assert(made());
    return __head[__v] < size() ? __head[__v] : __v;
  }

  /**
   * @brief Get LCA in O(log(size)) time.
   * @param __u 1st node
   * @param __v 2nd node
   * @return Lowest Common Ancestor of the two.
   */
  size_t lca(size_t __u, size_t __v) const {
    assert(made());
    if (__in[__v] < __in[__u]) std::swap(__u, __v);
    if (__in[__v] < __out[__u]) return __u;
    while (__in[__u] < __in[__v]) __v = parent(top(__v));
    return __v;
  }

  /**
   * @brief Ancestor.
   * @return k-th ancestor of v.
   */
  size_t ancestor(size_t __v, size_t __k) const {
    assert(made());
    while (__k) {
      assert(__in[__v]);
      auto __t = top(__v);
      auto __d = __in[__v] - __in[__t];
      if (__d < __k) {
        __k -= __d + 1;
        __v = __head[__t] - size();
      } else {
        __v = __sorted[__in[__v] - __k];
        __k = 0;
      }
    }
    return __v;
  }

  size_t depth(size_t __v) const { return __depth[__v]; }

  size_t distance(size_t __u, size_t __v) const {
    return __depth[__u] + __depth[__v] - __depth[lca(__u, __v)] * 2;
  }

  /**
   * @brief Split a path into O(log(size)) paths.
   * @return Pair of list of ascending paths. first.back() is the index of
   * lca(u, v).
   */
  auto split_path(size_t __u, size_t __v) const {
    assert(made());
    if (__in[__v] < __in[__u]) std::swap(__u, __v);
    std::vector<std::pair<size_t, size_t>> left, right;
    auto utop = top(__u), vtop = top(__v);
    while (utop != vtop) {
      left.emplace_back(__in[vtop], __in[__v] + 1);
      vtop = top(__v = parent(vtop));
      if (__in[__v] < __in[__u]) {
        std::swap(__u, __v);
        std::swap(utop, vtop);
        std::swap(left, right);
      }
    }
    left.emplace_back(__in[__u], __in[__v] + 1);
    return std::make_pair(left, right);
  }

  /**
   * @brief Split a path upto root() into O(log(size)) paths.
   * @return List of ascending paths. back() is the index of lca(root(), v).
   */
  auto split_path(size_t __v) const {
    assert(made());
    auto [left, right] = split_path(root(), __v);
    right.insert(right.begin(), left.begin(), left.end());
    return right;
  }
};
