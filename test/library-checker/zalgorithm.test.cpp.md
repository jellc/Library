---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/string/z_algorithm.hpp
    title: Z-Algorithm
  - icon: ':heavy_check_mark:'
    path: src/utils/io/ostream.hpp
    title: Output Stream
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/zalgorithm
    links:
    - https://judge.yosupo.jp/problem/zalgorithm
  bundledCode: "#line 1 \"test/library-checker/zalgorithm.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/zalgorithm\"\n\n#line 2 \"src/string/z_algorithm.hpp\"\
    \n\n/**\n * @file z_algorithm.hpp\n * @brief Z-Algorithm\n * @date 2021-01-08\n\
    \ */\n\n#include <string>\n#include <vector>\n\nnamespace workspace {\n\n/**\n\
    \ * @brief Construct Z-array in linear time.\n * @param __s A string\n * @return\
    \ The i-th element (0-indexed) is the length of the Longest Common\n * Prefix\
    \ between __s and __s[i:].\n */\ntemplate <class _Str> std::vector<size_t> z_algorithm(_Str\
    \ const &__s) {\n  std::vector<size_t> __z(__s.size());\n  if (!__z.empty()) {\n\
    \    for (size_t __i{1}, __j{0}; __i != __s.size(); ++__i) {\n      if (__z[__i\
    \ - __j] + __i < __z[__j] + __j) {\n        __z[__i] = __z[__i - __j];\n     \
    \ } else {\n        size_t __k{__z[__j] + __j > __i ? __z[__j] + __j - __i : 0};\n\
    \        while (__k + __i < __s.size() && __s[__k] == __s[__k + __i]) ++__k;\n\
    \        __z[__i] = __k;\n        __j = __i;\n      }\n    }\n    __z.front()\
    \ = __s.size();\n  }\n  return __z;\n}\n\n}  // namespace workspace\n#line 2 \"\
    src/utils/io/ostream.hpp\"\n\n/*\n * @file ostream.hpp\n * @brief Output Stream\n\
    \ */\n\n#include <iostream>\n#include <tuple>\n\nnamespace workspace {\n\ntemplate\
    \ <class T, class U>\nstd::ostream &operator<<(std::ostream &os, const std::pair<T,\
    \ U> &p) {\n  return os << p.first << ' ' << p.second;\n}\ntemplate <class tuple_t,\
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
    #line 5 \"test/library-checker/zalgorithm.test.cpp\"\n\nint main() {\n  using\
    \ namespace workspace;\n  std::string s;\n  std::cin >> s;\n  std::cout << z_algorithm(s)\
    \ << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/zalgorithm\"\n\n#include\
    \ \"src/string/z_algorithm.hpp\"\n#include \"src/utils/io/ostream.hpp\"\n\nint\
    \ main() {\n  using namespace workspace;\n  std::string s;\n  std::cin >> s;\n\
    \  std::cout << z_algorithm(s) << \"\\n\";\n}\n"
  dependsOn:
  - src/string/z_algorithm.hpp
  - src/utils/io/ostream.hpp
  isVerificationFile: true
  path: test/library-checker/zalgorithm.test.cpp
  requiredBy: []
  timestamp: '2021-01-08 22:31:47+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/library-checker/zalgorithm.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/zalgorithm.test.cpp
- /verify/test/library-checker/zalgorithm.test.cpp.html
title: test/library-checker/zalgorithm.test.cpp
---
