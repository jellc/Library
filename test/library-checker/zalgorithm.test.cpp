#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"
#include <bits/stdc++.h>

#include "string/z_algorithm.hpp"
#include "utils/stream.hpp"

int main() {
  std::string s;
  std::cin >> s;
  workspace::z_algorithm z(s);
  std::cout << z << "\n";
}
