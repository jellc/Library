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
    \nnamespace workspace {\n\ntemplate <class _Tp> constexpr auto sign_of(const _Tp\
    \ &__x) noexcept {\n  return __x != _Tp(0) ? (__x > _Tp(0) ? +1 : -1) : 0;\n}\n\
    \n// Extended numeric type.\ntemplate <class _Tp> class extended {\n  bool infinite{};\n\
    \  int_least8_t sign{};  // in {0, +1, -1}\n  _Tp value{};          // is 0 if\
    \ infinite\n\n  template <class _Os>\n  friend _Os &operator<<(_Os &__os, const\
    \ extended &__x) noexcept {\n    return __x.infinite ? __os << (__x.sign > 0 ?\
    \ '+' : '-') << \"infinity\"\n                        : __os << __x.value;\n \
    \ }\n\n  template <class _Is>\n  friend _Is &operator>>(_Is &__is, extended &__x)\
    \ noexcept {\n    __x.infinite = false;\n    __is >> __x.value;\n    __x.sign\
    \ = sign_of(__x.value);\n    return __is;\n  }\n\n  constexpr extended(bool __x,\
    \ int_least8_t __y, const _Tp &__z) noexcept\n      : infinite(__x), sign(__y),\
    \ value(__z) {}\n\n public:\n  constexpr static extended infinity{true, +1, 0};\n\
    \n  constexpr extended() noexcept {}\n\n  constexpr extended(const _Tp &__x) noexcept\n\
    \      : sign(sign_of(__x)), value(__x) {}\n\n  constexpr std::enable_if_t<std::is_swappable<_Tp>::value>\
    \ swap(\n      extended &__x) noexcept {\n    std::swap(infinite, __x.infinite);\n\
    \    std::swap(sign, __x.sign);\n    std::swap(value, __x.value);\n  }\n\n  //\
    \ constexpr operator _Tp &() noexcept { return value; }\n\n  constexpr operator\
    \ _Tp const &() const noexcept { return value; }\n\n  constexpr operator bool()\
    \ const noexcept { return sign; }\n\n  constexpr extended operator+() const noexcept\
    \ { return *this; }\n\n  constexpr extended operator-() const noexcept {\n   \
    \ return extended(infinite, -sign, -value);\n  }\n\n  constexpr extended &operator+=(const\
    \ extended &__x) noexcept {\n    if (__x.infinite) return *this = __x;\n    return\
    \ operator+=(__x.value);\n  }\n\n  constexpr extended &operator+=(const _Tp &__x)\
    \ noexcept {\n    if (!infinite) sign = sign_of(value += __x);\n    return *this;\n\
    \  }\n\n  constexpr extended &operator-=(const extended &__x) noexcept {\n   \
    \ return operator+=(-__x);\n  }\n\n  constexpr extended &operator-=(const _Tp\
    \ &__x) noexcept {\n    return operator+=(-__x);\n  }\n\n  constexpr extended\
    \ &operator*=(const extended &__x) noexcept {\n    if (sign *= __x.sign)\n   \
    \   infinite = infinite || __x.infinite, value *= __x.value;\n    else\n     \
    \ infinite = false, value = 0;\n    return *this;\n  }\n\n  constexpr extended\
    \ &operator*=(const _Tp &__x) noexcept {\n    if (sign *= sign_of(__x))\n    \
    \  value *= __x;\n    else\n      infinite = false, value = 0;\n    return *this;\n\
    \  }\n\n  constexpr extended &operator/=(const extended &__x) noexcept {\n   \
    \ if (__x.infinite)\n      infinite = false, sign = 0, value = 0;\n    else if\
    \ (__x.sign)\n      sign *= __x.sign, value /= __x.value;\n    else\n      infinite\
    \ = true, value = 0;\n    return *this;\n  }\n\n  constexpr extended &operator/=(const\
    \ _Tp &__x) noexcept {\n    auto __s = sign_of(__x);\n    if (__s)\n      sign\
    \ *= __s, value /= __x;\n    else\n      infinite = true, value = 0;\n    return\
    \ *this;\n  }\n\n  constexpr extended operator+(const extended &__x) const noexcept\
    \ {\n    return extended(*this) += __x;\n  }\n\n  constexpr extended operator-(const\
    \ extended &__x) const noexcept {\n    return extended(*this) -= __x;\n  }\n\n\
    \  constexpr extended operator*(const extended &__x) const noexcept {\n    return\
    \ extended(*this) *= __x;\n  }\n\n  constexpr extended operator/(const extended\
    \ &__x) const noexcept {\n    return extended(*this) /= __x;\n  }\n\n  constexpr\
    \ extended operator+(const _Tp &__x) const noexcept {\n    return extended(*this)\
    \ += __x;\n  }\n\n  constexpr extended operator-(const _Tp &__x) const noexcept\
    \ {\n    return extended(*this) -= __x;\n  }\n\n  constexpr extended operator*(const\
    \ _Tp &__x) const noexcept {\n    return extended(*this) *= __x;\n  }\n\n  constexpr\
    \ extended operator/(const _Tp &__x) const noexcept {\n    return extended(*this)\
    \ /= __x;\n  }\n\n  constexpr friend extended operator+(const _Tp &__x,\n    \
    \                                  const extended &__y) noexcept {\n    return\
    \ extended(__x) += __y;\n  }\n\n  constexpr friend extended operator-(const _Tp\
    \ &__x,\n                                      const extended &__y) noexcept {\n\
    \    return extended(__x) -= __y;\n  }\n\n  constexpr friend extended operator*(const\
    \ _Tp &__x,\n                                      const extended &__y) noexcept\
    \ {\n    return extended(__x) *= __y;\n  }\n\n  constexpr friend extended operator/(const\
    \ _Tp &__x,\n                                      const extended &__y) noexcept\
    \ {\n    return extended(__x) /= __y;\n  }\n\n  constexpr bool operator==(const\
    \ extended &__x) const noexcept {\n    return infinite == __x.infinite && sign\
    \ == __x.sign && value == __x.value;\n  }\n\n  constexpr bool operator==(const\
    \ _Tp &__x) const noexcept {\n    return !infinite && value == __x;\n  }\n\n \
    \ constexpr friend bool operator==(const _Tp &__x,\n                         \
    \          const extended &__y) noexcept {\n    return __y.operator==(__x);\n\
    \  }\n\n  constexpr bool operator!=(const extended &__x) const noexcept {\n  \
    \  return !operator==(__x);\n  }\n\n  constexpr bool operator!=(const _Tp &__x)\
    \ const noexcept {\n    return !operator==(__x);\n  }\n\n  constexpr friend bool\
    \ operator!=(const _Tp &__x,\n                                   const extended\
    \ &__y) noexcept {\n    return __y.operator!=(__x);\n  }\n\n  constexpr bool operator<(const\
    \ extended &__x) const noexcept {\n    auto __l = sign * infinite, __r = __x.sign\
    \ * __x.infinite;\n    return __l != __r ? __l < __r : value < __x.value;\n  }\n\
    \n  constexpr bool operator<=(const extended &__x) const noexcept {\n    auto\
    \ __l = sign * infinite, __r = __x.sign * __x.infinite;\n    return __l != __r\
    \ ? __l < __r : value <= __x.value;\n  }\n\n  constexpr bool operator<(const _Tp\
    \ &__x) const noexcept {\n    return infinite ? sign < 0 : value < __x;\n  }\n\
    \n  constexpr bool operator<=(const _Tp &__x) const noexcept {\n    return infinite\
    \ ? sign < 0 : value <= __x;\n  }\n\n  constexpr bool operator>(const extended\
    \ &__x) const noexcept {\n    return __x.operator<(*this);\n  }\n\n  constexpr\
    \ bool operator>=(const extended &__x) const noexcept {\n    return __x.operator<=(*this);\n\
    \  }\n\n  constexpr bool operator>(const _Tp &__x) const noexcept {\n    return\
    \ infinite ? sign > 0 : value > __x;\n  }\n\n  constexpr bool operator>=(const\
    \ _Tp &__x) const noexcept {\n    return infinite ? sign > 0 : value >= __x;\n\
    \  }\n\n  constexpr friend bool operator<(const _Tp &__x,\n                  \
    \                const extended &__y) noexcept {\n    return __y.operator>(__x);\n\
    \  }\n\n  constexpr friend bool operator>(const _Tp &__x,\n                  \
    \                const extended &__y) noexcept {\n    return __y.operator<(__x);\n\
    \  }\n\n  constexpr friend bool operator<=(const _Tp &__x,\n                 \
    \                  const extended &__y) noexcept {\n    return __y.operator>=(__x);\n\
    \  }\n\n  constexpr friend bool operator>=(const _Tp &__x,\n                 \
    \                  const extended &__y) noexcept {\n    return __y.operator<=(__x);\n\
    \  }\n};\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file extended.hpp\n * @brief Extended Numeric Type\n\
    \ */\n\n#include <cstdint>\n#include <type_traits>\n\nnamespace workspace {\n\n\
    template <class _Tp> constexpr auto sign_of(const _Tp &__x) noexcept {\n  return\
    \ __x != _Tp(0) ? (__x > _Tp(0) ? +1 : -1) : 0;\n}\n\n// Extended numeric type.\n\
    template <class _Tp> class extended {\n  bool infinite{};\n  int_least8_t sign{};\
    \  // in {0, +1, -1}\n  _Tp value{};          // is 0 if infinite\n\n  template\
    \ <class _Os>\n  friend _Os &operator<<(_Os &__os, const extended &__x) noexcept\
    \ {\n    return __x.infinite ? __os << (__x.sign > 0 ? '+' : '-') << \"infinity\"\
    \n                        : __os << __x.value;\n  }\n\n  template <class _Is>\n\
    \  friend _Is &operator>>(_Is &__is, extended &__x) noexcept {\n    __x.infinite\
    \ = false;\n    __is >> __x.value;\n    __x.sign = sign_of(__x.value);\n    return\
    \ __is;\n  }\n\n  constexpr extended(bool __x, int_least8_t __y, const _Tp &__z)\
    \ noexcept\n      : infinite(__x), sign(__y), value(__z) {}\n\n public:\n  constexpr\
    \ static extended infinity{true, +1, 0};\n\n  constexpr extended() noexcept {}\n\
    \n  constexpr extended(const _Tp &__x) noexcept\n      : sign(sign_of(__x)), value(__x)\
    \ {}\n\n  constexpr std::enable_if_t<std::is_swappable<_Tp>::value> swap(\n  \
    \    extended &__x) noexcept {\n    std::swap(infinite, __x.infinite);\n    std::swap(sign,\
    \ __x.sign);\n    std::swap(value, __x.value);\n  }\n\n  // constexpr operator\
    \ _Tp &() noexcept { return value; }\n\n  constexpr operator _Tp const &() const\
    \ noexcept { return value; }\n\n  constexpr operator bool() const noexcept { return\
    \ sign; }\n\n  constexpr extended operator+() const noexcept { return *this; }\n\
    \n  constexpr extended operator-() const noexcept {\n    return extended(infinite,\
    \ -sign, -value);\n  }\n\n  constexpr extended &operator+=(const extended &__x)\
    \ noexcept {\n    if (__x.infinite) return *this = __x;\n    return operator+=(__x.value);\n\
    \  }\n\n  constexpr extended &operator+=(const _Tp &__x) noexcept {\n    if (!infinite)\
    \ sign = sign_of(value += __x);\n    return *this;\n  }\n\n  constexpr extended\
    \ &operator-=(const extended &__x) noexcept {\n    return operator+=(-__x);\n\
    \  }\n\n  constexpr extended &operator-=(const _Tp &__x) noexcept {\n    return\
    \ operator+=(-__x);\n  }\n\n  constexpr extended &operator*=(const extended &__x)\
    \ noexcept {\n    if (sign *= __x.sign)\n      infinite = infinite || __x.infinite,\
    \ value *= __x.value;\n    else\n      infinite = false, value = 0;\n    return\
    \ *this;\n  }\n\n  constexpr extended &operator*=(const _Tp &__x) noexcept {\n\
    \    if (sign *= sign_of(__x))\n      value *= __x;\n    else\n      infinite\
    \ = false, value = 0;\n    return *this;\n  }\n\n  constexpr extended &operator/=(const\
    \ extended &__x) noexcept {\n    if (__x.infinite)\n      infinite = false, sign\
    \ = 0, value = 0;\n    else if (__x.sign)\n      sign *= __x.sign, value /= __x.value;\n\
    \    else\n      infinite = true, value = 0;\n    return *this;\n  }\n\n  constexpr\
    \ extended &operator/=(const _Tp &__x) noexcept {\n    auto __s = sign_of(__x);\n\
    \    if (__s)\n      sign *= __s, value /= __x;\n    else\n      infinite = true,\
    \ value = 0;\n    return *this;\n  }\n\n  constexpr extended operator+(const extended\
    \ &__x) const noexcept {\n    return extended(*this) += __x;\n  }\n\n  constexpr\
    \ extended operator-(const extended &__x) const noexcept {\n    return extended(*this)\
    \ -= __x;\n  }\n\n  constexpr extended operator*(const extended &__x) const noexcept\
    \ {\n    return extended(*this) *= __x;\n  }\n\n  constexpr extended operator/(const\
    \ extended &__x) const noexcept {\n    return extended(*this) /= __x;\n  }\n\n\
    \  constexpr extended operator+(const _Tp &__x) const noexcept {\n    return extended(*this)\
    \ += __x;\n  }\n\n  constexpr extended operator-(const _Tp &__x) const noexcept\
    \ {\n    return extended(*this) -= __x;\n  }\n\n  constexpr extended operator*(const\
    \ _Tp &__x) const noexcept {\n    return extended(*this) *= __x;\n  }\n\n  constexpr\
    \ extended operator/(const _Tp &__x) const noexcept {\n    return extended(*this)\
    \ /= __x;\n  }\n\n  constexpr friend extended operator+(const _Tp &__x,\n    \
    \                                  const extended &__y) noexcept {\n    return\
    \ extended(__x) += __y;\n  }\n\n  constexpr friend extended operator-(const _Tp\
    \ &__x,\n                                      const extended &__y) noexcept {\n\
    \    return extended(__x) -= __y;\n  }\n\n  constexpr friend extended operator*(const\
    \ _Tp &__x,\n                                      const extended &__y) noexcept\
    \ {\n    return extended(__x) *= __y;\n  }\n\n  constexpr friend extended operator/(const\
    \ _Tp &__x,\n                                      const extended &__y) noexcept\
    \ {\n    return extended(__x) /= __y;\n  }\n\n  constexpr bool operator==(const\
    \ extended &__x) const noexcept {\n    return infinite == __x.infinite && sign\
    \ == __x.sign && value == __x.value;\n  }\n\n  constexpr bool operator==(const\
    \ _Tp &__x) const noexcept {\n    return !infinite && value == __x;\n  }\n\n \
    \ constexpr friend bool operator==(const _Tp &__x,\n                         \
    \          const extended &__y) noexcept {\n    return __y.operator==(__x);\n\
    \  }\n\n  constexpr bool operator!=(const extended &__x) const noexcept {\n  \
    \  return !operator==(__x);\n  }\n\n  constexpr bool operator!=(const _Tp &__x)\
    \ const noexcept {\n    return !operator==(__x);\n  }\n\n  constexpr friend bool\
    \ operator!=(const _Tp &__x,\n                                   const extended\
    \ &__y) noexcept {\n    return __y.operator!=(__x);\n  }\n\n  constexpr bool operator<(const\
    \ extended &__x) const noexcept {\n    auto __l = sign * infinite, __r = __x.sign\
    \ * __x.infinite;\n    return __l != __r ? __l < __r : value < __x.value;\n  }\n\
    \n  constexpr bool operator<=(const extended &__x) const noexcept {\n    auto\
    \ __l = sign * infinite, __r = __x.sign * __x.infinite;\n    return __l != __r\
    \ ? __l < __r : value <= __x.value;\n  }\n\n  constexpr bool operator<(const _Tp\
    \ &__x) const noexcept {\n    return infinite ? sign < 0 : value < __x;\n  }\n\
    \n  constexpr bool operator<=(const _Tp &__x) const noexcept {\n    return infinite\
    \ ? sign < 0 : value <= __x;\n  }\n\n  constexpr bool operator>(const extended\
    \ &__x) const noexcept {\n    return __x.operator<(*this);\n  }\n\n  constexpr\
    \ bool operator>=(const extended &__x) const noexcept {\n    return __x.operator<=(*this);\n\
    \  }\n\n  constexpr bool operator>(const _Tp &__x) const noexcept {\n    return\
    \ infinite ? sign > 0 : value > __x;\n  }\n\n  constexpr bool operator>=(const\
    \ _Tp &__x) const noexcept {\n    return infinite ? sign > 0 : value >= __x;\n\
    \  }\n\n  constexpr friend bool operator<(const _Tp &__x,\n                  \
    \                const extended &__y) noexcept {\n    return __y.operator>(__x);\n\
    \  }\n\n  constexpr friend bool operator>(const _Tp &__x,\n                  \
    \                const extended &__y) noexcept {\n    return __y.operator<(__x);\n\
    \  }\n\n  constexpr friend bool operator<=(const _Tp &__x,\n                 \
    \                  const extended &__y) noexcept {\n    return __y.operator>=(__x);\n\
    \  }\n\n  constexpr friend bool operator>=(const _Tp &__x,\n                 \
    \                  const extended &__y) noexcept {\n    return __y.operator<=(__x);\n\
    \  }\n};\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/algebra/extended.hpp
  requiredBy: []
  timestamp: '2021-10-23 12:28:11+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/algebra/extended.hpp
layout: document
redirect_from:
- /library/src/algebra/extended.hpp
- /library/src/algebra/extended.hpp.html
title: Extended Numeric Type
---