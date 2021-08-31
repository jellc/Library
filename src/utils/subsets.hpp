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
  using difference_type = std::ptrdiff_t;
  using value_type = _Int;
  using pointer = void;
  using reference = value_type;
  using iterator_category = std::bidirectional_iterator_tag;

  constexpr iterator() = default;
  constexpr iterator(_Int __x, bool __y) noexcept
      : __a(0), __b(__x), __stop(__y) {}

  constexpr iterator &operator++() noexcept {
    assert(!__stop);
    __stop = !(++(__a |= ~__b) &= __b);
    return *this;
  }
  constexpr iterator operator++(int) noexcept {
    auto __tmp = *this;
    operator++();
    return __tmp;
  }

  constexpr iterator &operator--() noexcept {
    assert(__a || __stop);
    --__a &= __b, __stop = false;
    return *this;
  }
  constexpr iterator operator--(int) noexcept {
    auto __tmp = *this;
    operator--();
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
  using _Base = iterator<int>;

  decltype(std::begin(std::declval<_Container>())) __p;

 public:
  using difference_type = std::ptrdiff_t;
  using value_type = _Container;
  using pointer = void;
  using reference = value_type;
  using iterator_category = std::bidirectional_iterator_tag;

  iterator() = default;
  iterator(const _Container &__c, bool __stop) noexcept
      : _Base((1 << __c.size()) - 1, __stop), __p(__c.begin()) {}

  iterator &operator++() noexcept {
    _Base::operator++();
    return *this;
  }
  iterator operator++(int) noexcept {
    auto __tmp = *this;
    _Base::operator++();
    return __tmp;
  }

  iterator &operator--() noexcept {
    _Base::operator--();
    return *this;
  }
  iterator operator--(int) noexcept {
    auto __tmp = *this;
    _Base::operator--();
    return __tmp;
  }

  value_type operator*() const noexcept {
    static std::vector<std::decay_t<decltype(*__p)>> __v;
    __v.clear();

    auto __n = _Base::operator*();
    for (auto __i = __p; __n; __n >>= 1, ++__i)
      if (__n & 1) __v.emplace_back(*__i);

    return value_type(std::make_move_iterator(__v.begin()),
                      std::make_move_iterator(__v.end()));
  }

  bool operator==(const iterator &__x) const noexcept {
    return __p == __x.__p && _Base::operator==(__x);
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
  using reference = value_type;

  using difference_type = std::ptrdiff_t;
  using size_type = std::size_t;

  using iterator = _subsets_impl::iterator<value_type>;
  using const_iterator = iterator;

  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = reverse_iterator;

  template <class _Tp>
  constexpr subsets(_Tp &&__x) noexcept : __c(std::forward<_Tp>(__x)) {}

  template <class _Tp>
  constexpr subsets(std::initializer_list<_Tp> __x) noexcept : __c(__x) {}

  constexpr iterator begin() const noexcept { return {__c, false}; }
  constexpr const_iterator cbegin() const noexcept { return begin(); }

  constexpr iterator end() const noexcept { return {__c, true}; }
  constexpr const_iterator cend() const noexcept { return end(); }

  constexpr reverse_iterator rbegin() const noexcept {
    return reverse_iterator{end()};
  }
  constexpr const_reverse_iterator crbegin() const noexcept { return rbegin(); }

  constexpr reverse_iterator rend() const noexcept {
    return reverse_iterator{begin()};
  }
  constexpr const_reverse_iterator crend() const noexcept { return rend(); }

  constexpr bool empty() const noexcept { return false; }

#if __cplusplus >= 201703L
  constexpr size_type size() const noexcept {
    if constexpr (std::is_convertible<_Container, size_type>::value)
      return 1 << __builtin_popcount(__c);
    else
      return 1 << __c.size();
  }
#endif
};

#if __cpp_deduction_guides >= 201606L

template <class _Tp> subsets(_Tp &&) -> subsets<_Tp>;

template <class _Tp>
subsets(std::initializer_list<_Tp>) -> subsets<std::vector<_Tp>>;

#endif

}  // namespace workspace
