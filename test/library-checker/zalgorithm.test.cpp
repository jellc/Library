#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include "src/string/z_algorithm.hpp"
#include "src/utils/io/ostream.hpp"

int main() {
  using namespace workspace;
  std::string s;
  std::cin >> s;
  std::cout << z_algorithm(s) << "\n";
}
