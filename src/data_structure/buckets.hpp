#pragma once

/**
 * @file buckets.hpp
 * @brief Buckets
 */

#include <cmath>
#include <vector>

namespace workspace {

/**
 * @brief Buckets on a sequence.
 */
template <class _Iterator, class _Pack, class _Unpack> struct buckets {
  // Require random access.
  static_assert(
      std::is_same<typename std::iterator_traits<_Iterator>::iterator_category,
                   std::random_access_iterator_tag>::value);

  using difference_type =
      typename std::iterator_traits<_Iterator>::difference_type;

  _Iterator __begin, __end;

  using value_type = decltype(std::declval<_Pack>()(std::declval<_Iterator>(),
                                                    std::declval<_Iterator>()));

  struct bucket {
    value_type __data;
    _Iterator __begin;
    _Iterator __end;
  };

  _Pack __pack;
  _Unpack __unpack;
  difference_type __unit;
  std::vector<bucket> __buckets;

  void prepare() {
    if (!__unit) __unit = round(sqrt(std::distance(__begin, __end)));

    for (auto __l = __begin, __r = __l; __r != __end; __l = __r) {
      for (auto __n = __unit; __r != __end && __n; --__n) ++__r;
      __buckets.push_back({__pack(__l, __r), __l, __r});
    }
  }

 public:
  /**
   * @brief Constuct a new buckets object.
   */
  buckets(_Iterator __first, _Iterator __last, _Pack __pack, _Unpack __unpack,
          difference_type __unit = 0)
      : __begin(__first),
        __end(__last),
        __pack(__pack),
        __unpack(__unpack),
        __unit(__unit) {
    prepare();
  }

  /**
   * @brief Number of buckets.
   */
  auto size() const { return __buckets.size(); }

  bool empty() const { return __begin == __end; }

  /**
   * @brief Operate on a subsegment.
   *
   * @param __first
   * @param __last
   * @param __oper
   */
  template <class _Operator>
  void operator()(_Iterator __first, _Iterator __last, _Operator __oper) {
    if (__first == __last) return;

    auto __index = std::distance(__begin, __first);
    auto __b = std::next(__buckets.begin(), __index / __unit);

    if (__index % __unit) {
      __unpack(__b->__data, __b->__begin, __b->__end);

      auto __mid = std::distance(__last, __b->__end) > 0 ? __last : __b->__end;

      auto __tmp = __pack(__first, __mid);
      __oper(__tmp);
      __unpack(__tmp, __first, __mid);

      __b->__data = __pack(__b->__begin, __b->__end);
      ++__b;
    }

    while (true) {
      if (__b == __buckets.end()) return;
      if (std::distance(__b->__end, __last) < 0) break;

      __oper(__b->__data);
      ++__b;
    }

    if (std::distance(__b->__begin, __last) > 0) {
      __unpack(__b->__data, __b->__begin, __b->__end);

      auto __tmp = __pack(__b->__begin, __last);
      __oper(__tmp);
      __unpack(__tmp, __b->__begin, __last);

      __b->__data = __pack(__b->__begin, __b->__end);
    }
  }

  /**
   * @brief Operate on a subsegment.
   *
   * @param __i
   * @param __j
   * @param __oper
   */
  template <class _Operator>
  void operator()(difference_type __i, difference_type __j, _Operator __oper) {
    operator()(std::next(__begin, __i), std::next(__begin, __j), __oper);
  }
};

}  // namespace workspace
