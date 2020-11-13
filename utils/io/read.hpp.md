---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: template.cpp
    title: Template
  - icon: ':warning:'
    path: utils.hpp
    title: utils.hpp
  - icon: ':heavy_check_mark:'
    path: utils/io.hpp
    title: utils/io.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/aors_score.test.cpp
    title: test/aizu-online-judge/aors_score.test.cpp
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
  bundledCode: "#line 2 \"utils/io/read.hpp\"\n#include <iostream>\nnamespace workspace\
    \ {\n// read with std::cin.\ntemplate <class T = void>\nstruct read\n{\n    typename\
    \ std::remove_const<T>::type value;\n    template <class... types>\n    read(types...\
    \ args) : value(args...) { std::cin >> value; }\n    operator T() const { return\
    \ value; }\n};\ntemplate <>\nstruct read<void>\n{\n    template <class T>\n  \
    \  operator T() const { T value; std::cin >> value; return value; }\n};\n} //\
    \ namespace workspace\n"
  code: "#pragma once\n#include <iostream>\nnamespace workspace {\n// read with std::cin.\n\
    template <class T = void>\nstruct read\n{\n    typename std::remove_const<T>::type\
    \ value;\n    template <class... types>\n    read(types... args) : value(args...)\
    \ { std::cin >> value; }\n    operator T() const { return value; }\n};\ntemplate\
    \ <>\nstruct read<void>\n{\n    template <class T>\n    operator T() const { T\
    \ value; std::cin >> value; return value; }\n};\n} // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: utils/io/read.hpp
  requiredBy:
  - template.cpp
  - utils.hpp
  - utils/io.hpp
  timestamp: '2020-11-14 01:28:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/zalgorithm.test.cpp
  - test/library-checker/suffix_array.test.cpp
  - test/aizu-online-judge/aors_score.test.cpp
  - test/aizu-online-judge/range_minimum_query.test.cpp
  - test/aizu-online-judge/pattern_search.test.cpp
  - test/aizu-online-judge/extended_euclid_algorithm.test.cpp
  - test/aizu-online-judge/do_use_segment_tree.test.cpp
documentation_of: utils/io/read.hpp
layout: document
redirect_from:
- /library/utils/io/read.hpp
- /library/utils/io/read.hpp.html
title: utils/io/read.hpp
---
