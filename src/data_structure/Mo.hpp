#pragma once

/**
 * @file Mo.hpp
 * @brief Mo's Algorithm
 */

#include <cassert>
#include <cmath>
#include <functional>
#include <numeric>
#include <vector>

namespace workspace {

/**
 * @brief Mo's Alorithm. Process queries about contiguous subarrays.
 *
 * @tparam Push_back
 * @tparam Pop_back
 * @tparam Push_front Use `Push_back` as default
 * @tparam Pop_front Use `Pop_back` as default
 */
template <class Push_back, class Pop_back, class Push_front = Push_back,
          class Pop_front = Pop_back>
class Mo {
  Push_front push_front;
  Pop_front pop_front;
  Push_back push_back;
  Pop_back pop_back;
  std::vector<size_t> lft, rgt, ord;
  std::vector<size_t>::iterator iter;
  size_t lpos, rpos;

 public:
  /**
   * @brief Construct a new Mo object.
   *
   * @param push_back
   * @param pop_back
   */
  Mo(Push_back push_back, Pop_back pop_back)
      : Mo(push_back, pop_back, push_back, pop_back) {}

  /**
   * @brief Construct a new Mo object.
   *
   * @param push_front
   * @param pop_front
   * @param push_back
   * @param pop_back
   */
  Mo(Push_front push_front, Pop_front pop_front, Push_back push_back,
     Pop_back pop_back)
      : push_front(push_front),
        pop_front(pop_front),
        push_back(push_back),
        pop_back(pop_back),
        lpos(),
        rpos() {}

  /**
   * @return Number of queries.
   */
  size_t size() const { return lft.size(); }

  /**
   * @brief Add a query for the interval [l, r).
   *
   * @param __l Left end, inclusive
   * @param __r Right end, exclusive
   * @return Index of the query.
   */
  size_t add_query(size_t __l, size_t __r) {
    assert(__l <= __r);
    lft.emplace_back(__l), rgt.emplace_back(__r);
    return lft.size() - 1;
  }

  /**
   * @brief Sort all queries.
   */
  void make() {
    assert(size());
    ord.resize(size());
    std::iota(ord.begin(), ord.end(), 0);
    const size_t width =
        ceil(*max_element(rgt.begin(), rgt.end()) / sqrt(size()));
    std::sort(ord.begin(), ord.end(), [&](size_t x, size_t y) {
      if (lft[x] / width != lft[y] / width) return lft[x] < lft[y];
      return rgt[x] < rgt[y];
    });
    iter = ord.begin();
  }

  /**
   * @brief Process the next query.
   * @return Index of the query.
   */
  size_t process() {
    if (iter == ord.end()) return ord.size();
    const size_t id = *iter++, l = lft[id], r = rgt[id];
    while (lpos > l) push_front(--lpos);
    while (rpos < r) push_back(rpos++);
    while (lpos < l) pop_front(lpos++);
    while (rpos > r) pop_back(--rpos);
    return id;
  }
};

}  // namespace workspace
