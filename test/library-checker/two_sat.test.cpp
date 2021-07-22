#define PROBLEM "https://judge.yosupo.jp/problem/two_sat"

#include "src/combinatorics/two_sat.hpp"

#include <cstdio>

int main() {
  char s[4];
  int n, m;
  scanf("%s%s%d%d", s, s, &n, &m);
  workspace::two_sat sol(n);
  while (m--) {
    int a, b;
    scanf("%d%d%s", &a, &b, s);
    if (a < 0)
      a = ~(-a - 1);
    else
      --a;
    if (b < 0)
      b = ~(-b - 1);
    else
      --b;
    sol.add_clause(a, b);
  }
  if (sol.run()) {
    printf("s SATISFIABLE\nv ");
    for (int i = 0; i < n; ++i) printf("%d ", sol[i] ? i + 1 : -(i + 1));
    printf("0\n");
  } else {
    printf("s UNSATISFIABLE\n");
  }
}
