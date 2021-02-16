#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det"

#include "src/algebra/linear/lu.hpp"
#include "src/modular/modint.hpp"
#include "src/utils/io/istream.hpp"

int main() {
  using namespace workspace;
  using mint = modint<998244353>;

  int n;
  cin >> n;
  std::cout << lu_decomposition([&] {
                 matrix<mint> a(n, n);
                 cin >> a;
                 return a;
               }())
                   .det()
            << "\n";
}
