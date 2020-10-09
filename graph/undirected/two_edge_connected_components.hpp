#pragma once
#include <cassert>
#include <vector>

// instance: an undirected and not necessarily simple graph
class two_edge_connected_component {
  static constexpr size_t nil = -1;
  std::vector<size_t> stack, low, comp;
  std::vector<std::vector<size_t>> graph, tree, memb;

  void make(size_t now, size_t pre) {
    size_t ord = low[now] = stack.size();
    stack.emplace_back(now);
    std::vector<size_t> brid;
    for (size_t to : graph[now]) {
      if (to == pre) {
        pre = nil;
        continue;
      }
      if (low[to] == nil) make(to, now);
      if (low[to] > ord) {
        brid.emplace_back(to);
        graph[to].emplace_back(now);
      } else if (low[now] > low[to])
        low[now] = low[to];
    }
    brid.swap(graph[now]);
    if (ord == low[now]) {
      auto pos = stack.end();
      tree.resize(tree.size() + 1);
      auto &adjc = tree.back();
      do {
        --pos;
        comp[*pos] = memb.size();
        for (size_t u : graph[*pos]) adjc.emplace_back(comp[u]);
      } while (*pos != now);
      memb.emplace_back(pos, stack.end());
      stack.erase(pos, stack.end());
    }
  }

 public:
  two_edge_connected_component(size_t n) : comp(n), graph(n) {
    stack.reserve(n), tree.reserve(n), memb.reserve(n);
  }

  void add_edge(size_t u, size_t v) {
    assert(u < size()), assert(v < size());
    graph[u].emplace_back(v), graph[v].emplace_back(u);
  }

  void make() {
    low.assign(size(), nil);
    for (size_t v = 0; v != size(); ++v)
      if (low[v] == nil) make(v, nil);
  }

  size_t size() const { return graph.size(); }

  size_t size(size_t i) {
    assert(i < count());
    return memb[i].size();
  }

  size_t count() const { return memb.size(); }

  size_t operator[](size_t v) const {
    assert(v < size());
    return comp[v];
  }

  const std::vector<size_t> &bridge(size_t v) const {
    assert(v < size());
    return graph[v];
  }

  const std::vector<size_t> &component(size_t i) const {
    assert(i < count());
    return memb[i];
  }

  const std::vector<std::vector<size_t>> &bridge_tree() const { return tree; }
};  // class two_edge_connected_component
