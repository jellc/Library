---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Operation Traits
    links: []
  bundledCode: "#line 2 \"src/algebra/system/operation.hpp\"\n\n/**\n * @file operation.hpp\n\
    \ * @brief Operation Traits\n */\n\n#include <type_traits>\n\nnamespace workspace\
    \ {\n\n// Unary `+`\ntemplate <class _Tp>\nusing require_unary_plus = std::enable_if_t<\n\
    \    std::is_convertible<decltype(+std::declval<const _Tp &>()), _Tp>::value>;\n\
    \ntemplate <class _Tp, class = void> struct has_unary_plus : std::false_type {};\n\
    \ntemplate <class _Tp>\nstruct has_unary_plus<_Tp, require_unary_plus<_Tp>> :\
    \ std::true_type {};\n\n// Unary `-`\ntemplate <class _Tp>\nusing require_unary_minus\
    \ = std::enable_if_t<\n    std::is_convertible<decltype(-std::declval<const _Tp\
    \ &>()), _Tp>::value>;\n\ntemplate <class _Tp, class = void> struct has_unary_minus\
    \ : std::false_type {};\n\ntemplate <class _Tp>\nstruct has_unary_minus<_Tp, require_unary_minus<_Tp>>\
    \ : std::true_type {};\n\n// Binary `+`\ntemplate <class _Tp1, class _Tp2 = _Tp1>\n\
    using require_binary_plus =\n    std::enable_if_t<std::is_convertible<decltype(std::declval<const\
    \ _Tp1 &>() +\n                                                  std::declval<const\
    \ _Tp2 &>()),\n                                         _Tp1>::value>;\n\ntemplate\
    \ <class _Tp1, class _Tp2 = _Tp1, class = void>\nstruct has_binary_plus : std::false_type\
    \ {};\n\ntemplate <class _Tp1, class _Tp2>\nstruct has_binary_plus<_Tp1, _Tp2,\
    \ require_binary_plus<_Tp1, _Tp2>>\n    : std::true_type {};\n\n// Binary `-`\n\
    template <class _Tp1, class _Tp2 = _Tp1>\nusing require_binary_minus =\n    std::enable_if_t<std::is_convertible<decltype(std::declval<const\
    \ _Tp1 &>() -\n                                                  std::declval<const\
    \ _Tp2 &>()),\n                                         _Tp1>::value>;\n\ntemplate\
    \ <class _Tp1, class _Tp2 = _Tp1, class = void>\nstruct has_binary_minus : std::false_type\
    \ {};\n\ntemplate <class _Tp1, class _Tp2>\nstruct has_binary_minus<_Tp1, _Tp2,\
    \ require_binary_minus<_Tp1, _Tp2>>\n    : std::true_type {};\n\n// Binary `*`\n\
    template <class _Tp1, class _Tp2 = _Tp1>\nusing require_binary_multiplies =\n\
    \    std::enable_if_t<std::is_convertible<decltype(std::declval<const _Tp1 &>()\
    \ *\n                                                  std::declval<const _Tp2\
    \ &>()),\n                                         _Tp1>::value>;\n\ntemplate\
    \ <class _Tp1, class _Tp2 = _Tp1, class = void>\nstruct has_binary_multiplies\
    \ : std::false_type {};\n\ntemplate <class _Tp1, class _Tp2>\nstruct has_binary_multiplies<_Tp1,\
    \ _Tp2, require_binary_multiplies<_Tp1, _Tp2>>\n    : std::true_type {};\n\n//\
    \ Binary `/`\ntemplate <class _Tp1, class _Tp2 = _Tp1>\nusing require_binary_divides\
    \ =\n    std::enable_if_t<std::is_convertible<decltype(std::declval<const _Tp1\
    \ &>() /\n                                                  std::declval<const\
    \ _Tp2 &>()),\n                                         _Tp1>::value>;\n\ntemplate\
    \ <class _Tp1, class _Tp2 = _Tp1, class = void>\nstruct has_binary_divides : std::false_type\
    \ {};\n\ntemplate <class _Tp1, class _Tp2>\nstruct has_binary_divides<_Tp1, _Tp2,\
    \ require_binary_divides<_Tp1, _Tp2>>\n    : std::true_type {};\n\n// Binary `%`\n\
    template <class _Tp1, class _Tp2 = _Tp1>\nusing require_binary_modulus =\n   \
    \ std::enable_if_t<std::is_convertible<decltype(std::declval<const _Tp1 &>() %\n\
    \                                                  std::declval<const _Tp2 &>()),\n\
    \                                         _Tp1>::value>;\n\ntemplate <class _Tp1,\
    \ class _Tp2 = _Tp1, class = void>\nstruct has_binary_modulus : std::false_type\
    \ {};\n\ntemplate <class _Tp1, class _Tp2>\nstruct has_binary_modulus<_Tp1, _Tp2,\
    \ require_binary_modulus<_Tp1, _Tp2>>\n    : std::true_type {};\n\n}  // namespace\
    \ workspace\n"
  code: "#pragma once\n\n/**\n * @file operation.hpp\n * @brief Operation Traits\n\
    \ */\n\n#include <type_traits>\n\nnamespace workspace {\n\n// Unary `+`\ntemplate\
    \ <class _Tp>\nusing require_unary_plus = std::enable_if_t<\n    std::is_convertible<decltype(+std::declval<const\
    \ _Tp &>()), _Tp>::value>;\n\ntemplate <class _Tp, class = void> struct has_unary_plus\
    \ : std::false_type {};\n\ntemplate <class _Tp>\nstruct has_unary_plus<_Tp, require_unary_plus<_Tp>>\
    \ : std::true_type {};\n\n// Unary `-`\ntemplate <class _Tp>\nusing require_unary_minus\
    \ = std::enable_if_t<\n    std::is_convertible<decltype(-std::declval<const _Tp\
    \ &>()), _Tp>::value>;\n\ntemplate <class _Tp, class = void> struct has_unary_minus\
    \ : std::false_type {};\n\ntemplate <class _Tp>\nstruct has_unary_minus<_Tp, require_unary_minus<_Tp>>\
    \ : std::true_type {};\n\n// Binary `+`\ntemplate <class _Tp1, class _Tp2 = _Tp1>\n\
    using require_binary_plus =\n    std::enable_if_t<std::is_convertible<decltype(std::declval<const\
    \ _Tp1 &>() +\n                                                  std::declval<const\
    \ _Tp2 &>()),\n                                         _Tp1>::value>;\n\ntemplate\
    \ <class _Tp1, class _Tp2 = _Tp1, class = void>\nstruct has_binary_plus : std::false_type\
    \ {};\n\ntemplate <class _Tp1, class _Tp2>\nstruct has_binary_plus<_Tp1, _Tp2,\
    \ require_binary_plus<_Tp1, _Tp2>>\n    : std::true_type {};\n\n// Binary `-`\n\
    template <class _Tp1, class _Tp2 = _Tp1>\nusing require_binary_minus =\n    std::enable_if_t<std::is_convertible<decltype(std::declval<const\
    \ _Tp1 &>() -\n                                                  std::declval<const\
    \ _Tp2 &>()),\n                                         _Tp1>::value>;\n\ntemplate\
    \ <class _Tp1, class _Tp2 = _Tp1, class = void>\nstruct has_binary_minus : std::false_type\
    \ {};\n\ntemplate <class _Tp1, class _Tp2>\nstruct has_binary_minus<_Tp1, _Tp2,\
    \ require_binary_minus<_Tp1, _Tp2>>\n    : std::true_type {};\n\n// Binary `*`\n\
    template <class _Tp1, class _Tp2 = _Tp1>\nusing require_binary_multiplies =\n\
    \    std::enable_if_t<std::is_convertible<decltype(std::declval<const _Tp1 &>()\
    \ *\n                                                  std::declval<const _Tp2\
    \ &>()),\n                                         _Tp1>::value>;\n\ntemplate\
    \ <class _Tp1, class _Tp2 = _Tp1, class = void>\nstruct has_binary_multiplies\
    \ : std::false_type {};\n\ntemplate <class _Tp1, class _Tp2>\nstruct has_binary_multiplies<_Tp1,\
    \ _Tp2, require_binary_multiplies<_Tp1, _Tp2>>\n    : std::true_type {};\n\n//\
    \ Binary `/`\ntemplate <class _Tp1, class _Tp2 = _Tp1>\nusing require_binary_divides\
    \ =\n    std::enable_if_t<std::is_convertible<decltype(std::declval<const _Tp1\
    \ &>() /\n                                                  std::declval<const\
    \ _Tp2 &>()),\n                                         _Tp1>::value>;\n\ntemplate\
    \ <class _Tp1, class _Tp2 = _Tp1, class = void>\nstruct has_binary_divides : std::false_type\
    \ {};\n\ntemplate <class _Tp1, class _Tp2>\nstruct has_binary_divides<_Tp1, _Tp2,\
    \ require_binary_divides<_Tp1, _Tp2>>\n    : std::true_type {};\n\n// Binary `%`\n\
    template <class _Tp1, class _Tp2 = _Tp1>\nusing require_binary_modulus =\n   \
    \ std::enable_if_t<std::is_convertible<decltype(std::declval<const _Tp1 &>() %\n\
    \                                                  std::declval<const _Tp2 &>()),\n\
    \                                         _Tp1>::value>;\n\ntemplate <class _Tp1,\
    \ class _Tp2 = _Tp1, class = void>\nstruct has_binary_modulus : std::false_type\
    \ {};\n\ntemplate <class _Tp1, class _Tp2>\nstruct has_binary_modulus<_Tp1, _Tp2,\
    \ require_binary_modulus<_Tp1, _Tp2>>\n    : std::true_type {};\n\n}  // namespace\
    \ workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/algebra/system/operation.hpp
  requiredBy: []
  timestamp: '2021-05-07 14:31:52+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/algebra/system/operation.hpp
layout: document
redirect_from:
- /library/src/algebra/system/operation.hpp
- /library/src/algebra/system/operation.hpp.html
title: Operation Traits
---
