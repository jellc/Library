#define PROBLEM "https://judge.yosupo.jp/problem/sort_points_by_argument"

#include <algorithm>
#include <iostream>

#include "src/geometry/compare.hpp"

int main() {
  using namespace workspace;

  int n;
  std::cin >> n;
  std::vector<point<long long>> pos(n);
  for (auto &[x, y] : pos) std::cin >> x >> y;

  std::sort(pos.begin(), pos.end(), less_arg<long long>());
  for (auto &[x, y] : pos) std::cout << x << " " << y << "\n";
}
