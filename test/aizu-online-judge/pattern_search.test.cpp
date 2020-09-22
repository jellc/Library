#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_C"
#include "string/rolling_hash.hpp"
#include "utils/stream.hpp"

int main() {
  size_t h, w, r, c;
  std::cin >> h >> w;
  std::vector<std::string> grid(h);
  std::cin >> grid >> r >> c;
  std::vector<std::string> pattern(r);
  std::cin >> pattern;

  std::string oneln;
  for (size_t j = c; j--;) {
    for (size_t i = 0; i < r; ++i) {
      oneln += pattern[i][j];
    }
  }
  std::string transposed;
  for (size_t j = 0; j < w; ++j) {
    for (size_t i = 0; i < h; ++i) {
      transposed += grid[i][j];
    }
  }

  rolling_hash_table grid_hash_table(transposed);
  auto pattern_hash = rolling_hash_table(oneln).substr();

  for (size_t i = 0; i + r <= h; ++i) {
    rolling_hashed hash;
    for (size_t j = 0; j < w; ++j) {
      hash = grid_hash_table.substr(h * j + i, r) + hash;
      if (j >= c) {
        hash = hash - grid_hash_table.substr(h * (j - c) + i, r);
      }
      if (hash == pattern_hash) std::cout << i << " " << j - c + 1 << "\n";
    }
  }
}
