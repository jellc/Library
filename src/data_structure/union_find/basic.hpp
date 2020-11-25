#pragma once

/*
 * @file basic.hpp
 * @brief Basic Union-Find
 */

#include <cassert>
#include <cstdint>
#include <vector>

namespace workspace {

template <typename Tp> struct union_find {
 protected:
  using signed_t = typename std::make_signed<Tp>::type;
  using unsigned_t = typename std::make_unsigned<Tp>::type;

  std::vector<signed_t> link;

 public:
  /*
   * @param n The number of nodes.
   */
  union_find(Tp n = 0) : link(n, 1) {}

  /*
   * @fn find
   * @param x A node.
   * @return The representative of the group.
   */
  virtual unsigned_t find(unsigned_t x) {
    assert(x < size());
    return link[x] > 0 ? x : -(link[x] = -(signed_t)find(-link[x]));
  }

  /*
   * @fn size
   * @return The number of nodes.
   */
  unsigned_t size() const { return link.size(); }

  /*
   * @fn size
   * @param x A node.
   * @return The number of nodes in the group.
   */
  virtual unsigned_t size(unsigned_t x) {
    assert(x < size());
    return link[find(x)];
  }

  /*
   * @fn same
   * @param x 1st node.
   * @param y 2nd node.
   * @return Whether or not the two nodes belong to the same group.
   */
  bool same(unsigned_t x, unsigned_t y) {
    assert(x < size());
    assert(y < size());
    return find(x) == find(y);
  }

  /*
   * @fn unite
   * @param x 1st node.
   * @param y 2nd node.
   * @return Whether or not the two groups were merged anew.
   */
  virtual bool unite(unsigned_t x, unsigned_t y) {
    assert(x < size()), x = find(x);
    assert(y < size()), y = find(y);
    if (x == y) return false;
    if (link[x] < link[y]) std::swap(x, y);
    link[x] += link[y];
    link[y] = -(signed_t)x;
    return true;
  }
};

}  // namespace workspace
