#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_E"

#include <iostream>

#include "src/number_theory/ext_gcd.hpp"
#include "src/utils/io/ostream.hpp"

int main() {
  using namespace workspace;
  int a, b;
  std::cin >> a >> b;
  __int128_t _a = a;
  auto [x, y] = ext_gcd(_a, b);
  if (x > 0) x -= b, y += a;
  if ((y - x) * 2 > a + b) x += b, y -= a;
  a = x, b = y;
  std::cout << std::tie(a, b) << "\n";
}
