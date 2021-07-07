---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Nd-vector
    links: []
  bundledCode: "#line 2 \"src/data_structure/ndvec.hpp\"\n\n/**\n * @file ndvec.hpp\n\
    \ * @brief Nd-vector\n */\n\n#include <vector>\n\n#line 2 \"lib/cxx17\"\n\n#ifndef\
    \ _CXX17_CONSTEXPR\n#if __cplusplus >= 201703L\n#define _CXX17_CONSTEXPR constexpr\n\
    #else\n#define _CXX17_CONSTEXPR\n#endif\n#endif\n\n#ifndef _CXX17_STATIC_ASSERT\n\
    #if __cplusplus >= 201703L\n#define _CXX17_STATIC_ASSERT static_assert\n#else\n\
    #define _CXX17_STATIC_ASSERT assert\n#endif\n#endif\n\n#if __cplusplus < 201703L\n\
    \nnamespace std {\n\n/**\n *  @brief  Return the size of a container.\n *  @param\
    \  __cont  Container.\n */\ntemplate <typename _Container>\nconstexpr auto size(const\
    \ _Container& __cont) noexcept(noexcept(__cont.size()))\n    -> decltype(__cont.size())\
    \ {\n  return __cont.size();\n}\n\n/**\n *  @brief  Return the size of an array.\n\
    \ */\ntemplate <typename _Tp, size_t _Nm>\nconstexpr size_t size(const _Tp (&)[_Nm])\
    \ noexcept {\n  return _Nm;\n}\n\n}  // namespace std\n\n#endif\n#line 11 \"src/data_structure/ndvec.hpp\"\
    \n\nnamespace workspace {\n\ntemplate <class _Tp, size_t _Dim>\nclass ndvec :\
    \ public std::vector<ndvec<_Tp, _Dim - 1>> {\n public:\n  static constexpr auto\
    \ dimension = _Dim;\n  using container_type = std::vector<ndvec<_Tp, _Dim - 1>>;\n\
    \  using size_type = typename container_type::size_type;\n\n  ndvec() = default;\n\
    \n  template <class _Size, size_t _Nm>\n  ndvec(const _Size (&__size)[_Nm], const\
    \ _Tp& __x = {}) noexcept\n      : container_type(__size[_Nm - _Dim], {__size,\
    \ __x}) {}\n\n  template <size_type _Nm = 0> size_type size() const noexcept {\n\
    \    _CXX17_STATIC_ASSERT(_Nm < dimension);\n    if _CXX17_CONSTEXPR (_Nm) {\n\
    \      return container_type::operator[](0).template size<_Nm - 1>();\n    }\n\
    \    return container_type::size();\n  }\n};\n\ntemplate <class _Tp> class ndvec<_Tp,\
    \ 1> : public std::vector<_Tp> {\n public:\n  static constexpr auto dimension\
    \ = 1;\n  using container_type = std::vector<_Tp>;\n  using size_type = typename\
    \ container_type::size_type;\n\n  ndvec() = default;\n\n  template <class _Size,\
    \ size_t _Nm>\n  ndvec(const _Size (&__size)[_Nm], const _Tp& __x = {}) noexcept\n\
    \      : container_type(__size[_Nm - 1], __x) {}\n\n  template <size_type _Nm\
    \ = 0> size_type size() const noexcept {\n    _CXX17_STATIC_ASSERT(!_Nm);\n  \
    \  return container_type::size();\n  }\n};\n\n#if __cplusplus >= 201703L\n\ntemplate\
    \ <class _Tp, class _Size, size_t _Dim>\nndvec(const _Size (&)[_Dim], const _Tp&)\
    \ -> ndvec<_Tp, _Dim>;\n\n#endif\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file ndvec.hpp\n * @brief Nd-vector\n */\n\n#include\
    \ <vector>\n\n#include \"lib/cxx17\"\n\nnamespace workspace {\n\ntemplate <class\
    \ _Tp, size_t _Dim>\nclass ndvec : public std::vector<ndvec<_Tp, _Dim - 1>> {\n\
    \ public:\n  static constexpr auto dimension = _Dim;\n  using container_type =\
    \ std::vector<ndvec<_Tp, _Dim - 1>>;\n  using size_type = typename container_type::size_type;\n\
    \n  ndvec() = default;\n\n  template <class _Size, size_t _Nm>\n  ndvec(const\
    \ _Size (&__size)[_Nm], const _Tp& __x = {}) noexcept\n      : container_type(__size[_Nm\
    \ - _Dim], {__size, __x}) {}\n\n  template <size_type _Nm = 0> size_type size()\
    \ const noexcept {\n    _CXX17_STATIC_ASSERT(_Nm < dimension);\n    if _CXX17_CONSTEXPR\
    \ (_Nm) {\n      return container_type::operator[](0).template size<_Nm - 1>();\n\
    \    }\n    return container_type::size();\n  }\n};\n\ntemplate <class _Tp> class\
    \ ndvec<_Tp, 1> : public std::vector<_Tp> {\n public:\n  static constexpr auto\
    \ dimension = 1;\n  using container_type = std::vector<_Tp>;\n  using size_type\
    \ = typename container_type::size_type;\n\n  ndvec() = default;\n\n  template\
    \ <class _Size, size_t _Nm>\n  ndvec(const _Size (&__size)[_Nm], const _Tp& __x\
    \ = {}) noexcept\n      : container_type(__size[_Nm - 1], __x) {}\n\n  template\
    \ <size_type _Nm = 0> size_type size() const noexcept {\n    _CXX17_STATIC_ASSERT(!_Nm);\n\
    \    return container_type::size();\n  }\n};\n\n#if __cplusplus >= 201703L\n\n\
    template <class _Tp, class _Size, size_t _Dim>\nndvec(const _Size (&)[_Dim], const\
    \ _Tp&) -> ndvec<_Tp, _Dim>;\n\n#endif\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/data_structure/ndvec.hpp
  requiredBy: []
  timestamp: '2021-07-07 20:07:23+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/data_structure/ndvec.hpp
layout: document
redirect_from:
- /library/src/data_structure/ndvec.hpp
- /library/src/data_structure/ndvec.hpp.html
title: Nd-vector
---
