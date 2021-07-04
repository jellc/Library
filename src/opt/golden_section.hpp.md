---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/algebra/system/operation.hpp
    title: Operation Traits
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Golden Section
    links: []
  bundledCode: "#line 2 \"src/opt/golden_section.hpp\"\n\n/**\n * @file golden_section.hpp\n\
    \ * @brief Golden Section\n */\n\n#include <type_traits>\n\n#line 2 \"src/algebra/system/operation.hpp\"\
    \n\n/**\n * @file operation.hpp\n * @brief Operation Traits\n */\n\n#line 9 \"\
    src/algebra/system/operation.hpp\"\n\nnamespace workspace {\n\n// Unary `+`\n\
    template <class _Tp>\nusing require_unary_plus = std::enable_if_t<\n    std::is_convertible<decltype(+std::declval<const\
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
    template <class _Tp1, class _Tp2 = _Tp1>\nusing require_binary_minus =\n    std::__void_t<decltype(std::declval<const\
    \ _Tp1 &>() -\n                           std::declval<const _Tp2 &>())>;\n\n\
    template <class _Tp1, class _Tp2 = _Tp1, class = void>\nstruct has_binary_minus\
    \ : std::false_type {};\n\ntemplate <class _Tp1, class _Tp2>\nstruct has_binary_minus<_Tp1,\
    \ _Tp2, require_binary_minus<_Tp1, _Tp2>>\n    : std::true_type {};\n\n// Binary\
    \ `*`\ntemplate <class _Tp1, class _Tp2 = _Tp1>\nusing require_binary_multiplies\
    \ =\n    std::enable_if_t<std::is_convertible<decltype(std::declval<const _Tp1\
    \ &>() *\n                                                  std::declval<const\
    \ _Tp2 &>()),\n                                         _Tp1>::value>;\n\ntemplate\
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
    \ require_binary_modulus<_Tp1, _Tp2>>\n    : std::true_type {};\n\ntemplate <class\
    \ _Tp1, class _Tp2 = _Tp1, class = void, class = void,\n          class = void,\
    \ class = void>\nstruct has_arithmetic : std::false_type {};\n\ntemplate <class\
    \ _Tp1, class _Tp2>\nstruct has_arithmetic<_Tp1, _Tp2, require_binary_plus<_Tp1,\
    \ _Tp2>,\n                      require_binary_minus<_Tp1, _Tp2>,\n          \
    \            require_binary_multiplies<_Tp1, _Tp2>,\n                      require_binary_divides<_Tp1,\
    \ _Tp2>> : std::true_type {};\n\ntemplate <class _Tp1, class _Tp2 = _Tp1>\nusing\
    \ require_arithmetic = std::enable_if_t<has_arithmetic<_Tp1, _Tp2>::value>;\n\n\
    }  // namespace workspace\n#line 11 \"src/opt/golden_section.hpp\"\n\nnamespace\
    \ workspace {\n\n/**\n * @brief Golden section search.\n */\ntemplate <class _Iterator,\
    \ class _Function>\nstd::enable_if_t<has_binary_minus<_Iterator>::value, _Iterator>\
    \ golden_section(\n    _Iterator __first, _Iterator __last, _Function&& __f) {\n\
    \  if (__last - __first < 2) return __first;\n\n  decltype(__last - __first) __a{1},\
    \ __b{2};\n  while (__a + __b <= __last - __first) std::swap(__a += __b, __b);\n\
    \n  auto __f1 = __f(__last - __b), __f2 = __f(__last - __a);\n\n  while (__a !=\
    \ 1) {\n    std::swap(__a, __b -= __a);\n\n    if (__f2 < __f1)\n      __f1 =\
    \ __f2, __f2 = __f(__last - __a);\n\n    else if ((__last -= __b) - __first <\
    \ __b)\n      std::swap(__a, __b -= __a), __f2 = __f(__last - __a);\n\n    else\n\
    \      __f2 = __f1, __f1 = __f(__last - __b);\n  }\n\n  return __f1 < __f2 ? __last\
    \ - __b : __last - __a;\n}\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file golden_section.hpp\n * @brief Golden Section\n\
    \ */\n\n#include <type_traits>\n\n#include \"src/algebra/system/operation.hpp\"\
    \n\nnamespace workspace {\n\n/**\n * @brief Golden section search.\n */\ntemplate\
    \ <class _Iterator, class _Function>\nstd::enable_if_t<has_binary_minus<_Iterator>::value,\
    \ _Iterator> golden_section(\n    _Iterator __first, _Iterator __last, _Function&&\
    \ __f) {\n  if (__last - __first < 2) return __first;\n\n  decltype(__last - __first)\
    \ __a{1}, __b{2};\n  while (__a + __b <= __last - __first) std::swap(__a += __b,\
    \ __b);\n\n  auto __f1 = __f(__last - __b), __f2 = __f(__last - __a);\n\n  while\
    \ (__a != 1) {\n    std::swap(__a, __b -= __a);\n\n    if (__f2 < __f1)\n    \
    \  __f1 = __f2, __f2 = __f(__last - __a);\n\n    else if ((__last -= __b) - __first\
    \ < __b)\n      std::swap(__a, __b -= __a), __f2 = __f(__last - __a);\n\n    else\n\
    \      __f2 = __f1, __f1 = __f(__last - __b);\n  }\n\n  return __f1 < __f2 ? __last\
    \ - __b : __last - __a;\n}\n\n}  // namespace workspace\n"
  dependsOn:
  - src/algebra/system/operation.hpp
  isVerificationFile: false
  path: src/opt/golden_section.hpp
  requiredBy: []
  timestamp: '2021-07-05 01:35:36+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/opt/golden_section.hpp
layout: document
redirect_from:
- /library/src/opt/golden_section.hpp
- /library/src/opt/golden_section.hpp.html
title: Golden Section
---
