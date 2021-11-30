#pragma once

/**
 * @file lazy.hpp
 * @brief Lazy Segment Tree
 */

#include <cassert>
#include <queue>
#include <vector>

#include "src/algebra/system/monoid.hpp"
#include "src/algebra/system/operation.hpp"
#include "src/utils/sfinae.hpp"
#include "waitings.hpp"

namespace workspace {

template <class _Monoid, class _End,
          class Monoid_container = std::vector<_Monoid>,
          class Endomorphism_container = std::vector<_End>>
class lazy_segment_tree {
  static_assert(
      std::is_same<_Monoid, typename Monoid_container::value_type>::value);

  static_assert(
      std::is_same<_End, typename Endomorphism_container::value_type>::value);

  static_assert(has_binary_plus<_Monoid>::value,
                "\'_Monoid\' has no proper binary \'operator+\'.");

  static_assert(has_binary_multiplies<_End>::value,
                "\'_End\' has no proper binary \'operator*\'.");

  static_assert(has_binary_multiplies<_Monoid, _End>::value,
                "\'_End\' is not applicable to \'_Monoid\'.");

  size_t size_orig, height, size_ext;
  Monoid_container data;
  Endomorphism_container lazy;
  internal::waitings wait;

  void repair() {
    while (!wait.empty()) {
      const size_t __i = wait.pop() >> 1;
      if (__i && wait.push(__i)) pull(__i);
    }
  }

  void _apply(size_t node, const _End &__e) {
    data[node] = data[node] * __e;
    if (node < size_ext) lazy[node] = lazy[node] * __e;
  }

  void push(size_t node) {
    _apply(node << 1, lazy[node]);
    _apply(node << 1 | 1, lazy[node]);
    lazy[node] = _End{};
  }

  void pull(size_t node) { data[node] = data[node << 1] + data[node << 1 | 1]; }

  template <class _Pred>
  size_t left_partition_subtree(size_t node, _Monoid mono, size_t step,
                                _Pred __pred) {
    assert(node);
    while (node < size_ext) {
      push(node);
      const _Monoid __tmp = data[(node <<= 1) | 1] + mono;
      if (__pred(__tmp))
        mono = std::move(__tmp);
      else
        ++node;
    }
    return ++node -= size_ext;
  }

  template <class _Pred>
  size_t right_partition_subtree(size_t node, _Monoid mono, size_t step,
                                 _Pred __pred) {
    assert(node);
    while (node < size_ext) {
      push(node);
      const _Monoid __tmp = mono + data[node <<= 1];
      if (__pred(__tmp)) ++node, mono = std::move(__tmp);
    }
    return (node -= size_ext) < size_orig ? node : size_orig;
  }

 public:
  class iterator {
    lazy_segment_tree *__p;
    size_t __i;

   public:
    using difference_type = typename std::make_signed<size_t>::type;
    using value_type = _Monoid;
    using reference = _Monoid &;
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
    iterator(lazy_segment_tree *__p, size_t __i) : __p(__p), __i(__i) {}

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

  lazy_segment_tree(size_t __n = 0)
      : size_orig{__n},
        height(__n > 1 ? 32 - __builtin_clz(__n - 1) : 0),
        size_ext{1u << height},
        data(size_ext << 1),
        lazy(size_ext),
        wait(size_ext << 1) {}

  lazy_segment_tree(size_t __n, const _Monoid &init) : lazy_segment_tree(__n) {
    std::fill_n(std::next(std::begin(data), size_ext), __n, init);
    for (size_t i{size_ext}; --i;) pull(i);
  }

  template <class iter_type, class value_type = typename std::iterator_traits<
                                 iter_type>::value_type>
  lazy_segment_tree(iter_type first, iter_type last)
      : size_orig(std::distance(first, last)),
        height(size_orig > 1 ? 32 - __builtin_clz(size_orig - 1) : 0),
        size_ext{1u << height},
        data(size_ext << 1),
        lazy(size_ext),
        wait(size_ext << 1) {
    static_assert(std::is_constructible<_Monoid, value_type>::value,
                  "_Monoid(iter_type::value_type) is not constructible.");
    for (auto iter{std::next(std::begin(data), size_ext)};
         iter != std::end(data) && first != last; ++iter, ++first)
      *iter = _Monoid(*first);
    for (size_t i{size_ext}; --i;) pull(i);
  }

  /**
   * @return Number of elements.
   */
  size_t size() const { return size_orig; }

  /**
   * @param __i Index of the element
   * @return Reference to the element.
   */
  _Monoid &operator[](size_t __i) {
    assert(__i < size_orig);
    __i |= size_ext;
    wait.push(__i);
    for (size_t i = height; i; --i) push(__i >> i);
    return data[__i];
  }

  void apply(const _End &__e) { apply(0, size_orig, __e); }

  void apply(size_t __i, const _End &__e) { apply(__i, __i + 1, __e); }

  void apply(size_t first, size_t last, const _End &__e) {
    assert(last <= size_orig);
    repair();
    if (first >= last) return;
    first += size_ext, last += size_ext;
    --last;
    for (size_t i = height; i; --i) push(first >> i), push(last >> i);
    ++last;
    for (size_t l = first, r = last; l != r; l >>= 1, r >>= 1) {
      if (l & 1) _apply(l++, __e);
      if (r & 1) _apply(--r, __e);
    }
    for (first >>= __builtin_ffs(first); first; first >>= 1) pull(first);
    for (last >>= __builtin_ffs(last); last; last >>= 1) pull(last);
  }

  /**
   * @param first Left end, inclusive
   * @param last Right end, exclusive
   * @return Sum of elements in the interval.
   */
  _Monoid fold(size_t first, size_t last) {
    assert(last <= size_orig);
    repair();
    if (first >= last) return _Monoid{};
    first += size_ext, last += size_ext - 1;
    _Monoid left_val{}, right_val{};
    for (size_t l = first, r = last + 1; l != r; l >>= 1, r >>= 1) {
      if (l & 1) left_val = left_val + data[l++];
      if (r & 1) right_val = data[--r] + right_val;
      left_val = left_val * lazy[first >>= 1];
      right_val = right_val * lazy[last >>= 1];
    }
    while (first >>= 1, last >>= 1) {
      left_val = left_val * lazy[first];
      right_val = right_val * lazy[last];
    }
    return left_val + right_val;
  }

  /**
   * @return Sum of all elements.
   */
  _Monoid fold() {
    repair();
    return data[1];
  }

  /**
   * @brief Binary search for the partition point.
   * @param __r Right fixed end of the interval, exclusive
   * @param __pred Predicate in the form of 'bool(_Monoid)'
   * @return Left end of the extremal interval satisfying the condition,
   * inclusive.
   */
  template <class _Pred> size_t left_partition(size_t __r, _Pred __pred) {
    assert(__r <= size_orig);
    repair();
    __r += size_ext - 1;
    for (size_t i{height}; i; --i) push(__r >> i);
    ++__r;
    _Monoid mono{};
    for (size_t __l{size_ext}, step{}; __l != __r;
         __l >>= 1, __r >>= 1, ++step) {
      if ((__l & 1) != (__r & 1)) {
        const _Monoid __tmp = data[--__r] + mono;
        if (!__pred(__tmp))
          return left_partition_subtree(__r, std::move(mono), step, __pred);
        mono = std::move(__tmp);
      }
    }
    return 0;
  }

  /**
   * @brief Binary search for the partition point.
   * @param __l Left fixed end of the interval, inclusive
   * @param __pred Predicate in the form of 'bool(_Monoid)'
   * @return Right end of the extremal interval satisfying the condition,
   * exclusive.
   */
  template <class _Pred> size_t right_partition(size_t __l, _Pred __pred) {
    assert(__l <= size_orig);
    repair();
    __l += size_ext;
    for (size_t i{height}; i; --i) push(__l >> i);
    _Monoid mono{};
    for (size_t __r{size_ext << 1}, step{}; __l != __r;
         __l >>= 1, __r >>= 1, ++step) {
      if ((__l & 1) != (__r & 1)) {
        const _Monoid __tmp = mono + data[__l];
        if (!__pred(__tmp))
          return right_partition_subtree(__l, std::move(mono), step, __pred);
        mono = std::move(__tmp);
        ++__l;
      }
    }
    return size_orig;
  }
};

}  // namespace workspace
