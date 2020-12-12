---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':question:'
    path: src/data_structure/segment_tree/basic.hpp
    title: Segment Tree
  - icon: ':heavy_check_mark:'
    path: src/data_structure/segment_tree/lazy.hpp
    title: Lazy Segment Tree
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/2450.test.cpp
    title: test/aizu-online-judge/2450.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/DSL_2_A.test.cpp
    title: test/aizu-online-judge/DSL_2_A.test.cpp
  - icon: ':x:'
    path: test/library-checker/point_add_range_sum.test.cpp
    title: test/library-checker/point_add_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/point_set_range_composite.test.cpp
    title: test/library-checker/point_set_range_composite.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/range_affine_range_sum.test.cpp
    title: test/library-checker/range_affine_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/static_range_inversions_query.test.cpp
    title: test/library-checker/static_range_inversions_query.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 2 \"src/algebra/system/monoid.hpp\"\n#include <limits>\n\nnamespace\
    \ workspace {\ntemplate <class T, class E = T> struct min_monoid {\n  using value_type\
    \ = T;\n  static T min, max;\n  T value;\n  min_monoid() : value(max) {}\n  min_monoid(const\
    \ T &value) : value(value) {}\n  operator T() const { return value; }\n  min_monoid\
    \ operator+(const min_monoid &rhs) const {\n    return value < rhs.value ? *this\
    \ : rhs;\n  }\n  min_monoid operator*(const E &rhs) const;\n};\n\ntemplate <class\
    \ T, class E>\nT min_monoid<T, E>::min = std::numeric_limits<T>::min() / 2;\n\
    template <class T, class E>\nT min_monoid<T, E>::max = std::numeric_limits<T>::max()\
    \ / 2;\n\ntemplate <class T, class E = T> struct max_monoid : min_monoid<T, E>\
    \ {\n  using base = min_monoid<T, E>;\n  using base::min_monoid;\n  max_monoid()\
    \ : base(base::min) {}\n  max_monoid operator+(const max_monoid &rhs) const {\n\
    \    return !(base::value < rhs.value) ? *this : rhs;\n  }\n  max_monoid operator*(const\
    \ E &rhs) const;\n};\n}\n"
  code: "#pragma once\n#include <limits>\n\nnamespace workspace {\ntemplate <class\
    \ T, class E = T> struct min_monoid {\n  using value_type = T;\n  static T min,\
    \ max;\n  T value;\n  min_monoid() : value(max) {}\n  min_monoid(const T &value)\
    \ : value(value) {}\n  operator T() const { return value; }\n  min_monoid operator+(const\
    \ min_monoid &rhs) const {\n    return value < rhs.value ? *this : rhs;\n  }\n\
    \  min_monoid operator*(const E &rhs) const;\n};\n\ntemplate <class T, class E>\n\
    T min_monoid<T, E>::min = std::numeric_limits<T>::min() / 2;\ntemplate <class\
    \ T, class E>\nT min_monoid<T, E>::max = std::numeric_limits<T>::max() / 2;\n\n\
    template <class T, class E = T> struct max_monoid : min_monoid<T, E> {\n  using\
    \ base = min_monoid<T, E>;\n  using base::min_monoid;\n  max_monoid() : base(base::min)\
    \ {}\n  max_monoid operator+(const max_monoid &rhs) const {\n    return !(base::value\
    \ < rhs.value) ? *this : rhs;\n  }\n  max_monoid operator*(const E &rhs) const;\n\
    };\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: src/algebra/system/monoid.hpp
  requiredBy:
  - src/data_structure/segment_tree/lazy.hpp
  - src/data_structure/segment_tree/basic.hpp
  timestamp: '2020-11-26 16:42:40+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/library-checker/range_affine_range_sum.test.cpp
  - test/library-checker/point_set_range_composite.test.cpp
  - test/library-checker/point_add_range_sum.test.cpp
  - test/library-checker/static_range_inversions_query.test.cpp
  - test/aizu-online-judge/DSL_2_A.test.cpp
  - test/aizu-online-judge/2450.test.cpp
documentation_of: src/algebra/system/monoid.hpp
layout: document
redirect_from:
- /library/src/algebra/system/monoid.hpp
- /library/src/algebra/system/monoid.hpp.html
title: src/algebra/system/monoid.hpp
---