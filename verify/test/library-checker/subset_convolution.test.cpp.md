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


# :heavy_check_mark: test/library-checker/subset_convolution.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#8a40f8ed03f4cdb6c2fe0a2d4731a143">test/library-checker</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/library-checker/subset_convolution.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-08-06 06:10:42+09:00


* see: <a href="https://judge.yosupo.jp/problem/subset_convolution">https://judge.yosupo.jp/problem/subset_convolution</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/algebra/convolution/subset.hpp.html">algebra/convolution/subset.hpp</a>
* :heavy_check_mark: <a href="../../../library/modulus/compile-time/modint.hpp.html">modulus/compile-time/modint.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/subset_convolution"
#include "../../algebra/convolution/subset.hpp"
#include "../../modulus/compile-time/modint.hpp"
#include <iostream>

int main()
{
    using mint=modint<998244353>;
    using std::cin;
    int n; cin>>n;
    std::vector<mint> a(1<<n),b(1<<n);
    for(auto &x: a) cin>>x;
    for(auto &x: b) cin>>x;
    a=subset_convolute(a,b);
    for(auto x: a) printf("%d ",x.value());
    puts("");
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/library-checker/subset_convolution.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/subset_convolution"
#line 1 "algebra/convolution/subset.hpp"
#include <cassert>
#include <vector>

template <class Ring>
std::vector<Ring> subset_convolute(const std::vector<Ring> &f, const std::vector<Ring> &g)
{
    assert(!f.empty()); assert(!g.empty());
    const size_t n = __builtin_ctz(std::min(f.size(), g.size()));
    std::vector ff(n + 1, std::vector<Ring>(1 << n)), gg(ff);
    ff[0] = f, gg[0] = g;
    for(size_t k = 0; k != n; ++k)
    {
        for(size_t i = k + 1; ~i; --i)
        {
            for(size_t s = 0; s != 1u << n; ++s)
            {
                if(s >> k & 1)
                {
                    if(i)
                    {
                        ff[i][s] = ff[i - 1][s];
                        gg[i][s] = gg[i - 1][s];
                    }
                    else
                    {
                        ff[i][s] = gg[i][s] = Ring{};
                    }
                    ff[i][s] += ff[i][s ^ 1 << k];
                    gg[i][s] += gg[i][s ^ 1 << k];
                }
            }
        }
    }
    for(size_t i = n; ~i; --i)
    {
        for(size_t s = 0; s != 1u << n; ++s)
        {
            ff[i][s] *= gg[0][s];
            for(size_t j = i; j; --j)
            {
                ff[i][s] += ff[i - j][s] * gg[j][s];
            }
        }
    }
    for(size_t k = n - 1; ~k; --k)
    {
        for(size_t s = 0; s != 1u << n; ++s)
        {
            if(~s >> k & 1)
            {
                for(size_t i = n; ~i; --i)
                {
                    ff[i][s ^ 1 << k] -= ff[i][s];
                    if(i) ff[i][s] = ff[i - 1][s];
                }
            }
        }
    }
    return ff[n];
}
#line 1 "modulus/compile-time/modint.hpp"


#line 4 "modulus/compile-time/modint.hpp"
#include <iostream>

template <int mod>
class modint
{
    int val;
public:
    static constexpr modint one() noexcept { return 1; }
    constexpr modint() noexcept : val(0) {}
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    constexpr modint(int_type _val) noexcept : val((_val %= mod) < 0 ? mod + _val : _val) {}
    constexpr long long value() const noexcept { return val; }
    constexpr modint operator++(int) noexcept { modint t = *this; return operator+=(1), t; }
    constexpr modint operator--(int) noexcept { modint t = *this; return operator-=(1), t; }
    constexpr modint &operator++() noexcept { return operator+=(1); }
    constexpr modint &operator--() noexcept { return operator-=(1); }
    constexpr modint operator-() const noexcept { return modint(-val); }
    constexpr modint &operator+=(const modint &rhs) noexcept { return (val += rhs.val) < mod ? 0 : val -= mod, *this; }
    constexpr modint &operator-=(const modint &rhs) noexcept { return (val += mod - rhs.val) < mod ? 0 : val -= mod, *this; }
    constexpr modint &operator*=(const modint &rhs) noexcept { return val = (long long)val * rhs.val % mod, *this; }
    constexpr modint &operator/=(const modint &rhs) noexcept { return *this *= inverse(rhs); }
    constexpr modint operator+(const modint &rhs) const noexcept { return modint(*this) += rhs; }
    constexpr modint operator-(const modint &rhs) const noexcept { return modint(*this) -= rhs; }
    constexpr modint operator*(const modint &rhs) const noexcept { return modint(*this) *= rhs; }
    constexpr modint operator/(const modint &rhs) const noexcept { return modint(*this) /= rhs; }
    constexpr bool operator==(const modint &rhs) const noexcept { return val == rhs.val; }
    constexpr bool operator!=(const modint &rhs) const noexcept { return val != rhs.val; }
    constexpr bool operator!() const noexcept { return !val; }
    friend constexpr modint operator+(long long lhs, modint rhs) noexcept { return modint(lhs) + rhs; }
    friend constexpr modint operator-(long long lhs, modint rhs) noexcept { return modint(lhs) - rhs; }
    friend constexpr modint operator*(long long lhs, modint rhs) noexcept { return modint(lhs) * rhs; }
    friend constexpr modint operator/(long long lhs, modint rhs) noexcept { return modint(lhs) / rhs; }
    static constexpr modint inverse(const modint &rhs) noexcept
    {
        assert(rhs != 0);
        int a{mod}, b{rhs.val}, u{}, v{1}, t{};
        while(b) t = a / b, a ^= b ^= (a -= t * b) ^= b, u ^= v ^= (u -= t * v) ^= v;
        return {u};
    }
    static constexpr modint pow(modint rhs, long long e) noexcept
    {
        if(e < 0) e = e % (mod - 1) + mod - 1;
        modint res{1};
        while(e) { if(e & 1) res *= rhs; rhs *= rhs, e >>= 1; }
        return res;
    }
    friend std::ostream &operator<<(std::ostream &os, const modint &rhs) noexcept { return os << rhs.val; }
    friend std::istream &operator>>(std::istream &is, modint &rhs) noexcept { long long val; rhs = {(is >> val, val)}; return is; }
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


#line 5 "test/library-checker/subset_convolution.test.cpp"

int main()
{
    using mint=modint<998244353>;
    using std::cin;
    int n; cin>>n;
    std::vector<mint> a(1<<n),b(1<<n);
    for(auto &x: a) cin>>x;
    for(auto &x: b) cin>>x;
    a=subset_convolute(a,b);
    for(auto x: a) printf("%d ",x.value());
    puts("");
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

