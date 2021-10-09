#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_4_A"

#include <iostream>

#include "src/graph/digraph.h"

int main() {
  size_t n, m, u, v;
  std::cin >> n >> m;

  struct tag {
    bool valid{};
  };
  workspace::digraph<tag> g(n);

  while (m--) {
    std::cin >> u >> v;
    g.add_edge(u, v, true);
  }

  u = g.add_node();
  for (v = 0; v < n; ++v) g.add_edge(u, v, true);

  std::vector<decltype(g)::edge_type> parent(n);
  std::vector path{u};

  for (auto &&e : g.dfs(u)) {
    while (path.back() != e.tail) {
      parent[path.back()].valid = false;
      path.pop_back();
    }

    path.emplace_back(e.head);
    parent[e.head] = e;

    for (auto &&f : g[e.head])
      if (parent[f.head].valid) {
        std::cout << "1\n";
        return 0;
      }
  }

  std::cout << "0\n";
}
