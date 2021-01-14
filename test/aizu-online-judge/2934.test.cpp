#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/2934"

#include <iostream>

#include "src/string/Manacher.hpp"

int main() {
  using namespace workspace;
  size_t n;
  std::string s;
  std::cin >> n >> s;
  auto r = Manacher(s);
  for (size_t k = 2; k <= n; ++k) {
    bool fail = false;
    for (size_t i = k - 1; i < n; i += k - 1)
      if (r[i] < std::min(k, n - i)) fail = true;
    if (!fail) {
      std::cout << k << "\n";
      return 0;
    }
  }
}
