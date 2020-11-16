#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include <iostream>
#include <string>

#include "src/string/rolling_hash.hpp"
#include "src/utils/binary_search.hpp"

int main() {
  std::string s;
  std::cin >> s;
  workspace::rolling_hash_table hash(s);
  for (size_t i = 0; i < size(s); ++i) {
    if (i) std::cout << " ";
    std::cout << workspace::binary_search(
        size_t(0), size(s) + 1, [&](size_t len) -> bool {
          return hash.substr(0, len) == hash.substr(i, len);
        });
  }
  std::cout << "\n";
}
