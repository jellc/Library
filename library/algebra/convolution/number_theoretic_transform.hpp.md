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


# :warning: algebra/convolution/number_theoretic_transform.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#3cd9fd076f2d75c19d145e9eb33bfef8">algebra/convolution</a>
* <a href="{{ site.github.repository_url }}/blob/master/algebra/convolution/number_theoretic_transform.hpp">View this file on GitHub</a>
    - Last commit date: 2020-06-27 01:08:32+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef number_theoretic_transform_hpp
#define number_theoretic_transform_hpp

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

namespace number_theoretic_transform
{
    constexpr int mod = 998244353;
    constexpr int primitive = 3;

    class modint
    {
        int val;
    public:
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

    class zeta_calc
    {
        static constexpr size_t n = __builtin_ctz(mod - 1);
        modint _zeta[n + 1];
      public:
        constexpr zeta_calc() : _zeta{}
        {
            _zeta[n] = modint::pow(modint(primitive), (mod - 1) / (1 << n));
            for(size_t i{n}; i; --i) _zeta[i - 1] = _zeta[i] * _zeta[i];
        }
        constexpr modint operator[](size_t k) const { return _zeta[k]; }
    }; // class zeta_calc
    constexpr zeta_calc zeta;

    class inv_calc
    {
        static constexpr size_t n = __builtin_ctz(mod - 1);
        modint _inv[n + 1];
      public:
        constexpr inv_calc() : _inv{1, (mod + 1) / 2} { for(size_t i{1}; i < n; ++i) _inv[i + 1] = _inv[i] * _inv[1]; }
        constexpr modint operator[](size_t k) const { return _inv[k]; }
    }; // class inv_calc
    constexpr inv_calc inv;

    using poly_t = std::vector<modint>;

    void discrete_Fourier_transform(poly_t &f)
    {
        const size_t n{f.size()}, mask{n - 1};
        assert(__builtin_popcount(n) == 1); // degree of f must be a power of two.
        static poly_t g; g.resize(n);
        for(size_t i{n >> 1}, ii{1}; i; i >>= 1, ++ii, swap(f, g))
        {
            modint powzeta{1};
            for(size_t j{}; j < n; powzeta *= zeta[ii])
            {
                for(size_t k{}, x{mask & j << 1}, y{mask & (i + (j << 1))}; k < i; ++k, ++j, ++x, ++y)
                {
                    g[j] = f[x] + powzeta * f[y];
                }
            }
        }
    }

    void inverse_discrete_Fourier_transform(poly_t &f)
    {
        discrete_Fourier_transform(f), reverse(next(f.begin()), f.end());
        const size_t k = __builtin_ctz(f.size()); for(modint &e : f) e *= inv[k];
    }

    poly_t convolute(poly_t f, poly_t g)
    {
        if(f.empty() || g.empty()) return poly_t();
        const size_t deg_f{f.size() - 1}, deg_g{g.size() - 1}, deg_h{deg_f + deg_g}, n(1u << (32 - __builtin_clz(deg_h)));
        static poly_t h;
        f.resize(n, 0), g.resize(n, 0), h.resize(n);
        discrete_Fourier_transform(f), discrete_Fourier_transform(g);
        for(size_t i{}; i < n; ++i) h[i] = f[i] * g[i];
        inverse_discrete_Fourier_transform(h); h.resize(deg_h + 1);
        return h;
    }
} // namespace Number_theoretic_transform

#endif // number_theoretic_transform_hpp

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "algebra/convolution/number_theoretic_transform.hpp"



#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

namespace number_theoretic_transform
{
    constexpr int mod = 998244353;
    constexpr int primitive = 3;

    class modint
    {
        int val;
    public:
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

    class zeta_calc
    {
        static constexpr size_t n = __builtin_ctz(mod - 1);
        modint _zeta[n + 1];
      public:
        constexpr zeta_calc() : _zeta{}
        {
            _zeta[n] = modint::pow(modint(primitive), (mod - 1) / (1 << n));
            for(size_t i{n}; i; --i) _zeta[i - 1] = _zeta[i] * _zeta[i];
        }
        constexpr modint operator[](size_t k) const { return _zeta[k]; }
    }; // class zeta_calc
    constexpr zeta_calc zeta;

    class inv_calc
    {
        static constexpr size_t n = __builtin_ctz(mod - 1);
        modint _inv[n + 1];
      public:
        constexpr inv_calc() : _inv{1, (mod + 1) / 2} { for(size_t i{1}; i < n; ++i) _inv[i + 1] = _inv[i] * _inv[1]; }
        constexpr modint operator[](size_t k) const { return _inv[k]; }
    }; // class inv_calc
    constexpr inv_calc inv;

    using poly_t = std::vector<modint>;

    void discrete_Fourier_transform(poly_t &f)
    {
        const size_t n{f.size()}, mask{n - 1};
        assert(__builtin_popcount(n) == 1); // degree of f must be a power of two.
        static poly_t g; g.resize(n);
        for(size_t i{n >> 1}, ii{1}; i; i >>= 1, ++ii, swap(f, g))
        {
            modint powzeta{1};
            for(size_t j{}; j < n; powzeta *= zeta[ii])
            {
                for(size_t k{}, x{mask & j << 1}, y{mask & (i + (j << 1))}; k < i; ++k, ++j, ++x, ++y)
                {
                    g[j] = f[x] + powzeta * f[y];
                }
            }
        }
    }

    void inverse_discrete_Fourier_transform(poly_t &f)
    {
        discrete_Fourier_transform(f), reverse(next(f.begin()), f.end());
        const size_t k = __builtin_ctz(f.size()); for(modint &e : f) e *= inv[k];
    }

    poly_t convolute(poly_t f, poly_t g)
    {
        if(f.empty() || g.empty()) return poly_t();
        const size_t deg_f{f.size() - 1}, deg_g{g.size() - 1}, deg_h{deg_f + deg_g}, n(1u << (32 - __builtin_clz(deg_h)));
        static poly_t h;
        f.resize(n, 0), g.resize(n, 0), h.resize(n);
        discrete_Fourier_transform(f), discrete_Fourier_transform(g);
        for(size_t i{}; i < n; ++i) h[i] = f[i] * g[i];
        inverse_discrete_Fourier_transform(h); h.resize(deg_h + 1);
        return h;
    }
} // namespace Number_theoretic_transform



```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

