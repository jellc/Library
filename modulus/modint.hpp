#pragma once
#include <cassert>
#include <iostream>

#include "utils/sfinae.hpp"

namespace workspace {

namespace internal {

template <auto Mod = 0, typename Mod_type = decltype(Mod)> struct modint_base {
  static_assert(is_integral_ext<decltype(Mod)>::value,
                "Mod must be integral type.");

  using mod_type = typename std::conditional<
      0 < Mod, typename std::add_const<Mod_type>::type, Mod_type>::type;
  static mod_type mod;

  using value_type = typename std::decay<mod_type>::type;

  constexpr operator value_type() const noexcept { return value; }

  constexpr static modint_base one() noexcept { return 1; }

  constexpr modint_base() noexcept = default;

  template <class int_type,
            typename std::enable_if<is_integral_ext<int_type>::value>::type * =
                nullptr>
  constexpr modint_base(int_type n) noexcept
      : value((n %= mod) < 0 ? mod + n : n) {}

  constexpr modint_base(bool n) noexcept : modint_base(int(n)) {}

  constexpr modint_base operator++(int) noexcept {
    modint_base t{*this};
    return operator+=(1), t;
  }

  constexpr modint_base operator--(int) noexcept {
    modint_base t{*this};
    return operator-=(1), t;
  }

  constexpr modint_base &operator++() noexcept { return operator+=(1); }

  constexpr modint_base &operator--() noexcept { return operator-=(1); }

  constexpr modint_base operator-() const noexcept {
    return value ? mod - value : 0;
  }

  constexpr modint_base &operator+=(const modint_base &rhs) noexcept {
    return (value += rhs.value) < mod ? 0 : value -= mod, *this;
  }

  constexpr modint_base &operator-=(const modint_base &rhs) noexcept {
    return (value += mod - rhs.value) < mod ? 0 : value -= mod, *this;
  }

  constexpr modint_base &operator*=(const modint_base &rhs) noexcept {
    return value = (typename multiplicable_uint<value_type>::type)value *
                   rhs.value % mod,
           *this;
  }

  constexpr modint_base &operator/=(const modint_base &rhs) noexcept {
    return operator*=(rhs.inverse());
  }

  template <class int_type>
  constexpr typename std::enable_if<is_integral_ext<int_type>::value,
                                    modint_base>::type
  operator+(const int_type &rhs) const noexcept {
    return modint_base{*this} += rhs;
  }

  constexpr modint_base operator+(const modint_base &rhs) const noexcept {
    return modint_base{*this} += rhs;
  }

  template <class int_type>
  constexpr typename std::enable_if<is_integral_ext<int_type>::value,
                                    modint_base>::type
  operator-(const int_type &rhs) const noexcept {
    return modint_base{*this} -= rhs;
  }

  constexpr modint_base operator-(const modint_base &rhs) const noexcept {
    return modint_base{*this} -= rhs;
  }

  template <class int_type>
  constexpr typename std::enable_if<is_integral_ext<int_type>::value,
                                    modint_base>::type
  operator*(const int_type &rhs) const noexcept {
    return modint_base{*this} *= rhs;
  }

  constexpr modint_base operator*(const modint_base &rhs) const noexcept {
    return modint_base{*this} *= rhs;
  }

  template <class int_type>
  constexpr typename std::enable_if<is_integral_ext<int_type>::value,
                                    modint_base>::type
  operator/(const int_type &rhs) const noexcept {
    return modint_base{*this} /= rhs;
  }

  constexpr modint_base operator/(const modint_base &rhs) const noexcept {
    return modint_base{*this} /= rhs;
  }

  template <class int_type>
  constexpr friend typename std::enable_if<is_integral_ext<int_type>::value,
                                           modint_base>::type
  operator+(const int_type &lhs, const modint_base &rhs) noexcept {
    return modint_base(lhs) + rhs;
  }

  template <class int_type>
  constexpr friend typename std::enable_if<is_integral_ext<int_type>::value,
                                           modint_base>::type
  operator-(const int_type &lhs, const modint_base &rhs) noexcept {
    return modint_base(lhs) - rhs;
  }

  template <class int_type>
  constexpr friend typename std::enable_if<is_integral_ext<int_type>::value,
                                           modint_base>::type
  operator*(const int_type &lhs, const modint_base &rhs) noexcept {
    return modint_base(lhs) * rhs;
  }

  template <class int_type>
  constexpr friend typename std::enable_if<is_integral_ext<int_type>::value,
                                           modint_base>::type
  operator/(const int_type &lhs, const modint_base &rhs) noexcept {
    return modint_base(lhs) / rhs;
  }

  constexpr modint_base inverse() const noexcept {
    assert(value);
    value_type a{mod}, b{value}, u{}, v{1}, t{};
    while (b)
      t = a / b, a ^= b ^= (a -= t * b) ^= b, u ^= v ^= (u -= t * v) ^= v;
    return {u};
  }

  template <class int_type>
  constexpr typename std::enable_if<is_integral_ext<int_type>::value,
                                    modint_base>::type
  power(int_type e) noexcept {
    return pow(*this, e);
  }

  template <class int_type>
  friend constexpr typename std::enable_if<is_integral_ext<int_type>::value,
                                           modint_base>::type
  pow(modint_base b, int_type e) noexcept {
    modint_base res{1};
    for (e < 0 ? b = b.inverse(), e = -e : 0; e; e >>= 1, b *= b)
      if (e & 1) res *= b;
    return res;
  }

  friend std::ostream &operator<<(std::ostream &os,
                                  const modint_base &rhs) noexcept {
    return os << rhs.value;
  }

  friend std::istream &operator>>(std::istream &is, modint_base &rhs) noexcept {
    intmax_t value;
    rhs = (is >> value, value);
    return is;
  }

 protected:
  value_type value = 0;
};

template <auto Mod, typename Mod_type>
typename modint_base<Mod, Mod_type>::mod_type modint_base<Mod, Mod_type>::mod =
    Mod;

}  // namespace internal

/*
 * @struct modint
 * @brief modular arithmetic.
 * @tparam Mod modulus
 */
template <auto Mod> struct modint : internal::modint_base<Mod> {
  static_assert(Mod > 0);
};

/*
 * @struct modint_runtime
 * @brief runtime modular arithmetic.
 * @tparam type_id uniquely assigned
 */
template <unsigned type_id = 0>
struct modint_runtime : internal::modint_base<-(signed)type_id> {};

// #define modint_newtype modint_runtime<__COUNTER__>

}  // namespace workspace
