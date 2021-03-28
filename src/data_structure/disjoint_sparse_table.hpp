/**
 * @file disjoint_sparse_table.hpp
 * @brief Disjoint Sparse Table
 */

#include <cassert>
#include <vector>

namespace workspace {

/**
 * @brief Disjoint Sparse Table.
 *
 * @tparam _Semigroup `operator+`
 */
template <class _Semigroup> class disjoint_sparse_table {
 public:
  using value_type = _Semigroup;
  using container_type = std::vector<std::vector<_Semigroup>>;
  using size_type = typename container_type::size_type;
  using const_reference = typename container_type::const_reference;

 protected:
  container_type __table;

  void make() {
    for (size_type __w = 2; __w < size(); __w <<= 1) {
      auto &__t = __table.emplace_back();
      __t.reserve(size());

      const auto &__a = __table.front();

      for (size_type __i = __w; __i < size(); __i += __w << 1) {
        __t.emplace_back(__a[__i - 1]);

        for (size_type __k = 2; __k <= __w; ++__k)
          __t.emplace_back(__a[__i - __k] + __t.back());

        __t.emplace_back(__a[__i]);

        for (size_type __k = 1; __k < __w && __i + __k < size(); ++__k)
          __t.emplace_back(__t.back() + __a[__i + __k]);
      }
    }
  }

 public:
  /**
   * @brief Default construct.
   */
  disjoint_sparse_table() = default;

  /**
   * @brief Construct in O(n log(n)) time.
   *
   * @param __x Vector
   */
  disjoint_sparse_table(const std::vector<_Semigroup> &__x) {
    __table.emplace_back(__x);
    make();
  }

  /**
   * @brief Construct in O(n log(n)) time.
   *
   * @param __x Vector
   */
  disjoint_sparse_table(std::vector<_Semigroup> &&__x) {
    __table.emplace_back(std::move(__x));
    make();
  }

  /**
   * @brief Construct in O(n log(n)) time.
   *
   * @param __first
   * @param __last
   */
  template <class _IIter> disjoint_sparse_table(_IIter __first, _IIter __last) {
    __table.emplace_back(__first, __last);
    make();
  }

  /**
   * @return Number of elements.
   */
  size_type size() const {
    return __table.empty() ? 0 : __table.front().size();
  }

  bool empty() const { return !size(); }

  /**
   * @param __first Left end, inclusive.
   * @param __last Right end, exclusive.
   * @return Sum of given range.
   */
  value_type fold(size_type __first, size_type __last) {
    assert(__first < __last);
    --__last;
    if (__first == __last) return __table.front()[__first];

    size_type __b = 31 - __builtin_clz(__first ^ __last);
    return __table[__b][__first ^ ((1 << __b) - 1)] + __table[__b][__last];
  }

  const_reference operator[](size_type __i) const {
    return __table.front()[__i];
  }
};

template <class _IIter>
disjoint_sparse_table(_IIter, _IIter)
    -> disjoint_sparse_table<typename std::iterator_traits<_IIter>::value_type>;

}  // namespace workspace
