#define PROBLEM "https://judge.yosupo.jp/problem/bitwise_and_convolution"

#include "src/algebra/convolution/bitand.hh"
#include "src/modular/modint.hpp"
#include "src/utils/io/istream.hpp"
#include "src/utils/io/ostream.hpp"

int main() {
  using namespace workspace;
  using mint = modint<998244353>;
  size_t n;
  cin >> n;
  std::vector<mint> a(1 << n), b(1 << n);
  cin >> a >> b;
  std::cout << bitand_conv(a, b) << "\n";
}
