#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_A"

#include "data_structure/segment_tree/basic.hpp"
#include "utils/io.hpp"

int main() {
  using mono = workspace::min_monoid<int>;
  mono::max = std::numeric_limits<int>::max();
  int n, q;
  std::cin >> n >> q;
  segment_tree<mono> seg(n);
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
