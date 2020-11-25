---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: src/string/z_algorithm.hpp
    title: Z-Algorithm
  - icon: ':question:'
    path: src/utils/io/ostream.hpp
    title: Output Stream
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/zalgorithm
    links:
    - https://judge.yosupo.jp/problem/zalgorithm
  bundledCode: "#line 1 \"test/library-checker/zalgorithm.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/zalgorithm\"\n\n#line 2 \"src/string/z_algorithm.hpp\"\
    \n\n/*\n * @file z_algorith.hpp\n * @brief Z-Algorithm\n */\n\n#include <string>\n\
    #include <vector>\n\nnamespace workspace {\n\n/*\n * @class z_algorithm\n * @brief\
    \ construct Z-array in linear time.\n * @tparam str_type the type of string\n\
    \ */\ntemplate <class str_type = std::string> class z_algorithm {\n  str_type\
    \ key;\n  std::vector<size_t> z;\n\n  void make() {\n    if (z.empty()) return;\n\
    \    for (size_t i{1}, j{0}; i != size(); ++i) {\n      if (z[i - j] + i < z[j]\
    \ + j) {\n        z[i] = z[i - j];\n      } else {\n        size_t k{z[j] + j\
    \ > i ? z[j] + j - i : 0};\n        while (k + i < size() && key[k] == key[k +\
    \ i]) ++k;\n        z[i] = k;\n        j = i;\n      }\n    }\n    z.front() =\
    \ size();\n  }\n\n public:\n  z_algorithm(const str_type &key) : key(key), z(size())\
    \ { make(); }\n\n  std::vector<size_t>::const_iterator begin() const { return\
    \ z.begin(); }\n\n  std::vector<size_t>::const_iterator end() const { return z.end();\
    \ }\n\n  /*\n   * @fn size\n   * @return length of the string\n   */\n  size_t\
    \ size() const { return key.size(); }\n\n  /*\n   * @fn operator[]\n   * @param\
    \ i index\n   * @return LCP of (i)-th suffix and the whole string\n   */\n  size_t\
    \ operator[](size_t i) const {\n    assert(i < size());\n    return z[i];\n  }\n\
    \n  /*\n   * @fn pattern_search\n   * @param str\n   * @return length of the string\n\
    \   */\n  std::vector<size_t> pattern_search(const str_type &str) const {\n  \
    \  str_type ccat(key);\n    ccat.insert(end(ccat), begin(str), end(str));\n  \
    \  z_algorithm z(ccat);\n    std::vector<size_t> res(z.begin() + size(), z.end());\n\
    \    for (size_t &x : res)\n      if (x > size()) x = size();\n    return res;\n\
    \  }\n};\n\n}  // namespace workspace\n#line 2 \"src/utils/io/ostream.hpp\"\n\n\
    /*\n * @file ostream.hpp\n * @brief Output Stream\n */\n\n#include <iostream>\n\
    #include <tuple>\n\nnamespace workspace {\n\ntemplate <class T, class U>\nstd::ostream\
    \ &operator<<(std::ostream &os, const std::pair<T, U> &p) {\n  return os << p.first\
    \ << ' ' << p.second;\n}\ntemplate <class tuple_t, size_t index> struct tuple_os\
    \ {\n  static std::ostream &apply(std::ostream &os, const tuple_t &t) {\n    tuple_os<tuple_t,\
    \ index - 1>::apply(os, t);\n    return os << ' ' << std::get<index>(t);\n  }\n\
    };\ntemplate <class tuple_t> struct tuple_os<tuple_t, 0> {\n  static std::ostream\
    \ &apply(std::ostream &os, const tuple_t &t) {\n    return os << std::get<0>(t);\n\
    \  }\n};\ntemplate <class tuple_t> struct tuple_os<tuple_t, SIZE_MAX> {\n  static\
    \ std::ostream &apply(std::ostream &os, const tuple_t &t) { return os; }\n};\n\
    \ntemplate <class... T>\nstd::ostream &operator<<(std::ostream &os, const std::tuple<T...>\
    \ &t) {\n  return tuple_os<std::tuple<T...>,\n                  std::tuple_size<std::tuple<T...>>::value\
    \ - 1>::apply(os, t);\n}\n\ntemplate <class Container,\n          typename = decltype(std::begin(std::declval<Container>()))>\n\
    typename std::enable_if<\n    !std::is_same<typename std::decay<Container>::type,\
    \ std::string>::value &&\n        !std::is_same<typename std::decay<Container>::type,\
    \ char *>::value,\n    std::ostream &>::type\noperator<<(std::ostream &os, const\
    \ Container &cont) {\n  bool head = true;\n  for (auto &&e : cont) head ? head\
    \ = 0 : (os << ' ', 0), os << e;\n  return os;\n}\n\n}  // namespace workspace\n\
    #line 5 \"test/library-checker/zalgorithm.test.cpp\"\n\nint main() {\n  std::string\
    \ s;\n  std::cin >> s;\n  workspace::z_algorithm z(s);\n  std::cout << z << \"\
    \\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/zalgorithm\"\n\n#include\
    \ \"src/string/z_algorithm.hpp\"\n#include \"src/utils/io/ostream.hpp\"\n\nint\
    \ main() {\n  std::string s;\n  std::cin >> s;\n  workspace::z_algorithm z(s);\n\
    \  std::cout << z << \"\\n\";\n}\n"
  dependsOn:
  - src/string/z_algorithm.hpp
  - src/utils/io/ostream.hpp
  isVerificationFile: true
  path: test/library-checker/zalgorithm.test.cpp
  requiredBy: []
  timestamp: '2020-11-23 02:53:42+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/library-checker/zalgorithm.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/zalgorithm.test.cpp
- /verify/test/library-checker/zalgorithm.test.cpp.html
title: test/library-checker/zalgorithm.test.cpp
---
