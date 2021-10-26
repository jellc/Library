---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Pair Operations
    links: []
  bundledCode: "#line 1 \"src/algebra/pair.hpp\"\n#include <tuple>\n\n/**\n * @file\
    \ pair.hpp\n * @brief Pair Operations\n */\n\nnamespace workspace {\n\n// Pairwise\
    \ addition.\ntemplate <class _T1, class _T2, class _U1, class _U2>\nauto operator+(const\
    \ std::pair<_T1, _T2>& __p1,\n               const std::pair<_U1, _U2>& __p2)\
    \ noexcept {\n  return std::make_pair(__p1.first + __p2.first, __p1.second + __p2.second);\n\
    }\n\n// Pairwise addition assignment.\ntemplate <class _T1, class _T2, class _U1,\
    \ class _U2>\nauto& operator+=(std::pair<_T1, _T2>& __p1,\n                 const\
    \ std::pair<_U1, _U2>& __p2) noexcept {\n  __p1.first += __p2.first, __p1.second\
    \ += __p2.second;\n  return __p1;\n}\n\n// Pairwise subtraction.\ntemplate <class\
    \ _T1, class _T2, class _U1, class _U2>\nauto operator-(const std::pair<_T1, _T2>&\
    \ __p1,\n               const std::pair<_U1, _U2>& __p2) noexcept {\n  return\
    \ std::make_pair(__p1.first - __p2.first, __p1.second - __p2.second);\n}\n\n//\
    \ Pairwise subtraction assignment.\ntemplate <class _T1, class _T2, class _U1,\
    \ class _U2>\nauto& operator-=(std::pair<_T1, _T2>& __p1,\n                 const\
    \ std::pair<_U1, _U2>& __p2) noexcept {\n  __p1.first -= __p2.first, __p1.second\
    \ -= __p2.second;\n  return __p1;\n}\n\n// Pairwise multiplication.\ntemplate\
    \ <class _T1, class _T2, class _U1, class _U2>\nauto operator*(const std::pair<_T1,\
    \ _T2>& __p1,\n               const std::pair<_U1, _U2>& __p2) noexcept {\n  return\
    \ std::make_pair(__p1.first * __p2.first, __p1.second * __p2.second);\n}\n\n//\
    \ Pairwise multiplication assignment.\ntemplate <class _T1, class _T2, class _U1,\
    \ class _U2>\nauto& operator*=(std::pair<_T1, _T2>& __p1,\n                 const\
    \ std::pair<_U1, _U2>& __p2) noexcept {\n  __p1.first *= __p2.first, __p1.second\
    \ *= __p2.second;\n  return __p1;\n}\n\n// Pairwise division.\ntemplate <class\
    \ _T1, class _T2, class _U1, class _U2>\nauto operator/(const std::pair<_T1, _T2>&\
    \ __p1,\n               const std::pair<_U1, _U2>& __p2) noexcept {\n  return\
    \ std::make_pair(__p1.first / __p2.first, __p1.second / __p2.second);\n}\n\n//\
    \ Pairwise division assignment.\ntemplate <class _T1, class _T2, class _U1, class\
    \ _U2>\nauto& operator/=(std::pair<_T1, _T2>& __p1,\n                 const std::pair<_U1,\
    \ _U2>& __p2) noexcept {\n  __p1.first /= __p2.first, __p1.second /= __p2.second;\n\
    \  return __p1;\n}\n\n}  // namespace workspace\n"
  code: "#include <tuple>\n\n/**\n * @file pair.hpp\n * @brief Pair Operations\n */\n\
    \nnamespace workspace {\n\n// Pairwise addition.\ntemplate <class _T1, class _T2,\
    \ class _U1, class _U2>\nauto operator+(const std::pair<_T1, _T2>& __p1,\n   \
    \            const std::pair<_U1, _U2>& __p2) noexcept {\n  return std::make_pair(__p1.first\
    \ + __p2.first, __p1.second + __p2.second);\n}\n\n// Pairwise addition assignment.\n\
    template <class _T1, class _T2, class _U1, class _U2>\nauto& operator+=(std::pair<_T1,\
    \ _T2>& __p1,\n                 const std::pair<_U1, _U2>& __p2) noexcept {\n\
    \  __p1.first += __p2.first, __p1.second += __p2.second;\n  return __p1;\n}\n\n\
    // Pairwise subtraction.\ntemplate <class _T1, class _T2, class _U1, class _U2>\n\
    auto operator-(const std::pair<_T1, _T2>& __p1,\n               const std::pair<_U1,\
    \ _U2>& __p2) noexcept {\n  return std::make_pair(__p1.first - __p2.first, __p1.second\
    \ - __p2.second);\n}\n\n// Pairwise subtraction assignment.\ntemplate <class _T1,\
    \ class _T2, class _U1, class _U2>\nauto& operator-=(std::pair<_T1, _T2>& __p1,\n\
    \                 const std::pair<_U1, _U2>& __p2) noexcept {\n  __p1.first -=\
    \ __p2.first, __p1.second -= __p2.second;\n  return __p1;\n}\n\n// Pairwise multiplication.\n\
    template <class _T1, class _T2, class _U1, class _U2>\nauto operator*(const std::pair<_T1,\
    \ _T2>& __p1,\n               const std::pair<_U1, _U2>& __p2) noexcept {\n  return\
    \ std::make_pair(__p1.first * __p2.first, __p1.second * __p2.second);\n}\n\n//\
    \ Pairwise multiplication assignment.\ntemplate <class _T1, class _T2, class _U1,\
    \ class _U2>\nauto& operator*=(std::pair<_T1, _T2>& __p1,\n                 const\
    \ std::pair<_U1, _U2>& __p2) noexcept {\n  __p1.first *= __p2.first, __p1.second\
    \ *= __p2.second;\n  return __p1;\n}\n\n// Pairwise division.\ntemplate <class\
    \ _T1, class _T2, class _U1, class _U2>\nauto operator/(const std::pair<_T1, _T2>&\
    \ __p1,\n               const std::pair<_U1, _U2>& __p2) noexcept {\n  return\
    \ std::make_pair(__p1.first / __p2.first, __p1.second / __p2.second);\n}\n\n//\
    \ Pairwise division assignment.\ntemplate <class _T1, class _T2, class _U1, class\
    \ _U2>\nauto& operator/=(std::pair<_T1, _T2>& __p1,\n                 const std::pair<_U1,\
    \ _U2>& __p2) noexcept {\n  __p1.first /= __p2.first, __p1.second /= __p2.second;\n\
    \  return __p1;\n}\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/algebra/pair.hpp
  requiredBy: []
  timestamp: '2021-10-26 14:13:08+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/algebra/pair.hpp
layout: document
redirect_from:
- /library/src/algebra/pair.hpp
- /library/src/algebra/pair.hpp.html
title: Pair Operations
---
