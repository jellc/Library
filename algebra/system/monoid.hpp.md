---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: data_structure/segment_tree/basic.hpp
    title: data_structure/segment_tree/basic.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/library-checker/static_range_inversions_query.test.cpp
    title: test/library-checker/static_range_inversions_query.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/point_set_range_composite.test.cpp
    title: test/library-checker/point_set_range_composite.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 2 \"algebra/system/monoid.hpp\"\n#include <limits>\ntemplate\
    \ <class T>\nstruct min_monoid\n{\n    using value_type = T;\n    static T min,\
    \ max;\n    T value;\n    min_monoid() : value(max) {}\n    min_monoid(const T\
    \ &value) : value(value) {}\n    operator T() const { return value; }\n    min_monoid\
    \ operator+(const min_monoid &rhs) const\n    {\n        return value < rhs.value\
    \ ? *this : rhs;\n    }\n};\ntemplate <class T> T min_monoid<T>::min = std::numeric_limits<T>::min();\n\
    template <class T> T min_monoid<T>::max = std::numeric_limits<T>::max();\ntemplate\
    \ <class T>\nstruct max_monoid : min_monoid<T>\n{\n    using base = min_monoid<T>;\n\
    \    using base::min_monoid;\n    max_monoid() : base(base::min) {}\n    max_monoid\
    \ operator+(const max_monoid &rhs) const\n    {\n        return !(base::value\
    \ < rhs.value) ? *this : rhs;\n    }\n};\n"
  code: "#pragma once\n#include <limits>\ntemplate <class T>\nstruct min_monoid\n\
    {\n    using value_type = T;\n    static T min, max;\n    T value;\n    min_monoid()\
    \ : value(max) {}\n    min_monoid(const T &value) : value(value) {}\n    operator\
    \ T() const { return value; }\n    min_monoid operator+(const min_monoid &rhs)\
    \ const\n    {\n        return value < rhs.value ? *this : rhs;\n    }\n};\ntemplate\
    \ <class T> T min_monoid<T>::min = std::numeric_limits<T>::min();\ntemplate <class\
    \ T> T min_monoid<T>::max = std::numeric_limits<T>::max();\ntemplate <class T>\n\
    struct max_monoid : min_monoid<T>\n{\n    using base = min_monoid<T>;\n    using\
    \ base::min_monoid;\n    max_monoid() : base(base::min) {}\n    max_monoid operator+(const\
    \ max_monoid &rhs) const\n    {\n        return !(base::value < rhs.value) ? *this\
    \ : rhs;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: algebra/system/monoid.hpp
  requiredBy:
  - data_structure/segment_tree/basic.hpp
  timestamp: '2020-09-03 02:05:06+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/static_range_inversions_query.test.cpp
  - test/library-checker/point_set_range_composite.test.cpp
documentation_of: algebra/system/monoid.hpp
layout: document
redirect_from:
- /library/algebra/system/monoid.hpp
- /library/algebra/system/monoid.hpp.html
title: algebra/system/monoid.hpp
---
