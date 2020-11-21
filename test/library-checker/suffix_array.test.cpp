#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"
#include <bits/stdc++.h>

#include "src/string/suffix_array.hpp"
#include "src/utils/io/ostream.hpp"

int main() {
  std::string s;
  std::cin >> s;
  std::cout << workspace::suffix_array<std::string>(s) << "\n";
}
