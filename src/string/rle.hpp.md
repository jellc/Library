---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Run-length Encoding
    links: []
  bundledCode: "#line 2 \"src/string/rle.hpp\"\n\n/**\n * @file rle.hpp\n * @brief\
    \ Run-length Encoding\n */\n\n#include <vector>\n\nnamespace workspace {\n\ntemplate\
    \ <class _Iterator>\nauto run_length_encoding(_Iterator __first, _Iterator __last)\
    \ {\n  std::vector<std::pair<typename std::iterator_traits<_Iterator>::value_type,\n\
    \                        std::size_t>>\n      __rle;\n\n  while (__first != __last)\n\
    \    for (__rle.emplace_back(*__first, 0);\n         __first != __last && __rle.back().first\
    \ == *__first; ++__first)\n      ++__rle.back().second;\n\n  return __rle;\n}\n\
    \n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file rle.hpp\n * @brief Run-length Encoding\n */\n\
    \n#include <vector>\n\nnamespace workspace {\n\ntemplate <class _Iterator>\nauto\
    \ run_length_encoding(_Iterator __first, _Iterator __last) {\n  std::vector<std::pair<typename\
    \ std::iterator_traits<_Iterator>::value_type,\n                        std::size_t>>\n\
    \      __rle;\n\n  while (__first != __last)\n    for (__rle.emplace_back(*__first,\
    \ 0);\n         __first != __last && __rle.back().first == *__first; ++__first)\n\
    \      ++__rle.back().second;\n\n  return __rle;\n}\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/string/rle.hpp
  requiredBy: []
  timestamp: '2021-04-23 00:08:06+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/string/rle.hpp
layout: document
redirect_from:
- /library/src/string/rle.hpp
- /library/src/string/rle.hpp.html
title: Run-length Encoding
---
