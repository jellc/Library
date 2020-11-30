#pragma once

/*
 * @file basic.hpp
 * @brief Segment Tree
 */

#include <cassert>
#include <queue>
#include <vector>

#include "src/algebra/system/monoid.hpp"
#include "src/utils/sfinae.hpp"
#include "waitings.hpp"

namespace workspace {

template <class Monoid, class Container = std::vector<Monoid>>
class segment_tree {
  static_assert(std::is_same<Monoid, mapped_type<Container>>::value);

  static_assert(
      std::is_same<Monoid, decltype(std::declval<const Monoid>() +
                                    std::declval<const Monoid>())>::value,
      "\'Monoid\' has no proper binary \'operator+\'.");

  size_t size_orig, height, size_ext;
  Container data;
  internal::waitings wait;

  void repair() {
    while (!wait.empty()) {
      const size_t index = wait.pop() >> 1;
      if (index && wait.push(index)) pull(index);
    }
  }

  void pull(const size_t node) {
    data[node] = data[node << 1] + data[node << 1 | 1];
  }

  template <class Pred>
  static constexpr decltype(std::declval<Pred>()(Monoid{})) pass_args(
      Pred pred, Monoid const &_1, size_t _2) {
    return pred(_1);
  }

  template <class Pred>
  static constexpr decltype(std::declval<Pred>()(Monoid{}, size_t{})) pass_args(
      Pred pred, Monoid const &_1, size_t _2) {
    return pred(_1, _2);
  }

  template <class Pred>
  size_t left_partition_subtree(size_t node, Monoid mono, size_t step,
                                Pred pred) const {
    assert(node);
    while (node < size_ext) {
      const Monoid tmp = data[(node <<= 1) | 1] + mono;
      if (pass_args(pred, tmp, ((node | 1) << --step) ^ size_ext))
        mono = tmp;
      else
        ++node;
    }
    return ++node -= size_ext;
  }

  template <class Pred>
  size_t right_partition_subtree(size_t node, Monoid mono, size_t step,
                                 Pred pred) const {
    assert(node);
    while (node < size_ext) {
      const Monoid tmp = mono + data[node <<= 1];
      if (pass_args(pred, tmp, ((node | 1) << --step) ^ size_ext))
        ++node, mono = tmp;
    }
    return (node -= size_ext) < size_orig ? node : size_orig;
  }

 public:
  using value_type = Monoid;

  segment_tree(const size_t n = 0)
      : size_orig{n},
        height(n > 1 ? 32 - __builtin_clz(n - 1) : 0),
        size_ext{1u << height},
        data(size_ext << 1),
        wait(size_ext << 1) {}

  segment_tree(const size_t n, const Monoid &init) : segment_tree(n) {
    std::fill(std::next(std::begin(data), size_ext), std::end(data), init);
    for (size_t i{size_ext}; --i;) pull(i);
  }

  template <class iter_type, class value_type = typename std::iterator_traits<
                                 iter_type>::value_type>
  segment_tree(iter_type first, iter_type last)
      : size_orig(std::distance(first, last)),
        height(size_orig > 1 ? 32 - __builtin_clz(size_orig - 1) : 0),
        size_ext{1u << height},
        data(size_ext << 1),
        wait(size_ext << 1) {
    static_assert(std::is_constructible<Monoid, value_type>::value,
                  "Monoid(iter_type::value_type) is not constructible.");
    for (auto iter{std::next(std::begin(data), size_ext)};
         iter != std::end(data) && first != last; ++iter, ++first)
      *iter = Monoid{*first};
    for (size_t i{size_ext}; --i;) pull(i);
  }

  template <class Cont, typename = typename Cont::value_type>
  segment_tree(const Cont &cont)
      : segment_tree(std::begin(cont), std::end(cont)) {}

  /*
   * @fn size
   * @return Number of elements.
   */
  size_t size() const { return size_orig; }

  // size_t capacity() const { return size_ext; }

  /*
   * @fn operator[]
   * @param index Index of the element
   * @return Reference to the element.
   */
  Monoid &operator[](size_t index) {
    assert(index < size_orig);
    wait.push(index |= size_ext);
    return data[index];
  }

  /*
   * @fn operator[]
   * @param index Index of the element
   * @return Const reference to the element.
   */
  const Monoid &operator[](size_t index) const {
    assert(index < size_orig);
    return data[index |= size_orig];
  }

  /*
   * @fn fold
   * @param first Left end, inclusive
   * @param last Right end, exclusive
   * @return Sum of elements in the interval.
   */
  Monoid fold(size_t first, size_t last) {
    assert(last <= size_orig);
    repair();
    Monoid leftval{}, rightval{};
    first += size_ext, last += size_ext;
    while (first < last) {
      if (first & 1) leftval = leftval + data[first++];
      if (last & 1) rightval = data[--last] + rightval;
      first >>= 1, last >>= 1;
    }
    return leftval + rightval;
  }

  /*
   * @fn fold
   * @return Sum of all elements.
   */
  Monoid fold() { return fold(0, size_orig); }

  /*
   * @fn left_partition
   * @brief Binary search for the partition point.
   * @param right Right fixed end of the interval, exclusive
   * @param pred Predicate in the form of either 'bool(Monoid)' or 'bool(Monoid,
   * size_t)'
   * @return Left end of the extremal interval satisfying the condition,
   * inclusive.
   */
  template <class Pred> size_t left_partition(size_t right, Pred pred) {
    assert(right <= size_orig);
    repair();
    right += size_ext;
    Monoid mono{};
    for (size_t left{size_ext}, step{}; left != right;
         left >>= 1, right >>= 1, ++step) {
      if ((left & 1) != (right & 1)) {
        const Monoid tmp = data[--right] + mono;
        if (!pass_args(pred, tmp, (right << step) ^ size_ext))
          return left_partition_subtree(right, mono, step, pred);
        mono = tmp;
      }
    }
    return 0;
  }

  /*
   * @fn right_partition
   * @brief Binary search for the partition point.
   * @param left Left fixed end of the interval, inclusive
   * @param pred Predicate in the form of either 'bool(Monoid)' or 'bool(Monoid,
   * size_t)'
   * @return Right end of the extremal interval satisfying the condition,
   * exclusive.
   */
  template <class Pred> size_t right_partition(size_t left, Pred pred) {
    assert(left <= size_orig);
    repair();
    left += size_ext;
    Monoid mono{};
    for (size_t right{size_ext << 1}, step{}; left != right;
         left >>= 1, right >>= 1, ++step) {
      if ((left & 1) != (right & 1)) {
        const Monoid tmp = mono + data[left];
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
