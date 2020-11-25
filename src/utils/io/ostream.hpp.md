---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/NTL_1_E.test.cpp
    title: test/aizu-online-judge/NTL_1_E.test.cpp
  - icon: ':x:'
    path: test/library-checker/suffix_array.test.cpp
    title: test/library-checker/suffix_array.test.cpp
  - icon: ':x:'
    path: test/library-checker/zalgorithm.test.cpp
    title: test/library-checker/zalgorithm.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    document_title: Output Stream
    links: []
  bundledCode: "#line 2 \"src/utils/io/ostream.hpp\"\n\n/*\n * @file ostream.hpp\n\
    \ * @brief Output Stream\n */\n\n#include <iostream>\n#include <tuple>\n\nnamespace\
    \ workspace {\n\ntemplate <class T, class U>\nstd::ostream &operator<<(std::ostream\
    \ &os, const std::pair<T, U> &p) {\n  return os << p.first << ' ' << p.second;\n\
    }\ntemplate <class tuple_t, size_t index> struct tuple_os {\n  static std::ostream\
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
    \ = 0 : (os << ' ', 0), os << e;\n  return os;\n}\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/*\n * @file ostream.hpp\n * @brief Output Stream\n */\n\n\
    #include <iostream>\n#include <tuple>\n\nnamespace workspace {\n\ntemplate <class\
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
    \ = 0 : (os << ' ', 0), os << e;\n  return os;\n}\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/utils/io/ostream.hpp
  requiredBy: []
  timestamp: '2020-11-23 02:53:42+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/library-checker/zalgorithm.test.cpp
  - test/library-checker/suffix_array.test.cpp
  - test/aizu-online-judge/NTL_1_E.test.cpp
documentation_of: src/utils/io/ostream.hpp
layout: document
redirect_from:
- /library/src/utils/io/ostream.hpp
- /library/src/utils/io/ostream.hpp.html
title: Output Stream
---
