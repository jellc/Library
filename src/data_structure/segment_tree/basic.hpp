#pragma once

/*
 * @file basic.hpp
 * @brief Segment Tree
 */

#include <cassert>
#include <queue>
#include <vector>

#include "algebra/system/monoid.hpp"
#include "src/utils/sfinae.hpp"
#include "waitlist.hpp"

namespace workspace {

template <class Monoid, class Container = std::vector<Monoid>>
class segment_tree {
  static_assert(std::is_same<Monoid, mapped_type<Container>>::value);

  size_t size_orig, height, size_ext;
  Container data;
  internal::waitlist wait;

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
  size_t left_partition_subtree(size_t index, const Pred pred,
                                Monoid mono) const {
    assert(index);
    while (index < size_ext) {
      const Monoid tmp = data[(index <<= 1) | 1] + mono;
      if (pred(tmp))
        mono = tmp;
      else
        ++index;
    }
    return ++index -= size_ext;
  }

  template <class Pred>
  size_t right_partition_subtree(size_t index, const Pred pred,
                                 Monoid mono) const {
    assert(index);
    while (index < size_ext) {
      const Monoid tmp = mono + data[index <<= 1];
      if (pred(tmp)) ++index, mono = tmp;
    }
    return (index -= size_ext) < size_orig ? index : size_orig;
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

  size_t size() const { return size_orig; }
  size_t capacity() const { return size_ext; }

  // reference to the element at the index.
  Monoid &operator[](size_t index) {
    assert(index < size_orig);
    wait.push(index |= size_ext);
    return data[index];
  }

  // const reference to the element at the index.
  const Monoid &operator[](size_t index) const {
    assert(index < size_orig);
    return data[index |= size_orig];
  }

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

  Monoid fold() { return fold(0, size_orig); }

  template <class Pred> size_t left_partition(size_t right, Pred pred) {
    assert(right <= size_orig);
    repair();
    right += size_ext;
    Monoid mono{};
    for (size_t left{size_ext}; left != right; left >>= 1, right >>= 1) {
      if ((left & 1) != (right & 1)) {
        const Monoid tmp = data[--right] + mono;
        if (!pred(tmp)) return left_partition_subtree(right, pred, mono);
        mono = tmp;
      }
    }
    return 0;
  }

  template <class Pred> size_t right_partition(size_t left, Pred pred) {
    assert(left <= size_orig);
    repair();
    left += size_ext;
    Monoid mono{};
    for (size_t right{size_ext << 1}; left != right; left >>= 1, right >>= 1) {
      if ((left & 1) != (right & 1)) {
        const Monoid tmp = mono + data[left];
        if (!pred(tmp)) return right_partition_subtree(left, pred, mono);
        mono = tmp;
        ++left;
      }
    }
    return size_orig;
  }
};

}  // namespace workspace
