#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ITP1_6_D"

#include "src/algebra/linear/matrix.hpp"
#include "src/utils/io/istream.hpp"
#include "src/utils/io/ostream.hpp"

int main() {
  using namespace workspace;
  int n, m;
  cin >> n >> m;
  matrix<long long> a(n, m), b(m, 1);
  cin >> a >> b;
  std::cout << (a *= b);
}
