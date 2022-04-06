#define PROBLEM "https://judge.yosupo.jp/problem/pow_of_formal_power_series"

#include "src/algebra/fps.hpp"
#include "src/algebra/modint.hpp"
#include "src/utils/io/istream.hpp"
#include "src/utils/io/ostream.hpp"

int main() {
  using namespace workspace;

  int n, m;
  cin >> n >> m;
  formal_power_series<modint<998244353>> f(n);
  cin >> f;
  std::cout << f.pow(m) << "\n";
}
