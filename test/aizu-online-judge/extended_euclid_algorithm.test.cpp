#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/1/NTL_1_E"
#include "number_theory/ext_gcd.hpp"
#include "utils/stream.hpp"

int main() {
  int a, b;
  std::cin >> a >> b;
  __int128_t _a = a, _b = b;
  auto [x, y] = ext_gcd(_a, _b);
  if (x > 0) x -= b, y += a;
  if ((y - x) * 2 > a + b) x += b, y -= a;
  a = x, b = y;
  std::cout << std::tie(a, b) << "\n";
}
