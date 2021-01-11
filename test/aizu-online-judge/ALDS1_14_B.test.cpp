#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_B"

#include <algorithm>
#include <cassert>
#include <iostream>

#include "src/string/kmp.hpp"

int main() {
  using namespace workspace;

  std::string t, p;
  std::cin >> t >> p;
  auto b = mp_algorithm(p + '$' + t);
  auto sb = kmp_algorithm(p + '$' + t);
  for (size_t i = 0, j = p.size() * 2 + 1; j < b.size(); ++i, ++j)
    if (b[j] == p.size()) {
      assert(sb[j] == p.size());
      std::cout << i << "\n";
    } else
      assert(sb[j] != p.size());
}
