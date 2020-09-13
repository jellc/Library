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


# :heavy_check_mark: utils/sfinae.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#2b3583e6e17721c54496bd04e57a0c15">utils</a>
* <a href="{{ site.github.repository_url }}/blob/master/utils/sfinae.hpp">View this file on GitHub</a>
    - Last commit date: 2020-09-13 23:59:20+09:00




## Required by

* :heavy_check_mark: <a href="../combinatorics/binomial.hpp.html">combinatorics/binomial.hpp</a>
* :heavy_check_mark: <a href="../data_structure/segment_tree/basic.hpp.html">data_structure/segment_tree/basic.hpp</a>
* :heavy_check_mark: <a href="../data_structure/segment_tree/lazy.hpp.html">data_structure/segment_tree/lazy.hpp</a>
* :warning: <a href="../dev/fraction.hpp.html">dev/fraction.hpp</a>
* :heavy_check_mark: <a href="../modulus/inverse.hpp.html">modulus/inverse.hpp</a>
* :heavy_check_mark: <a href="../modulus/modint.hpp.html">modulus/modint.hpp</a>
* :heavy_check_mark: <a href="../number_theory/ext_gcd.hpp.html">number_theory/ext_gcd.hpp</a>
* :heavy_check_mark: <a href="../string/suffix_array.hpp.html">string/suffix_array.hpp</a>
* :warning: <a href="../template.cpp.html">template.cpp</a>
* :heavy_check_mark: <a href="hash.hpp.html">utils/hash.hpp</a>
* :heavy_check_mark: <a href="stream.hpp.html">utils/stream.hpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aizu-online-judge/balls_and_boxes_4.test.cpp.html">test/aizu-online-judge/balls_and_boxes_4.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aizu-online-judge/extended_euclid_algorithm.test.cpp.html">test/aizu-online-judge/extended_euclid_algorithm.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/library-checker/associative_array.test.cpp.html">test/library-checker/associative_array.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/library-checker/number_of_substrings.test.cpp.html">test/library-checker/number_of_substrings.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/library-checker/point_set_range_composite.test.cpp.html">test/library-checker/point_set_range_composite.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/library-checker/queue_operate_all_composite.test.cpp.html">test/library-checker/queue_operate_all_composite.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/library-checker/range_affine_range_sum.test.cpp.html">test/library-checker/range_affine_range_sum.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/library-checker/static_range_inversions_query.test.cpp.html">test/library-checker/static_range_inversions_query.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/library-checker/subset_convolution.test.cpp.html">test/library-checker/subset_convolution.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/library-checker/suffix_array.test.cpp.html">test/library-checker/suffix_array.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/library-checker/zalgorithm.test.cpp.html">test/library-checker/zalgorithm.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

