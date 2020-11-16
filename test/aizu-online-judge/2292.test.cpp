#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/0063"

#include "src/string/Manacher.hpp"

int main() {
  std::string str;
  while (std::cin >> str) {
    std::string str2;
    for (auto &&c : str) {
      str2 += c;
      str2 += ' ';
    }
    workspace::Manacher mnch(str2);
    size_t ans = 0;
    for (auto &&l : workspace::Manacher(str2)) {
      ans += l;
    }
    ans -= str.size();
    std::cout << ans << "\n";
  }
}
