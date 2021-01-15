---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/number_theory/ext_gcd.hpp
    title: Extended Euclidean Algorithm
  - icon: ':heavy_check_mark:'
    path: src/utils/sfinae.hpp
    title: SFINAE
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Order
    links: []
  bundledCode: "#line 1 \"src/number_theory/order.hpp\"\n/**\n * @file order.hpp\n\
    \ * @brief Order\n * @date 2021-01-15\n *\n *\n */\n\n#include <unordered_map>\n\
    \n#line 2 \"src/number_theory/ext_gcd.hpp\"\n\n/*\n * @file ext_gcd\n * @brief\
    \ Extended Euclidean Algorithm\n */\n\n#include <tuple>\n\n#line 2 \"src/utils/sfinae.hpp\"\
    \n\n/**\n * @file sfinae.hpp\n * @brief SFINAE\n */\n\n#include <cstdint>\n#include\
    \ <iterator>\n#include <type_traits>\n\n#ifdef __SIZEOF_INT128__\n#define __INT128_DEFINED__\
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
    \ 11 \"src/number_theory/ext_gcd.hpp\"\n\nnamespace workspace {\n\n/**\n * @param\
    \ a Integer\n * @param b Integer\n * @return Pair of integers (x, y) s.t. ax +\
    \ by = g = gcd(a, b), |x| < |b/g|,\n * |y| < |a/g|.\n * @note return (0, 0) if\
    \ (a, b) = (0, 0)\n */\ntemplate <typename T1, typename T2> constexpr auto ext_gcd(T1\
    \ a, T2 b) {\n  static_assert(is_integral_ext<T1>::value);\n  static_assert(is_integral_ext<T2>::value);\n\
    \  using result_type =\n      typename std::make_signed<typename std::common_type<T1,\
    \ T2>::type>::type;\n  result_type p{1}, q{}, r{}, s{1}, t;\n  while (b) {\n \
    \   r ^= p ^= r ^= p -= (t = a / b) * r;\n    s ^= q ^= s ^= q -= t * s;\n   \
    \ b ^= a ^= b ^= a %= b;\n  }\n  if (a < 0) p = -p, q = -q;\n  return std::make_pair(p,\
    \ q);\n}\n\n}  // namespace workspace\n#line 12 \"src/number_theory/order.hpp\"\
    \n\nnamespace workspace {\n\n/**\n * @brief\n *\n * @param __x Integer\n * @param\
    \ __mod Modulus\n * @return The order of @p __x modulo @p __mod.\n */\ntemplate\
    \ <class Tp>\nconstexpr typename std::enable_if<(is_integral_ext<Tp>::value),\
    \ Tp>::type order(\n    Tp __x, const Tp __mod) noexcept {\n  assert(__mod > 0);\n\
    \  using int_type = typename multiplicable_int<Tp>::type;\n\n  __x %= __mod;\n\
    \  if (__x < 0) __x += __mod;\n  std::unordered_map<Tp, Tp> __ls;\n  int_type\
    \ __p;\n  Tp __i;\n  for (__i = 1, __p = __x; __i * __i < __mod; ++__i, (__p *=\
    \ __x) %= __mod)\n    __ls.emplace(__p, __i);\n\n  for (int_type __q{1}, __v{1},\
    \ __j{0};;\n       __v = ext_gcd((__q *= __p) %= __mod, __mod).first, __j += __i,\n\
    \       __ls[1] = 0)\n    if (auto __f = __ls.find(__v < 0 ? __v += __mod : __v);\
    \ __f != __ls.end())\n      return __j + __f->second;\n};\n\n}  // namespace workspace\n"
  code: "/**\n * @file order.hpp\n * @brief Order\n * @date 2021-01-15\n *\n *\n */\n\
    \n#include <unordered_map>\n\n#include \"ext_gcd.hpp\"\n\nnamespace workspace\
    \ {\n\n/**\n * @brief\n *\n * @param __x Integer\n * @param __mod Modulus\n *\
    \ @return The order of @p __x modulo @p __mod.\n */\ntemplate <class Tp>\nconstexpr\
    \ typename std::enable_if<(is_integral_ext<Tp>::value), Tp>::type order(\n   \
    \ Tp __x, const Tp __mod) noexcept {\n  assert(__mod > 0);\n  using int_type =\
    \ typename multiplicable_int<Tp>::type;\n\n  __x %= __mod;\n  if (__x < 0) __x\
    \ += __mod;\n  std::unordered_map<Tp, Tp> __ls;\n  int_type __p;\n  Tp __i;\n\
    \  for (__i = 1, __p = __x; __i * __i < __mod; ++__i, (__p *= __x) %= __mod)\n\
    \    __ls.emplace(__p, __i);\n\n  for (int_type __q{1}, __v{1}, __j{0};;\n   \
    \    __v = ext_gcd((__q *= __p) %= __mod, __mod).first, __j += __i,\n       __ls[1]\
    \ = 0)\n    if (auto __f = __ls.find(__v < 0 ? __v += __mod : __v); __f != __ls.end())\n\
    \      return __j + __f->second;\n};\n\n}  // namespace workspace\n"
  dependsOn:
  - src/number_theory/ext_gcd.hpp
  - src/utils/sfinae.hpp
  isVerificationFile: false
  path: src/number_theory/order.hpp
  requiredBy: []
  timestamp: '2021-01-16 01:15:37+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/number_theory/order.hpp
layout: document
redirect_from:
- /library/src/number_theory/order.hpp
- /library/src/number_theory/order.hpp.html
title: Order
---
