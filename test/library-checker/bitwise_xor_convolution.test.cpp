#define PROBLEM "https://judge.yosupo.jp/problem/bitwise_xor_convolution"

#include <vector>

#include "src/algebra/convolution/bitxor.hpp"
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
  std::cout << bitxor_conv(a, b) << "\n";
}
