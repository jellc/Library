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


# :heavy_check_mark: modulus/modint.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#06efba23b1f3a9b846a25c6b49f30348">modulus</a>
* <a href="{{ site.github.repository_url }}/blob/master/modulus/modint.hpp">View this file on GitHub</a>
    - Last commit date: 2020-08-24 22:40:12+09:00




## Required by

* :heavy_check_mark: <a href="../combinatorics/binomial.hpp.html">combinatorics/binomial.hpp</a>
* :heavy_check_mark: <a href="inverse.hpp.html">modulus/inverse.hpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aizu-online-judge/balls_and_boxes_4.test.cpp.html">test/aizu-online-judge/balls_and_boxes_4.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/library-checker/point_set_range_composite.test.cpp.html">test/library-checker/point_set_range_composite.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/library-checker/queue_operate_all_composite.test.cpp.html">test/library-checker/queue_operate_all_composite.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/library-checker/range_affine_range_sum.test.cpp.html">test/library-checker/range_affine_range_sum.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/library-checker/subset_convolution.test.cpp.html">test/library-checker/subset_convolution.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <cassert>
#include <iostream>
template <int_fast64_t mod = 0> // compile-time defined modulo.
struct modint
{
    static_assert(mod > 0);
    template <bool i32, class = void> struct modif { using value_type = int_least32_t; };
    template <class void_t> struct modif<false, void_t> { using value_type = int_least64_t; };
    using value_type = typename modif<mod < (1 << 30)>::value_type;
    constexpr static modint one() noexcept { return 1; }
    constexpr operator value_type() const noexcept { return value; }
    constexpr modint() noexcept = default;
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    constexpr modint(int_type n) noexcept : value((n %= mod) < 0 ? mod + n : n) {}
    constexpr modint operator++(int) noexcept { modint t{*this}; return operator+=(1), t; }
    constexpr modint operator--(int) noexcept { modint t{*this}; return operator-=(1), t; }
    constexpr modint &operator++() noexcept { return operator+=(1); }
    constexpr modint &operator--() noexcept { return operator-=(1); }
    constexpr modint operator-() const noexcept { return value ? mod - value : 0; }
    constexpr modint &operator+=(const modint &rhs) noexcept { return (value += rhs.value) < mod ? 0 : value -= mod, *this; }
    constexpr modint &operator-=(const modint &rhs) noexcept { return (value += mod - rhs.value) < mod ? 0 : value -= mod, *this; }
    constexpr modint &operator*=(const modint &rhs) noexcept { return value = (int_fast64_t)value * rhs.value % mod, *this; }
    constexpr modint &operator/=(const modint &rhs) noexcept { return operator*=(rhs.inverse()); }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    constexpr modint operator+(const int_type &rhs) const noexcept { return modint{*this} += rhs; }
    constexpr modint operator+(const modint &rhs) const noexcept { return modint{*this} += rhs; }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    constexpr modint operator-(const int_type &rhs) const noexcept { return modint{*this} -= rhs; }
    constexpr modint operator-(const modint &rhs) const noexcept { return modint{*this} -= rhs; }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    constexpr modint operator*(const int_type &rhs) const noexcept { return modint{*this} *= rhs; }
    constexpr modint operator*(const modint &rhs) const noexcept { return modint{*this} *= rhs; }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    constexpr modint operator/(const int_type &rhs) const noexcept { return modint{*this} /= rhs; }
    constexpr modint operator/(const modint &rhs) const noexcept { return modint{*this} /= rhs; }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    constexpr friend modint operator+(const int_type &lhs, const modint &rhs) noexcept { return modint(lhs) + rhs; }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    constexpr friend modint operator-(const int_type &lhs, const modint &rhs) noexcept { return modint(lhs) - rhs; }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    constexpr friend modint operator*(const int_type &lhs, const modint &rhs) noexcept { return modint(lhs) * rhs; }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    constexpr friend modint operator/(const int_type &lhs, const modint &rhs) noexcept { return modint(lhs) / rhs; }
    constexpr modint inverse() const noexcept
    {
        assert(value);
        value_type a{mod}, b{value}, u{}, v{1}, t{};
        while(b) t = a / b, a ^= b ^= (a -= t * b) ^= b, u ^= v ^= (u -= t * v) ^= v;
        return {u};
    }
    constexpr static modint pow(modint rhs, int_fast64_t e) noexcept
    {
        if(e < 0) e = e % (mod - 1) + mod - 1;
        modint res{1};
        while(e) { if(e & 1) res *= rhs; rhs *= rhs, e >>= 1; }
        return res;
    }
    friend std::ostream &operator<<(std::ostream &os, const modint &rhs) noexcept { return os << rhs.value; }
    friend std::istream &operator>>(std::istream &is, modint &rhs) noexcept { int_fast64_t value; rhs = (is >> value, value); return is; }
protected:
    value_type value = 0;
}; // class modint
template <> // runtime defined modulo as default(mod = 0).
struct modint<0>
{
    using value_type = int_fast64_t;
    static value_type &mod() noexcept { static value_type mod{}; return mod; }
    static modint one() noexcept { return 1; }
    operator value_type() const noexcept { return value; }
    modint() noexcept = default;
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    modint(int_type n) noexcept : value{ (assert(mod()), n %= mod() < 0 ? n + mod() : n) } {}
    modint operator++(int) noexcept { modint t{*this}; return operator+=(1), t; }
    modint operator--(int) noexcept { modint t{*this}; return operator-=(1), t; }
    modint &operator++() noexcept { return operator+=(1); }
    modint &operator--() noexcept { return operator-=(1); }
    modint operator-() const noexcept { return value ? mod() - value : 0; }
    modint &operator+=(const modint &rhs) noexcept { return (value += rhs.value) < mod() ? 0 : value -= mod(), *this; }
    modint &operator-=(const modint &rhs) noexcept { return (value += mod() - rhs.value) < mod() ? 0 : value -= mod(), *this; }
    modint &operator*=(const modint &rhs) noexcept { return (value *= rhs.value) %= mod(), *this; }
    modint &operator/=(const modint &rhs) noexcept { return operator*=(rhs.inverse()); }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    modint operator+(const int_type &rhs) const noexcept { return modint{*this} += rhs; }
    modint operator+(const modint &rhs) const noexcept { return modint{*this} += rhs; }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    modint operator-(const int_type &rhs) const noexcept { return modint{*this} -= rhs; }
    modint operator-(const modint &rhs) const noexcept { return modint{*this} -= rhs; }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    modint operator*(const int_type &rhs) const noexcept { return modint{*this} *= rhs; }
    modint operator*(const modint &rhs) const noexcept { return modint{*this} *= rhs; }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    modint operator/(const int_type &rhs) const noexcept { return modint{*this} /= rhs; }
    modint operator/(const modint &rhs) const noexcept { return modint{*this} /= rhs; }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    friend modint operator+(const int_type &lhs, const modint &rhs) noexcept { return modint(lhs) + rhs; }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    friend modint operator-(const int_type &lhs, const modint &rhs) noexcept { return modint(lhs) - rhs; }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    friend modint operator*(const int_type &lhs, const modint &rhs) noexcept { return modint(lhs) * rhs; }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    friend modint operator/(const int_type &lhs, const modint &rhs) noexcept { return modint(lhs) / rhs; }
    modint inverse() const noexcept
    {
        assert(mod() && value);
        value_type a{mod()}, b{value}, u{}, v{1}, t{};
        while(b) t = a / b, a ^= b ^= (a -= t * b) ^= b, u ^= v ^= (u -= t * v) ^= v;
        return {u};
    }
    static modint pow(modint rhs, int_fast64_t e) noexcept
    {
        if(e < 0) e = e % (mod() - 1) + mod() - 1;
        modint res{1};
        while(e) { if(e & 1) res *= rhs; rhs *= rhs, e >>= 1; }
        return res;
    }
    friend std::ostream &operator<<(std::ostream &os, const modint &rhs) noexcept { return os << rhs.value; }
    friend std::istream &operator>>(std::istream &is, modint &rhs) noexcept { int_fast64_t value; rhs = modint((is >> value, value)); return is; }
protected:
    value_type value = 0;
}; // class modint<0>
using modint_runtime = modint<0>;

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "modulus/modint.hpp"
#include <cassert>
#include <iostream>
template <int_fast64_t mod = 0> // compile-time defined modulo.
struct modint
{
    static_assert(mod > 0);
    template <bool i32, class = void> struct modif { using value_type = int_least32_t; };
    template <class void_t> struct modif<false, void_t> { using value_type = int_least64_t; };
    using value_type = typename modif<mod < (1 << 30)>::value_type;
    constexpr static modint one() noexcept { return 1; }
    constexpr operator value_type() const noexcept { return value; }
    constexpr modint() noexcept = default;
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    constexpr modint(int_type n) noexcept : value((n %= mod) < 0 ? mod + n : n) {}
    constexpr modint operator++(int) noexcept { modint t{*this}; return operator+=(1), t; }
    constexpr modint operator--(int) noexcept { modint t{*this}; return operator-=(1), t; }
    constexpr modint &operator++() noexcept { return operator+=(1); }
    constexpr modint &operator--() noexcept { return operator-=(1); }
    constexpr modint operator-() const noexcept { return value ? mod - value : 0; }
    constexpr modint &operator+=(const modint &rhs) noexcept { return (value += rhs.value) < mod ? 0 : value -= mod, *this; }
    constexpr modint &operator-=(const modint &rhs) noexcept { return (value += mod - rhs.value) < mod ? 0 : value -= mod, *this; }
    constexpr modint &operator*=(const modint &rhs) noexcept { return value = (int_fast64_t)value * rhs.value % mod, *this; }
    constexpr modint &operator/=(const modint &rhs) noexcept { return operator*=(rhs.inverse()); }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    constexpr modint operator+(const int_type &rhs) const noexcept { return modint{*this} += rhs; }
    constexpr modint operator+(const modint &rhs) const noexcept { return modint{*this} += rhs; }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    constexpr modint operator-(const int_type &rhs) const noexcept { return modint{*this} -= rhs; }
    constexpr modint operator-(const modint &rhs) const noexcept { return modint{*this} -= rhs; }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    constexpr modint operator*(const int_type &rhs) const noexcept { return modint{*this} *= rhs; }
    constexpr modint operator*(const modint &rhs) const noexcept { return modint{*this} *= rhs; }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    constexpr modint operator/(const int_type &rhs) const noexcept { return modint{*this} /= rhs; }
    constexpr modint operator/(const modint &rhs) const noexcept { return modint{*this} /= rhs; }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    constexpr friend modint operator+(const int_type &lhs, const modint &rhs) noexcept { return modint(lhs) + rhs; }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    constexpr friend modint operator-(const int_type &lhs, const modint &rhs) noexcept { return modint(lhs) - rhs; }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    constexpr friend modint operator*(const int_type &lhs, const modint &rhs) noexcept { return modint(lhs) * rhs; }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    constexpr friend modint operator/(const int_type &lhs, const modint &rhs) noexcept { return modint(lhs) / rhs; }
    constexpr modint inverse() const noexcept
    {
        assert(value);
        value_type a{mod}, b{value}, u{}, v{1}, t{};
        while(b) t = a / b, a ^= b ^= (a -= t * b) ^= b, u ^= v ^= (u -= t * v) ^= v;
        return {u};
    }
    constexpr static modint pow(modint rhs, int_fast64_t e) noexcept
    {
        if(e < 0) e = e % (mod - 1) + mod - 1;
        modint res{1};
        while(e) { if(e & 1) res *= rhs; rhs *= rhs, e >>= 1; }
        return res;
    }
    friend std::ostream &operator<<(std::ostream &os, const modint &rhs) noexcept { return os << rhs.value; }
    friend std::istream &operator>>(std::istream &is, modint &rhs) noexcept { int_fast64_t value; rhs = (is >> value, value); return is; }
protected:
    value_type value = 0;
}; // class modint
template <> // runtime defined modulo as default(mod = 0).
struct modint<0>
{
    using value_type = int_fast64_t;
    static value_type &mod() noexcept { static value_type mod{}; return mod; }
    static modint one() noexcept { return 1; }
    operator value_type() const noexcept { return value; }
    modint() noexcept = default;
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    modint(int_type n) noexcept : value{ (assert(mod()), n %= mod() < 0 ? n + mod() : n) } {}
    modint operator++(int) noexcept { modint t{*this}; return operator+=(1), t; }
    modint operator--(int) noexcept { modint t{*this}; return operator-=(1), t; }
    modint &operator++() noexcept { return operator+=(1); }
    modint &operator--() noexcept { return operator-=(1); }
    modint operator-() const noexcept { return value ? mod() - value : 0; }
    modint &operator+=(const modint &rhs) noexcept { return (value += rhs.value) < mod() ? 0 : value -= mod(), *this; }
    modint &operator-=(const modint &rhs) noexcept { return (value += mod() - rhs.value) < mod() ? 0 : value -= mod(), *this; }
    modint &operator*=(const modint &rhs) noexcept { return (value *= rhs.value) %= mod(), *this; }
    modint &operator/=(const modint &rhs) noexcept { return operator*=(rhs.inverse()); }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    modint operator+(const int_type &rhs) const noexcept { return modint{*this} += rhs; }
    modint operator+(const modint &rhs) const noexcept { return modint{*this} += rhs; }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    modint operator-(const int_type &rhs) const noexcept { return modint{*this} -= rhs; }
    modint operator-(const modint &rhs) const noexcept { return modint{*this} -= rhs; }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    modint operator*(const int_type &rhs) const noexcept { return modint{*this} *= rhs; }
    modint operator*(const modint &rhs) const noexcept { return modint{*this} *= rhs; }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    modint operator/(const int_type &rhs) const noexcept { return modint{*this} /= rhs; }
    modint operator/(const modint &rhs) const noexcept { return modint{*this} /= rhs; }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    friend modint operator+(const int_type &lhs, const modint &rhs) noexcept { return modint(lhs) + rhs; }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    friend modint operator-(const int_type &lhs, const modint &rhs) noexcept { return modint(lhs) - rhs; }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    friend modint operator*(const int_type &lhs, const modint &rhs) noexcept { return modint(lhs) * rhs; }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    friend modint operator/(const int_type &lhs, const modint &rhs) noexcept { return modint(lhs) / rhs; }
    modint inverse() const noexcept
    {
        assert(mod() && value);
        value_type a{mod()}, b{value}, u{}, v{1}, t{};
        while(b) t = a / b, a ^= b ^= (a -= t * b) ^= b, u ^= v ^= (u -= t * v) ^= v;
        return {u};
    }
    static modint pow(modint rhs, int_fast64_t e) noexcept
    {
        if(e < 0) e = e % (mod() - 1) + mod() - 1;
        modint res{1};
        while(e) { if(e & 1) res *= rhs; rhs *= rhs, e >>= 1; }
        return res;
    }
    friend std::ostream &operator<<(std::ostream &os, const modint &rhs) noexcept { return os << rhs.value; }
    friend std::istream &operator>>(std::istream &is, modint &rhs) noexcept { int_fast64_t value; rhs = modint((is >> value, value)); return is; }
protected:
    value_type value = 0;
}; // class modint<0>
using modint_runtime = modint<0>;

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

