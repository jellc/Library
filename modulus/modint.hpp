#pragma once
#include <cassert>
#include <iostream>

#include "utils/sfinae.hpp"

template <auto Mod = 0, typename Mod_type = decltype(Mod)> struct modint {
  static_assert(is_integral_ext<decltype(Mod)>::value,
                "Mod must be integral type.");
  static_assert(!(Mod < 0), "Mod must be non-negative.");

  using mod_type = typename std::conditional<
      Mod != 0, typename std::add_const<Mod_type>::type, Mod_type>::type;
  static mod_type mod;

  using value_type = typename std::decay<mod_type>::type;

  constexpr operator value_type() const noexcept { return value; }

  constexpr static modint one() noexcept { return 1; }

  constexpr modint() noexcept = default;

  template <class int_type,
            typename std::enable_if<is_integral_ext<int_type>::value>::type * =
                nullptr>
  constexpr modint(int_type n) noexcept : value((n %= mod) < 0 ? mod + n : n) {}

  constexpr modint(bool n) noexcept : modint(int(n)) {}

  constexpr modint operator++(int) noexcept {
    modint t{*this};
    return operator+=(1), t;
  }

  constexpr modint operator--(int) noexcept {
    modint t{*this};
    return operator-=(1), t;
  }

  constexpr modint &operator++() noexcept { return operator+=(1); }

  constexpr modint &operator--() noexcept { return operator-=(1); }

  constexpr modint operator-() const noexcept {
    return value ? mod - value : 0;
  }

  constexpr modint &operator+=(const modint &rhs) noexcept {
    return (value += rhs.value) < mod ? 0 : value -= mod, *this;
  }

  constexpr modint &operator-=(const modint &rhs) noexcept {
    return (value += mod - rhs.value) < mod ? 0 : value -= mod, *this;
  }

  constexpr modint &operator*=(const modint &rhs) noexcept {
    return value = (typename multiplicable_uint<value_type>::type)value *
                   rhs.value % mod,
           *this;
  }

  constexpr modint &operator/=(const modint &rhs) noexcept {
    return operator*=(rhs.inverse());
  }

  template <class int_type>
  constexpr
      typename std::enable_if<is_integral_ext<int_type>::value, modint>::type
      operator+(const int_type &rhs) const noexcept {
    return modint{*this} += rhs;
  }

  constexpr modint operator+(const modint &rhs) const noexcept {
    return modint{*this} += rhs;
  }

  template <class int_type>
  constexpr
      typename std::enable_if<is_integral_ext<int_type>::value, modint>::type
      operator-(const int_type &rhs) const noexcept {
    return modint{*this} -= rhs;
  }

  constexpr modint operator-(const modint &rhs) const noexcept {
    return modint{*this} -= rhs;
  }

  template <class int_type>
  constexpr
      typename std::enable_if<is_integral_ext<int_type>::value, modint>::type
      operator*(const int_type &rhs) const noexcept {
    return modint{*this} *= rhs;
  }

  constexpr modint operator*(const modint &rhs) const noexcept {
    return modint{*this} *= rhs;
  }

  template <class int_type>
  constexpr
      typename std::enable_if<is_integral_ext<int_type>::value, modint>::type
      operator/(const int_type &rhs) const noexcept {
    return modint{*this} /= rhs;
  }

  constexpr modint operator/(const modint &rhs) const noexcept {
    return modint{*this} /= rhs;
  }

  template <class int_type>
  constexpr friend
      typename std::enable_if<is_integral_ext<int_type>::value, modint>::type
      operator+(const int_type &lhs, const modint &rhs) noexcept {
    return modint(lhs) + rhs;
  }

  template <class int_type>
  constexpr friend
      typename std::enable_if<is_integral_ext<int_type>::value, modint>::type
      operator-(const int_type &lhs, const modint &rhs) noexcept {
    return modint(lhs) - rhs;
  }

  template <class int_type>
  constexpr friend
      typename std::enable_if<is_integral_ext<int_type>::value, modint>::type
      operator*(const int_type &lhs, const modint &rhs) noexcept {
    return modint(lhs) * rhs;
  }

  template <class int_type>
  constexpr friend
      typename std::enable_if<is_integral_ext<int_type>::value, modint>::type
      operator/(const int_type &lhs, const modint &rhs) noexcept {
    return modint(lhs) / rhs;
  }

  constexpr modint inverse() const noexcept {
    assert(value);
    value_type a{mod}, b{value}, u{}, v{1}, t{};
    while (b)
      t = a / b, a ^= b ^= (a -= t * b) ^= b, u ^= v ^= (u -= t * v) ^= v;
    return {u};
  }

  template <class int_type>
  constexpr
      typename std::enable_if<is_integral_ext<int_type>::value, modint>::type
      power(int_type e) noexcept {
    if (e < 0) e = e % (mod - 1) + mod - 1;
    modint res{1};
    for (modint p{value}; e; e >>= 1, p *= p) {
      if (e & 1) res *= p;
    }
    return res;
  }

  template <class int_type>
  friend constexpr
      typename std::enable_if<is_integral_ext<int_type>::value, modint>::type
      pow(modint b, int_type e) noexcept {
    modint res{1};
    for ((e %= mod - 1) < 0 ? e += mod - 1 : 0; e; e >>= 1, b *= b)
      if (e & 1) res *= b;
    return res;
  }

  friend std::ostream &operator<<(std::ostream &os,
                                  const modint &rhs) noexcept {
    return os << rhs.value;
  }

  friend std::istream &operator>>(std::istream &is, modint &rhs) noexcept {
    intmax_t value;
    rhs = (is >> value, value);
    return is;
  }

 protected:
  value_type value = 0;
};

template <auto Mod, typename Mod_type>
typename modint<Mod, Mod_type>::mod_type modint<Mod, Mod_type>::mod = Mod;

using modint_runtime = modint<0>;
