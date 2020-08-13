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
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :warning: modulus/compile-time/modint.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#6a766f280bf2a78039d52a3337357612">modulus/compile-time</a>
* <a href="{{ site.github.repository_url }}/blob/master/modulus/compile-time/modint.hpp">View this file on GitHub</a>
    - Last commit date: 2020-08-08 23:17:57+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <cassert>
#include <iostream>
template <int_fast64_t mod>
struct modint
{
    using value_type = int_fast64_t;
    static constexpr modint one() noexcept { return 1; }
    constexpr modint() noexcept : val(0) {}
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    constexpr modint(int_type _val) noexcept : val((_val %= mod) < 0 ? mod + _val : _val) {}
    constexpr value_type value() const noexcept { return val; }
    constexpr modint operator++(int) noexcept { modint t{*this}; return operator+=(1), t; }
    constexpr modint operator--(int) noexcept { modint t{*this}; return operator-=(1), t; }
    constexpr modint &operator++() noexcept { return operator+=(1); }
    constexpr modint &operator--() noexcept { return operator-=(1); }
    constexpr modint operator-() const noexcept { return modint(-val); }
    constexpr modint &operator+=(const modint &rhs) noexcept { return (val += rhs.val) < mod ? 0 : val -= mod, *this; }
    constexpr modint &operator-=(const modint &rhs) noexcept { return (val += mod - rhs.val) < mod ? 0 : val -= mod, *this; }
    constexpr modint &operator*=(const modint &rhs) noexcept { return val = val * rhs.val % mod, *this; }
    constexpr modint &operator/=(const modint &rhs) noexcept { return *this *= inverse(rhs); }
    constexpr modint operator+(const modint &rhs) const noexcept { return modint(*this) += rhs; }
    constexpr modint operator-(const modint &rhs) const noexcept { return modint(*this) -= rhs; }
    constexpr modint operator*(const modint &rhs) const noexcept { return modint(*this) *= rhs; }
    constexpr modint operator/(const modint &rhs) const noexcept { return modint(*this) /= rhs; }
    constexpr bool operator==(const modint &rhs) const noexcept { return val == rhs.val; }
    constexpr bool operator!=(const modint &rhs) const noexcept { return val != rhs.val; }
    constexpr bool operator!() const noexcept { return !val; }
    friend constexpr modint operator+(value_type lhs, modint rhs) noexcept { return modint(lhs) + rhs; }
    friend constexpr modint operator-(value_type lhs, modint rhs) noexcept { return modint(lhs) - rhs; }
    friend constexpr modint operator*(value_type lhs, modint rhs) noexcept { return modint(lhs) * rhs; }
    friend constexpr modint operator/(value_type lhs, modint rhs) noexcept { return modint(lhs) / rhs; }
    static constexpr modint inverse(const modint &rhs) noexcept
    {
        assert(rhs != 0);
        value_type a{mod}, b{rhs.val}, u{}, v{1}, t{};
        while(b) t = a / b, a ^= b ^= (a -= t * b) ^= b, u ^= v ^= (u -= t * v) ^= v;
        return {u};
    }
    static constexpr modint pow(modint rhs, int_fast64_t e) noexcept
    {
        if(e < 0) e = e % (mod - 1) + mod - 1;
        modint res{1};
        while(e) { if(e & 1) res *= rhs; rhs *= rhs, e >>= 1; }
        return res;
    }
    friend std::ostream &operator<<(std::ostream &os, const modint &rhs) noexcept { return os << rhs.val; }
    friend std::istream &operator>>(std::istream &is, modint &rhs) noexcept { value_type val; rhs = (is >> val, val); return is; }
protected:
    value_type val;
}; // class modint
// specialization for modulo 2.
template <>
class modint<2>
{
    bool val;
public:
    static constexpr modint one() noexcept { return 1; }
    constexpr modint() noexcept : val(false) {}
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    constexpr modint(int_type _val) noexcept : val(_val & 1) {}
    constexpr operator bool() const noexcept { return val; }
    constexpr bool value() const noexcept { return val; }
    constexpr modint &operator+=(const modint &rhs) noexcept { return val ^= rhs.val, *this; }
    constexpr modint &operator-=(const modint &rhs) noexcept { return val ^= rhs.val, *this; }
    constexpr modint &operator*=(const modint &rhs) noexcept { return val &= rhs.val, *this; }
    constexpr modint &operator/=(const modint &rhs) noexcept { assert(rhs.val); return *this; }
    constexpr modint operator!() const noexcept { return !val; }
    constexpr modint operator-() const noexcept { return *this; }
    constexpr modint operator+(const modint &rhs) const noexcept { return val != rhs.val; }
    constexpr modint operator-(const modint &rhs) const noexcept { return val != rhs.val; }
    constexpr modint operator*(const modint &rhs) const noexcept { return val && rhs.val; }
    constexpr modint operator/(const modint &rhs) const noexcept { assert(rhs.val); return *this; }
    constexpr bool operator==(const modint &rhs) const noexcept { return val == rhs.val; }
    constexpr bool operator!=(const modint &rhs) const noexcept { return val != rhs.val; }
    friend constexpr modint operator+(long long lhs, modint rhs) noexcept { return lhs & 1 ? !rhs : rhs; }
    friend constexpr modint operator-(long long lhs, modint rhs) noexcept { return lhs & 1 ? !rhs : rhs; }
    friend constexpr modint operator*(long long lhs, modint rhs) noexcept { return lhs & 1 ? rhs : modint<2>{0}; }
    friend constexpr modint operator/(long long lhs, modint rhs) noexcept { assert(rhs.val); return lhs & 1 ? rhs : modint<2>{0}; }
    friend std::ostream &operator<<(std::ostream &os, const modint &rhs) noexcept { return os << rhs.val; }
    friend std::istream &operator>>(std::istream &is, modint &rhs) noexcept { long long val; rhs.val = (is >> val, val & 1); return is; }
}; // class modint<2>

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "modulus/compile-time/modint.hpp"
#include <cassert>
#include <iostream>
template <int_fast64_t mod>
struct modint
{
    using value_type = int_fast64_t;
    static constexpr modint one() noexcept { return 1; }
    constexpr modint() noexcept : val(0) {}
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    constexpr modint(int_type _val) noexcept : val((_val %= mod) < 0 ? mod + _val : _val) {}
    constexpr value_type value() const noexcept { return val; }
    constexpr modint operator++(int) noexcept { modint t{*this}; return operator+=(1), t; }
    constexpr modint operator--(int) noexcept { modint t{*this}; return operator-=(1), t; }
    constexpr modint &operator++() noexcept { return operator+=(1); }
    constexpr modint &operator--() noexcept { return operator-=(1); }
    constexpr modint operator-() const noexcept { return modint(-val); }
    constexpr modint &operator+=(const modint &rhs) noexcept { return (val += rhs.val) < mod ? 0 : val -= mod, *this; }
    constexpr modint &operator-=(const modint &rhs) noexcept { return (val += mod - rhs.val) < mod ? 0 : val -= mod, *this; }
    constexpr modint &operator*=(const modint &rhs) noexcept { return val = val * rhs.val % mod, *this; }
    constexpr modint &operator/=(const modint &rhs) noexcept { return *this *= inverse(rhs); }
    constexpr modint operator+(const modint &rhs) const noexcept { return modint(*this) += rhs; }
    constexpr modint operator-(const modint &rhs) const noexcept { return modint(*this) -= rhs; }
    constexpr modint operator*(const modint &rhs) const noexcept { return modint(*this) *= rhs; }
    constexpr modint operator/(const modint &rhs) const noexcept { return modint(*this) /= rhs; }
    constexpr bool operator==(const modint &rhs) const noexcept { return val == rhs.val; }
    constexpr bool operator!=(const modint &rhs) const noexcept { return val != rhs.val; }
    constexpr bool operator!() const noexcept { return !val; }
    friend constexpr modint operator+(value_type lhs, modint rhs) noexcept { return modint(lhs) + rhs; }
    friend constexpr modint operator-(value_type lhs, modint rhs) noexcept { return modint(lhs) - rhs; }
    friend constexpr modint operator*(value_type lhs, modint rhs) noexcept { return modint(lhs) * rhs; }
    friend constexpr modint operator/(value_type lhs, modint rhs) noexcept { return modint(lhs) / rhs; }
    static constexpr modint inverse(const modint &rhs) noexcept
    {
        assert(rhs != 0);
        value_type a{mod}, b{rhs.val}, u{}, v{1}, t{};
        while(b) t = a / b, a ^= b ^= (a -= t * b) ^= b, u ^= v ^= (u -= t * v) ^= v;
        return {u};
    }
    static constexpr modint pow(modint rhs, int_fast64_t e) noexcept
    {
        if(e < 0) e = e % (mod - 1) + mod - 1;
        modint res{1};
        while(e) { if(e & 1) res *= rhs; rhs *= rhs, e >>= 1; }
        return res;
    }
    friend std::ostream &operator<<(std::ostream &os, const modint &rhs) noexcept { return os << rhs.val; }
    friend std::istream &operator>>(std::istream &is, modint &rhs) noexcept { value_type val; rhs = (is >> val, val); return is; }
protected:
    value_type val;
}; // class modint
// specialization for modulo 2.
template <>
class modint<2>
{
    bool val;
public:
    static constexpr modint one() noexcept { return 1; }
    constexpr modint() noexcept : val(false) {}
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    constexpr modint(int_type _val) noexcept : val(_val & 1) {}
    constexpr operator bool() const noexcept { return val; }
    constexpr bool value() const noexcept { return val; }
    constexpr modint &operator+=(const modint &rhs) noexcept { return val ^= rhs.val, *this; }
    constexpr modint &operator-=(const modint &rhs) noexcept { return val ^= rhs.val, *this; }
    constexpr modint &operator*=(const modint &rhs) noexcept { return val &= rhs.val, *this; }
    constexpr modint &operator/=(const modint &rhs) noexcept { assert(rhs.val); return *this; }
    constexpr modint operator!() const noexcept { return !val; }
    constexpr modint operator-() const noexcept { return *this; }
    constexpr modint operator+(const modint &rhs) const noexcept { return val != rhs.val; }
    constexpr modint operator-(const modint &rhs) const noexcept { return val != rhs.val; }
    constexpr modint operator*(const modint &rhs) const noexcept { return val && rhs.val; }
    constexpr modint operator/(const modint &rhs) const noexcept { assert(rhs.val); return *this; }
    constexpr bool operator==(const modint &rhs) const noexcept { return val == rhs.val; }
    constexpr bool operator!=(const modint &rhs) const noexcept { return val != rhs.val; }
    friend constexpr modint operator+(long long lhs, modint rhs) noexcept { return lhs & 1 ? !rhs : rhs; }
    friend constexpr modint operator-(long long lhs, modint rhs) noexcept { return lhs & 1 ? !rhs : rhs; }
    friend constexpr modint operator*(long long lhs, modint rhs) noexcept { return lhs & 1 ? rhs : modint<2>{0}; }
    friend constexpr modint operator/(long long lhs, modint rhs) noexcept { assert(rhs.val); return lhs & 1 ? rhs : modint<2>{0}; }
    friend std::ostream &operator<<(std::ostream &os, const modint &rhs) noexcept { return os << rhs.val; }
    friend std::istream &operator>>(std::istream &is, modint &rhs) noexcept { long long val; rhs.val = (is >> val, val & 1); return is; }
}; // class modint<2>

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

