#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/5/DPL_5_D"
#include <cstdio>

#include "combinatorics/binomial.hpp"

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  printf("%d\n", binomial<modint<1000000007>>()(n + k - 1, n));
}
