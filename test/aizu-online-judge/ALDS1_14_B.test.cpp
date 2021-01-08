#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_B"

#include <algorithm>
#include <iostream>

#include "src/string/kmp.hpp"

int main() {
  using namespace workspace;

  std::string t, p;
  std::cin >> t >> p;
  auto k = kmp_algorithm(p + '$' + t);
  for (size_t i = 0, j = p.size() * 2; j < k.size(); ++i, ++j)
    if (k[j] == p.size()) std::cout << i << "\n";
}
