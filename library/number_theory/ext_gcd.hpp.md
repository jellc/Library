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


# :heavy_check_mark: number_theory/ext_gcd.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#814c07620aec62314b2fd23fc462e282">number_theory</a>
* <a href="{{ site.github.repository_url }}/blob/master/number_theory/ext_gcd.hpp">View this file on GitHub</a>
    - Last commit date: 2020-09-13 15:12:39+09:00




## Depends on

* :heavy_check_mark: <a href="../utils/sfinae.hpp.html">utils/sfinae.hpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aizu-online-judge/extended_euclid_algorithm.test.cpp.html">test/aizu-online-judge/extended_euclid_algorithm.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <tuple>

#include "utils/sfinae.hpp"
template <class int_type>
constexpr typename std::enable_if<is_integral_ext<int_type>::value,
                                  std::pair<int_type, int_type>>::type
ext_gcd(int_type a, int_type b) {
  bool neg_a = a < 0, neg_b = b < 0;
  int_type p{1}, q{}, r{}, s{1}, t{};
  while (b) {
    r ^= p ^= r ^= p -= (t = a / b) * r;
    s ^= q ^= s ^= q -= t * s;
    b ^= a ^= b ^= a %= b;
  }
  return {neg_a ? -p : p, neg_b ? -q : q};
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "number_theory/ext_gcd.hpp"
#include <tuple>

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
#line 5 "number_theory/ext_gcd.hpp"
template <class int_type>
constexpr typename std::enable_if<is_integral_ext<int_type>::value,
                                  std::pair<int_type, int_type>>::type
ext_gcd(int_type a, int_type b) {
  bool neg_a = a < 0, neg_b = b < 0;
  int_type p{1}, q{}, r{}, s{1}, t{};
  while (b) {
    r ^= p ^= r ^= p -= (t = a / b) * r;
    s ^= q ^= s ^= q -= t * s;
    b ^= a ^= b ^= a %= b;
  }
  return {neg_a ? -p : p, neg_b ? -q : q};
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

