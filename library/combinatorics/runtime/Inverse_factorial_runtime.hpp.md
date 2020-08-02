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


# :warning: combinatorics/runtime/Inverse_factorial_runtime.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#16433cc04c471e1e6dbf9e346eeaab28">combinatorics/runtime</a>
* <a href="{{ site.github.repository_url }}/blob/master/combinatorics/runtime/Inverse_factorial_runtime.hpp">View this file on GitHub</a>
    - Last commit date: 2020-01-19 02:16:26+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef Modint_runtime_hpp
#define Modint_runtime_hpp
#include <cassert>
#include <iostream>

// modulo statically fixed
class modint_runtime
{
    long long val;
    friend std::ostream &operator<<(std::ostream &os, const modint_runtime &other) noexcept { return os << other.val; }
    friend std::istream &operator>>(std::istream &is, modint_runtime &other) noexcept { long long val; other = modint_runtime((is >> val, val)); return is; }
public:
    static long long &mod() noexcept { static long long mod{}; return mod; }
    modint_runtime(long long x = 0) : val{(x %= mod()) < 0 ? x + mod() : x} {}
    long long value() const noexcept { return val; }
    modint_runtime operator++(int) noexcept { modint_runtime t = *this; return ++val, t; }
    modint_runtime &operator++() noexcept { return ++val, *this; }
    modint_runtime operator--(int) noexcept { modint_runtime t = *this; return --val, t; }
    modint_runtime &operator--() noexcept { return --val, *this; }
    modint_runtime &operator=(long long other) noexcept { return val = (other %= mod()) < 0 ? other + mod() : other, *this; }
    modint_runtime &operator+=(long long other) noexcept { return (val += other % mod()) < mod() ? 0 : val -= mod(), *this; }
    modint_runtime &operator+=(const modint_runtime &other) noexcept { return (val += other.val) < mod() ? 0 : val -= mod(), *this; }
    modint_runtime &operator-=(long long other) noexcept { return (val += mod() - other % mod()) < mod() ? 0 : val -= mod(), *this; }
    modint_runtime &operator-=(const modint_runtime &other) noexcept { return (val += mod() - other.val) < mod() ? 0 : val -= mod(), *this; }
    modint_runtime &operator*=(long long other) noexcept { return (val *= other % mod()) %= mod(), *this; }
    modint_runtime &operator*=(const modint_runtime &other) noexcept { return (val *= other.val) %= mod(), *this; }
    modint_runtime &operator/=(long long other) noexcept { return *this *= inverse(other); }
    modint_runtime &operator/=(const modint_runtime &other) noexcept { return *this *= inverse(other); }
    modint_runtime operator-() const noexcept { return modint_runtime(-val); }
    modint_runtime operator+(const modint_runtime &other) const noexcept { return modint_runtime{*this} += other; }
    modint_runtime operator-(const modint_runtime &other) const noexcept { return modint_runtime{*this} -= other; }
    modint_runtime operator*(const modint_runtime &other) const noexcept { return modint_runtime{*this} *= other; }
    modint_runtime operator/(const modint_runtime &other) const noexcept { return modint_runtime{*this} /= other; }
    bool operator==(const modint_runtime &other) const noexcept { return val == other.val; }
    bool operator!=(const modint_runtime &other) const noexcept { return val != other.val; }
    bool operator!() const noexcept { return !val; }
    friend modint_runtime operator+(long long x, modint_runtime y) noexcept { return {x + y.val}; }
    friend modint_runtime operator-(long long x, modint_runtime y) noexcept { return {x - y.val}; }
    friend modint_runtime operator*(long long x, modint_runtime y) noexcept { return {x % mod() * y.val}; }
    friend modint_runtime operator/(long long x, modint_runtime y) noexcept { return {x % mod() * inverse(y).val}; }
    static modint_runtime inverse(const modint_runtime &other) noexcept
    {
        assert(mod() && other.val);
        long long a{mod()}, b{other.val}, u{}, v{1}, t{};
        while(b) t = a / b, a ^= b ^= (a -= t * b) ^= b, u ^= v ^= (u -= t * v) ^= v;
        return {u};
    }
    static modint_runtime pow(modint_runtime other, long long e) noexcept
    {
        if(e < 0) e = e % (mod() - 1) + mod() - 1;
        modint_runtime res{1};
        while(e) { if(e & 1) res *= other; other *= other, e >>= 1; }
        return res;
    }
}; // class modint_runtime
#endif // Modint_runtime_hpp

#ifndef Inverse_runtime_hpp
#define Inverse_runtime_hpp
#include <vector>

class inverse_runtime
{
    const int mod;
    int n;
    std::vector<int> inv;
public:
    inverse_runtime(int _mod) : mod{_mod}, n{2}, inv{0, 1} {}
    int modulo() const { return mod; }
    void reserve(int m)
    {
        if(m < n) return;
        m = 1 << (32 - __builtin_clz(m));
        inv.resize(m);
        for(int i = n; i < m; ++i) inv[i] = mod - (long long)mod / i * inv[mod % i] % mod;
        n = m;
    }
    // modint_runtime operator()(const int x) noexcept { assert(x), reserve(x); return {inv[x], mod}; }
    modint_runtime operator()(const int x) noexcept { assert(x), reserve(x); return {inv[x]}; }
};

#endif // Inverse_runtime_hpp

#ifndef Inverse_factorial_runtime_hpp
#define Inverse_factorial_runtime_hpp
#include <vector>

class inverse_factorial_runtime
{
    inverse_runtime &inv_gen;
    const int mod;
    int n;
    std::vector<int> inv_fact;
public:
    inverse_factorial_runtime(inverse_runtime &_inv_gen) : inv_gen{_inv_gen}, mod{_inv_gen.modulo()}, n{1}, inv_fact{1} {}
    int modulo() const { return mod; }
    void reserve(int m)
    {
        if(m < n) return;
        m = 1 << (32 - __builtin_clz(m));
        inv_fact.resize(m);
        for(int i = n; i < m; ++i) inv_fact[i] = inv_fact[i - 1] * inv_gen(i).value() % mod;
        n = m;
    }
    // modint_runtime operator()(const int x) noexcept { reserve(x); return {x < 0 ? 0 : inv_fact[x], mod}; }
    modint_runtime operator()(const int x) noexcept { reserve(x); return {x < 0 ? 0 : inv_fact[x]}; }
};

#endif // Inverse_factorial_runtime_hpp
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
Traceback (most recent call last):
  File "/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/docs.py", line 349, in write_contents
    bundled_code = language.bundle(self.file_class.file_path, basedir=pathlib.Path.cwd())
  File "/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py", line 185, in bundle
    bundler.update(path)
  File "/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 282, in update
    raise BundleErrorAt(path, i + 1, "found codes out of include guard")
onlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: combinatorics/runtime/Inverse_factorial_runtime.hpp: line 57: found codes out of include guard

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

