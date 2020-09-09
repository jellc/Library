---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :heavy_check_mark: combinatorics/binomial.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#ac1ed416572b96a9f5d69740d174ef3d">combinatorics</a>
* <a href="{{ site.github.repository_url }}/blob/master/combinatorics/binomial.hpp">View this file on GitHub</a>
    - Last commit date: 2020-09-09 13:38:41+09:00




## Depends on

* :heavy_check_mark: <a href="factorial.hpp.html">combinatorics/factorial.hpp</a>
* :heavy_check_mark: <a href="../modulus/inverse.hpp.html">modulus/inverse.hpp</a>
* :heavy_check_mark: <a href="../modulus/modint.hpp.html">modulus/modint.hpp</a>
* :heavy_check_mark: <a href="../utils/sfinae.hpp.html">utils/sfinae.hpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aizu-online-judge/balls_and_boxes_4.test.cpp.html">test/aizu-online-judge/balls_and_boxes_4.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include "factorial.hpp"
#include "modulus/inverse.hpp"
#include "modulus/modint.hpp"
template <class, class = int> struct binomial;
template <class Modint>
struct binomial<Modint, decltype((void *)Modint::mod, 0)> {
  using value_type = Modint;
  struct mulinv_Op {
    value_type operator()(const value_type &f, const size_t &n) const {
      return f * inv(n);
    }
  };
  static inverse<value_type> inv;
  static factorial<value_type, mulinv_Op> fact_inv;
  static factorial<value_type> fact;
  value_type operator()(const int &n, const int &k) {
    return fact_inv(k) * fact_inv(n - k) * fact(n);
  }
};
template <class Modint>
inverse<Modint> binomial<Modint, decltype((void *)Modint::mod, 0)>::inv;
template <class Modint>
factorial<Modint,
          class binomial<Modint, decltype((void *)Modint::mod, 0)>::mulinv_Op>
    binomial<Modint, decltype((void *)Modint::mod, 0)>::fact_inv {
  1
};
template <class Modint>
factorial<Modint> binomial<Modint, decltype((void *)Modint::mod, 0)>::fact;

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "combinatorics/factorial.hpp"
#include <functional>
#include <vector>
template <class T, class Op = std::multiplies<T>>
class factorial
{
    std::vector<T> fact;
    Op op;
public:
    factorial(T init = 1, Op op = Op()) : fact{init}, op{op} {}
    T operator()(const int &n)
    {
        if(n < 0) return 0;
        for(int m(fact.size()); m <= n; ++m) fact.emplace_back(op(fact.back(), m));
        return fact[n];
    }
}; // class factorial
#line 3 "modulus/inverse.hpp"

#line 2 "modulus/modint.hpp"
#include <cassert>
#include <iostream>

#line 2 "utils/sfinae.hpp"
#include <cstdint>
#include <type_traits>

template <class type, template <class> class trait>
using enable_if_trait_type = typename std::enable_if<trait<type>::value>::type;

template <class Container>
using element_type = typename std::decay<decltype(
    *std::begin(std::declval<Container&>()))>::type;

template <class T, class = void> struct is_integral_ext : std::false_type {};
template <class T>
struct is_integral_ext<
    T, typename std::enable_if<std::is_integral<T>::value>::type>
    : std::true_type {};
template <> struct is_integral_ext<__int128_t> : std::true_type {};
template <> struct is_integral_ext<__uint128_t> : std::true_type {};
template <class T>
constexpr static bool is_integral_ext_v = is_integral_ext<T>::value;

template <typename T, typename = void> struct multiplicable_uint {
  using type = uint_least32_t;
};
template <typename T>
struct multiplicable_uint<T, typename std::enable_if<(2 < sizeof(T))>::type> {
  using type = uint_least64_t;
};
template <typename T>
struct multiplicable_uint<T, typename std::enable_if<(4 < sizeof(T))>::type> {
  using type = __uint128_t;
};
#line 6 "modulus/modint.hpp"

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
    modint res{1}, p{*this};
    for (modint p{value}; e; e >>= 1, p *= p) {
      if (e & 1) res *= p;
    }
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
#line 5 "modulus/inverse.hpp"
template <class, class = int> struct inverse;
// mod must be prime.
template <class Modint>
struct inverse<Modint, decltype((void *)Modint::mod, 0)> {
  using value_type = Modint;
  constexpr value_type operator()(int n) const {
    constexpr int_fast64_t mod = value_type::mod;
    assert(n %= mod);
    if (n < 0) n += mod;
    if (inv.empty()) inv = {1, mod != 1};
    for (int m(inv.size()); m <= n; ++m)
      inv.emplace_back(mod / m * -inv[mod % m]);
    return inv[n];
  }

 private:
  static std::vector<value_type> inv;
};
template <class Modint>
std::vector<Modint> inverse<Modint, decltype((void *)Modint::mod, 0)>::inv;
#line 5 "combinatorics/binomial.hpp"
template <class, class = int> struct binomial;
template <class Modint>
struct binomial<Modint, decltype((void *)Modint::mod, 0)> {
  using value_type = Modint;
  struct mulinv_Op {
    value_type operator()(const value_type &f, const size_t &n) const {
      return f * inv(n);
    }
  };
  static inverse<value_type> inv;
  static factorial<value_type, mulinv_Op> fact_inv;
  static factorial<value_type> fact;
  value_type operator()(const int &n, const int &k) {
    return fact_inv(k) * fact_inv(n - k) * fact(n);
  }
};
template <class Modint>
inverse<Modint> binomial<Modint, decltype((void *)Modint::mod, 0)>::inv;
template <class Modint>
factorial<Modint,
          class binomial<Modint, decltype((void *)Modint::mod, 0)>::mulinv_Op>
    binomial<Modint, decltype((void *)Modint::mod, 0)>::fact_inv {
  1
};
template <class Modint>
factorial<Modint> binomial<Modint, decltype((void *)Modint::mod, 0)>::fact;

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

