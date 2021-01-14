/**
 * @file disjoint_sparse_table.hpp
 * @brief Disjoint Sparse Table
 * @date 2021-01-14
 *
 *
 */

#include <cassert>
#include <vector>

namespace workspace {

/**
 * @brief Disjoint Sparse Table.
 *
 * @tparam Semigroup `operator+`
 */
template <class Semigroup> class disjoint_sparse_table {
  using container_type = std::vector<std::vector<Semigroup>>;
  container_type __dst;

 public:
  using value_type = Semigroup;
  using size_type = typename container_type::size_type;
  using const_reference = typename container_type::const_reference;

 public:
  disjoint_sparse_table() = default;

  /**
   * @brief Construct in O(n log(n)) time.
   *
   * @param __args Create a vector from.
   */
  template <class... Args> disjoint_sparse_table(Args... __args) {
    __dst.emplace_back(__args...);
    const size_type size = __dst.front().size();
    for (size_type __w = 2; __w < size; __w <<= 1) {
      typename container_type::value_type __t;
      __t.reserve(size);
      for (size_type __i = __w; __i < size; __i += __w << 1) {
        __t.emplace_back(__dst.front()[__i - 1]);
        for (size_type __k = 2; __k <= __w; ++__k)
          __t.emplace_back(__dst.front()[__i - __k] + __t.back());
        __t.emplace_back(__dst.front()[__i]);
        for (size_type __k = 1; __k < __w && __i + __k < size; ++__k)
          __t.emplace_back(__t.back() + __dst.front()[__i + __k]);
      }
      __dst.emplace_back(::std::move(__t));
    }
  }

  /**
   * @return The number of elements.
   */
  size_type size() const { return __dst.empty() ? 0 : __dst.front().size(); }

  bool empty() const { return !size(); }

  /**
   * @param __first Left end, inclusive.
   * @param __last Right end, exclusive.
   * @return The sum of given range.
   */
  value_type fold(size_type __first, size_type __last) {
    assert(__first < __last);
    --__last;
    if (__first == __last) return __dst.front()[__first];
    size_type __b = 31 - __builtin_clz(__first ^ __last);
    return __dst[__b][__first ^ ((1 << __b) - 1)] + __dst[__b][__last];
  }

  const_reference operator[](size_type __i) const { return __dst.front()[__i]; }
};

}  // namespace workspace
