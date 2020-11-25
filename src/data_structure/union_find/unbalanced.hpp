#pragma once

/*
 * @file unbalanced.hpp
 * @brief Unbalanced Union-Find
 */

#include "basic.hpp"

namespace workspace {

class unbalanced_union_find : public union_find<uint_least32_t> {
  using base = union_find<uint_least32_t>;

 public:
  using base::union_find;

  bool unite(unsigned_t x, unsigned_t y) override {
    assert(x < size()), x = find(x);
    assert(y < size()), y = find(y);
    if (x == y) return false;
    link[x] += link[y];
    link[y] = -(signed_t)x;
    return true;
  }
};

}  // namespace workspace
