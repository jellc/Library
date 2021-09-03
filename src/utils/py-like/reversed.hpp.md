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
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Reversed
    links: []
  bundledCode: "#line 2 \"src/utils/py-like/reversed.hpp\"\n\n/**\n * @file reversed.hpp\n\
    \ * @brief Reversed\n */\n\n#include <vector>\n\n#line 2 \"lib/cxx17\"\n\n#line\
    \ 2 \"lib/cxx14\"\n\n#ifndef _CXX14_CONSTEXPR\n#if __cplusplus >= 201402L\n#define\
    \ _CXX14_CONSTEXPR constexpr\n#else\n#define _CXX14_CONSTEXPR\n#endif\n#endif\n\
    #line 4 \"lib/cxx17\"\n\n#ifndef _CXX17_CONSTEXPR\n#if __cplusplus >= 201703L\n\
    #define _CXX17_CONSTEXPR constexpr\n#else\n#define _CXX17_CONSTEXPR\n#endif\n\
    #endif\n\n#ifndef _CXX17_STATIC_ASSERT\n#if __cplusplus >= 201703L\n#define _CXX17_STATIC_ASSERT\
    \ static_assert\n#else\n#define _CXX17_STATIC_ASSERT assert\n#endif\n#endif\n\n\
    #include <iterator>\n\n#if __cplusplus < 201703L\n\nnamespace std {\n\n/**\n *\
    \  @brief  Return the size of a container.\n *  @param  __cont  Container.\n */\n\
    template <typename _Container>\nconstexpr auto size(const _Container& __cont)\
    \ noexcept(noexcept(__cont.size()))\n    -> decltype(__cont.size()) {\n  return\
    \ __cont.size();\n}\n\n/**\n *  @brief  Return the size of an array.\n */\ntemplate\
    \ <typename _Tp, size_t _Nm>\nconstexpr size_t size(const _Tp (&)[_Nm]) noexcept\
    \ {\n  return _Nm;\n}\n\nstruct monostate {};\n\n}  // namespace std\n\n#else\n\
    \n#include <variant>\n\n#endif\n#line 11 \"src/utils/py-like/reversed.hpp\"\n\n\
    namespace workspace {\n\n// Reversed container.\ntemplate <class _Container> class\
    \ reversed {\n  _Container __c;\n\n public:\n  template <class _Tp>\n  constexpr\
    \ reversed(_Tp &&__x) noexcept : __c(std::forward<_Container>(__x)) {}\n\n  template\
    \ <class _Tp>\n  constexpr reversed(std::initializer_list<_Tp> __x) noexcept :\
    \ __c(__x) {}\n\n  constexpr decltype(auto) begin() noexcept { return std::rbegin(__c);\
    \ }\n  constexpr decltype(auto) begin() const noexcept { return std::rbegin(__c);\
    \ }\n\n  constexpr decltype(auto) end() noexcept { return std::rend(__c); }\n\
    \  constexpr decltype(auto) end() const noexcept { return std::rend(__c); }\n\n\
    \  constexpr bool empty() const noexcept { return std::empty(__c); }\n\n  constexpr\
    \ decltype(auto) size() const noexcept { return std::size(__c); }\n\n  using iterator\
    \ = decltype(std::rbegin(__c));\n  using const_iterator = decltype(std::crbegin(__c));\n\
    \n  using size_type = decltype(std::size(__c));\n  using difference_type =\n \
    \     typename std::iterator_traits<iterator>::difference_type;\n  using value_type\
    \ = typename std::iterator_traits<iterator>::value_type;\n\n  using reference\
    \ = typename std::iterator_traits<iterator>::reference;\n  using const_reference\
    \ =\n      typename std::iterator_traits<const_iterator>::reference;\n};\n\n#if\
    \ __cpp_deduction_guides >= 201606L\n\ntemplate <class _Tp> reversed(_Tp &&) ->\
    \ reversed<_Tp>;\n\ntemplate <class _Tp>\nreversed(std::initializer_list<_Tp>)\
    \ -> reversed<std::initializer_list<_Tp>>;\n\n#endif\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file reversed.hpp\n * @brief Reversed\n */\n\n#include\
    \ <vector>\n\n#include \"lib/cxx17\"\n\nnamespace workspace {\n\n// Reversed container.\n\
    template <class _Container> class reversed {\n  _Container __c;\n\n public:\n\
    \  template <class _Tp>\n  constexpr reversed(_Tp &&__x) noexcept : __c(std::forward<_Container>(__x))\
    \ {}\n\n  template <class _Tp>\n  constexpr reversed(std::initializer_list<_Tp>\
    \ __x) noexcept : __c(__x) {}\n\n  constexpr decltype(auto) begin() noexcept {\
    \ return std::rbegin(__c); }\n  constexpr decltype(auto) begin() const noexcept\
    \ { return std::rbegin(__c); }\n\n  constexpr decltype(auto) end() noexcept {\
    \ return std::rend(__c); }\n  constexpr decltype(auto) end() const noexcept {\
    \ return std::rend(__c); }\n\n  constexpr bool empty() const noexcept { return\
    \ std::empty(__c); }\n\n  constexpr decltype(auto) size() const noexcept { return\
    \ std::size(__c); }\n\n  using iterator = decltype(std::rbegin(__c));\n  using\
    \ const_iterator = decltype(std::crbegin(__c));\n\n  using size_type = decltype(std::size(__c));\n\
    \  using difference_type =\n      typename std::iterator_traits<iterator>::difference_type;\n\
    \  using value_type = typename std::iterator_traits<iterator>::value_type;\n\n\
    \  using reference = typename std::iterator_traits<iterator>::reference;\n  using\
    \ const_reference =\n      typename std::iterator_traits<const_iterator>::reference;\n\
    };\n\n#if __cpp_deduction_guides >= 201606L\n\ntemplate <class _Tp> reversed(_Tp\
    \ &&) -> reversed<_Tp>;\n\ntemplate <class _Tp>\nreversed(std::initializer_list<_Tp>)\
    \ -> reversed<std::initializer_list<_Tp>>;\n\n#endif\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/utils/py-like/reversed.hpp
  requiredBy:
  - src/utils/py-like/enumerate.hpp
  - src/utils/py-like/range.hpp
  timestamp: '2021-09-03 13:40:23+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/utils/py-like/reversed.hpp
layout: document
redirect_from:
- /library/src/utils/py-like/reversed.hpp
- /library/src/utils/py-like/reversed.hpp.html
title: Reversed
---
