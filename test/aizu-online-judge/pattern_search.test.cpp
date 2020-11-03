#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_C"
#include "string/rolling_hash.hpp"
#include "utils/stream.hpp"

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);

  size_t h, w, r, c;

  std::cin >> h >> w;
  std::string transposed(h * w, '?');
  for (size_t i = 0; i < h; ++i) {
    for (size_t j = 0; j < w; ++j) {
      std::cin >> transposed[j * h + i];
    }
  }

  std::cin >> r >> c;
  std::string oneln(r * c, '?');
  for (size_t i = 0; i < r; ++i) {
    for (size_t j = c; j--;) {
      std::cin >> oneln[j * r + i];
    }
  }

  workspace::rolling_hash_table grid_hash_table(transposed);
  auto pattern_hash = workspace::rolling_hash_table(oneln).substr();

  for (size_t i = 0; i + r <= h; ++i) {
    workspace::rolling_hashed hash;
    for (size_t j = 0; j < w; ++j) {
      hash = grid_hash_table.substr(h * j + i, r) + hash;
      if (j >= c) {
        hash -= grid_hash_table.substr(h * (j - c) + i, r);
      }
      if (hash == pattern_hash) std::cout << i << " " << j - c + 1 << "\n";
    }
  }
}
