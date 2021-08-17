---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Cat
    links: []
  bundledCode: "#line 2 \"src/utils/cat.hpp\"\n\n/**\n * @file cat.hpp\n * @brief\
    \ Cat\n */\n\n#include <iterator>\n\n#line 2 \"lib/cxx17\"\n\n#ifndef _CXX17_CONSTEXPR\n\
    #if __cplusplus >= 201703L\n#define _CXX17_CONSTEXPR constexpr\n#else\n#define\
    \ _CXX17_CONSTEXPR\n#endif\n#endif\n\n#ifndef _CXX17_STATIC_ASSERT\n#if __cplusplus\
    \ >= 201703L\n#define _CXX17_STATIC_ASSERT static_assert\n#else\n#define _CXX17_STATIC_ASSERT\
    \ assert\n#endif\n#endif\n\n#line 20 \"lib/cxx17\"\n\n#if __cplusplus < 201703L\n\
    \nnamespace std {\n\n/**\n *  @brief  Return the size of a container.\n *  @param\
    \  __cont  Container.\n */\ntemplate <typename _Container>\nconstexpr auto size(const\
    \ _Container& __cont) noexcept(noexcept(__cont.size()))\n    -> decltype(__cont.size())\
    \ {\n  return __cont.size();\n}\n\n/**\n *  @brief  Return the size of an array.\n\
    \ */\ntemplate <typename _Tp, size_t _Nm>\nconstexpr size_t size(const _Tp (&)[_Nm])\
    \ noexcept {\n  return _Nm;\n}\n\nstruct monostate {};\n\n}  // namespace std\n\
    \n#else\n\n#include <variant>\n\n#endif\n#line 11 \"src/utils/cat.hpp\"\n\nnamespace\
    \ workspace {\n\n/**\n * @brief Concatenate two sequences.\n *\n * @param __c1\n\
    \ * @param __c2\n * @return Concatenated sequence.\n */\ntemplate <class _C1,\
    \ class _C2>\nconstexpr decltype(auto) cat(_C1 &&__c1, _C2 &&__c2) noexcept {\n\
    \  auto __c = std::forward<_C1>(__c1);\n\n  if _CXX17_CONSTEXPR (std::is_rvalue_reference<decltype(__c2)>::value)\n\
    \    __c.insert(std::end(__c), std::make_move_iterator(std::begin(__c2)),\n  \
    \             std::make_move_iterator(std::end(__c2)));\n  else\n    __c.insert(std::end(__c),\
    \ std::cbegin(__c2), std::cend(__c2));\n\n  return __c;\n}\n\n/**\n * @return\
    \ Concatenated sequence.\n */\ntemplate <class _C1, class _C2, class... _Args>\n\
    constexpr decltype(auto) cat(_C1 &&__c1, _C2 &&__c2,\n                       \
    \      _Args &&...__args) noexcept {\n  return cat(cat(std::forward<_C1>(__c1),\
    \ std::forward<_C2>(__c2)),\n             std::forward<_Args>(__args)...);\n}\n\
    \n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file cat.hpp\n * @brief Cat\n */\n\n#include <iterator>\n\
    \n#include \"lib/cxx17\"\n\nnamespace workspace {\n\n/**\n * @brief Concatenate\
    \ two sequences.\n *\n * @param __c1\n * @param __c2\n * @return Concatenated\
    \ sequence.\n */\ntemplate <class _C1, class _C2>\nconstexpr decltype(auto) cat(_C1\
    \ &&__c1, _C2 &&__c2) noexcept {\n  auto __c = std::forward<_C1>(__c1);\n\n  if\
    \ _CXX17_CONSTEXPR (std::is_rvalue_reference<decltype(__c2)>::value)\n    __c.insert(std::end(__c),\
    \ std::make_move_iterator(std::begin(__c2)),\n               std::make_move_iterator(std::end(__c2)));\n\
    \  else\n    __c.insert(std::end(__c), std::cbegin(__c2), std::cend(__c2));\n\n\
    \  return __c;\n}\n\n/**\n * @return Concatenated sequence.\n */\ntemplate <class\
    \ _C1, class _C2, class... _Args>\nconstexpr decltype(auto) cat(_C1 &&__c1, _C2\
    \ &&__c2,\n                             _Args &&...__args) noexcept {\n  return\
    \ cat(cat(std::forward<_C1>(__c1), std::forward<_C2>(__c2)),\n             std::forward<_Args>(__args)...);\n\
    }\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/utils/cat.hpp
  requiredBy: []
  timestamp: '2021-08-17 17:53:53+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/utils/cat.hpp
layout: document
redirect_from:
- /library/src/utils/cat.hpp
- /library/src/utils/cat.hpp.html
title: Cat
---
