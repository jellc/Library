---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':question:'
    path: src/algebra/linear/lu.hpp
    title: LU decomposition
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/ITP1_6_D.test.cpp
    title: test/aizu-online-judge/ITP1_6_D.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/ITP1_7_D.test.cpp
    title: test/aizu-online-judge/ITP1_7_D.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/matrix_det.test.cpp
    title: test/library-checker/matrix_det.test.cpp
  - icon: ':x:'
    path: test/library-checker/system_of_linear_equations.test.cpp
    title: test/library-checker/system_of_linear_equations.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    document_title: Matrix
    links: []
  bundledCode: "#line 2 \"src/algebra/linear/matrix.hpp\"\n\n/**\n * @file matrix.hpp\n\
    \ * @brief Matrix\n * @date 2021-02-15\n *\n *\n */\n\n#include <cassert>\n#include\
    \ <valarray>\n\nnamespace workspace {\n\n/**\n * @brief Fixed size matrix.\n *\n\
    \ * @tparam _Scalar\n * @tparam _Rows Number of rows\n * @tparam _Cols Number\
    \ of columns\n */\ntemplate <class _Scalar, std::size_t _Rows = 0, std::size_t\
    \ _Cols = _Rows>\nclass matrix {\n public:\n  _Scalar __data[_Rows][_Cols] = {};\n\
    \n  using value_type = _Scalar;\n  using size_type = std::size_t;\n\n  constexpr\
    \ static matrix eye() {\n    static_assert(_Rows == _Cols);\n\n    matrix __e;\n\
    \    for (size_type __d = 0; __d != _Rows; ++__d) __e.__data[__d][__d] = 1;\n\
    \    return __e;\n  }\n\n  constexpr operator decltype((__data))() { return __data;\
    \ }\n  constexpr operator decltype(std::declval<const matrix>().__data)\n    \
    \  const&() const {\n    return __data;\n  }\n\n  constexpr auto begin() { return\
    \ __data; }\n  constexpr auto begin() const { return __data; }\n\n  constexpr\
    \ auto end() { return __data + _Rows; }\n  constexpr auto end() const { return\
    \ __data + _Rows; }\n\n  constexpr size_type rows() const { return _Rows; }\n\n\
    \  constexpr size_type cols() const { return _Cols; }\n\n  constexpr auto transpose()\
    \ const {\n    matrix<_Scalar, _Cols, _Rows> __t;\n\n    for (size_type __r =\
    \ 0; __r != _Rows; ++__r)\n      for (size_type __c = 0; __c != _Cols; ++__c)\n\
    \        __t.__data[__c][__r] = __data[__r][__c];\n\n    return __t;\n  }\n\n\
    \  constexpr matrix operator+() const { return *this; }\n\n  constexpr matrix\
    \ operator-() const {\n    matrix __cp = *this;\n\n    for (auto& __v : __cp.__data)\n\
    \      for (auto& __e : __v) __e = -__e;\n\n    return __cp;\n  }\n\n  template\
    \ <class _Matrix> constexpr matrix& operator+=(const _Matrix& __x) {\n    auto\
    \ __m = std::min(_Rows, __x.rows());\n    auto __n = std::min(_Cols, __x.cols());\n\
    \n    for (size_type __r = 0; __r != __m; ++__r)\n      for (size_type __c = 0;\
    \ __c != __n; ++__c)\n        __data[__r][__c] += __x[__r][__c];\n\n    return\
    \ *this;\n  }\n\n  template <class _Matrix>\n  constexpr matrix operator+(const\
    \ _Matrix& __x) const {\n    return matrix(*this) += __x;\n  }\n\n  template <class\
    \ _Matrix> constexpr matrix& operator-=(const _Matrix& __x) {\n    auto __m =\
    \ std::min(_Rows, __x.rows());\n    auto __n = std::min(_Cols, __x.cols());\n\n\
    \    for (size_type __r = 0; __r != __m; ++__r)\n      for (size_type __c = 0;\
    \ __c != __n; ++__c)\n        __data[__r][__c] -= __x[__r][__c];\n\n    return\
    \ *this;\n  }\n\n  template <class _Matrix>\n  constexpr matrix operator-(const\
    \ _Matrix& __x) const {\n    return matrix(*this) -= __x;\n  }\n\n  template <class\
    \ _Scalar2>\n  constexpr matrix& operator*=(const matrix<_Scalar2, _Cols, _Cols>&\
    \ __x) {\n    if (this == &__x) return operator=(operator*(__x));\n\n    for (auto&\
    \ __r : __data) {\n      _Scalar __tmp[_Cols] = {};\n\n      auto __v = *__x.__data;\n\
    \      for (auto& __w : __tmp) {\n        auto __i = __v++;\n        for (const\
    \ auto& __e : __r) __w += __e * *__i, __i += _Cols;\n      }\n\n      auto __w\
    \ = __tmp;\n      for (auto& __e : __r) __e = std::move(*__w++);\n    }\n\n  \
    \  return *this;\n  }\n\n  template <class _Scalar2, size_type _Rows2, size_type\
    \ _Cols2>\n  constexpr auto operator*(const matrix<_Scalar2, _Rows2, _Cols2>&\
    \ __x) const {\n    matrix<typename std::common_type<_Scalar, _Scalar2>::type,\
    \ _Rows, _Cols2>\n        __m;\n\n    auto __w = *__m.__data;\n    for (const\
    \ auto& __r : __data)\n      for (auto __v = *__x.__data, __v_end = __v + _Cols2;\
    \ __v != __v_end;\n           ++__w) {\n        auto __i = __v++;\n        for\
    \ (auto __e = __r; __e != __r + std::min(_Cols, _Rows2); ++__e)\n          *__w\
    \ += *__e * *__i, __i += _Cols2;\n      }\n\n    return __m;\n  }\n\n  template\
    \ <class _Matrix>\n  constexpr\n      typename std::enable_if<!std::is_convertible<_Matrix,\
    \ value_type>::value,\n                              matrix<_Scalar>>::type\n\
    \      operator*(const _Matrix& __x) const {\n    matrix<_Scalar> __m(_Rows, __x.cols());\n\
    \n    for (size_type __r = 0; __r != _Rows; ++__r)\n      for (size_type __i =\
    \ 0; __i != __x.cols(); ++__i)\n        for (size_type __c = 0; __c != std::min(_Cols,\
    \ __x.rows()); ++__c)\n          __m[__r][__i] += __data[__r][__c] * __x[__c][__i];\n\
    \n    return __m;\n  }\n\n  constexpr matrix& operator*=(const value_type& __x)\
    \ {\n    for (auto& __v : __data)\n      for (auto& __e : __v) __e *= __x;\n\n\
    \    return *this;\n  }\n\n  constexpr matrix operator*(const value_type& __x)\
    \ const {\n    return matrix(*this) *= __x;\n  }\n\n  constexpr matrix& operator/=(const\
    \ value_type& __x) {\n    assert(__x != value_type(0));\n\n    for (auto& __v\
    \ : __data)\n      for (auto& __e : __v) __e /= __x;\n\n    return *this;\n  }\n\
    \n  constexpr matrix operator/(const value_type& __x) const {\n    return matrix(*this)\
    \ /= __x;\n  }\n\n  template <class _Int> constexpr matrix pow(_Int __e) const\
    \ {\n    assert(0 <= __e);\n\n    matrix __m = eye();\n    for (matrix __cp =\
    \ *this; __e; __cp *= __cp, __e >>= 1)\n      if (__e & 1) __m *= __cp;\n\n  \
    \  return __m;\n  }\n\n  template <class _Os>\n  constexpr friend _Os& operator<<(_Os&\
    \ __os, const matrix& __x) {\n    for (auto __i = __x.begin(); __i != __x.end();\
    \ ++__i, __os << '\\n')\n      for (size_type __c = 0; __c != _Cols; ++__c)\n\
    \        __c ? void(__os << ' ') : (void)0, __os << *(*__i + __c);\n\n    return\
    \ __os;\n  }\n};  // namespace workspace\n\n/**\n * @brief Dynamic matrix.\n *\n\
    \ * @tparam _Scalar\n * @tparam _Rows Number of rows\n * @tparam _Cols Number\
    \ of columns\n */\ntemplate <class _Scalar>\nclass matrix<_Scalar, 0, 0> : public\
    \ std::valarray<std::valarray<_Scalar>> {\n  using base = std::valarray<std::valarray<_Scalar>>;\n\
    \  using row_type = typename base::value_type;\n\n public:\n  using value_type\
    \ = _Scalar;\n  using size_type = std::size_t;\n\n  using base::operator[];\n\n\
    \  static matrix eye(size_type __n) {\n    matrix __e(__n, __n);\n    for (size_type\
    \ __d = 0; __d != __n; ++__d) __e[__d][__d] = 1;\n    return __e;\n  }\n\n  matrix()\
    \ = default;\n\n  matrix(size_type __n) : matrix(__n, __n) {}\n\n  matrix(size_type\
    \ __m, size_type __n) : base(row_type(__n), __m) {}\n\n  template <class _Tp,\
    \ typename = typename std::enable_if<\n                           std::is_constructible<base,\
    \ _Tp>::value &&\n                           !std::is_constructible<size_type,\
    \ _Tp>::value>::type>\n  matrix(_Tp&& __x) : base(__x) {}\n\n  matrix(std::initializer_list<row_type>\
    \ __x) : base(__x) {}\n\n  size_type rows() const { return base::size(); }\n\n\
    \  size_type cols() const { return rows() ? operator[](0).size() : 0; }\n\n  matrix\
    \ transpose() const {\n    matrix __t(cols(), rows());\n\n    for (size_type __r\
    \ = 0; __r != rows(); ++__r)\n      for (size_type __c = 0; __c != cols(); ++__c)\n\
    \        __t[__c][__r] = operator[](__r)[__c];\n\n    return __t;\n  }\n\n  void\
    \ resize(size_type __m, size_type __n) {\n    matrix __t(__m, __n);\n\n    if\
    \ (rows() < __m) __m = rows();\n    if (cols() < __n) __n = cols();\n\n    for\
    \ (size_type __r = 0; __r != __m; ++__r)\n      for (size_type __c = 0; __c !=\
    \ __n; ++__c)\n        __t[__r][__c] = std::move(operator[](__r)[__c]);\n\n  \
    \  base::swap(__t);\n  }\n\n  // binary operators {{\n\n  template <class _Matrix,\
    \ typename = void>\n  struct is_valarray_based : std::false_type {};\n\n  template\
    \ <class _Matrix>\n  struct is_valarray_based<\n      _Matrix,\n      typename\
    \ std::enable_if<std::is_same<\n          row_type, typename std::decay<decltype(\n\
    \                        std::declval<_Matrix>()[0])>::type>::value>::type>\n\
    \      : std::true_type {};\n\n  template <class _Matrix>\n  typename std::enable_if<!std::is_convertible<_Matrix,\
    \ value_type>::value,\n                          matrix&>::type\n  operator*=(_Matrix&&\
    \ __x) {\n    return *this = operator*(std::forward<_Matrix>(__x));\n  }\n\n \
    \ template <class _Matrix>\n  typename std::enable_if<!std::is_convertible<_Matrix,\
    \ value_type>::value,\n                          matrix>::type\n  operator*(const\
    \ _Matrix& __x) const {\n    matrix __m(rows(), __x.cols());\n\n    if constexpr\
    \ (is_valarray_based<_Matrix>::value)\n      for (size_type __r = 0; __r != rows();\
    \ ++__r)\n        for (size_type __c = 0; __c != std::min(cols(), __x.rows());\
    \ ++__c)\n          __m[__r] += operator[](__r)[__c] * __x[__c];\n\n    else\n\
    \      for (size_type __r = 0; __r != rows(); ++__r)\n        for (size_type __i\
    \ = 0; __i != __x.cols(); ++__i)\n          for (size_type __c = 0; __c != std::min(cols(),\
    \ __x.rows()); ++__c)\n            __m[__r][__i] += operator[](__r)[__c] * __x[__c][__i];\n\
    \n    return __m;\n  }\n\n  matrix& operator*=(const value_type& __x) {\n    for\
    \ (size_type __r = 0; __r != rows(); ++__r)\n      operator[](__r).operator*=(__x);\n\
    \n    return *this;\n  }\n\n  matrix operator*(const value_type& __x) const {\
    \ return matrix(*this) *= __x; }\n\n  friend matrix operator*(const value_type&\
    \ __x, matrix __i) {\n    for (size_type __r = 0; __r != __i.rows(); ++__r)\n\
    \      __i.operator[](__r) = __x * __i.operator[](__r);\n\n    return __i;\n \
    \ }\n\n  matrix& operator/=(const value_type& __x) {\n    assert(__x != value_type(0));\n\
    \n    for (size_type __r = 0; __r != rows(); ++__r)\n      operator[](__r).operator/=(__x);\n\
    \n    return *this;\n  }\n\n  matrix operator/(const value_type& __x) const {\
    \ return matrix(*this) /= __x; }\n\n  // }} binary operators\n\n  template <class\
    \ _Int> matrix pow(_Int __e) const {\n    assert(0 <= __e);\n\n    matrix __m\
    \ = eye(rows());\n    for (matrix __cp = *this; __e; __cp *= __cp, __e >>= 1)\n\
    \      if (__e & 1) __m *= __cp;\n\n    return __m;\n  }\n\n  // template <class\
    \ _Is> friend _Is& operator>>(_Is& __is, matrix& __x) {\n  //   for (size_type\
    \ __r = 0; __r != __x.rows(); ++__r)\n  //     for (size_type __c = 0; __c !=\
    \ __x.cols(); ++__c)\n  //       __is >> __x.operator[](__r).operator[](__c);\n\
    \n  //   return __is;\n  // }\n\n  template <class _Os> friend _Os& operator<<(_Os&\
    \ __os, const matrix& __x) {\n    for (size_type __r = 0; __r != __x.rows(); ++__r,\
    \ __os << '\\n')\n      for (size_type __c = 0; __c != __x.cols(); ++__c)\n  \
    \      __c ? void(__os << ' ') : (void)0,\n            __os << __x.operator[](__r).operator[](__c);\n\
    \n    return __os;\n  }\n};\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file matrix.hpp\n * @brief Matrix\n * @date 2021-02-15\n\
    \ *\n *\n */\n\n#include <cassert>\n#include <valarray>\n\nnamespace workspace\
    \ {\n\n/**\n * @brief Fixed size matrix.\n *\n * @tparam _Scalar\n * @tparam _Rows\
    \ Number of rows\n * @tparam _Cols Number of columns\n */\ntemplate <class _Scalar,\
    \ std::size_t _Rows = 0, std::size_t _Cols = _Rows>\nclass matrix {\n public:\n\
    \  _Scalar __data[_Rows][_Cols] = {};\n\n  using value_type = _Scalar;\n  using\
    \ size_type = std::size_t;\n\n  constexpr static matrix eye() {\n    static_assert(_Rows\
    \ == _Cols);\n\n    matrix __e;\n    for (size_type __d = 0; __d != _Rows; ++__d)\
    \ __e.__data[__d][__d] = 1;\n    return __e;\n  }\n\n  constexpr operator decltype((__data))()\
    \ { return __data; }\n  constexpr operator decltype(std::declval<const matrix>().__data)\n\
    \      const&() const {\n    return __data;\n  }\n\n  constexpr auto begin() {\
    \ return __data; }\n  constexpr auto begin() const { return __data; }\n\n  constexpr\
    \ auto end() { return __data + _Rows; }\n  constexpr auto end() const { return\
    \ __data + _Rows; }\n\n  constexpr size_type rows() const { return _Rows; }\n\n\
    \  constexpr size_type cols() const { return _Cols; }\n\n  constexpr auto transpose()\
    \ const {\n    matrix<_Scalar, _Cols, _Rows> __t;\n\n    for (size_type __r =\
    \ 0; __r != _Rows; ++__r)\n      for (size_type __c = 0; __c != _Cols; ++__c)\n\
    \        __t.__data[__c][__r] = __data[__r][__c];\n\n    return __t;\n  }\n\n\
    \  constexpr matrix operator+() const { return *this; }\n\n  constexpr matrix\
    \ operator-() const {\n    matrix __cp = *this;\n\n    for (auto& __v : __cp.__data)\n\
    \      for (auto& __e : __v) __e = -__e;\n\n    return __cp;\n  }\n\n  template\
    \ <class _Matrix> constexpr matrix& operator+=(const _Matrix& __x) {\n    auto\
    \ __m = std::min(_Rows, __x.rows());\n    auto __n = std::min(_Cols, __x.cols());\n\
    \n    for (size_type __r = 0; __r != __m; ++__r)\n      for (size_type __c = 0;\
    \ __c != __n; ++__c)\n        __data[__r][__c] += __x[__r][__c];\n\n    return\
    \ *this;\n  }\n\n  template <class _Matrix>\n  constexpr matrix operator+(const\
    \ _Matrix& __x) const {\n    return matrix(*this) += __x;\n  }\n\n  template <class\
    \ _Matrix> constexpr matrix& operator-=(const _Matrix& __x) {\n    auto __m =\
    \ std::min(_Rows, __x.rows());\n    auto __n = std::min(_Cols, __x.cols());\n\n\
    \    for (size_type __r = 0; __r != __m; ++__r)\n      for (size_type __c = 0;\
    \ __c != __n; ++__c)\n        __data[__r][__c] -= __x[__r][__c];\n\n    return\
    \ *this;\n  }\n\n  template <class _Matrix>\n  constexpr matrix operator-(const\
    \ _Matrix& __x) const {\n    return matrix(*this) -= __x;\n  }\n\n  template <class\
    \ _Scalar2>\n  constexpr matrix& operator*=(const matrix<_Scalar2, _Cols, _Cols>&\
    \ __x) {\n    if (this == &__x) return operator=(operator*(__x));\n\n    for (auto&\
    \ __r : __data) {\n      _Scalar __tmp[_Cols] = {};\n\n      auto __v = *__x.__data;\n\
    \      for (auto& __w : __tmp) {\n        auto __i = __v++;\n        for (const\
    \ auto& __e : __r) __w += __e * *__i, __i += _Cols;\n      }\n\n      auto __w\
    \ = __tmp;\n      for (auto& __e : __r) __e = std::move(*__w++);\n    }\n\n  \
    \  return *this;\n  }\n\n  template <class _Scalar2, size_type _Rows2, size_type\
    \ _Cols2>\n  constexpr auto operator*(const matrix<_Scalar2, _Rows2, _Cols2>&\
    \ __x) const {\n    matrix<typename std::common_type<_Scalar, _Scalar2>::type,\
    \ _Rows, _Cols2>\n        __m;\n\n    auto __w = *__m.__data;\n    for (const\
    \ auto& __r : __data)\n      for (auto __v = *__x.__data, __v_end = __v + _Cols2;\
    \ __v != __v_end;\n           ++__w) {\n        auto __i = __v++;\n        for\
    \ (auto __e = __r; __e != __r + std::min(_Cols, _Rows2); ++__e)\n          *__w\
    \ += *__e * *__i, __i += _Cols2;\n      }\n\n    return __m;\n  }\n\n  template\
    \ <class _Matrix>\n  constexpr\n      typename std::enable_if<!std::is_convertible<_Matrix,\
    \ value_type>::value,\n                              matrix<_Scalar>>::type\n\
    \      operator*(const _Matrix& __x) const {\n    matrix<_Scalar> __m(_Rows, __x.cols());\n\
    \n    for (size_type __r = 0; __r != _Rows; ++__r)\n      for (size_type __i =\
    \ 0; __i != __x.cols(); ++__i)\n        for (size_type __c = 0; __c != std::min(_Cols,\
    \ __x.rows()); ++__c)\n          __m[__r][__i] += __data[__r][__c] * __x[__c][__i];\n\
    \n    return __m;\n  }\n\n  constexpr matrix& operator*=(const value_type& __x)\
    \ {\n    for (auto& __v : __data)\n      for (auto& __e : __v) __e *= __x;\n\n\
    \    return *this;\n  }\n\n  constexpr matrix operator*(const value_type& __x)\
    \ const {\n    return matrix(*this) *= __x;\n  }\n\n  constexpr matrix& operator/=(const\
    \ value_type& __x) {\n    assert(__x != value_type(0));\n\n    for (auto& __v\
    \ : __data)\n      for (auto& __e : __v) __e /= __x;\n\n    return *this;\n  }\n\
    \n  constexpr matrix operator/(const value_type& __x) const {\n    return matrix(*this)\
    \ /= __x;\n  }\n\n  template <class _Int> constexpr matrix pow(_Int __e) const\
    \ {\n    assert(0 <= __e);\n\n    matrix __m = eye();\n    for (matrix __cp =\
    \ *this; __e; __cp *= __cp, __e >>= 1)\n      if (__e & 1) __m *= __cp;\n\n  \
    \  return __m;\n  }\n\n  template <class _Os>\n  constexpr friend _Os& operator<<(_Os&\
    \ __os, const matrix& __x) {\n    for (auto __i = __x.begin(); __i != __x.end();\
    \ ++__i, __os << '\\n')\n      for (size_type __c = 0; __c != _Cols; ++__c)\n\
    \        __c ? void(__os << ' ') : (void)0, __os << *(*__i + __c);\n\n    return\
    \ __os;\n  }\n};  // namespace workspace\n\n/**\n * @brief Dynamic matrix.\n *\n\
    \ * @tparam _Scalar\n * @tparam _Rows Number of rows\n * @tparam _Cols Number\
    \ of columns\n */\ntemplate <class _Scalar>\nclass matrix<_Scalar, 0, 0> : public\
    \ std::valarray<std::valarray<_Scalar>> {\n  using base = std::valarray<std::valarray<_Scalar>>;\n\
    \  using row_type = typename base::value_type;\n\n public:\n  using value_type\
    \ = _Scalar;\n  using size_type = std::size_t;\n\n  using base::operator[];\n\n\
    \  static matrix eye(size_type __n) {\n    matrix __e(__n, __n);\n    for (size_type\
    \ __d = 0; __d != __n; ++__d) __e[__d][__d] = 1;\n    return __e;\n  }\n\n  matrix()\
    \ = default;\n\n  matrix(size_type __n) : matrix(__n, __n) {}\n\n  matrix(size_type\
    \ __m, size_type __n) : base(row_type(__n), __m) {}\n\n  template <class _Tp,\
    \ typename = typename std::enable_if<\n                           std::is_constructible<base,\
    \ _Tp>::value &&\n                           !std::is_constructible<size_type,\
    \ _Tp>::value>::type>\n  matrix(_Tp&& __x) : base(__x) {}\n\n  matrix(std::initializer_list<row_type>\
    \ __x) : base(__x) {}\n\n  size_type rows() const { return base::size(); }\n\n\
    \  size_type cols() const { return rows() ? operator[](0).size() : 0; }\n\n  matrix\
    \ transpose() const {\n    matrix __t(cols(), rows());\n\n    for (size_type __r\
    \ = 0; __r != rows(); ++__r)\n      for (size_type __c = 0; __c != cols(); ++__c)\n\
    \        __t[__c][__r] = operator[](__r)[__c];\n\n    return __t;\n  }\n\n  void\
    \ resize(size_type __m, size_type __n) {\n    matrix __t(__m, __n);\n\n    if\
    \ (rows() < __m) __m = rows();\n    if (cols() < __n) __n = cols();\n\n    for\
    \ (size_type __r = 0; __r != __m; ++__r)\n      for (size_type __c = 0; __c !=\
    \ __n; ++__c)\n        __t[__r][__c] = std::move(operator[](__r)[__c]);\n\n  \
    \  base::swap(__t);\n  }\n\n  // binary operators {{\n\n  template <class _Matrix,\
    \ typename = void>\n  struct is_valarray_based : std::false_type {};\n\n  template\
    \ <class _Matrix>\n  struct is_valarray_based<\n      _Matrix,\n      typename\
    \ std::enable_if<std::is_same<\n          row_type, typename std::decay<decltype(\n\
    \                        std::declval<_Matrix>()[0])>::type>::value>::type>\n\
    \      : std::true_type {};\n\n  template <class _Matrix>\n  typename std::enable_if<!std::is_convertible<_Matrix,\
    \ value_type>::value,\n                          matrix&>::type\n  operator*=(_Matrix&&\
    \ __x) {\n    return *this = operator*(std::forward<_Matrix>(__x));\n  }\n\n \
    \ template <class _Matrix>\n  typename std::enable_if<!std::is_convertible<_Matrix,\
    \ value_type>::value,\n                          matrix>::type\n  operator*(const\
    \ _Matrix& __x) const {\n    matrix __m(rows(), __x.cols());\n\n    if constexpr\
    \ (is_valarray_based<_Matrix>::value)\n      for (size_type __r = 0; __r != rows();\
    \ ++__r)\n        for (size_type __c = 0; __c != std::min(cols(), __x.rows());\
    \ ++__c)\n          __m[__r] += operator[](__r)[__c] * __x[__c];\n\n    else\n\
    \      for (size_type __r = 0; __r != rows(); ++__r)\n        for (size_type __i\
    \ = 0; __i != __x.cols(); ++__i)\n          for (size_type __c = 0; __c != std::min(cols(),\
    \ __x.rows()); ++__c)\n            __m[__r][__i] += operator[](__r)[__c] * __x[__c][__i];\n\
    \n    return __m;\n  }\n\n  matrix& operator*=(const value_type& __x) {\n    for\
    \ (size_type __r = 0; __r != rows(); ++__r)\n      operator[](__r).operator*=(__x);\n\
    \n    return *this;\n  }\n\n  matrix operator*(const value_type& __x) const {\
    \ return matrix(*this) *= __x; }\n\n  friend matrix operator*(const value_type&\
    \ __x, matrix __i) {\n    for (size_type __r = 0; __r != __i.rows(); ++__r)\n\
    \      __i.operator[](__r) = __x * __i.operator[](__r);\n\n    return __i;\n \
    \ }\n\n  matrix& operator/=(const value_type& __x) {\n    assert(__x != value_type(0));\n\
    \n    for (size_type __r = 0; __r != rows(); ++__r)\n      operator[](__r).operator/=(__x);\n\
    \n    return *this;\n  }\n\n  matrix operator/(const value_type& __x) const {\
    \ return matrix(*this) /= __x; }\n\n  // }} binary operators\n\n  template <class\
    \ _Int> matrix pow(_Int __e) const {\n    assert(0 <= __e);\n\n    matrix __m\
    \ = eye(rows());\n    for (matrix __cp = *this; __e; __cp *= __cp, __e >>= 1)\n\
    \      if (__e & 1) __m *= __cp;\n\n    return __m;\n  }\n\n  // template <class\
    \ _Is> friend _Is& operator>>(_Is& __is, matrix& __x) {\n  //   for (size_type\
    \ __r = 0; __r != __x.rows(); ++__r)\n  //     for (size_type __c = 0; __c !=\
    \ __x.cols(); ++__c)\n  //       __is >> __x.operator[](__r).operator[](__c);\n\
    \n  //   return __is;\n  // }\n\n  template <class _Os> friend _Os& operator<<(_Os&\
    \ __os, const matrix& __x) {\n    for (size_type __r = 0; __r != __x.rows(); ++__r,\
    \ __os << '\\n')\n      for (size_type __c = 0; __c != __x.cols(); ++__c)\n  \
    \      __c ? void(__os << ' ') : (void)0,\n            __os << __x.operator[](__r).operator[](__c);\n\
    \n    return __os;\n  }\n};\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/algebra/linear/matrix.hpp
  requiredBy:
  - src/algebra/linear/lu.hpp
  timestamp: '2021-02-22 16:48:42+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/aizu-online-judge/ITP1_6_D.test.cpp
  - test/aizu-online-judge/ITP1_7_D.test.cpp
  - test/library-checker/matrix_det.test.cpp
  - test/library-checker/system_of_linear_equations.test.cpp
documentation_of: src/algebra/linear/matrix.hpp
layout: document
redirect_from:
- /library/src/algebra/linear/matrix.hpp
- /library/src/algebra/linear/matrix.hpp.html
title: Matrix
---
