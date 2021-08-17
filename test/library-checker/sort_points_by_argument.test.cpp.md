---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/geometry/point.hpp
    title: Point
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/sort_points_by_argument
    links:
    - https://judge.yosupo.jp/problem/sort_points_by_argument
  bundledCode: "#line 1 \"test/library-checker/sort_points_by_argument.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/sort_points_by_argument\"\n\n\
    #include <algorithm>\n#include <iostream>\n\n#line 2 \"src/geometry/point.hpp\"\
    \n\n/**\n * @file point.hpp\n * @brief Point\n */\n\n#include <tuple>\n\nnamespace\
    \ workspace {\n\n// Point class as position vector.\ntemplate <class _Scalar,\
    \ std::size_t _Dimension = 2>\nstruct point : std::array<_Scalar, _Dimension>\
    \ {\n  using container_type = std::array<_Scalar, _Dimension>;\n\n  using typename\
    \ container_type::size_type;\n  using typename container_type::value_type;\n\n\
    \ protected:\n  using container_type::_M_elems;\n\n public:\n  // Itself.\n  constexpr\
    \ point operator+() const noexcept { return *this; }\n\n  // Vector negation.\n\
    \  constexpr point operator-() const noexcept {\n    point __p;\n    for (size_type\
    \ __i = 0; __i != _Dimension; ++__i) __p[__i] = -_M_elems[__i];\n    return __p;\n\
    \  }\n\n  // Vector sum.\n  constexpr point &operator+=(const point &__p) noexcept\
    \ {\n    for (size_type __i = 0; __i != _Dimension; ++__i) _M_elems[__i] += __p[__i];\n\
    \    return *this;\n  }\n\n  // Vector sum.\n  constexpr point operator+(const\
    \ point &__p) const noexcept {\n    return point(*this) += __p;\n  }\n\n  // Vector\
    \ difference.\n  constexpr point &operator-=(const point &__p) noexcept {\n  \
    \  for (size_type __i = 0; __i != _Dimension; ++__i) _M_elems[__i] -= __p[__i];\n\
    \    return *this;\n  }\n\n  // Vector difference.\n  constexpr point operator-(const\
    \ point &__p) const noexcept {\n    return point(*this) -= __p;\n  }\n\n  // Scalar\
    \ multiplication.\n  constexpr point &operator*=(value_type __c) noexcept {\n\
    \    for (size_type __i = 0; __i != _Dimension; ++__i) _M_elems[__i] *= __c;\n\
    \    return *this;\n  }\n\n  // Scalar multiplication.\n  constexpr point operator*(value_type\
    \ __c) const noexcept {\n    return point(*this) *= __c;\n  }\n\n  // Scalar division.\n\
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
    \ _Up> && ...), _Tp>,\n             1 + sizeof...(_Up)>;\n#endif\n\n// Compare\
    \ by value of `atan2`.\ntemplate <class _Scalar> struct less_arg {\n  using value_type\
    \ = point<_Scalar, 2>;\n  using first_argument_type = value_type;\n  using second_argument_type\
    \ = value_type;\n  using result_type = bool;\n\n  value_type origin;\n\n  less_arg()\
    \ noexcept : origin() {}\n  less_arg(const value_type &__o) noexcept : origin(__o)\
    \ {}\n\n  constexpr bool operator()(const value_type &__p,\n                 \
    \           const value_type &__q) const noexcept {\n    if (__p[1] == origin[1])\n\
    \      return origin[0] <= __p[0] &&\n             (origin[1] < __q[1] ||\n  \
    \            (__q[1] == origin[1] && __q[0] < origin[0]));\n\n    return origin[1]\
    \ < __p[1] ? origin[1] <= __q[1] && origin.ccw(__p, __q)\n                   \
    \           : origin[1] <= __q[1] || origin.ccw(__p, __q);\n  }\n};\n\n}  // namespace\
    \ workspace\n\nnamespace std {\n\ntemplate <class _Scalar, size_t _Dimension>\n\
    struct tuple_size<workspace::point<_Scalar, _Dimension>>\n    : tuple_size<array<_Scalar,\
    \ _Dimension>> {};\n\ntemplate <size_t _Nm, class _Scalar, size_t _Dimension>\n\
    struct tuple_element<_Nm, workspace::point<_Scalar, _Dimension>>\n    : tuple_element<_Nm,\
    \ array<_Scalar, _Dimension>> {};\n\n}  // namespace std\n#line 7 \"test/library-checker/sort_points_by_argument.test.cpp\"\
    \n\nint main() {\n  using namespace workspace;\n\n  int n;\n  std::cin >> n;\n\
    \  std::vector<point<long long>> pos(n);\n  for (auto &[x, y] : pos) std::cin\
    \ >> x >> y;\n\n  std::sort(pos.begin(), pos.end(), less_arg<long long>());\n\
    \  for (auto &[x, y] : pos) std::cout << x << \" \" << y << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/sort_points_by_argument\"\
    \n\n#include <algorithm>\n#include <iostream>\n\n#include \"src/geometry/point.hpp\"\
    \n\nint main() {\n  using namespace workspace;\n\n  int n;\n  std::cin >> n;\n\
    \  std::vector<point<long long>> pos(n);\n  for (auto &[x, y] : pos) std::cin\
    \ >> x >> y;\n\n  std::sort(pos.begin(), pos.end(), less_arg<long long>());\n\
    \  for (auto &[x, y] : pos) std::cout << x << \" \" << y << \"\\n\";\n}\n"
  dependsOn:
  - src/geometry/point.hpp
  isVerificationFile: true
  path: test/library-checker/sort_points_by_argument.test.cpp
  requiredBy: []
  timestamp: '2021-08-17 17:46:36+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/library-checker/sort_points_by_argument.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/sort_points_by_argument.test.cpp
- /verify/test/library-checker/sort_points_by_argument.test.cpp.html
title: test/library-checker/sort_points_by_argument.test.cpp
---
