#define PROBLEM "https://judge.yosupo.jp/problem/cartesian_tree"

#include <algorithm>

#include "src/data_structure/cartesian_tree.hpp"
#include "src/utils/io/istream.hpp"
#include "src/utils/io/ostream.hpp"

int main() {
  using namespace workspace;

  int n;
  cin >> n;
  std::vector<int> a(n);
  cin >> a;
  auto ans = Cartesian_tree(a.begin(), a.end());
  auto r = std::find(ans.begin(), ans.end(), -1);
  *r = r - ans.begin();
  std::cout << ans << "\n";
}
