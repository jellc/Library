#define PROBLEM "https://judge.yosupo.jp/problem/sort_points_by_argument"

#include <algorithm>
#include <cstdio>

#include "src/utils/compare.hpp"

int main() {
  struct point {
    int x, y;
  };

  int n;
  point pos[1 << 18];

  scanf("%d", &n);
  for (int i = 0; i != n; ++i) scanf("%d%d", &pos[i].x, &pos[i].y);

  std::sort(pos, pos + n, workspace::compare_arg<point>);

  for (int i = 0; i != n; ++i) printf("%d %d\n", pos[i].x, pos[i].y);
}
