---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/number_theory/ext_gcd.hpp
    title: Extended Euclidean Algorithm
  - icon: ':heavy_check_mark:'
    path: src/utils/io/ostream.hpp
    title: Output Stream
  - icon: ':question:'
    path: src/utils/sfinae.hpp
    title: SFINAE
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_E
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_E
  bundledCode: "#line 1 \"test/aizu-online-judge/NTL_1_E.test.cpp\"\n#define PROBLEM\
    \ \"https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_E\"\n\n#line 2 \"src/number_theory/ext_gcd.hpp\"\
    \n\n/*\n * @file ext_gcd\n * @brief Extended Euclidean Algorithm\n */\n\n#include\
    \ <tuple>\n\n#line 2 \"src/utils/sfinae.hpp\"\n\n/*\n * @file sfinae.hpp\n * @brief\
    \ SFINAE\n */\n\n#include <cstdint>\n#include <iterator>\n#include <type_traits>\n\
    \nnamespace workspace {\n\ntemplate <class type, template <class> class trait>\n\
    using enable_if_trait_type = typename std::enable_if<trait<type>::value>::type;\n\
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
    \n#ifdef __SIZEOF_INT128__\ntemplate <> struct is_integral_ext<__int128_t> : std::true_type\
    \ {};\ntemplate <> struct is_integral_ext<__uint128_t> : std::true_type {};\n\
    #endif\n\n#if __cplusplus >= 201402\ntemplate <class T>\nconstexpr static bool\
    \ is_integral_ext_v = is_integral_ext<T>::value;\n#endif\n\ntemplate <typename\
    \ T, typename = void> struct multiplicable_uint {\n  using type = uint_least32_t;\n\
    };\ntemplate <typename T>\nstruct multiplicable_uint<T, typename std::enable_if<(2\
    \ < sizeof(T))>::type> {\n  using type = uint_least64_t;\n};\n\n#ifdef __SIZEOF_INT128__\n\
    template <typename T>\nstruct multiplicable_uint<T, typename std::enable_if<(4\
    \ < sizeof(T))>::type> {\n  using type = __uint128_t;\n};\n#endif\n\n}  // namespace\
    \ workspace\n#line 11 \"src/number_theory/ext_gcd.hpp\"\n\nnamespace workspace\
    \ {\n\n/*\n * @fn ext_gcd\n * @param a an integer\n * @param b an integer\n *\
    \ @return a pair of integers (x, y) s.t. ax + by = gcd(a, b)\n * @note return\
    \ (0, 0) if (a, b) = (0, 0)\n */\ntemplate <typename T1, typename T2>\nconstexpr\
    \ typename std::enable_if<\n    (is_integral_ext<T1>::value && is_integral_ext<T2>::value),\n\
    \    std::pair<typename std::common_type<T1, T2>::type,\n              typename\
    \ std::common_type<T1, T2>::type>>::type\next_gcd(T1 a, T2 b) {\n  typename std::common_type<T1,\
    \ T2>::type p{1}, q{}, r{}, s{1}, t{};\n  if (a < 0) {\n    std::tie(p, q) = ext_gcd(-a,\
    \ b);\n    p = -p;\n  } else if (b < 0) {\n    std::tie(p, q) = ext_gcd(a, -b);\n\
    \    q = -q;\n  } else {\n    while (b) {\n      r ^= p ^= r ^= p -= (t = a /\
    \ b) * r;\n      s ^= q ^= s ^= q -= t * s;\n      b ^= a ^= b ^= a %= b;\n  \
    \  }\n  }\n  return {p, q};\n}\n\n}  // namespace workspace\n#line 2 \"src/utils/io/ostream.hpp\"\
    \n\n/*\n * @file ostream.hpp\n * @brief Output Stream\n */\n\n#include <iostream>\n\
    #line 10 \"src/utils/io/ostream.hpp\"\n\nnamespace workspace {\n\ntemplate <class\
    \ T, class U>\nstd::ostream &operator<<(std::ostream &os, const std::pair<T, U>\
    \ &p) {\n  return os << p.first << ' ' << p.second;\n}\ntemplate <class tuple_t,\
    \ size_t index> struct tuple_os {\n  static std::ostream &apply(std::ostream &os,\
    \ const tuple_t &t) {\n    tuple_os<tuple_t, index - 1>::apply(os, t);\n    return\
    \ os << ' ' << std::get<index>(t);\n  }\n};\ntemplate <class tuple_t> struct tuple_os<tuple_t,\
    \ 0> {\n  static std::ostream &apply(std::ostream &os, const tuple_t &t) {\n \
    \   return os << std::get<0>(t);\n  }\n};\ntemplate <class tuple_t> struct tuple_os<tuple_t,\
    \ SIZE_MAX> {\n  static std::ostream &apply(std::ostream &os, const tuple_t &t)\
    \ { return os; }\n};\n\ntemplate <class... T>\nstd::ostream &operator<<(std::ostream\
    \ &os, const std::tuple<T...> &t) {\n  return tuple_os<std::tuple<T...>,\n   \
    \               std::tuple_size<std::tuple<T...>>::value - 1>::apply(os, t);\n\
    }\n\ntemplate <class Container,\n          typename = decltype(std::begin(std::declval<Container>()))>\n\
    typename std::enable_if<\n    !std::is_same<typename std::decay<Container>::type,\
    \ std::string>::value &&\n        !std::is_same<typename std::decay<Container>::type,\
    \ char *>::value,\n    std::ostream &>::type\noperator<<(std::ostream &os, const\
    \ Container &cont) {\n  bool head = true;\n  for (auto &&e : cont) head ? head\
    \ = 0 : (os << ' ', 0), os << e;\n  return os;\n}\n\n}  // namespace workspace\n\
    #line 5 \"test/aizu-online-judge/NTL_1_E.test.cpp\"\n\nint main() {\n  using namespace\
    \ workspace;\n  int a, b;\n  std::cin >> a >> b;\n  __int128_t _a = a, _b = b;\n\
    \  auto [x, y] = ext_gcd(_a, b);\n  if (x > 0) x -= b, y += a;\n  if ((y - x)\
    \ * 2 > a + b) x += b, y -= a;\n  a = x, b = y;\n  std::cout << std::tie(a, b)\
    \ << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_E\"\n\n\
    #include \"src/number_theory/ext_gcd.hpp\"\n#include \"src/utils/io/ostream.hpp\"\
    \n\nint main() {\n  using namespace workspace;\n  int a, b;\n  std::cin >> a >>\
    \ b;\n  __int128_t _a = a, _b = b;\n  auto [x, y] = ext_gcd(_a, b);\n  if (x >\
    \ 0) x -= b, y += a;\n  if ((y - x) * 2 > a + b) x += b, y -= a;\n  a = x, b =\
    \ y;\n  std::cout << std::tie(a, b) << \"\\n\";\n}\n"
  dependsOn:
  - src/number_theory/ext_gcd.hpp
  - src/utils/sfinae.hpp
  - src/utils/io/ostream.hpp
  isVerificationFile: true
  path: test/aizu-online-judge/NTL_1_E.test.cpp
  requiredBy: []
  timestamp: '2020-12-01 16:34:20+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aizu-online-judge/NTL_1_E.test.cpp
layout: document
redirect_from:
- /verify/test/aizu-online-judge/NTL_1_E.test.cpp
- /verify/test/aizu-online-judge/NTL_1_E.test.cpp.html
title: test/aizu-online-judge/NTL_1_E.test.cpp
---
