---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Boyer-Moore Majority Vote Algorithm
    links: []
  bundledCode: "#line 2 \"src/misc/majority_vote.hpp\"\n\n/**\n * @file majority_vote.hpp\n\
    \ * @brief Boyer-Moore Majority Vote Algorithm\n */\n\n#include <algorithm>\n\
    #include <cassert>\n#include <vector>\n\nnamespace workspace {\n\n/**\n * @brief\
    \ Boyer-Moore majority vote algorithm.\n * @return Elements which appears at least\
    \ k times in given range.\n */\ntemplate <class _Iterator>\nauto majority_vote(_Iterator\
    \ __first, _Iterator __last, size_t __k) {\n  assert(__k);\n\n  using value_type\
    \ = typename std::iterator_traits<_Iterator>::value_type;\n\n  struct pile {\n\
    \    value_type value;\n    size_t count;\n    operator value_type() const { return\
    \ value; }\n  };\n\n  std::vector<pile> __piles;\n  size_t __max = std::distance(__first,\
    \ __last) / __k;\n\n  for (auto __it = __first; __it != __last; ++__it) {\n  \
    \  bool __exist = false;\n\n    for (auto &__x : __piles)\n      if (__x.value\
    \ == *__it) {\n        ++__x.count, __exist = true;\n        break;\n      }\n\
    \n    if (__exist) continue;\n\n    if (__piles.size() < __max)\n      __piles.push_back({*__it,\
    \ 1});\n\n    else {\n      for (auto &__x : __piles) __x.count -= 1;\n      __piles.erase(std::remove_if(__piles.begin(),\
    \ __piles.end(),\n                                   [](const auto &__x) { return\
    \ !__x.count; }),\n                    __piles.end());\n    }\n  }\n\n  for (auto\
    \ &&__x : __piles) __x.count = 0;\n\n  while (__first != __last) {\n    for (auto\
    \ &__x : __piles)\n      if (__x.value == *__first) {\n        ++__x.count;\n\
    \        break;\n      }\n    ++__first;\n  }\n\n  __piles.erase(\n      std::remove_if(__piles.begin(),\
    \ __piles.end(),\n                     [&](const auto &__x) { return __x.count\
    \ < __k; }),\n      __piles.end());\n\n  return __piles;\n}\n\n}  // namespace\
    \ workspace\n"
  code: "#pragma once\n\n/**\n * @file majority_vote.hpp\n * @brief Boyer-Moore Majority\
    \ Vote Algorithm\n */\n\n#include <algorithm>\n#include <cassert>\n#include <vector>\n\
    \nnamespace workspace {\n\n/**\n * @brief Boyer-Moore majority vote algorithm.\n\
    \ * @return Elements which appears at least k times in given range.\n */\ntemplate\
    \ <class _Iterator>\nauto majority_vote(_Iterator __first, _Iterator __last, size_t\
    \ __k) {\n  assert(__k);\n\n  using value_type = typename std::iterator_traits<_Iterator>::value_type;\n\
    \n  struct pile {\n    value_type value;\n    size_t count;\n    operator value_type()\
    \ const { return value; }\n  };\n\n  std::vector<pile> __piles;\n  size_t __max\
    \ = std::distance(__first, __last) / __k;\n\n  for (auto __it = __first; __it\
    \ != __last; ++__it) {\n    bool __exist = false;\n\n    for (auto &__x : __piles)\n\
    \      if (__x.value == *__it) {\n        ++__x.count, __exist = true;\n     \
    \   break;\n      }\n\n    if (__exist) continue;\n\n    if (__piles.size() <\
    \ __max)\n      __piles.push_back({*__it, 1});\n\n    else {\n      for (auto\
    \ &__x : __piles) __x.count -= 1;\n      __piles.erase(std::remove_if(__piles.begin(),\
    \ __piles.end(),\n                                   [](const auto &__x) { return\
    \ !__x.count; }),\n                    __piles.end());\n    }\n  }\n\n  for (auto\
    \ &&__x : __piles) __x.count = 0;\n\n  while (__first != __last) {\n    for (auto\
    \ &__x : __piles)\n      if (__x.value == *__first) {\n        ++__x.count;\n\
    \        break;\n      }\n    ++__first;\n  }\n\n  __piles.erase(\n      std::remove_if(__piles.begin(),\
    \ __piles.end(),\n                     [&](const auto &__x) { return __x.count\
    \ < __k; }),\n      __piles.end());\n\n  return __piles;\n}\n\n}  // namespace\
    \ workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/misc/majority_vote.hpp
  requiredBy: []
  timestamp: '2021-07-11 22:33:28+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/misc/majority_vote.hpp
layout: document
redirect_from:
- /library/src/misc/majority_vote.hpp
- /library/src/misc/majority_vote.hpp.html
title: Boyer-Moore Majority Vote Algorithm
---
