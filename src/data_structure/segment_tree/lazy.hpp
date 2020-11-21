#pragma once

/*
 * @file lazy.hpp
 * @brief Lazy Segment Tree
 */

#include <cassert>
#include <queue>
#include <vector>

#include "algebra/system/monoid.hpp"
#include "src/utils/sfinae.hpp"
#include "waitlist.hpp"

namespace workspace {

template <class Monoid, class Endomorphism,
          class Monoid_container = std::vector<Monoid>,
          class Endomorphism_container = std::vector<Endomorphism>>
class lazy_segment_tree {
  static_assert(std::is_same<Monoid, mapped_type<Monoid_container>>::value);

  static_assert(
      std::is_same<Endomorphism, mapped_type<Endomorphism_container>>::value);

  static_assert(std::is_same<Monoid, decltype(Monoid{} + Monoid{})>::value,
                "\'Monoid\' has no proper binary operator+.");

  static_assert(std::is_same<Endomorphism,
                             decltype(Endomorphism{} * Endomorphism{})>::value,
                "\'Endomorphism\' has no proper binary operator*.");

  static_assert(
      std::is_same<Monoid, decltype(Monoid{} * Endomorphism{})>::value,
      "\'Endomorphism\' is not applicable to \'Monoid\'.");

  size_t size_orig, height, size_ext;
  Monoid_container data;
  Endomorphism_container lazy;
  internal::waitlist wait;

  void repair() {
    while (!wait.empty()) {
      const size_t index = wait.pop() >> 1;
      if (index && wait.push(index)) pull(index);
    }
  }

  void apply(size_t node, const Endomorphism &endo) {
    data[node] = data[node] * endo;
    if (node < size_ext) lazy[node] = lazy[node] * endo;
  }

  void push(size_t node) {
    if (!(node < size_ext)) return;
    apply(node << 1, lazy[node]);
    apply(node << 1 | 1, lazy[node]);
    lazy[node] = Endomorphism{};
  }

  void pull(size_t node) { data[node] = data[node << 1] + data[node << 1 | 1]; }

  template <class Pred>
  size_t left_partition_subtree(size_t node, Pred pred, Monoid mono) {
    assert(node);
    while (node < size_ext) {
      push(node);
      const Monoid &tmp = data[(node <<= 1) | 1] + mono;
      if (pred(tmp))
        mono = tmp;
      else
        ++node;
    }
    return ++node -= size_ext;
  }

  template <class Pred>
  size_t right_partition_subtree(size_t node, Pred pred, Monoid mono) {
    assert(node);
    while (node < size_ext) {
      push(node);
      const Monoid &tmp = mono + data[node <<= 1];
      if (pred(tmp)) ++node, mono = tmp;
    }
    return (node -= size_ext) < size_orig ? node : size_orig;
  }

 public:
  using value_type = Monoid;

  lazy_segment_tree(size_t n = 0)
      : size_orig{n},
        height(n > 1 ? 32 - __builtin_clz(n - 1) : 0),
        size_ext{1u << height},
        data(size_ext << 1),
        lazy(size_ext),
        wait(size_ext << 1) {}

  lazy_segment_tree(size_t n, const Monoid &init) : lazy_segment_tree(n) {
    std::fill(std::next(std::begin(data), size_ext), std::end(data), init);
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
    static_assert(std::is_constructible<Monoid, value_type>::value,
                  "Monoid(iter_type::value_type) is not constructible.");
    for (auto iter{std::next(std::begin(data), size_ext)};
         iter != std::end(data) && first != last; ++iter, ++first)
      *iter = Monoid(*first);
    for (size_t i{size_ext}; --i;) pull(i);
  }

  template <class Container, typename = element_type<Container>>
  lazy_segment_tree(const Container &cont)
      : lazy_segment_tree(std::begin(cont), std::end(cont)) {}

  size_t size() const { return size_orig; }

  size_t capacity() const { return size_ext; }

  Monoid &operator[](size_t index) {
    assert(index < size_orig);
    index |= size_ext;
    wait.push(index);
    for (size_t i = height; i; --i) push(index >> i);
    return data[index];
  }

  void update(size_t index, const Endomorphism &endo) {
    update(index, index + 1, endo);
  }

  void update(size_t first, size_t last, const Endomorphism &endo) {
    assert(last <= size_orig);
    repair();
    if (first >= last) return;
    first += size_ext, last += size_ext - 1;
    for (size_t i = height; i; --i) push(first >> i), push(last >> i);
    for (size_t l = first, r = last + 1; last; l >>= 1, r >>= 1) {
      if (l < r) {
        if (l & 1) apply(l++, endo);
        if (r & 1) apply(--r, endo);
      }
      if (first >>= 1, last >>= 1) {
        pull(first), pull(last);
      }
    }
  }

  Monoid fold() { return fold(0, size_orig); }

  Monoid fold(size_t first, size_t last) {
    assert(last <= size_orig);
    repair();
    if (first >= last) return Monoid{};
    first += size_ext, last += size_ext - 1;
    Monoid left_val{}, right_val{};
    for (size_t l = first, r = last + 1; last; l >>= 1, r >>= 1) {
      if (l < r) {
        if (l & 1) left_val = left_val + data[l++];
        if (r & 1) right_val = data[--r] + right_val;
      }
      if (first >>= 1, last >>= 1) {
        left_val = left_val * lazy[first];
        right_val = right_val * lazy[last];
      }
    }
    return left_val + right_val;
  }

  template <class Pred> size_t left_partition(size_t right, Pred pred) {
    assert(right <= size_orig);
    repair();
    right += size_ext - 1;
    for (size_t i{height}; i; --i) push(right >> i);
    ++right;
    Monoid mono{};
    for (size_t left{size_ext}; left != right; left >>= 1, right >>= 1) {
      if ((left & 1) != (right & 1)) {
        const Monoid &tmp = data[--right] + mono;
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
    for (size_t i{height}; i; --i) push(left >> i);
    Monoid mono{};
    for (size_t right{size_ext << 1}; left != right; left >>= 1, right >>= 1) {
      if ((left & 1) != (right & 1)) {
        const Monoid &tmp = mono + data[left];
        if (!pred(tmp)) return right_partition_subtree(left, pred, mono);
        mono = tmp;
        ++left;
      }
    }
    return size_orig;
  }
};

}  // namespace workspace
