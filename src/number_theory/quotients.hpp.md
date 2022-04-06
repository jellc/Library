---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: src/utils/round_div.hpp
    title: Round Integer Division
  - icon: ':question:'
    path: src/utils/sfinae.hpp
    title: SFINAE
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"src/number_theory/quotients.hpp\"\n\n#include <vector>\n\
    \n#line 2 \"src/utils/round_div.hpp\"\n\n/*\n * @file round_div.hpp\n * @brief\
    \ Round Integer Division\n */\n\n#include <cassert>\n\n#line 2 \"src/utils/sfinae.hpp\"\
    \n\n/**\n * @file sfinae.hpp\n * @brief SFINAE\n */\n\n#include <cstdint>\n#include\
    \ <iterator>\n#include <type_traits>\n\n#ifndef __INT128_DEFINED__\n\n#ifdef __SIZEOF_INT128__\n\
    #define __INT128_DEFINED__ 1\n#else\n#define __INT128_DEFINED__ 0\n#endif\n\n\
    #endif\n\nnamespace std {\n\n#if __INT128_DEFINED__\n\ntemplate <> struct make_signed<__uint128_t>\
    \ { using type = __int128_t; };\ntemplate <> struct make_signed<__int128_t> {\
    \ using type = __int128_t; };\n\ntemplate <> struct make_unsigned<__uint128_t>\
    \ { using type = __uint128_t; };\ntemplate <> struct make_unsigned<__int128_t>\
    \ { using type = __uint128_t; };\n\ntemplate <> struct is_signed<__uint128_t>\
    \ : std::false_type {};\ntemplate <> struct is_signed<__int128_t> : std::true_type\
    \ {};\n\ntemplate <> struct is_unsigned<__uint128_t> : std::true_type {};\ntemplate\
    \ <> struct is_unsigned<__int128_t> : std::false_type {};\n\n#endif\n\n}  // namespace\
    \ std\n\nnamespace workspace {\n\ntemplate <class Tp, class... Args> struct variadic_front\
    \ { using type = Tp; };\n\ntemplate <class... Args> struct variadic_back;\n\n\
    template <class Tp> struct variadic_back<Tp> { using type = Tp; };\n\ntemplate\
    \ <class Tp, class... Args> struct variadic_back<Tp, Args...> {\n  using type\
    \ = typename variadic_back<Args...>::type;\n};\n\ntemplate <class type, template\
    \ <class> class trait>\nusing enable_if_trait_type = typename std::enable_if<trait<type>::value>::type;\n\
    \n/**\n * @brief Return type of subscripting ( @c [] ) access.\n */\ntemplate\
    \ <class _Tp>\nusing subscripted_type =\n    typename std::decay<decltype(std::declval<_Tp&>()[0])>::type;\n\
    \ntemplate <class Container>\nusing element_type = typename std::decay<decltype(*std::begin(\n\
    \    std::declval<Container&>()))>::type;\n\ntemplate <class _Tp, class = void>\
    \ struct has_begin : std::false_type {};\n\ntemplate <class _Tp>\nstruct has_begin<\n\
    \    _Tp, std::__void_t<decltype(std::begin(std::declval<const _Tp&>()))>>\n \
    \   : std::true_type {\n  using type = decltype(std::begin(std::declval<const\
    \ _Tp&>()));\n};\n\ntemplate <class _Tp, class = void> struct has_size : std::false_type\
    \ {};\n\ntemplate <class _Tp>\nstruct has_size<_Tp, std::__void_t<decltype(std::size(std::declval<_Tp>()))>>\n\
    \    : std::true_type {};\n\ntemplate <class _Tp, class = void> struct has_resize\
    \ : std::false_type {};\n\ntemplate <class _Tp>\nstruct has_resize<_Tp, std::__void_t<decltype(std::declval<_Tp>().resize(\n\
    \                           std::declval<size_t>()))>> : std::true_type {};\n\n\
    template <class _Tp, class = void> struct has_mod : std::false_type {};\n\ntemplate\
    \ <class _Tp>\nstruct has_mod<_Tp, std::__void_t<decltype(_Tp::mod)>> : std::true_type\
    \ {};\n\ntemplate <class _Tp, class = void> struct is_integral_ext : std::false_type\
    \ {};\ntemplate <class _Tp>\nstruct is_integral_ext<\n    _Tp, typename std::enable_if<std::is_integral<_Tp>::value>::type>\n\
    \    : std::true_type {};\n\n#if __INT128_DEFINED__\n\ntemplate <> struct is_integral_ext<__int128_t>\
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
    \    : first_arg<decltype(&_Tp::operator())> {};\n\ntemplate <class _Container,\
    \ class = void> struct get_dimension {\n  static constexpr size_t value = 0;\n\
    };\n\ntemplate <class _Container>\nstruct get_dimension<_Container,\n        \
    \             std::enable_if_t<has_begin<_Container>::value>> {\n  static constexpr\
    \ size_t value =\n      1 + get_dimension<typename std::iterator_traits<\n   \
    \           typename has_begin<_Container>::type>::value_type>::value;\n};\n\n\
    }  // namespace workspace\n#line 11 \"src/utils/round_div.hpp\"\n\nnamespace workspace\
    \ {\n\n/*\n * @fn floor_div\n * @brief floor of fraction.\n * @param x the numerator\n\
    \ * @param y the denominator\n * @return maximum integer z s.t. z <= x / y\n *\
    \ @note y must be nonzero.\n */\ntemplate <typename T1, typename T2>\nconstexpr\
    \ typename std::enable_if<(is_integral_ext<T1>::value &&\n                   \
    \                is_integral_ext<T2>::value),\n                              \
    \    typename std::common_type<T1, T2>::type>::type\nfloor_div(T1 x, T2 y) {\n\
    \  assert(y != 0);\n  if (y < 0) x = -x, y = -y;\n  return x < 0 ? (x - y + 1)\
    \ / y : x / y;\n}\n\n/*\n * @fn ceil_div\n * @brief ceil of fraction.\n * @param\
    \ x the numerator\n * @param y the denominator\n * @return minimum integer z s.t.\
    \ z >= x / y\n * @note y must be nonzero.\n */\ntemplate <typename T1, typename\
    \ T2>\nconstexpr typename std::enable_if<(is_integral_ext<T1>::value &&\n    \
    \                               is_integral_ext<T2>::value),\n               \
    \                   typename std::common_type<T1, T2>::type>::type\nceil_div(T1\
    \ x, T2 y) {\n  assert(y != 0);\n  if (y < 0) x = -x, y = -y;\n  return x < 0\
    \ ? x / y : (x + y - 1) / y;\n}\n\n}  // namespace workspace\n#line 6 \"src/number_theory/quotients.hpp\"\
    \n\nnamespace workspace {\n\ntemplate <class _Tp> auto quotients(_Tp __n) {\n\
    \  assert(__n >= 0);\n  std::vector<std::pair<_Tp, _Tp>> res;\n  for (_Tp q =\
    \ __n + 1; q;) {\n    _Tp k = __n / q + 1;\n    q = __n / k;\n    res.emplace_back(k,\
    \ q);\n  }\n  return res;\n}\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n#include <vector>\n\n#include \"src/utils/round_div.hpp\"\
    \n\nnamespace workspace {\n\ntemplate <class _Tp> auto quotients(_Tp __n) {\n\
    \  assert(__n >= 0);\n  std::vector<std::pair<_Tp, _Tp>> res;\n  for (_Tp q =\
    \ __n + 1; q;) {\n    _Tp k = __n / q + 1;\n    q = __n / k;\n    res.emplace_back(k,\
    \ q);\n  }\n  return res;\n}\n\n}  // namespace workspace\n"
  dependsOn:
  - src/utils/round_div.hpp
  - src/utils/sfinae.hpp
  isVerificationFile: false
  path: src/number_theory/quotients.hpp
  requiredBy: []
  timestamp: '2022-04-06 15:02:09+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/number_theory/quotients.hpp
layout: document
redirect_from:
- /library/src/number_theory/quotients.hpp
- /library/src/number_theory/quotients.hpp.html
title: src/number_theory/quotients.hpp
---
