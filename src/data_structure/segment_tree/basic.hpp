#pragma once

/**
 * @file basic.hpp
 * @brief Segment Tree
 */

#include <cassert>
#include <vector>

#include "src/algebra/system/monoid.hpp"

namespace workspace {

/**
 * @tparam Monoid `operator+`
 * @tparam Container_tmpl `operator[]`, `size_type`
 */
template <class Monoid, template <class...> class Container_tmpl = std::vector>
class segment_tree {
  static_assert(
      std::is_same<Monoid, decltype(std::declval<const Monoid>() +
                                    std::declval<const Monoid>())>::value,
      "\'Monoid\' has no proper binary \'operator+\'.");

  struct node {
    Monoid value{};
    bool latest{true};
  };

  using container_type = Container_tmpl<node>;

 public:
  using size_type = typename container_type::size_type;

  class iterator {
    segment_tree *__p;
    size_type __i;

   public:
    using difference_type = typename std::make_signed<size_type>::type;
    using value_type = Monoid;
    using reference = Monoid &;
    using pointer = iterator;
    using iterator_category = std::random_access_iterator_tag;

    /**
     * @brief Construct a new iterator object
     *
     */
    iterator() = default;

    /**
     * @brief Construct a new iterator object
     *
     * @param __p Pointer to a segment tree object
     * @param __i Index
     */
    iterator(segment_tree *__p, size_type __i) : __p(__p), __i(__i) {}

    bool operator==(iterator const &rhs) const {
      return __p == rhs.__p && __i == rhs.__i;
    }
    bool operator!=(iterator const &rhs) const { return !operator==(rhs); }

    bool operator<(iterator const &rhs) const { return __i < rhs.__i; }
    bool operator>(iterator const &rhs) const { return __i > rhs.__i; }
    bool operator<=(iterator const &rhs) const { return __i <= rhs.__i; }
    bool operator>=(iterator const &rhs) const { return __i >= rhs.__i; }

    iterator &operator++() { return ++__i, *this; }
    iterator &operator--() { return --__i, *this; }

    difference_type operator-(iterator const &rhs) const {
      return __i - rhs.__i;
    }

    /**
     * @brief
     *
     * @return reference
     */
    reference operator*() const { return __p->operator[](__i); }
  };

  using value_type = typename iterator::value_type;
  using reference = typename iterator::reference;

  iterator begin() { return {this, 0}; }
  iterator end() { return {this, size_orig}; }

  auto rbegin() { return std::make_reverse_iterator(end()); }
  auto rend() { return std::make_reverse_iterator(begin()); }

 protected:
  size_type size_orig, height, size_ext;
  container_type data;

  Monoid const &pull(size_type __i) noexcept {
    if (!data[__i].latest)
      data[__i] = {pull(__i << 1) + pull(__i << 1 | 1), true};
    return data[__i].value;
  }

  template <class Pred>
  static constexpr decltype(std::declval<Pred>()(Monoid{})) pass_args(
      Pred pred, Monoid const &_1, [[maybe_unused]] size_type _2) {
    return pred(_1);
  }

  template <class Pred>
  static constexpr decltype(std::declval<Pred>()(Monoid{}, size_type{}))
  pass_args(Pred pred, Monoid const &_1, size_type _2) {
    return pred(_1, _2);
  }

  template <class Pred>
  size_type left_partition_subtree(size_type __i, Monoid mono, size_type step,
                                   Pred pred) {
    assert(__i);
    while (__i < size_ext) {
      const Monoid tmp = pull((__i <<= 1) | 1) + mono;
      if (pass_args(pred, tmp, ((__i | 1) << --step) ^ size_ext))
        mono = tmp;
      else
        ++__i;
    }
    return ++__i -= size_ext;
  }

  template <class Pred>
  size_type right_partition_subtree(size_type __i, Monoid mono, size_type step,
                                    Pred pred) {
    assert(__i);
    while (__i < size_ext) {
      const Monoid tmp = mono + pull(__i <<= 1);
      if (pass_args(pred, tmp, ((__i | 1) << --step) ^ size_ext))
        ++__i, mono = tmp;
    }
    return (__i -= size_ext) < size_orig ? __i : size_orig;
  }

 public:
  /**
   * @brief Construct a new segment tree object
   *
   * @param __n Number of elements.
   */
  segment_tree(size_type __n = 0)
      : size_orig{__n},
        height(__n > 1 ? 64 - __builtin_clzll(__n - 1) : 0),
        size_ext{size_type{1} << height} {
    if constexpr (std::is_constructible_v<container_type, size_t>)
      data = container_type(size_ext << 1);
  }

  /**
   * @brief Construct a new segment tree object
   *
   * @tparam Tp
   * @param __n Number of elements.
   * @param init
   */
  template <class Tp,
            std::enable_if_t<std::is_convertible_v<Tp, Monoid>> * = nullptr>
  segment_tree(size_type __n, Tp const &init) : segment_tree(__n) {
    for (auto i = begin(); i != end(); ++i) *i = init;
  }

  /**
   * @brief Construct a new segment tree object
   *
   * @tparam Iterator
   * @param __first
   * @param __last
   */
  template <class Iterator,
            std::enable_if_t<std::is_convertible_v<
                typename std::iterator_traits<Iterator>::value_type, Monoid>>
                * = nullptr>
  segment_tree(Iterator __first, Iterator __last)
      : segment_tree(std::distance(__first, __last)) {
    for (auto i = begin(); __first != __last; ++i, ++__first) *i = *__first;
  }

  /**
   * @return Number of elements.
   */
  size_type size() const { return size_orig; }

  /**
   * @param __i Index of the element
   * @return Reference to the element.
   */
  reference operator[](size_type __i) {
    assert(__i < size_orig);
    __i |= size_ext;
    for (size_type __j{__i >> 1}; __j && data[__j].latest; __j >>= 1)
      data[__j].latest = false;
    return data[__i].value;
  }

  /**
   * @param first Left end, inclusive
   * @param last Right end, exclusive
   * @return Sum of elements in the interval.
   */
  value_type fold(size_type first, size_type last) {
    assert(last <= size_orig);
    Monoid left{}, right{};
    first += size_ext, last += size_ext;
    while (first < last) {
      if (first & 1) left = left + pull(first++);
      if (last & 1) right = pull(--last) + right;
      first >>= 1, last >>= 1;
    }
    return left + right;
  }

  /**
   * @return The whole sum.
   */
  value_type fold() { return fold(0, size_orig); }

  /**
   * @brief Binary search for the partition point.
   * @param right Right fixed end of the interval, exclusive
   * @param pred Predicate in the form of either 'bool(Monoid)' or 'bool(Monoid,
   * size_type)'
   * @return Left end of the extremal interval satisfying the condition,
   * inclusive.
   */
  template <class Pred> size_type left_partition(size_type right, Pred pred) {
    assert(right <= size_orig);
    right += size_ext;
    Monoid mono{};
    for (size_type left{size_ext}, step{}; left != right;
         left >>= 1, right >>= 1, ++step) {
      if ((left & 1) != (right & 1)) {
        const Monoid tmp = pull(--right) + mono;
        if (!pass_args(pred, tmp, (right << step) ^ size_ext))
          return left_partition_subtree(right, mono, step, pred);
        mono = tmp;
      }
    }
    return 0;
  }

  /**
   * @brief Binary search for the partition point.
   * @param left Left fixed end of the interval, inclusive
   * @param pred Predicate in the form of either 'bool(Monoid)' or 'bool(Monoid,
   * size_type)'
   * @return Right end of the extremal interval satisfying the condition,
   * exclusive.
   */
  template <class Pred> size_type right_partition(size_type left, Pred pred) {
    assert(left <= size_orig);
    left += size_ext;
    Monoid mono{};
    for (size_type right{size_ext << 1}, step{}; left != right;
         left >>= 1, right >>= 1, ++step) {
      if ((left & 1) != (right & 1)) {
        const Monoid tmp = mono + pull(left);
        if (!pass_args(pred, tmp, ((left + 1) << step) ^ size_ext))
          return right_partition_subtree(left, mono, step, pred);
        mono = tmp;
        ++left;
      }
    }
    return size_orig;
  }
};

}  // namespace workspace
