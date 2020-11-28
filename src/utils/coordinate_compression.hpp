#pragma once

/*
 * @file coordinate_compression.hpp
 * @brief Coordinate Compression
 */

#include <algorithm>
#include <vector>

namespace workspace {

template <class Type, class Result = size_t>
struct coordinate_compression : std::vector<Type> {
  using std::vector<Type>::vector;
  using std::vector<Type>::begin;
  using std::vector<Type>::end;

  using result_type = Result;

  void make() {
    std::sort(begin(), end());
    std::vector<Type>::erase(std::unique(begin(), end()), end());
  }

  result_type compress(const Type &value) const {
    return std::lower_bound(begin(), end(), value) - begin();
  }

  template <class Iter>
  std::vector<result_type> compress(Iter first, Iter last) const {
    static_assert(std::is_convertible<
                  typename std::decay<decltype(*std::declval<Iter>())>::type,
                  Type>::value);
    std::vector<result_type> res;
    for (Iter iter = first; iter != last; ++iter)
      res.emplace_back(compress(*iter));
    return res;
  }
};

}  // namespace workspace
