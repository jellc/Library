#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_6_A"

#include <cstdio>

#include "src/graph/directed/flow/Dinic.hpp"

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  workspace::Dinic<int> dinic(n);
  while (m--) {
    int u, v, c;
    scanf("%d%d%d", &u, &v, &c);
    dinic.add_edge(u, v, c);
  }
  printf("%d\n", dinic.run(0, n - 1));
}
