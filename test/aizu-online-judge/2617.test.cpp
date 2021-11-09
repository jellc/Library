#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/2617"

#include <iostream>
#include <numeric>

#include "src/misc/inversion.hpp"

int main() {
  int n;
  std::cin >> n;
  std::vector<long long> p(n), l(n);
  for (auto &&x : p) {
    std::cin >> x;
  }
  for (auto &&x : l) {
    std::cin >> x;
  }

  std::partial_sum(p.begin(), p.end(), p.begin());

  auto ans = workspace::inversion(p.begin(), p.end());
  std::sort(p.begin(), p.end());

  for (auto i = n; --i;) p[i] -= p[i - 1];
  for (auto i = 0; i < n; ++i)
    if (p[i] < l[i]) {
      std::cout << "-1\n";
      return 0;
    }

  std::cout << ans << "\n";
}
