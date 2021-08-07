#define PROBLEM "https://judge.yosupo.jp/problem/division_of_polynomials"

#include "src/algebra/modint.hpp"
#include "src/algebra/polynomial.hpp"
#include "src/utils/io/istream.hpp"
#include "src/utils/io/ostream.hpp"

int main() {
  using namespace workspace;
  using poly = polynomial<modint<998244353>>;

  int n, m;
  cin >> n >> m;
  poly f(n), g(m);
  cin >> f >> g;

  auto [q, r] = f.divmod(g);
  std::cout << q.size() << " " << r.size() << "\n";
  std::cout << q << "\n";
  std::cout << r << "\n";
}
