#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_interpolation"

#include "src/algebra/interpolation.hpp"
#include "src/algebra/modint.hpp"
#include "src/utils/io/istream.hpp"
#include "src/utils/io/ostream.hpp"

int main() {
  using namespace workspace;
  using mint = modint<998244353>;

  int n;
  cin >> n;
  std::vector<std::pair<mint, mint>> xy(n);
  for (auto&& [x, y] : xy) cin >> x;
  for (auto&& [x, y] : xy) cin >> y;
  auto p = interpolate(begin(xy), end(xy));
  p.resize(n);
  std::cout << p << "\n";
}
