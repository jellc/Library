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
    document_title: Rational
    links: []
  bundledCode: "#line 2 \"src/algebra/rational.hpp\"\n\n/**\n * @file rational.hpp\n\
    \ * @brief Rational\n */\n\n#include <cassert>\n\n#line 2 \"lib/cxx17\"\n\n#line\
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
    \n#include <variant>\n\n#endif\n#line 2 \"src/algebra/system/operation.hpp\"\n\
    \n/**\n * @file operation.hpp\n * @brief Operation Traits\n */\n\n#include <type_traits>\n\
    \n#line 11 \"src/algebra/system/operation.hpp\"\n\nnamespace workspace {\n\n//\
    \ Unary `+`\ntemplate <class _Tp>\nusing require_unary_plus = std::enable_if_t<\n\
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
    // Binary `<`\ntemplate <class _Tp, class = void> struct is_comparable : std::false_type\
    \ {};\n\ntemplate <class _Tp>\nstruct is_comparable<_Tp, std::__void_t<decltype(std::declval<const\
    \ _Tp &>() <\n                                                 std::declval<const\
    \ _Tp &>())>>\n    : std::true_type {};\n\ntemplate <class _Tp, bool _Default\
    \ = false> struct try_less : std::less<_Tp> {\n  constexpr bool operator()(const\
    \ _Tp &__x, const _Tp &__y) noexcept {\n    if _CXX17_CONSTEXPR (is_comparable<_Tp>::value)\n\
    \      return std::less<_Tp>::operator()(__x, __y);\n    else\n      return _Default;\n\
    \  }\n};\n\n}  // namespace workspace\n#line 12 \"src/algebra/rational.hpp\"\n\
    \nnamespace workspace {\n\n/**\n * @brief Rational.\n * @tparam _Tp Ring structure\n\
    \ */\ntemplate <class _Tp> class rational {\n  _Tp __num, __den;\n\n public:\n\
    \  _CXX14_CONSTEXPR rational(const _Tp &__x, const _Tp &__y) noexcept\n      :\
    \ __num(__x), __den(__y) {}\n\n  _CXX14_CONSTEXPR rational(const _Tp &__x, _Tp\
    \ &&__y) noexcept\n      : __num(__x), __den(std::move(__y)) {}\n\n  _CXX14_CONSTEXPR\
    \ rational(_Tp &&__x, const _Tp &__y) noexcept\n      : __num(std::move(__x)),\
    \ __den(__y) {}\n\n  _CXX14_CONSTEXPR rational(_Tp &&__x = 0, _Tp &&__y = 1) noexcept\n\
    \      : __num(std::move(__x)), __den(std::move(__y)) {}\n\n  _CXX14_CONSTEXPR\
    \ rational(std::initializer_list<_Tp> __x) noexcept\n      : __num(__x.size()\
    \ > 0 ? *__x.begin() : _Tp(0)),\n        __den(__x.size() > 1 ? *std::next(__x.begin())\
    \ : _Tp(1)) {}\n\n  _CXX14_CONSTEXPR rational operator+() const noexcept { return\
    \ *this; }\n\n  _CXX14_CONSTEXPR rational operator-() const noexcept {\n    return\
    \ {-__num, __den};\n  }\n\n  _CXX14_CONSTEXPR rational operator+(const rational\
    \ &__x) const noexcept {\n    return {__num * __x.__den + __x.__num * __den, __den\
    \ * __x.__den};\n  }\n\n  _CXX14_CONSTEXPR rational operator-(const rational &__x)\
    \ const noexcept {\n    return {__num * __x.__den - __x.__num * __den, __den *\
    \ __x.__den};\n  }\n\n  _CXX14_CONSTEXPR rational operator*(const rational &__x)\
    \ const noexcept {\n    return {__num * __x.__num, __den * __x.__den};\n  }\n\n\
    \  _CXX14_CONSTEXPR rational operator/(const rational &__x) const noexcept {\n\
    \    assert(__x.__num != _Tp(0));\n    return {__num * __x.__den, __den * __x.__num};\n\
    \  }\n\n  _CXX14_CONSTEXPR rational &operator+=(const rational &__x) noexcept\
    \ {\n    (__num *= __x.__den) += __den * __x.__num, __den *= __x.__den;\n    return\
    \ *this;\n  }\n\n  _CXX14_CONSTEXPR rational &operator-=(const rational &__x)\
    \ noexcept {\n    (__num *= __x.__den) -= __den * __x.__num, __den *= __x.__den;\n\
    \    return *this;\n  }\n\n  _CXX14_CONSTEXPR rational &operator*=(const rational\
    \ &__x) noexcept {\n    __num *= __x.__num, __den *= __x.__den;\n    return *this;\n\
    \  }\n\n  _CXX14_CONSTEXPR rational &operator/=(const rational &__x) noexcept\
    \ {\n    __num *= __x.__den, __den *= __x.__num;\n    return *this;\n  }\n\n \
    \ _CXX14_CONSTEXPR bool operator==(const rational &__x) const noexcept {\n   \
    \ return __num * __x.__den == __den * __x.__num;\n  }\n\n  _CXX14_CONSTEXPR bool\
    \ operator!=(const rational &__x) const noexcept {\n    return __num * __x.__den\
    \ != __den * __x.__num;\n  }\n\n  _CXX14_CONSTEXPR bool operator<(const rational\
    \ &__x) const noexcept {\n    return (__den > 0) ^ (__x.den > 0) ? __num * __x.__den\
    \ > __den * __x.__num\n                                       : __num * __x.__den\
    \ < __den * __x.__num;\n  }\n\n  _CXX14_CONSTEXPR bool operator>(const rational\
    \ &__x) const noexcept {\n    return (__den > 0) ^ (__x.den > 0) ? __num * __x.__den\
    \ < __den * __x.__num\n                                       : __num * __x.__den\
    \ > __den * __x.__num;\n  }\n\n  _CXX14_CONSTEXPR bool operator<=(const rational\
    \ &__x) const noexcept {\n    return !operator>(__x);\n  }\n\n  _CXX14_CONSTEXPR\
    \ bool operator>=(const rational &__x) const noexcept {\n    return !operator<(__x);\n\
    \  }\n\n  _CXX14_CONSTEXPR\n  std::enable_if_t<std::is_swappable<_Tp>::value>\
    \ swap(rational &__x) noexcept {\n    std::swap(__num, __x.__num), std::swap(__den,\
    \ __x.__den);\n  }\n\n  template <size_t _Nm> friend constexpr auto &get(rational\
    \ &__x) noexcept {\n    static_assert(_Nm < 2);\n    if _CXX17_CONSTEXPR (_Nm)\
    \ return __x.__den;\n    return __x.__num;\n  }\n\n  template <size_t _Nm>\n \
    \ friend constexpr const auto &get(const rational &__x) noexcept {\n    static_assert(_Nm\
    \ < 2);\n    if _CXX17_CONSTEXPR (_Nm) return __x.__den;\n    return __x.__num;\n\
    \  }\n\n  template <size_t _Nm> friend constexpr auto &&get(rational &&__x) noexcept\
    \ {\n    static_assert(_Nm < 2);\n    if _CXX17_CONSTEXPR (_Nm) return std::move(__x.__den);\n\
    \    return std::move(__x.__num);\n  }\n};\n\n}  // namespace workspace\n\nnamespace\
    \ std {\n\ntemplate <class _Tp>\nstruct tuple_size<workspace::rational<_Tp>> :\
    \ integral_constant<size_t, 2> {};\n\ntemplate <class _Tp, size_t _Nm>\nstruct\
    \ tuple_element<_Nm, workspace::rational<_Tp>> {\n  using type = _Tp;\n};\n\n\
    }  // namespace std\n"
  code: "#pragma once\n\n/**\n * @file rational.hpp\n * @brief Rational\n */\n\n#include\
    \ <cassert>\n\n#include \"lib/cxx17\"\n#include \"system/operation.hpp\"\n\nnamespace\
    \ workspace {\n\n/**\n * @brief Rational.\n * @tparam _Tp Ring structure\n */\n\
    template <class _Tp> class rational {\n  _Tp __num, __den;\n\n public:\n  _CXX14_CONSTEXPR\
    \ rational(const _Tp &__x, const _Tp &__y) noexcept\n      : __num(__x), __den(__y)\
    \ {}\n\n  _CXX14_CONSTEXPR rational(const _Tp &__x, _Tp &&__y) noexcept\n    \
    \  : __num(__x), __den(std::move(__y)) {}\n\n  _CXX14_CONSTEXPR rational(_Tp &&__x,\
    \ const _Tp &__y) noexcept\n      : __num(std::move(__x)), __den(__y) {}\n\n \
    \ _CXX14_CONSTEXPR rational(_Tp &&__x = 0, _Tp &&__y = 1) noexcept\n      : __num(std::move(__x)),\
    \ __den(std::move(__y)) {}\n\n  _CXX14_CONSTEXPR rational(std::initializer_list<_Tp>\
    \ __x) noexcept\n      : __num(__x.size() > 0 ? *__x.begin() : _Tp(0)),\n    \
    \    __den(__x.size() > 1 ? *std::next(__x.begin()) : _Tp(1)) {}\n\n  _CXX14_CONSTEXPR\
    \ rational operator+() const noexcept { return *this; }\n\n  _CXX14_CONSTEXPR\
    \ rational operator-() const noexcept {\n    return {-__num, __den};\n  }\n\n\
    \  _CXX14_CONSTEXPR rational operator+(const rational &__x) const noexcept {\n\
    \    return {__num * __x.__den + __x.__num * __den, __den * __x.__den};\n  }\n\
    \n  _CXX14_CONSTEXPR rational operator-(const rational &__x) const noexcept {\n\
    \    return {__num * __x.__den - __x.__num * __den, __den * __x.__den};\n  }\n\
    \n  _CXX14_CONSTEXPR rational operator*(const rational &__x) const noexcept {\n\
    \    return {__num * __x.__num, __den * __x.__den};\n  }\n\n  _CXX14_CONSTEXPR\
    \ rational operator/(const rational &__x) const noexcept {\n    assert(__x.__num\
    \ != _Tp(0));\n    return {__num * __x.__den, __den * __x.__num};\n  }\n\n  _CXX14_CONSTEXPR\
    \ rational &operator+=(const rational &__x) noexcept {\n    (__num *= __x.__den)\
    \ += __den * __x.__num, __den *= __x.__den;\n    return *this;\n  }\n\n  _CXX14_CONSTEXPR\
    \ rational &operator-=(const rational &__x) noexcept {\n    (__num *= __x.__den)\
    \ -= __den * __x.__num, __den *= __x.__den;\n    return *this;\n  }\n\n  _CXX14_CONSTEXPR\
    \ rational &operator*=(const rational &__x) noexcept {\n    __num *= __x.__num,\
    \ __den *= __x.__den;\n    return *this;\n  }\n\n  _CXX14_CONSTEXPR rational &operator/=(const\
    \ rational &__x) noexcept {\n    __num *= __x.__den, __den *= __x.__num;\n   \
    \ return *this;\n  }\n\n  _CXX14_CONSTEXPR bool operator==(const rational &__x)\
    \ const noexcept {\n    return __num * __x.__den == __den * __x.__num;\n  }\n\n\
    \  _CXX14_CONSTEXPR bool operator!=(const rational &__x) const noexcept {\n  \
    \  return __num * __x.__den != __den * __x.__num;\n  }\n\n  _CXX14_CONSTEXPR bool\
    \ operator<(const rational &__x) const noexcept {\n    return (__den > 0) ^ (__x.den\
    \ > 0) ? __num * __x.__den > __den * __x.__num\n                             \
    \          : __num * __x.__den < __den * __x.__num;\n  }\n\n  _CXX14_CONSTEXPR\
    \ bool operator>(const rational &__x) const noexcept {\n    return (__den > 0)\
    \ ^ (__x.den > 0) ? __num * __x.__den < __den * __x.__num\n                  \
    \                     : __num * __x.__den > __den * __x.__num;\n  }\n\n  _CXX14_CONSTEXPR\
    \ bool operator<=(const rational &__x) const noexcept {\n    return !operator>(__x);\n\
    \  }\n\n  _CXX14_CONSTEXPR bool operator>=(const rational &__x) const noexcept\
    \ {\n    return !operator<(__x);\n  }\n\n  _CXX14_CONSTEXPR\n  std::enable_if_t<std::is_swappable<_Tp>::value>\
    \ swap(rational &__x) noexcept {\n    std::swap(__num, __x.__num), std::swap(__den,\
    \ __x.__den);\n  }\n\n  template <size_t _Nm> friend constexpr auto &get(rational\
    \ &__x) noexcept {\n    static_assert(_Nm < 2);\n    if _CXX17_CONSTEXPR (_Nm)\
    \ return __x.__den;\n    return __x.__num;\n  }\n\n  template <size_t _Nm>\n \
    \ friend constexpr const auto &get(const rational &__x) noexcept {\n    static_assert(_Nm\
    \ < 2);\n    if _CXX17_CONSTEXPR (_Nm) return __x.__den;\n    return __x.__num;\n\
    \  }\n\n  template <size_t _Nm> friend constexpr auto &&get(rational &&__x) noexcept\
    \ {\n    static_assert(_Nm < 2);\n    if _CXX17_CONSTEXPR (_Nm) return std::move(__x.__den);\n\
    \    return std::move(__x.__num);\n  }\n};\n\n}  // namespace workspace\n\nnamespace\
    \ std {\n\ntemplate <class _Tp>\nstruct tuple_size<workspace::rational<_Tp>> :\
    \ integral_constant<size_t, 2> {};\n\ntemplate <class _Tp, size_t _Nm>\nstruct\
    \ tuple_element<_Nm, workspace::rational<_Tp>> {\n  using type = _Tp;\n};\n\n\
    }  // namespace std\n"
  dependsOn:
  - src/algebra/system/operation.hpp
  isVerificationFile: false
  path: src/algebra/rational.hpp
  requiredBy: []
  timestamp: '2021-11-30 17:55:32+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/algebra/rational.hpp
layout: document
redirect_from:
- /library/src/algebra/rational.hpp
- /library/src/algebra/rational.hpp.html
title: Rational
---
