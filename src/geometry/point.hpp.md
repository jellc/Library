---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: src/geometry/compare.hpp
    title: Compare Argument
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/library-checker/sort_points_by_argument.test.cpp
    title: test/library-checker/sort_points_by_argument.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Point
    links: []
  bundledCode: "#line 2 \"src/geometry/point.hpp\"\n\n/**\n * @file point.hpp\n *\
    \ @brief Point\n */\n\n#include <tuple>\n\nnamespace workspace {\n\n// Point class\
    \ as position vector.\ntemplate <class _Scalar, std::size_t _Dimension = 2>\n\
    struct point : std::array<_Scalar, _Dimension> {\n  using container_type = std::array<_Scalar,\
    \ _Dimension>;\n\n  using typename container_type::size_type;\n  using typename\
    \ container_type::value_type;\n\n protected:\n  using container_type::_M_elems;\n\
    \n public:\n  // Itself.\n  constexpr point operator+() const noexcept { return\
    \ *this; }\n\n  // Vector negation.\n  constexpr point operator-() const noexcept\
    \ {\n    point __p;\n    for (size_type __i = 0; __i != _Dimension; ++__i) __p[__i]\
    \ = -_M_elems[__i];\n    return __p;\n  }\n\n  // Vector sum.\n  constexpr point\
    \ &operator+=(const point &__p) noexcept {\n    for (size_type __i = 0; __i !=\
    \ _Dimension; ++__i) _M_elems[__i] += __p[__i];\n    return *this;\n  }\n\n  //\
    \ Vector sum.\n  constexpr point operator+(const point &__p) const noexcept {\n\
    \    return point(*this) += __p;\n  }\n\n  // Vector difference.\n  constexpr\
    \ point &operator-=(const point &__p) noexcept {\n    for (size_type __i = 0;\
    \ __i != _Dimension; ++__i) _M_elems[__i] -= __p[__i];\n    return *this;\n  }\n\
    \n  // Vector difference.\n  constexpr point operator-(const point &__p) const\
    \ noexcept {\n    return point(*this) -= __p;\n  }\n\n  // Scalar multiplication.\n\
    \  constexpr point &operator*=(value_type __c) noexcept {\n    for (size_type\
    \ __i = 0; __i != _Dimension; ++__i) _M_elems[__i] *= __c;\n    return *this;\n\
    \  }\n\n  // Scalar multiplication.\n  constexpr point operator*(value_type __c)\
    \ const noexcept {\n    return point(*this) *= __c;\n  }\n\n  // Scalar division.\n\
    \  constexpr point &operator/=(value_type __c) noexcept {\n    for (size_type\
    \ __i = 0; __i != _Dimension; ++__i) _M_elems[__i] /= __c;\n    return *this;\n\
    \  }\n\n  // Scalar division.\n  constexpr point operator/(value_type __c) const\
    \ noexcept {\n    return point(*this) /= __c;\n  }\n\n  // Dot product.\n  constexpr\
    \ value_type dot(const point &__p) const noexcept {\n    value_type __ret = 0;\n\
    \    for (size_type __i = 0; __i != _Dimension; ++__i)\n      __ret += _M_elems[__i]\
    \ * __p[__i];\n    return __ret;\n  }\n\n  // Euclidian norm.\n  constexpr value_type\
    \ norm() const noexcept {\n    value_type __ret = 0;\n    for (size_type __i =\
    \ 0; __i != _Dimension; ++__i)\n      __ret += _M_elems[__i] * _M_elems[__i];\n\
    \    return sqrt(__ret);\n  }\n\n  // Euclidian distance.\n  constexpr value_type\
    \ distance(const point &__p) const noexcept {\n    return operator-(__p).norm();\n\
    \  }\n\n  constexpr auto arg() const noexcept {\n    return atan2(_M_elems[1],\
    \ _M_elems[0]);\n  }\n\n  // Cross product.\n  constexpr auto cross(const point\
    \ &__p) const noexcept {\n    if constexpr (_Dimension == 2)\n      return _M_elems[0]\
    \ * __p[1] - _M_elems[1] * __p[0];\n    else if constexpr (_Dimension == 3)\n\
    \      return point{_M_elems[1] * __p[2] - _M_elems[2] * __p[1],\n           \
    \        _M_elems[2] * __p[0] - _M_elems[0] * __p[2],\n                   _M_elems[0]\
    \ * __p[1] - _M_elems[1] * __p[0]};\n  }\n\n  /**\n   * @brief Counter-clockwise.\n\
    \   * @param __p\n   * @param __q\n   * @return Whether __p is in the counter-clockwise\
    \ direction of __q around\n   this.\n   */\n  constexpr bool ccw(const point &__p,\
    \ const point &__q) const noexcept {\n    return value_type(0) < operator-(__p).cross(operator-(__q));\n\
    \  }\n};\n\n#if __cpp_deduction_guides >= 201606\ntemplate <typename _Tp, typename...\
    \ _Up>\npoint(_Tp, _Up...)\n    -> point<std::enable_if_t<(std::is_same_v<_Tp,\
    \ _Up> && ...), _Tp>,\n             1 + sizeof...(_Up)>;\n#endif\n\n}  // namespace\
    \ workspace\n\nnamespace std {\n\ntemplate <class _Scalar, size_t _Dimension>\n\
    struct tuple_size<workspace::point<_Scalar, _Dimension>>\n    : tuple_size<array<_Scalar,\
    \ _Dimension>> {};\n\ntemplate <size_t _Nm, class _Scalar, size_t _Dimension>\n\
    struct tuple_element<_Nm, workspace::point<_Scalar, _Dimension>>\n    : tuple_element<_Nm,\
    \ array<_Scalar, _Dimension>> {};\n\n}  // namespace std\n"
  code: "#pragma once\n\n/**\n * @file point.hpp\n * @brief Point\n */\n\n#include\
    \ <tuple>\n\nnamespace workspace {\n\n// Point class as position vector.\ntemplate\
    \ <class _Scalar, std::size_t _Dimension = 2>\nstruct point : std::array<_Scalar,\
    \ _Dimension> {\n  using container_type = std::array<_Scalar, _Dimension>;\n\n\
    \  using typename container_type::size_type;\n  using typename container_type::value_type;\n\
    \n protected:\n  using container_type::_M_elems;\n\n public:\n  // Itself.\n \
    \ constexpr point operator+() const noexcept { return *this; }\n\n  // Vector\
    \ negation.\n  constexpr point operator-() const noexcept {\n    point __p;\n\
    \    for (size_type __i = 0; __i != _Dimension; ++__i) __p[__i] = -_M_elems[__i];\n\
    \    return __p;\n  }\n\n  // Vector sum.\n  constexpr point &operator+=(const\
    \ point &__p) noexcept {\n    for (size_type __i = 0; __i != _Dimension; ++__i)\
    \ _M_elems[__i] += __p[__i];\n    return *this;\n  }\n\n  // Vector sum.\n  constexpr\
    \ point operator+(const point &__p) const noexcept {\n    return point(*this)\
    \ += __p;\n  }\n\n  // Vector difference.\n  constexpr point &operator-=(const\
    \ point &__p) noexcept {\n    for (size_type __i = 0; __i != _Dimension; ++__i)\
    \ _M_elems[__i] -= __p[__i];\n    return *this;\n  }\n\n  // Vector difference.\n\
    \  constexpr point operator-(const point &__p) const noexcept {\n    return point(*this)\
    \ -= __p;\n  }\n\n  // Scalar multiplication.\n  constexpr point &operator*=(value_type\
    \ __c) noexcept {\n    for (size_type __i = 0; __i != _Dimension; ++__i) _M_elems[__i]\
    \ *= __c;\n    return *this;\n  }\n\n  // Scalar multiplication.\n  constexpr\
    \ point operator*(value_type __c) const noexcept {\n    return point(*this) *=\
    \ __c;\n  }\n\n  // Scalar division.\n  constexpr point &operator/=(value_type\
    \ __c) noexcept {\n    for (size_type __i = 0; __i != _Dimension; ++__i) _M_elems[__i]\
    \ /= __c;\n    return *this;\n  }\n\n  // Scalar division.\n  constexpr point\
    \ operator/(value_type __c) const noexcept {\n    return point(*this) /= __c;\n\
    \  }\n\n  // Dot product.\n  constexpr value_type dot(const point &__p) const\
    \ noexcept {\n    value_type __ret = 0;\n    for (size_type __i = 0; __i != _Dimension;\
    \ ++__i)\n      __ret += _M_elems[__i] * __p[__i];\n    return __ret;\n  }\n\n\
    \  // Euclidian norm.\n  constexpr value_type norm() const noexcept {\n    value_type\
    \ __ret = 0;\n    for (size_type __i = 0; __i != _Dimension; ++__i)\n      __ret\
    \ += _M_elems[__i] * _M_elems[__i];\n    return sqrt(__ret);\n  }\n\n  // Euclidian\
    \ distance.\n  constexpr value_type distance(const point &__p) const noexcept\
    \ {\n    return operator-(__p).norm();\n  }\n\n  constexpr auto arg() const noexcept\
    \ {\n    return atan2(_M_elems[1], _M_elems[0]);\n  }\n\n  // Cross product.\n\
    \  constexpr auto cross(const point &__p) const noexcept {\n    if constexpr (_Dimension\
    \ == 2)\n      return _M_elems[0] * __p[1] - _M_elems[1] * __p[0];\n    else if\
    \ constexpr (_Dimension == 3)\n      return point{_M_elems[1] * __p[2] - _M_elems[2]\
    \ * __p[1],\n                   _M_elems[2] * __p[0] - _M_elems[0] * __p[2],\n\
    \                   _M_elems[0] * __p[1] - _M_elems[1] * __p[0]};\n  }\n\n  /**\n\
    \   * @brief Counter-clockwise.\n   * @param __p\n   * @param __q\n   * @return\
    \ Whether __p is in the counter-clockwise direction of __q around\n   this.\n\
    \   */\n  constexpr bool ccw(const point &__p, const point &__q) const noexcept\
    \ {\n    return value_type(0) < operator-(__p).cross(operator-(__q));\n  }\n};\n\
    \n#if __cpp_deduction_guides >= 201606\ntemplate <typename _Tp, typename... _Up>\n\
    point(_Tp, _Up...)\n    -> point<std::enable_if_t<(std::is_same_v<_Tp, _Up> &&\
    \ ...), _Tp>,\n             1 + sizeof...(_Up)>;\n#endif\n\n}  // namespace workspace\n\
    \nnamespace std {\n\ntemplate <class _Scalar, size_t _Dimension>\nstruct tuple_size<workspace::point<_Scalar,\
    \ _Dimension>>\n    : tuple_size<array<_Scalar, _Dimension>> {};\n\ntemplate <size_t\
    \ _Nm, class _Scalar, size_t _Dimension>\nstruct tuple_element<_Nm, workspace::point<_Scalar,\
    \ _Dimension>>\n    : tuple_element<_Nm, array<_Scalar, _Dimension>> {};\n\n}\
    \  // namespace std\n"
  dependsOn: []
  isVerificationFile: false
  path: src/geometry/point.hpp
  requiredBy:
  - src/geometry/compare.hpp
  timestamp: '2021-08-17 20:06:23+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/sort_points_by_argument.test.cpp
documentation_of: src/geometry/point.hpp
layout: document
redirect_from:
- /library/src/geometry/point.hpp
- /library/src/geometry/point.hpp.html
title: Point
---
