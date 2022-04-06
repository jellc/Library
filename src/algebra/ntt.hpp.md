---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: src/number_theory/ext_gcd.hpp
    title: Extended Euclidean Algorithm
  - icon: ':x:'
    path: src/number_theory/primitive_root.hpp
    title: Primitive Root
  - icon: ':question:'
    path: src/utils/sfinae.hpp
    title: SFINAE
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Number Theoretic Transform
    links:
    - https://github.com/atcoder/ac-library/blob/master/atcoder/convolution.hpp
  bundledCode: "#line 2 \"src/algebra/ntt.hpp\"\n\n/**\n * @file ntt.hpp\n * @brief\
    \ Number Theoretic Transform\n * @date 2021-02-20\n *\n *\n */\n\n#line 2 \"src/number_theory/ext_gcd.hpp\"\
    \n\n/**\n * @file ext_gcd.hpp\n * @brief Extended Euclidean Algorithm\n */\n\n\
    #include <tuple>\n\n#line 2 \"src/utils/sfinae.hpp\"\n\n/**\n * @file sfinae.hpp\n\
    \ * @brief SFINAE\n */\n\n#include <cstdint>\n#include <iterator>\n#include <type_traits>\n\
    \n#ifndef __INT128_DEFINED__\n\n#ifdef __SIZEOF_INT128__\n#define __INT128_DEFINED__\
    \ 1\n#else\n#define __INT128_DEFINED__ 0\n#endif\n\n#endif\n\nnamespace std {\n\
    \n#if __INT128_DEFINED__\n\ntemplate <> struct make_signed<__uint128_t> { using\
    \ type = __int128_t; };\ntemplate <> struct make_signed<__int128_t> { using type\
    \ = __int128_t; };\n\ntemplate <> struct make_unsigned<__uint128_t> { using type\
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
    #line 11 \"src/number_theory/ext_gcd.hpp\"\n\nnamespace workspace {\n\n/**\n *\
    \ @param __a Integer\n * @param __b Integer\n * @return Pair of integers (x, y)\
    \ s.t. ax + by = g = gcd(a, b) and (b = 0 or 0\n * <= x < |b/g|) and (a = 0 or\
    \ -|a/g| < y <= 0). Return (0, 0) if (a, b) = (0,\n * 0).\n */\ntemplate <typename\
    \ _T1, typename _T2>\nconstexpr auto ext_gcd(_T1 __a, _T2 __b) noexcept {\n  static_assert(is_integral_ext<_T1>::value);\n\
    \  static_assert(is_integral_ext<_T2>::value);\n\n  using value_type = typename\
    \ std::make_signed<\n      typename std::common_type<_T1, _T2>::type>::type;\n\
    \  using result_type = std::pair<value_type, value_type>;\n\n  value_type a{__a},\
    \ b{__b}, p{1}, q{}, r{}, s{1};\n\n  while (b != value_type(0)) {\n    auto t\
    \ = a / b;\n    r ^= p ^= r ^= p -= t * r;\n    s ^= q ^= s ^= q -= t * s;\n \
    \   b ^= a ^= b ^= a -= t * b;\n  }\n\n  if (a < 0) p = -p, q = -q, a = -a;\n\n\
    \  if (p < 0) {\n    __a /= a, __b /= a;\n\n    if (__b > 0)\n      p += __b,\
    \ q -= __a;\n    else\n      p -= __b, q += __a;\n  }\n\n  return result_type{p,\
    \ q};\n}\n\n/**\n * @param __a Integer\n * @param __b Integer\n * @param __c Integer\n\
    \ * @return Pair of integers (x, y) s.t. ax + by = c and (b = 0 or 0 <= x <\n\
    \ * |b/g|). Return (0, 0) if there is no solution.\n */\ntemplate <typename _T1,\
    \ typename _T2, typename _T3>\nconstexpr auto ext_gcd(_T1 __a, _T2 __b, _T3 __c)\
    \ noexcept {\n  static_assert(is_integral_ext<_T1>::value);\n  static_assert(is_integral_ext<_T2>::value);\n\
    \  static_assert(is_integral_ext<_T3>::value);\n\n  using value_type = typename\
    \ std::make_signed<\n      typename std::common_type<_T1, _T2, _T3>::type>::type;\n\
    \  using result_type = std::pair<value_type, value_type>;\n\n  value_type a{__a},\
    \ b{__b}, p{1}, q{}, r{}, s{1};\n\n  while (b != value_type(0)) {\n    auto t\
    \ = a / b;\n    r ^= p ^= r ^= p -= t * r;\n    s ^= q ^= s ^= q -= t * s;\n \
    \   b ^= a ^= b ^= a -= t * b;\n  }\n\n  if (__c % a) return result_type{};\n\n\
    \  __a /= a, __b /= a, __c /= a;\n  p *= __c, q *= __c;\n\n  if (__b != value_type(0))\
    \ {\n    auto t = p / __b;\n    p -= __b * t;\n    q += __a * t;\n\n    if (p\
    \ < 0) {\n      if (__b > 0)\n        p += __b, q -= __a;\n      else\n      \
    \  p -= __b, q += __a;\n    }\n  }\n\n  return result_type{p, q};\n}\n\n}  //\
    \ namespace workspace\n#line 2 \"src/number_theory/primitive_root.hpp\"\n\n/**\n\
    \ * @file primitive_root.hpp\n * @brief Primitive Root\n * @date 2020-12-28\n\
    \ */\n\n#line 10 \"src/number_theory/primitive_root.hpp\"\n\nnamespace workspace\
    \ {\n\n/**\n * @brief Compile time primitive root.\n *\n * @tparam __mod Positive\
    \ integer\n * @return Minimum positive one if it exists. Otherwise 0.\n */\ntemplate\
    \ <class Tp>\nconstexpr typename std::enable_if<(is_integral_ext<Tp>::value),\
    \ Tp>::type\nprimitive_root(const Tp __mod) noexcept {\n  assert(__mod > 0);\n\
    \  using int_type = typename multiplicable_uint<Tp>::type;\n\n  int_type __r =\
    \ __mod, __p[16] = {}, *__q = __p;\n  for (int_type __i = 2; __i <= __r / __i;\
    \ ++__i) {\n    if (__r % __i) continue;\n    *__q++ = __i;\n    while (!(__r\
    \ % __i)) __r /= __i;\n  }\n  if (__r != 1) *__q++ = __r;\n\n  int_type __tot\
    \ = __mod;\n  for (__q = __p; *__q; *__q++ = 0) (__tot /= *__q) *= *__q - 1;\n\
    \  __r = __tot, __q = __p + 1, __p[0] = 1;\n  for (int_type __i = 2; __i <= __r\
    \ / __i; ++__i) {\n    if (__r % __i) continue;\n    *__q++ = __i;\n    while\
    \ (!(__r % __i)) __r /= __i;\n  }\n  if (__r != 1) *__q++ = __r;\n\n  for (Tp\
    \ __r = 1; __r != __mod; ++__r) {\n    auto __cnt = 0;\n    for (__q = __p; *__q;\
    \ ++__q) {\n      int_type __w = 1;\n      for (int_type __e = __tot / *__q, __x\
    \ = __r; __e;\n           __e >>= 1, (__x *= __x) %= __mod)\n        if (__e &\
    \ 1) (__w *= __x) %= __mod;\n      if (__w == 1 && ++__cnt > 1) break;\n    }\n\
    \    if (__cnt == 1) return __r;\n  }\n\n  return 0;\n};\n\n}  // namespace workspace\n\
    #line 13 \"src/algebra/ntt.hpp\"\n\nnamespace workspace {\n\nnamespace ntt_impl\
    \ {\n\n/**\n * @see\n * https://github.com/atcoder/ac-library/blob/master/atcoder/convolution.hpp\n\
    \ */\n\ntemplate <class _Tp> struct __coef {\n  _Tp sum_e[30];  // sum_e[i] =\
    \ ies[0] * ... * ies[i - 1] * es[i]\n\n  constexpr __coef() : sum_e{} {\n    if\
    \ (_Tp::mod < 2) return;\n\n    int cnt2 = __builtin_ctz(_Tp::mod - 1);\n    _Tp\
    \ e = 1;\n    {\n      auto p = (_Tp::mod - 1) >> cnt2;\n      _Tp w = primitive_root(_Tp::mod);\n\
    \      while (p) {\n        if (p & 1) e *= w;\n        p >>= 1;\n        w *=\
    \ w;\n      }\n    }\n\n    _Tp ie = ext_gcd(decltype(_Tp::mod)(e), _Tp::mod).first;\n\
    \    _Tp es[30] = {}, ies[30] = {};  // es[i]^(2^(2+i)) == 1\n    for (int i =\
    \ cnt2; i >= 2; i--) {\n      // e^(2^i) == 1\n      es[i - 2] = e;\n      ies[i\
    \ - 2] = ie;\n      e *= e;\n      ie *= ie;\n    }\n\n    _Tp now = 1;\n    for\
    \ (int i = 0; i <= cnt2 - 2; i++) {\n      sum_e[i] = es[i] * now;\n      now\
    \ *= ies[i];\n    }\n  }\n};\n\ntemplate <class _Tp> struct __icoef {\n  _Tp sum_ie[30];\
    \  // sum_e[i] = ies[0] * ... * ies[i - 1] * es[i]\n\n  constexpr __icoef() :\
    \ sum_ie{} {\n    if (_Tp::mod < 2) return;\n\n    int cnt2 = __builtin_ctz(_Tp::mod\
    \ - 1);\n    _Tp e = 1;\n    {\n      auto p = (_Tp::mod - 1) >> cnt2;\n     \
    \ _Tp w = primitive_root(_Tp::mod);\n      while (p) {\n        if (p & 1) e *=\
    \ w;\n        p >>= 1;\n        w *= w;\n      }\n    }\n\n    _Tp ie = ext_gcd(decltype(_Tp::mod)(e),\
    \ _Tp::mod).first;\n    _Tp es[30] = {}, ies[30] = {};  // es[i]^(2^(2+i)) ==\
    \ 1\n    for (int i = cnt2; i >= 2; i--) {\n      // e^(2^i) == 1\n      es[i\
    \ - 2] = e;\n      ies[i - 2] = ie;\n      e *= e;\n      ie *= ie;\n    }\n\n\
    \    _Tp now = 1;\n    for (int i = 0; i <= cnt2 - 2; i++) {\n      sum_ie[i]\
    \ = ies[i] * now;\n      now *= es[i];\n    }\n  }\n};\n\ntemplate <class _Tp>\
    \ struct __ipow2 {\n  _Tp __ip2[30];\n  constexpr __ipow2() : __ip2{1, (1 + _Tp::mod)\
    \ / 2} {\n    for (size_t __i = 1; __i + 1 != std::size(__ip2); ++__i)\n     \
    \ __ip2[__i + 1] = __ip2[__i] * __ip2[1];\n  }\n};\n\ntemplate <class _FIter>\n\
    constexpr void ntt(_FIter __first, _FIter __last) noexcept {\n  using value_type\
    \ = typename std::decay<decltype(*__first)>::type;\n  constexpr __coef<value_type>\
    \ _;\n\n  auto __h = __builtin_ctz(std::distance(__first, __last));\n\n  for (ptrdiff_t\
    \ __p = 1 << __h; __p >>= 1;) {\n    value_type now = -1;\n    auto __l = __first;\n\
    \n    for (size_t __s = 1 << __h; __l != __last;\n         now *= _.sum_e[__builtin_ctz(--__s)])\
    \ {\n      auto __r = __l + __p;\n\n      for (auto __mid = __r; __l != __mid;\
    \ ++__l, ++__r) {\n        auto __tmp = *__l;\n        *__l -= *__r *= now;\n\
    \        *__r += __tmp;\n      }\n\n      __l = __r;\n    }\n  }\n}\n\ntemplate\
    \ <class _A> constexpr void ntt(_A &a) noexcept {\n  ntt(std::begin(a), std::end(a));\n\
    }\n\ntemplate <class _FIter>\nconstexpr void intt(_FIter __first, _FIter __last)\
    \ noexcept {\n  using value_type = typename std::decay<decltype(*__first)>::type;\n\
    \  constexpr __icoef<value_type> _;\n\n  auto __h = __builtin_ctz(std::distance(__first,\
    \ __last));\n\n  for (ptrdiff_t __p = 1; __p >> __h ^ 1; __p <<= 1) {\n    value_type\
    \ inow = 1;\n    auto __l = __first;\n\n    for (size_t __s = 1 << __h; __l !=\
    \ __last;\n         inow *= _.sum_ie[__builtin_ctz(--__s)]) {\n      auto __r\
    \ = __l + __p;\n\n      for (auto __mid = __r; __l != __mid; ++__l, ++__r) {\n\
    \        auto __tmp = (*__l - *__r) * inow;\n        *__l += *__r;\n        *__r\
    \ = __tmp;\n      }\n\n      __l = __r;\n    }\n  }\n\n  constexpr __ipow2<value_type>\
    \ __;\n  while (__first != __last) *--__last *= __.__ip2[__h];\n}  // namespace\
    \ ntt_impl\n\ntemplate <class _A> constexpr void intt(_A &a) noexcept {\n  intt(std::begin(a),\
    \ std::end(a));\n}\n\n}  // namespace ntt_impl\n\nusing ntt_impl::intt;\nusing\
    \ ntt_impl::ntt;\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file ntt.hpp\n * @brief Number Theoretic Transform\n\
    \ * @date 2021-02-20\n *\n *\n */\n\n#include \"src/number_theory/ext_gcd.hpp\"\
    \n#include \"src/number_theory/primitive_root.hpp\"\n\nnamespace workspace {\n\
    \nnamespace ntt_impl {\n\n/**\n * @see\n * https://github.com/atcoder/ac-library/blob/master/atcoder/convolution.hpp\n\
    \ */\n\ntemplate <class _Tp> struct __coef {\n  _Tp sum_e[30];  // sum_e[i] =\
    \ ies[0] * ... * ies[i - 1] * es[i]\n\n  constexpr __coef() : sum_e{} {\n    if\
    \ (_Tp::mod < 2) return;\n\n    int cnt2 = __builtin_ctz(_Tp::mod - 1);\n    _Tp\
    \ e = 1;\n    {\n      auto p = (_Tp::mod - 1) >> cnt2;\n      _Tp w = primitive_root(_Tp::mod);\n\
    \      while (p) {\n        if (p & 1) e *= w;\n        p >>= 1;\n        w *=\
    \ w;\n      }\n    }\n\n    _Tp ie = ext_gcd(decltype(_Tp::mod)(e), _Tp::mod).first;\n\
    \    _Tp es[30] = {}, ies[30] = {};  // es[i]^(2^(2+i)) == 1\n    for (int i =\
    \ cnt2; i >= 2; i--) {\n      // e^(2^i) == 1\n      es[i - 2] = e;\n      ies[i\
    \ - 2] = ie;\n      e *= e;\n      ie *= ie;\n    }\n\n    _Tp now = 1;\n    for\
    \ (int i = 0; i <= cnt2 - 2; i++) {\n      sum_e[i] = es[i] * now;\n      now\
    \ *= ies[i];\n    }\n  }\n};\n\ntemplate <class _Tp> struct __icoef {\n  _Tp sum_ie[30];\
    \  // sum_e[i] = ies[0] * ... * ies[i - 1] * es[i]\n\n  constexpr __icoef() :\
    \ sum_ie{} {\n    if (_Tp::mod < 2) return;\n\n    int cnt2 = __builtin_ctz(_Tp::mod\
    \ - 1);\n    _Tp e = 1;\n    {\n      auto p = (_Tp::mod - 1) >> cnt2;\n     \
    \ _Tp w = primitive_root(_Tp::mod);\n      while (p) {\n        if (p & 1) e *=\
    \ w;\n        p >>= 1;\n        w *= w;\n      }\n    }\n\n    _Tp ie = ext_gcd(decltype(_Tp::mod)(e),\
    \ _Tp::mod).first;\n    _Tp es[30] = {}, ies[30] = {};  // es[i]^(2^(2+i)) ==\
    \ 1\n    for (int i = cnt2; i >= 2; i--) {\n      // e^(2^i) == 1\n      es[i\
    \ - 2] = e;\n      ies[i - 2] = ie;\n      e *= e;\n      ie *= ie;\n    }\n\n\
    \    _Tp now = 1;\n    for (int i = 0; i <= cnt2 - 2; i++) {\n      sum_ie[i]\
    \ = ies[i] * now;\n      now *= es[i];\n    }\n  }\n};\n\ntemplate <class _Tp>\
    \ struct __ipow2 {\n  _Tp __ip2[30];\n  constexpr __ipow2() : __ip2{1, (1 + _Tp::mod)\
    \ / 2} {\n    for (size_t __i = 1; __i + 1 != std::size(__ip2); ++__i)\n     \
    \ __ip2[__i + 1] = __ip2[__i] * __ip2[1];\n  }\n};\n\ntemplate <class _FIter>\n\
    constexpr void ntt(_FIter __first, _FIter __last) noexcept {\n  using value_type\
    \ = typename std::decay<decltype(*__first)>::type;\n  constexpr __coef<value_type>\
    \ _;\n\n  auto __h = __builtin_ctz(std::distance(__first, __last));\n\n  for (ptrdiff_t\
    \ __p = 1 << __h; __p >>= 1;) {\n    value_type now = -1;\n    auto __l = __first;\n\
    \n    for (size_t __s = 1 << __h; __l != __last;\n         now *= _.sum_e[__builtin_ctz(--__s)])\
    \ {\n      auto __r = __l + __p;\n\n      for (auto __mid = __r; __l != __mid;\
    \ ++__l, ++__r) {\n        auto __tmp = *__l;\n        *__l -= *__r *= now;\n\
    \        *__r += __tmp;\n      }\n\n      __l = __r;\n    }\n  }\n}\n\ntemplate\
    \ <class _A> constexpr void ntt(_A &a) noexcept {\n  ntt(std::begin(a), std::end(a));\n\
    }\n\ntemplate <class _FIter>\nconstexpr void intt(_FIter __first, _FIter __last)\
    \ noexcept {\n  using value_type = typename std::decay<decltype(*__first)>::type;\n\
    \  constexpr __icoef<value_type> _;\n\n  auto __h = __builtin_ctz(std::distance(__first,\
    \ __last));\n\n  for (ptrdiff_t __p = 1; __p >> __h ^ 1; __p <<= 1) {\n    value_type\
    \ inow = 1;\n    auto __l = __first;\n\n    for (size_t __s = 1 << __h; __l !=\
    \ __last;\n         inow *= _.sum_ie[__builtin_ctz(--__s)]) {\n      auto __r\
    \ = __l + __p;\n\n      for (auto __mid = __r; __l != __mid; ++__l, ++__r) {\n\
    \        auto __tmp = (*__l - *__r) * inow;\n        *__l += *__r;\n        *__r\
    \ = __tmp;\n      }\n\n      __l = __r;\n    }\n  }\n\n  constexpr __ipow2<value_type>\
    \ __;\n  while (__first != __last) *--__last *= __.__ip2[__h];\n}  // namespace\
    \ ntt_impl\n\ntemplate <class _A> constexpr void intt(_A &a) noexcept {\n  intt(std::begin(a),\
    \ std::end(a));\n}\n\n}  // namespace ntt_impl\n\nusing ntt_impl::intt;\nusing\
    \ ntt_impl::ntt;\n\n}  // namespace workspace\n"
  dependsOn:
  - src/number_theory/ext_gcd.hpp
  - src/utils/sfinae.hpp
  - src/number_theory/primitive_root.hpp
  isVerificationFile: false
  path: src/algebra/ntt.hpp
  requiredBy: []
  timestamp: '2021-07-16 03:07:50+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/algebra/ntt.hpp
layout: document
redirect_from:
- /library/src/algebra/ntt.hpp
- /library/src/algebra/ntt.hpp.html
title: Number Theoretic Transform
---
