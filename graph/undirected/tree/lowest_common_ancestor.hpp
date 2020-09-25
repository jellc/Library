#pragma once
#include <cassert>
#include <vector>

class lowest_common_ancestor {
  std::vector<std::vector<size_t>> tree, table;
  std::vector<size_t> &sorted, index;

  void tour(const size_t node, const size_t prev) {
    index[node] = sorted.size();
    sorted.emplace_back(node);
    for (const size_t to : tree[node]) {
      if (to != prev) {
        tour(to, node);
        sorted.emplace_back(node);
      }
    }
  }

  void make_table() {
    const size_t len = sorted.size();
    for (size_t w = 2; w < len; w <<= 1) {
      std::vector<size_t> &crt(table.back()), nxt(crt);
      for (size_t i = 0, j = w >> 1; j != len; ++i, ++j)
        if (index[crt[j]] < index[crt[i]]) nxt[i] = crt[j];
      table.emplace_back(nxt);
    }
  }

 public:
  lowest_common_ancestor(const size_t n = 0)
      : tree(n), table(1), sorted(table.front()), index(n) {}

  size_t size() const { return tree.size(); }

  void add_edge(const size_t u, const size_t v) {
    assert(u < size());
    assert(v < size());
    tree[u].emplace_back(v);
    tree[v].emplace_back(u);
  }

  // O(n log(n))
  void make(const size_t root) {
    assert(root < size());
    tour(root, root);
    make_table();
  }

  // O(1)
  size_t query(size_t u, size_t v) const {
    assert(u < size());
    assert(v < size());
    if (u == v) return u;
    if ((v = index[v]) < (u = index[u])) std::swap(u, v);
    size_t h = std::__lg(v - u);
    return std::min(table[h][u], table[h][v - (1 << h)]);
  }
};  // class lowest_common_ancestor
