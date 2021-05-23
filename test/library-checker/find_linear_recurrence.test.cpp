#define PROBLEM "https://judge.yosupo.jp/problem/find_linear_recurrence"

#include "src/algebra/berlekamp_massey.hpp"
#include "src/modular/modint.hpp"
#include "src/utils/io/istream.hpp"
#include "src/utils/io/ostream.hpp"

int main() {
  using namespace workspace;
  using mint = modint<998244353>;

  int n;
  cin >> n;
  polynomial<mint> a(n);
  cin >> a;
  auto b = a;
  a = Berlekamp_Massey(a.begin(), a.end());
  a.pop_back();
  for (auto &&x : a) x = -x;
  std::reverse(a.begin(), a.end());
  std::cout << a.size() << "\n";
  std::cout << a << "\n";
}
