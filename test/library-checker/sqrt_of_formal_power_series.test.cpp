#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_of_formal_power_series"

#include "src/algebra/fps.hpp"
#include "src/algebra/modint.hpp"
#include "src/utils/io/istream.hpp"
#include "src/utils/io/ostream.hpp"

int main() {
  using namespace workspace;

  int n;
  cin >> n;
  formal_power_series<modint<998244353>> a(n);
  cin >> a;
  a = a.sqrt();
  if (a.empty())
    std::cout << "-1\n";
  else {
    a.resize(n);
    std::cout << a << "\n";
  }
}
