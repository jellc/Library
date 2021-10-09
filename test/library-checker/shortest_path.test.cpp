#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path"

#include <iostream>

#include "src/graph/digraph.h"

int main() {
  size_t n, m, s, t, a, b, c;
  std::cin >> n >> m >> s >> t;

  workspace::weighted_digraph<long long> g(n);
  while (m--) {
    std::cin >> a >> b >> c;
    g.add_edge(a, b, c);
  }

  auto edges = g.dijkstra(s);
  decltype(edges) path;

  for (auto i = edges.rbegin(); i != edges.rend(); ++i)
    if (i->head == t) t = i->tail, path.emplace_back(*i);

  if (s != t) {
    std::cout << "-1\n";
    return 0;
  }

  std::cout << path.front().weight << " " << path.size() << "\n";

  for (auto i = path.rbegin(); i != path.rend(); ++i)
    std::cout << i->tail << " " << i->head << "\n";
}
