---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/algebra/modint.hpp
    title: Modular Arithmetic
  - icon: ':heavy_check_mark:'
    path: src/combinatorics/binomial.hpp
    title: Binomial Coefficient
  - icon: ':heavy_check_mark:'
    path: src/combinatorics/factorial.hpp
    title: Factorial
  - icon: ':heavy_check_mark:'
    path: src/number_theory/pow_mod.hpp
    title: Modular Exponentiation
  - icon: ':heavy_check_mark:'
    path: src/number_theory/sqrt_mod.hpp
    title: Tonelli-Shanks Algorithm
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
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/DPL_5_D
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/DPL_5_D
  bundledCode: "#line 1 \"test/aizu-online-judge/DPL_5_D.test.cpp\"\n#define PROBLEM\
    \ \"https://onlinejudge.u-aizu.ac.jp/problems/DPL_5_D\"\n\n#include <cstdio>\n\
    \n#line 2 \"src/algebra/modint.hpp\"\n\n/**\n * @file modint.hpp\n *\n * @brief\
    \ Modular Arithmetic\n */\n\n#include <cassert>\n#include <iostream>\n#include\
    \ <vector>\n\n#line 2 \"src/number_theory/sqrt_mod.hpp\"\n\n/**\n * @file sqrt_mod.hpp\n\
    \ * @brief Tonelli-Shanks Algorithm\n */\n\n#line 2 \"src/number_theory/pow_mod.hpp\"\
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
    \ __a;\n};\n\n}  // namespace workspace\n#line 15 \"src/algebra/modint.hpp\"\n\
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
    \ %= mod) < 0 ? value_type(__n + mod) : value_type(__n)) {}\n\n  constexpr modint(bool\
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
    \ _Tp> constexpr modint_if<_Tp> pow(_Tp __e) const noexcept {\n    modint __r{mod\
    \ != 1, direct_ctor_tag};\n\n    for (modint __b{__e < 0 ? __e = -__e, _div(1,\
    \ value) : value,\n                              direct_ctor_tag};\n         __e;\
    \ __e >>= 1, __b *= __b)\n      if (__e & 1) __r *= __b;\n\n    return __r;\n\
    \  }\n\n  template <class _Tp>\n  constexpr friend modint_if<_Tp> pow(modint __b,\
    \ _Tp __e) noexcept {\n    if (__e < 0) {\n      __e = -__e;\n      __b.value\
    \ = _div(1, __b.value);\n    }\n\n    modint __r{mod != 1, direct_ctor_tag};\n\
    \n    for (; __e; __e >>= 1, __b *= __b)\n      if (__e & 1) __r *= __b;\n\n \
    \   return __r;\n  }\n\n  constexpr modint sqrt() const noexcept {\n    return\
    \ {sqrt_mod(value, mod), direct_ctor_tag};\n  }\n\n  friend constexpr modint sqrt(const\
    \ modint &__x) noexcept {\n    return {sqrt_mod(__x.value, mod), direct_ctor_tag};\n\
    \  }\n\n  friend std::istream &operator>>(std::istream &__is, modint &__x) noexcept\
    \ {\n    std::string __s;\n    __is >> __s;\n    bool __neg = false;\n    if (__s.front()\
    \ == '-') {\n      __neg = true;\n      __s.erase(__s.begin());\n    }\n    __x\
    \ = 0;\n    for (char __c : __s) __x = __x * 10 + (__c - '0');\n    if (__neg)\
    \ __x = -__x;\n    return __is;\n  }\n};\n\ntemplate <auto _Mod, unsigned _Storage>\n\
    typename modint<_Mod, _Storage>::mod_type modint<_Mod, _Storage>::mod =\n    _Mod\
    \ > 0 ? _Mod : 0;\n\ntemplate <auto _Mod, unsigned _Storage>\nunsigned modint<_Mod,\
    \ _Storage>::storage = _Storage;\n\n}  // namespace _modint_impl\n\ntemplate <auto\
    \ _Mod, unsigned _Storage = 0,\n          typename = std::enable_if_t<(_Mod >\
    \ 0)>>\nusing modint = _modint_impl::modint<_Mod, _Storage>;\n\ntemplate <unsigned\
    \ _Id = 0, unsigned _Storage = 0>\nusing runtime_modint = _modint_impl::modint<-(signed)_Id,\
    \ 0>;\n\ntemplate <unsigned _Id = 0, unsigned _Storage = 0>\nusing runtime_modint64\
    \ = _modint_impl::modint<-(int_least64_t)_Id, 0>;\n\n}  // namespace workspace\n\
    #line 2 \"src/combinatorics/binomial.hpp\"\n\n/**\n * @file binomial.hpp\n * @brief\
    \ Binomial Coefficient\n */\n\n#line 9 \"src/combinatorics/binomial.hpp\"\n\n\
    #line 2 \"src/combinatorics/factorial.hpp\"\n\n/**\n * @file factorial.hpp\n *\
    \ @brief Factorial\n */\n\n#line 9 \"src/combinatorics/factorial.hpp\"\n\nnamespace\
    \ workspace {\n\n// Factorial.\ntemplate <class _Tp, class _X = int_least64_t>\
    \ _Tp factorial(_X __x) noexcept {\n  if (__x < 0) return 0;\n  static std::vector<_Tp>\
    \ __t{1};\n  static size_t __i = (__t.reserve(0x1000000), 0);\n  while (__i <\
    \ size_t(__x)) __t.emplace_back(__t.back() * _Tp(++__i));\n  return __t[__x];\n\
    }\n\n// Inverse of factorial.\ntemplate <class _Tp, class _X = int_least64_t>\n\
    _Tp inverse_factorial(_X __x) noexcept {\n  if (__x < 0) return 0;\n  static std::vector<_Tp>\
    \ __t{1};\n  static size_t __i = (__t.reserve(0x1000000), 0);\n  while (__i <\
    \ size_t(__x)) __t.emplace_back(__t.back() / _Tp(++__i));\n  return __t[__x];\n\
    }\n\n}  // namespace workspace\n#line 11 \"src/combinatorics/binomial.hpp\"\n\n\
    namespace workspace {\n\nnamespace _binom_impl {\n\nstruct _binom_table {\n  constexpr\
    \ static int size = 132;\n  __uint128_t __b[size][size]{1};\n\n  constexpr _binom_table()\
    \ noexcept {\n    for (int __i = 1; __i != size; ++__i)\n      for (int __j =\
    \ 0; __j != __i; ++__j)\n        __b[__i][__j] += __b[__i - 1][__j],\n       \
    \     __b[__i][__j + 1] += __b[__i - 1][__j];\n  }\n\n  constexpr auto operator()(int\
    \ __x, int __y) const noexcept {\n    return __x < 0 || __x < __y ? 0 : (assert(__x\
    \ < size), __b[__x][__y]);\n  }\n};\n\nconstexpr _binom_table table;\n\n}  //\
    \ namespace _binom_impl\n\n/**\n * @brief Binomial coefficient for integer args.\
    \ Be careful with overflow.\n */\ntemplate <class _Tp, class _X = int_fast64_t,\
    \ class _Y = int_fast64_t>\nconstexpr _Tp binomial(_X __x, _Y __y) {\n  if constexpr\
    \ (is_integral_ext<_Tp>::value)\n    return _binom_impl::table(__x, __y);\n\n\
    \  if (__y < 0 || __x < __y) return 0;\n\n  return factorial<_Tp>(__x) * inverse_factorial<_Tp>(__y)\
    \ *\n         inverse_factorial<_Tp>(__x - __y);\n}\n\n/**\n * @brief Catalan\
    \ number.\n */\ntemplate <class _Tp, class _X = int_fast64_t> constexpr _Tp catalan(_X\
    \ __x) {\n  return __x < 0\n             ? _Tp(0)\n             : binomial<_Tp>(__x\
    \ << 1, __x) - binomial<_Tp>(__x << 1, __x + 1);\n}\n\n}  // namespace workspace\n\
    #line 7 \"test/aizu-online-judge/DPL_5_D.test.cpp\"\n\nint main() {\n  using namespace\
    \ workspace;\n  int n, k;\n  scanf(\"%d%d\", &n, &k);\n  printf(\"%d\\n\", binomial<modint<1000000007>>(n\
    \ + k - 1, n));\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/DPL_5_D\"\n\n\
    #include <cstdio>\n\n#include \"src/algebra/modint.hpp\"\n#include \"src/combinatorics/binomial.hpp\"\
    \n\nint main() {\n  using namespace workspace;\n  int n, k;\n  scanf(\"%d%d\"\
    , &n, &k);\n  printf(\"%d\\n\", binomial<modint<1000000007>>(n + k - 1, n));\n\
    }\n"
  dependsOn:
  - src/algebra/modint.hpp
  - src/number_theory/sqrt_mod.hpp
  - src/number_theory/pow_mod.hpp
  - src/utils/sfinae.hpp
  - src/combinatorics/binomial.hpp
  - src/combinatorics/factorial.hpp
  isVerificationFile: true
  path: test/aizu-online-judge/DPL_5_D.test.cpp
  requiredBy: []
  timestamp: '2021-10-09 12:38:59+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aizu-online-judge/DPL_5_D.test.cpp
layout: document
redirect_from:
- /verify/test/aizu-online-judge/DPL_5_D.test.cpp
- /verify/test/aizu-online-judge/DPL_5_D.test.cpp.html
title: test/aizu-online-judge/DPL_5_D.test.cpp
---
