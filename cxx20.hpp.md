---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: template.cpp
    title: Code template
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"cxx20.hpp\"\n#if __cplusplus <= 201703L\n\n#if __has_include(<bit>)\n\
    #include <bit>\n#endif\n\n#include <vector>\nnamespace std {\ntemplate <typename\
    \ _Tp, typename _Alloc, typename _Predicate>\ninline typename vector<_Tp, _Alloc>::size_type\
    \ erase_if(\n    vector<_Tp, _Alloc>& __cont, _Predicate __pred) {\n  const auto\
    \ __osz = __cont.size();\n  __cont.erase(std::remove_if(__cont.begin(), __cont.end(),\
    \ __pred),\n               __cont.end());\n  return __osz - __cont.size();\n}\n\
    template <typename _Tp, typename _Alloc, typename _Up>\ninline typename vector<_Tp,\
    \ _Alloc>::size_type erase(\n    vector<_Tp, _Alloc>& __cont, const _Up& __value)\
    \ {\n  const auto __osz = __cont.size();\n  __cont.erase(std::remove(__cont.begin(),\
    \ __cont.end(), __value),\n               __cont.end());\n  return __osz - __cont.size();\n\
    }\n}\n\n#endif\n"
  code: "#if __cplusplus <= 201703L\n\n#if __has_include(<bit>)\n#include <bit>\n\
    #endif\n\n#include <vector>\nnamespace std {\ntemplate <typename _Tp, typename\
    \ _Alloc, typename _Predicate>\ninline typename vector<_Tp, _Alloc>::size_type\
    \ erase_if(\n    vector<_Tp, _Alloc>& __cont, _Predicate __pred) {\n  const auto\
    \ __osz = __cont.size();\n  __cont.erase(std::remove_if(__cont.begin(), __cont.end(),\
    \ __pred),\n               __cont.end());\n  return __osz - __cont.size();\n}\n\
    template <typename _Tp, typename _Alloc, typename _Up>\ninline typename vector<_Tp,\
    \ _Alloc>::size_type erase(\n    vector<_Tp, _Alloc>& __cont, const _Up& __value)\
    \ {\n  const auto __osz = __cont.size();\n  __cont.erase(std::remove(__cont.begin(),\
    \ __cont.end(), __value),\n               __cont.end());\n  return __osz - __cont.size();\n\
    }\n}\n\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: cxx20.hpp
  requiredBy:
  - template.cpp
  timestamp: '2020-10-18 20:34:11+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: cxx20.hpp
layout: document
redirect_from:
- /library/cxx20.hpp
- /library/cxx20.hpp.html
title: cxx20.hpp
---
