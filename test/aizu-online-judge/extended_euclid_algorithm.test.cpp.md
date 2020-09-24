---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: number_theory/ext_gcd.hpp
    title: number_theory/ext_gcd.hpp
  - icon: ':question:'
    path: utils/sfinae.hpp
    title: utils/sfinae.hpp
  - icon: ':heavy_check_mark:'
    path: utils/stream.hpp
    title: utils/stream.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/1/NTL_1_E
    links:
    - https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/1/NTL_1_E
  bundledCode: "#line 1 \"test/aizu-online-judge/extended_euclid_algorithm.test.cpp\"\
    \n#define PROBLEM \\\n  \"https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/1/NTL_1_E\"\
    \n#line 2 \"number_theory/ext_gcd.hpp\"\n#include <tuple>\n\n#line 2 \"utils/sfinae.hpp\"\
    \n#include <cstdint>\n#include <type_traits>\n\ntemplate <class type, template\
    \ <class> class trait>\nusing enable_if_trait_type = typename std::enable_if<trait<type>::value>::type;\n\
    \ntemplate <class Container>\nusing element_type = typename std::decay<decltype(\n\
    \    *std::begin(std::declval<Container&>()))>::type;\n\ntemplate <class T, class\
    \ = int> struct mapped_of {\n  using type = element_type<T>;\n};\ntemplate <class\
    \ T>\nstruct mapped_of<T,\n                 typename std::pair<int, typename T::mapped_type>::first_type>\
    \ {\n  using type = typename T::mapped_type;\n};\ntemplate <class T> using mapped_type\
    \ = typename mapped_of<T>::type;\n\ntemplate <class T, class = void> struct is_integral_ext\
    \ : std::false_type {};\ntemplate <class T>\nstruct is_integral_ext<\n    T, typename\
    \ std::enable_if<std::is_integral<T>::value>::type>\n    : std::true_type {};\n\
    template <> struct is_integral_ext<__int128_t> : std::true_type {};\ntemplate\
    \ <> struct is_integral_ext<__uint128_t> : std::true_type {};\n#if __cplusplus\
    \ >= 201402\ntemplate <class T>\nconstexpr static bool is_integral_ext_v = is_integral_ext<T>::value;\n\
    #endif\n\ntemplate <typename T, typename = void> struct multiplicable_uint {\n\
    \  using type = uint_least32_t;\n};\ntemplate <typename T>\nstruct multiplicable_uint<T,\
    \ typename std::enable_if<(2 < sizeof(T))>::type> {\n  using type = uint_least64_t;\n\
    };\ntemplate <typename T>\nstruct multiplicable_uint<T, typename std::enable_if<(4\
    \ < sizeof(T))>::type> {\n  using type = __uint128_t;\n};\n#line 5 \"number_theory/ext_gcd.hpp\"\
    \ntemplate <class int_type>\nconstexpr typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                  std::pair<int_type, int_type>>::type\next_gcd(int_type\
    \ a, int_type b) {\n  int_type p{1}, q{}, r{}, s{1}, t{};\n  if (a < 0) {\n  \
    \  std::tie(p, q) = ext_gcd(-a, b);\n    p = -p;\n  } else if (b < 0) {\n    std::tie(p,\
    \ q) = ext_gcd(a, -b);\n    q = -q;\n  } else {\n    while (b) {\n      r ^= p\
    \ ^= r ^= p -= (t = a / b) * r;\n      s ^= q ^= s ^= q -= t * s;\n      b ^=\
    \ a ^= b ^= a %= b;\n    }\n  }\n  return {p, q};\n}\n#line 2 \"utils/stream.hpp\"\
    \n#include <iostream>\n#line 4 \"utils/stream.hpp\"\n\n#line 6 \"utils/stream.hpp\"\
    \nnamespace std {\ntemplate <class T, class U> istream &operator>>(istream &is,\
    \ pair<T, U> &p) {\n  return is >> p.first >> p.second;\n}\ntemplate <class T,\
    \ class U>\nostream &operator<<(ostream &os, const pair<T, U> &p) {\n  return\
    \ os << p.first << ' ' << p.second;\n}\ntemplate <class tuple_t, size_t index>\
    \ struct tuple_is {\n  static istream &apply(istream &is, tuple_t &t) {\n    tuple_is<tuple_t,\
    \ index - 1>::apply(is, t);\n    return is >> get<index>(t);\n  }\n};\ntemplate\
    \ <class tuple_t> struct tuple_is<tuple_t, SIZE_MAX> {\n  static istream &apply(istream\
    \ &is, tuple_t &t) { return is; }\n};\ntemplate <class... T> istream &operator>>(istream\
    \ &is, tuple<T...> &t) {\n  return tuple_is<tuple<T...>, tuple_size<tuple<T...>>::value\
    \ - 1>::apply(is,\n                                                          \
    \                t);\n}\ntemplate <class tuple_t, size_t index> struct tuple_os\
    \ {\n  static ostream &apply(ostream &os, const tuple_t &t) {\n    tuple_os<tuple_t,\
    \ index - 1>::apply(os, t);\n    return os << ' ' << get<index>(t);\n  }\n};\n\
    template <class tuple_t> struct tuple_os<tuple_t, 0> {\n  static ostream &apply(ostream\
    \ &os, const tuple_t &t) {\n    return os << get<0>(t);\n  }\n};\ntemplate <class\
    \ tuple_t> struct tuple_os<tuple_t, SIZE_MAX> {\n  static ostream &apply(ostream\
    \ &os, const tuple_t &t) { return os; }\n};\ntemplate <class... T> ostream &operator<<(ostream\
    \ &os, const tuple<T...> &t) {\n  return tuple_os<tuple<T...>, tuple_size<tuple<T...>>::value\
    \ - 1>::apply(os,\n                                                          \
    \                t);\n}\ntemplate <class Container, typename Value = element_type<Container>>\n\
    typename enable_if<!is_same<typename decay<Container>::type, string>::value &&\n\
    \                       !is_same<typename decay<Container>::type, char *>::value,\n\
    \                   istream &>::type\noperator>>(istream &is, Container &cont)\
    \ {\n  for (auto &&e : cont) is >> e;\n  return is;\n}\ntemplate <class Container,\
    \ typename Value = element_type<Container>>\ntypename enable_if<!is_same<typename\
    \ decay<Container>::type, string>::value &&\n                       !is_same<typename\
    \ decay<Container>::type, char *>::value,\n                   ostream &>::type\n\
    operator<<(ostream &os, const Container &cont) {\n  bool head = true;\n  for (auto\
    \ &&e : cont) head ? head = 0 : (os << ' ', 0), os << e;\n  return os;\n}\n} \
    \ // namespace std\n#line 5 \"test/aizu-online-judge/extended_euclid_algorithm.test.cpp\"\
    \n\nint main() {\n  int a, b;\n  std::cin >> a >> b;\n  __int128_t _a = a, _b\
    \ = b;\n  auto [x, y] = ext_gcd(_a, _b);\n  if (x > 0) x -= b, y += a;\n  if ((y\
    \ - x) * 2 > a + b) x += b, y -= a;\n  a = x, b = y;\n  std::cout << std::tie(a,\
    \ b) << \"\\n\";\n}\n"
  code: "#define PROBLEM \\\n  \"https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/1/NTL_1_E\"\
    \n#include \"number_theory/ext_gcd.hpp\"\n#include \"utils/stream.hpp\"\n\nint\
    \ main() {\n  int a, b;\n  std::cin >> a >> b;\n  __int128_t _a = a, _b = b;\n\
    \  auto [x, y] = ext_gcd(_a, _b);\n  if (x > 0) x -= b, y += a;\n  if ((y - x)\
    \ * 2 > a + b) x += b, y -= a;\n  a = x, b = y;\n  std::cout << std::tie(a, b)\
    \ << \"\\n\";\n}\n"
  dependsOn:
  - number_theory/ext_gcd.hpp
  - utils/sfinae.hpp
  - utils/stream.hpp
  isVerificationFile: true
  path: test/aizu-online-judge/extended_euclid_algorithm.test.cpp
  requiredBy: []
  timestamp: '2020-09-24 00:53:44+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aizu-online-judge/extended_euclid_algorithm.test.cpp
layout: document
redirect_from:
- /verify/test/aizu-online-judge/extended_euclid_algorithm.test.cpp
- /verify/test/aizu-online-judge/extended_euclid_algorithm.test.cpp.html
title: test/aizu-online-judge/extended_euclid_algorithm.test.cpp
---
