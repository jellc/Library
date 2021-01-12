#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_D"

#include <iostream>

#include "src/number_theory/totient.hpp"

int main() {
  using namespace workspace;
  int n;
  std::cin >> n;
  std::cout << totient(n) << "\n";
}
