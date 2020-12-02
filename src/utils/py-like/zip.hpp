#pragma once

/*
 * @file zip.hpp
 * @breif Zip
 */

#include <tuple>

#if __cplusplus >= 201703L

namespace workspace {

template <class> struct zipped_iter;

template <class... Args> class zipped {
  using ref_tuple = std::tuple<Args...>;
  ref_tuple args;

  template <size_t N = 0> constexpr auto begin_cat() const {
    if constexpr (N != std::tuple_size<ref_tuple>::value) {
      return std::tuple_cat(std::tuple(std::begin(std::get<N>(args))),
                            begin_cat<N + 1>());
    } else
      return std::tuple<>();
  }

  template <size_t N = 0> constexpr auto end_cat() const {
    if constexpr (N != std::tuple_size<ref_tuple>::value) {
      return std::tuple_cat(std::tuple(std::end(std::get<N>(args))),
                            end_cat<N + 1>());
    } else
      return std::tuple<>();
  }

  using iter_tuple = decltype(std::declval<zipped>().begin_cat());

 public:
  zipped(Args &&... args) : args(args...) {}

  class iterator {
    zipped_iter<iter_tuple> iters;

    template <size_t N = 0> constexpr bool equal(const iterator &rhs) const {
      if constexpr (N != std::tuple_size<iter_tuple>::value) {
        return std::get<N>(iters) == std::get<N>(rhs.iters) ||
               equal<N + 1>(rhs);
      } else
        return false;
    }

    template <size_t N = 0> constexpr void increment() {
      if constexpr (N != std::tuple_size<iter_tuple>::value) {
        ++std::get<N>(iters);
        increment<N + 1>();
      }
    }

    template <size_t N = 0> constexpr void decrement() {
      if constexpr (N != std::tuple_size<iter_tuple>::value) {
        --std::get<N>(iters);
        decrement<N + 1>();
      }
    }

   public:
    using difference_type = std::ptrdiff_t;
    using value_type = zipped_iter<iter_tuple>;
    using reference = zipped_iter<iter_tuple> &;
    using pointer = iterator;
    using iterator_category = std::bidirectional_iterator_tag;

    constexpr iterator() = default;
    constexpr iterator(iter_tuple const &iters) : iters(iters) {}

    constexpr bool operator==(const iterator &rhs) const { return equal(rhs); }
    constexpr bool operator!=(const iterator &rhs) const { return !equal(rhs); }

    constexpr iterator &operator++() {
      increment();
      return *this;
    }
    constexpr iterator &operator--() {
      decrement();
      return *this;
    }

    constexpr auto &operator*() { return iters; }
  };

  constexpr iterator begin() const { return iterator{begin_cat()}; }
  constexpr iterator end() const { return iterator{end_cat()}; }

  constexpr std::reverse_iterator<iterator> rbegin() const {
    return std::make_reverse_iterator(end());
  }
  constexpr std::reverse_iterator<iterator> rend() const {
    return std::make_reverse_iterator(begin());
  }
};

template <class Iter_tuple> struct zipped_iter : Iter_tuple {
  constexpr zipped_iter(Iter_tuple const &__t) : Iter_tuple::tuple(__t) {}

  template <size_t N> friend constexpr auto &get(zipped_iter<Iter_tuple> &__z) {
    return *std::get<N>(__z);
  }

  template <size_t N> friend constexpr auto get(zipped_iter<Iter_tuple> &&__z) {
    return std::move(*std::get<N>(__z));
  }
};

}  // namespace workspace

namespace std {

template <size_t N, class Iter_tuple>
struct tuple_element<N, workspace::zipped_iter<Iter_tuple>> {
  using type = typename remove_reference<typename iterator_traits<
      typename tuple_element<N, Iter_tuple>::type>::reference>::type;
};

template <class Iter_tuple>
struct tuple_size<workspace::zipped_iter<Iter_tuple>> : tuple_size<Iter_tuple> {
};

}  // namespace std

namespace workspace {

template <class... Args> constexpr auto zip(Args &&... args) {
  return zipped<Args...>(std::forward<Args>(args)...);
}

template <class... Args>
constexpr auto zip(std::initializer_list<Args> &&... args) {
  return zipped<std::initializer_list<Args>...>(
      std::forward<std::initializer_list<Args>>(args)...);
}

}  // namespace workspace

#endif
