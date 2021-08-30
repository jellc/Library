#pragma once

/**
 * @file subsets.hpp
 * @brief Subsets
 */

#include <vector>

namespace workspace {

namespace _subsets_impl {

template <class _Int, bool = std::is_integral<_Int>::value> class iterator {
  _Int __a, __b;
  bool __stop;

 public:
  using value_type = _Int;
  using difference_type = size_t;
  using iterator_category = std::forward_iterator_tag;
  using reference = value_type;
  using pointer = void;

  constexpr iterator() = default;
  constexpr iterator(_Int __x, bool __y) noexcept
      : __a(__x), __b(__x), __stop(__y) {}

  constexpr iterator &operator++() noexcept {
    assert(!__stop);
    __stop = (--__a &= __b) == __b;
    return *this;
  }
  constexpr iterator operator++(int) noexcept {
    assert(!__stop);
    iterator __tmp = *this;
    operator++();
    return __tmp;
  }

  constexpr value_type operator*() const noexcept {
    assert(!__stop);
    return __a;
  }

  constexpr bool operator==(const iterator &__x) const noexcept {
    return __a == __x.__a && __b == __x.__b && __stop == __x.__stop;
  }
  constexpr bool operator!=(const iterator &__x) const noexcept {
    return !operator==(__x);
  }
};

template <class _Container>
class iterator<_Container, false> : public iterator<int> {
  using base_type = iterator<int>;

  decltype(std::begin(std::declval<_Container>())) __p;

 public:
  using value_type = _Container;
  using difference_type = size_t;
  using iterator_category = std::forward_iterator_tag;
  using reference = value_type;
  using pointer = void;

  iterator() = default;
  iterator(const _Container &__c, bool __stop) noexcept
      : base_type((1 << __c.size()) - 1, __stop), __p(__c.begin()) {}

  iterator &operator++() noexcept {
    base_type::operator++();
    return *this;
  }
  iterator operator++(int) noexcept {
    auto __tmp = *this;
    base_type::operator++();
    return __tmp;
  }

  value_type operator*() const noexcept {
    static std::vector<std::decay_t<decltype(*__p)>> __v;
    __v.clear();

    auto __n = base_type::operator*();

    for (auto __i = __p; __n; __n >>= 1, ++__i)
      if (__n & 1) __v.emplace_back(*__i);

    return value_type(std::make_move_iterator(__v.begin()),
                      std::make_move_iterator(__v.end()));
  }

  bool operator==(const iterator &__x) const noexcept {
    return __p == __x.__p && base_type::operator==(__x);
  }
  bool operator!=(const iterator &__x) const noexcept {
    return !operator==(__x);
  }
};

}  // namespace _subsets_impl

template <class _Container> class subsets {
  _Container __c;

 public:
  using value_type = std::decay_t<_Container>;
  using iterator = _subsets_impl::iterator<value_type>;
  using const_iterator = iterator;
  using size_type = size_t;

  template <class _Tp> constexpr subsets(_Tp &&__x) noexcept : __c(__x) {}
  template <class _Tp>
  constexpr subsets(std::initializer_list<_Tp> __x) noexcept : __c(__x) {}

  constexpr iterator begin() const noexcept { return {__c, false}; }
  constexpr iterator end() const noexcept { return {__c, true}; }

  constexpr size_type size() const noexcept {
    if constexpr (std::is_convertible<_Container, size_type>::value)
      return 1 << __builtin_popcount(__c);
    else
      return 1 << __c.size();
  }
};

#if __cpp_deduction_guides >= 201606L

template <class _Tp> subsets(_Tp &&) -> subsets<_Tp>;

template <class _Tp>
subsets(std::initializer_list<_Tp>) -> subsets<std::vector<_Tp>>;

#endif

}  // namespace workspace
