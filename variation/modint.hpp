#pragma once
#include <cassert>
#include <iostream>
template <auto &mod>  // compile-time defined modulo.
struct modint {
  using value_type = int_least64_t;
  constexpr static modint one() noexcept { return 1; }
  constexpr operator value_type() const noexcept { return value; }
  constexpr modint() noexcept = default;
  template <class int_type, std::enable_if_t<std::is_integral<int_type>::value,
                                             std::nullptr_t> = nullptr>
  constexpr modint(int_type n) noexcept : value((n %= mod) < 0 ? mod + n : n) {}
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
    return value = (int_fast64_t)value * rhs.value % mod, *this;
  }
  constexpr modint &operator/=(const modint &rhs) noexcept {
    return operator*=(rhs.inverse());
  }
  template <class int_type, std::enable_if_t<std::is_integral<int_type>::value,
                                             std::nullptr_t> = nullptr>
  constexpr modint operator+(const int_type &rhs) const noexcept {
    return modint{*this} += rhs;
  }
  constexpr modint operator+(const modint &rhs) const noexcept {
    return modint{*this} += rhs;
  }
  template <class int_type, std::enable_if_t<std::is_integral<int_type>::value,
                                             std::nullptr_t> = nullptr>
  constexpr modint operator-(const int_type &rhs) const noexcept {
    return modint{*this} -= rhs;
  }
  constexpr modint operator-(const modint &rhs) const noexcept {
    return modint{*this} -= rhs;
  }
  template <class int_type, std::enable_if_t<std::is_integral<int_type>::value,
                                             std::nullptr_t> = nullptr>
  constexpr modint operator*(const int_type &rhs) const noexcept {
    return modint{*this} *= rhs;
  }
  constexpr modint operator*(const modint &rhs) const noexcept {
    return modint{*this} *= rhs;
  }
  template <class int_type, std::enable_if_t<std::is_integral<int_type>::value,
                                             std::nullptr_t> = nullptr>
  constexpr modint operator/(const int_type &rhs) const noexcept {
    return modint{*this} /= rhs;
  }
  constexpr modint operator/(const modint &rhs) const noexcept {
    return modint{*this} /= rhs;
  }
  template <class int_type, std::enable_if_t<std::is_integral<int_type>::value,
                                             std::nullptr_t> = nullptr>
  constexpr friend modint operator+(const int_type &lhs,
                                    const modint &rhs) noexcept {
    return modint(lhs) + rhs;
  }
  template <class int_type, std::enable_if_t<std::is_integral<int_type>::value,
                                             std::nullptr_t> = nullptr>
  constexpr friend modint operator-(const int_type &lhs,
                                    const modint &rhs) noexcept {
    return modint(lhs) - rhs;
  }
  template <class int_type, std::enable_if_t<std::is_integral<int_type>::value,
                                             std::nullptr_t> = nullptr>
  constexpr friend modint operator*(const int_type &lhs,
                                    const modint &rhs) noexcept {
    return modint(lhs) * rhs;
  }
  template <class int_type, std::enable_if_t<std::is_integral<int_type>::value,
                                             std::nullptr_t> = nullptr>
  constexpr friend modint operator/(const int_type &lhs,
                                    const modint &rhs) noexcept {
    return modint(lhs) / rhs;
  }
  constexpr modint inverse() const noexcept {
    assert(value);
    value_type a{mod}, b{value}, u{}, v{1}, t{};
    while (b)
      t = a / b, a ^= b ^= (a -= t * b) ^= b, u ^= v ^= (u -= t * v) ^= v;
    return {u};
  }
  constexpr static modint pow(modint rhs, int_fast64_t e) noexcept {
    if (e < 0) e = e % (mod - 1) + mod - 1;
    modint res{1};
    while (e) {
      if (e & 1) res *= rhs;
      rhs *= rhs, e >>= 1;
    }
    return res;
  }
  friend std::ostream &operator<<(std::ostream &os,
                                  const modint &rhs) noexcept {
    return os << rhs.value;
  }
  friend std::istream &operator>>(std::istream &is, modint &rhs) noexcept {
    int_fast64_t value;
    rhs = (is >> value, value);
    return is;
  }

 protected:
  value_type value = 0;
};  // class modint
