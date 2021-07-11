---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Inversion
    links: []
  bundledCode: "#line 2 \"src/misc/inversion.hpp\"\n\n/**\n * @file inversion.hpp\n\
    \ * @brief Inversion\n */\n\n#include <algorithm>\n#include <vector>\n\nnamespace\
    \ workspace {\n\ntemplate <class _Iterator>\nauto left_inversion(_Iterator __first,\
    \ _Iterator __last) noexcept {\n  std::vector<typename std::iterator_traits<_Iterator>::value_type>\
    \ __v(__first,\n                                                             \
    \           __last);\n  std::sort(__v.begin(), __v.end(), greater<void>{});\n\
    \  std::vector<size_t> __inv, __sum(__v.size() + 1);\n  while (__first != __last)\
    \ {\n    auto& __c = __inv.emplace_back();\n    size_t __e = std::distance(\n\
    \        __v.begin(),\n        std::lower_bound(__v.begin(), __v.end(), *__first++,\
    \ greater<void>{}));\n    for (auto __i = ++__e; __i; __i &= __i - 1) __c += __sum[__i];\n\
    \    for (; __e < __sum.size(); __e += __e & -__e) ++__sum[__e];\n  }\n  return\
    \ __inv;\n}\n\ntemplate <class _Iterator>\nauto right_inversion(_Iterator __first,\
    \ _Iterator __last) noexcept {\n  std::vector<typename std::iterator_traits<_Iterator>::value_type>\
    \ __v(__first,\n                                                             \
    \           __last);\n  std::sort(__v.begin(), __v.end());\n  std::vector<size_t>\
    \ __inv, __sum(__v.size() + 1);\n  while (__first != __last) {\n    auto& __c\
    \ = __inv.emplace_back();\n    size_t __e = std::distance(\n        __v.begin(),\
    \ std::lower_bound(__v.begin(), __v.end(), *--__last));\n    for (auto __i = ++__e;\
    \ __i; __i &= __i - 1) __c += __sum[__i];\n    for (; __e < __sum.size(); __e\
    \ += __e & -__e) ++__sum[__e];\n  }\n  std::reverse(__inv.begin(), __inv.end());\n\
    \  return __inv;\n}\n\ntemplate <class _Iterator>\nauto inversion(_Iterator __first,\
    \ _Iterator __last) noexcept {\n  size_t __res = 0;\n  for (auto __x : left_inversion(__first,\
    \ __last)) __res += __x;\n  return __res;\n}\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file inversion.hpp\n * @brief Inversion\n */\n\n\
    #include <algorithm>\n#include <vector>\n\nnamespace workspace {\n\ntemplate <class\
    \ _Iterator>\nauto left_inversion(_Iterator __first, _Iterator __last) noexcept\
    \ {\n  std::vector<typename std::iterator_traits<_Iterator>::value_type> __v(__first,\n\
    \                                                                        __last);\n\
    \  std::sort(__v.begin(), __v.end(), greater<void>{});\n  std::vector<size_t>\
    \ __inv, __sum(__v.size() + 1);\n  while (__first != __last) {\n    auto& __c\
    \ = __inv.emplace_back();\n    size_t __e = std::distance(\n        __v.begin(),\n\
    \        std::lower_bound(__v.begin(), __v.end(), *__first++, greater<void>{}));\n\
    \    for (auto __i = ++__e; __i; __i &= __i - 1) __c += __sum[__i];\n    for (;\
    \ __e < __sum.size(); __e += __e & -__e) ++__sum[__e];\n  }\n  return __inv;\n\
    }\n\ntemplate <class _Iterator>\nauto right_inversion(_Iterator __first, _Iterator\
    \ __last) noexcept {\n  std::vector<typename std::iterator_traits<_Iterator>::value_type>\
    \ __v(__first,\n                                                             \
    \           __last);\n  std::sort(__v.begin(), __v.end());\n  std::vector<size_t>\
    \ __inv, __sum(__v.size() + 1);\n  while (__first != __last) {\n    auto& __c\
    \ = __inv.emplace_back();\n    size_t __e = std::distance(\n        __v.begin(),\
    \ std::lower_bound(__v.begin(), __v.end(), *--__last));\n    for (auto __i = ++__e;\
    \ __i; __i &= __i - 1) __c += __sum[__i];\n    for (; __e < __sum.size(); __e\
    \ += __e & -__e) ++__sum[__e];\n  }\n  std::reverse(__inv.begin(), __inv.end());\n\
    \  return __inv;\n}\n\ntemplate <class _Iterator>\nauto inversion(_Iterator __first,\
    \ _Iterator __last) noexcept {\n  size_t __res = 0;\n  for (auto __x : left_inversion(__first,\
    \ __last)) __res += __x;\n  return __res;\n}\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/misc/inversion.hpp
  requiredBy: []
  timestamp: '2021-07-11 22:33:28+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/misc/inversion.hpp
layout: document
redirect_from:
- /library/src/misc/inversion.hpp
- /library/src/misc/inversion.hpp.html
title: Inversion
---
