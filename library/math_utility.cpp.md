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
<script type="text/javascript" src="../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../assets/css/copy-button.css" />


# :warning: math_utility.cpp

<a href="../index.html">Back to top page</a>

* category: <a href="../index.html#5058f1af8388633f609cadb75a75dc9d">.</a>
* <a href="{{ site.github.repository_url }}/blob/master/math_utility.cpp">View this file on GitHub</a>
    - Last commit date: 2019-12-24 00:46:14+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <bits/stdc++.h>

namespace math
{
    template <class int_t> std::vector<int_t> prime_factorization(int_t x)
    {
        std::vector<int_t> res(__builtin_ctzll(x), 2); x >>= __builtin_ctzll(x);
        for(int_t p{3}; p * p <= x; p += 2) while(!(x % p)) x /= p, res.emplace_back(p);
        if(x > 1) res.emplace_back(x); return res;
    }
    template <class int_t> constexpr int_t gcd(int_t x, int_t y) { x = x > 0 ? x : -x, y = y > 0 ? y : -y; while(y) y ^= x ^= y ^= x %= y; return x; }
    template <class int_t> constexpr int_t lcm(int_t x, int_t y) { return x ? x / gcd(x, y) * y : 0; }
    // a tuple (g, x, y) s.t. g = gcd(a, b) && ax + by = g.
    template <class int_t> constexpr std::tuple<int_t, int_t, int_t> ext_gcd(int_t a, int_t b)
    {
        int_t sgn_a{a >= 0 ? 1 : (a = -a, 0)}, sgn_b{b >= 0 ? 1 : (b = -b, 0)};
        int_t p{1}, q{}, r{}, s{1}, t{};
        while(b)
        {
            r ^= p ^= r ^= p -= (t = a / b) * r;
            s ^= q ^= s ^= q -= t * s;
            b ^= a ^= b ^= a %= b;
        }
        return std::tuple<int_t, int_t, int_t>(a, sgn_a ? p : -p, sgn_b ? q : -q);
    }
    // a pair (x, y) s.t. "x mod y" is true iff "k mod m" && "l mod n", (-1, -1) if not exist.
    template <class int_t>
    constexpr std::pair<int_t, int_t> modulo_composition(int_t k, int_t m, int_t l, int_t n)
    {
        assert(m > 0 and n > 0);
        int_t g, x, y; std::tie(g, x, y) = ext_gcd(m, n);
        k += ((k %= m) < 0) * m, l += ((l %= n) < 0) * n;
        int_t s = k / g, t = l / g, r = k % g;
        if(r != l % g) return std::pair<int_t, int_t>{-1, -1};
        int_t lcm = m / g * n;
        return std::pair<int_t, int_t>{(m * x % lcm * t % lcm + n * y % lcm * s % lcm + r + lcm * 2) % lcm, lcm};
    }
} // namespace math
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "math_utility.cpp"
#include <bits/stdc++.h>

namespace math
{
    template <class int_t> std::vector<int_t> prime_factorization(int_t x)
    {
        std::vector<int_t> res(__builtin_ctzll(x), 2); x >>= __builtin_ctzll(x);
        for(int_t p{3}; p * p <= x; p += 2) while(!(x % p)) x /= p, res.emplace_back(p);
        if(x > 1) res.emplace_back(x); return res;
    }
    template <class int_t> constexpr int_t gcd(int_t x, int_t y) { x = x > 0 ? x : -x, y = y > 0 ? y : -y; while(y) y ^= x ^= y ^= x %= y; return x; }
    template <class int_t> constexpr int_t lcm(int_t x, int_t y) { return x ? x / gcd(x, y) * y : 0; }
    // a tuple (g, x, y) s.t. g = gcd(a, b) && ax + by = g.
    template <class int_t> constexpr std::tuple<int_t, int_t, int_t> ext_gcd(int_t a, int_t b)
    {
        int_t sgn_a{a >= 0 ? 1 : (a = -a, 0)}, sgn_b{b >= 0 ? 1 : (b = -b, 0)};
        int_t p{1}, q{}, r{}, s{1}, t{};
        while(b)
        {
            r ^= p ^= r ^= p -= (t = a / b) * r;
            s ^= q ^= s ^= q -= t * s;
            b ^= a ^= b ^= a %= b;
        }
        return std::tuple<int_t, int_t, int_t>(a, sgn_a ? p : -p, sgn_b ? q : -q);
    }
    // a pair (x, y) s.t. "x mod y" is true iff "k mod m" && "l mod n", (-1, -1) if not exist.
    template <class int_t>
    constexpr std::pair<int_t, int_t> modulo_composition(int_t k, int_t m, int_t l, int_t n)
    {
        assert(m > 0 and n > 0);
        int_t g, x, y; std::tie(g, x, y) = ext_gcd(m, n);
        k += ((k %= m) < 0) * m, l += ((l %= n) < 0) * n;
        int_t s = k / g, t = l / g, r = k % g;
        if(r != l % g) return std::pair<int_t, int_t>{-1, -1};
        int_t lcm = m / g * n;
        return std::pair<int_t, int_t>{(m * x % lcm * t % lcm + n * y % lcm * s % lcm + r + lcm * 2) % lcm, lcm};
    }
} // namespace math

```
{% endraw %}

<a href="../index.html">Back to top page</a>

