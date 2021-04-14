#define PROBLEM "https://judge.yosupo.jp/problem/system_of_linear_equations"

#include "src/algebra/linear/lu.hpp"
#include "src/modular/modint.hpp"
#include "src/utils/io/istream.hpp"
#include "src/utils/io/ostream.hpp"

namespace workspace {

using mint = modint<998244353>;
using mat = matrix<mint>;

void main() {
  // start here!

  size_t n, m;
  cin >> n >> m;

  lu_decomposition lu = [&] {
    mat a(n, m);
    cin >> a;
    return a;
  }();

  auto res = lu.solve([&] {
    std::vector<mint> b(n);
    cin >> b;
    return b;
  }());

  if (!res.first) {
    std::cout << "-1\n";
    return;
  }

  auto ker = lu.kernel();
  std::cout << ker.size() << "\n" << res.second << "\n";
  for (auto &&v : ker) std::cout << v << "\n";
}

}  // namespace workspace

int main() { workspace::main(); }
