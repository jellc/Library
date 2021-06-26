---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: src/utils/py-like/enumerate.hpp
    title: Enumerate
  - icon: ':heavy_check_mark:'
    path: src/utils/py-like/zip.hpp
    title: Zip
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/library-checker/number_of_substrings.test.cpp
    title: test/library-checker/number_of_substrings.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Iterator Category
    links: []
  bundledCode: "#line 2 \"src/utils/iterator/category.hpp\"\n\n/*\n * @file category.hpp\n\
    \ * @brief Iterator Category\n */\n\n#include <cstddef>\n#include <tuple>\n\n\
    namespace workspace {\n\n/*\n * @tparam Tuple Tuple of iterator types\n */\ntemplate\
    \ <class Tuple, size_t N = std::tuple_size<Tuple>::value - 1>\nstruct common_iterator_category\
    \ {\n  using type = typename std::common_type<\n      typename common_iterator_category<Tuple,\
    \ N - 1>::type,\n      typename std::iterator_traits<typename std::tuple_element<\n\
    \          N, Tuple>::type>::iterator_category>::type;\n};\n\ntemplate <class\
    \ Tuple> struct common_iterator_category<Tuple, 0> {\n  using type = typename\
    \ std::iterator_traits<\n      typename std::tuple_element<0, Tuple>::type>::iterator_category;\n\
    };\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/*\n * @file category.hpp\n * @brief Iterator Category\n\
    \ */\n\n#include <cstddef>\n#include <tuple>\n\nnamespace workspace {\n\n/*\n\
    \ * @tparam Tuple Tuple of iterator types\n */\ntemplate <class Tuple, size_t\
    \ N = std::tuple_size<Tuple>::value - 1>\nstruct common_iterator_category {\n\
    \  using type = typename std::common_type<\n      typename common_iterator_category<Tuple,\
    \ N - 1>::type,\n      typename std::iterator_traits<typename std::tuple_element<\n\
    \          N, Tuple>::type>::iterator_category>::type;\n};\n\ntemplate <class\
    \ Tuple> struct common_iterator_category<Tuple, 0> {\n  using type = typename\
    \ std::iterator_traits<\n      typename std::tuple_element<0, Tuple>::type>::iterator_category;\n\
    };\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/utils/iterator/category.hpp
  requiredBy:
  - src/utils/py-like/enumerate.hpp
  - src/utils/py-like/zip.hpp
  timestamp: '2020-12-04 21:34:12+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/number_of_substrings.test.cpp
documentation_of: src/utils/iterator/category.hpp
layout: document
redirect_from:
- /library/src/utils/iterator/category.hpp
- /library/src/utils/iterator/category.hpp.html
title: Iterator Category
---
