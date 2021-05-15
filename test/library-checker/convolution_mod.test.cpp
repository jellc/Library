#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "src/algebra/polynomial.hpp"
#include "src/modular/modint.hpp"
#include "src/utils/io/istream.hpp"
#include "src/utils/io/ostream.hpp"

int main() {
  using namespace workspace;

  int n, m;
  cin >> n >> m;
  polynomial<modint<998244353>> a(n), b(m);
  cin >> a >> b;
  (a *= b).resize(n + m - 1);
  std::cout << a << "\n";
}
