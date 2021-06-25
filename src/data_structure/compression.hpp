#pragma once

/**
 * @file compression.hpp
 * @brief Compression
 */

#include <algorithm>
#include <cassert>
#include <vector>

namespace workspace {

template <class _Tp> class compression {
  std::vector<_Tp> __vec;

  decltype(auto) begin() { return __vec.begin(); }

  decltype(auto) end() { return __vec.end(); }

 public:
  using size_type = typename std::vector<_Tp>::size_type;

  /**
   * @brief Construct a new compression object.
   */
  compression() = default;

  /**
   * @brief Construct a new compression object.
   *
   * @param __first
   * @param __last
   */
  template <class _IIter>
  compression(_IIter __first, _IIter __last) noexcept : __vec(__first, __last) {
    make();
  }

  decltype(auto) begin() const noexcept { return __vec.begin(); }

  decltype(auto) end() const noexcept { return __vec.end(); }

  decltype(auto) operator[](size_type __i) const noexcept {
    assert(__i < size());
    return __vec[__i];
  }

  size_type size() const noexcept { return __vec.size(); }

  template <class... _Args> decltype(auto) emplace(_Args&&... __args) noexcept {
    return __vec.emplace_back(std::forward<_Args>(__args)...);
  }

  template <class... _Args> void insert(_Args&&... __args) noexcept {
    __vec.insert(end(), std::forward<_Args>(__args)...);
  }

  /**
   * @brief Sort and make unique.
   * @return Number of different values.
   */
  size_type make() noexcept {
    std::sort(begin(), end());

    __vec.erase(std::unique(begin(), end(),
                            [](const _Tp& __l, const _Tp& __r) {
                              return !(__l < __r) && !(__r < __l);
                            }),
                end());

    return size();
  }

  size_type lower_bound(const _Tp& __x) const noexcept {
    return std::lower_bound(begin(), end(), __x) - begin();
  }

  size_type upper_bound(const _Tp& __x) const noexcept {
    return std::upper_bound(begin(), end(), __x) - begin();
  }
};

template <class _IIter>
compression(_IIter, _IIter)
    -> compression<typename std::iterator_traits<_IIter>::value_type>;

}  // namespace workspace
