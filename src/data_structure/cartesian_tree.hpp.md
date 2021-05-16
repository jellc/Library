---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Cartesian Tree
    links: []
  bundledCode: "#line 2 \"src/data_structure/cartesian_tree.hpp\"\n\n/**\n * @file\
    \ cartesian_tree.hpp\n * @brief Cartesian Tree\n */\n\n#include <vector>\n\nnamespace\
    \ workspace {\n\n/**\n * @brief Cartesian Tree.\n */\ntemplate <class _Iterator>\n\
    auto Cartesian_tree(_Iterator __first, _Iterator __last) noexcept {\n  std::vector<std::size_t>\
    \ __p;\n  std::vector<_Iterator> __it;\n\n  for (std::size_t __i = 0, __j = -1;\
    \ __first != __last;\n       __p.emplace_back(__j), __j = __i++, __it.emplace_back(__first++))\
    \ {\n    std::size_t __k = -1;\n    while (~__j && *__first < *__it[__j]) __k\
    \ = __j, __j = __p[__j];\n    if (~__k) __p[__k] = __i;\n  }\n\n  return __p;\n\
    }\n\n/**\n * @brief Cartesian Tree.\n */\ntemplate <class _Iterator, class _Compare>\n\
    auto Cartesian_tree(_Iterator __first, _Iterator __last,\n                   \
    \ _Compare __comp) noexcept {\n  std::vector<std::size_t> __p;\n  std::vector<_Iterator>\
    \ __it;\n\n  for (std::size_t __i = 0, __j = -1; __first != __last;\n       __p.emplace_back(__j),\
    \ __j = __i++, __it.emplace_back(__first++)) {\n    std::size_t __k = -1;\n  \
    \  while (~__j && __comp(*__first, *__it[__j])) __k = __j, __j = __p[__j];\n \
    \   if (~__k) __p[__k] = __i;\n  }\n\n  return __p;\n}\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file cartesian_tree.hpp\n * @brief Cartesian Tree\n\
    \ */\n\n#include <vector>\n\nnamespace workspace {\n\n/**\n * @brief Cartesian\
    \ Tree.\n */\ntemplate <class _Iterator>\nauto Cartesian_tree(_Iterator __first,\
    \ _Iterator __last) noexcept {\n  std::vector<std::size_t> __p;\n  std::vector<_Iterator>\
    \ __it;\n\n  for (std::size_t __i = 0, __j = -1; __first != __last;\n       __p.emplace_back(__j),\
    \ __j = __i++, __it.emplace_back(__first++)) {\n    std::size_t __k = -1;\n  \
    \  while (~__j && *__first < *__it[__j]) __k = __j, __j = __p[__j];\n    if (~__k)\
    \ __p[__k] = __i;\n  }\n\n  return __p;\n}\n\n/**\n * @brief Cartesian Tree.\n\
    \ */\ntemplate <class _Iterator, class _Compare>\nauto Cartesian_tree(_Iterator\
    \ __first, _Iterator __last,\n                    _Compare __comp) noexcept {\n\
    \  std::vector<std::size_t> __p;\n  std::vector<_Iterator> __it;\n\n  for (std::size_t\
    \ __i = 0, __j = -1; __first != __last;\n       __p.emplace_back(__j), __j = __i++,\
    \ __it.emplace_back(__first++)) {\n    std::size_t __k = -1;\n    while (~__j\
    \ && __comp(*__first, *__it[__j])) __k = __j, __j = __p[__j];\n    if (~__k) __p[__k]\
    \ = __i;\n  }\n\n  return __p;\n}\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/data_structure/cartesian_tree.hpp
  requiredBy: []
  timestamp: '2021-05-16 13:40:13+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/data_structure/cartesian_tree.hpp
layout: document
redirect_from:
- /library/src/data_structure/cartesian_tree.hpp
- /library/src/data_structure/cartesian_tree.hpp.html
title: Cartesian Tree
---
