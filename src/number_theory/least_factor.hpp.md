---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: src/utils/sfinae.hpp
    title: SFINAE
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Least Prime Factor
    links: []
  bundledCode: "#line 2 \"src/number_theory/least_factor.hpp\"\n\n/*\n * @file least_factor.hpp\n\
    \ * @brief Least Prime Factor\n */\n\n#include <cassert>\n#include <vector>\n\n\
    #line 2 \"src/utils/sfinae.hpp\"\n\n/**\n * @file sfinae.hpp\n * @brief SFINAE\n\
    \ */\n\n#include <cstdint>\n#include <iterator>\n#include <type_traits>\n\n#ifndef\
    \ __INT128_DEFINED__\n\n#ifdef __SIZEOF_INT128__\n#define __INT128_DEFINED__ 1\n\
    #else\n#define __INT128_DEFINED__ 0\n#endif\n\n#endif\n\nnamespace std {\n\n#if\
    \ __INT128_DEFINED__\n\ntemplate <> struct make_signed<__uint128_t> { using type\
    \ = __int128_t; };\ntemplate <> struct make_signed<__int128_t> { using type =\
    \ __int128_t; };\n\ntemplate <> struct make_unsigned<__uint128_t> { using type\
    \ = __uint128_t; };\ntemplate <> struct make_unsigned<__int128_t> { using type\
    \ = __uint128_t; };\n\ntemplate <> struct is_signed<__uint128_t> : std::false_type\
    \ {};\ntemplate <> struct is_signed<__int128_t> : std::true_type {};\n\ntemplate\
    \ <> struct is_unsigned<__uint128_t> : std::true_type {};\ntemplate <> struct\
    \ is_unsigned<__int128_t> : std::false_type {};\n\n#endif\n\n}  // namespace std\n\
    \nnamespace workspace {\n\ntemplate <class Tp, class... Args> struct variadic_front\
    \ { using type = Tp; };\n\ntemplate <class... Args> struct variadic_back;\n\n\
    template <class Tp> struct variadic_back<Tp> { using type = Tp; };\n\ntemplate\
    \ <class Tp, class... Args> struct variadic_back<Tp, Args...> {\n  using type\
    \ = typename variadic_back<Args...>::type;\n};\n\ntemplate <class type, template\
    \ <class> class trait>\nusing enable_if_trait_type = typename std::enable_if<trait<type>::value>::type;\n\
    \n/**\n * @brief Return type of subscripting ( @c [] ) access.\n */\ntemplate\
    \ <class _Tp>\nusing subscripted_type =\n    typename std::decay<decltype(std::declval<_Tp&>()[0])>::type;\n\
    \ntemplate <class Container>\nusing element_type = typename std::decay<decltype(\n\
    \    *std::begin(std::declval<Container&>()))>::type;\n\ntemplate <class _Tp,\
    \ class = std::nullptr_t>\nstruct has_begin : std::false_type {};\n\ntemplate\
    \ <class _Tp>\nstruct has_begin<_Tp, decltype(std::begin(std::declval<_Tp>()),\
    \ nullptr)>\n    : std::true_type {};\n\ntemplate <class _Tp, class = void> struct\
    \ has_mod : std::false_type {};\n\ntemplate <class _Tp>\nstruct has_mod<_Tp, std::__void_t<decltype(_Tp::mod)>>\
    \ : std::true_type {};\n\ntemplate <class _Tp, class = void> struct is_integral_ext\
    \ : std::false_type {};\ntemplate <class _Tp>\nstruct is_integral_ext<\n    _Tp,\
    \ typename std::enable_if<std::is_integral<_Tp>::value>::type>\n    : std::true_type\
    \ {};\n\n#if __INT128_DEFINED__\n\ntemplate <> struct is_integral_ext<__int128_t>\
    \ : std::true_type {};\ntemplate <> struct is_integral_ext<__uint128_t> : std::true_type\
    \ {};\n\n#endif\n\n#if __cplusplus >= 201402\n\ntemplate <class _Tp>\nconstexpr\
    \ static bool is_integral_ext_v = is_integral_ext<_Tp>::value;\n\n#endif\n\ntemplate\
    \ <typename _Tp, typename = void> struct multiplicable_uint {\n  using type =\
    \ uint_least32_t;\n};\ntemplate <typename _Tp>\nstruct multiplicable_uint<\n \
    \   _Tp,\n    typename std::enable_if<(2 < sizeof(_Tp)) &&\n                 \
    \           (!__INT128_DEFINED__ || sizeof(_Tp) <= 4)>::type> {\n  using type\
    \ = uint_least64_t;\n};\n\n#if __INT128_DEFINED__\n\ntemplate <typename _Tp>\n\
    struct multiplicable_uint<_Tp,\n                          typename std::enable_if<(4\
    \ < sizeof(_Tp))>::type> {\n  using type = __uint128_t;\n};\n\n#endif\n\ntemplate\
    \ <typename _Tp> struct multiplicable_int {\n  using type =\n      typename std::make_signed<typename\
    \ multiplicable_uint<_Tp>::type>::type;\n};\n\ntemplate <typename _Tp> struct\
    \ multiplicable {\n  using type = std::conditional_t<\n      is_integral_ext<_Tp>::value,\n\
    \      std::conditional_t<std::is_signed<_Tp>::value,\n                      \
    \   typename multiplicable_int<_Tp>::type,\n                         typename\
    \ multiplicable_uint<_Tp>::type>,\n      _Tp>;\n};\n\ntemplate <class> struct\
    \ first_arg { using type = void; };\n\ntemplate <class _R, class _Tp, class...\
    \ _Args>\nstruct first_arg<_R(_Tp, _Args...)> {\n  using type = _Tp;\n};\n\ntemplate\
    \ <class _R, class _Tp, class... _Args>\nstruct first_arg<_R (*)(_Tp, _Args...)>\
    \ {\n  using type = _Tp;\n};\n\ntemplate <class _G, class _R, class _Tp, class...\
    \ _Args>\nstruct first_arg<_R (_G::*)(_Tp, _Args...)> {\n  using type = _Tp;\n\
    };\n\ntemplate <class _G, class _R, class _Tp, class... _Args>\nstruct first_arg<_R\
    \ (_G::*)(_Tp, _Args...) const> {\n  using type = _Tp;\n};\n\ntemplate <class\
    \ _Tp, class = void> struct parse_compare : first_arg<_Tp> {};\n\ntemplate <class\
    \ _Tp>\nstruct parse_compare<_Tp, std::__void_t<decltype(&_Tp::operator())>>\n\
    \    : first_arg<decltype(&_Tp::operator())> {};\n\n}  // namespace workspace\n\
    #line 12 \"src/number_theory/least_factor.hpp\"\n\nnamespace workspace {\n\n/*\n\
    \ * @class least_factor\n * @brief Calculate the least prime factor for positive\
    \ integers.\n * @tparam N Range of calculation, exclusive\n */\ntemplate <unsigned\
    \ N> class least_factor {\n  unsigned least[N], prime[N >> 3], n;\n\n public:\n\
    \  constexpr least_factor() : least{1}, prime{}, n{} {\n    for (auto i = 2u;\
    \ i < N; ++i) {\n      if (!least[i]) prime[n++] = least[i] = i;\n      for (auto\
    \ *p = prime; *p && *p <= least[i] && *p * i < N; ++p) {\n        least[*p * i]\
    \ = *p;\n      }\n    }\n  }\n\n  /*\n   * @param x an integer with 0 < |x| <\
    \ N\n   * @return Least prime factor of x\n   */\n  template <typename int_type>\n\
    \  constexpr\n      typename std::enable_if<is_integral_ext<int_type>::value,\
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
  timestamp: '2021-05-25 17:32:10+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/number_theory/least_factor.hpp
layout: document
redirect_from:
- /library/src/number_theory/least_factor.hpp
- /library/src/number_theory/least_factor.hpp.html
title: Least Prime Factor
---
