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
    \ * @brief Nd-vector\n */\n\n#include <vector>\n\n#line 2 \"lib/cxx17\"\n\n#line\
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
    \ {\n  return _Nm;\n}\n\n/**\n *  @brief  Return whether a container is empty.\n\
    \ *  @param  __cont  Container.\n */\ntemplate <typename _Container>\n[[nodiscard]]\
    \ constexpr auto empty(const _Container& __cont) noexcept(\n    noexcept(__cont.empty()))\
    \ -> decltype(__cont.empty()) {\n  return __cont.empty();\n}\n\n/**\n *  @brief\
    \  Return whether an array is empty (always false).\n */\ntemplate <typename _Tp,\
    \ size_t _Nm>\n[[nodiscard]] constexpr bool empty(const _Tp (&)[_Nm]) noexcept\
    \ {\n  return false;\n}\n\n/**\n *  @brief  Return whether an initializer_list\
    \ is empty.\n *  @param  __il  Initializer list.\n */\ntemplate <typename _Tp>\n\
    [[nodiscard]] constexpr bool empty(initializer_list<_Tp> __il) noexcept {\n  return\
    \ __il.size() == 0;\n}\n\nstruct monostate {};\n\n}  // namespace std\n\n#else\n\
    \n#include <variant>\n\n#endif\n#line 11 \"src/data_structure/ndvec.hpp\"\n\n\
    namespace workspace {\n\ntemplate <class _Tp, size_t _Dim>\nclass ndvec : public\
    \ std::vector<ndvec<_Tp, _Dim - 1>> {\n public:\n  static constexpr auto dimension\
    \ = _Dim;\n  using container_type = std::vector<ndvec<_Tp, _Dim - 1>>;\n  using\
    \ size_type = typename container_type::size_type;\n\n  ndvec() = default;\n\n\
    \  template <size_t _Nm>\n  ndvec(const size_t (&__size)[_Nm], const _Tp& __x\
    \ = {}) noexcept\n      : container_type(__size[_Nm - _Dim], {__size, __x}) {}\n\
    \n  template <size_type _Nm = 0> size_type size() const noexcept {\n    _CXX17_STATIC_ASSERT(_Nm\
    \ < dimension);\n    if _CXX17_CONSTEXPR (_Nm) {\n      return container_type::operator[](0).template\
    \ size<_Nm - 1>();\n    }\n    return container_type::size();\n  }\n\n  void fill(const\
    \ _Tp& __x) noexcept {\n    for (auto __i = container_type::begin(); __i != container_type::end();\n\
    \         ++__i)\n      __i->fill(__x);\n  }\n};\n\ntemplate <class _Tp> class\
    \ ndvec<_Tp, 1> : public std::vector<_Tp> {\n public:\n  static constexpr auto\
    \ dimension = 1;\n  using container_type = std::vector<_Tp>;\n  using size_type\
    \ = typename container_type::size_type;\n\n  ndvec() = default;\n\n  template\
    \ <size_t _Nm>\n  ndvec(const size_t (&__size)[_Nm], const _Tp& __x = {}) noexcept\n\
    \      : container_type(__size[_Nm - 1], __x) {}\n\n  template <size_type _Nm\
    \ = 0> size_type size() const noexcept {\n    _CXX17_STATIC_ASSERT(!_Nm);\n  \
    \  return container_type::size();\n  }\n\n  void fill(const _Tp& __x) noexcept\
    \ {\n    for (auto __i = container_type::begin(); __i != container_type::end();\n\
    \         ++__i)\n      *__i = __x;\n  }\n};\n\n#if __cpp_deduction_guides >=\
    \ 201606L\n\ntemplate <class _Tp, size_t _Dim>\nndvec(const size_t (&)[_Dim],\
    \ const _Tp&) -> ndvec<_Tp, _Dim>;\n\n#endif\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file ndvec.hpp\n * @brief Nd-vector\n */\n\n#include\
    \ <vector>\n\n#include \"lib/cxx17\"\n\nnamespace workspace {\n\ntemplate <class\
    \ _Tp, size_t _Dim>\nclass ndvec : public std::vector<ndvec<_Tp, _Dim - 1>> {\n\
    \ public:\n  static constexpr auto dimension = _Dim;\n  using container_type =\
    \ std::vector<ndvec<_Tp, _Dim - 1>>;\n  using size_type = typename container_type::size_type;\n\
    \n  ndvec() = default;\n\n  template <size_t _Nm>\n  ndvec(const size_t (&__size)[_Nm],\
    \ const _Tp& __x = {}) noexcept\n      : container_type(__size[_Nm - _Dim], {__size,\
    \ __x}) {}\n\n  template <size_type _Nm = 0> size_type size() const noexcept {\n\
    \    _CXX17_STATIC_ASSERT(_Nm < dimension);\n    if _CXX17_CONSTEXPR (_Nm) {\n\
    \      return container_type::operator[](0).template size<_Nm - 1>();\n    }\n\
    \    return container_type::size();\n  }\n\n  void fill(const _Tp& __x) noexcept\
    \ {\n    for (auto __i = container_type::begin(); __i != container_type::end();\n\
    \         ++__i)\n      __i->fill(__x);\n  }\n};\n\ntemplate <class _Tp> class\
    \ ndvec<_Tp, 1> : public std::vector<_Tp> {\n public:\n  static constexpr auto\
    \ dimension = 1;\n  using container_type = std::vector<_Tp>;\n  using size_type\
    \ = typename container_type::size_type;\n\n  ndvec() = default;\n\n  template\
    \ <size_t _Nm>\n  ndvec(const size_t (&__size)[_Nm], const _Tp& __x = {}) noexcept\n\
    \      : container_type(__size[_Nm - 1], __x) {}\n\n  template <size_type _Nm\
    \ = 0> size_type size() const noexcept {\n    _CXX17_STATIC_ASSERT(!_Nm);\n  \
    \  return container_type::size();\n  }\n\n  void fill(const _Tp& __x) noexcept\
    \ {\n    for (auto __i = container_type::begin(); __i != container_type::end();\n\
    \         ++__i)\n      *__i = __x;\n  }\n};\n\n#if __cpp_deduction_guides >=\
    \ 201606L\n\ntemplate <class _Tp, size_t _Dim>\nndvec(const size_t (&)[_Dim],\
    \ const _Tp&) -> ndvec<_Tp, _Dim>;\n\n#endif\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/data_structure/ndvec.hpp
  requiredBy: []
  timestamp: '2022-04-06 15:49:21+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/data_structure/ndvec.hpp
layout: document
redirect_from:
- /library/src/data_structure/ndvec.hpp
- /library/src/data_structure/ndvec.hpp.html
title: Nd-vector
---
