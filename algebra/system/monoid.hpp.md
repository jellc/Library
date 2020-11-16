---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"algebra/system/monoid.hpp\"\n#include <limits>\n\nnamespace\
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
  path: algebra/system/monoid.hpp
  requiredBy: []
  timestamp: '2020-09-27 13:46:39+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: algebra/system/monoid.hpp
layout: document
redirect_from:
- /library/algebra/system/monoid.hpp
- /library/algebra/system/monoid.hpp.html
title: algebra/system/monoid.hpp
---
