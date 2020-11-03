---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: utils/sfinae.hpp
    title: utils/sfinae.hpp
  _extendedRequiredBy:
  - icon: ':warning:'
    path: template.cpp
    title: template.cpp
  - icon: ':warning:'
    path: utils.hpp
    title: utils.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/do_use_segment_tree.test.cpp
    title: test/aizu-online-judge/do_use_segment_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/extended_euclid_algorithm.test.cpp
    title: test/aizu-online-judge/extended_euclid_algorithm.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/pattern_search.test.cpp
    title: test/aizu-online-judge/pattern_search.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/range_minimum_query.test.cpp
    title: test/aizu-online-judge/range_minimum_query.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/suffix_array.test.cpp
    title: test/library-checker/suffix_array.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/zalgorithm.test.cpp
    title: test/library-checker/zalgorithm.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"utils/stream.hpp\"\n#include <iostream>\n#include <tuple>\n\
    \n#line 2 \"utils/sfinae.hpp\"\n#include <cstdint>\n#include <iterator>\n#include\
    \ <type_traits>\n\ntemplate <class type, template <class> class trait>\nusing\
    \ enable_if_trait_type = typename std::enable_if<trait<type>::value>::type;\n\n\
    template <class Container>\nusing element_type = typename std::decay<decltype(\n\
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
    \ < sizeof(T))>::type> {\n  using type = __uint128_t;\n};\n#line 6 \"utils/stream.hpp\"\
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
    \ // namespace std\n"
  code: "#pragma once\n#include <iostream>\n#include <tuple>\n\n#include \"sfinae.hpp\"\
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
    \ // namespace std\n"
  dependsOn:
  - utils/sfinae.hpp
  isVerificationFile: false
  path: utils/stream.hpp
  requiredBy:
  - template.cpp
  - utils.hpp
  timestamp: '2020-10-10 01:30:31+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/zalgorithm.test.cpp
  - test/library-checker/suffix_array.test.cpp
  - test/aizu-online-judge/range_minimum_query.test.cpp
  - test/aizu-online-judge/pattern_search.test.cpp
  - test/aizu-online-judge/extended_euclid_algorithm.test.cpp
  - test/aizu-online-judge/do_use_segment_tree.test.cpp
documentation_of: utils/stream.hpp
layout: document
redirect_from:
- /library/utils/stream.hpp
- /library/utils/stream.hpp.html
title: utils/stream.hpp
---
