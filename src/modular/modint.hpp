#pragma once

/**
 * @file modint.hpp
 *
 * @brief Modular Arithmetic
 */

#include <cassert>
#include <iostream>
#include <vector>

#include "src/number_theory/sqrt_mod.hpp"
#include "src/utils/sfinae.hpp"

namespace workspace {

namespace _modint_impl {

template <auto _Mod, unsigned _Storage> struct modint {
  static_assert(is_integral_ext<decltype(_Mod)>::value,
                "_Mod must be integral type.");

  using mod_type = std::make_signed_t<typename std::conditional<
      0 < _Mod, std::add_const_t<decltype(_Mod)>, decltype(_Mod)>::type>;

  using value_type = std::decay_t<mod_type>;

  using mul_type = typename multiplicable_uint<value_type>::type;

  // Modulus
  static mod_type mod;

  static unsigned storage;

 private:
  value_type value = 0;

  struct direct_ctor_t {};
  constexpr static direct_ctor_t direct_ctor_tag{};

  // Direct constructor
  template <class _Tp>
  constexpr modint(_Tp __n, direct_ctor_t) noexcept : value(__n) {}

 public:
  constexpr modint() noexcept = default;

  template <class _Tp, typename = std::enable_if_t<is_integral_ext<_Tp>::value>>
  constexpr modint(_Tp __n) noexcept
      : value((__n %= mod) < 0 ? __n += mod : __n) {}

  constexpr modint(bool __n) noexcept : value(__n) {}

  constexpr operator value_type() const noexcept { return value; }

  // unary operators {{
  constexpr modint operator++(int) noexcept {
    modint __t{*this};
    operator++();
    return __t;
  }

  constexpr modint operator--(int) noexcept {
    modint __t{*this};
    operator--();
    return __t;
  }

  constexpr modint &operator++() noexcept {
    if (++value == mod) value = 0;
    return *this;
  }

  constexpr modint &operator--() noexcept {
    if (!value)
      value = mod - 1;
    else
      --value;
    return *this;
  }

  constexpr modint operator+() const noexcept { return *this; }

  constexpr modint operator-() const noexcept {
    return {value ? mod - value : 0, direct_ctor_tag};
  }

  // }} unary operators

  // operator+= {{

  constexpr modint &operator+=(const modint &__x) noexcept {
    if ((value += __x.value) >= mod) value -= mod;
    return *this;
  }

  template <class _Tp>
  constexpr typename std::enable_if<is_integral_ext<_Tp>::value, modint>::type &
  operator+=(_Tp const &__x) noexcept {
    if (((value += __x) %= mod) < 0) value += mod;
    return *this;
  }

  // }} operator+=

  // operator+ {{

  template <class _Tp>
  constexpr typename std::enable_if<is_integral_ext<_Tp>::value, modint>::type
  operator+(_Tp const &__x) const noexcept {
    return modint{*this} += __x;
  }

  constexpr modint operator+(modint __x) const noexcept { return __x += *this; }

  template <class _Tp>
  constexpr friend
      typename std::enable_if<is_integral_ext<_Tp>::value, modint>::type
      operator+(_Tp const &__x, modint __y) noexcept {
    return __y += __x;
  }

  // }} operator+

  // operator-= {{

  constexpr modint &operator-=(const modint &__x) noexcept {
    if ((value -= __x.value) < 0) value += mod;
    return *this;
  }

  template <class _Tp>
  constexpr typename std::enable_if<is_integral_ext<_Tp>::value, modint>::type &
  operator-=(_Tp __x) noexcept {
    if (((value -= __x) %= mod) < 0) value += mod;
    return *this;
  }

  // }} operator-=

  // operator- {{

  template <class _Tp>
  constexpr typename std::enable_if<is_integral_ext<_Tp>::value, modint>::type
  operator-(_Tp const &__x) const noexcept {
    return modint{*this} -= __x;
  }

  constexpr modint operator-(const modint &__x) const noexcept {
    return modint{*this} -= __x;
  }

  template <class _Tp>
  constexpr friend
      typename std::enable_if<is_integral_ext<_Tp>::value, modint>::type
      operator-(_Tp __x, const modint &__y) noexcept {
    if (((__x -= __y.value) %= mod) < 0) __x += mod;
    return {__x, direct_ctor_tag};
  }

  // }} operator-

  // operator*= {{

  constexpr modint &operator*=(const modint &__x) noexcept {
    value =
        static_cast<value_type>(value * static_cast<mul_type>(__x.value) % mod);
    return *this;
  }

  template <class _Tp>
  constexpr typename std::enable_if<is_integral_ext<_Tp>::value, modint>::type &
  operator*=(_Tp __x) noexcept {
    value = static_cast<value_type>(
        value * mul_type((__x %= mod) < 0 ? __x + mod : __x) % mod);
    return *this;
  }

  // }} operator*=

  // operator* {{

  constexpr modint operator*(const modint &__x) const noexcept {
    return {static_cast<mul_type>(value) * __x.value % mod, direct_ctor_tag};
  }

  template <class _Tp>
  constexpr typename std::enable_if<is_integral_ext<_Tp>::value, modint>::type
  operator*(_Tp __x) const noexcept {
    __x %= mod;
    if (__x < 0) __x += mod;
    return {static_cast<mul_type>(value) * __x % mod, direct_ctor_tag};
  }

  template <class _Tp>
  constexpr friend
      typename std::enable_if<is_integral_ext<_Tp>::value, modint>::type
      operator*(_Tp __x, const modint &__y) noexcept {
    __x %= mod;
    if (__x < 0) __x += mod;
    return {static_cast<mul_type>(__x) * __y.value % mod, direct_ctor_tag};
  }

  // }} operator*

 protected:
  static value_type _mem(value_type __x) {
    static std::vector<value_type> __m{0, 1};
    static value_type __i = (__m.reserve(_Storage), 1);
    while (__i < __x) {
      ++__i;
      __m.emplace_back(mod - mul_type(mod / __i) * __m[mod % __i] % mod);
    }
    return __m[__x];
  }

  template <class _Tp>
  constexpr static
      typename std::enable_if<is_integral_ext<_Tp>::value, value_type>::type
      _div(mul_type __r, _Tp __x) noexcept {
    assert(__x != _Tp(0));
    if (!__r) return 0;

    std::make_signed_t<_Tp> __v{};
    bool __neg = __x < 0 ? __x = -__x, true : false;

    if (static_cast<decltype(storage)>(__x) < storage)
      __v = _mem(__x);
    else {
      decltype(__v) __y{mod}, __u{1}, __t;

      while (__x)
        __t = __y / __x, __y ^= __x ^= (__y -= __t * __x) ^= __x,
        __v ^= __u ^= (__v -= __t * __u) ^= __u;

      if (__y < 0) __neg ^= 1;
    }

    if (__neg)
      __v = 0 < __v ? mod - __v : -__v;
    else if (__v < 0)
      __v += mod;

    return __r == mul_type(1) ? static_cast<value_type>(__v)
                              : static_cast<value_type>(__r * __v % mod);
  }

 public:
  // operator/= {{

  constexpr modint &operator/=(const modint &__x) noexcept {
    if (value) value = _div(value, __x.value);
    return *this;
  }

  template <class _Tp>
  constexpr typename std::enable_if<is_integral_ext<_Tp>::value, modint>::type &
  operator/=(_Tp __x) noexcept {
    if (value) value = _div(value, __x %= mod);
    return *this;
  }

  // }} operator/=

  // operator/ {{

  constexpr modint operator/(const modint &__x) const noexcept {
    if (!value) return {};
    return {_div(value, __x.value), direct_ctor_tag};
  }

  template <class _Tp>
  constexpr typename std::enable_if<is_integral_ext<_Tp>::value, modint>::type
  operator/(_Tp __x) const noexcept {
    if (!value) return {};
    return {_div(value, __x %= mod), direct_ctor_tag};
  }

  template <class _Tp>
  constexpr friend
      typename std::enable_if<is_integral_ext<_Tp>::value, modint>::type
      operator/(_Tp __x, const modint &__y) noexcept {
    if (!__x) return {};
    if ((__x %= mod) < 0) __x += mod;
    return {_div(__x, __y.value), direct_ctor_tag};
  }

  // }} operator/

  constexpr modint inv() const noexcept { return _div(1, value); }

  template <class _Tp>
  constexpr std::__enable_if_t<is_integral_ext<_Tp>::value, modint> pow(
      _Tp __e) const noexcept {
    modint __r{1, direct_ctor_tag};

    for (modint __b{__e < 0 ? __e = -__e, _div(1, value) : value,
                              direct_ctor_tag};
         __e; __e >>= 1, __b *= __b)
      if (__e & 1) __r *= __b;

    return __r;
  }

  template <class _Tp>
  friend constexpr std::__enable_if_t<is_integral_ext<_Tp>::value, modint> pow(
      modint __b, _Tp __e) noexcept {
    if (__e < 0) {
      __e = -__e;
      __b.value = _div(1, __b.value);
    }

    modint __r{1, direct_ctor_tag};

    for (; __e; __e >>= 1, __b *= __b)
      if (__e & 1) __r *= __b;

    return __r;
  }

  constexpr modint sqrt() const noexcept {
    return {sqrt_mod(value, mod), direct_ctor_tag};
  }

  friend constexpr modint sqrt(const modint &__x) noexcept {
    return {sqrt_mod(__x.value, mod), direct_ctor_tag};
  }

  template <class _Os>
  friend _Os &operator<<(_Os &__os, const modint &__x) noexcept {
    return __os << __x.value;
  }

  friend std::istream &operator>>(std::istream &__is, modint &__x) noexcept {
    std::string __s;
    __is >> __s;
    bool __neg = false;
    if (__s.front() == '-') {
      __neg = true;
      __s.erase(__s.begin());
    }
    __x = 0;
    for (char __c : __s) __x = __x * 10 + (__c - '0');
    if (__neg) __x = -__x;
    return __is;
  }
};

template <auto _Mod, unsigned _Storage>
typename modint<_Mod, _Storage>::mod_type modint<_Mod, _Storage>::mod =
    _Mod > 0 ? _Mod : 0;

template <auto _Mod, unsigned _Storage>
unsigned modint<_Mod, _Storage>::storage = _Storage;

}  // namespace _modint_impl

template <auto _Mod, unsigned _Storage = 0,
          typename = std::enable_if_t<(_Mod > 0)>>
using modint = _modint_impl::modint<_Mod, _Storage>;

template <unsigned _Id = 0>
using modint_runtime = _modint_impl::modint<-(signed)_Id, 0>;

}  // namespace workspace
