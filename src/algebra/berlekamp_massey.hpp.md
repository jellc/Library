---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/algebra/complex.hpp
    title: Complex Number
  - icon: ':heavy_check_mark:'
    path: src/algebra/fft.hpp
    title: Fast Fourier Transform
  - icon: ':heavy_check_mark:'
    path: src/algebra/polynomial.hpp
    title: Polynomial
  - icon: ':heavy_check_mark:'
    path: src/number_theory/ext_gcd.hpp
    title: Extended Euclidean Algorithm
  - icon: ':heavy_check_mark:'
    path: src/number_theory/primitive_root.hpp
    title: Primitive Root
  - icon: ':question:'
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
    \ \"src/algebra/fft.hpp\"\n\n/**\n * @file fft.hpp\n * @brief Fast Fourier Transform\n\
    \ */\n\n#line 9 \"src/algebra/fft.hpp\"\n\n#line 2 \"src/algebra/complex.hpp\"\
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
    \ workspace\n#line 15 \"src/algebra/polynomial.hpp\"\n\nnamespace workspace {\n\
    \n/**\n * @brief Polynomial.\n *\n * @tparam _Tp Ring structure\n * @tparam _Conv_threshold\
    \ Threshold for convolution method\n */\ntemplate <class _Tp, std::size_t _Conv_threshold\
    \ = 64>\nclass polynomial : public std::vector<_Tp> {\n  using vec = std::vector<_Tp>;\n\
    \  using poly = polynomial;\n\n  template <class _Os> friend _Os& operator<<(_Os&\
    \ __os, const poly& __x) {\n    bool __head = true;\n    for (const auto& __a\
    \ : __x) {\n      if (!__head) __os << ' ';\n      __head = false;\n      __os\
    \ << __a;\n    }\n    return __os;\n  }\n\n public:\n  using typename vec::size_type;\n\
    \  using typename vec::value_type;\n  using vec::size;\n  using vec::vec;\n\n\
    \  using field = typename _fft_impl::field<_Tp>::type;\n\n protected:\n  constexpr\
    \ static _fft_impl::coef<field> __coef{};\n  static std::vector<field> __work1,\
    \ __work2;\n\n  void _erase_leading_zeros() noexcept {\n    auto __i = vec::_M_impl._M_finish;\n\
    \    while (__i != vec::_M_impl._M_start && *(__i - 1) == _Tp(0)) --__i;\n   \
    \ vec::_M_erase_at_end(__i);\n  }\n\n  template <class _Iter> void _dft(_Iter\
    \ __first, _Iter __last) const noexcept {\n    fft<false>(__first, __last);\n\
    \  }\n\n  template <class _Iter>\n  void _idft(_Iter __first, _Iter __last) const\
    \ noexcept {\n    fft<true>(__first, __last);\n  }\n\n  void _conv_naive(const\
    \ poly& __x) noexcept {\n    if (vec::_M_impl._M_start == vec::_M_impl._M_finish)\
    \ return;\n\n    if (__x._M_impl._M_start == __x._M_impl._M_finish) {\n      vec::_M_erase_at_end(vec::_M_impl._M_start);\n\
    \      return;\n    }\n\n    vec::_M_default_append(__x._M_impl._M_finish - __x._M_impl._M_start\
    \ - 1);\n\n    for (auto __i = vec::_M_impl._M_finish; __i-- != vec::_M_impl._M_start;)\
    \ {\n      auto __j = __i, __k = __x._M_impl._M_start;\n      *__i *= *__k++;\n\
    \n      while (__j != vec::_M_impl._M_start && __k != __x._M_impl._M_finish)\n\
    \        *__i += *--__j * *__k++;\n    }\n  }\n\n  template <class _Poly> void\
    \ _conv_dft(_Poly&& __x) noexcept {\n    size_type __n = vec::_M_impl._M_finish\
    \ - vec::_M_impl._M_start,\n              __m = __x._M_impl._M_finish - __x._M_impl._M_start,\n\
    \              __len = 1 << (32 - __builtin_clz(__n + __m - 1));\n\n    if (__work1.size()\
    \ < __len) __work1.resize(__len);\n    if (__work2.size() < __len) __work2.resize(__len);\n\
    \n    vec::_M_default_append(__m - 1);\n\n    if _CXX17_CONSTEXPR (std::is_same<_Tp,\
    \ field>::value) {\n      std::fill(std::move(vec::_M_impl._M_start, vec::_M_impl._M_finish,\n\
    \                          __work1.data()),\n                __work1.data() +\
    \ __len, _Tp(0));\n\n      std::fill(std::move(__x._M_impl._M_start, __x._M_impl._M_finish,\n\
    \                          __work2.data()),\n                __work2.data() +\
    \ __len, _Tp(0));\n\n      fft(__work1.data(), __len);\n      fft(__work2.data(),\
    \ __len);\n\n      for (size_type __i = 0; __i < __len; ++__i)\n        __work1[__i]\
    \ *= std::move(__work2[__i]);\n\n      ifft(__work1.data(), __len);\n\n      std::move(__work1.data(),\
    \ __work1.data() + __n + __m - 1,\n                vec::_M_impl._M_start);\n \
    \   }\n\n    else {\n      std::fill_n(__work1.data(), __len, _Tp(0));\n     \
    \ std::fill_n(__work2.data(), __len, _Tp(0));\n\n      for (size_type __i = 0;\
    \ __i < __n; ++__i)\n        __work1[__i].real(vec::_M_impl._M_start[__i]);\n\n\
    \      for (size_type __i = 0; __i < __m; ++__i)\n        __work1[__i].imag(__x._M_impl._M_start[__i]);\n\
    \n      fft(__work1.data(), __len);\n\n      __work2[0].imag(__work1[0].real()\
    \ * __work1[0].imag());\n\n      for (size_type __b = 1; __b != __len; __b <<=\
    \ 1)\n        for (size_type __i = __b, __j = __b << 1; __j-- != __b; ++__i)\n\
    \          __work2[__i] = (__work1[__i] + conj(__work1[__j])) *\n            \
    \             (__work1[__i] - conj(__work1[__j])) / 4;\n\n      ifft(__work2.data(),\
    \ __len);\n\n      for (size_type __i = 0; __i < __n + __m - 1; ++__i)\n     \
    \   if _CXX17_CONSTEXPR (std::is_floating_point<_Tp>::value)\n          vec::_M_impl._M_start[__i]\
    \ = __work2[__i].imag();\n        else\n          vec::_M_impl._M_start[__i] =\
    \ roundl(__work2[__i].imag());\n    }\n  }\n\n  size_type _divmod_naive(const\
    \ poly& __x) {\n    auto __xfin = __x._M_impl._M_finish;\n    auto __xlen = __x.size();\n\
    \    while (__xfin != __x._M_impl._M_start && *(__xfin - 1) == _Tp(0))\n     \
    \ --__xfin, --__xlen;\n\n    assert(__xlen != 0);\n    _erase_leading_zeros();\n\
    \n    auto __p = vec::_M_impl._M_finish;\n\n    while (size_type(__p - vec::_M_impl._M_start)\
    \ >= __xlen) {\n      --__p;\n\n      auto __src = __xfin;\n      auto __dst =\
    \ __p;\n\n      *__dst /= *--__src;\n      while (__src != __x._M_impl._M_start)\
    \ *--__dst -= *--__src * *__p;\n    }\n\n    return std::min<size_type>(__xlen\
    \ - 1, __p - vec::_M_impl._M_start);\n  }\n\n  void _div_naive(const poly& __x)\
    \ { operator>>=(_divmod_naive(__x)); }\n\n  void _div_doubling(poly&& __x) noexcept\
    \ {\n    _erase_leading_zeros();\n    __x._erase_leading_zeros();\n\n    auto\
    \ __n = vec::_M_impl._M_finish - vec::_M_impl._M_start;\n    auto __m = __x._M_impl._M_finish\
    \ - __x._M_impl._M_start;\n\n    if (__n < __m)\n      vec::clear();\n    else\
    \ {\n      assert(__m != 0);\n\n      std::reverse(__x._M_impl._M_start, __x._M_impl._M_finish);\n\
    \      __x = __x.inv(__n - __m + 1);\n\n      std::reverse(vec::_M_impl._M_start,\
    \ vec::_M_impl._M_finish);\n      vec::_M_erase_at_end(vec::_M_impl._M_finish\
    \ - (__m - 1));\n\n      operator*=(__x).resize(__n - __m + 1);\n      std::reverse(vec::_M_impl._M_start,\
    \ vec::_M_impl._M_finish);\n    }\n  }\n\n public:\n  /**\n   * @return Degree\
    \ of %polynomial. Return -1 if it equals zero.\n   */\n  size_type deg() const\
    \ noexcept { return size() - 1; }\n\n  /**\n   * @param __i Not exceeding the\
    \ degree.\n   * @return Coefficient of x^i.\n   */\n  typename vec::reference\
    \ operator[](size_type __i) noexcept {\n    assert(__i < size());\n    return\
    \ *(vec::_M_impl._M_start + __i);\n  }\n\n  /**\n   * @param __i Not exceeding\
    \ the degree.\n   * @return Coefficient of x^i.\n   */\n  typename vec::const_reference\
    \ operator[](size_type __i) const noexcept {\n    assert(__i < size());\n    return\
    \ *(vec::_M_impl._M_start + __i);\n  }\n\n  /**\n   * @brief Evaluate at given\
    \ point.\n   */\n  _Tp eval(const _Tp& __a) const noexcept {\n    _Tp __v(0),\
    \ __p(1);\n\n    for (auto __i = vec::_M_impl._M_start; __i != vec::_M_impl._M_finish;\n\
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
    \n    delete[] __tree;\n\n    return __result;\n  }\n\n  /**\n   * @brief Multiply\
    \ by x^i.\n   */\n  poly& operator<<=(size_type __i) noexcept {\n    vec::insert(vec::begin(),\
    \ __i, _Tp(0));\n    return *this;\n  }\n\n  /**\n   * @brief Divide by x^i.\n\
    \   */\n  poly& operator>>=(size_type __i) noexcept {\n    vec::_M_erase_at_end(\n\
    \        std::move(vec::_M_impl._M_start + std::min(__i, size()),\n          \
    \        vec::_M_impl._M_finish, vec::_M_impl._M_start));\n\n    return *this;\n\
    \  }\n\n  /**\n   * @brief Multiply by x^i.\n   */\n  poly operator<<(size_type\
    \ __i) const noexcept {\n    return poly(*this).operator<<=(__i);\n  }\n\n  /**\n\
    \   * @brief Divide by x^i.\n   */\n  poly operator>>(size_type __i) const noexcept\
    \ {\n    return poly(*this).operator>>=(__i);\n  }\n\n  poly operator+() const\
    \ noexcept { return *this; }\n\n  poly operator-() const noexcept {\n    poly\
    \ __x = *this;\n    for (auto __i = __x._M_impl._M_start; __i != __x._M_impl._M_finish;\
    \ ++__i)\n      *__i = -*__i;\n    return __x;\n  }\n\n  poly& operator+=(const\
    \ poly& __x) noexcept {\n    if (size() < __x.size()) vec::_M_default_append(__x.size()\
    \ - size());\n\n    for (auto __i = vec::_M_impl._M_start, __j = __x._M_impl._M_start;\n\
    \         __j != __x._M_impl._M_finish; ++__i, ++__j)\n      *__i += *__j;\n\n\
    \    _erase_leading_zeros();\n    return *this;\n  }\n\n  poly& operator+=(const\
    \ _Tp& __c) noexcept {\n    if (__c != static_cast<_Tp>(0)) {\n      if (vec::_M_impl._M_start\
    \ == vec::_M_impl._M_finish)\n        vec::emplace_back(__c);\n      else\n  \
    \      *vec::_M_impl._M_start += __c, _erase_leading_zeros();\n    }\n\n    return\
    \ *this;\n  }\n\n  poly& operator-=(const poly& __x) noexcept {\n    if (size()\
    \ < __x.size()) vec::_M_default_append(__x.size() - size());\n\n    for (auto\
    \ __i = vec::_M_impl._M_start, __j = __x._M_impl._M_start;\n         __j != __x._M_impl._M_finish;\
    \ ++__i, ++__j)\n      *__i -= *__j;\n\n    _erase_leading_zeros();\n    return\
    \ *this;\n  }\n\n  poly& operator-=(const _Tp& __c) noexcept {\n    if (__c !=\
    \ static_cast<_Tp>(0)) {\n      if (vec::_M_impl._M_start == vec::_M_impl._M_finish)\n\
    \        vec::emplace_back(-__c);\n      else\n        *vec::_M_impl._M_start\
    \ -= __c, _erase_leading_zeros();\n    }\n\n    return *this;\n  }\n\n  poly&\
    \ operator*=(const poly& __x) noexcept {\n    if (this == std::addressof(__x))\
    \  // with itself\n      return operator*=(poly(__x));\n\n    std::min(size(),\
    \ __x.size()) > _Conv_threshold ? _conv_dft(__x)\n                           \
    \                        : _conv_naive(__x);\n\n    return *this;\n  }\n\n  poly&\
    \ operator*=(poly&& __x) noexcept {\n    if (this == std::addressof(__x))  //\
    \ with itself\n      return operator*=(poly(__x));\n\n    std::min(size(), __x.size())\
    \ > _Conv_threshold\n        ? _conv_dft(std::move(__x))\n        : _conv_naive(std::move(__x));\n\
    \n    return *this;\n  }\n\n  poly& operator*=(const _Tp& __c) noexcept {\n  \
    \  if (__c == static_cast<_Tp>(0))\n      vec::_M_erase_at_end(vec::_M_impl._M_start);\n\
    \    else\n      for (auto __i = vec::_M_impl._M_start; __i != vec::_M_impl._M_finish;\n\
    \           ++__i)\n        *__i *= __c;\n\n    return *this;\n  }\n\n  poly&\
    \ operator/=(const _Tp& __c) noexcept {\n    assert(__c != static_cast<_Tp>(0));\n\
    \n    for (auto __i = vec::_M_impl._M_start; __i != vec::_M_impl._M_finish; ++__i)\n\
    \      *__i /= __c;\n\n    return *this;\n  }\n\n  poly pow(size_type __e) const\
    \ noexcept {\n    if (vec::empty()) return *this;\n\n    if (!__e) return {1};\n\
    \n    if (size() == 1) {\n      _Tp __x = vec::front(), __y = 1;\n      for (auto\
    \ __i = __e; __i; __i >>= 1, __x *= __x)\n        if (__i & 1) __y *= __x;\n \
    \     return {__y};\n    }\n\n    size_type __deg = (size() - 1) * __e;\n    assert(__deg\
    \ > 0);\n\n    poly __p(1 << (32 - __builtin_clz(__deg)));\n    std::copy(vec::_M_impl._M_start,\
    \ vec::_M_impl._M_finish,\n              __p._M_impl._M_start);\n\n    fft(__p._M_impl._M_start,\
    \ __p._M_impl._M_finish);\n\n    for (auto&& __x : __p) {\n      _Tp __y = 1;\n\
    \      for (auto __i = __e; __i; __i >>= 1, __x *= __x)\n        if (__i & 1)\
    \ __y *= __x;\n      __x = __y;\n    }\n\n    ifft(__p._M_impl._M_start, __p._M_impl._M_finish);\n\
    \n    __p.resize(__deg + 1);\n    return __p;\n  }\n\n  poly rev() const noexcept\
    \ { return rev(size()); }\n\n  poly rev(size_type __n) const noexcept {\n    poly\
    \ __r(__n);\n\n    auto __src = vec::_M_impl._M_start;\n    auto __dst = __r._M_impl._M_finish;\n\
    \    for (size_type __i = std::min(__n, size()); __i; --__i) *--__dst = *__src++;\n\
    \n    return __r;\n  }\n\n  poly inv() const noexcept { return inv(size()); }\n\
    \n  /**\n   * @brief Multiplicative inverse modulo x^n.\n   *\n   * @param __n\
    \ Degree of modulus\n   * @return\n   */\n  poly inv(size_type __n) const noexcept\
    \ {\n    if (!__n) return {};\n    assert(*vec::_M_impl._M_start != _Tp(0));\n\
    \n    size_type __len = 1;\n    while (__len < __n) __len <<= 1;\n\n    poly __y(__len);\n\
    \    auto __xp = new _Tp[__len], __yp = __y._M_impl._M_start,\n         __zp =\
    \ new _Tp[__len];\n\n    *__yp = _Tp(1) / *vec::_M_impl._M_start;\n\n    for (size_type\
    \ __i = 1; __i != __len; __i <<= 1) {\n      std::fill(std::copy_n(__yp, __i,\
    \ __zp), __zp + (__i << 1), _Tp(0));\n\n      _dft(__zp, __zp + (__i << 1));\n\
    \n      std::fill(\n          std::copy_n(vec::_M_impl._M_start, std::min(__i\
    \ << 1, size()), __xp),\n          __xp + (__i << 1), _Tp(0));\n\n      _dft(__xp,\
    \ __xp + (__i << 1));\n\n      for (size_type __j = 0; __j != (__i << 1); ++__j)\
    \ __xp[__j] *= -__zp[__j];\n\n      _idft(__xp, __xp + (__i << 1));\n\n      std::fill(std::move(__xp\
    \ + __i, __xp + (__i << 1), __xp),\n                __xp + (__i << 1), _Tp(0));\n\
    \n      _dft(__xp, __xp + (__i << 1));\n\n      for (size_type __j = 0; __j !=\
    \ (__i << 1); ++__j)\n        __xp[__j] *= static_cast<_Tp&&>(__zp[__j]);\n\n\
    \      _idft(__xp, __xp + (__i << 1));\n\n      std::move(__xp, __xp + __i, __yp\
    \ + __i);\n    }\n\n    delete[] __xp;\n    delete[] __zp;\n\n    __y._M_erase_at_end(__yp\
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
    \ __int;\n  }\n\n  /**\n   * @brief\n   *\n   * @param __a\n   * @return f(x +\
    \ a)\n   */\n  poly shift(const _Tp& __a) const noexcept {\n    size_type __n\
    \ = size();\n    poly __s(*this), __e(__n);\n    _Tp __cs(1), __ce(1);\n\n   \
    \ for (size_type __i{0}; __i != __n;\n         __cs *= _Tp(++__i), __ce *= __a\
    \ / _Tp(__i))\n      __s[__i] *= __cs, __e[__n - 1 - __i] = __ce;\n\n    __s *=\
    \ std::move(__e);\n    __ce = 1;\n\n    for (size_type __i{0}; __i != __n; __ce\
    \ /= _Tp(++__i))\n      __e[__i] = __s[__n - 1 + __i] * __ce;\n\n    return __e;\n\
    \  }\n};\n\ntemplate <class _Tp, size_t _C>\nstd::vector<typename polynomial<_Tp,\
    \ _C>::field> polynomial<_Tp, _C>::__work1;\n\ntemplate <class _Tp, size_t _C>\n\
    std::vector<typename polynomial<_Tp, _C>::field> polynomial<_Tp, _C>::__work2;\n\
    \n/**\n * @brief Generating function of the sum of k-th powers of the first n\n\
    \ * non-negative integers. O(d \\\\log d) time in modulo x^d.\n *\n * @return\
    \ \\\\sum_{k=0}^{d-1} x^k \\\\sum_{i=0}^{n-1} i^k.\n */\ntemplate <class _Tp>\
    \ polynomial<_Tp> power_sum(_Tp __n, std::size_t __d) {\n  if (!__d) return {};\n\
    \n  polynomial<_Tp> __f(__d), __e(__d);\n  __f[0] = __n;\n  for (std::size_t __i\
    \ = 1; __i != __d; ++__i) __f[__i] = __f[__i - 1] * __n;\n\n  _Tp __c{1};\n  for\
    \ (std::size_t __i = 0; __i != __d; ++__i)\n    __c /= __i + 1, __f[__i] *= __c,\
    \ __e[__i] = __c;\n\n  (__f *= __e.inv(__d)).resize(__d);\n\n  __c = 1;\n  for\
    \ (std::size_t __i = 0; __i != __d; __c *= ++__i) __f[__i] *= __c;\n  return __f;\n\
    }\n\n}  // namespace workspace\n#line 11 \"src/algebra/berlekamp_massey.hpp\"\n\
    \nnamespace workspace {\n\ntemplate <class _Iterator>\nauto Berlekamp_Massey(_Iterator\
    \ __first, _Iterator __last) noexcept {\n  using value_type = typename std::iterator_traits<_Iterator>::value_type;\n\
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
  - src/algebra/fft.hpp
  - src/algebra/complex.hpp
  - src/number_theory/ext_gcd.hpp
  - src/utils/sfinae.hpp
  - src/number_theory/primitive_root.hpp
  isVerificationFile: false
  path: src/algebra/berlekamp_massey.hpp
  requiredBy: []
  timestamp: '2022-04-06 15:02:09+09:00'
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
