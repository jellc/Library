---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Extended Numeric Type
    links: []
  bundledCode: "#line 2 \"src/algebra/extended.hpp\"\n\n/**\n * @file extended.hpp\n\
    \ * @brief Extended Numeric Type\n */\n\n#include <cstdint>\n#include <type_traits>\n\
    \n#line 2 \"lib/cxx17\"\n\n#line 2 \"lib/cxx14\"\n\n#ifndef _CXX14_CONSTEXPR\n\
    #if __cplusplus >= 201402L\n#define _CXX14_CONSTEXPR constexpr\n#else\n#define\
    \ _CXX14_CONSTEXPR\n#endif\n#endif\n#line 4 \"lib/cxx17\"\n\n#ifndef _CXX17_CONSTEXPR\n\
    #if __cplusplus >= 201703L\n#define _CXX17_CONSTEXPR constexpr\n#else\n#define\
    \ _CXX17_CONSTEXPR\n#endif\n#endif\n\n#ifndef _CXX17_STATIC_ASSERT\n#if __cplusplus\
    \ >= 201703L\n#define _CXX17_STATIC_ASSERT static_assert\n#else\n#define _CXX17_STATIC_ASSERT\
    \ assert\n#endif\n#endif\n\n#include <iterator>\n\n#if __cplusplus < 201703L\n\
    \nnamespace std {\n\n/**\n *  @brief  Return the size of a container.\n *  @param\
    \  __cont  Container.\n */\ntemplate <typename _Container>\nconstexpr auto size(const\
    \ _Container& __cont) noexcept(noexcept(__cont.size()))\n    -> decltype(__cont.size())\
    \ {\n  return __cont.size();\n}\n\n/**\n *  @brief  Return the size of an array.\n\
    \ */\ntemplate <typename _Tp, size_t _Nm>\nconstexpr size_t size(const _Tp (&)[_Nm])\
    \ noexcept {\n  return _Nm;\n}\n\n/**\n *  @brief  Return whether a container\
    \ is empty.\n *  @param  __cont  Container.\n */\ntemplate <typename _Container>\n\
    [[nodiscard]] constexpr auto empty(const _Container& __cont) noexcept(\n    noexcept(__cont.empty()))\
    \ -> decltype(__cont.empty()) {\n  return __cont.empty();\n}\n\n/**\n *  @brief\
    \  Return whether an array is empty (always false).\n */\ntemplate <typename _Tp,\
    \ size_t _Nm>\n[[nodiscard]] constexpr bool empty(const _Tp (&)[_Nm]) noexcept\
    \ {\n  return false;\n}\n\n/**\n *  @brief  Return whether an initializer_list\
    \ is empty.\n *  @param  __il  Initializer list.\n */\ntemplate <typename _Tp>\n\
    [[nodiscard]] constexpr bool empty(initializer_list<_Tp> __il) noexcept {\n  return\
    \ __il.size() == 0;\n}\n\nstruct monostate {};\n\n}  // namespace std\n\n#else\n\
    \n#include <variant>\n\n#endif\n#line 12 \"src/algebra/extended.hpp\"\n\nnamespace\
    \ workspace {\n\ntemplate <class _Tp> constexpr auto sign_of(const _Tp &__x) noexcept\
    \ {\n  return __x != _Tp(0) ? (__x > _Tp(0) ? +1 : -1) : 0;\n}\n\n// Extended\
    \ numeric type.\ntemplate <class _Tp> class extended {\n  bool infinite{};\n \
    \ int_least8_t sign{};  // in {0, +1, -1}\n  _Tp value{};          // is 0 if\
    \ infinite\n\n  template <class _Os>\n  friend _Os &operator<<(_Os &__os, const\
    \ extended &__x) noexcept {\n    return __x.infinite ? __os << (__x.sign > 0 ?\
    \ '+' : '-') << \"infinity\"\n                        : __os << __x.value;\n \
    \ }\n\n  friend std::istream &operator>>(std::istream &__is, extended &__x) noexcept\
    \ {\n    __x.infinite = false;\n    __is >> __x.value;\n    __x.sign = sign_of(__x.value);\n\
    \    return __is;\n  }\n\n  constexpr extended(bool __x, int_least8_t __y, const\
    \ _Tp &__z) noexcept\n      : infinite(__x), sign(__y), value(__z) {}\n\n public:\n\
    \  constexpr static extended infinity{true, +1, 0};\n\n  constexpr extended()\
    \ noexcept {}\n\n  constexpr extended(const _Tp &__x) noexcept\n      : sign(sign_of(__x)),\
    \ value(__x) {}\n\n  constexpr std::enable_if_t<std::is_swappable<_Tp>::value>\
    \ swap(\n      extended &__x) noexcept {\n    std::swap(infinite, __x.infinite);\n\
    \    std::swap(sign, __x.sign);\n    std::swap(value, __x.value);\n  }\n\n  template\
    \ <class _U> constexpr operator _U const &() const noexcept {\n    if _CXX17_CONSTEXPR\
    \ (std::is_same_v<_U, bool>) return sign;\n    return value;\n  }\n\n  template\
    \ <class _U> constexpr operator _U() const noexcept {\n    if _CXX17_CONSTEXPR\
    \ (std::is_same_v<_U, bool>) return sign;\n    return value;\n  }\n\n  constexpr\
    \ extended operator+() const noexcept { return *this; }\n\n  constexpr extended\
    \ operator-() const noexcept {\n    return extended(infinite, -sign, -value);\n\
    \  }\n\n  constexpr extended &operator+=(const extended &__x) noexcept {\n   \
    \ if (__x.infinite) return *this = __x;\n    return operator+=(__x.value);\n \
    \ }\n\n  template <class _U>\n  constexpr std::enable_if_t<std::is_convertible<_U,\
    \ _Tp>::value, extended &>\n  operator+=(const _U &__x) noexcept {\n    if (!infinite)\
    \ sign = sign_of(value += __x);\n    return *this;\n  }\n\n  constexpr extended\
    \ &operator-=(const extended &__x) noexcept {\n    return operator+=(-__x);\n\
    \  }\n\n  template <class _U>\n  constexpr std::enable_if_t<std::is_convertible<_U,\
    \ _Tp>::value, extended &>\n  operator-=(const _U &__x) noexcept {\n    return\
    \ operator+=(-__x);\n  }\n\n  constexpr extended &operator*=(const extended &__x)\
    \ noexcept {\n    if (sign *= __x.sign)\n      infinite = infinite || __x.infinite,\
    \ value *= __x.value;\n    else\n      infinite = false, value = 0;\n    return\
    \ *this;\n  }\n\n  template <class _U>\n  constexpr std::enable_if_t<std::is_convertible<_U,\
    \ _Tp>::value, extended &>\n  operator*=(const _U &__x) noexcept {\n    if (sign\
    \ *= sign_of(__x))\n      value *= __x;\n    else\n      infinite = false, value\
    \ = 0;\n    return *this;\n  }\n\n  constexpr extended &operator/=(const extended\
    \ &__x) noexcept {\n    if (__x.infinite)\n      infinite = false, sign = 0, value\
    \ = 0;\n    else if (__x.sign)\n      (value /= __x.value) ? sign *= __x.sign\
    \ : sign = 0;\n    else\n      infinite = true, value = 0;\n    return *this;\n\
    \  }\n\n  template <class _U>\n  constexpr std::enable_if_t<std::is_convertible<_U,\
    \ _Tp>::value, extended &>\n  operator/=(const _U &__x) noexcept {\n    auto __s\
    \ = sign_of(__x);\n    if (__s)\n      (value /= __x) ? sign *= __s : sign = 0;\n\
    \    else\n      infinite = true, value = 0;\n    return *this;\n  }\n\n  constexpr\
    \ extended &operator%=(const extended &__x) noexcept {\n    if (!__x.infinite)\
    \ sign = sign_of(value %= __x);\n    return *this;\n  }\n\n  template <class _U>\n\
    \  constexpr std::enable_if_t<std::is_convertible<_U, _Tp>::value, extended &>\n\
    \  operator%=(const _U &__x) noexcept {\n    sign = sign_of(value %= __x);\n \
    \   return *this;\n  }\n\n  constexpr extended operator+(const extended &__x)\
    \ const noexcept {\n    return extended(*this) += __x;\n  }\n\n  constexpr extended\
    \ operator-(const extended &__x) const noexcept {\n    return extended(*this)\
    \ -= __x;\n  }\n\n  constexpr extended operator*(const extended &__x) const noexcept\
    \ {\n    return extended(*this) *= __x;\n  }\n\n  constexpr extended operator/(const\
    \ extended &__x) const noexcept {\n    return extended(*this) /= __x;\n  }\n\n\
    \  constexpr extended operator%(const extended &__x) const noexcept {\n    return\
    \ extended(*this) %= __x;\n  }\n\n  template <class _U>\n  constexpr std::enable_if_t<std::is_convertible<_U,\
    \ _Tp>::value, extended>\n  operator+(const _U &__x) const noexcept {\n    return\
    \ extended(*this) += __x;\n  }\n\n  template <class _U>\n  constexpr std::enable_if_t<std::is_convertible<_U,\
    \ _Tp>::value, extended>\n  operator-(const _U &__x) const noexcept {\n    return\
    \ extended(*this) -= __x;\n  }\n\n  template <class _U>\n  constexpr std::enable_if_t<std::is_convertible<_U,\
    \ _Tp>::value, extended>\n  operator*(const _U &__x) const noexcept {\n    return\
    \ extended(*this) *= __x;\n  }\n\n  template <class _U>\n  constexpr std::enable_if_t<std::is_convertible<_U,\
    \ _Tp>::value, extended>\n  operator/(const _U &__x) const noexcept {\n    return\
    \ extended(*this) /= __x;\n  }\n\n  template <class _U>\n  constexpr std::enable_if_t<std::is_convertible<_U,\
    \ _Tp>::value, extended>\n  operator%(const _U &__x) const noexcept {\n    return\
    \ extended(*this) %= __x;\n  }\n\n  template <class _U>\n  constexpr friend std::enable_if_t<std::is_convertible<_U,\
    \ _Tp>::value,\n                                    extended>\n  operator+(const\
    \ _U &__x, const extended &__y) noexcept {\n    return extended(__x) += __y;\n\
    \  }\n\n  template <class _U>\n  constexpr friend std::enable_if_t<std::is_convertible<_U,\
    \ _Tp>::value,\n                                    extended>\n  operator-(const\
    \ _U &__x, const extended &__y) noexcept {\n    return extended(__x) -= __y;\n\
    \  }\n\n  template <class _U>\n  constexpr friend std::enable_if_t<std::is_convertible<_U,\
    \ _Tp>::value,\n                                    extended>\n  operator*(const\
    \ _U &__x, const extended &__y) noexcept {\n    return extended(__x) *= __y;\n\
    \  }\n\n  template <class _U>\n  constexpr friend std::enable_if_t<std::is_convertible<_U,\
    \ _Tp>::value,\n                                    extended>\n  operator/(const\
    \ _U &__x, const extended &__y) noexcept {\n    return extended(__x) /= __y;\n\
    \  }\n\n  template <class _U>\n  constexpr friend std::enable_if_t<std::is_convertible<_U,\
    \ _Tp>::value,\n                                    extended>\n  operator%(const\
    \ _U &__x, const extended &__y) noexcept {\n    return extended(__x) %= __y;\n\
    \  }\n\n  constexpr bool operator==(const extended &__x) const noexcept {\n  \
    \  return infinite == __x.infinite && sign == __x.sign && value == __x.value;\n\
    \  }\n\n  template <class _U>\n  constexpr std::enable_if_t<std::is_convertible<_U,\
    \ _Tp>::value, bool>\n  operator==(const _U &__x) const noexcept {\n    return\
    \ !infinite && value == static_cast<_Tp>(__x);\n  }\n\n  template <class _U>\n\
    \  constexpr friend std::enable_if_t<std::is_convertible<_U, _Tp>::value, bool>\n\
    \  operator==(const _U &__x, const extended &__y) noexcept {\n    return __y.operator==(__x);\n\
    \  }\n\n  constexpr bool operator!=(const extended &__x) const noexcept {\n  \
    \  return !operator==(__x);\n  }\n\n  template <class _U>\n  constexpr std::enable_if_t<std::is_convertible<_U,\
    \ _Tp>::value, bool>\n  operator!=(const _U &__x) const noexcept {\n    return\
    \ !operator==(__x);\n  }\n\n  template <class _U>\n  constexpr friend std::enable_if_t<std::is_convertible<_U,\
    \ _Tp>::value, bool>\n  operator!=(const _U &__x, const extended &__y) noexcept\
    \ {\n    return __y.operator!=(__x);\n  }\n\n  constexpr bool operator<(const\
    \ extended &__x) const noexcept {\n    auto __l = sign * infinite, __r = __x.sign\
    \ * __x.infinite;\n    return __l != __r ? __l < __r : value < __x.value;\n  }\n\
    \n  constexpr bool operator<=(const extended &__x) const noexcept {\n    auto\
    \ __l = sign * infinite, __r = __x.sign * __x.infinite;\n    return __l != __r\
    \ ? __l < __r : value <= __x.value;\n  }\n\n  template <class _U>\n  constexpr\
    \ std::enable_if_t<std::is_convertible<_U, _Tp>::value, bool>\n  operator<(const\
    \ _U &__x) const noexcept {\n    return infinite ? sign < 0 : value < static_cast<_Tp>(__x);\n\
    \  }\n\n  template <class _U>\n  constexpr std::enable_if_t<std::is_convertible<_U,\
    \ _Tp>::value, bool>\n  operator<=(const _U &__x) const noexcept {\n    return\
    \ infinite ? sign < 0 : value <= static_cast<_Tp>(__x);\n  }\n\n  constexpr bool\
    \ operator>(const extended &__x) const noexcept {\n    return __x.operator<(*this);\n\
    \  }\n\n  constexpr bool operator>=(const extended &__x) const noexcept {\n  \
    \  return __x.operator<=(*this);\n  }\n\n  template <class _U>\n  constexpr std::enable_if_t<std::is_convertible<_U,\
    \ _Tp>::value, bool>\n  operator>(const _U &__x) const noexcept {\n    return\
    \ infinite ? sign > 0 : value > static_cast<_Tp>(__x);\n  }\n\n  template <class\
    \ _U>\n  constexpr std::enable_if_t<std::is_convertible<_U, _Tp>::value, bool>\n\
    \  operator>=(const _U &__x) const noexcept {\n    return infinite ? sign > 0\
    \ : value >= static_cast<_Tp>(__x);\n  }\n\n  template <class _U>\n  constexpr\
    \ friend std::enable_if_t<std::is_convertible<_U, _Tp>::value, bool>\n  operator<(const\
    \ _U &__x, const extended &__y) noexcept {\n    return __y.operator>(__x);\n \
    \ }\n\n  template <class _U>\n  constexpr friend std::enable_if_t<std::is_convertible<_U,\
    \ _Tp>::value, bool>\n  operator>(const _U &__x, const extended &__y) noexcept\
    \ {\n    return __y.operator<(__x);\n  }\n\n  template <class _U>\n  constexpr\
    \ friend std::enable_if_t<std::is_convertible<_U, _Tp>::value, bool>\n  operator<=(const\
    \ _U &__x, const extended &__y) noexcept {\n    return __y.operator>=(__x);\n\
    \  }\n\n  template <class _U>\n  constexpr friend std::enable_if_t<std::is_convertible<_U,\
    \ _Tp>::value, bool>\n  operator>=(const _U &__x, const extended &__y) noexcept\
    \ {\n    return __y.operator<=(__x);\n  }\n};\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file extended.hpp\n * @brief Extended Numeric Type\n\
    \ */\n\n#include <cstdint>\n#include <type_traits>\n\n#include \"lib/cxx17\"\n\
    \nnamespace workspace {\n\ntemplate <class _Tp> constexpr auto sign_of(const _Tp\
    \ &__x) noexcept {\n  return __x != _Tp(0) ? (__x > _Tp(0) ? +1 : -1) : 0;\n}\n\
    \n// Extended numeric type.\ntemplate <class _Tp> class extended {\n  bool infinite{};\n\
    \  int_least8_t sign{};  // in {0, +1, -1}\n  _Tp value{};          // is 0 if\
    \ infinite\n\n  template <class _Os>\n  friend _Os &operator<<(_Os &__os, const\
    \ extended &__x) noexcept {\n    return __x.infinite ? __os << (__x.sign > 0 ?\
    \ '+' : '-') << \"infinity\"\n                        : __os << __x.value;\n \
    \ }\n\n  friend std::istream &operator>>(std::istream &__is, extended &__x) noexcept\
    \ {\n    __x.infinite = false;\n    __is >> __x.value;\n    __x.sign = sign_of(__x.value);\n\
    \    return __is;\n  }\n\n  constexpr extended(bool __x, int_least8_t __y, const\
    \ _Tp &__z) noexcept\n      : infinite(__x), sign(__y), value(__z) {}\n\n public:\n\
    \  constexpr static extended infinity{true, +1, 0};\n\n  constexpr extended()\
    \ noexcept {}\n\n  constexpr extended(const _Tp &__x) noexcept\n      : sign(sign_of(__x)),\
    \ value(__x) {}\n\n  constexpr std::enable_if_t<std::is_swappable<_Tp>::value>\
    \ swap(\n      extended &__x) noexcept {\n    std::swap(infinite, __x.infinite);\n\
    \    std::swap(sign, __x.sign);\n    std::swap(value, __x.value);\n  }\n\n  template\
    \ <class _U> constexpr operator _U const &() const noexcept {\n    if _CXX17_CONSTEXPR\
    \ (std::is_same_v<_U, bool>) return sign;\n    return value;\n  }\n\n  template\
    \ <class _U> constexpr operator _U() const noexcept {\n    if _CXX17_CONSTEXPR\
    \ (std::is_same_v<_U, bool>) return sign;\n    return value;\n  }\n\n  constexpr\
    \ extended operator+() const noexcept { return *this; }\n\n  constexpr extended\
    \ operator-() const noexcept {\n    return extended(infinite, -sign, -value);\n\
    \  }\n\n  constexpr extended &operator+=(const extended &__x) noexcept {\n   \
    \ if (__x.infinite) return *this = __x;\n    return operator+=(__x.value);\n \
    \ }\n\n  template <class _U>\n  constexpr std::enable_if_t<std::is_convertible<_U,\
    \ _Tp>::value, extended &>\n  operator+=(const _U &__x) noexcept {\n    if (!infinite)\
    \ sign = sign_of(value += __x);\n    return *this;\n  }\n\n  constexpr extended\
    \ &operator-=(const extended &__x) noexcept {\n    return operator+=(-__x);\n\
    \  }\n\n  template <class _U>\n  constexpr std::enable_if_t<std::is_convertible<_U,\
    \ _Tp>::value, extended &>\n  operator-=(const _U &__x) noexcept {\n    return\
    \ operator+=(-__x);\n  }\n\n  constexpr extended &operator*=(const extended &__x)\
    \ noexcept {\n    if (sign *= __x.sign)\n      infinite = infinite || __x.infinite,\
    \ value *= __x.value;\n    else\n      infinite = false, value = 0;\n    return\
    \ *this;\n  }\n\n  template <class _U>\n  constexpr std::enable_if_t<std::is_convertible<_U,\
    \ _Tp>::value, extended &>\n  operator*=(const _U &__x) noexcept {\n    if (sign\
    \ *= sign_of(__x))\n      value *= __x;\n    else\n      infinite = false, value\
    \ = 0;\n    return *this;\n  }\n\n  constexpr extended &operator/=(const extended\
    \ &__x) noexcept {\n    if (__x.infinite)\n      infinite = false, sign = 0, value\
    \ = 0;\n    else if (__x.sign)\n      (value /= __x.value) ? sign *= __x.sign\
    \ : sign = 0;\n    else\n      infinite = true, value = 0;\n    return *this;\n\
    \  }\n\n  template <class _U>\n  constexpr std::enable_if_t<std::is_convertible<_U,\
    \ _Tp>::value, extended &>\n  operator/=(const _U &__x) noexcept {\n    auto __s\
    \ = sign_of(__x);\n    if (__s)\n      (value /= __x) ? sign *= __s : sign = 0;\n\
    \    else\n      infinite = true, value = 0;\n    return *this;\n  }\n\n  constexpr\
    \ extended &operator%=(const extended &__x) noexcept {\n    if (!__x.infinite)\
    \ sign = sign_of(value %= __x);\n    return *this;\n  }\n\n  template <class _U>\n\
    \  constexpr std::enable_if_t<std::is_convertible<_U, _Tp>::value, extended &>\n\
    \  operator%=(const _U &__x) noexcept {\n    sign = sign_of(value %= __x);\n \
    \   return *this;\n  }\n\n  constexpr extended operator+(const extended &__x)\
    \ const noexcept {\n    return extended(*this) += __x;\n  }\n\n  constexpr extended\
    \ operator-(const extended &__x) const noexcept {\n    return extended(*this)\
    \ -= __x;\n  }\n\n  constexpr extended operator*(const extended &__x) const noexcept\
    \ {\n    return extended(*this) *= __x;\n  }\n\n  constexpr extended operator/(const\
    \ extended &__x) const noexcept {\n    return extended(*this) /= __x;\n  }\n\n\
    \  constexpr extended operator%(const extended &__x) const noexcept {\n    return\
    \ extended(*this) %= __x;\n  }\n\n  template <class _U>\n  constexpr std::enable_if_t<std::is_convertible<_U,\
    \ _Tp>::value, extended>\n  operator+(const _U &__x) const noexcept {\n    return\
    \ extended(*this) += __x;\n  }\n\n  template <class _U>\n  constexpr std::enable_if_t<std::is_convertible<_U,\
    \ _Tp>::value, extended>\n  operator-(const _U &__x) const noexcept {\n    return\
    \ extended(*this) -= __x;\n  }\n\n  template <class _U>\n  constexpr std::enable_if_t<std::is_convertible<_U,\
    \ _Tp>::value, extended>\n  operator*(const _U &__x) const noexcept {\n    return\
    \ extended(*this) *= __x;\n  }\n\n  template <class _U>\n  constexpr std::enable_if_t<std::is_convertible<_U,\
    \ _Tp>::value, extended>\n  operator/(const _U &__x) const noexcept {\n    return\
    \ extended(*this) /= __x;\n  }\n\n  template <class _U>\n  constexpr std::enable_if_t<std::is_convertible<_U,\
    \ _Tp>::value, extended>\n  operator%(const _U &__x) const noexcept {\n    return\
    \ extended(*this) %= __x;\n  }\n\n  template <class _U>\n  constexpr friend std::enable_if_t<std::is_convertible<_U,\
    \ _Tp>::value,\n                                    extended>\n  operator+(const\
    \ _U &__x, const extended &__y) noexcept {\n    return extended(__x) += __y;\n\
    \  }\n\n  template <class _U>\n  constexpr friend std::enable_if_t<std::is_convertible<_U,\
    \ _Tp>::value,\n                                    extended>\n  operator-(const\
    \ _U &__x, const extended &__y) noexcept {\n    return extended(__x) -= __y;\n\
    \  }\n\n  template <class _U>\n  constexpr friend std::enable_if_t<std::is_convertible<_U,\
    \ _Tp>::value,\n                                    extended>\n  operator*(const\
    \ _U &__x, const extended &__y) noexcept {\n    return extended(__x) *= __y;\n\
    \  }\n\n  template <class _U>\n  constexpr friend std::enable_if_t<std::is_convertible<_U,\
    \ _Tp>::value,\n                                    extended>\n  operator/(const\
    \ _U &__x, const extended &__y) noexcept {\n    return extended(__x) /= __y;\n\
    \  }\n\n  template <class _U>\n  constexpr friend std::enable_if_t<std::is_convertible<_U,\
    \ _Tp>::value,\n                                    extended>\n  operator%(const\
    \ _U &__x, const extended &__y) noexcept {\n    return extended(__x) %= __y;\n\
    \  }\n\n  constexpr bool operator==(const extended &__x) const noexcept {\n  \
    \  return infinite == __x.infinite && sign == __x.sign && value == __x.value;\n\
    \  }\n\n  template <class _U>\n  constexpr std::enable_if_t<std::is_convertible<_U,\
    \ _Tp>::value, bool>\n  operator==(const _U &__x) const noexcept {\n    return\
    \ !infinite && value == static_cast<_Tp>(__x);\n  }\n\n  template <class _U>\n\
    \  constexpr friend std::enable_if_t<std::is_convertible<_U, _Tp>::value, bool>\n\
    \  operator==(const _U &__x, const extended &__y) noexcept {\n    return __y.operator==(__x);\n\
    \  }\n\n  constexpr bool operator!=(const extended &__x) const noexcept {\n  \
    \  return !operator==(__x);\n  }\n\n  template <class _U>\n  constexpr std::enable_if_t<std::is_convertible<_U,\
    \ _Tp>::value, bool>\n  operator!=(const _U &__x) const noexcept {\n    return\
    \ !operator==(__x);\n  }\n\n  template <class _U>\n  constexpr friend std::enable_if_t<std::is_convertible<_U,\
    \ _Tp>::value, bool>\n  operator!=(const _U &__x, const extended &__y) noexcept\
    \ {\n    return __y.operator!=(__x);\n  }\n\n  constexpr bool operator<(const\
    \ extended &__x) const noexcept {\n    auto __l = sign * infinite, __r = __x.sign\
    \ * __x.infinite;\n    return __l != __r ? __l < __r : value < __x.value;\n  }\n\
    \n  constexpr bool operator<=(const extended &__x) const noexcept {\n    auto\
    \ __l = sign * infinite, __r = __x.sign * __x.infinite;\n    return __l != __r\
    \ ? __l < __r : value <= __x.value;\n  }\n\n  template <class _U>\n  constexpr\
    \ std::enable_if_t<std::is_convertible<_U, _Tp>::value, bool>\n  operator<(const\
    \ _U &__x) const noexcept {\n    return infinite ? sign < 0 : value < static_cast<_Tp>(__x);\n\
    \  }\n\n  template <class _U>\n  constexpr std::enable_if_t<std::is_convertible<_U,\
    \ _Tp>::value, bool>\n  operator<=(const _U &__x) const noexcept {\n    return\
    \ infinite ? sign < 0 : value <= static_cast<_Tp>(__x);\n  }\n\n  constexpr bool\
    \ operator>(const extended &__x) const noexcept {\n    return __x.operator<(*this);\n\
    \  }\n\n  constexpr bool operator>=(const extended &__x) const noexcept {\n  \
    \  return __x.operator<=(*this);\n  }\n\n  template <class _U>\n  constexpr std::enable_if_t<std::is_convertible<_U,\
    \ _Tp>::value, bool>\n  operator>(const _U &__x) const noexcept {\n    return\
    \ infinite ? sign > 0 : value > static_cast<_Tp>(__x);\n  }\n\n  template <class\
    \ _U>\n  constexpr std::enable_if_t<std::is_convertible<_U, _Tp>::value, bool>\n\
    \  operator>=(const _U &__x) const noexcept {\n    return infinite ? sign > 0\
    \ : value >= static_cast<_Tp>(__x);\n  }\n\n  template <class _U>\n  constexpr\
    \ friend std::enable_if_t<std::is_convertible<_U, _Tp>::value, bool>\n  operator<(const\
    \ _U &__x, const extended &__y) noexcept {\n    return __y.operator>(__x);\n \
    \ }\n\n  template <class _U>\n  constexpr friend std::enable_if_t<std::is_convertible<_U,\
    \ _Tp>::value, bool>\n  operator>(const _U &__x, const extended &__y) noexcept\
    \ {\n    return __y.operator<(__x);\n  }\n\n  template <class _U>\n  constexpr\
    \ friend std::enable_if_t<std::is_convertible<_U, _Tp>::value, bool>\n  operator<=(const\
    \ _U &__x, const extended &__y) noexcept {\n    return __y.operator>=(__x);\n\
    \  }\n\n  template <class _U>\n  constexpr friend std::enable_if_t<std::is_convertible<_U,\
    \ _Tp>::value, bool>\n  operator>=(const _U &__x, const extended &__y) noexcept\
    \ {\n    return __y.operator<=(__x);\n  }\n};\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/algebra/extended.hpp
  requiredBy: []
  timestamp: '2021-11-30 17:55:32+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/algebra/extended.hpp
layout: document
redirect_from:
- /library/src/algebra/extended.hpp
- /library/src/algebra/extended.hpp.html
title: Extended Numeric Type
---
