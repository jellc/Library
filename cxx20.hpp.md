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
    document_title: C++20 features
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 310, in update\n    raise BundleErrorAt(path, i + 1, \"#pragma once found\
    \ in a non-first line\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ cxx20.hpp: line 6: #pragma once found in a non-first line\n"
  code: "/*\n * @file cxx20.hpp\n * @brief C++20 features\n */\n\n#pragma once\n\n\
    #if __cplusplus <= 201703L\n\n#if __has_include(<bit>)\n#include <bit>\n#endif\n\
    \n#include <vector>\n\nnamespace std {\n\n/*\n * @fn erase_if\n * @brief Erase\
    \ the elements of a container that do not satisfy the condition.\n * @param __cont\
    \ Container.\n * @param __pred Predicate.\n * @return Number of the erased elements.\n\
    \ */\ntemplate <typename _Tp, typename _Alloc, typename _Predicate>\ninline typename\
    \ vector<_Tp, _Alloc>::size_type erase_if(\n    vector<_Tp, _Alloc>& __cont, _Predicate\
    \ __pred) {\n  const auto __osz = __cont.size();\n  __cont.erase(std::remove_if(__cont.begin(),\
    \ __cont.end(), __pred),\n               __cont.end());\n  return __osz - __cont.size();\n\
    }\n\n/*\n * @fn erase\n * @brief Erase the elements of a container that are equal\
    \ to the given value.\n * @param __cont Container.\n * @param __value Value.\n\
    \ * @return Number of the erased elements.\n */\ntemplate <typename _Tp, typename\
    \ _Alloc, typename _Up>\ninline typename vector<_Tp, _Alloc>::size_type erase(\n\
    \    vector<_Tp, _Alloc>& __cont, const _Up& __value) {\n  const auto __osz =\
    \ __cont.size();\n  __cont.erase(std::remove(__cont.begin(), __cont.end(), __value),\n\
    \               __cont.end());\n  return __osz - __cont.size();\n}\n\n}  // namespace\
    \ std\n\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: cxx20.hpp
  requiredBy:
  - template.cpp
  timestamp: '2020-11-04 18:12:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: cxx20.hpp
layout: document
redirect_from:
- /library/cxx20.hpp
- /library/cxx20.hpp.html
title: C++20 features
---
