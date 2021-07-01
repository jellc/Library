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
    \ * @brief Nd-vector\n */\n\n#include <vector>\n\nnamespace workspace {\n\ntemplate\
    \ <class _Tp, size_t _Nm>\nclass ndvec : public std::vector<ndvec<_Tp, _Nm - 1>>\
    \ {\n public:\n  static constexpr auto dimension = _Nm;\n  using container_type\
    \ = std::vector<ndvec<_Tp, _Nm - 1>>;\n\n  template <class _Dim, size_t _Size>\n\
    \  ndvec(const _Dim (&__dim)[_Size], const _Tp& __x = {})\n      : container_type(__dim[_Size\
    \ - _Nm], {__dim, __x}) {}\n};\n\ntemplate <class _Tp> class ndvec<_Tp, 1> : public\
    \ std::vector<_Tp> {\n public:\n  static constexpr auto dimension = 1;\n  using\
    \ container_type = std::vector<_Tp>;\n\n  template <class _Dim, size_t _Size>\n\
    \  ndvec(const _Dim (&__dim)[_Size], const _Tp& __x = {})\n      : container_type(__dim[_Size\
    \ - 1], __x) {}\n};\n\n#if __cplusplus >= 201703L\n\ntemplate <class _Tp, class\
    \ _Dim, size_t _Nm>\nndvec(const _Dim (&)[_Nm], const _Tp&) -> ndvec<_Tp, _Nm>;\n\
    \n#endif\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file ndvec.hpp\n * @brief Nd-vector\n */\n\n#include\
    \ <vector>\n\nnamespace workspace {\n\ntemplate <class _Tp, size_t _Nm>\nclass\
    \ ndvec : public std::vector<ndvec<_Tp, _Nm - 1>> {\n public:\n  static constexpr\
    \ auto dimension = _Nm;\n  using container_type = std::vector<ndvec<_Tp, _Nm -\
    \ 1>>;\n\n  template <class _Dim, size_t _Size>\n  ndvec(const _Dim (&__dim)[_Size],\
    \ const _Tp& __x = {})\n      : container_type(__dim[_Size - _Nm], {__dim, __x})\
    \ {}\n};\n\ntemplate <class _Tp> class ndvec<_Tp, 1> : public std::vector<_Tp>\
    \ {\n public:\n  static constexpr auto dimension = 1;\n  using container_type\
    \ = std::vector<_Tp>;\n\n  template <class _Dim, size_t _Size>\n  ndvec(const\
    \ _Dim (&__dim)[_Size], const _Tp& __x = {})\n      : container_type(__dim[_Size\
    \ - 1], __x) {}\n};\n\n#if __cplusplus >= 201703L\n\ntemplate <class _Tp, class\
    \ _Dim, size_t _Nm>\nndvec(const _Dim (&)[_Nm], const _Tp&) -> ndvec<_Tp, _Nm>;\n\
    \n#endif\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/data_structure/ndvec.hpp
  requiredBy: []
  timestamp: '2021-07-02 03:31:24+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/data_structure/ndvec.hpp
layout: document
redirect_from:
- /library/src/data_structure/ndvec.hpp
- /library/src/data_structure/ndvec.hpp.html
title: Nd-vector
---
