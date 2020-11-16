#define IGNORE
#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"
#include "algebra/formal_power_series/all.hpp"
#include "modulus/modint.hpp"
#include "utils/stream.hpp"

int main() {
  int n, m;
  std::cin >> n >> m;
  FormalPowerSeries<LazyMontgomeryModInt<998244353>> a(n), b(m);
  std::cin >> a >> b;
  std::cout << a * b << '\n';
}
