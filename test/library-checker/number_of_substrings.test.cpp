#define PROBLEM "https://judge.yosupo.jp/problem/number_of_substrings"

#include <iostream>

#include "src/string/suffix_array.hpp"
#include "src/utils/py-like/zip.hpp"

int main() {
  std::string s;
  std::cin >> s;
  workspace::suffix_array sa(s);
  long long ans = 0;
  for (auto &&[x, y] : zip(sa, sa.lcp_array())) {
    ans += s.size() - x - y;
  }
  printf("%lld\n", ans);
}
