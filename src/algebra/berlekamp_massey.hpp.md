---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/algebra/ntt.hpp
    title: Number Theoretic Transform
  - icon: ':heavy_check_mark:'
    path: src/algebra/polynomial.hpp
    title: Polynomial
  - icon: ':heavy_check_mark:'
    path: src/number_theory/ext_gcd.hpp
    title: Extended Euclidean Algorithm
  - icon: ':heavy_check_mark:'
    path: src/number_theory/primitive_root.hpp
    title: Primitive Root
  - icon: ':heavy_check_mark:'
    path: src/utils/sfinae.hpp
    title: SFINAE
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/library-checker/find_linear_recurrence.test.cpp
    title: test/library-checker/find_linear_recurrence.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Berlekamp-Massey Algorithm
    links: []
  bundledCode: "#line 2 \"src/algebra/berlekamp_massey.hpp\"\n\n/**\n * @file berlekamp_massey.hpp\n\
    \ * @brief Berlekamp-Massey Algorithm\n */\n\n#include <numeric>\n\n#line 2 \"\
    src/algebra/polynomial.hpp\"\n\n/**\n * @file polynomial.hpp\n * @brief Polynomial\n\
    \ */\n\n#include <algorithm>\n#include <cassert>\n#include <vector>\n\n#line 2\
    \ \"lib/cxx17\"\n\n#ifndef _CXX17_CONSTEXPR\n#if __cplusplus >= 201703L\n#define\
    \ _CXX17_CONSTEXPR constexpr\n#else\n#define _CXX17_CONSTEXPR\n#endif\n#endif\n\
    \n#ifndef _CXX17_STATIC_ASSERT\n#if __cplusplus >= 201703L\n#define _CXX17_STATIC_ASSERT\
    \ static_assert\n#else\n#define _CXX17_STATIC_ASSERT assert\n#endif\n#endif\n\n\
    #if __cplusplus < 201703L\n\nnamespace std {\n\n/**\n *  @brief  Return the size\
    \ of a container.\n *  @param  __cont  Container.\n */\ntemplate <typename _Container>\n\
    constexpr auto size(const _Container& __cont) noexcept(noexcept(__cont.size()))\n\
    \    -> decltype(__cont.size()) {\n  return __cont.size();\n}\n\n/**\n *  @brief\
    \  Return the size of an array.\n */\ntemplate <typename _Tp, size_t _Nm>\nconstexpr\
    \ size_t size(const _Tp (&)[_Nm]) noexcept {\n  return _Nm;\n}\n\n}  // namespace\
    \ std\n\n#endif\n#line 2 \"src/algebra/ntt.hpp\"\n\n/**\n * @file ntt.hpp\n *\
    \ @brief Number Theoretic Transform\n * @date 2021-02-20\n *\n *\n */\n\n#line\
    \ 2 \"src/number_theory/ext_gcd.hpp\"\n\n/**\n * @file ext_gcd.hpp\n * @brief\
    \ Extended Euclidean Algorithm\n */\n\n#include <tuple>\n\n#line 2 \"src/utils/sfinae.hpp\"\
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
    \ s.t. ax + by = g = gcd(a, b), 0 <= x <\n * |b/g|, -|a/g| < y <= 0. Return (0,\
    \ 0) if (a, b) = (0, 0).\n */\ntemplate <typename _T1, typename _T2> constexpr\
    \ auto ext_gcd(_T1 __a, _T2 __b) {\n  static_assert(is_integral_ext<_T1>::value);\n\
    \  static_assert(is_integral_ext<_T2>::value);\n\n  using result_type = typename\
    \ std::make_signed<\n      typename std::common_type<_T1, _T2>::type>::type;\n\
    \n  result_type a{__a}, b{__b}, p{1}, q{}, r{}, s{1};\n\n  // Euclidean algorithm\n\
    \  while (b) {\n    result_type t = a / b;\n    r ^= p ^= r ^= p -= t * r;\n \
    \   s ^= q ^= s ^= q -= t * s;\n    b ^= a ^= b ^= a -= t * b;\n  }\n\n  // Normalize\n\
    \  if (a < 0) p = -p, q = -q;\n  if (p < 0) p += __b / a, q -= __a / a;\n\n  return\
    \ std::make_pair(p, q);\n}\n\n}  // namespace workspace\n#line 2 \"src/number_theory/primitive_root.hpp\"\
    \n\n/**\n * @file primitive_root.hpp\n * @brief Primitive Root\n * @date 2020-12-28\n\
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
    \ ntt_impl::ntt;\n\n}  // namespace workspace\n#line 15 \"src/algebra/polynomial.hpp\"\
    \n\nnamespace workspace {\n\n/**\n * @brief Polynomial.\n *\n * @tparam _Tp Ring\
    \ structure\n * @tparam _Conv_threshold Threshold for convolution method\n */\n\
    template <class _Tp, std::size_t _Conv_threshold = 64>\nclass polynomial : public\
    \ std::vector<_Tp> {\n  using vec = std::vector<_Tp>;\n  using poly = polynomial;\n\
    \n  template <class _Os> friend _Os& operator<<(_Os& __os, const poly& __x) {\n\
    \    bool __head = true;\n    for (const auto& __a : __x) {\n      if (!__head)\
    \ __os << ' ';\n      __head = false;\n      __os << __a;\n    }\n    return __os;\n\
    \  }\n\n public:\n  using vec::vec;\n  using size_type = typename vec::size_type;\n\
    \n protected:\n  void _erase_leading_zeros() noexcept {\n    auto __i = vec::_M_impl._M_finish;\n\
    \    while (__i != vec::_M_impl._M_start && *(__i - 1) == _Tp(0)) --__i;\n   \
    \ vec::_M_erase_at_end(__i);\n  }\n\n  template <class _Iter> void _dft(_Iter\
    \ __first, _Iter __last) const noexcept {\n    if _CXX17_CONSTEXPR (has_mod<_Tp>::value)\n\
    \      ntt(__first, __last);\n    else {\n      // fft(__first, __last);\n   \
    \   assert(0);  // Not implemented!\n    }\n  }\n\n  template <class _Iter>\n\
    \  void _idft(_Iter __first, _Iter __last) const noexcept {\n    if _CXX17_CONSTEXPR\
    \ (has_mod<_Tp>::value)\n      intt(__first, __last);\n    else {\n      // ifft(__first,\
    \ __last);\n      assert(0);  // Not implemented!\n    }\n  }\n\n  void _conv_naive(const\
    \ poly& __x) noexcept {\n    if (vec::_M_impl._M_start == vec::_M_impl._M_finish)\
    \ return;\n\n    if (__x._M_impl._M_start == __x._M_impl._M_finish) {\n      vec::_M_erase_at_end(vec::_M_impl._M_start);\n\
    \      return;\n    }\n\n    vec::_M_default_append(__x._M_impl._M_finish - __x._M_impl._M_start\
    \ - 1);\n\n    for (auto __i = vec::_M_impl._M_finish; __i-- != vec::_M_impl._M_start;)\
    \ {\n      auto __j = __i, __k = __x._M_impl._M_start;\n      *__i *= *__k++;\n\
    \n      while (__j != vec::_M_impl._M_start && __k != __x._M_impl._M_finish)\n\
    \        *__i += *--__j * *__k++;\n    }\n  }\n\n  void _conv_dft(poly&& __x)\
    \ noexcept {\n    if _CXX17_CONSTEXPR (has_mod<_Tp>::value)\n      _conv_ntt(std::move(__x));\n\
    \    else {\n      // _conv_fft(std::move(__x));\n      assert(0);  // Not implemented!\n\
    \    }\n  }\n\n  void _conv_fft(poly&& __x) noexcept;\n\n  void _conv_ntt(poly&&\
    \ __x) noexcept {\n    size_type __n = vec::_M_impl._M_finish - vec::_M_impl._M_start,\n\
    \              __m = __x._M_impl._M_finish - __x._M_impl._M_start,\n         \
    \     __len = 1 << (32 - __builtin_clz(__n + __m - 1));\n\n    vec::_M_default_append(__len\
    \ - __n);\n    __x._M_default_append(__len - __m);\n\n    ntt(vec::_M_impl._M_start,\
    \ vec::_M_impl._M_finish);\n    ntt(__x._M_impl._M_start, __x._M_impl._M_finish);\n\
    \n    for (auto __i = vec::_M_impl._M_start, __j = __x._M_impl._M_start;\n   \
    \      __i != vec::_M_impl._M_finish; ++__i, ++__j)\n      *__i *= std::move(*__j);\n\
    \n    intt(vec::_M_impl._M_start, vec::_M_impl._M_finish);\n\n    vec::_M_erase_at_end(vec::_M_impl._M_start\
    \ + __n + __m - 1);\n  }\n\n  /**\n   * @brief\n   *\n   * @param __x\n   * @return\
    \ Degree of __x.\n   */\n  size_type _divmod_naive(const poly& __x) {\n    auto\
    \ __xfin = __x._M_impl._M_finish;\n    auto __xlen = __x.size();\n    while (__xfin\
    \ != __x._M_impl._M_start && *(__xfin - 1) == _Tp(0))\n      --__xfin, --__xlen;\n\
    \n    assert(__xlen != 0);\n    _erase_leading_zeros();\n\n    auto __p = vec::_M_impl._M_finish;\n\
    \n    while (size_type(__p - vec::_M_impl._M_start) >= __xlen) {\n      --__p;\n\
    \n      auto __src = __xfin;\n      auto __dst = __p;\n\n      *__dst /= *--__src;\n\
    \      while (__src != __x._M_impl._M_start) *--__dst -= *--__src * *__p;\n  \
    \  }\n\n    return std::min<size_type>(__xlen - 1, __p - vec::_M_impl._M_start);\n\
    \  }\n\n  void _div_naive(const poly& __x) { operator>>=(_divmod_naive(__x));\
    \ }\n\n  void _div_doubling(poly&& __x) noexcept {\n    _erase_leading_zeros();\n\
    \    __x._erase_leading_zeros();\n\n    auto __n = vec::_M_impl._M_finish - vec::_M_impl._M_start;\n\
    \    auto __m = __x._M_impl._M_finish - __x._M_impl._M_start;\n\n    if (__n <\
    \ __m)\n      vec::clear();\n    else {\n      assert(__m != 0);\n\n      std::reverse(__x._M_impl._M_start,\
    \ __x._M_impl._M_finish);\n      __x = __x.inv(__n - __m + 1);\n\n      std::reverse(vec::_M_impl._M_start,\
    \ vec::_M_impl._M_finish);\n      vec::_M_erase_at_end(vec::_M_impl._M_finish\
    \ - (__m - 1));\n\n      operator*=(__x).resize(__n - __m + 1);\n      std::reverse(vec::_M_impl._M_start,\
    \ vec::_M_impl._M_finish);\n    }\n  }\n\n public:\n  /**\n   * @return Degree\
    \ of %polynomial. Return -1 if it equals zero.\n   */\n  size_type deg() const\
    \ noexcept { return vec::size() - 1; }\n\n  /**\n   * @param __i Not exceeding\
    \ the degree.\n   * @return Coefficient of x^i.\n   */\n  typename vec::reference\
    \ operator[](size_type __i) noexcept {\n    assert(__i < vec::size());\n    return\
    \ *(vec::_M_impl._M_start + __i);\n  }\n\n  /**\n   * @param __i Not exceeding\
    \ the degree.\n   * @return Coefficient of x^i.\n   */\n  typename vec::const_reference\
    \ operator[](size_type __i) const noexcept {\n    assert(__i < vec::size());\n\
    \    return *(vec::_M_impl._M_start + __i);\n  }\n\n  /**\n   * @brief Evaluate\
    \ at given point.\n   */\n  _Tp eval(const _Tp& __a) const noexcept {\n    _Tp\
    \ __v(0), __p(1);\n\n    for (auto __i = vec::_M_impl._M_start; __i != vec::_M_impl._M_finish;\n\
    \         ++__i, __p *= __a)\n      __v += *__i * __p;\n\n    return __v;\n  }\n\
    \n  /**\n   * @brief In-place multipoint evaluation.\n   */\n  template <class\
    \ _Iter, typename = std::_RequireInputIter<_Iter>>\n  _Iter eval(_Iter __first,\
    \ _Iter __last) const noexcept {\n    return eval(__first, __last, __first);\n\
    \  }\n\n  /**\n   * @brief Multipoint evaluation.\n   */\n  template <class _InputIter,\
    \ class _OutputIter,\n            typename = std::_RequireInputIter<_InputIter>>\n\
    \  _OutputIter eval(_InputIter __first, _InputIter __last,\n                 \
    \  _OutputIter __result) const noexcept {\n    size_type __n = std::distance(__first,\
    \ __last);\n    if (!__n) return __result;\n\n    auto __tree = new poly[__n <<\
    \ 1];\n\n    for (auto __p = __tree + __n; __first != __last; ++__p, ++__first)\n\
    \      *__p = {-*__first, 1};\n\n    for (size_type __i = __n; --__i;)\n     \
    \ __tree[__i] = __tree[__i << 1] * __tree[__i << 1 | 1];\n\n    __tree[1] = operator%(std::move(__tree[1]));\n\
    \n    for (size_type __i = 2; __i != __n << 1; __i += 2)\n      __tree[__i] =\
    \ __tree[__i >> 1] % std::move(__tree[__i]),\n      __tree[__i | 1] =\n      \
    \    std::move(__tree[__i >> 1] %= std::move(__tree[__i | 1]));\n\n    for (size_type\
    \ __i = 0; __i != __n; ++__i)\n      *__result++ = std::move(*__tree[__n + __i]._M_impl._M_start);\n\
    \n    delete[] __tree;\n\n    return __result;\n  }\n\n  /**\n   * @brief Conversion\
    \ to bool.\n   *\n   * @return Whether the %polynomial is not zero.\n   */\n \
    \ operator bool() const noexcept {\n    auto __first = vec::_M_impl._M_start,\
    \ __last = vec::_M_impl._M_finish;\n\n    while (__first != __last)\n      if\
    \ (*__first++ != _Tp(0)) return true;\n\n    return false;\n  }\n\n  bool operator==(const\
    \ poly& __x) const noexcept {\n    auto __first1 = vec::_M_impl._M_start, __last1\
    \ = vec::_M_impl._M_finish;\n\n    auto __first2 = __x._M_impl._M_start, __last2\
    \ = __x._M_impl._M_finish;\n\n    if (__last1 - __first1 < __last2 - __first2)\
    \ {\n      while (__first1 != __last1)\n        if (*__first1++ != *__first2++)\
    \ return false;\n\n      while (__first2 != __last2)\n        if (*__first2++\
    \ != _Tp(0)) return false;\n    }\n\n    else {\n      while (__first2 != __last2)\n\
    \        if (*__first1++ != *__first2++) return false;\n\n      while (__first1\
    \ != __last1)\n        if (*__first1++ != _Tp(0)) return false;\n    }\n\n   \
    \ return true;\n  }\n\n  bool operator!=(const poly& __x) const noexcept { return\
    \ !operator==(__x); }\n\n  /**\n   * @brief Multiply by x^i.\n   */\n  poly& operator<<=(size_type\
    \ __i) noexcept {\n    vec::insert(vec::begin(), __i, _Tp(0));\n    return *this;\n\
    \  }\n\n  /**\n   * @brief Divide by x^i.\n   */\n  poly& operator>>=(size_type\
    \ __i) noexcept {\n    vec::_M_erase_at_end(\n        std::move(vec::_M_impl._M_start\
    \ + std::min(__i, vec::size()),\n                  vec::_M_impl._M_finish, vec::_M_impl._M_start));\n\
    \n    return *this;\n  }\n\n  /**\n   * @brief Multiply by x^i.\n   */\n  poly\
    \ operator<<(size_type __i) const noexcept {\n    return poly(*this).operator<<=(__i);\n\
    \  }\n\n  /**\n   * @brief Divide by x^i.\n   */\n  poly operator>>(size_type\
    \ __i) const noexcept {\n    return poly(*this).operator>>=(__i);\n  }\n\n  poly\
    \ operator+() const noexcept { return *this; }\n\n  poly operator-() const noexcept\
    \ {\n    poly __x = *this;\n    for (auto __i = __x._M_impl._M_start; __i != __x._M_impl._M_finish;\
    \ ++__i)\n      *__i = -*__i;\n    return __x;\n  }\n\n  poly& operator+=(const\
    \ poly& __x) noexcept {\n    if (vec::size() < __x.size())\n      vec::_M_default_append(__x.size()\
    \ - vec::size());\n\n    for (auto __i = vec::_M_impl._M_start, __j = __x._M_impl._M_start;\n\
    \         __j != __x._M_impl._M_finish; ++__i, ++__j)\n      *__i += *__j;\n\n\
    \    _erase_leading_zeros();\n    return *this;\n  }\n\n  poly& operator+=(const\
    \ _Tp& __c) noexcept {\n    if (__c != static_cast<_Tp>(0)) {\n      if (vec::_M_impl._M_start\
    \ == vec::_M_impl._M_finish)\n        vec::emplace_back(__c);\n      else\n  \
    \      *vec::_M_impl._M_start += __c, _erase_leading_zeros();\n    }\n\n    return\
    \ *this;\n  }\n\n  poly& operator-=(const poly& __x) noexcept {\n    if (vec::size()\
    \ < __x.size())\n      vec::_M_default_append(__x.size() - vec::size());\n\n \
    \   for (auto __i = vec::_M_impl._M_start, __j = __x._M_impl._M_start;\n     \
    \    __j != __x._M_impl._M_finish; ++__i, ++__j)\n      *__i -= *__j;\n\n    _erase_leading_zeros();\n\
    \    return *this;\n  }\n\n  poly& operator-=(const _Tp& __c) noexcept {\n   \
    \ if (__c != static_cast<_Tp>(0)) {\n      if (vec::_M_impl._M_start == vec::_M_impl._M_finish)\n\
    \        vec::emplace_back(-__c);\n      else\n        *vec::_M_impl._M_start\
    \ -= __c, _erase_leading_zeros();\n    }\n\n    return *this;\n  }\n\n  poly&\
    \ operator*=(const poly& __x) noexcept {\n    std::min(vec::size(), __x.size())\
    \ > _Conv_threshold\n        ? _conv_dft(poly(__x))\n        : _conv_naive(this\
    \ == std::addressof(__x) ? poly(__x) : __x);\n\n    return *this;\n  }\n\n  poly&\
    \ operator*=(poly&& __x) noexcept {\n    std::min(vec::size(), __x.size()) > _Conv_threshold\n\
    \        ? _conv_dft(std::move(__x))\n        : _conv_naive(__x);\n\n    return\
    \ *this;\n  }\n\n  poly& operator*=(const _Tp& __c) noexcept {\n    if (__c ==\
    \ static_cast<_Tp>(0))\n      vec::_M_erase_at_end(vec::_M_impl._M_start);\n \
    \   else\n      for (auto __i = vec::_M_impl._M_start; __i != vec::_M_impl._M_finish;\n\
    \           ++__i)\n        *__i *= __c;\n\n    return *this;\n  }\n\n  poly&\
    \ operator/=(const _Tp& __c) noexcept {\n    assert(__c != static_cast<_Tp>(0));\n\
    \n    for (auto __i = vec::_M_impl._M_start; __i != vec::_M_impl._M_finish; ++__i)\n\
    \      *__i /= __c;\n\n    return *this;\n  }\n\n  poly rev() const noexcept {\
    \ return rev(vec::size()); }\n\n  poly rev(size_type __n) const noexcept {\n \
    \   poly __r(__n);\n\n    auto __src = vec::_M_impl._M_start;\n    auto __dst\
    \ = __r._M_impl._M_finish;\n    for (size_type __i = std::min(__n, vec::size());\
    \ __i; --__i)\n      *--__dst = *__src++;\n\n    return __r;\n  }\n\n  poly inv()\
    \ const noexcept { return inv(vec::size()); }\n\n  /**\n   * @brief Multiplicative\
    \ inverse modulo x^n.\n   *\n   * @param __n Degree of modulus\n   * @return\n\
    \   */\n  poly inv(size_type __n) const noexcept {\n    if (!__n) return {};\n\
    \    assert(*vec::_M_impl._M_start != _Tp(0));\n\n    size_type __len = 1;\n \
    \   while (__len < __n) __len <<= 1;\n\n    poly __y(__len);\n    auto __xp =\
    \ new _Tp[__len], __yp = __y._M_impl._M_start,\n         __zp = new _Tp[__len];\n\
    \n    *__yp = _Tp(1) / *vec::_M_impl._M_start;\n\n    for (size_type __i = 1;\
    \ __i != __len; __i <<= 1) {\n      std::fill(std::copy_n(__yp, __i, __zp), __zp\
    \ + (__i << 1), _Tp(0));\n\n      _dft(__zp, __zp + (__i << 1));\n\n      std::fill(std::copy_n(vec::_M_impl._M_start,\n\
    \                            std::min(__i << 1, vec::size()), __xp),\n       \
    \         __xp + (__i << 1), _Tp(0));\n\n      _dft(__xp, __xp + (__i << 1));\n\
    \n      for (size_type __j = 0; __j != (__i << 1); ++__j) __xp[__j] *= -__zp[__j];\n\
    \n      _idft(__xp, __xp + (__i << 1));\n\n      std::fill(std::move(__xp + __i,\
    \ __xp + (__i << 1), __xp),\n                __xp + (__i << 1), _Tp(0));\n\n \
    \     _dft(__xp, __xp + (__i << 1));\n\n      for (size_type __j = 0; __j != (__i\
    \ << 1); ++__j)\n        __xp[__j] *= static_cast<_Tp&&>(__zp[__j]);\n\n     \
    \ _idft(__xp, __xp + (__i << 1));\n\n      std::move(__xp, __xp + __i, __yp +\
    \ __i);\n    }\n\n    delete[] __xp;\n    delete[] __zp;\n\n    __y._M_erase_at_end(__yp\
    \ + __n);\n    return __y;\n  }\n\n  poly& operator/=(const poly& __x) noexcept\
    \ {\n    if (__x.size() > _Conv_threshold)\n      _div_doubling(poly(__x));\n\
    \    else\n      _div_naive(__x);\n\n    return *this;\n  }\n\n  poly& operator/=(poly&&\
    \ __x) noexcept {\n    if (__x.size() > _Conv_threshold)\n      _div_doubling(std::move(__x));\n\
    \    else\n      _div_naive(__x);\n\n    return *this;\n  }\n\n  poly& operator%=(const\
    \ poly& __x) noexcept {\n    if (__x.size() > _Conv_threshold)\n      return operator-=(__x.operator*(operator/(__x)));\n\
    \n    vec::_M_erase_at_end(vec::_M_impl._M_start + _divmod_naive(__x));\n    return\
    \ *this;\n  }\n\n  template <class _T> poly operator+(_T&& __x) const noexcept\
    \ {\n    return poly(*this).operator+=(std::forward<_T>(__x));\n  }\n\n  template\
    \ <class _T> poly operator-(_T&& __x) const noexcept {\n    return poly(*this).operator-=(std::forward<_T>(__x));\n\
    \  }\n\n  template <class _T> poly operator*(_T&& __x) const noexcept {\n    return\
    \ poly(*this).operator*=(std::forward<_T>(__x));\n  }\n\n  template <class _T>\
    \ poly operator/(_T&& __x) const noexcept {\n    return poly(*this).operator/=(std::forward<_T>(__x));\n\
    \  }\n\n  template <class _T> poly operator%(_T&& __x) const noexcept {\n    return\
    \ poly(*this).operator%=(std::forward<_T>(__x));\n  }\n\n  std::pair<poly, poly>\
    \ divmod(const poly& __x) const {\n    if (__x.size() > _Conv_threshold) return\
    \ {operator/(__x), operator%(__x)};\n\n    poly __rem(*this);\n    auto __p =\
    \ __rem._M_impl._M_start + __rem._divmod_naive(__x);\n\n    poly __quot(__p, __rem._M_impl._M_finish);\n\
    \    __rem._M_erase_at_end(__p);\n\n    return {__quot, __rem};\n  }\n\n  /**\n\
    \   * @brief Differentiate.\n   *\n   * @return Derivative.\n   */\n  poly deriv()\
    \ const noexcept {\n    if (auto __s = vec::_M_impl._M_start, __f = vec::_M_impl._M_finish;\n\
    \        __s != __f) {\n      poly __der(++__s, __f);\n\n      __s = __der._M_impl._M_start,\
    \ __f = __der._M_impl._M_finish;\n      for (_Tp __i(1); __s != __f; ++__s, __i\
    \ += 1) *__s *= __i;\n\n      __der._erase_leading_zeros();\n      return __der;\n\
    \    }\n\n    return {};\n  }\n\n  /**\n   * @brief Differentiate at given point.\n\
    \   *\n   * @return Derivative coefficient.\n   */\n  _Tp deriv(const _Tp& __a)\
    \ const noexcept {\n    _Tp __der(0);\n\n    if (auto __s = vec::_M_impl._M_start,\
    \ __f = vec::_M_impl._M_finish;\n        __s != __f)\n      for (_Tp __i(1), __p(1);\
    \ ++__s != __f; __i += 1, __p *= __a)\n        __der += *__s * __i * __p;\n\n\
    \    return __der;\n  }\n\n  /**\n   * @brief Integrate.\n   *\n   * @return Integral\
    \ indefinite at the degrees divisible by the characteristic\n   * of `_Tp`. Coefficients\
    \ are set as 0 there.\n   */\n  poly integ() const noexcept {\n    if (auto __s\
    \ = vec::_M_impl._M_start, __f = vec::_M_impl._M_finish;\n        __s != __f)\
    \ {\n      poly __int(__f - __s + 1);\n\n      __f = std::copy(__s, __f, __int._M_impl._M_start\
    \ + 1);\n      __s = __int._M_impl._M_start + 1;\n      for (_Tp __i(1); __s !=\
    \ __f; ++__s, __i += 1)\n        __i == _Tp(0) ? assert(*__s == _Tp(0)) : void(*__s\
    \ /= __i);\n\n      return __int;\n    }\n\n    return {};\n  }\n\n  /**\n   *\
    \ @brief Integrate in given range.\n   *\n   * @return Definite integral over\
    \ [0, __a].\n   */\n  _Tp integ(const _Tp& __a) const noexcept {\n    _Tp __int(0);\n\
    \n    auto __s = vec::_M_impl._M_start, __f = vec::_M_impl._M_finish;\n    for\
    \ (_Tp __p(__a), __i(1); __s != __f; ++__s, __p *= __a, __i += 1)\n      __int\
    \ += *__s / __i * __p;\n\n    return __int;\n  }\n\n  /**\n   * @brief Integrate\
    \ in given range.\n   *\n   * @return Definite integral over [__a, __b].\n   */\n\
    \  _Tp integ(const _Tp& __a, const _Tp& __b) const noexcept {\n    _Tp __int(0);\n\
    \n    auto __s = vec::_M_impl._M_start, __f = vec::_M_impl._M_finish;\n    for\
    \ (_Tp __pa(__a), __pb(__b), __i(1); __s != __f;\n         ++__s, __pa *= __a,\
    \ __pb *= __b, __i += 1)\n      __int += *__s / __i * (__pb - __pa);\n\n    return\
    \ __int;\n  }\n};\n\n/**\n * @brief Polynomial interpolation in O(n log(n)^2)\
    \ time.\n *\n * @param __first\n * @param __last\n * @return\n */\ntemplate <class\
    \ _InputIter, typename = std::_RequireInputIter<_InputIter>>\nauto interpolate(_InputIter\
    \ __first, _InputIter __last) {\n  size_t __n = std::distance(__first, __last);\n\
    \n  auto [__1, __2] =\n      typename std::iterator_traits<decltype(__first)>::value_type{};\n\
    \n  using poly = polynomial<decltype(__1)>;\n\n  if (!__n) return poly{};\n\n\
    \  struct node {\n    poly __all, __lack;\n  };\n\n  auto __tree = new node[__n\
    \ << 1];\n  auto __iter = __first;\n\n  for (size_t __i = 0; __i != __n; ++__i)\
    \ {\n    auto&& [__a, __b] = *__iter++;\n    __tree[__i + __n].__all = {-__a,\
    \ 1}, __tree[__i + __n].__lack = {1};\n  }\n\n  for (size_t __i = __n; --__i;)\n\
    \    __tree[__i].__all = __tree[__i << 1].__all * __tree[__i << 1 | 1].__all,\n\
    \    __tree[__i].__lack =\n        __tree[__i << 1].__all * std::move(__tree[__i\
    \ << 1 | 1].__lack) +\n        __tree[__i << 1 | 1].__all * std::move(__tree[__i\
    \ << 1].__lack);\n\n  for (size_t __i = 2; __i != __n << 1; __i += 2)\n    __tree[__i].__lack\
    \ = __tree[__i >> 1].__lack % __tree[__i].__all,\n    __tree[__i | 1].__lack =\n\
    \        std::move(__tree[__i >> 1].__lack %= __tree[__i | 1].__all);\n\n  for\
    \ (size_t __i = 0; __i != __n; ++__i) {\n    auto&& [__a, __b] = *__first++;\n\
    \    __tree[__i + __n].__lack[0] =\n        std::move(__b) / std::move(__tree[__i\
    \ + __n].__lack[0]);\n  }\n\n  for (size_t __i = __n; --__i;)\n    __tree[__i].__lack\
    \ = std::move(__tree[__i << 1].__all) *\n                             std::move(__tree[__i\
    \ << 1 | 1].__lack) +\n                         std::move(__tree[__i << 1 | 1].__all)\
    \ *\n                             std::move(__tree[__i << 1].__lack);\n\n  auto\
    \ __result = std::move(__tree[1].__lack);\n\n  delete[] __tree;\n\n  return __result;\n\
    }\n\n// /**\n//  * @brief \\\\prod_{i=0}^{n-1} (x+i) \\\\bmod x^d.\n//  */\n//\
    \ template <class _Tp> auto rising_factorial(_Tp __n, std::size_t __d) {}\n\n\
    // /**\n//  * @brief \\\\prod_{i=0}^{n-1} (x+i).\n//  */\n// template <class _Tp>\
    \ auto rising_factorial(_Tp __n) {\n//   return rising_factorial(__n, __n);\n\
    // }\n\n// /**\n//  * @brief \\\\prod_{i=0}^{n-1} (x-i) \\\\bmod x^d.\n//  */\n\
    // template <class _Tp> auto falling_factorial(_Tp __n, std::size_t __d) {\n//\
    \   auto __f = rising_factorial(__n, __d);\n//   for (std::size_t __i = (__n &\
    \ 1) ^ 1; __i < __d; __i += 2)\n//     __f[__i] = -__f[__i];\n//   return __f;\n\
    // }\n\n// /**\n//  * @brief \\\\prod_{i=0}^{n-1} (x-i).\n//  */\n// template\
    \ <class _Tp> auto falling_factorial(_Tp __n) {\n//   return falling_factorial(__n,\
    \ __n);\n// }\n\n/**\n * @brief \\\\sum_{j=0}^{d-1} x^j \\\\sum_{i=0}^{n-1} i^j.\n\
    \ */\ntemplate <class _Tp> auto power_sums(_Tp __n, std::size_t __d) {\n  using\
    \ return_type = polynomial<_Tp>;\n  if (!__d) return return_type{};\n  return_type\
    \ __f(__d), __e(__d);\n  __f[0] = __n;\n  for (std::size_t __i = 1; __i != __d;\
    \ ++__i) __f[__i] = __f[__i - 1] * __n;\n  _Tp __c{1};\n  for (std::size_t __i\
    \ = 0; __i != __d; ++__i)\n    __c /= __i + 1, __f[__i] *= __c, __e[__i] = __c;\n\
    \  (__f *= __e.inv(__d)).resize(__d);\n  __c = 1;\n  for (std::size_t __i = 0;\
    \ __i != __d; __c *= ++__i) __f[__i] *= __c;\n  return __f;\n}\n\n}  // namespace\
    \ workspace\n#line 11 \"src/algebra/berlekamp_massey.hpp\"\n\nnamespace workspace\
    \ {\n\ntemplate <class _Iterator>\nauto Berlekamp_Massey(_Iterator __first, _Iterator\
    \ __last) noexcept {\n  using value_type = typename std::iterator_traits<_Iterator>::value_type;\n\
    \n  std::vector<value_type> __a(__first, __last);\n  polynomial<value_type> __c{1},\
    \ __b{1};\n\n  typename decltype(__c)::size_type __z = 1;\n\n  for (auto __s =\
    \ __a.begin(); __s != __a.end(); ++__s) {\n    ++__z;\n\n    auto __d = std::inner_product(__c.begin(),\
    \ __c.end(), __s + 1 - __c.size(),\n                                  value_type(0));\n\
    \    if (__d == value_type(0)) continue;\n\n    if (__c.size() < __z) {\n    \
    \  auto __tmp = __c;\n      __c <<= __z - __c.size();\n      __c -= __b *= __d;\n\
    \      __b = std::move(__tmp);\n      __b /= __d;\n      __z = __b.size();\n \
    \   } else {\n      for (auto __i = __c.end() - __z, __j = __b.begin(); __j !=\
    \ __b.end();\n           ++__i, ++__j)\n        *__i -= *__j * __d;\n    }\n \
    \ }\n\n  return __c;\n}\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file berlekamp_massey.hpp\n * @brief Berlekamp-Massey\
    \ Algorithm\n */\n\n#include <numeric>\n\n#include \"polynomial.hpp\"\n\nnamespace\
    \ workspace {\n\ntemplate <class _Iterator>\nauto Berlekamp_Massey(_Iterator __first,\
    \ _Iterator __last) noexcept {\n  using value_type = typename std::iterator_traits<_Iterator>::value_type;\n\
    \n  std::vector<value_type> __a(__first, __last);\n  polynomial<value_type> __c{1},\
    \ __b{1};\n\n  typename decltype(__c)::size_type __z = 1;\n\n  for (auto __s =\
    \ __a.begin(); __s != __a.end(); ++__s) {\n    ++__z;\n\n    auto __d = std::inner_product(__c.begin(),\
    \ __c.end(), __s + 1 - __c.size(),\n                                  value_type(0));\n\
    \    if (__d == value_type(0)) continue;\n\n    if (__c.size() < __z) {\n    \
    \  auto __tmp = __c;\n      __c <<= __z - __c.size();\n      __c -= __b *= __d;\n\
    \      __b = std::move(__tmp);\n      __b /= __d;\n      __z = __b.size();\n \
    \   } else {\n      for (auto __i = __c.end() - __z, __j = __b.begin(); __j !=\
    \ __b.end();\n           ++__i, ++__j)\n        *__i -= *__j * __d;\n    }\n \
    \ }\n\n  return __c;\n}\n\n}  // namespace workspace\n"
  dependsOn:
  - src/algebra/polynomial.hpp
  - src/algebra/ntt.hpp
  - src/number_theory/ext_gcd.hpp
  - src/utils/sfinae.hpp
  - src/number_theory/primitive_root.hpp
  isVerificationFile: false
  path: src/algebra/berlekamp_massey.hpp
  requiredBy: []
  timestamp: '2021-07-07 20:04:02+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/find_linear_recurrence.test.cpp
documentation_of: src/algebra/berlekamp_massey.hpp
layout: document
redirect_from:
- /library/src/algebra/berlekamp_massey.hpp
- /library/src/algebra/berlekamp_massey.hpp.html
title: Berlekamp-Massey Algorithm
---
