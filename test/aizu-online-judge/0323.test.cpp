#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/0323"
#define ERROR 1e-3

#include <cmath>
#include <cstdio>

#include "src/opt/binary_search.hpp"

int main() {
  int n;
  double x[1 << 17], r[1 << 17];

  scanf("%d", &n);
  for (auto i = 0; i < n; ++i) scanf("%lf%lf", x + i, r + i);

  auto isc = [&](const double d) -> bool {
    double lft = -1e6, rgt = 2e6;
    for (auto i = 0; i < n; ++i) {
      if (r[i] < d) return false;
      lft = std::max(lft, x[i] - sqrt(r[i] * r[i] - d * d));
      rgt = std::min(rgt, x[i] + sqrt(r[i] * r[i] - d * d));
    }
    return lft < rgt;
  };

  printf("%lf\n", workspace::binary_search(.0, 1e6, 1e-3, isc));
}
