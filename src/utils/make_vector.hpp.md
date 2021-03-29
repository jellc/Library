---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Multi-dimensional Vector
    links: []
  bundledCode: "#line 2 \"src/utils/make_vector.hpp\"\n\n/**\n * @file make_vector.hpp\n\
    \ * @brief Multi-dimensional Vector\n */\n\n#if __cplusplus >= 201703L\n\n#include\
    \ <tuple>\n#include <vector>\n\nnamespace workspace {\n\n/**\n * @brief Make a\
    \ multi-dimensional vector.\n *\n * @param __dim Dimension\n * @param __x Initial\
    \ value\n */\ntemplate <typename _Tp, class _Dim, size_t _Nm>\nconstexpr decltype(auto)\
    \ make_vector([[maybe_unused]] _Dim* __dim,\n                                \
    \     const _Tp& __x = _Tp()) {\n  static_assert(std::is_convertible<_Dim, size_t>::value);\n\
    \n  if constexpr (_Nm)\n    return std::vector(*__dim,\n                     \
    \  make_vector<_Tp, _Dim, _Nm - 1>(std::next(__dim), __x));\n  else\n    return\
    \ __x;\n}\n\n/**\n * @brief Make a multi-dimensional vector.\n *\n * @param __dim\
    \ Dimension\n * @param __x Initial value\n */\ntemplate <typename _Tp, class _Dim,\
    \ size_t _Nm>\nconstexpr decltype(auto) make_vector(const _Dim (&__dim)[_Nm],\n\
    \                                     const _Tp& __x = _Tp()) {\n  return make_vector<_Tp,\
    \ _Dim, _Nm>((_Dim*)__dim, __x);\n}\n\n/**\n * @brief Make a multi-dimensional\
    \ vector.\n *\n * @param __dim Dimension\n * @param __x Initial value\n */\ntemplate\
    \ <typename _Tp, class _Dim, size_t _Nm = 0>\nconstexpr decltype(auto) make_vector([[maybe_unused]]\
    \ const _Dim& __dim,\n                                     const _Tp& __x = _Tp())\
    \ {\n  if constexpr (_Nm == std::tuple_size<_Dim>::value)\n    return __x;\n\n\
    \  else {\n    static_assert(\n        std::is_convertible<std::tuple_element_t<_Nm,\
    \ _Dim>, size_t>::value);\n\n    return std::vector(std::get<_Nm>(__dim),\n  \
    \                     make_vector<_Tp, _Dim, _Nm + 1>(__dim, __x));\n  }\n}\n\n\
    }  // namespace workspace\n\n#endif\n"
  code: "#pragma once\n\n/**\n * @file make_vector.hpp\n * @brief Multi-dimensional\
    \ Vector\n */\n\n#if __cplusplus >= 201703L\n\n#include <tuple>\n#include <vector>\n\
    \nnamespace workspace {\n\n/**\n * @brief Make a multi-dimensional vector.\n *\n\
    \ * @param __dim Dimension\n * @param __x Initial value\n */\ntemplate <typename\
    \ _Tp, class _Dim, size_t _Nm>\nconstexpr decltype(auto) make_vector([[maybe_unused]]\
    \ _Dim* __dim,\n                                     const _Tp& __x = _Tp()) {\n\
    \  static_assert(std::is_convertible<_Dim, size_t>::value);\n\n  if constexpr\
    \ (_Nm)\n    return std::vector(*__dim,\n                       make_vector<_Tp,\
    \ _Dim, _Nm - 1>(std::next(__dim), __x));\n  else\n    return __x;\n}\n\n/**\n\
    \ * @brief Make a multi-dimensional vector.\n *\n * @param __dim Dimension\n *\
    \ @param __x Initial value\n */\ntemplate <typename _Tp, class _Dim, size_t _Nm>\n\
    constexpr decltype(auto) make_vector(const _Dim (&__dim)[_Nm],\n             \
    \                        const _Tp& __x = _Tp()) {\n  return make_vector<_Tp,\
    \ _Dim, _Nm>((_Dim*)__dim, __x);\n}\n\n/**\n * @brief Make a multi-dimensional\
    \ vector.\n *\n * @param __dim Dimension\n * @param __x Initial value\n */\ntemplate\
    \ <typename _Tp, class _Dim, size_t _Nm = 0>\nconstexpr decltype(auto) make_vector([[maybe_unused]]\
    \ const _Dim& __dim,\n                                     const _Tp& __x = _Tp())\
    \ {\n  if constexpr (_Nm == std::tuple_size<_Dim>::value)\n    return __x;\n\n\
    \  else {\n    static_assert(\n        std::is_convertible<std::tuple_element_t<_Nm,\
    \ _Dim>, size_t>::value);\n\n    return std::vector(std::get<_Nm>(__dim),\n  \
    \                     make_vector<_Tp, _Dim, _Nm + 1>(__dim, __x));\n  }\n}\n\n\
    }  // namespace workspace\n\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: src/utils/make_vector.hpp
  requiredBy: []
  timestamp: '2021-03-30 01:16:02+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/utils/make_vector.hpp
layout: document
redirect_from:
- /library/src/utils/make_vector.hpp
- /library/src/utils/make_vector.hpp.html
title: Multi-dimensional Vector
---
