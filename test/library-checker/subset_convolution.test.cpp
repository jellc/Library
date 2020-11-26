#define PROBLEM "https://judge.yosupo.jp/problem/subset_convolution"
#include <iostream>

#include "src/algebra/convolution/subset.hpp"
#include "src/modular/modint.hpp"

int main() {
  using mint = workspace::modint<998244353>;
  using std::cin;
  int n;
  cin >> n;
  std::vector<mint> a(1 << n), b(1 << n);
  for (auto &x : a) cin >> x;
  for (auto &x : b) cin >> x;
  a = subset_convolute(a, b);
  for (auto x : a) printf("%d ", x);
  puts("");
}
