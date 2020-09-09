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


# :warning: dev/fraction.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#e77989ed21758e78331b20e477fc5582">dev</a>
* <a href="{{ site.github.repository_url }}/blob/master/dev/fraction.hpp">View this file on GitHub</a>
    - Last commit date: 2020-09-09 22:32:55+09:00




## Depends on

* :heavy_check_mark: <a href="../utils/sfinae.hpp.html">utils/sfinae.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include "utils/sfinae.hpp"
template <class T> struct fraction {
  static_assert(is_integral_ext_v<T>);
  T num, den;
  constexpr fraction(const T &num = 0, const T &den = 1) : num(num), den(den) {}
  constexpr fraction operator-() const { return {-num, den}; }
  constexpr fraction operator-(const fraction &rhs) const {
    return {num * rhs.den - rhs.num * den, den * rhs.den};
  }
  constexpr bool operator<(const fraction &rhs) const {
    return operator-(rhs).num < 0;
  }

 private:
  constexpr void normalize();
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
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
#line 3 "dev/fraction.hpp"
template <class T> struct fraction {
  static_assert(is_integral_ext_v<T>);
  T num, den;
  constexpr fraction(const T &num = 0, const T &den = 1) : num(num), den(den) {}
  constexpr fraction operator-() const { return {-num, den}; }
  constexpr fraction operator-(const fraction &rhs) const {
    return {num * rhs.den - rhs.num * den, den * rhs.den};
  }
  constexpr bool operator<(const fraction &rhs) const {
    return operator-(rhs).num < 0;
  }

 private:
  constexpr void normalize();
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

