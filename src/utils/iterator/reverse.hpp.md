---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: src/utils/py-like/enumerate.hpp
    title: Enumerate
  - icon: ':warning:'
    path: src/utils/py-like/range.hpp
    title: Range
  - icon: ':heavy_check_mark:'
    path: src/utils/py-like/zip.hpp
    title: Zip
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/library-checker/number_of_substrings.test.cpp
    title: test/library-checker/number_of_substrings.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Reverse Iterator
    links:
    - http://gcc.gnu.org/PR51823
  bundledCode: "#line 2 \"src/utils/iterator/reverse.hpp\"\n\n/*\n * @file reverse_iterator.hpp\n\
    \ * @brief Reverse Iterator\n */\n\n#if __cplusplus >= 201703L\n\n#include <iterator>\n\
    #include <optional>\n\nnamespace workspace {\n\n/*\n * @class reverse_iterator\n\
    \ * @brief Wrapper class for `std::reverse_iterator`.\n * @see http://gcc.gnu.org/PR51823\n\
    \ */\ntemplate <class Iterator>\nclass reverse_iterator : public std::reverse_iterator<Iterator>\
    \ {\n  using base_std = std::reverse_iterator<Iterator>;\n  std::optional<typename\
    \ base_std::value_type> deref;\n\n public:\n  using base_std::reverse_iterator;\n\
    \n  constexpr typename base_std::reference operator*() noexcept {\n    if (!deref)\
    \ {\n      Iterator tmp = base_std::current;\n      deref = *--tmp;\n    }\n \
    \   return deref.value();\n  }\n\n  constexpr reverse_iterator &operator++() noexcept\
    \ {\n    base_std::operator++();\n    deref.reset();\n    return *this;\n  }\n\
    \  constexpr reverse_iterator &operator--() noexcept {\n    base_std::operator++();\n\
    \    deref.reset();\n    return *this;\n  }\n  constexpr reverse_iterator operator++(int)\
    \ noexcept {\n    base_std::operator++();\n    deref.reset();\n    return *this;\n\
    \  }\n  constexpr reverse_iterator operator--(int) noexcept {\n    base_std::operator++();\n\
    \    deref.reset();\n    return *this;\n  }\n};\n\n}  // namespace workspace\n\
    \n#endif\n"
  code: "#pragma once\n\n/*\n * @file reverse_iterator.hpp\n * @brief Reverse Iterator\n\
    \ */\n\n#if __cplusplus >= 201703L\n\n#include <iterator>\n#include <optional>\n\
    \nnamespace workspace {\n\n/*\n * @class reverse_iterator\n * @brief Wrapper class\
    \ for `std::reverse_iterator`.\n * @see http://gcc.gnu.org/PR51823\n */\ntemplate\
    \ <class Iterator>\nclass reverse_iterator : public std::reverse_iterator<Iterator>\
    \ {\n  using base_std = std::reverse_iterator<Iterator>;\n  std::optional<typename\
    \ base_std::value_type> deref;\n\n public:\n  using base_std::reverse_iterator;\n\
    \n  constexpr typename base_std::reference operator*() noexcept {\n    if (!deref)\
    \ {\n      Iterator tmp = base_std::current;\n      deref = *--tmp;\n    }\n \
    \   return deref.value();\n  }\n\n  constexpr reverse_iterator &operator++() noexcept\
    \ {\n    base_std::operator++();\n    deref.reset();\n    return *this;\n  }\n\
    \  constexpr reverse_iterator &operator--() noexcept {\n    base_std::operator++();\n\
    \    deref.reset();\n    return *this;\n  }\n  constexpr reverse_iterator operator++(int)\
    \ noexcept {\n    base_std::operator++();\n    deref.reset();\n    return *this;\n\
    \  }\n  constexpr reverse_iterator operator--(int) noexcept {\n    base_std::operator++();\n\
    \    deref.reset();\n    return *this;\n  }\n};\n\n}  // namespace workspace\n\
    \n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: src/utils/iterator/reverse.hpp
  requiredBy:
  - src/utils/py-like/zip.hpp
  - src/utils/py-like/range.hpp
  - src/utils/py-like/enumerate.hpp
  timestamp: '2020-12-05 12:12:40+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/number_of_substrings.test.cpp
documentation_of: src/utils/iterator/reverse.hpp
layout: document
redirect_from:
- /library/src/utils/iterator/reverse.hpp
- /library/src/utils/iterator/reverse.hpp.html
title: Reverse Iterator
---
