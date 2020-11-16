/*
 * @file Mo.hpp
 * @brief Mo's Algorithm
 */

#pragma once
#include <cassert>
#include <cmath>
#include <functional>
#include <numeric>
#include <vector>

namespace workspace {

/*
 * @class Mo
 * @brief process queries about contiguous subarray
 * @tparam Push_back
 * @tparam Pop_back
 * @tparam Push_front Push_back as default
 * @tparam Pop_front Pop_back as default
 */
template <class Push_back, class Pop_back, class Push_front = Push_back,
          class Pop_front = Pop_back>
class Mo {
  Push_front push_front;
  Pop_front pop_front;
  Push_back push_back;
  Pop_back pop_back;
  std::vector<size_t> lft, rgt, ord;
  std::vector<size_t>::iterator itr;
  size_t lpos, rpos;

 public:
  /*
   * @param push_back
   * @param pop_back
   */
  Mo(Push_back push_back, Pop_back pop_back)
      : Mo(push_back, pop_back, push_back, pop_back) {}

  /*
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

  /*
   * @return number of queries
   */
  size_t size() const { return lft.size(); }

  /*
   * @brief add query
   * @param l left end, inclusive
   * @param r right end, exclusive
   */
  void set(size_t l, size_t r) {
    assert(!(r < l));
    lft.emplace_back(l), rgt.emplace_back(r);
  }

  /*
   * @brief sort queries
   */
  void make() {
    assert(size());
    ord.resize(size());
    iota(ord.begin(), ord.end(), 0);
    const size_t width = sqrt(*max_element(rgt.begin(), rgt.end()));
    std::sort(ord.begin(), ord.end(), [&](size_t x, size_t y) {
      if (lft[x] / width != lft[y] / width) return lft[x] < lft[y];
      return rgt[x] < rgt[y];
    });
    itr = ord.begin();
  }

  /*
   * @brief process one query
   * @return index of query
   */
  size_t process() {
    if (itr == ord.end()) return ord.size();
    const size_t id = *itr++, l = lft[id], r = rgt[id];
    while (lpos > l) push_front(--lpos);
    while (rpos < r) push_back(rpos++);
    while (lpos < l) pop_front(lpos++);
    while (rpos > r) pop_back(--rpos);
    return id;
  }
};

}  // namespace workspace
