---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Change Less/Greater
    links: []
  bundledCode: "#line 2 \"src/utils/chval.hpp\"\n\n/**\n * @file chval.hpp\n * @brief\
    \ Change Less/Greater\n */\n\n#include <functional>\n\nnamespace workspace {\n\
    \n/**\n * @brief Substitute __y for __x if __y < __x.\n * @param __x Reference\n\
    \ * @param __y Comparison target\n * @return Whether or not __x is updated.\n\
    \ */\ntemplate <class _T1, class _T2,\n          typename = decltype(std::declval<_T2>()\
    \ < std::declval<_T1 &>())>\ntypename std::enable_if<std::is_assignable<_T1 &,\
    \ _T2>::value, bool>::type chle(\n    _T1 &__x, _T2 &&__y) noexcept {\n  return\
    \ __y < __x ? __x = std::forward<_T2>(__y), true : false;\n}\n\n/**\n * @brief\
    \ Substitute __y for __x if __x < __y.\n * @param __x Reference\n * @param __y\
    \ Comparison target\n * @return Whether or not __x is updated.\n */\ntemplate\
    \ <class _T1, class _T2,\n          typename = decltype(std::declval<_T1 &>()\
    \ < std::declval<_T2>())>\ntypename std::enable_if<std::is_assignable<_T1 &, _T2>::value,\
    \ bool>::type chge(\n    _T1 &__x, _T2 &&__y) noexcept {\n  return __x < __y ?\
    \ __x = std::forward<_T2>(__y), true : false;\n}\n\n/**\n * @brief Substitute\
    \ __y for __x if __comp(__y, __x) is true.\n * @param __x Reference\n * @param\
    \ __y Comparison target\n * @param __comp Compare function object\n * @return\
    \ Whether or not __x is updated.\n */\ntemplate <class _T1, class _T2, class _Compare,\n\
    \          typename = decltype(std::declval<_Compare>()(std::declval<_T2>(),\n\
    \                                                       std::declval<_T1 &>()))>\n\
    typename std::enable_if<std::is_assignable<_T1 &, _T2>::value, bool>::type chle(\n\
    \    _T1 &__x, _T2 &&__y, _Compare __comp) noexcept {\n  return __comp(__y, __x)\
    \ ? __x = std::forward<_T2>(__y), true : false;\n}\n\n/**\n * @brief Substitute\
    \ __y for __x if __comp(__x, __y) is true.\n * @param __x Reference\n * @param\
    \ __y Comparison target\n * @param __comp Compare function object\n * @return\
    \ Whether or not __x is updated.\n */\ntemplate <class _T1, class _T2, class _Compare,\n\
    \          typename = decltype(std::declval<_Compare>()(std::declval<_T1 &>(),\n\
    \                                                       std::declval<_T2>()))>\n\
    typename std::enable_if<std::is_assignable<_T1 &, _T2>::value, bool>::type chge(\n\
    \    _T1 &__x, _T2 &&__y, _Compare __comp) noexcept {\n  return __comp(__x, __y)\
    \ ? __x = std::forward<_T2>(__y), true : false;\n}\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file chval.hpp\n * @brief Change Less/Greater\n\
    \ */\n\n#include <functional>\n\nnamespace workspace {\n\n/**\n * @brief Substitute\
    \ __y for __x if __y < __x.\n * @param __x Reference\n * @param __y Comparison\
    \ target\n * @return Whether or not __x is updated.\n */\ntemplate <class _T1,\
    \ class _T2,\n          typename = decltype(std::declval<_T2>() < std::declval<_T1\
    \ &>())>\ntypename std::enable_if<std::is_assignable<_T1 &, _T2>::value, bool>::type\
    \ chle(\n    _T1 &__x, _T2 &&__y) noexcept {\n  return __y < __x ? __x = std::forward<_T2>(__y),\
    \ true : false;\n}\n\n/**\n * @brief Substitute __y for __x if __x < __y.\n *\
    \ @param __x Reference\n * @param __y Comparison target\n * @return Whether or\
    \ not __x is updated.\n */\ntemplate <class _T1, class _T2,\n          typename\
    \ = decltype(std::declval<_T1 &>() < std::declval<_T2>())>\ntypename std::enable_if<std::is_assignable<_T1\
    \ &, _T2>::value, bool>::type chge(\n    _T1 &__x, _T2 &&__y) noexcept {\n  return\
    \ __x < __y ? __x = std::forward<_T2>(__y), true : false;\n}\n\n/**\n * @brief\
    \ Substitute __y for __x if __comp(__y, __x) is true.\n * @param __x Reference\n\
    \ * @param __y Comparison target\n * @param __comp Compare function object\n *\
    \ @return Whether or not __x is updated.\n */\ntemplate <class _T1, class _T2,\
    \ class _Compare,\n          typename = decltype(std::declval<_Compare>()(std::declval<_T2>(),\n\
    \                                                       std::declval<_T1 &>()))>\n\
    typename std::enable_if<std::is_assignable<_T1 &, _T2>::value, bool>::type chle(\n\
    \    _T1 &__x, _T2 &&__y, _Compare __comp) noexcept {\n  return __comp(__y, __x)\
    \ ? __x = std::forward<_T2>(__y), true : false;\n}\n\n/**\n * @brief Substitute\
    \ __y for __x if __comp(__x, __y) is true.\n * @param __x Reference\n * @param\
    \ __y Comparison target\n * @param __comp Compare function object\n * @return\
    \ Whether or not __x is updated.\n */\ntemplate <class _T1, class _T2, class _Compare,\n\
    \          typename = decltype(std::declval<_Compare>()(std::declval<_T1 &>(),\n\
    \                                                       std::declval<_T2>()))>\n\
    typename std::enable_if<std::is_assignable<_T1 &, _T2>::value, bool>::type chge(\n\
    \    _T1 &__x, _T2 &&__y, _Compare __comp) noexcept {\n  return __comp(__x, __y)\
    \ ? __x = std::forward<_T2>(__y), true : false;\n}\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/utils/chval.hpp
  requiredBy: []
  timestamp: '2021-03-03 13:03:00+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/utils/chval.hpp
layout: document
redirect_from:
- /library/src/utils/chval.hpp
- /library/src/utils/chval.hpp.html
title: Change Less/Greater
---
