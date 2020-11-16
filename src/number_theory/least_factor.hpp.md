---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/utils/sfinae.hpp
    title: src/utils/sfinae.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Least Prime Factor
    links: []
  bundledCode: "#line 2 \"src/number_theory/least_factor.hpp\"\n\n/*\n * @file least_factor.hpp\n\
    \ * @brief Least Prime Factor\n */\n\n#include <cassert>\n#include <vector>\n\n\
    #line 2 \"src/utils/sfinae.hpp\"\n#include <cstdint>\n#include <iterator>\n#include\
    \ <type_traits>\n\ntemplate <class type, template <class> class trait>\nusing\
    \ enable_if_trait_type = typename std::enable_if<trait<type>::value>::type;\n\n\
    template <class Container>\nusing element_type = typename std::decay<decltype(\n\
    \    *std::begin(std::declval<Container&>()))>::type;\n\ntemplate <class T, class\
    \ = int> struct mapped_of {\n  using type = element_type<T>;\n};\ntemplate <class\
    \ T>\nstruct mapped_of<T,\n                 typename std::pair<int, typename T::mapped_type>::first_type>\
    \ {\n  using type = typename T::mapped_type;\n};\ntemplate <class T> using mapped_type\
    \ = typename mapped_of<T>::type;\n\ntemplate <class T, class = void> struct is_integral_ext\
    \ : std::false_type {};\ntemplate <class T>\nstruct is_integral_ext<\n    T, typename\
    \ std::enable_if<std::is_integral<T>::value>::type>\n    : std::true_type {};\n\
    template <> struct is_integral_ext<__int128_t> : std::true_type {};\ntemplate\
    \ <> struct is_integral_ext<__uint128_t> : std::true_type {};\n#if __cplusplus\
    \ >= 201402\ntemplate <class T>\nconstexpr static bool is_integral_ext_v = is_integral_ext<T>::value;\n\
    #endif\n\ntemplate <typename T, typename = void> struct multiplicable_uint {\n\
    \  using type = uint_least32_t;\n};\ntemplate <typename T>\nstruct multiplicable_uint<T,\
    \ typename std::enable_if<(2 < sizeof(T))>::type> {\n  using type = uint_least64_t;\n\
    };\ntemplate <typename T>\nstruct multiplicable_uint<T, typename std::enable_if<(4\
    \ < sizeof(T))>::type> {\n  using type = __uint128_t;\n};\n#line 12 \"src/number_theory/least_factor.hpp\"\
    \n\nnamespace workspace {\n\n/*\n * @class least_factor\n * @brief Calculate the\
    \ least prime factor for positive integers.\n * @tparam N Range of calculation,\
    \ exclusive\n */\ntemplate <unsigned N> class least_factor {\n  unsigned least[N],\
    \ prime[N >> 3], n;\n\n public:\n  constexpr least_factor() : least{1}, prime{},\
    \ n{} {\n    for (auto i = 2u; i < N; ++i) {\n      if (!least[i]) prime[n++]\
    \ = least[i] = i;\n      for (auto *p = prime; *p && *p <= least[i] && *p * i\
    \ < N; ++p) {\n        least[*p * i] = *p;\n      }\n    }\n  }\n\n  /*\n   *\
    \ @param x an integer with 0 < |x| < N\n   * @return Least prime factor of x\n\
    \   */\n  template <typename int_type>\n  constexpr\n      typename std::enable_if<is_integral_ext<int_type>::value,\
    \ int_type>::type\n      operator()(int_type x) const {\n    assert(x);\n    if\
    \ (x < 0) x = -x;\n    assert(x < N);\n    return least[x];\n  }\n\n  /*\n   *\
    \ @fn primes\n   * @return Sorted list of prime numbers less than N\n   */\n \
    \ const std::vector<unsigned> &primes() const {\n    static const std::vector<unsigned>\
    \ prime_vector(prime, prime + n);\n    return prime_vector;\n  }\n};\n\n}  //\
    \ namespace workspace\n"
  code: "#pragma once\n\n/*\n * @file least_factor.hpp\n * @brief Least Prime Factor\n\
    \ */\n\n#include <cassert>\n#include <vector>\n\n#include \"src/utils/sfinae.hpp\"\
    \n\nnamespace workspace {\n\n/*\n * @class least_factor\n * @brief Calculate the\
    \ least prime factor for positive integers.\n * @tparam N Range of calculation,\
    \ exclusive\n */\ntemplate <unsigned N> class least_factor {\n  unsigned least[N],\
    \ prime[N >> 3], n;\n\n public:\n  constexpr least_factor() : least{1}, prime{},\
    \ n{} {\n    for (auto i = 2u; i < N; ++i) {\n      if (!least[i]) prime[n++]\
    \ = least[i] = i;\n      for (auto *p = prime; *p && *p <= least[i] && *p * i\
    \ < N; ++p) {\n        least[*p * i] = *p;\n      }\n    }\n  }\n\n  /*\n   *\
    \ @param x an integer with 0 < |x| < N\n   * @return Least prime factor of x\n\
    \   */\n  template <typename int_type>\n  constexpr\n      typename std::enable_if<is_integral_ext<int_type>::value,\
    \ int_type>::type\n      operator()(int_type x) const {\n    assert(x);\n    if\
    \ (x < 0) x = -x;\n    assert(x < N);\n    return least[x];\n  }\n\n  /*\n   *\
    \ @fn primes\n   * @return Sorted list of prime numbers less than N\n   */\n \
    \ const std::vector<unsigned> &primes() const {\n    static const std::vector<unsigned>\
    \ prime_vector(prime, prime + n);\n    return prime_vector;\n  }\n};\n\n}  //\
    \ namespace workspace\n"
  dependsOn:
  - src/utils/sfinae.hpp
  isVerificationFile: false
  path: src/number_theory/least_factor.hpp
  requiredBy: []
  timestamp: '2020-11-16 22:50:09+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/number_theory/least_factor.hpp
layout: document
redirect_from:
- /library/src/number_theory/least_factor.hpp
- /library/src/number_theory/least_factor.hpp.html
title: Least Prime Factor
---
