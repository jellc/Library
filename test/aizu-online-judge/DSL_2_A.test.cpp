#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_A"

#include <iostream>

#include "src/data_structure/segment_tree/basic.hpp"

int main() {
  using mono = workspace::min_monoid<int>;
  mono::max = std::numeric_limits<int>::max();
  int n, q;
  std::cin >> n >> q;
  workspace::segment_tree<mono> seg(n);
  while (q--) {
    int tp, x, y;
    std::cin >> tp >> x >> y;
    if (tp) {
      std::cout << seg.fold(x, y + 1) << '\n';
    } else {
      seg[x] = y;
    }
  }
}
