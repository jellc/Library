#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"
#include <bits/stdc++.h>

#include "string/Z_algorithm.hpp"

int main() {
  std::string s;
  std::cin >> s;
  Z_algorithm z(s);
  for (int e : z) printf(" %d", e);
  puts("");
}
