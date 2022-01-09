---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/algebra/convolution/bitand.hpp
    title: Bitwise And Convolution
  - icon: ':heavy_check_mark:'
    path: src/algebra/convolution/bitor.hpp
    title: Bitwise Or Convolution
  - icon: ':heavy_check_mark:'
    path: src/algebra/convolution/zeta.hpp
    title: Fast Zeta Transform
  - icon: ':heavy_check_mark:'
    path: src/algebra/modint.hpp
    title: Modular Arithmetic
  - icon: ':heavy_check_mark:'
    path: src/number_theory/pow_mod.hpp
    title: Modular Exponentiation
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
    PROBLEM: https://judge.yosupo.jp/problem/bitwise_and_convolution
    links:
    - https://judge.yosupo.jp/problem/bitwise_and_convolution
  bundledCode: "#line 1 \"test/library-checker/bitwise_and_convolution.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/bitwise_and_convolution\"\n\n\
    #line 2 \"src/algebra/convolution/bitand.hpp\"\n\n/**\n * @file bitand.hpp\n *\
    \ @brief Bitwise And Convolution\n * @date 2021-01-08\n */\n\n#include <algorithm>\n\
    \n#line 2 \"src/algebra/convolution/bitor.hpp\"\n\n/**\n * @file bitor.hpp\n *\
    \ @brief Bitwise Or Convolution\n * @date 2021-01-08\n */\n\n#line 2 \"src/algebra/convolution/zeta.hpp\"\
    \n\n/**\n * @file zeta.hpp\n * @brief Fast Zeta Transform\n */\n\n#include <cstddef>\n\
    \n#line 2 \"lib/bit\"\n\n#if __cplusplus > 201703L\n\n#include <bit>\n\n#elif\
    \ __cplusplus > 201402L\n\n#ifndef _GLIBCXX_BIT\n#define _GLIBCXX_BIT 1\n\n#include\
    \ <limits>\n#include <type_traits>\n\nnamespace std {\n\ntemplate <typename _Tp>\
    \ constexpr int __countl_zero(_Tp __x) noexcept {\n  constexpr auto _Nd = numeric_limits<_Tp>::digits;\n\
    \n  if (__x == 0) return _Nd;\n\n  constexpr auto _Nd_ull = numeric_limits<unsigned\
    \ long long>::digits;\n  constexpr auto _Nd_ul = numeric_limits<unsigned long>::digits;\n\
    \  constexpr auto _Nd_u = numeric_limits<unsigned>::digits;\n\n  if _GLIBCXX17_CONSTEXPR\
    \ (_Nd <= _Nd_u) {\n    constexpr int __diff = _Nd_u - _Nd;\n    return __builtin_clz(__x)\
    \ - __diff;\n  } else if _GLIBCXX17_CONSTEXPR (_Nd <= _Nd_ul) {\n    constexpr\
    \ int __diff = _Nd_ul - _Nd;\n    return __builtin_clzl(__x) - __diff;\n  } else\
    \ if _GLIBCXX17_CONSTEXPR (_Nd <= _Nd_ull) {\n    constexpr int __diff = _Nd_ull\
    \ - _Nd;\n    return __builtin_clzll(__x) - __diff;\n  } else  // (_Nd > _Nd_ull)\n\
    \  {\n    static_assert(_Nd <= (2 * _Nd_ull),\n                  \"Maximum supported\
    \ integer size is 128-bit\");\n\n    unsigned long long __high = __x >> _Nd_ull;\n\
    \    if (__high != 0) {\n      constexpr int __diff = (2 * _Nd_ull) - _Nd;\n \
    \     return __builtin_clzll(__high) - __diff;\n    }\n    constexpr auto __max_ull\
    \ = numeric_limits<unsigned long long>::max();\n    unsigned long long __low =\
    \ __x & __max_ull;\n    return (_Nd - _Nd_ull) + __builtin_clzll(__low);\n  }\n\
    }\n\ntemplate <typename _Tp> constexpr int __countr_zero(_Tp __x) noexcept {\n\
    \  constexpr auto _Nd = numeric_limits<_Tp>::digits;\n\n  if (__x == 0) return\
    \ _Nd;\n\n  constexpr auto _Nd_ull = numeric_limits<unsigned long long>::digits;\n\
    \  constexpr auto _Nd_ul = numeric_limits<unsigned long>::digits;\n  constexpr\
    \ auto _Nd_u = numeric_limits<unsigned>::digits;\n\n  if _GLIBCXX17_CONSTEXPR\
    \ (_Nd <= _Nd_u)\n    return __builtin_ctz(__x);\n  else if _GLIBCXX17_CONSTEXPR\
    \ (_Nd <= _Nd_ul)\n    return __builtin_ctzl(__x);\n  else if _GLIBCXX17_CONSTEXPR\
    \ (_Nd <= _Nd_ull)\n    return __builtin_ctzll(__x);\n  else  // (_Nd > _Nd_ull)\n\
    \  {\n    static_assert(_Nd <= (2 * _Nd_ull),\n                  \"Maximum supported\
    \ integer size is 128-bit\");\n\n    constexpr auto __max_ull = numeric_limits<unsigned\
    \ long long>::max();\n    unsigned long long __low = __x & __max_ull;\n    if\
    \ (__low != 0) return __builtin_ctzll(__low);\n    unsigned long long __high =\
    \ __x >> _Nd_ull;\n    return __builtin_ctzll(__high) + _Nd_ull;\n  }\n}\n\ntemplate\
    \ <typename _Tp> constexpr int __popcount(_Tp __x) noexcept {\n  constexpr auto\
    \ _Nd = numeric_limits<_Tp>::digits;\n\n  if (__x == 0) return 0;\n\n  constexpr\
    \ auto _Nd_ull = numeric_limits<unsigned long long>::digits;\n  constexpr auto\
    \ _Nd_ul = numeric_limits<unsigned long>::digits;\n  constexpr auto _Nd_u = numeric_limits<unsigned>::digits;\n\
    \n  if _GLIBCXX17_CONSTEXPR (_Nd <= _Nd_u)\n    return __builtin_popcount(__x);\n\
    \  else if _GLIBCXX17_CONSTEXPR (_Nd <= _Nd_ul)\n    return __builtin_popcountl(__x);\n\
    \  else if _GLIBCXX17_CONSTEXPR (_Nd <= _Nd_ull)\n    return __builtin_popcountll(__x);\n\
    \  else  // (_Nd > _Nd_ull)\n  {\n    static_assert(_Nd <= (2 * _Nd_ull),\n  \
    \                \"Maximum supported integer size is 128-bit\");\n\n    constexpr\
    \ auto __max_ull = numeric_limits<unsigned long long>::max();\n    unsigned long\
    \ long __low = __x & __max_ull;\n    unsigned long long __high = __x >> _Nd_ull;\n\
    \    return __builtin_popcountll(__low) + __builtin_popcountll(__high);\n  }\n\
    }\n\ntemplate <typename _Tp> constexpr _Tp __bit_ceil(_Tp __x) noexcept {\n  constexpr\
    \ auto _Nd = numeric_limits<_Tp>::digits;\n  if (__x == 0 || __x == 1) return\
    \ 1;\n  auto __shift_exponent = _Nd - __countl_zero((_Tp)(__x - 1u));\n#ifdef\
    \ _GLIBCXX_HAVE_BUILTIN_IS_CONSTANT_EVALUATED\n  if (!__builtin_is_constant_evaluated())\
    \ {\n    __glibcxx_assert(__shift_exponent != numeric_limits<_Tp>::digits);\n\
    \  }\n#endif\n  using __promoted_type = decltype(__x << 1);\n  if _GLIBCXX17_CONSTEXPR\
    \ (!is_same<__promoted_type, _Tp>::value) {\n    const int __extra_exp = sizeof(__promoted_type)\
    \ / sizeof(_Tp) / 2;\n    __shift_exponent |= (__shift_exponent & _Nd) << __extra_exp;\n\
    \  }\n  return (_Tp)1u << __shift_exponent;\n}\n\ntemplate <typename _Tp> constexpr\
    \ _Tp __bit_floor(_Tp __x) noexcept {\n  constexpr auto _Nd = numeric_limits<_Tp>::digits;\n\
    \  if (__x == 0) return 0;\n  return (_Tp)1u << (_Nd - __countl_zero((_Tp)(__x\
    \ >> 1)));\n}\n\ntemplate <typename _Tp> constexpr _Tp __bit_width(_Tp __x) noexcept\
    \ {\n  constexpr auto _Nd = numeric_limits<_Tp>::digits;\n  return _Nd - __countl_zero(__x);\n\
    }\n\n}  // namespace std\n\n#endif\n\n#endif\n#line 11 \"src/algebra/convolution/zeta.hpp\"\
    \n\nnamespace workspace {\n\n/**\n * @brief Fast zeta transform on a lattice.\n\
    \ * @param f Value list of the function\n * @param n Number of join-irreducible\
    \ elements, bit-width of indices\n * @return Value list of resulting function.\n\
    \ */\ntemplate <class A> A fast_zeta(A f, size_t n) {\n  while (n--)\n    for\
    \ (size_t s = 0; s != std::size(f); ++s)\n      if (s >> n & 1) f[s] += f[s ^\
    \ 1 << n];\n  return f;\n}\n\n/**\n * @brief Fast zeta transform on a lattice.\n\
    \ * @param f Value list of the function\n * @return Value list of resulting function.\n\
    \ */\ntemplate <class A> A fast_zeta(A const &f) {\n  return fast_zeta(f, std::__countr_zero(std::__bit_floor(std::size(f))));\n\
    }\n\n/**\n * @brief Inverse of fast zeta transform.\n * @param f Value list of\
    \ the function\n * @param n Number of join-irreducible elements, bit-width of\
    \ indices\n * @return Value list of resulting function.\n */\ntemplate <class\
    \ A> A fast_mobius(A f, size_t n) {\n  while (n--)\n    for (size_t s = 0; s !=\
    \ std::size(f); ++s)\n      if (s >> n & 1) f[s] -= f[s ^ 1 << n];\n  return f;\n\
    }\n\n/**\n * @brief Inverse of fast zeta transform.\n * @param f Value list of\
    \ the function\n * @return Value list of resulting function.\n */\ntemplate <class\
    \ A> A fast_mobius(A const &f) {\n  return fast_mobius(f, std::__countr_zero(std::__bit_floor(std::size(f))));\n\
    }\n\n}  // namespace workspace\n#line 10 \"src/algebra/convolution/bitor.hpp\"\
    \n\nnamespace workspace {\n\ntemplate <class A> A bitor_conv(A f, A g) {\n  f\
    \ = fast_zeta(f);\n  g = fast_zeta(g);\n  for (size_t i = 0; i != std::__bit_floor(std::size(f));\
    \ ++i) f[i] *= g[i];\n  f = fast_mobius(f);\n  return f;\n}\n\n}  // namespace\
    \ workspace\n#line 12 \"src/algebra/convolution/bitand.hpp\"\n\nnamespace workspace\
    \ {\n\ntemplate <class A> A bitand_conv(A f, A g) {\n  std::reverse(std::begin(f),\
    \ std::end(f));\n  std::reverse(std::begin(g), std::end(g));\n  f = bitor_conv(f,\
    \ g);\n  std::reverse(std::begin(f), std::end(f));\n  return f;\n}\n\n}  // namespace\
    \ workspace\n#line 2 \"src/algebra/modint.hpp\"\n\n/**\n * @file modint.hpp\n\
    \ * @brief Modular Arithmetic\n */\n\n#include <cassert>\n#include <iostream>\n\
    #include <vector>\n\n#line 2 \"src/number_theory/sqrt_mod.hpp\"\n\n/**\n * @file\
    \ sqrt_mod.hpp\n * @brief Tonelli-Shanks Algorithm\n */\n\n#line 2 \"src/number_theory/pow_mod.hpp\"\
    \n\n/**\n * @file mod_pow.hpp\n * @brief Modular Exponentiation\n */\n\n#line\
    \ 9 \"src/number_theory/pow_mod.hpp\"\n\n#line 2 \"src/utils/sfinae.hpp\"\n\n\
    /**\n * @file sfinae.hpp\n * @brief SFINAE\n */\n\n#include <cstdint>\n#include\
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
    \ __a;\n};\n\n}  // namespace workspace\n#line 14 \"src/algebra/modint.hpp\"\n\
    \nnamespace workspace {\n\nnamespace _modint_impl {\n\ntemplate <auto _Mod, unsigned\
    \ _Storage> struct modint {\n  static_assert(is_integral_ext<decltype(_Mod)>::value,\n\
    \                \"_Mod must be integral type.\");\n\n  using mod_type = std::make_signed_t<typename\
    \ std::conditional<\n      0 < _Mod, std::add_const_t<decltype(_Mod)>, decltype(_Mod)>::type>;\n\
    \n  using value_type = std::decay_t<mod_type>;\n\n  using reference = value_type\
    \ &;\n  using const_reference = value_type const &;\n\n  using mul_type = typename\
    \ multiplicable_uint<value_type>::type;\n\n  static mod_type mod;  // Modulus.\n\
    \n  static unsigned storage;\n\n private:\n  template <class _Tp>\n  using modint_if\
    \ = std::enable_if_t<is_integral_ext<_Tp>::value, modint>;\n\n  value_type value\
    \ = 0;  // within [0, mod).\n\n  struct direct_ctor_t {};\n  constexpr static\
    \ direct_ctor_t direct_ctor_tag{};\n\n  // Direct constructor\n  template <class\
    \ _Tp>\n  constexpr modint(_Tp __n, direct_ctor_t) noexcept : value(__n) {}\n\n\
    \ public:\n  constexpr modint() noexcept = default;\n\n  template <class _Tp,\
    \ class = std::enable_if_t<\n                           std::is_convertible<_Tp,\
    \ value_type>::value>>\n  constexpr modint(_Tp __n) noexcept\n      : value((__n\
    \ %= mod) < _Tp(0) ? static_cast<value_type>(__n) + mod\n                    \
    \                : static_cast<value_type>(__n)) {}\n\n  constexpr modint(bool\
    \ __n) noexcept : value(__n) {}\n\n  constexpr operator reference() noexcept {\
    \ return value; }\n\n  constexpr operator const_reference() const noexcept { return\
    \ value; }\n\n  // unary operators {{\n  constexpr modint operator++(int) noexcept\
    \ {\n    modint __t{*this};\n    operator++();\n    return __t;\n  }\n\n  constexpr\
    \ modint operator--(int) noexcept {\n    modint __t{*this};\n    operator--();\n\
    \    return __t;\n  }\n\n  constexpr modint &operator++() noexcept {\n    if (++value\
    \ == mod) value = 0;\n    return *this;\n  }\n\n  constexpr modint &operator--()\
    \ noexcept {\n    if (!value)\n      value = mod - 1;\n    else\n      --value;\n\
    \    return *this;\n  }\n\n  constexpr modint operator+() const noexcept { return\
    \ *this; }\n\n  constexpr modint operator-() const noexcept {\n    return {value\
    \ ? mod - value : 0, direct_ctor_tag};\n  }\n\n  // }} unary operators\n\n  //\
    \ operator+= {{\n\n  constexpr modint &operator+=(const modint &__x) noexcept\
    \ {\n    if ((value += __x.value) >= mod) value -= mod;\n    return *this;\n \
    \ }\n\n  template <class _Tp> constexpr modint_if<_Tp> &operator+=(_Tp __x) noexcept\
    \ {\n    __x %= mod, value += __x;\n    if (value < 0)\n      value += mod;\n\
    \    else if (value >= mod)\n      value -= mod;\n    return *this;\n  }\n\n \
    \ // }} operator+=\n\n  // operator+ {{\n\n  template <class _Tp>\n  constexpr\
    \ modint_if<_Tp> operator+(_Tp const &__x) const noexcept {\n    return modint{*this}\
    \ += __x;\n  }\n\n  constexpr modint operator+(modint __x) const noexcept { return\
    \ __x += *this; }\n\n  template <class _Tp>\n  constexpr friend modint_if<_Tp>\
    \ operator+(_Tp const &__x,\n                                            modint\
    \ __y) noexcept {\n    return __y += __x;\n  }\n\n  // }} operator+\n\n  // operator-=\
    \ {{\n\n  constexpr modint &operator-=(const modint &__x) noexcept {\n    if ((value\
    \ -= __x.value) < 0) value += mod;\n    return *this;\n  }\n\n  template <class\
    \ _Tp> constexpr modint_if<_Tp> &operator-=(_Tp __x) noexcept {\n    __x %= mod,\
    \ value -= __x;\n    if (value < 0)\n      value += mod;\n    else if (value >=\
    \ mod)\n      value -= mod;\n    return *this;\n  }\n\n  // }} operator-=\n\n\
    \  // operator- {{\n\n  template <class _Tp>\n  constexpr modint_if<_Tp> operator-(_Tp\
    \ const &__x) const noexcept {\n    return modint{*this} -= __x;\n  }\n\n  constexpr\
    \ modint operator-(const modint &__x) const noexcept {\n    return modint{*this}\
    \ -= __x;\n  }\n\n  template <class _Tp>\n  constexpr friend modint_if<_Tp> operator-(_Tp\
    \ __x,\n                                            const modint &__y) noexcept\
    \ {\n    if (((__x -= __y.value) %= mod) < 0) __x += mod;\n    return {__x, direct_ctor_tag};\n\
    \  }\n\n  // }} operator-\n\n  // operator*= {{\n\n  constexpr modint &operator*=(const\
    \ modint &__x) noexcept {\n    value =\n        static_cast<value_type>(value\
    \ * static_cast<mul_type>(__x.value) % mod);\n    return *this;\n  }\n\n  template\
    \ <class _Tp> constexpr modint_if<_Tp> &operator*=(_Tp __x) noexcept {\n    value\
    \ = static_cast<value_type>(\n        value * ((__x %= mod) < 0 ? mul_type(__x\
    \ + mod) : mul_type(__x)) % mod);\n    return *this;\n  }\n\n  // }} operator*=\n\
    \n  // operator* {{\n\n  constexpr modint operator*(const modint &__x) const noexcept\
    \ {\n    return {static_cast<mul_type>(value) * __x.value % mod, direct_ctor_tag};\n\
    \  }\n\n  template <class _Tp>\n  constexpr modint_if<_Tp> operator*(_Tp __x)\
    \ const noexcept {\n    __x %= mod;\n    if (__x < 0) __x += mod;\n    return\
    \ {static_cast<mul_type>(value) * __x % mod, direct_ctor_tag};\n  }\n\n  template\
    \ <class _Tp>\n  constexpr friend modint_if<_Tp> operator*(_Tp __x,\n        \
    \                                    const modint &__y) noexcept {\n    __x %=\
    \ mod;\n    if (__x < 0) __x += mod;\n    return {static_cast<mul_type>(__x) *\
    \ __y.value % mod, direct_ctor_tag};\n  }\n\n  // }} operator*\n\n protected:\n\
    \  static value_type _mem(value_type __x) {\n    static std::vector<value_type>\
    \ __m{0, 1};\n    static value_type __i = (__m.reserve(storage), 1);\n    while\
    \ (__i < __x) {\n      ++__i;\n      __m.emplace_back(mod - mul_type(mod / __i)\
    \ * __m[mod % __i] % mod);\n    }\n    return __m[__x];\n  }\n\n  static value_type\
    \ _div(mul_type __r, value_type __x) noexcept {\n    assert(__x != value_type(0));\n\
    \    if (!__r) return 0;\n\n    std::make_signed_t<value_type> __v{};\n    bool\
    \ __neg = __x < 0 ? __x = -__x, true : false;\n\n    if (static_cast<decltype(storage)>(__x)\
    \ < storage)\n      __v = _mem(__x);\n    else {\n      value_type __y{mod}, __u{1},\
    \ __t;\n\n      while (__x)\n        __t = __y / __x, __y ^= __x ^= (__y -= __t\
    \ * __x) ^= __x,\n        __v ^= __u ^= (__v -= __t * __u) ^= __u;\n\n      if\
    \ (__y < 0) __neg ^= 1;\n    }\n\n    if (__neg)\n      __v = 0 < __v ? mod -\
    \ __v : -__v;\n    else if (__v < 0)\n      __v += mod;\n\n    return __r == mul_type(1)\
    \ ? static_cast<value_type>(__v)\n                              : static_cast<value_type>(__r\
    \ * __v % mod);\n  }\n\n public:\n  static void reserve(unsigned __n) noexcept\
    \ {\n    if (storage < __n) storage = __n;\n  }\n\n  // operator/= {{\n\n  constexpr\
    \ modint &operator/=(const modint &__x) noexcept {\n    if (value) value = _div(value,\
    \ __x.value);\n    return *this;\n  }\n\n  template <class _Tp> constexpr modint_if<_Tp>\
    \ &operator/=(_Tp __x) noexcept {\n    if (value) value = _div(value, __x %= mod);\n\
    \    return *this;\n  }\n\n  // }} operator/=\n\n  // operator/ {{\n\n  constexpr\
    \ modint operator/(const modint &__x) const noexcept {\n    if (!value) return\
    \ {};\n    return {_div(value, __x.value), direct_ctor_tag};\n  }\n\n  template\
    \ <class _Tp>\n  constexpr modint_if<_Tp> operator/(_Tp __x) const noexcept {\n\
    \    if (!value) return {};\n    return {_div(value, __x %= mod), direct_ctor_tag};\n\
    \  }\n\n  template <class _Tp>\n  constexpr friend modint_if<_Tp> operator/(_Tp\
    \ __x,\n                                            const modint &__y) noexcept\
    \ {\n    if (!__x) return {};\n    if ((__x %= mod) < 0) __x += mod;\n    return\
    \ {_div(__x, __y.value), direct_ctor_tag};\n  }\n\n  // }} operator/\n\n  constexpr\
    \ modint inv() const noexcept { return _div(1, value); }\n\n  template <class\
    \ _Tp> constexpr modint pow(_Tp __e) const noexcept {\n    static_assert(not std::is_floating_point<_Tp>::value);\n\
    \n    modint __r{mod != 1, direct_ctor_tag};\n\n    for (modint __b{__e < _Tp(0)\
    \ ? __e = -__e, _div(1, value) : value,\n                                   direct_ctor_tag};\n\
    \         __e; __e /= 2, __b *= __b)\n      if (__e % 2) __r *= __b;\n\n    return\
    \ __r;\n  }\n\n  template <class _Tp>\n  constexpr friend modint pow(modint __b,\
    \ _Tp __e) noexcept {\n    static_assert(not std::is_floating_point<_Tp>::value);\n\
    \n    if (__e < _Tp(0)) {\n      __e = -__e;\n      __b.value = _div(1, __b.value);\n\
    \    }\n\n    modint __r{mod != 1, direct_ctor_tag};\n\n    for (; __e; __e /=\
    \ 2, __b *= __b)\n      if (__e % 2) __r *= __b;\n\n    return __r;\n  }\n\n \
    \ constexpr modint sqrt() const noexcept {\n    return {sqrt_mod(value, mod),\
    \ direct_ctor_tag};\n  }\n\n  friend constexpr modint sqrt(const modint &__x)\
    \ noexcept {\n    return {sqrt_mod(__x.value, mod), direct_ctor_tag};\n  }\n\n\
    \  friend std::istream &operator>>(std::istream &__is, modint &__x) noexcept {\n\
    \    std::string __s;\n    __is >> __s;\n    bool __neg = false;\n    if (__s.front()\
    \ == '-') {\n      __neg = true;\n      __s.erase(__s.begin());\n    }\n    __x\
    \ = 0;\n    for (char __c : __s) __x = __x * 10 + (__c - '0');\n    if (__neg)\
    \ __x = -__x;\n    return __is;\n  }\n};\n\ntemplate <auto _Mod, unsigned _Storage>\n\
    typename modint<_Mod, _Storage>::mod_type modint<_Mod, _Storage>::mod =\n    _Mod\
    \ > 0 ? _Mod : 0;\n\ntemplate <auto _Mod, unsigned _Storage>\nunsigned modint<_Mod,\
    \ _Storage>::storage = _Storage;\n\n}  // namespace _modint_impl\n\nconstexpr\
    \ unsigned _modint_default_storage = 1 << 24;\n\ntemplate <auto _Mod, unsigned\
    \ _Storage = _modint_default_storage,\n          typename = std::enable_if_t<(_Mod\
    \ > 0)>>\nusing modint = _modint_impl::modint<_Mod, _Storage>;\n\ntemplate <unsigned\
    \ _Id = 0, unsigned _Storage = _modint_default_storage>\nusing runtime_modint\
    \ = _modint_impl::modint<-(signed)_Id, _Storage>;\n\ntemplate <unsigned _Id =\
    \ 0, unsigned _Storage = _modint_default_storage>\nusing runtime_modint64 = _modint_impl::modint<-(int_least64_t)_Id,\
    \ _Storage>;\n\n}  // namespace workspace\n#line 2 \"src/utils/io/istream.hpp\"\
    \n\n/**\n * @file istream.hpp\n * @brief Input Stream\n */\n\n#include <cxxabi.h>\n\
    \n#line 12 \"src/utils/io/istream.hpp\"\n#include <tuple>\n\n#line 2 \"lib/cxx17\"\
    \n\n#line 2 \"lib/cxx14\"\n\n#ifndef _CXX14_CONSTEXPR\n#if __cplusplus >= 201402L\n\
    #define _CXX14_CONSTEXPR constexpr\n#else\n#define _CXX14_CONSTEXPR\n#endif\n\
    #endif\n#line 4 \"lib/cxx17\"\n\n#ifndef _CXX17_CONSTEXPR\n#if __cplusplus >=\
    \ 201703L\n#define _CXX17_CONSTEXPR constexpr\n#else\n#define _CXX17_CONSTEXPR\n\
    #endif\n#endif\n\n#ifndef _CXX17_STATIC_ASSERT\n#if __cplusplus >= 201703L\n#define\
    \ _CXX17_STATIC_ASSERT static_assert\n#else\n#define _CXX17_STATIC_ASSERT assert\n\
    #endif\n#endif\n\n#line 22 \"lib/cxx17\"\n\n#if __cplusplus < 201703L\n\nnamespace\
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
    \n#include <variant>\n\n#endif\n#line 16 \"src/utils/io/istream.hpp\"\n\nnamespace\
    \ workspace {\n\nnamespace _istream_impl {\n\ntemplate <class _Tp, typename =\
    \ void> struct helper {\n  helper(std::istream &__is, _Tp &__x) {\n    if _CXX17_CONSTEXPR\
    \ (has_begin<_Tp &>::value)\n      for (auto &&__e : __x) helper<std::decay_t<decltype(__e)>>(__is,\
    \ __e);\n    else\n      static_assert(has_begin<_Tp>::value, \"istream unsupported\
    \ type.\");\n  }\n};\n\ntemplate <class _Tp>\nstruct helper<_Tp, std::__void_t<decltype(std::declval<std::istream\
    \ &>() >>\n                                          std::declval<_Tp &>())>>\
    \ {\n  helper(std::istream &__is, _Tp &__x) { __is >> __x; }\n};\n\n#ifdef __SIZEOF_INT128__\n\
    \ntemplate <> struct helper<__uint128_t, void> {\n  helper(std::istream &__is,\
    \ __uint128_t &__x) {\n    std::string __s;\n    __is >> __s;\n    bool __neg\
    \ = false;\n    if (__s.front() == '-') __neg = true, __s.erase(__s.begin());\n\
    \    __x = 0;\n    for (char __d : __s) {\n      __x *= 10;\n      __d -= '0';\n\
    \      if (__neg)\n        __x -= __d;\n      else\n        __x += __d;\n    }\n\
    \  }\n};\n\ntemplate <> struct helper<__int128_t, void> {\n  helper(std::istream\
    \ &__is, __int128_t &__x) {\n    std::string __s;\n    __is >> __s;\n    bool\
    \ __neg = false;\n    if (__s.front() == '-') __neg = true, __s.erase(__s.begin());\n\
    \    __x = 0;\n    for (char __d : __s) {\n      __x *= 10;\n      __d -= '0';\n\
    \      if (__neg)\n        __x -= __d;\n      else\n        __x += __d;\n    }\n\
    \  }\n};\n\n#endif  // INT128\n\ntemplate <class _T1, class _T2> struct helper<std::pair<_T1,\
    \ _T2>> {\n  helper(std::istream &__is, std::pair<_T1, _T2> &__x) {\n    helper<_T1>(__is,\
    \ __x.first), helper<_T2>(__is, __x.second);\n  }\n};\n\ntemplate <class... _Tp>\
    \ struct helper<std::tuple<_Tp...>> {\n  helper(std::istream &__is, std::tuple<_Tp...>\
    \ &__x) { iterate(__is, __x); }\n\n private:\n  template <class _Tuple, size_t\
    \ _Nm = 0>\n  void iterate(std::istream &__is, _Tuple &__x) {\n    if _CXX17_CONSTEXPR\
    \ (_Nm != std::tuple_size<_Tuple>::value) {\n      helper<typename std::tuple_element<_Nm,\
    \ _Tuple>::type>(\n          __is, std::get<_Nm>(__x)),\n          iterate<_Tuple,\
    \ _Nm + 1>(__is, __x);\n    }\n  }\n};\n\n}  // namespace _istream_impl\n\n/**\n\
    \ * @brief A wrapper class for std::istream.\n */\nclass istream : public std::istream\
    \ {\n public:\n  /**\n   * @brief Wrapped operator.\n   */\n  template <typename\
    \ _Tp> istream &operator>>(_Tp &__x) {\n    _istream_impl::helper<_Tp>(*this,\
    \ __x);\n    if (std::istream::fail()) {\n      static auto once = atexit([] {\n\
    \        std::cerr << \"\\n\\033[43m\\033[30mwarning: failed to read \\'\"\n \
    \                 << abi::__cxa_demangle(typeid(_Tp).name(), 0, 0, 0)\n      \
    \            << \"\\'.\\033[0m\\n\\n\";\n      });\n      assert(!once);\n   \
    \ }\n    return *this;\n  }\n};\n\ndecltype(auto) cin = static_cast<istream &>(std::cin);\n\
    \n}  // namespace workspace\n#line 2 \"src/utils/io/ostream.hpp\"\n\n/**\n * @file\
    \ ostream.hpp\n * @brief Output Stream\n */\n\n#line 9 \"src/utils/io/ostream.hpp\"\
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
    typename std::enable_if<\n    !std::is_convertible<std::decay_t<_Container>, std::string>::value\
    \ &&\n        !std::is_convertible<std::decay_t<_Container>, char *>::value,\n\
    \    ostream_ref<_Os>>::type\noperator<<(_Os &__os, const _Container &__cont)\
    \ {\n  bool __h = true;\n  for (auto &&__e : __cont) __h ? __h = 0 : (__os <<\
    \ ' ', 0), __os << __e;\n  return __os;\n}\n\n#ifdef __SIZEOF_INT128__\n\n/**\n\
    \ * @brief Stream insertion operator for __int128_t.\n *\n * @param __os Output\
    \ Stream\n * @param __x 128-bit integer\n * @return Reference to __os.\n */\n\
    template <class _Os> ostream_ref<_Os> operator<<(_Os &__os, __int128_t __x) {\n\
    \  if (!__x) return __os << '0';\n  if (__x < 0) __os << '-';\n  char __s[40],\
    \ *__p = __s;\n  while (__x) {\n    auto __d = __x % 10;\n    *__p++ = '0' + (__x\
    \ < 0 ? -__d : __d);\n    __x /= 10;\n  }\n  *__p = 0;\n  for (char *__t = __s;\
    \ __t < --__p; ++__t) *__t ^= *__p ^= *__t ^= *__p;\n  return __os << __s;\n}\n\
    \n/**\n * @brief Stream insertion operator for __uint128_t.\n *\n * @param __os\
    \ Output Stream\n * @param __x 128-bit unsigned integer\n * @return Reference\
    \ to __os.\n */\ntemplate <class _Os> ostream_ref<_Os> operator<<(_Os &__os, __uint128_t\
    \ __x) {\n  if (!__x) return __os << '0';\n  char __s[40], *__p = __s;\n  while\
    \ (__x) *__p++ = '0' + __x % 10, __x /= 10;\n  *__p = 0;\n  for (char *__t = __s;\
    \ __t < --__p; ++__t) *__t ^= *__p ^= *__t ^= *__p;\n  return __os << __s;\n}\n\
    \n#endif\n\n}  // namespace workspace\n#line 7 \"test/library-checker/bitwise_and_convolution.test.cpp\"\
    \n\nint main() {\n  using namespace workspace;\n  using mint = modint<998244353>;\n\
    \  size_t n;\n  cin >> n;\n  std::vector<mint> a(1 << n), b(1 << n);\n  cin >>\
    \ a >> b;\n  std::cout << bitand_conv(a, b) << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/bitwise_and_convolution\"\
    \n\n#include \"src/algebra/convolution/bitand.hpp\"\n#include \"src/algebra/modint.hpp\"\
    \n#include \"src/utils/io/istream.hpp\"\n#include \"src/utils/io/ostream.hpp\"\
    \n\nint main() {\n  using namespace workspace;\n  using mint = modint<998244353>;\n\
    \  size_t n;\n  cin >> n;\n  std::vector<mint> a(1 << n), b(1 << n);\n  cin >>\
    \ a >> b;\n  std::cout << bitand_conv(a, b) << \"\\n\";\n}\n"
  dependsOn:
  - src/algebra/convolution/bitand.hpp
  - src/algebra/convolution/bitor.hpp
  - src/algebra/convolution/zeta.hpp
  - src/algebra/modint.hpp
  - src/number_theory/sqrt_mod.hpp
  - src/number_theory/pow_mod.hpp
  - src/utils/sfinae.hpp
  - src/utils/io/istream.hpp
  - src/utils/io/ostream.hpp
  isVerificationFile: true
  path: test/library-checker/bitwise_and_convolution.test.cpp
  requiredBy: []
  timestamp: '2022-01-09 13:28:19+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/library-checker/bitwise_and_convolution.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/bitwise_and_convolution.test.cpp
- /verify/test/library-checker/bitwise_and_convolution.test.cpp.html
title: test/library-checker/bitwise_and_convolution.test.cpp
---
