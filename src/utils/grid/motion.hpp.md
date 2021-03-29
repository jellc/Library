---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Motion
    links: []
  bundledCode: "#line 2 \"src/utils/grid/motion.hpp\"\n\n/**\n * @file motion.hpp\n\
    \ * @brief Motion\n */\n\n#include <algorithm>\n\nnamespace workspace {\n\n/**\n\
    \ * @brief Transpose.\n *\n * @param __grid\n */\ntemplate <class _Grid, typename\
    \ = decltype(std::declval<std::decay_t< _Grid>>()[0].resize(0))>\nconstexpr decltype(auto)\
    \ transpose(_Grid &&__grid) {\n  auto __h = std::size(__grid), __w = std::size(__grid[0]);\n\
    \n  std::decay_t<_Grid> __t(__w);\n  for (auto &&__r : __t) __r.resize(__h);\n\
    \n  using reference = decltype(__grid[0][0]);\n\n  for (size_t __i = 0; __i !=\
    \ __h; ++__i)\n    for (size_t __j = 0; __j != __w; ++__j)\n      __t[__j][__i]\
    \ = std::forward<reference>(__grid[__i][__j]);\n\n  return __t;\n}\n\n/**\n *\
    \ @brief Transpose.\n *\n * @param __grid\n */\ntemplate <class _Tp, size_t _Rows,\
    \ size_t _Cols>\nconstexpr decltype(auto) transpose(const _Tp (&__grid)[_Rows][_Cols])\
    \ {\n  std::array<std::array<_Tp, _Rows>, _Cols> __t;\n\n  for (size_t __i = 0;\
    \ __i != _Rows; ++__i)\n    for (size_t __j = 0; __j != _Cols; ++__j) __t[__j][__i]\
    \ = __grid[__i][__j];\n\n  return __t;\n}\n\n/**\n * @brief Transpose.\n *\n *\
    \ @param __grid\n */\ntemplate <class _Tp, size_t _Rows, size_t _Cols>\nconstexpr\
    \ decltype(auto) transpose(_Tp(&&__grid)[_Rows][_Cols]) {\n  std::array<std::array<_Tp,\
    \ _Rows>, _Cols> __t;\n\n  for (size_t __i = 0; __i != _Rows; ++__i)\n    for\
    \ (size_t __j = 0; __j != _Cols; ++__j)\n      __t[__j][__i] = std::move(__grid[__i][__j]);\n\
    \n  return __t;\n}\n\n/**\n * @brief Transpose.\n *\n * @param __grid\n */\ntemplate\
    \ <class _Tp, size_t _Rows, size_t _Cols>\nconstexpr decltype(auto) transpose(\n\
    \    const std::array<std::array<_Tp, _Cols>, _Rows> &__grid) {\n  std::array<std::array<_Tp,\
    \ _Rows>, _Cols> __t;\n\n  for (size_t __i = 0; __i != _Rows; ++__i)\n    for\
    \ (size_t __j = 0; __j != _Cols; ++__j) __t[__j][__i] = __grid[__i][__j];\n\n\
    \  return __t;\n}\n\n/**\n * @brief Transpose.\n *\n * @param __grid\n */\ntemplate\
    \ <class _Tp, size_t _Rows, size_t _Cols>\nconstexpr decltype(auto) transpose(\n\
    \    std::array<std::array<_Tp, _Cols>, _Rows> &&__grid) {\n  std::array<std::array<_Tp,\
    \ _Rows>, _Cols> __t;\n\n  for (size_t __i = 0; __i != _Rows; ++__i)\n    for\
    \ (size_t __j = 0; __j != _Cols; ++__j)\n      __t[__j][__i] = std::move(__grid[__i][__j]);\n\
    \n  return __t;\n}\n\n/**\n * @brief Roll the grid counter-clockwise.\n *\n *\
    \ @param __grid\n * @return\n */\ntemplate <class _Grid> decltype(auto) roll_ccw(const\
    \ _Grid &__grid) {\n  auto __t = transpose(__grid);\n  std::reverse(std::begin(__t),\
    \ std::end(__t));\n  return __t;\n}\n\n/**\n * @brief Roll the grid counter-clockwise.\n\
    \ *\n * @param __grid\n * @return\n */\ntemplate <class _Grid> decltype(auto)\
    \ roll_ccw(_Grid &&__grid) {\n  auto __t = transpose(std::move(__grid));\n  std::reverse(std::begin(__t),\
    \ std::end(__t));\n  return __t;\n}\n\n/**\n * @brief Roll the grid clockwise.\n\
    \ *\n * @param __grid\n * @return\n */\ntemplate <class _Grid> decltype(auto)\
    \ roll_cw(const _Grid &__grid) {\n  auto __t = transpose(__grid);\n  for (auto\
    \ &&__r : __t) std::reverse(std::begin(__r), std::end(__r));\n  return __t;\n\
    }\n\n/**\n * @brief Roll the grid clockwise.\n *\n * @param __grid\n * @return\n\
    \ */\ntemplate <class _Grid> decltype(auto) roll_cw(_Grid &&__grid) {\n  std::reverse(std::begin(__grid),\
    \ std::end(__grid));\n  return transpose(std::move(__grid));\n}\n\n}  // namespace\
    \ workspace\n"
  code: "#pragma once\n\n/**\n * @file motion.hpp\n * @brief Motion\n */\n\n#include\
    \ <algorithm>\n\nnamespace workspace {\n\n/**\n * @brief Transpose.\n *\n * @param\
    \ __grid\n */\ntemplate <class _Grid, typename = decltype(std::declval<std::decay_t<\
    \ _Grid>>()[0].resize(0))>\nconstexpr decltype(auto) transpose(_Grid &&__grid)\
    \ {\n  auto __h = std::size(__grid), __w = std::size(__grid[0]);\n\n  std::decay_t<_Grid>\
    \ __t(__w);\n  for (auto &&__r : __t) __r.resize(__h);\n\n  using reference =\
    \ decltype(__grid[0][0]);\n\n  for (size_t __i = 0; __i != __h; ++__i)\n    for\
    \ (size_t __j = 0; __j != __w; ++__j)\n      __t[__j][__i] = std::forward<reference>(__grid[__i][__j]);\n\
    \n  return __t;\n}\n\n/**\n * @brief Transpose.\n *\n * @param __grid\n */\ntemplate\
    \ <class _Tp, size_t _Rows, size_t _Cols>\nconstexpr decltype(auto) transpose(const\
    \ _Tp (&__grid)[_Rows][_Cols]) {\n  std::array<std::array<_Tp, _Rows>, _Cols>\
    \ __t;\n\n  for (size_t __i = 0; __i != _Rows; ++__i)\n    for (size_t __j = 0;\
    \ __j != _Cols; ++__j) __t[__j][__i] = __grid[__i][__j];\n\n  return __t;\n}\n\
    \n/**\n * @brief Transpose.\n *\n * @param __grid\n */\ntemplate <class _Tp, size_t\
    \ _Rows, size_t _Cols>\nconstexpr decltype(auto) transpose(_Tp(&&__grid)[_Rows][_Cols])\
    \ {\n  std::array<std::array<_Tp, _Rows>, _Cols> __t;\n\n  for (size_t __i = 0;\
    \ __i != _Rows; ++__i)\n    for (size_t __j = 0; __j != _Cols; ++__j)\n      __t[__j][__i]\
    \ = std::move(__grid[__i][__j]);\n\n  return __t;\n}\n\n/**\n * @brief Transpose.\n\
    \ *\n * @param __grid\n */\ntemplate <class _Tp, size_t _Rows, size_t _Cols>\n\
    constexpr decltype(auto) transpose(\n    const std::array<std::array<_Tp, _Cols>,\
    \ _Rows> &__grid) {\n  std::array<std::array<_Tp, _Rows>, _Cols> __t;\n\n  for\
    \ (size_t __i = 0; __i != _Rows; ++__i)\n    for (size_t __j = 0; __j != _Cols;\
    \ ++__j) __t[__j][__i] = __grid[__i][__j];\n\n  return __t;\n}\n\n/**\n * @brief\
    \ Transpose.\n *\n * @param __grid\n */\ntemplate <class _Tp, size_t _Rows, size_t\
    \ _Cols>\nconstexpr decltype(auto) transpose(\n    std::array<std::array<_Tp,\
    \ _Cols>, _Rows> &&__grid) {\n  std::array<std::array<_Tp, _Rows>, _Cols> __t;\n\
    \n  for (size_t __i = 0; __i != _Rows; ++__i)\n    for (size_t __j = 0; __j !=\
    \ _Cols; ++__j)\n      __t[__j][__i] = std::move(__grid[__i][__j]);\n\n  return\
    \ __t;\n}\n\n/**\n * @brief Roll the grid counter-clockwise.\n *\n * @param __grid\n\
    \ * @return\n */\ntemplate <class _Grid> decltype(auto) roll_ccw(const _Grid &__grid)\
    \ {\n  auto __t = transpose(__grid);\n  std::reverse(std::begin(__t), std::end(__t));\n\
    \  return __t;\n}\n\n/**\n * @brief Roll the grid counter-clockwise.\n *\n * @param\
    \ __grid\n * @return\n */\ntemplate <class _Grid> decltype(auto) roll_ccw(_Grid\
    \ &&__grid) {\n  auto __t = transpose(std::move(__grid));\n  std::reverse(std::begin(__t),\
    \ std::end(__t));\n  return __t;\n}\n\n/**\n * @brief Roll the grid clockwise.\n\
    \ *\n * @param __grid\n * @return\n */\ntemplate <class _Grid> decltype(auto)\
    \ roll_cw(const _Grid &__grid) {\n  auto __t = transpose(__grid);\n  for (auto\
    \ &&__r : __t) std::reverse(std::begin(__r), std::end(__r));\n  return __t;\n\
    }\n\n/**\n * @brief Roll the grid clockwise.\n *\n * @param __grid\n * @return\n\
    \ */\ntemplate <class _Grid> decltype(auto) roll_cw(_Grid &&__grid) {\n  std::reverse(std::begin(__grid),\
    \ std::end(__grid));\n  return transpose(std::move(__grid));\n}\n\n}  // namespace\
    \ workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/utils/grid/motion.hpp
  requiredBy: []
  timestamp: '2021-03-30 00:15:19+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/utils/grid/motion.hpp
layout: document
redirect_from:
- /library/src/utils/grid/motion.hpp
- /library/src/utils/grid/motion.hpp.html
title: Motion
---
