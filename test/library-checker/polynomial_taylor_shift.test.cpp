#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_taylor_shift"

#include "src/algebra/modint.hpp"
#include "src/algebra/polynomial.hpp"
#include "src/utils/io/istream.hpp"
#include "src/utils/io/ostream.hpp"

int main() {
  using namespace workspace;

  int n, c;
  cin >> n >> c;
  polynomial<modint<998244353>> a(n);
  cin >> a;
  std::cout << a.shift(c) << "\n";
}
