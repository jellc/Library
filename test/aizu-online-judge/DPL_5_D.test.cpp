#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/DPL_5_D"

#include <cstdio>

#include "src/combinatorics/binomial.hpp"

int main() {
  using namespace workspace;
  int n, k;
  scanf("%d%d", &n, &k);
  printf("%d\n", binomial<modint<1000000007>>(n + k - 1, n));
}
