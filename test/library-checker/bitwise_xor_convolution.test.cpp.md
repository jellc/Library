---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/algebra/convolution/bitxor.hpp
    title: Bitwise Xor Convolution
  - icon: ':heavy_check_mark:'
    path: src/modular/modint.hpp
    title: Modular Arithmetic
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
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/bitwise_xor_convolution
    links:
    - https://judge.yosupo.jp/problem/bitwise_xor_convolution
  bundledCode: "#line 1 \"test/library-checker/bitwise_xor_convolution.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/bitwise_xor_convolution\"\n\n\
    #include <vector>\n\n#line 2 \"src/algebra/convolution/bitxor.hpp\"\n\n/**\n *\
    \ @file bitxor.hpp\n * @brief Bitwise Xor Convolution\n * @date 2021-01-08\n */\n\
    \n#include <iterator>\n\n#line 1 \"lib/bit\"\n#if __cplusplus > 201703L\n\n#include\
    \ <bit>\n\n#else\n\n#ifndef _GLIBCXX_BIT\n#define _GLIBCXX_BIT 1\n\n#include <limits>\n\
    #include <type_traits>\n\nnamespace std {\n\ntemplate <typename _Tp> constexpr\
    \ _Tp __rotl(_Tp __x, int __s) noexcept {\n  constexpr auto _Nd = numeric_limits<_Tp>::digits;\n\
    \  const int __r = __s % _Nd;\n  if (__r == 0)\n    return __x;\n  else if (__r\
    \ > 0)\n    return (__x << __r) | (__x >> ((_Nd - __r) % _Nd));\n  else\n    return\
    \ (__x >> -__r) | (__x << ((_Nd + __r) % _Nd));  // rotr(x, -r)\n}\n\ntemplate\
    \ <typename _Tp> constexpr _Tp __rotr(_Tp __x, int __s) noexcept {\n  constexpr\
    \ auto _Nd = numeric_limits<_Tp>::digits;\n  const int __r = __s % _Nd;\n  if\
    \ (__r == 0)\n    return __x;\n  else if (__r > 0)\n    return (__x >> __r) |\
    \ (__x << ((_Nd - __r) % _Nd));\n  else\n    return (__x << -__r) | (__x >> ((_Nd\
    \ + __r) % _Nd));  // rotl(x, -r)\n}\n\ntemplate <typename _Tp> constexpr int\
    \ __countl_zero(_Tp __x) noexcept {\n  constexpr auto _Nd = numeric_limits<_Tp>::digits;\n\
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
    }\n\ntemplate <typename _Tp> constexpr int __countl_one(_Tp __x) noexcept {\n\
    \  if (__x == numeric_limits<_Tp>::max()) return numeric_limits<_Tp>::digits;\n\
    \  return __countl_zero<_Tp>((_Tp)~__x);\n}\n\ntemplate <typename _Tp> constexpr\
    \ int __countr_zero(_Tp __x) noexcept {\n  constexpr auto _Nd = numeric_limits<_Tp>::digits;\n\
    \n  if (__x == 0) return _Nd;\n\n  constexpr auto _Nd_ull = numeric_limits<unsigned\
    \ long long>::digits;\n  constexpr auto _Nd_ul = numeric_limits<unsigned long>::digits;\n\
    \  constexpr auto _Nd_u = numeric_limits<unsigned>::digits;\n\n  if _GLIBCXX17_CONSTEXPR\
    \ (_Nd <= _Nd_u)\n    return __builtin_ctz(__x);\n  else if _GLIBCXX17_CONSTEXPR\
    \ (_Nd <= _Nd_ul)\n    return __builtin_ctzl(__x);\n  else if _GLIBCXX17_CONSTEXPR\
    \ (_Nd <= _Nd_ull)\n    return __builtin_ctzll(__x);\n  else  // (_Nd > _Nd_ull)\n\
    \  {\n    static_assert(_Nd <= (2 * _Nd_ull),\n                  \"Maximum supported\
    \ integer size is 128-bit\");\n\n    constexpr auto __max_ull = numeric_limits<unsigned\
    \ long long>::max();\n    unsigned long long __low = __x & __max_ull;\n    if\
    \ (__low != 0) return __builtin_ctzll(__low);\n    unsigned long long __high =\
    \ __x >> _Nd_ull;\n    return __builtin_ctzll(__high) + _Nd_ull;\n  }\n}\n\ntemplate\
    \ <typename _Tp> constexpr int __countr_one(_Tp __x) noexcept {\n  if (__x ==\
    \ numeric_limits<_Tp>::max()) return numeric_limits<_Tp>::digits;\n  return __countr_zero((_Tp)~__x);\n\
    }\n\ntemplate <typename _Tp> constexpr int __popcount(_Tp __x) noexcept {\n  constexpr\
    \ auto _Nd = numeric_limits<_Tp>::digits;\n\n  if (__x == 0) return 0;\n\n  constexpr\
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
    }\n\ntemplate <typename _Tp> constexpr bool __has_single_bit(_Tp __x) noexcept\
    \ {\n  return __popcount(__x) == 1;\n}\n\ntemplate <typename _Tp> constexpr _Tp\
    \ __bit_ceil(_Tp __x) noexcept {\n  constexpr auto _Nd = numeric_limits<_Tp>::digits;\n\
    \  if (__x == 0 || __x == 1) return 1;\n  auto __shift_exponent = _Nd - __countl_zero((_Tp)(__x\
    \ - 1u));\n#ifdef _GLIBCXX_HAVE_BUILTIN_IS_CONSTANT_EVALUATED\n  if (!__builtin_is_constant_evaluated())\
    \ {\n    __glibcxx_assert(__shift_exponent != numeric_limits<_Tp>::digits);\n\
    \  }\n#endif\n  using __promoted_type = decltype(__x << 1);\n  if _GLIBCXX17_CONSTEXPR\
    \ (!is_same<__promoted_type, _Tp>::value) {\n    const int __extra_exp = sizeof(__promoted_type)\
    \ / sizeof(_Tp) / 2;\n    __shift_exponent |= (__shift_exponent & _Nd) << __extra_exp;\n\
    \  }\n  return (_Tp)1u << __shift_exponent;\n}\n\ntemplate <typename _Tp> constexpr\
    \ _Tp __bit_floor(_Tp __x) noexcept {\n  constexpr auto _Nd = numeric_limits<_Tp>::digits;\n\
    \  if (__x == 0) return 0;\n  return (_Tp)1u << (_Nd - __countl_zero((_Tp)(__x\
    \ >> 1)));\n}\n\ntemplate <typename _Tp> constexpr _Tp __bit_width(_Tp __x) noexcept\
    \ {\n  constexpr auto _Nd = numeric_limits<_Tp>::digits;\n  return _Nd - __countl_zero(__x);\n\
    }\n\n}  // namespace std\n\n#endif\n\n#endif\n#line 12 \"src/algebra/convolution/bitxor.hpp\"\
    \n\nnamespace workspace {\n\ntemplate <class A> A bitwise_fft(A f) {\n  size_t\
    \ len = std::__bit_floor(std::size(f));\n  for (size_t p = 1; p < len; p <<= 1)\
    \ {\n    for (size_t i = 0; i < len; i += p << 1) {\n      for (size_t j = 0;\
    \ j < p; ++j) {\n        auto t = f[i + j + p];\n        f[i + j + p] = f[i +\
    \ j] - t;\n        f[i + j] += t;\n      }\n    }\n  }\n  return f;\n}\n\ntemplate\
    \ <class A> A bitwise_ifft(A f) {\n  size_t len = std::__bit_floor(std::size(f));\n\
    \  for (size_t p = len; p != 1; p >>= 1) {\n    for (size_t i = 0; i < len; i\
    \ += p) {\n      for (size_t j = 0; j << 1 < p; ++j) {\n        auto t = f[i +\
    \ j + (p >> 1)];\n        f[i + j + (p >> 1)] = (f[i + j] - t) / 2;\n        (f[i\
    \ + j] += t) /= 2;\n      }\n    }\n  }\n  return f;\n}\n\ntemplate <class A>\
    \ A bitxor_conv(A f, A g) {\n  f = bitwise_fft(f);\n  g = bitwise_fft(g);\n  for\
    \ (size_t i = 0; i != std::size(f); ++i) f[i] *= g[i];\n  f = bitwise_ifft(f);\n\
    \  return f;\n}\n\n}  // namespace workspace\n#line 2 \"src/modular/modint.hpp\"\
    \n\n/*\n * @file modint.hpp\n * @brief Modular Arithmetic\n */\n\n#include <cassert>\n\
    #include <iostream>\n\n#line 2 \"src/utils/sfinae.hpp\"\n\n/**\n * @file sfinae.hpp\n\
    \ * @brief SFINAE\n */\n\n#include <cstdint>\n#line 10 \"src/utils/sfinae.hpp\"\
    \n#include <type_traits>\n\n#ifdef __SIZEOF_INT128__\n#define __INT128_DEFINED__\
    \ 1\n#else\n#define __INT128_DEFINED__ 0\n#endif\n\nnamespace std {\n\n#if __INT128_DEFINED__\n\
    \ntemplate <> struct make_signed<__uint128_t> { using type = __int128_t; };\n\
    template <> struct make_signed<__int128_t> { using type = __int128_t; };\n\ntemplate\
    \ <> struct make_unsigned<__uint128_t> { using type = __uint128_t; };\ntemplate\
    \ <> struct make_unsigned<__int128_t> { using type = __uint128_t; };\n\n#endif\n\
    \n}  // namespace std\n\nnamespace workspace {\n\ntemplate <class type, template\
    \ <class> class trait>\nusing enable_if_trait_type = typename std::enable_if<trait<type>::value>::type;\n\
    \ntemplate <class Container>\nusing element_type = typename std::decay<decltype(\n\
    \    *std::begin(std::declval<Container&>()))>::type;\n\ntemplate <class T, class\
    \ = std::nullptr_t>\nstruct has_begin : std::false_type {};\n\ntemplate <class\
    \ T>\nstruct has_begin<T, decltype(std::begin(std::declval<T>()), nullptr)>\n\
    \    : std::true_type {};\n\ntemplate <class T, class = int> struct mapped_of\
    \ {\n  using type = element_type<T>;\n};\ntemplate <class T>\nstruct mapped_of<T,\n\
    \                 typename std::pair<int, typename T::mapped_type>::first_type>\
    \ {\n  using type = typename T::mapped_type;\n};\ntemplate <class T> using mapped_type\
    \ = typename mapped_of<T>::type;\n\ntemplate <class T, class = void> struct is_integral_ext\
    \ : std::false_type {};\ntemplate <class T>\nstruct is_integral_ext<\n    T, typename\
    \ std::enable_if<std::is_integral<T>::value>::type>\n    : std::true_type {};\n\
    \n#if __INT128_DEFINED__\n\ntemplate <> struct is_integral_ext<__int128_t> : std::true_type\
    \ {};\ntemplate <> struct is_integral_ext<__uint128_t> : std::true_type {};\n\n\
    #endif\n\n#if __cplusplus >= 201402\n\ntemplate <class T>\nconstexpr static bool\
    \ is_integral_ext_v = is_integral_ext<T>::value;\n\n#endif\n\ntemplate <typename\
    \ T, typename = void> struct multiplicable_uint {\n  using type = uint_least32_t;\n\
    };\ntemplate <typename T>\nstruct multiplicable_uint<\n    T, typename std::enable_if<(2\
    \ < sizeof(T)) &&\n                               (!__INT128_DEFINED__ || sizeof(T)\
    \ <= 4)>::type> {\n  using type = uint_least64_t;\n};\n\n#if __INT128_DEFINED__\n\
    \ntemplate <typename T>\nstruct multiplicable_uint<T, typename std::enable_if<(4\
    \ < sizeof(T))>::type> {\n  using type = __uint128_t;\n};\n\n#endif\n\ntemplate\
    \ <typename T> struct multiplicable_int {\n  using type =\n      typename std::make_signed<typename\
    \ multiplicable_uint<T>::type>::type;\n};\n\n}  // namespace workspace\n#line\
    \ 12 \"src/modular/modint.hpp\"\n\nnamespace workspace {\n\nnamespace internal\
    \ {\n\n/*\n * @struct modint_base\n * @brief base of modular arithmetic.\n * @tparam\
    \ Mod identifier, which represents modulus if positive\n */\ntemplate <auto Mod>\
    \ struct modint_base {\n  static_assert(is_integral_ext<decltype(Mod)>::value,\n\
    \                \"Mod must be integral type.\");\n\n  using mod_type =\n    \
    \  typename std::conditional<0 < Mod,\n                                typename\
    \ std::add_const<decltype(Mod)>::type,\n                                decltype(Mod)>::type;\n\
    \  static mod_type mod;\n\n  using value_type = typename std::decay<mod_type>::type;\n\
    \n  constexpr operator value_type() const noexcept { return value; }\n\n  constexpr\
    \ static modint_base one() noexcept { return 1; }\n\n  constexpr modint_base()\
    \ noexcept = default;\n\n  template <class int_type,\n            typename std::enable_if<is_integral_ext<int_type>::value>::type\
    \ * =\n                nullptr>\n  constexpr modint_base(int_type n) noexcept\n\
    \      : value((n %= mod) < 0 ? mod + n : n) {}\n\n  constexpr modint_base(bool\
    \ n) noexcept : modint_base(int(n)) {}\n\n  constexpr modint_base operator++(int)\
    \ noexcept {\n    modint_base t{*this};\n    return operator+=(1), t;\n  }\n\n\
    \  constexpr modint_base operator--(int) noexcept {\n    modint_base t{*this};\n\
    \    return operator-=(1), t;\n  }\n\n  constexpr modint_base &operator++() noexcept\
    \ { return operator+=(1); }\n\n  constexpr modint_base &operator--() noexcept\
    \ { return operator-=(1); }\n\n  constexpr modint_base operator-() const noexcept\
    \ {\n    return value ? mod - value : 0;\n  }\n\n  constexpr modint_base &operator+=(const\
    \ modint_base &rhs) noexcept {\n    return (value += rhs.value) < mod ? 0 : value\
    \ -= mod, *this;\n  }\n\n  constexpr modint_base &operator-=(const modint_base\
    \ &rhs) noexcept {\n    return (value += mod - rhs.value) < mod ? 0 : value -=\
    \ mod, *this;\n  }\n\n  constexpr modint_base &operator*=(const modint_base &rhs)\
    \ noexcept {\n    return value = (typename multiplicable_uint<value_type>::type)value\
    \ *\n                   rhs.value % mod,\n           *this;\n  }\n\n  constexpr\
    \ modint_base &operator/=(const modint_base &rhs) noexcept {\n    return operator*=(rhs.inverse());\n\
    \  }\n\n  template <class int_type>\n  constexpr typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                    modint_base>::type\n  operator+(const int_type\
    \ &rhs) const noexcept {\n    return modint_base{*this} += rhs;\n  }\n\n  constexpr\
    \ modint_base operator+(const modint_base &rhs) const noexcept {\n    return modint_base{*this}\
    \ += rhs;\n  }\n\n  template <class int_type>\n  constexpr typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                    modint_base>::type\n  operator-(const int_type\
    \ &rhs) const noexcept {\n    return modint_base{*this} -= rhs;\n  }\n\n  constexpr\
    \ modint_base operator-(const modint_base &rhs) const noexcept {\n    return modint_base{*this}\
    \ -= rhs;\n  }\n\n  template <class int_type>\n  constexpr typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                    modint_base>::type\n  operator*(const int_type\
    \ &rhs) const noexcept {\n    return modint_base{*this} *= rhs;\n  }\n\n  constexpr\
    \ modint_base operator*(const modint_base &rhs) const noexcept {\n    return modint_base{*this}\
    \ *= rhs;\n  }\n\n  template <class int_type>\n  constexpr typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                    modint_base>::type\n  operator/(const int_type\
    \ &rhs) const noexcept {\n    return modint_base{*this} /= rhs;\n  }\n\n  constexpr\
    \ modint_base operator/(const modint_base &rhs) const noexcept {\n    return modint_base{*this}\
    \ /= rhs;\n  }\n\n  template <class int_type>\n  constexpr friend typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                           modint_base>::type\n  operator+(const\
    \ int_type &lhs, const modint_base &rhs) noexcept {\n    return modint_base(lhs)\
    \ + rhs;\n  }\n\n  template <class int_type>\n  constexpr friend typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                           modint_base>::type\n  operator-(const\
    \ int_type &lhs, const modint_base &rhs) noexcept {\n    return modint_base(lhs)\
    \ - rhs;\n  }\n\n  template <class int_type>\n  constexpr friend typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                           modint_base>::type\n  operator*(const\
    \ int_type &lhs, const modint_base &rhs) noexcept {\n    return modint_base(lhs)\
    \ * rhs;\n  }\n\n  template <class int_type>\n  constexpr friend typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                           modint_base>::type\n  operator/(const\
    \ int_type &lhs, const modint_base &rhs) noexcept {\n    return modint_base(lhs)\
    \ / rhs;\n  }\n\n  constexpr modint_base inverse() const noexcept {\n    assert(value);\n\
    \    value_type a{mod}, b{value}, u{}, v{1}, t{};\n    while (b)\n      t = a\
    \ / b, a ^= b ^= (a -= t * b) ^= b, u ^= v ^= (u -= t * v) ^= v;\n    return {u};\n\
    \  }\n\n  template <class int_type>\n  constexpr typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                    modint_base>::type\n  power(int_type e) noexcept\
    \ {\n    return pow(*this, e);\n  }\n\n  template <class int_type>\n  friend constexpr\
    \ typename std::enable_if<is_integral_ext<int_type>::value,\n                \
    \                           modint_base>::type\n  pow(modint_base b, int_type\
    \ e) noexcept {\n    modint_base res{1};\n    for (e < 0 ? b = b.inverse(), e\
    \ = -e : 0; e; e >>= 1, b *= b)\n      if (e & 1) res *= b;\n    return res;\n\
    \  }\n\n  friend std::ostream &operator<<(std::ostream &os,\n                \
    \                  const modint_base &rhs) noexcept {\n    return os << rhs.value;\n\
    \  }\n\n  friend std::istream &operator>>(std::istream &is, modint_base &rhs)\
    \ noexcept {\n    intmax_t value;\n    rhs = (is >> value, value);\n    return\
    \ is;\n  }\n\n protected:\n  value_type value = 0;\n};\n\ntemplate <auto Mod>\n\
    typename modint_base<Mod>::mod_type modint_base<Mod>::mod = Mod;\n\n}  // namespace\
    \ internal\n\n/*\n * @typedef modint\n * @brief modular arithmetic.\n * @tparam\
    \ Mod modulus\n */\ntemplate <auto Mod, typename std::enable_if<(Mod > 0)>::type\
    \ * = nullptr>\nusing modint = internal::modint_base<Mod>;\n\n/*\n * @typedef\
    \ modint_runtime\n * @brief runtime modular arithmetic.\n * @tparam type_id uniquely\
    \ assigned\n */\ntemplate <unsigned type_id = 0>\nusing modint_runtime = internal::modint_base<-(signed)type_id>;\n\
    \n// #define modint_newtype modint_runtime<__COUNTER__>\n\n}  // namespace workspace\n\
    #line 2 \"src/utils/io/istream.hpp\"\n\n/**\n * @file istream.hpp\n * @brief Input\
    \ Stream\n */\n\n#include <cxxabi.h>\n\n#line 12 \"src/utils/io/istream.hpp\"\n\
    #include <tuple>\n\n#line 15 \"src/utils/io/istream.hpp\"\n\nnamespace workspace\
    \ {\n\nnamespace internal {\n\ntemplate <class Tp, typename = std::nullptr_t>\
    \ struct istream_helper {\n  istream_helper(std::istream &is, Tp &x) {\n    if\
    \ constexpr (has_begin<Tp>::value)\n      for (auto &&e : x)\n        istream_helper<typename\
    \ std::decay<decltype(e)>::type>(is, e);\n    else\n      static_assert(has_begin<Tp>::value,\
    \ \"istream unsupported type.\");\n  }\n};\n\ntemplate <class Tp>\nstruct istream_helper<\n\
    \    Tp,\n    decltype(std::declval<std::decay<decltype(std::declval<std::istream\
    \ &>() >>\n                                              std::declval<Tp &>())>>(),\n\
    \             nullptr)> {\n  istream_helper(std::istream &is, Tp &x) { is >> x;\
    \ }\n};\n\n#ifdef __SIZEOF_INT128__\n\ntemplate <> struct istream_helper<__int128_t,\
    \ std::nullptr_t> {\n  istream_helper(std::istream &is, __int128_t &x) {\n   \
    \ std::string s;\n    is >> s;\n    bool negative = s.front() == '-' ? s.erase(s.begin()),\
    \ true : false;\n    x = 0;\n    for (char e : s) x = x * 10 + e - '0';\n    if\
    \ (negative) x = -x;\n  }\n};\n\ntemplate <> struct istream_helper<__uint128_t,\
    \ std::nullptr_t> {\n  istream_helper(std::istream &is, __uint128_t &x) {\n  \
    \  std::string s;\n    is >> s;\n    bool negative = s.front() == '-' ? s.erase(s.begin()),\
    \ true : false;\n    x = 0;\n    for (char e : s) x = x * 10 + e - '0';\n    if\
    \ (negative) x = -x;\n  }\n};\n\n#endif  // INT128\n\ntemplate <class T1, class\
    \ T2> struct istream_helper<std::pair<T1, T2>> {\n  istream_helper(std::istream\
    \ &is, std::pair<T1, T2> &x) {\n    istream_helper<T1>(is, x.first), istream_helper<T2>(is,\
    \ x.second);\n  }\n};\n\ntemplate <class... Tps> struct istream_helper<std::tuple<Tps...>>\
    \ {\n  istream_helper(std::istream &is, std::tuple<Tps...> &x) { iterate(is, x);\
    \ }\n\n private:\n  template <class Tp, size_t N = 0> void iterate(std::istream\
    \ &is, Tp &x) {\n    if constexpr (N == std::tuple_size<Tp>::value)\n      return;\n\
    \    else\n      istream_helper<typename std::tuple_element<N, Tp>::type>(is,\n\
    \                                                               std::get<N>(x)),\n\
    \          iterate<Tp, N + 1>(is, x);\n  }\n};\n\n}  // namespace internal\n\n\
    /**\n * @brief A wrapper class for std::istream.\n */\nclass istream : public\
    \ std::istream {\n public:\n  /**\n   * @brief Wrapped operator.\n   */\n  template\
    \ <typename Tp> istream &operator>>(Tp &x) {\n    internal::istream_helper<Tp>(*this,\
    \ x);\n    if (std::istream::fail()) {\n      static auto once = atexit([] {\n\
    \        std::cerr << \"\\n\\033[43m\\033[30mwarning: failed to read \\'\"\n \
    \                 << abi::__cxa_demangle(typeid(Tp).name(), 0, 0, 0)\n       \
    \           << \"\\'.\\033[0m\\n\\n\";\n      });\n      assert(!once);\n    }\n\
    \    return *this;\n  }\n};\n\nnamespace internal {\nauto *const cin_ptr = (istream\
    \ *)&std::cin;\n}\nauto &cin = *internal::cin_ptr;\n\n}  // namespace workspace\n\
    #line 2 \"src/utils/io/ostream.hpp\"\n\n/*\n * @file ostream.hpp\n * @brief Output\
    \ Stream\n */\n\n#line 10 \"src/utils/io/ostream.hpp\"\n\nnamespace workspace\
    \ {\n\ntemplate <class T, class U>\nstd::ostream &operator<<(std::ostream &os,\
    \ const std::pair<T, U> &p) {\n  return os << p.first << ' ' << p.second;\n}\n\
    template <class tuple_t, size_t index> struct tuple_os {\n  static std::ostream\
    \ &apply(std::ostream &os, const tuple_t &t) {\n    tuple_os<tuple_t, index -\
    \ 1>::apply(os, t);\n    return os << ' ' << std::get<index>(t);\n  }\n};\ntemplate\
    \ <class tuple_t> struct tuple_os<tuple_t, 0> {\n  static std::ostream &apply(std::ostream\
    \ &os, const tuple_t &t) {\n    return os << std::get<0>(t);\n  }\n};\ntemplate\
    \ <class tuple_t> struct tuple_os<tuple_t, SIZE_MAX> {\n  static std::ostream\
    \ &apply(std::ostream &os, const tuple_t &t) { return os; }\n};\n\ntemplate <class...\
    \ T>\nstd::ostream &operator<<(std::ostream &os, const std::tuple<T...> &t) {\n\
    \  return tuple_os<std::tuple<T...>,\n                  std::tuple_size<std::tuple<T...>>::value\
    \ - 1>::apply(os, t);\n}\n\ntemplate <class Container,\n          typename = decltype(std::begin(std::declval<Container>()))>\n\
    typename std::enable_if<\n    !std::is_same<typename std::decay<Container>::type,\
    \ std::string>::value &&\n        !std::is_same<typename std::decay<Container>::type,\
    \ char *>::value,\n    std::ostream &>::type\noperator<<(std::ostream &os, const\
    \ Container &cont) {\n  bool head = true;\n  for (auto &&e : cont) head ? head\
    \ = 0 : (os << ' ', 0), os << e;\n  return os;\n}\n\n}  // namespace workspace\n\
    #line 9 \"test/library-checker/bitwise_xor_convolution.test.cpp\"\n\nint main()\
    \ {\n  using namespace workspace;\n  using mint = modint<998244353>;\n  size_t\
    \ n;\n  cin >> n;\n  std::vector<mint> a(1 << n), b(1 << n);\n  cin >> a >> b;\n\
    \  std::cout << bitxor_conv(a, b) << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/bitwise_xor_convolution\"\
    \n\n#include <vector>\n\n#include \"src/algebra/convolution/bitxor.hpp\"\n#include\
    \ \"src/modular/modint.hpp\"\n#include \"src/utils/io/istream.hpp\"\n#include\
    \ \"src/utils/io/ostream.hpp\"\n\nint main() {\n  using namespace workspace;\n\
    \  using mint = modint<998244353>;\n  size_t n;\n  cin >> n;\n  std::vector<mint>\
    \ a(1 << n), b(1 << n);\n  cin >> a >> b;\n  std::cout << bitxor_conv(a, b) <<\
    \ \"\\n\";\n}\n"
  dependsOn:
  - src/algebra/convolution/bitxor.hpp
  - src/modular/modint.hpp
  - src/utils/sfinae.hpp
  - src/utils/io/istream.hpp
  - src/utils/io/ostream.hpp
  isVerificationFile: true
  path: test/library-checker/bitwise_xor_convolution.test.cpp
  requiredBy: []
  timestamp: '2021-01-13 00:11:06+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/library-checker/bitwise_xor_convolution.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/bitwise_xor_convolution.test.cpp
- /verify/test/library-checker/bitwise_xor_convolution.test.cpp.html
title: test/library-checker/bitwise_xor_convolution.test.cpp
---
