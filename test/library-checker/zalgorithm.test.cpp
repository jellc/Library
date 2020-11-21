#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include "src/string/z_algorithm.hpp"
#include "src/utils/io/ostream.hpp"

int main() {
  std::string s;
  std::cin >> s;
  workspace::z_algorithm z(s);
  std::cout << z << "\n";
}
