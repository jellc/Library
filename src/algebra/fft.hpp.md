---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/algebra/complex.hpp
    title: Complex Number
  - icon: ':heavy_check_mark:'
    path: src/number_theory/ext_gcd.hpp
    title: Extended Euclidean Algorithm
  - icon: ':heavy_check_mark:'
    path: src/number_theory/primitive_root.hpp
    title: Primitive Root
  - icon: ':heavy_check_mark:'
    path: src/utils/sfinae.hpp
    title: SFINAE
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: src/algebra/berlekamp_massey.hpp
    title: Berlekamp-Massey Algorithm
  - icon: ':heavy_check_mark:'
    path: src/algebra/fps.hpp
    title: Formal Power Series
  - icon: ':heavy_check_mark:'
    path: src/algebra/interpolation.hpp
    title: Polynomial Interpolation
  - icon: ':heavy_check_mark:'
    path: src/algebra/polynomial.hpp
    title: Polynomial
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/library-checker/convolution_mod.test.cpp
    title: test/library-checker/convolution_mod.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/division_of_polynomials.test.cpp
    title: test/library-checker/division_of_polynomials.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/exp_of_formal_power_series.test.cpp
    title: test/library-checker/exp_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/find_linear_recurrence.test.cpp
    title: test/library-checker/find_linear_recurrence.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/inv_of_formal_power_series.test.cpp
    title: test/library-checker/inv_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/log_of_formal_power_series.test.cpp
    title: test/library-checker/log_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/multipoint_evaluation.test.cpp
    title: test/library-checker/multipoint_evaluation.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/polynomial_interpolation.test.cpp
    title: test/library-checker/polynomial_interpolation.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/polynomial_taylor_shift.test.cpp
    title: test/library-checker/polynomial_taylor_shift.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/pow_of_formal_power_series.test.cpp
    title: test/library-checker/pow_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/sqrt_of_formal_power_series.test.cpp
    title: test/library-checker/sqrt_of_formal_power_series.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Fast Fourier Transform
    links: []
  bundledCode: "#line 2 \"src/algebra/fft.hpp\"\n\n/**\n * @file fft.hpp\n * @brief\
    \ Fast Fourier Transform\n */\n\n#include <vector>\n\n#line 2 \"src/algebra/complex.hpp\"\
    \n\n/**\n * @file complex.hpp\n * @brief Complex Number\n */\n\nnamespace workspace\
    \ {\n\n// Complex number.\ntemplate <class _Tp> class complex {\n  _Tp re, im;\n\
    \n  friend constexpr complex conj(const complex &x) noexcept {\n    return {x.re,\
    \ -x.im};\n  }\n\n  friend constexpr _Tp abs(const complex &x) noexcept {\n  \
    \  return hypot(x.re, x.im);\n  }\n\n  friend constexpr _Tp arg(const complex\
    \ &x) noexcept {\n    return atan2(x.re, x.im);\n  }\n\n  template <class _Is>\n\
    \  friend constexpr _Is &operator>>(_Is &__is, complex &x) noexcept {\n    return\
    \ __is >> x.re >> x.im;\n  }\n\n  template <class _Os>\n  friend constexpr _Os\
    \ &operator<<(_Os &__os, const complex &x) noexcept {\n    return __os << x.re\
    \ << ' ' << x.im;\n  }\n\n public:\n  constexpr complex() noexcept : re{}, im{}\
    \ {}\n  constexpr complex(_Tp _re) noexcept : re{_re}, im{} {}\n  constexpr complex(_Tp\
    \ _re, _Tp _im) noexcept : re{_re}, im{_im} {}\n\n  constexpr _Tp real() const\
    \ noexcept { return re; }\n  constexpr void real(_Tp _re) noexcept { re = _re;\
    \ }\n\n  constexpr _Tp imag() const noexcept { return im; }\n  constexpr void\
    \ imag(_Tp _im) noexcept { im = _im; }\n\n  constexpr complex operator+() const\
    \ noexcept { return *this; }\n  constexpr complex operator-() const noexcept {\
    \ return {-re, -im}; }\n\n  constexpr complex &operator+=(const complex &x) noexcept\
    \ {\n    return re += x.re, im += x.im, *this;\n  }\n  constexpr complex &operator-=(const\
    \ complex &x) noexcept {\n    return re -= x.re, im -= x.im, *this;\n  }\n  constexpr\
    \ complex &operator*=(const complex &x) noexcept {\n    _Tp _re{re * x.re - im\
    \ * x.im};\n    return im = im * x.re + x.im * re, re = _re, *this;\n  }\n  constexpr\
    \ complex &operator*=(_Tp x) noexcept {\n    return re *= x, im *= x, *this;\n\
    \  }\n  constexpr complex &operator/=(const complex &x) noexcept {\n    return\
    \ (*this *= conj(x)) /= re * re + im * im;\n  }\n  constexpr complex &operator/=(_Tp\
    \ x) noexcept {\n    return re /= x, im /= x, *this;\n  }\n\n  constexpr complex\
    \ operator+(const complex &x) const noexcept {\n    return {re + x.re, im + x.im};\n\
    \  }\n  constexpr complex operator-(const complex &x) const noexcept {\n    return\
    \ {re - x.re, im - x.im};\n  }\n\n  constexpr complex operator*(const complex\
    \ &x) const noexcept {\n    return complex(*this) *= x;\n  }\n\n  constexpr complex\
    \ operator*(_Tp x) const noexcept { return {re * x, im * x}; }\n\n  constexpr\
    \ complex operator/(const complex &x) const noexcept {\n    return complex(*this)\
    \ /= x;\n  }\n\n  constexpr complex operator/(_Tp x) const noexcept { return {re\
    \ / x, im / x}; }\n};\n\n}  // namespace workspace\n#line 2 \"lib/cxx17\"\n\n\
    #line 2 \"lib/cxx14\"\n\n#ifndef _CXX14_CONSTEXPR\n#if __cplusplus >= 201402L\n\
    #define _CXX14_CONSTEXPR constexpr\n#else\n#define _CXX14_CONSTEXPR\n#endif\n\
    #endif\n#line 4 \"lib/cxx17\"\n\n#ifndef _CXX17_CONSTEXPR\n#if __cplusplus >=\
    \ 201703L\n#define _CXX17_CONSTEXPR constexpr\n#else\n#define _CXX17_CONSTEXPR\n\
    #endif\n#endif\n\n#ifndef _CXX17_STATIC_ASSERT\n#if __cplusplus >= 201703L\n#define\
    \ _CXX17_STATIC_ASSERT static_assert\n#else\n#define _CXX17_STATIC_ASSERT assert\n\
    #endif\n#endif\n\n#include <iterator>\n\n#if __cplusplus < 201703L\n\nnamespace\
    \ std {\n\n/**\n *  @brief  Return the size of a container.\n *  @param  __cont\
    \  Container.\n */\ntemplate <typename _Container>\nconstexpr auto size(const\
    \ _Container& __cont) noexcept(noexcept(__cont.size()))\n    -> decltype(__cont.size())\
    \ {\n  return __cont.size();\n}\n\n/**\n *  @brief  Return the size of an array.\n\
    \ */\ntemplate <typename _Tp, size_t _Nm>\nconstexpr size_t size(const _Tp (&)[_Nm])\
    \ noexcept {\n  return _Nm;\n}\n\n/**\n *  @brief  Return whether a container\
    \ is empty.\n *  @param  __cont  Container.\n */\ntemplate <typename _Container>\n\
    [[nodiscard]] constexpr auto empty(const _Container& __cont) noexcept(\n    noexcept(__cont.empty()))\
    \ -> decltype(__cont.empty()) {\n  return __cont.empty();\n}\n\n/**\n *  @brief\
    \  Return whether an array is empty (always false).\n */\ntemplate <typename _Tp,\
    \ size_t _Nm>\n[[nodiscard]] constexpr bool empty(const _Tp (&)[_Nm]) noexcept\
    \ {\n  return false;\n}\n\n/**\n *  @brief  Return whether an initializer_list\
    \ is empty.\n *  @param  __il  Initializer list.\n */\ntemplate <typename _Tp>\n\
    [[nodiscard]] constexpr bool empty(initializer_list<_Tp> __il) noexcept {\n  return\
    \ __il.size() == 0;\n}\n\nstruct monostate {};\n\n}  // namespace std\n\n#else\n\
    \n#include <variant>\n\n#endif\n#line 2 \"src/number_theory/ext_gcd.hpp\"\n\n\
    /**\n * @file ext_gcd.hpp\n * @brief Extended Euclidean Algorithm\n */\n\n#include\
    \ <tuple>\n\n#line 2 \"src/utils/sfinae.hpp\"\n\n/**\n * @file sfinae.hpp\n *\
    \ @brief SFINAE\n */\n\n#include <cstdint>\n#line 10 \"src/utils/sfinae.hpp\"\n\
    #include <type_traits>\n\n#ifndef __INT128_DEFINED__\n\n#ifdef __SIZEOF_INT128__\n\
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
    }  // namespace workspace\n#line 11 \"src/number_theory/ext_gcd.hpp\"\n\nnamespace\
    \ workspace {\n\n/**\n * @param __a Integer\n * @param __b Integer\n * @return\
    \ Pair of integers (x, y) s.t. ax + by = g = gcd(a, b) and (b = 0 or 0\n * <=\
    \ x < |b/g|) and (a = 0 or -|a/g| < y <= 0). Return (0, 0) if (a, b) = (0,\n *\
    \ 0).\n */\ntemplate <typename _T1, typename _T2>\nconstexpr auto ext_gcd(_T1\
    \ __a, _T2 __b) noexcept {\n  static_assert(is_integral_ext<_T1>::value);\n  static_assert(is_integral_ext<_T2>::value);\n\
    \n  using value_type = typename std::make_signed<\n      typename std::common_type<_T1,\
    \ _T2>::type>::type;\n  using result_type = std::pair<value_type, value_type>;\n\
    \n  value_type a{__a}, b{__b}, p{1}, q{}, r{}, s{1};\n\n  while (b != value_type(0))\
    \ {\n    auto t = a / b;\n    r ^= p ^= r ^= p -= t * r;\n    s ^= q ^= s ^= q\
    \ -= t * s;\n    b ^= a ^= b ^= a -= t * b;\n  }\n\n  if (a < 0) p = -p, q = -q,\
    \ a = -a;\n\n  if (p < 0) {\n    __a /= a, __b /= a;\n\n    if (__b > 0)\n   \
    \   p += __b, q -= __a;\n    else\n      p -= __b, q += __a;\n  }\n\n  return\
    \ result_type{p, q};\n}\n\n/**\n * @param __a Integer\n * @param __b Integer\n\
    \ * @param __c Integer\n * @return Pair of integers (x, y) s.t. ax + by = c and\
    \ (b = 0 or 0 <= x <\n * |b/g|). Return (0, 0) if there is no solution.\n */\n\
    template <typename _T1, typename _T2, typename _T3>\nconstexpr auto ext_gcd(_T1\
    \ __a, _T2 __b, _T3 __c) noexcept {\n  static_assert(is_integral_ext<_T1>::value);\n\
    \  static_assert(is_integral_ext<_T2>::value);\n  static_assert(is_integral_ext<_T3>::value);\n\
    \n  using value_type = typename std::make_signed<\n      typename std::common_type<_T1,\
    \ _T2, _T3>::type>::type;\n  using result_type = std::pair<value_type, value_type>;\n\
    \n  value_type a{__a}, b{__b}, p{1}, q{}, r{}, s{1};\n\n  while (b != value_type(0))\
    \ {\n    auto t = a / b;\n    r ^= p ^= r ^= p -= t * r;\n    s ^= q ^= s ^= q\
    \ -= t * s;\n    b ^= a ^= b ^= a -= t * b;\n  }\n\n  if (__c % a) return result_type{};\n\
    \n  __a /= a, __b /= a, __c /= a;\n  p *= __c, q *= __c;\n\n  if (__b != value_type(0))\
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
    #line 15 \"src/algebra/fft.hpp\"\n\nnamespace workspace {\n\nnamespace _fft_impl\
    \ {\n\ntemplate <class _Tp, bool = std::is_floating_point<_Tp>::value, class =\
    \ void>\nstruct to_float {\n  using type = double;\n};\n\ntemplate <class _Tp>\
    \ struct to_float<_Tp, true> { using type = _Tp; };\n\n// template <class _Tp>\n\
    // struct to_float<_Tp, false, std::enable_if_t<sizeof(_Tp) <= sizeof(float)>>\
    \ {\n//   using type = float;\n// };\n\ntemplate <class _Tp>\nstruct to_float<_Tp,\
    \ false, std::enable_if_t<(sizeof(_Tp) > sizeof(double))>> {\n  using type = long\
    \ double;\n};\n\n// Assume ntt-friendly mod.\ntemplate <class _Tp> struct field\
    \ {\n  using type = std::conditional_t<has_mod<_Tp>::value, _Tp,\n           \
    \                       complex<typename to_float<_Tp>::type>>;\n};\n\ntemplate\
    \ <class _Tp> struct field<complex<_Tp>> : field<_Tp> {};\n\n// Modular\ntemplate\
    \ <class _Tp, int _Nm = 29, bool = has_mod<_Tp>::value> struct coef {\n  _Tp s[_Nm],\
    \ is[_Nm], ip2[_Nm];\n\n  _CXX14_CONSTEXPR coef() : s{}, is{}, ip2{1, (1 + _Tp::mod)\
    \ / 2} {\n    if (_Tp::mod < 2) return;\n\n    int cnt2 = std::min(__builtin_ctz(_Tp::mod\
    \ - 1), _Nm + 1);\n\n    _Tp e = 1;\n    _Tp w = primitive_root(_Tp::mod);\n \
    \   for (auto p = (_Tp::mod - 1) >> cnt2; p; p >>= 1, w *= w)\n      if (p & 1)\
    \ e *= w;\n\n    _Tp ie = ext_gcd(decltype(_Tp::mod)(e), _Tp::mod).first;\n  \
    \  _Tp es[_Nm]{}, ies[_Nm]{};\n\n    for (int i = cnt2; i >= 2; i--) {\n     \
    \ es[i - 2] = e, e *= e;\n      ies[i - 2] = ie, ie *= ie;\n    }\n\n    e = ie\
    \ = 1;\n    for (int i = 0; i < cnt2 - 1; i++) {\n      s[i] = es[i] * e, e *=\
    \ ies[i];\n      is[i] = ies[i] * ie, ie *= es[i];\n    }\n\n    for (int i =\
    \ 1; i < _Nm - 1; ++i) ip2[i + 1] = ip2[i] * ip2[1];\n  }\n};\n\n// Complex\n\
    template <class _Tp, int _Nm> struct coef<_Tp, _Nm, false> {\n  _Tp s[_Nm], is[_Nm],\
    \ ip2[_Nm];\n\n  static_assert(_Nm < 30);\n\n  _CXX14_CONSTEXPR static _Tp es[29]\
    \ = {\n      {0, 1},\n      {0.70710678118654752438189403651, 0.70710678118654752443610414514},\n\
    \      {0.92387953251128675610142140795, 0.38268343236508977172325753068},\n \
    \     {0.98078528040323044911909938781, 0.19509032201612826785692544201},\n  \
    \    {0.99518472667219688623102546998, 0.09801714032956060199569840382},\n   \
    \   {0.99879545620517239270077028412, 0.04906767432741801425693899119},\n    \
    \  {0.99969881869620422009748220149, 0.02454122852291228803212346128},\n     \
    \ {0.99992470183914454093764001552, 0.01227153828571992607945510345},\n      {0.99998117528260114264494415325,\
    \ 0.00613588464915447535972750246},\n      {0.99999529380957617150137498041, 0.00306795676296597627029751672},\n\
    \      {0.99999882345170190993313003025, 0.00153398018628476561237225788},\n \
    \     {0.99999970586288221914474799723, 0.00076699031874270452695124765},\n  \
    \    {0.99999992646571785113833452651, 0.00038349518757139558906815188},\n   \
    \   {0.99999998161642929381167504976, 0.00019174759731070330743679009},\n    \
    \  {0.99999999540410731290905263501, 0.00009587379909597734587360460},\n     \
    \ {0.99999999885102682753608427379, 0.00004793689960306688454884772},\n      {0.99999999971275670682981095982,\
    \ 0.00002396844980841821872882467},\n      {0.99999999992818917670745273995, 0.00001198422490506970642183282},\n\
    \      {0.99999999998204729416331065783, 0.00000599211245264242784278378},\n \
    \     {0.99999999999551182356793271877, 0.00000299605622633466075058210},\n  \
    \    {0.99999999999887795586487812538, 0.00000149802811316901122883643},\n   \
    \   {0.99999999999971948897977205850, 0.00000074901405658471572113723},\n    \
    \  {0.99999999999992987223139048746, 0.00000037450702829238412391495},\n     \
    \ {0.99999999999998246807140014902, 0.00000018725351414619534486931},\n      {0.99999999999999561700429751010,\
    \ 0.00000009362675707309808280024},\n      {0.99999999999999890425107437752, 0.00000004681337853654909269501},\n\
    \      {0.99999999999999972607632112153, 0.00000002340668926827455275977},\n \
    \     {0.99999999999999993153263280754, 0.00000001170334463413727718121},\n  \
    \    {0.99999999999999998286960567472, 0.00000000585167231706863869077}};\n\n\
    \  _CXX14_CONSTEXPR coef() : s{}, is{}, ip2{1, .5} {\n    _Tp ies[_Nm];\n    for\
    \ (int i = 0; i < _Nm; ++i) ies[i] = _Tp(1) / es[i];\n\n    _Tp e = 1, ie = 1;\n\
    \    for (int i = 0; i < _Nm; i++) {\n      s[i] = es[i] * e, e *= ies[i];\n \
    \     is[i] = ies[i] * ie, ie *= es[i];\n    }\n\n    for (int i = 1; i < _Nm\
    \ - 1; ++i) ip2[i + 1] = ip2[i] * ip2[1];\n  }\n};\n\n}  // namespace _fft_impl\n\
    \ntemplate <bool _Inverse = false, class _Iterator>\nvoid fft(_Iterator __first,\
    \ _Iterator __last) noexcept {\n  using value_type = typename std::iterator_traits<_Iterator>::value_type;\n\
    \  using difference_type =\n      typename std::iterator_traits<_Iterator>::difference_type;\n\
    \n  _CXX14_CONSTEXPR _fft_impl::coef<value_type> c;\n  auto __h = __builtin_ctz(std::distance(__first,\
    \ __last));\n\n  if _CXX17_CONSTEXPR (_Inverse) {\n    for (difference_type __p\
    \ = 1; __p >> __h ^ 1; __p <<= 1) {\n      value_type __iw = 1;\n      auto __l\
    \ = __first;\n\n      for (auto __i = 1 << __h; __l != __last;\n           __iw\
    \ *= c.is[__builtin_ctz(--__i)]) {\n        auto __r = std::next(__l, __p);\n\n\
    \        for (auto __mid = __r; __l != __mid; ++__l, ++__r) {\n          auto\
    \ __tmp = (*__l - *__r) * __iw;\n          *__l += *__r;\n          *__r = __tmp;\n\
    \        }\n\n        __l = __r;\n      }\n    }\n\n    while (__first != __last)\
    \ *--__last *= c.ip2[__h];\n  }\n\n  else {\n    for (difference_type __p = 1\
    \ << __h; __p >>= 1;) {\n      value_type __w = -1;\n      auto __l = __first;\n\
    \n      for (auto __i = 1 << __h; __l != __last;\n           __w *= c.s[__builtin_ctz(--__i)])\
    \ {\n        auto __r = std::next(__l, __p);\n\n        for (auto __mid = __r;\
    \ __l != __mid; ++__l, ++__r) {\n          auto __tmp = *__l;\n          *__l\
    \ -= *__r *= __w;\n          *__r += __tmp;\n        }\n\n        __l = __r;\n\
    \      }\n    }\n  }\n}\n\ntemplate <class _Iterator>\nvoid fft(_Iterator __first,\
    \ std::size_t __n) noexcept {\n  fft(__first, std::next(__first, __n));\n}\n\n\
    template <class _Iterator>\nvoid ifft(_Iterator __first, _Iterator __last) noexcept\
    \ {\n  fft<true>(__first, __last);\n}\n\ntemplate <class _Iterator>\nvoid ifft(_Iterator\
    \ __first, std::size_t __n) noexcept {\n  ifft(__first, std::next(__first, __n));\n\
    }\n\ntemplate <size_t _Nm, size_t _Dm, class _Container, class _Index>\ndecltype(auto)\
    \ access(_Container &__a, const _Index &__i) {\n  if _CXX17_CONSTEXPR (_Nm !=\
    \ _Dm)\n    return access<_Nm + 1, _Dm>(__a[__i[_Nm]], __i);\n  else\n    return\
    \ __a;\n}\n\ntemplate <bool _Inverse, size_t _Dm, class _Container, class _Tp,\
    \ class _Index>\nvoid dive(_Container &__a, const _Tp &__t, _Index &__i) {\n \
    \ if _CXX17_CONSTEXPR (has_size<_Tp>::value) {\n    for (__i.emplace_back(0);\
    \ __i.back() != std::size(__t); ++__i.back())\n      dive<_Inverse, _Dm + 1>(__a,\
    \ __t[__i.back()], __i);\n    __i.pop_back();\n  }\n\n  else {\n    static std::vector<_Tp>\
    \ __work;\n    // Resize to a power of 2.\n\n    size_t __len = 1 << (31 - __builtin_clz(std::size(__a)));\n\
    \    if (__work.size() < __len) __work.resize(__len);\n\n    for (size_t __k =\
    \ 0; __k != __len; ++__k)\n      __work[__k] = std::move(access<0, _Dm>(__a[__k],\
    \ __i));\n\n    fft<_Inverse>(__work.data(), __work.data() + __len);\n\n    for\
    \ (size_t __k = 0; __k != __len; ++__k)\n      access<0, _Dm>(__a[__k], __i) =\
    \ std::move(__work[__k]);\n  }\n}\n\ntemplate <bool _Inverse, class _Container>\
    \ void fft(_Container &__a) {\n  if _CXX17_CONSTEXPR (has_size<_Container>::value)\
    \ {\n    if _CXX17_CONSTEXPR (has_resize<_Container>::value)\n      // Resize\
    \ to a power of 2.\n      __a.resize(1 << (32 - __builtin_clz(__a.size() - 1)));\n\
    \n    std::vector<size_t> __i;\n    dive<_Inverse, 0>(__a, __a[0], __i);\n\n \
    \   for (size_t __k = 0; __k != std::size(__a); ++__k) fft<_Inverse>(__a[__k]);\n\
    \  }\n}\n\ntemplate <class _Container> auto conv_resize(_Container &__a, _Container\
    \ &__b) {\n  std::array<size_t, get_dimension<_Container>::value> __s;\n  rec(__a,\
    \ __s);\n  rec(__b, __s);\n  return __s;\n}\n\ntemplate <size_t _Nm, class _Container,\
    \ class _Size>\nvoid rec(const _Container &__a, _Size &__s) {\n  if _CXX17_CONSTEXPR\
    \ (_Nm != __s.size()) {\n    __s[_Nm] = std::max(__s[_Nm], std::size(__a));\n\
    \    for (auto &__x : __a) rec<_Nm + 1>(__x, __s);\n  }\n}\n\n}  // namespace\
    \ workspace\n"
  code: "#pragma once\n\n/**\n * @file fft.hpp\n * @brief Fast Fourier Transform\n\
    \ */\n\n#include <vector>\n\n#include \"complex.hpp\"\n#include \"lib/cxx17\"\n\
    #include \"src/number_theory/ext_gcd.hpp\"\n#include \"src/number_theory/primitive_root.hpp\"\
    \n#include \"src/utils/sfinae.hpp\"\n\nnamespace workspace {\n\nnamespace _fft_impl\
    \ {\n\ntemplate <class _Tp, bool = std::is_floating_point<_Tp>::value, class =\
    \ void>\nstruct to_float {\n  using type = double;\n};\n\ntemplate <class _Tp>\
    \ struct to_float<_Tp, true> { using type = _Tp; };\n\n// template <class _Tp>\n\
    // struct to_float<_Tp, false, std::enable_if_t<sizeof(_Tp) <= sizeof(float)>>\
    \ {\n//   using type = float;\n// };\n\ntemplate <class _Tp>\nstruct to_float<_Tp,\
    \ false, std::enable_if_t<(sizeof(_Tp) > sizeof(double))>> {\n  using type = long\
    \ double;\n};\n\n// Assume ntt-friendly mod.\ntemplate <class _Tp> struct field\
    \ {\n  using type = std::conditional_t<has_mod<_Tp>::value, _Tp,\n           \
    \                       complex<typename to_float<_Tp>::type>>;\n};\n\ntemplate\
    \ <class _Tp> struct field<complex<_Tp>> : field<_Tp> {};\n\n// Modular\ntemplate\
    \ <class _Tp, int _Nm = 29, bool = has_mod<_Tp>::value> struct coef {\n  _Tp s[_Nm],\
    \ is[_Nm], ip2[_Nm];\n\n  _CXX14_CONSTEXPR coef() : s{}, is{}, ip2{1, (1 + _Tp::mod)\
    \ / 2} {\n    if (_Tp::mod < 2) return;\n\n    int cnt2 = std::min(__builtin_ctz(_Tp::mod\
    \ - 1), _Nm + 1);\n\n    _Tp e = 1;\n    _Tp w = primitive_root(_Tp::mod);\n \
    \   for (auto p = (_Tp::mod - 1) >> cnt2; p; p >>= 1, w *= w)\n      if (p & 1)\
    \ e *= w;\n\n    _Tp ie = ext_gcd(decltype(_Tp::mod)(e), _Tp::mod).first;\n  \
    \  _Tp es[_Nm]{}, ies[_Nm]{};\n\n    for (int i = cnt2; i >= 2; i--) {\n     \
    \ es[i - 2] = e, e *= e;\n      ies[i - 2] = ie, ie *= ie;\n    }\n\n    e = ie\
    \ = 1;\n    for (int i = 0; i < cnt2 - 1; i++) {\n      s[i] = es[i] * e, e *=\
    \ ies[i];\n      is[i] = ies[i] * ie, ie *= es[i];\n    }\n\n    for (int i =\
    \ 1; i < _Nm - 1; ++i) ip2[i + 1] = ip2[i] * ip2[1];\n  }\n};\n\n// Complex\n\
    template <class _Tp, int _Nm> struct coef<_Tp, _Nm, false> {\n  _Tp s[_Nm], is[_Nm],\
    \ ip2[_Nm];\n\n  static_assert(_Nm < 30);\n\n  _CXX14_CONSTEXPR static _Tp es[29]\
    \ = {\n      {0, 1},\n      {0.70710678118654752438189403651, 0.70710678118654752443610414514},\n\
    \      {0.92387953251128675610142140795, 0.38268343236508977172325753068},\n \
    \     {0.98078528040323044911909938781, 0.19509032201612826785692544201},\n  \
    \    {0.99518472667219688623102546998, 0.09801714032956060199569840382},\n   \
    \   {0.99879545620517239270077028412, 0.04906767432741801425693899119},\n    \
    \  {0.99969881869620422009748220149, 0.02454122852291228803212346128},\n     \
    \ {0.99992470183914454093764001552, 0.01227153828571992607945510345},\n      {0.99998117528260114264494415325,\
    \ 0.00613588464915447535972750246},\n      {0.99999529380957617150137498041, 0.00306795676296597627029751672},\n\
    \      {0.99999882345170190993313003025, 0.00153398018628476561237225788},\n \
    \     {0.99999970586288221914474799723, 0.00076699031874270452695124765},\n  \
    \    {0.99999992646571785113833452651, 0.00038349518757139558906815188},\n   \
    \   {0.99999998161642929381167504976, 0.00019174759731070330743679009},\n    \
    \  {0.99999999540410731290905263501, 0.00009587379909597734587360460},\n     \
    \ {0.99999999885102682753608427379, 0.00004793689960306688454884772},\n      {0.99999999971275670682981095982,\
    \ 0.00002396844980841821872882467},\n      {0.99999999992818917670745273995, 0.00001198422490506970642183282},\n\
    \      {0.99999999998204729416331065783, 0.00000599211245264242784278378},\n \
    \     {0.99999999999551182356793271877, 0.00000299605622633466075058210},\n  \
    \    {0.99999999999887795586487812538, 0.00000149802811316901122883643},\n   \
    \   {0.99999999999971948897977205850, 0.00000074901405658471572113723},\n    \
    \  {0.99999999999992987223139048746, 0.00000037450702829238412391495},\n     \
    \ {0.99999999999998246807140014902, 0.00000018725351414619534486931},\n      {0.99999999999999561700429751010,\
    \ 0.00000009362675707309808280024},\n      {0.99999999999999890425107437752, 0.00000004681337853654909269501},\n\
    \      {0.99999999999999972607632112153, 0.00000002340668926827455275977},\n \
    \     {0.99999999999999993153263280754, 0.00000001170334463413727718121},\n  \
    \    {0.99999999999999998286960567472, 0.00000000585167231706863869077}};\n\n\
    \  _CXX14_CONSTEXPR coef() : s{}, is{}, ip2{1, .5} {\n    _Tp ies[_Nm];\n    for\
    \ (int i = 0; i < _Nm; ++i) ies[i] = _Tp(1) / es[i];\n\n    _Tp e = 1, ie = 1;\n\
    \    for (int i = 0; i < _Nm; i++) {\n      s[i] = es[i] * e, e *= ies[i];\n \
    \     is[i] = ies[i] * ie, ie *= es[i];\n    }\n\n    for (int i = 1; i < _Nm\
    \ - 1; ++i) ip2[i + 1] = ip2[i] * ip2[1];\n  }\n};\n\n}  // namespace _fft_impl\n\
    \ntemplate <bool _Inverse = false, class _Iterator>\nvoid fft(_Iterator __first,\
    \ _Iterator __last) noexcept {\n  using value_type = typename std::iterator_traits<_Iterator>::value_type;\n\
    \  using difference_type =\n      typename std::iterator_traits<_Iterator>::difference_type;\n\
    \n  _CXX14_CONSTEXPR _fft_impl::coef<value_type> c;\n  auto __h = __builtin_ctz(std::distance(__first,\
    \ __last));\n\n  if _CXX17_CONSTEXPR (_Inverse) {\n    for (difference_type __p\
    \ = 1; __p >> __h ^ 1; __p <<= 1) {\n      value_type __iw = 1;\n      auto __l\
    \ = __first;\n\n      for (auto __i = 1 << __h; __l != __last;\n           __iw\
    \ *= c.is[__builtin_ctz(--__i)]) {\n        auto __r = std::next(__l, __p);\n\n\
    \        for (auto __mid = __r; __l != __mid; ++__l, ++__r) {\n          auto\
    \ __tmp = (*__l - *__r) * __iw;\n          *__l += *__r;\n          *__r = __tmp;\n\
    \        }\n\n        __l = __r;\n      }\n    }\n\n    while (__first != __last)\
    \ *--__last *= c.ip2[__h];\n  }\n\n  else {\n    for (difference_type __p = 1\
    \ << __h; __p >>= 1;) {\n      value_type __w = -1;\n      auto __l = __first;\n\
    \n      for (auto __i = 1 << __h; __l != __last;\n           __w *= c.s[__builtin_ctz(--__i)])\
    \ {\n        auto __r = std::next(__l, __p);\n\n        for (auto __mid = __r;\
    \ __l != __mid; ++__l, ++__r) {\n          auto __tmp = *__l;\n          *__l\
    \ -= *__r *= __w;\n          *__r += __tmp;\n        }\n\n        __l = __r;\n\
    \      }\n    }\n  }\n}\n\ntemplate <class _Iterator>\nvoid fft(_Iterator __first,\
    \ std::size_t __n) noexcept {\n  fft(__first, std::next(__first, __n));\n}\n\n\
    template <class _Iterator>\nvoid ifft(_Iterator __first, _Iterator __last) noexcept\
    \ {\n  fft<true>(__first, __last);\n}\n\ntemplate <class _Iterator>\nvoid ifft(_Iterator\
    \ __first, std::size_t __n) noexcept {\n  ifft(__first, std::next(__first, __n));\n\
    }\n\ntemplate <size_t _Nm, size_t _Dm, class _Container, class _Index>\ndecltype(auto)\
    \ access(_Container &__a, const _Index &__i) {\n  if _CXX17_CONSTEXPR (_Nm !=\
    \ _Dm)\n    return access<_Nm + 1, _Dm>(__a[__i[_Nm]], __i);\n  else\n    return\
    \ __a;\n}\n\ntemplate <bool _Inverse, size_t _Dm, class _Container, class _Tp,\
    \ class _Index>\nvoid dive(_Container &__a, const _Tp &__t, _Index &__i) {\n \
    \ if _CXX17_CONSTEXPR (has_size<_Tp>::value) {\n    for (__i.emplace_back(0);\
    \ __i.back() != std::size(__t); ++__i.back())\n      dive<_Inverse, _Dm + 1>(__a,\
    \ __t[__i.back()], __i);\n    __i.pop_back();\n  }\n\n  else {\n    static std::vector<_Tp>\
    \ __work;\n    // Resize to a power of 2.\n\n    size_t __len = 1 << (31 - __builtin_clz(std::size(__a)));\n\
    \    if (__work.size() < __len) __work.resize(__len);\n\n    for (size_t __k =\
    \ 0; __k != __len; ++__k)\n      __work[__k] = std::move(access<0, _Dm>(__a[__k],\
    \ __i));\n\n    fft<_Inverse>(__work.data(), __work.data() + __len);\n\n    for\
    \ (size_t __k = 0; __k != __len; ++__k)\n      access<0, _Dm>(__a[__k], __i) =\
    \ std::move(__work[__k]);\n  }\n}\n\ntemplate <bool _Inverse, class _Container>\
    \ void fft(_Container &__a) {\n  if _CXX17_CONSTEXPR (has_size<_Container>::value)\
    \ {\n    if _CXX17_CONSTEXPR (has_resize<_Container>::value)\n      // Resize\
    \ to a power of 2.\n      __a.resize(1 << (32 - __builtin_clz(__a.size() - 1)));\n\
    \n    std::vector<size_t> __i;\n    dive<_Inverse, 0>(__a, __a[0], __i);\n\n \
    \   for (size_t __k = 0; __k != std::size(__a); ++__k) fft<_Inverse>(__a[__k]);\n\
    \  }\n}\n\ntemplate <class _Container> auto conv_resize(_Container &__a, _Container\
    \ &__b) {\n  std::array<size_t, get_dimension<_Container>::value> __s;\n  rec(__a,\
    \ __s);\n  rec(__b, __s);\n  return __s;\n}\n\ntemplate <size_t _Nm, class _Container,\
    \ class _Size>\nvoid rec(const _Container &__a, _Size &__s) {\n  if _CXX17_CONSTEXPR\
    \ (_Nm != __s.size()) {\n    __s[_Nm] = std::max(__s[_Nm], std::size(__a));\n\
    \    for (auto &__x : __a) rec<_Nm + 1>(__x, __s);\n  }\n}\n\n}  // namespace\
    \ workspace\n"
  dependsOn:
  - src/algebra/complex.hpp
  - src/number_theory/ext_gcd.hpp
  - src/utils/sfinae.hpp
  - src/number_theory/primitive_root.hpp
  isVerificationFile: false
  path: src/algebra/fft.hpp
  requiredBy:
  - src/algebra/interpolation.hpp
  - src/algebra/polynomial.hpp
  - src/algebra/berlekamp_massey.hpp
  - src/algebra/fps.hpp
  timestamp: '2022-04-06 15:02:09+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/log_of_formal_power_series.test.cpp
  - test/library-checker/sqrt_of_formal_power_series.test.cpp
  - test/library-checker/find_linear_recurrence.test.cpp
  - test/library-checker/pow_of_formal_power_series.test.cpp
  - test/library-checker/multipoint_evaluation.test.cpp
  - test/library-checker/polynomial_interpolation.test.cpp
  - test/library-checker/inv_of_formal_power_series.test.cpp
  - test/library-checker/polynomial_taylor_shift.test.cpp
  - test/library-checker/division_of_polynomials.test.cpp
  - test/library-checker/exp_of_formal_power_series.test.cpp
  - test/library-checker/convolution_mod.test.cpp
documentation_of: src/algebra/fft.hpp
layout: document
redirect_from:
- /library/src/algebra/fft.hpp
- /library/src/algebra/fft.hpp.html
title: Fast Fourier Transform
---
