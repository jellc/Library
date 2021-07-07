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
    \ * @brief Motion\n */\n\n#include <algorithm>\n\n#line 2 \"lib/cxx17\"\n\n#ifndef\
    \ _CXX17_CONSTEXPR\n#if __cplusplus >= 201703L\n#define _CXX17_CONSTEXPR constexpr\n\
    #else\n#define _CXX17_CONSTEXPR\n#endif\n#endif\n\n#ifndef _CXX17_STATIC_ASSERT\n\
    #if __cplusplus >= 201703L\n#define _CXX17_STATIC_ASSERT static_assert\n#else\n\
    #define _CXX17_STATIC_ASSERT assert\n#endif\n#endif\n\n#if __cplusplus < 201703L\n\
    \nnamespace std {\n\n/**\n *  @brief  Return the size of a container.\n *  @param\
    \  __cont  Container.\n */\ntemplate <typename _Container>\nconstexpr auto size(const\
    \ _Container& __cont) noexcept(noexcept(__cont.size()))\n    -> decltype(__cont.size())\
    \ {\n  return __cont.size();\n}\n\n/**\n *  @brief  Return the size of an array.\n\
    \ */\ntemplate <typename _Tp, size_t _Nm>\nconstexpr size_t size(const _Tp (&)[_Nm])\
    \ noexcept {\n  return _Nm;\n}\n\n}  // namespace std\n\n#endif\n#line 11 \"src/utils/grid/motion.hpp\"\
    \n\nnamespace workspace {\n\n/**\n * @brief Transpose.\n * @param __grid\n */\n\
    template <class _Grid,\n          typename = decltype(std::declval<std::decay_t<_Grid>>()[0].resize(0))>\n\
    constexpr decltype(auto) transpose(_Grid &&__grid) noexcept {\n#if __cplusplus\
    \ < 201703L\n  auto __h = __grid.size(), __w = __grid[0].size();\n#else\n  auto\
    \ __h = std::size(__grid), __w = std::size(__grid[0]);\n#endif\n  std::decay_t<_Grid>\
    \ __t(__w);\n  for (auto &&__r : __t) __r.resize(__h);\n  for (size_t __i = 0;\
    \ __i != __h; ++__i)\n    for (size_t __j = 0; __j != __w; ++__j)\n      if _CXX17_CONSTEXPR\
    \ (std::is_rvalue_reference<decltype(__grid)>::value)\n        __t[__j][__i] =\
    \ std::move(__grid[__i][__j]);\n      else\n        __t[__j][__i] = __grid[__i][__j];\n\
    \  return __t;\n}\n\n/**\n * @brief Transpose.\n * @param __grid\n */\ntemplate\
    \ <class _Tp, size_t _Rows, size_t _Cols>\nconstexpr decltype(auto) transpose(const\
    \ _Tp (&__grid)[_Rows][_Cols]) noexcept {\n  std::array<std::array<_Tp, _Rows>,\
    \ _Cols> __t;\n  for (size_t __i = 0; __i != _Rows; ++__i)\n    for (size_t __j\
    \ = 0; __j != _Cols; ++__j) __t[__j][__i] = __grid[__i][__j];\n  return __t;\n\
    }\n\n/**\n * @brief Transpose.\n * @param __grid\n */\ntemplate <class _Tp, size_t\
    \ _Rows, size_t _Cols>\nconstexpr decltype(auto) transpose(_Tp(&&__grid)[_Rows][_Cols])\
    \ noexcept {\n  std::array<std::array<_Tp, _Rows>, _Cols> __t;\n  for (size_t\
    \ __i = 0; __i != _Rows; ++__i)\n    for (size_t __j = 0; __j != _Cols; ++__j)\n\
    \      __t[__j][__i] = std::move(__grid[__i][__j]);\n  return __t;\n}\n\n/**\n\
    \ * @brief Transpose.\n * @param __grid\n */\ntemplate <class _Tp, size_t _Rows,\
    \ size_t _Cols>\nconstexpr decltype(auto) transpose(\n    const std::array<std::array<_Tp,\
    \ _Cols>, _Rows> &__grid) noexcept {\n  std::array<std::array<_Tp, _Rows>, _Cols>\
    \ __t;\n  for (size_t __i = 0; __i != _Rows; ++__i)\n    for (size_t __j = 0;\
    \ __j != _Cols; ++__j) __t[__j][__i] = __grid[__i][__j];\n  return __t;\n}\n\n\
    /**\n * @brief Transpose.\n * @param __grid\n */\ntemplate <class _Tp, size_t\
    \ _Rows, size_t _Cols>\nconstexpr decltype(auto) transpose(\n    std::array<std::array<_Tp,\
    \ _Cols>, _Rows> &&__grid) noexcept {\n  std::array<std::array<_Tp, _Rows>, _Cols>\
    \ __t;\n  for (size_t __i = 0; __i != _Rows; ++__i)\n    for (size_t __j = 0;\
    \ __j != _Cols; ++__j)\n      __t[__j][__i] = std::move(__grid[__i][__j]);\n \
    \ return __t;\n}\n\n/**\n * @brief Roll the grid counter-clockwise.\n * @param\
    \ __grid\n */\ntemplate <class _Grid> decltype(auto) roll_ccw(_Grid &&__grid)\
    \ noexcept {\n  if _CXX17_CONSTEXPR (std::is_rvalue_reference<decltype(__grid)>::value)\
    \ {\n    auto __t = transpose(std::move(__grid));\n    std::reverse(std::begin(__t),\
    \ std::end(__t));\n    return __t;\n  } else {\n    auto __t = transpose(__grid);\n\
    \    std::reverse(std::begin(__t), std::end(__t));\n    return __t;\n  }\n}\n\n\
    /**\n * @brief Roll the grid clockwise.\n * @param __grid\n */\ntemplate <class\
    \ _Grid> decltype(auto) roll_cw(_Grid &&__grid) noexcept {\n  if _CXX17_CONSTEXPR\
    \ (std::is_rvalue_reference<decltype(__grid)>::value) {\n    std::reverse(std::begin(__grid),\
    \ std::end(__grid));\n    return transpose(std::move(__grid));\n  } else {\n \
    \   auto __t = transpose(__grid);\n    for (auto &&__r : __t) std::reverse(std::begin(__r),\
    \ std::end(__r));\n    return __t;\n  }\n}\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file motion.hpp\n * @brief Motion\n */\n\n#include\
    \ <algorithm>\n\n#include \"lib/cxx17\"\n\nnamespace workspace {\n\n/**\n * @brief\
    \ Transpose.\n * @param __grid\n */\ntemplate <class _Grid,\n          typename\
    \ = decltype(std::declval<std::decay_t<_Grid>>()[0].resize(0))>\nconstexpr decltype(auto)\
    \ transpose(_Grid &&__grid) noexcept {\n#if __cplusplus < 201703L\n  auto __h\
    \ = __grid.size(), __w = __grid[0].size();\n#else\n  auto __h = std::size(__grid),\
    \ __w = std::size(__grid[0]);\n#endif\n  std::decay_t<_Grid> __t(__w);\n  for\
    \ (auto &&__r : __t) __r.resize(__h);\n  for (size_t __i = 0; __i != __h; ++__i)\n\
    \    for (size_t __j = 0; __j != __w; ++__j)\n      if _CXX17_CONSTEXPR (std::is_rvalue_reference<decltype(__grid)>::value)\n\
    \        __t[__j][__i] = std::move(__grid[__i][__j]);\n      else\n        __t[__j][__i]\
    \ = __grid[__i][__j];\n  return __t;\n}\n\n/**\n * @brief Transpose.\n * @param\
    \ __grid\n */\ntemplate <class _Tp, size_t _Rows, size_t _Cols>\nconstexpr decltype(auto)\
    \ transpose(const _Tp (&__grid)[_Rows][_Cols]) noexcept {\n  std::array<std::array<_Tp,\
    \ _Rows>, _Cols> __t;\n  for (size_t __i = 0; __i != _Rows; ++__i)\n    for (size_t\
    \ __j = 0; __j != _Cols; ++__j) __t[__j][__i] = __grid[__i][__j];\n  return __t;\n\
    }\n\n/**\n * @brief Transpose.\n * @param __grid\n */\ntemplate <class _Tp, size_t\
    \ _Rows, size_t _Cols>\nconstexpr decltype(auto) transpose(_Tp(&&__grid)[_Rows][_Cols])\
    \ noexcept {\n  std::array<std::array<_Tp, _Rows>, _Cols> __t;\n  for (size_t\
    \ __i = 0; __i != _Rows; ++__i)\n    for (size_t __j = 0; __j != _Cols; ++__j)\n\
    \      __t[__j][__i] = std::move(__grid[__i][__j]);\n  return __t;\n}\n\n/**\n\
    \ * @brief Transpose.\n * @param __grid\n */\ntemplate <class _Tp, size_t _Rows,\
    \ size_t _Cols>\nconstexpr decltype(auto) transpose(\n    const std::array<std::array<_Tp,\
    \ _Cols>, _Rows> &__grid) noexcept {\n  std::array<std::array<_Tp, _Rows>, _Cols>\
    \ __t;\n  for (size_t __i = 0; __i != _Rows; ++__i)\n    for (size_t __j = 0;\
    \ __j != _Cols; ++__j) __t[__j][__i] = __grid[__i][__j];\n  return __t;\n}\n\n\
    /**\n * @brief Transpose.\n * @param __grid\n */\ntemplate <class _Tp, size_t\
    \ _Rows, size_t _Cols>\nconstexpr decltype(auto) transpose(\n    std::array<std::array<_Tp,\
    \ _Cols>, _Rows> &&__grid) noexcept {\n  std::array<std::array<_Tp, _Rows>, _Cols>\
    \ __t;\n  for (size_t __i = 0; __i != _Rows; ++__i)\n    for (size_t __j = 0;\
    \ __j != _Cols; ++__j)\n      __t[__j][__i] = std::move(__grid[__i][__j]);\n \
    \ return __t;\n}\n\n/**\n * @brief Roll the grid counter-clockwise.\n * @param\
    \ __grid\n */\ntemplate <class _Grid> decltype(auto) roll_ccw(_Grid &&__grid)\
    \ noexcept {\n  if _CXX17_CONSTEXPR (std::is_rvalue_reference<decltype(__grid)>::value)\
    \ {\n    auto __t = transpose(std::move(__grid));\n    std::reverse(std::begin(__t),\
    \ std::end(__t));\n    return __t;\n  } else {\n    auto __t = transpose(__grid);\n\
    \    std::reverse(std::begin(__t), std::end(__t));\n    return __t;\n  }\n}\n\n\
    /**\n * @brief Roll the grid clockwise.\n * @param __grid\n */\ntemplate <class\
    \ _Grid> decltype(auto) roll_cw(_Grid &&__grid) noexcept {\n  if _CXX17_CONSTEXPR\
    \ (std::is_rvalue_reference<decltype(__grid)>::value) {\n    std::reverse(std::begin(__grid),\
    \ std::end(__grid));\n    return transpose(std::move(__grid));\n  } else {\n \
    \   auto __t = transpose(__grid);\n    for (auto &&__r : __t) std::reverse(std::begin(__r),\
    \ std::end(__r));\n    return __t;\n  }\n}\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/utils/grid/motion.hpp
  requiredBy: []
  timestamp: '2021-07-07 20:04:02+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/utils/grid/motion.hpp
layout: document
redirect_from:
- /library/src/utils/grid/motion.hpp
- /library/src/utils/grid/motion.hpp.html
title: Motion
---
