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


# :warning: combinatorics/compile-time/modint.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#dfc668f450222e8dc05cbabf0a30df41">combinatorics/compile-time</a>
* <a href="{{ site.github.repository_url }}/blob/master/combinatorics/compile-time/modint.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-09 13:42:34+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef modint_hpp
#define modint_hpp
#include <cassert>
#include <iostream>

template <int mod>
class modint
{
    int val;
public:
    static constexpr modint identity() noexcept { return 1; }
    constexpr modint() noexcept : val{0} {}
    constexpr modint(long long x) noexcept : val((x %= mod) < 0 ? mod + x : x) {}
    constexpr long long value() const noexcept { return val; }
    constexpr modint operator++(int) noexcept { modint t = *this; return ++val, t; }
    constexpr modint operator--(int) noexcept { modint t = *this; return --val, t; }
    constexpr modint &operator++() noexcept { return ++val, *this; }
    constexpr modint &operator--() noexcept { return --val, *this; }
    constexpr modint operator-() const noexcept { return modint(-val); }
    constexpr modint &operator+=(const modint &other) noexcept { return (val += other.val) < mod ? 0 : val -= mod, *this; }
    constexpr modint &operator-=(const modint &other) noexcept { return (val += mod - other.val) < mod ? 0 : val -= mod, *this; }
    constexpr modint &operator*=(const modint &other) noexcept { return val = (long long)val * other.val % mod, *this; }
    constexpr modint &operator/=(const modint &other) noexcept { return *this *= inverse(other); }
    constexpr modint operator+(const modint &other) const noexcept { return modint(*this) += other; }
    constexpr modint operator-(const modint &other) const noexcept { return modint(*this) -= other; }
    constexpr modint operator*(const modint &other) const noexcept { return modint(*this) *= other; }
    constexpr modint operator/(const modint &other) const noexcept { return modint(*this) /= other; }
    constexpr bool operator==(const modint &other) const noexcept { return val == other.val; }
    constexpr bool operator!=(const modint &other) const noexcept { return val != other.val; }
    constexpr bool operator!() const noexcept { return !val; }
    friend constexpr modint operator+(long long x, modint y) noexcept { return modint(x) + y; }
    friend constexpr modint operator-(long long x, modint y) noexcept { return modint(x) - y; }
    friend constexpr modint operator*(long long x, modint y) noexcept { return modint(x) * y; }
    friend constexpr modint operator/(long long x, modint y) noexcept { return modint(x) / y; }
    static constexpr modint inverse(const modint &other) noexcept
    {
        assert(other != 0);
        int a{mod}, b{other.val}, u{}, v{1}, t{};
        while(b) t = a / b, a ^= b ^= (a -= t * b) ^= b, u ^= v ^= (u -= t * v) ^= v;
        return {u};
    }
    static constexpr modint pow(modint other, long long e) noexcept
    {
        if(e < 0) e = e % (mod - 1) + mod - 1;
        modint res{1};
        while(e) { if(e & 1) res *= other; other *= other, e >>= 1; }
        return res;
    }
    friend std::ostream &operator<<(std::ostream &os, const modint &other) noexcept { return os << other.val; }
    friend std::istream &operator>>(std::istream &is, modint &other) noexcept { long long val; other = {(is >> val, val)}; return is; }
}; // class modint

template <>
class modint<2>
{
    bool val;
public:
    static constexpr modint identity() noexcept { return 1; }
    constexpr modint(bool x = false) noexcept : val{x} {}
    constexpr modint(int x) noexcept : val(x & 1) {}
    constexpr modint(long long x) noexcept : val(x & 1) {}
    constexpr operator bool() const noexcept { return val; }
    constexpr bool value() const noexcept { return val; }
    constexpr modint &operator+=(const modint &other) noexcept { return val ^= other.val, *this; }
    constexpr modint &operator-=(const modint &other) noexcept { return val ^= other.val, *this; }
    constexpr modint &operator*=(const modint &other) noexcept { return val &= other.val, *this; }
    constexpr modint &operator/=(const modint &other) noexcept { assert(other.val); return *this; }
    constexpr modint operator!() const noexcept { return !val; }
    constexpr modint operator-() const noexcept { return *this; }
    constexpr modint operator+(const modint &other) const noexcept { return val != other.val; }
    constexpr modint operator-(const modint &other) const noexcept { return val != other.val; }
    constexpr modint operator*(const modint &other) const noexcept { return val && other.val; }
    constexpr modint operator/(const modint &other) const noexcept { assert(other.val); return *this; }
    constexpr bool operator==(const modint &other) const noexcept { return val == other.val; }
    constexpr bool operator!=(const modint &other) const noexcept { return val != other.val; }
    friend constexpr modint operator+(long long x, modint y) noexcept { return x & 1 ? !y : y; }
    friend constexpr modint operator-(long long x, modint y) noexcept { return x & 1 ? !y : y; }
    friend constexpr modint operator*(long long x, modint y) noexcept { return x & 1 ? y : modint<2>{0}; }
    friend constexpr modint operator/(long long x, modint y) noexcept { assert(y.val); return x & 1 ? y : modint<2>{0}; }
    friend std::ostream &operator<<(std::ostream &os, const modint &other) noexcept { return os << other.val; }
    friend std::istream &operator>>(std::istream &is, modint &other) noexcept { long long val; other.val = (is >> val, val & 1); return is; }
}; // class modint specialization

#endif // modint_hpp
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "combinatorics/compile-time/modint.hpp"


#include <cassert>
#include <iostream>

template <int mod>
class modint
{
    int val;
public:
    static constexpr modint identity() noexcept { return 1; }
    constexpr modint() noexcept : val{0} {}
    constexpr modint(long long x) noexcept : val((x %= mod) < 0 ? mod + x : x) {}
    constexpr long long value() const noexcept { return val; }
    constexpr modint operator++(int) noexcept { modint t = *this; return ++val, t; }
    constexpr modint operator--(int) noexcept { modint t = *this; return --val, t; }
    constexpr modint &operator++() noexcept { return ++val, *this; }
    constexpr modint &operator--() noexcept { return --val, *this; }
    constexpr modint operator-() const noexcept { return modint(-val); }
    constexpr modint &operator+=(const modint &other) noexcept { return (val += other.val) < mod ? 0 : val -= mod, *this; }
    constexpr modint &operator-=(const modint &other) noexcept { return (val += mod - other.val) < mod ? 0 : val -= mod, *this; }
    constexpr modint &operator*=(const modint &other) noexcept { return val = (long long)val * other.val % mod, *this; }
    constexpr modint &operator/=(const modint &other) noexcept { return *this *= inverse(other); }
    constexpr modint operator+(const modint &other) const noexcept { return modint(*this) += other; }
    constexpr modint operator-(const modint &other) const noexcept { return modint(*this) -= other; }
    constexpr modint operator*(const modint &other) const noexcept { return modint(*this) *= other; }
    constexpr modint operator/(const modint &other) const noexcept { return modint(*this) /= other; }
    constexpr bool operator==(const modint &other) const noexcept { return val == other.val; }
    constexpr bool operator!=(const modint &other) const noexcept { return val != other.val; }
    constexpr bool operator!() const noexcept { return !val; }
    friend constexpr modint operator+(long long x, modint y) noexcept { return modint(x) + y; }
    friend constexpr modint operator-(long long x, modint y) noexcept { return modint(x) - y; }
    friend constexpr modint operator*(long long x, modint y) noexcept { return modint(x) * y; }
    friend constexpr modint operator/(long long x, modint y) noexcept { return modint(x) / y; }
    static constexpr modint inverse(const modint &other) noexcept
    {
        assert(other != 0);
        int a{mod}, b{other.val}, u{}, v{1}, t{};
        while(b) t = a / b, a ^= b ^= (a -= t * b) ^= b, u ^= v ^= (u -= t * v) ^= v;
        return {u};
    }
    static constexpr modint pow(modint other, long long e) noexcept
    {
        if(e < 0) e = e % (mod - 1) + mod - 1;
        modint res{1};
        while(e) { if(e & 1) res *= other; other *= other, e >>= 1; }
        return res;
    }
    friend std::ostream &operator<<(std::ostream &os, const modint &other) noexcept { return os << other.val; }
    friend std::istream &operator>>(std::istream &is, modint &other) noexcept { long long val; other = {(is >> val, val)}; return is; }
}; // class modint

template <>
class modint<2>
{
    bool val;
public:
    static constexpr modint identity() noexcept { return 1; }
    constexpr modint(bool x = false) noexcept : val{x} {}
    constexpr modint(int x) noexcept : val(x & 1) {}
    constexpr modint(long long x) noexcept : val(x & 1) {}
    constexpr operator bool() const noexcept { return val; }
    constexpr bool value() const noexcept { return val; }
    constexpr modint &operator+=(const modint &other) noexcept { return val ^= other.val, *this; }
    constexpr modint &operator-=(const modint &other) noexcept { return val ^= other.val, *this; }
    constexpr modint &operator*=(const modint &other) noexcept { return val &= other.val, *this; }
    constexpr modint &operator/=(const modint &other) noexcept { assert(other.val); return *this; }
    constexpr modint operator!() const noexcept { return !val; }
    constexpr modint operator-() const noexcept { return *this; }
    constexpr modint operator+(const modint &other) const noexcept { return val != other.val; }
    constexpr modint operator-(const modint &other) const noexcept { return val != other.val; }
    constexpr modint operator*(const modint &other) const noexcept { return val && other.val; }
    constexpr modint operator/(const modint &other) const noexcept { assert(other.val); return *this; }
    constexpr bool operator==(const modint &other) const noexcept { return val == other.val; }
    constexpr bool operator!=(const modint &other) const noexcept { return val != other.val; }
    friend constexpr modint operator+(long long x, modint y) noexcept { return x & 1 ? !y : y; }
    friend constexpr modint operator-(long long x, modint y) noexcept { return x & 1 ? !y : y; }
    friend constexpr modint operator*(long long x, modint y) noexcept { return x & 1 ? y : modint<2>{0}; }
    friend constexpr modint operator/(long long x, modint y) noexcept { assert(y.val); return x & 1 ? y : modint<2>{0}; }
    friend std::ostream &operator<<(std::ostream &os, const modint &other) noexcept { return os << other.val; }
    friend std::istream &operator>>(std::istream &is, modint &other) noexcept { long long val; other.val = (is >> val, val & 1); return is; }
}; // class modint specialization



```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

