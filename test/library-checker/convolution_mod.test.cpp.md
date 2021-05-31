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
    path: src/modular/modint.hpp
    title: Modular Arithmetic
  - icon: ':heavy_check_mark:'
    path: src/number_theory/ext_gcd.hpp
    title: Extended Euclidean Algorithm
  - icon: ':heavy_check_mark:'
    path: src/number_theory/pow_mod.hpp
    title: Modular Exponentiation
  - icon: ':heavy_check_mark:'
    path: src/number_theory/primitive_root.hpp
    title: Primitive Root
  - icon: ':heavy_check_mark:'
    path: src/number_theory/sqrt_mod.hpp
    title: Tonelli-Shanks Algorithm
  - icon: ':heavy_check_mark:'
    path: src/utils/io/istream.hpp
    title: Input Stream
  - icon: ':heavy_check_mark:'
    path: src/utils/io/ostream.hpp
    title: Output Stream
  - icon: ':heavy_check_mark:'
    path: src/utils/sfinae.hpp
    title: SFINAE
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/convolution_mod
    links:
    - https://judge.yosupo.jp/problem/convolution_mod
  bundledCode: "#line 1 \"test/library-checker/convolution_mod.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/convolution_mod\"\n\n#line 2 \"src/algebra/polynomial.hpp\"\
    \n\n/**\n * @file polynomial.hpp\n * @brief Polynomial\n */\n\n#include <algorithm>\n\
    #include <cassert>\n#include <vector>\n\n#line 2 \"lib/cxx17\"\n\n#ifndef _CXX17_CONSTEXPR\n\
    #if __cplusplus >= 201703L\n#define _CXX17_CONSTEXPR constexpr\n#else\n#define\
    \ _CXX17_CONSTEXPR\n#endif\n#endif\n#line 2 \"src/algebra/ntt.hpp\"\n\n/**\n *\
    \ @file ntt.hpp\n * @brief Number Theoretic Transform\n * @date 2021-02-20\n *\n\
    \ *\n */\n\n#line 2 \"src/number_theory/ext_gcd.hpp\"\n\n/**\n * @file ext_gcd.hpp\n\
    \ * @brief Extended Euclidean Algorithm\n */\n\n#include <tuple>\n\n#line 2 \"\
    src/utils/sfinae.hpp\"\n\n/**\n * @file sfinae.hpp\n * @brief SFINAE\n */\n\n\
    #include <cstdint>\n#include <iterator>\n#include <type_traits>\n\n#ifndef __INT128_DEFINED__\n\
    \n#ifdef __SIZEOF_INT128__\n#define __INT128_DEFINED__ 1\n#else\n#define __INT128_DEFINED__\
    \ 0\n#endif\n\n#endif\n\nnamespace std {\n\n#if __INT128_DEFINED__\n\ntemplate\
    \ <> struct make_signed<__uint128_t> { using type = __int128_t; };\ntemplate <>\
    \ struct make_signed<__int128_t> { using type = __int128_t; };\n\ntemplate <>\
    \ struct make_unsigned<__uint128_t> { using type = __uint128_t; };\ntemplate <>\
    \ struct make_unsigned<__int128_t> { using type = __uint128_t; };\n\ntemplate\
    \ <> struct is_signed<__uint128_t> : std::false_type {};\ntemplate <> struct is_signed<__int128_t>\
    \ : std::true_type {};\n\ntemplate <> struct is_unsigned<__uint128_t> : std::true_type\
    \ {};\ntemplate <> struct is_unsigned<__int128_t> : std::false_type {};\n\n#endif\n\
    \n}  // namespace std\n\nnamespace workspace {\n\ntemplate <class Tp, class...\
    \ Args> struct variadic_front { using type = Tp; };\n\ntemplate <class... Args>\
    \ struct variadic_back;\n\ntemplate <class Tp> struct variadic_back<Tp> { using\
    \ type = Tp; };\n\ntemplate <class Tp, class... Args> struct variadic_back<Tp,\
    \ Args...> {\n  using type = typename variadic_back<Args...>::type;\n};\n\ntemplate\
    \ <class type, template <class> class trait>\nusing enable_if_trait_type = typename\
    \ std::enable_if<trait<type>::value>::type;\n\n/**\n * @brief Return type of subscripting\
    \ ( @c [] ) access.\n */\ntemplate <class _Tp>\nusing subscripted_type =\n   \
    \ typename std::decay<decltype(std::declval<_Tp&>()[0])>::type;\n\ntemplate <class\
    \ Container>\nusing element_type = typename std::decay<decltype(\n    *std::begin(std::declval<Container&>()))>::type;\n\
    \ntemplate <class _Tp, class = std::nullptr_t>\nstruct has_begin : std::false_type\
    \ {};\n\ntemplate <class _Tp>\nstruct has_begin<_Tp, decltype(std::begin(std::declval<_Tp>()),\
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
    \ workspace\n#line 2 \"src/modular/modint.hpp\"\n\n/**\n * @file modint.hpp\n\
    \ *\n * @brief Modular Arithmetic\n */\n\n#line 10 \"src/modular/modint.hpp\"\n\
    #include <iostream>\n#line 12 \"src/modular/modint.hpp\"\n\n#line 2 \"src/number_theory/sqrt_mod.hpp\"\
    \n\n/**\n * @file sqrt_mod.hpp\n * @brief Tonelli-Shanks Algorithm\n */\n\n#line\
    \ 2 \"src/number_theory/pow_mod.hpp\"\n\n/**\n * @file mod_pow.hpp\n * @brief\
    \ Modular Exponentiation\n */\n\n#line 9 \"src/number_theory/pow_mod.hpp\"\n\n\
    #line 11 \"src/number_theory/pow_mod.hpp\"\n\nnamespace workspace {\n\n/**\n *\
    \ @brief Compile time modular exponentiation.\n *\n * @param __x\n * @param __n\
    \ Exponent\n * @param __mod Modulus\n * @return\n */\ntemplate <class _Tp>\nconstexpr\
    \ std::enable_if_t<(is_integral_ext<_Tp>::value), _Tp> pow_mod(\n    _Tp __x,\
    \ _Tp __n, _Tp __mod) noexcept {\n  assert(__mod > 0);\n\n  using mul_type = typename\
    \ multiplicable_uint<_Tp>::type;\n\n  if ((__x %= __mod) < 0) __x += __mod;\n\n\
    \  mul_type __y{1};\n\n  while (__n) {\n    if (__n & 1) (__y *= __x) %= __mod;\n\
    \    __x = (mul_type)__x * __x % __mod;\n    __n >>= 1;\n  }\n\n  return __y;\n\
    };\n\n}  // namespace workspace\n#line 10 \"src/number_theory/sqrt_mod.hpp\"\n\
    \nnamespace workspace {\n\n/**\n * @brief Compile time modular square root.\n\
    \ *\n * @param __x\n * @param __mod Modulus\n * @return One if it exists. Otherwise\
    \ -1.\n */\ntemplate <class _Tp>\nconstexpr std::enable_if_t<(is_integral_ext<_Tp>::value),\
    \ _Tp> sqrt_mod(\n    _Tp __x, _Tp __mod) noexcept {\n  assert(__mod > 0);\n\n\
    \  using mul_type = typename multiplicable_uint<_Tp>::type;\n\n  if ((__x %= __mod)\
    \ < 0) __x += __mod;\n\n  if (!__x) return 0;\n\n  if (__mod == 2) return __x;\n\
    \n  if (pow_mod(__x, __mod >> 1, __mod) != 1) return -1;\n\n  _Tp __z = __builtin_ctz(__mod\
    \ - 1), __q = __mod >> __z;\n\n  mul_type __a = pow_mod(__x, (__q + 1) >> 1, __mod),\
    \ __b = 2;\n  while (pow_mod<_Tp>(__b, __mod >> 1, __mod) == 1) ++__b;\n  __b\
    \ = pow_mod<_Tp>(__b, __q, __mod);\n\n  _Tp __shift = 0;\n\n  for (auto __r =\
    \ __a * __a % __mod * pow_mod(__x, __mod - 2, __mod) % __mod;\n       __r != 1;\
    \ (__r *= (__b *= __b) %= __mod) %= __mod) {\n    auto __bsf = __z;\n\n    for\
    \ (auto __e = __r; __e != 1; --__bsf) (__e *= __e) %= __mod;\n\n    while (++__shift\
    \ != __bsf) (__b *= __b) %= __mod;\n\n    (__a *= __b) %= __mod;\n  }\n\n  return\
    \ __a;\n};\n\n}  // namespace workspace\n#line 15 \"src/modular/modint.hpp\"\n\
    \nnamespace workspace {\n\nnamespace _modint_impl {\n\ntemplate <auto _Mod, unsigned\
    \ _Storage> struct modint {\n  static_assert(is_integral_ext<decltype(_Mod)>::value,\n\
    \                \"_Mod must be integral type.\");\n\n  using mod_type = std::make_signed_t<typename\
    \ std::conditional<\n      0 < _Mod, std::add_const_t<decltype(_Mod)>, decltype(_Mod)>::type>;\n\
    \n  using value_type = std::decay_t<mod_type>;\n\n  using mul_type = typename\
    \ multiplicable_uint<value_type>::type;\n\n  // Modulus\n  static mod_type mod;\n\
    \n  static unsigned storage;\n\n private:\n  value_type value = 0;\n\n  struct\
    \ direct_ctor_t {};\n  constexpr static direct_ctor_t direct_ctor_tag{};\n\n \
    \ // Direct constructor\n  template <class _Tp>\n  constexpr modint(_Tp __n, direct_ctor_t)\
    \ noexcept : value(__n) {}\n\n public:\n  constexpr modint() noexcept = default;\n\
    \n  template <class _Tp, typename = std::enable_if_t<is_integral_ext<_Tp>::value>>\n\
    \  constexpr modint(_Tp __n) noexcept\n      : value((__n %= mod) < 0 ? __n +=\
    \ mod : __n) {}\n\n  constexpr modint(bool __n) noexcept : value(__n) {}\n\n \
    \ constexpr operator value_type() const noexcept { return value; }\n\n  // unary\
    \ operators {{\n  constexpr modint operator++(int) noexcept {\n    modint __t{*this};\n\
    \    operator++();\n    return __t;\n  }\n\n  constexpr modint operator--(int)\
    \ noexcept {\n    modint __t{*this};\n    operator--();\n    return __t;\n  }\n\
    \n  constexpr modint &operator++() noexcept {\n    if (++value == mod) value =\
    \ 0;\n    return *this;\n  }\n\n  constexpr modint &operator--() noexcept {\n\
    \    if (!value)\n      value = mod - 1;\n    else\n      --value;\n    return\
    \ *this;\n  }\n\n  constexpr modint operator+() const noexcept { return *this;\
    \ }\n\n  constexpr modint operator-() const noexcept {\n    return {value ? mod\
    \ - value : 0, direct_ctor_tag};\n  }\n\n  // }} unary operators\n\n  // operator+=\
    \ {{\n\n  constexpr modint &operator+=(const modint &__x) noexcept {\n    if ((value\
    \ += __x.value) >= mod) value -= mod;\n    return *this;\n  }\n\n  template <class\
    \ _Tp>\n  constexpr std::enable_if_t<is_integral_ext<_Tp>::value, modint> &operator+=(\n\
    \      _Tp const &__x) noexcept {\n    if (((value += __x) %= mod) < 0) value\
    \ += mod;\n    return *this;\n  }\n\n  // }} operator+=\n\n  // operator+ {{\n\
    \n  template <class _Tp>\n  constexpr std::enable_if_t<is_integral_ext<_Tp>::value,\
    \ modint> operator+(\n      _Tp const &__x) const noexcept {\n    return modint{*this}\
    \ += __x;\n  }\n\n  constexpr modint operator+(modint __x) const noexcept { return\
    \ __x += *this; }\n\n  template <class _Tp>\n  constexpr friend std::enable_if_t<is_integral_ext<_Tp>::value,\
    \ modint>\n  operator+(_Tp const &__x, modint __y) noexcept {\n    return __y\
    \ += __x;\n  }\n\n  // }} operator+\n\n  // operator-= {{\n\n  constexpr modint\
    \ &operator-=(const modint &__x) noexcept {\n    if ((value -= __x.value) < 0)\
    \ value += mod;\n    return *this;\n  }\n\n  template <class _Tp>\n  constexpr\
    \ std::enable_if_t<is_integral_ext<_Tp>::value, modint> &operator-=(\n      _Tp\
    \ __x) noexcept {\n    if (((value -= __x) %= mod) < 0) value += mod;\n    return\
    \ *this;\n  }\n\n  // }} operator-=\n\n  // operator- {{\n\n  template <class\
    \ _Tp>\n  constexpr std::enable_if_t<is_integral_ext<_Tp>::value, modint> operator-(\n\
    \      _Tp const &__x) const noexcept {\n    return modint{*this} -= __x;\n  }\n\
    \n  constexpr modint operator-(const modint &__x) const noexcept {\n    return\
    \ modint{*this} -= __x;\n  }\n\n  template <class _Tp>\n  constexpr friend std::enable_if_t<is_integral_ext<_Tp>::value,\
    \ modint>\n  operator-(_Tp __x, const modint &__y) noexcept {\n    if (((__x -=\
    \ __y.value) %= mod) < 0) __x += mod;\n    return {__x, direct_ctor_tag};\n  }\n\
    \n  // }} operator-\n\n  // operator*= {{\n\n  constexpr modint &operator*=(const\
    \ modint &__x) noexcept {\n    value =\n        static_cast<value_type>(value\
    \ * static_cast<mul_type>(__x.value) % mod);\n    return *this;\n  }\n\n  template\
    \ <class _Tp>\n  constexpr std::enable_if_t<is_integral_ext<_Tp>::value, modint>\
    \ &operator*=(\n      _Tp __x) noexcept {\n    value = static_cast<value_type>(\n\
    \        value * mul_type((__x %= mod) < 0 ? __x + mod : __x) % mod);\n    return\
    \ *this;\n  }\n\n  // }} operator*=\n\n  // operator* {{\n\n  constexpr modint\
    \ operator*(const modint &__x) const noexcept {\n    return {static_cast<mul_type>(value)\
    \ * __x.value % mod, direct_ctor_tag};\n  }\n\n  template <class _Tp>\n  constexpr\
    \ std::enable_if_t<is_integral_ext<_Tp>::value, modint> operator*(\n      _Tp\
    \ __x) const noexcept {\n    __x %= mod;\n    if (__x < 0) __x += mod;\n    return\
    \ {static_cast<mul_type>(value) * __x % mod, direct_ctor_tag};\n  }\n\n  template\
    \ <class _Tp>\n  constexpr friend std::enable_if_t<is_integral_ext<_Tp>::value,\
    \ modint>\n  operator*(_Tp __x, const modint &__y) noexcept {\n    __x %= mod;\n\
    \    if (__x < 0) __x += mod;\n    return {static_cast<mul_type>(__x) * __y.value\
    \ % mod, direct_ctor_tag};\n  }\n\n  // }} operator*\n\n protected:\n  static\
    \ value_type _mem(value_type __x) {\n    static std::vector<value_type> __m{0,\
    \ 1};\n    static value_type __i = (__m.reserve(storage), 1);\n    while (__i\
    \ < __x) {\n      ++__i;\n      __m.emplace_back(mod - mul_type(mod / __i) * __m[mod\
    \ % __i] % mod);\n    }\n    return __m[__x];\n  }\n\n  static value_type _div(mul_type\
    \ __r, value_type __x) noexcept {\n    assert(__x != value_type(0));\n    if (!__r)\
    \ return 0;\n\n    std::make_signed_t<value_type> __v{};\n    bool __neg = __x\
    \ < 0 ? __x = -__x, true : false;\n\n    if (static_cast<decltype(storage)>(__x)\
    \ < storage)\n      __v = _mem(__x);\n    else {\n      value_type __y{mod}, __u{1},\
    \ __t;\n\n      while (__x)\n        __t = __y / __x, __y ^= __x ^= (__y -= __t\
    \ * __x) ^= __x,\n        __v ^= __u ^= (__v -= __t * __u) ^= __u;\n\n      if\
    \ (__y < 0) __neg ^= 1;\n    }\n\n    if (__neg)\n      __v = 0 < __v ? mod -\
    \ __v : -__v;\n    else if (__v < 0)\n      __v += mod;\n\n    return __r == mul_type(1)\
    \ ? static_cast<value_type>(__v)\n                              : static_cast<value_type>(__r\
    \ * __v % mod);\n  }\n\n public:\n  // operator/= {{\n\n  constexpr modint &operator/=(const\
    \ modint &__x) noexcept {\n    if (value) value = _div(value, __x.value);\n  \
    \  return *this;\n  }\n\n  template <class _Tp>\n  constexpr std::enable_if_t<is_integral_ext<_Tp>::value,\
    \ modint> &operator/=(\n      _Tp __x) noexcept {\n    if (value) value = _div(value,\
    \ __x %= mod);\n    return *this;\n  }\n\n  // }} operator/=\n\n  // operator/\
    \ {{\n\n  constexpr modint operator/(const modint &__x) const noexcept {\n   \
    \ if (!value) return {};\n    return {_div(value, __x.value), direct_ctor_tag};\n\
    \  }\n\n  template <class _Tp>\n  constexpr std::enable_if_t<is_integral_ext<_Tp>::value,\
    \ modint> operator/(\n      _Tp __x) const noexcept {\n    if (!value) return\
    \ {};\n    return {_div(value, __x %= mod), direct_ctor_tag};\n  }\n\n  template\
    \ <class _Tp>\n  constexpr friend std::enable_if_t<is_integral_ext<_Tp>::value,\
    \ modint>\n  operator/(_Tp __x, const modint &__y) noexcept {\n    if (!__x) return\
    \ {};\n    if ((__x %= mod) < 0) __x += mod;\n    return {_div(__x, __y.value),\
    \ direct_ctor_tag};\n  }\n\n  // }} operator/\n\n  constexpr modint inv() const\
    \ noexcept { return _div(1, value); }\n\n  template <class _Tp>\n  constexpr std::enable_if_t<is_integral_ext<_Tp>::value,\
    \ modint> pow(\n      _Tp __e) const noexcept {\n    modint __r{1, direct_ctor_tag};\n\
    \n    for (modint __b{__e < 0 ? __e = -__e, _div(1, value) : value,\n        \
    \                      direct_ctor_tag};\n         __e; __e >>= 1, __b *= __b)\n\
    \      if (__e & 1) __r *= __b;\n\n    return __r;\n  }\n\n  template <class _Tp>\n\
    \  constexpr friend std::enable_if_t<is_integral_ext<_Tp>::value, modint> pow(\n\
    \      modint __b, _Tp __e) noexcept {\n    if (__e < 0) {\n      __e = -__e;\n\
    \      __b.value = _div(1, __b.value);\n    }\n\n    modint __r{1, direct_ctor_tag};\n\
    \n    for (; __e; __e >>= 1, __b *= __b)\n      if (__e & 1) __r *= __b;\n\n \
    \   return __r;\n  }\n\n  constexpr modint sqrt() const noexcept {\n    return\
    \ {sqrt_mod(value, mod), direct_ctor_tag};\n  }\n\n  friend constexpr modint sqrt(const\
    \ modint &__x) noexcept {\n    return {sqrt_mod(__x.value, mod), direct_ctor_tag};\n\
    \  }\n\n  template <class _Os>\n  friend _Os &operator<<(_Os &__os, const modint\
    \ &__x) noexcept {\n    return __os << __x.value;\n  }\n\n  friend std::istream\
    \ &operator>>(std::istream &__is, modint &__x) noexcept {\n    std::string __s;\n\
    \    __is >> __s;\n    bool __neg = false;\n    if (__s.front() == '-') {\n  \
    \    __neg = true;\n      __s.erase(__s.begin());\n    }\n    __x = 0;\n    for\
    \ (char __c : __s) __x = __x * 10 + (__c - '0');\n    if (__neg) __x = -__x;\n\
    \    return __is;\n  }\n};\n\ntemplate <auto _Mod, unsigned _Storage>\ntypename\
    \ modint<_Mod, _Storage>::mod_type modint<_Mod, _Storage>::mod =\n    _Mod > 0\
    \ ? _Mod : 0;\n\ntemplate <auto _Mod, unsigned _Storage>\nunsigned modint<_Mod,\
    \ _Storage>::storage = _Storage;\n\n}  // namespace _modint_impl\n\ntemplate <auto\
    \ _Mod, unsigned _Storage = 0,\n          typename = std::enable_if_t<(_Mod >\
    \ 0)>>\nusing modint = _modint_impl::modint<_Mod, _Storage>;\n\ntemplate <unsigned\
    \ _Id = 0>\nusing modint_runtime = _modint_impl::modint<-(signed)_Id, 0>;\n\n\
    }  // namespace workspace\n#line 2 \"src/utils/io/istream.hpp\"\n\n/**\n * @file\
    \ istream.hpp\n * @brief Input Stream\n */\n\n#include <cxxabi.h>\n\n#line 13\
    \ \"src/utils/io/istream.hpp\"\n\n#line 16 \"src/utils/io/istream.hpp\"\n\nnamespace\
    \ workspace {\n\nnamespace _istream_impl {\n\ntemplate <class _Tp, typename =\
    \ void> struct istream_helper {\n  istream_helper(std::istream &__is, _Tp &__x)\
    \ {\n    if _CXX17_CONSTEXPR (has_begin<_Tp>::value)\n      for (auto &&__e :\
    \ __x)\n        istream_helper<std::decay_t<decltype(__e)>>(__is, __e);\n    else\n\
    \      static_assert(has_begin<_Tp>::value, \"istream unsupported type.\");\n\
    \  }\n};\n\ntemplate <class _Tp>\nstruct istream_helper<_Tp,\n               \
    \       std::__void_t<decltype(std::declval<std::istream &>() >>\n           \
    \                                  std::declval<_Tp &>())>> {\n  istream_helper(std::istream\
    \ &__is, _Tp &__x) { __is >> __x; }\n};\n\n#ifdef __SIZEOF_INT128__\n\ntemplate\
    \ <> struct istream_helper<__uint128_t, void> {\n  istream_helper(std::istream\
    \ &__is, __uint128_t &__x) {\n    std::string __s;\n    __is >> __s;\n    bool\
    \ __neg = false;\n    if (__s.front() == '-') __neg = true, __s.erase(__s.begin());\n\
    \    __x = 0;\n    for (char __d : __s) {\n      __x *= 10;\n      __d -= '0';\n\
    \      if (__neg)\n        __x -= __d;\n      else\n        __x += __d;\n    }\n\
    \  }\n};\n\ntemplate <> struct istream_helper<__int128_t, void> {\n  istream_helper(std::istream\
    \ &__is, __int128_t &__x) {\n    std::string __s;\n    __is >> __s;\n    bool\
    \ __neg = false;\n    if (__s.front() == '-') __neg = true, __s.erase(__s.begin());\n\
    \    __x = 0;\n    for (char __d : __s) {\n      __x *= 10;\n      __d -= '0';\n\
    \      if (__neg)\n        __x -= __d;\n      else\n        __x += __d;\n    }\n\
    \  }\n};\n\n#endif  // INT128\n\ntemplate <class _T1, class _T2> struct istream_helper<std::pair<_T1,\
    \ _T2>> {\n  istream_helper(std::istream &__is, std::pair<_T1, _T2> &__x) {\n\
    \    istream_helper<_T1>(__is, __x.first), istream_helper<_T2>(__is, __x.second);\n\
    \  }\n};\n\ntemplate <class... _Tp> struct istream_helper<std::tuple<_Tp...>>\
    \ {\n  istream_helper(std::istream &__is, std::tuple<_Tp...> &__x) {\n    iterate(__is,\
    \ __x);\n  }\n\n private:\n  template <class _Tuple, size_t N = 0>\n  void iterate(std::istream\
    \ &__is, _Tuple &__x) {\n    if _CXX17_CONSTEXPR (N != std::tuple_size<_Tuple>::value)\
    \ {\n      istream_helper<typename std::tuple_element<N, _Tuple>::type>(\n   \
    \       __is, std::get<N>(__x)),\n          iterate<_Tuple, N + 1>(__is, __x);\n\
    \    }\n  }\n};\n\n}  // namespace _istream_impl\n\n/**\n * @brief A wrapper class\
    \ for std::istream.\n */\nclass istream : public std::istream {\n public:\n  /**\n\
    \   * @brief Wrapped operator.\n   */\n  template <typename _Tp> istream &operator>>(_Tp\
    \ &__x) {\n    _istream_impl::istream_helper<_Tp>(*this, __x);\n    if (std::istream::fail())\
    \ {\n      static auto once = atexit([] {\n        std::cerr << \"\\n\\033[43m\\\
    033[30mwarning: failed to read \\'\"\n                  << abi::__cxa_demangle(typeid(_Tp).name(),\
    \ 0, 0, 0)\n                  << \"\\'.\\033[0m\\n\\n\";\n      });\n      assert(!once);\n\
    \    }\n    return *this;\n  }\n};\n\ndecltype(auto) cin = static_cast<istream\
    \ &>(std::cin);\n\n}  // namespace workspace\n#line 2 \"src/utils/io/ostream.hpp\"\
    \n\n/**\n * @file ostream.hpp\n * @brief Output Stream\n */\n\n#line 9 \"src/utils/io/ostream.hpp\"\
    \n\n#line 11 \"src/utils/io/ostream.hpp\"\n\nnamespace workspace {\n\ntemplate\
    \ <class _Os> struct is_ostream {\n  template <typename... _Args>\n  static std::true_type\
    \ __test(std::basic_ostream<_Args...> *);\n  static std::false_type __test(void\
    \ *);\n  constexpr static bool value = decltype(__test(std::declval<_Os *>()))::value;\n\
    };\n\ntemplate <class _Os>\nusing ostream_ref =\n    typename std::enable_if<is_ostream<_Os>::value,\
    \ _Os &>::type;\n\n/**\n * @brief Stream insertion operator for C-style array.\n\
    \ *\n * @param __os Output stream\n * @param __a Array\n * @return Reference to\
    \ __os.\n */\ntemplate <class _Os, class _Tp, size_t _Nm>\ntypename std::enable_if<bool(sizeof(_Tp)\
    \ > 2), ostream_ref<_Os>>::type\noperator<<(_Os &__os, const _Tp (&__a)[_Nm])\
    \ {\n  if _CXX17_CONSTEXPR (_Nm) {\n    __os << *__a;\n    for (auto __i = __a\
    \ + 1, __e = __a + _Nm; __i != __e; ++__i)\n      __os << ' ' << *__i;\n  }\n\
    \  return __os;\n}\n\n/**\n * @brief Stream insertion operator for std::array.\n\
    \ *\n * @param __os Output stream\n * @param __a Array\n * @return Reference to\
    \ __os.\n */\ntemplate <class _Os, class _Tp, size_t _Nm>\nostream_ref<_Os> operator<<(_Os\
    \ &__os, const std::array<_Tp, _Nm> &__a) {\n  if _CXX17_CONSTEXPR (_Nm) {\n \
    \   __os << __a[0];\n    for (size_t __i = 1; __i != _Nm; ++__i) __os << ' ' <<\
    \ __a[__i];\n  }\n  return __os;\n}\n\n/**\n * @brief Stream insertion operator\
    \ for std::pair.\n *\n * @param __os Output stream\n * @param __p Pair\n * @return\
    \ Reference to __os.\n */\ntemplate <class _Os, class _T1, class _T2>\nostream_ref<_Os>\
    \ operator<<(_Os &__os, const std::pair<_T1, _T2> &__p) {\n  return __os << __p.first\
    \ << ' ' << __p.second;\n}\n\n/**\n * @brief Stream insertion operator for std::tuple.\n\
    \ *\n * @param __os Output stream\n * @param __t Tuple\n * @return Reference to\
    \ __os.\n */\ntemplate <class _Os, class _Tp, size_t _Nm = 0>\ntypename std::enable_if<bool(std::tuple_size<_Tp>::value\
    \ + 1),\n                        ostream_ref<_Os>>::type\noperator<<(_Os &__os,\
    \ const _Tp &__t) {\n  if _CXX17_CONSTEXPR (_Nm != std::tuple_size<_Tp>::value)\
    \ {\n    if _CXX17_CONSTEXPR (_Nm) __os << ' ';\n    __os << std::get<_Nm>(__t);\n\
    \    operator<<<_Os, _Tp, _Nm + 1>(__os, __t);\n  }\n  return __os;\n}\n\ntemplate\
    \ <class _Os, class _Container,\n          typename = decltype(std::begin(std::declval<_Container>()))>\n\
    typename std::enable_if<\n    !std::is_same<std::decay_t<_Container>, std::string>::value\
    \ &&\n        !std::is_same<std::decay_t<_Container>, char *>::value,\n    ostream_ref<_Os>>::type\n\
    operator<<(_Os &__os, const _Container &__cont) {\n  bool __h = true;\n  for (auto\
    \ &&__e : __cont) __h ? __h = 0 : (__os << ' ', 0), __os << __e;\n  return __os;\n\
    }\n\n#ifdef __SIZEOF_INT128__\n\n/**\n * @brief Stream insertion operator for\
    \ __int128_t.\n *\n * @param __os Output Stream\n * @param __x 128-bit integer\n\
    \ * @return Reference to __os.\n */\ntemplate <class _Os> ostream_ref<_Os> operator<<(_Os\
    \ &__os, __int128_t __x) {\n  if (!__x) return __os << '0';\n  if (__x < 0) __os\
    \ << '-';\n  char __s[40], *__p = __s;\n  while (__x) {\n    auto __d = __x %\
    \ 10;\n    *__p++ = '0' + (__x < 0 ? -__d : __d);\n    __x /= 10;\n  }\n  *__p\
    \ = 0;\n  for (char *__t = __s; __t < --__p; ++__t) *__t ^= *__p ^= *__t ^= *__p;\n\
    \  return __os << __s;\n}\n\n/**\n * @brief Stream insertion operator for __uint128_t.\n\
    \ *\n * @param __os Output Stream\n * @param __x 128-bit unsigned integer\n *\
    \ @return Reference to __os.\n */\ntemplate <class _Os> ostream_ref<_Os> operator<<(_Os\
    \ &__os, __uint128_t __x) {\n  if (!__x) return __os << '0';\n  char __s[40],\
    \ *__p = __s;\n  while (__x) *__p++ = '0' + __x % 10, __x /= 10;\n  *__p = 0;\n\
    \  for (char *__t = __s; __t < --__p; ++__t) *__t ^= *__p ^= *__t ^= *__p;\n \
    \ return __os << __s;\n}\n\n#endif\n\n}  // namespace workspace\n#line 7 \"test/library-checker/convolution_mod.test.cpp\"\
    \n\nint main() {\n  using namespace workspace;\n\n  int n, m;\n  cin >> n >> m;\n\
    \  polynomial<modint<998244353>> a(n), b(m);\n  cin >> a >> b;\n  (a *= b).resize(n\
    \ + m - 1);\n  std::cout << a << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/convolution_mod\"\n\n#include\
    \ \"src/algebra/polynomial.hpp\"\n#include \"src/modular/modint.hpp\"\n#include\
    \ \"src/utils/io/istream.hpp\"\n#include \"src/utils/io/ostream.hpp\"\n\nint main()\
    \ {\n  using namespace workspace;\n\n  int n, m;\n  cin >> n >> m;\n  polynomial<modint<998244353>>\
    \ a(n), b(m);\n  cin >> a >> b;\n  (a *= b).resize(n + m - 1);\n  std::cout <<\
    \ a << \"\\n\";\n}\n"
  dependsOn:
  - src/algebra/polynomial.hpp
  - src/algebra/ntt.hpp
  - src/number_theory/ext_gcd.hpp
  - src/utils/sfinae.hpp
  - src/number_theory/primitive_root.hpp
  - src/modular/modint.hpp
  - src/number_theory/sqrt_mod.hpp
  - src/number_theory/pow_mod.hpp
  - src/utils/io/istream.hpp
  - src/utils/io/ostream.hpp
  isVerificationFile: true
  path: test/library-checker/convolution_mod.test.cpp
  requiredBy: []
  timestamp: '2021-05-31 22:43:54+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/library-checker/convolution_mod.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/convolution_mod.test.cpp
- /verify/test/library-checker/convolution_mod.test.cpp.html
title: test/library-checker/convolution_mod.test.cpp
---
