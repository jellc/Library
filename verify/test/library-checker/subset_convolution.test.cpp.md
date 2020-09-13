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
    - Last commit date: 2020-09-13 23:56:56+09:00


* see: <a href="https://judge.yosupo.jp/problem/subset_convolution">https://judge.yosupo.jp/problem/subset_convolution</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/algebra/convolution/subset.hpp.html">algebra/convolution/subset.hpp</a>
* :heavy_check_mark: <a href="../../../library/modulus/modint.hpp.html">modulus/modint.hpp</a>
* :heavy_check_mark: <a href="../../../library/utils/sfinae.hpp.html">utils/sfinae.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/subset_convolution"
#include <iostream>

#include "algebra/convolution/subset.hpp"
#include "modulus/modint.hpp"

int main() {
  using mint = modint<998244353>;
  using std::cin;
  int n;
  cin >> n;
  std::vector<mint> a(1 << n), b(1 << n);
  for (auto &x : a) cin >> x;
  for (auto &x : b) cin >> x;
  a = subset_convolute(a, b);
  for (auto x : a) printf("%d ", x);
  puts("");
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/library-checker/subset_convolution.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/subset_convolution"
#include <iostream>

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
#line 4 "modulus/modint.hpp"

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
#if __cplusplus >= 201402
template <class T>
constexpr static bool is_integral_ext_v = is_integral_ext<T>::value;
#endif

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
#line 6 "test/library-checker/subset_convolution.test.cpp"

int main() {
  using mint = modint<998244353>;
  using std::cin;
  int n;
  cin >> n;
  std::vector<mint> a(1 << n), b(1 << n);
  for (auto &x : a) cin >> x;
  for (auto &x : b) cin >> x;
  a = subset_convolute(a, b);
  for (auto x : a) printf("%d ", x);
  puts("");
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

