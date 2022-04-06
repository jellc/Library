#define PROBLEM "https://old.yosupo.jp/problem/inv_of_formal_power_series"

#include "src/algebra/modint.hpp"
#include "src/algebra/polynomial.hpp"
#include "src/utils/io/istream.hpp"
#include "src/utils/io/ostream.hpp"

int main() {
  using namespace workspace;

  int n;
  cin >> n;
  polynomial<modint<998244353>> a(n);
  cin >> a;
  std::cout << a.inv() << "\n";
}
