#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ITP1_7_D"

#include "src/algebra/linear/matrix.hpp"
#include "src/utils/io/istream.hpp"
#include "src/utils/io/ostream.hpp"

int main() {
  using namespace workspace;
  int n, m, l;
  cin >> n >> m >> l;
  matrix<long long> a(n, m), b(m, l);
  cin >> a >> b;
  for (const auto &r : a *b) std::cout << r << "\n";
}
