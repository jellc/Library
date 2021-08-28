#define PROBLEM "https://old.yosupo.jp/problem/multipoint_evaluation"

#include "src/algebra/modint.hpp"
#include "src/algebra/polynomial.hpp"
#include "src/utils/io/istream.hpp"
#include "src/utils/io/ostream.hpp"

int main() {
  using namespace workspace;
  using mint = modint<998244353>;

  int n, m;
  cin >> n >> m;
  polynomial<mint> f(n);
  std::vector<mint> p(m);
  cin >> f >> p;
  f.eval(begin(p), end(p));
  std::cout << p << "\n";
}
