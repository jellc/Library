#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_mod"

#include "src/number_theory/sqrt_mod.hpp"

int main() {
  int t, y, p;
  for (scanf("%d", &t); t; --t) {
    scanf("%d%d", &y, &p);
    printf("%d\n", workspace::sqrt_mod(y, p));
  }
}
