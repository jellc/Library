---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/algebra/linear/lu.hpp
    title: LU decomposition
  - icon: ':heavy_check_mark:'
    path: src/algebra/linear/matrix.hpp
    title: Matrix
  - icon: ':heavy_check_mark:'
    path: src/algebra/modint.hpp
    title: Modular Arithmetic
  - icon: ':heavy_check_mark:'
    path: src/number_theory/pow_mod.hpp
    title: Modular Exponentiation
  - icon: ':heavy_check_mark:'
    path: src/number_theory/sqrt_mod.hpp
    title: Tonelli-Shanks Algorithm
  - icon: ':heavy_check_mark:'
    path: src/utils/io/istream.hpp
    title: Input Stream
  - icon: ':heavy_check_mark:'
    path: src/utils/io/ostream.hpp
    title: Output Stream
  - icon: ':heavy_check_mark:'
    path: src/utils/sfinae.hpp
    title: SFINAE
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/system_of_linear_equations
    links:
    - https://judge.yosupo.jp/problem/system_of_linear_equations
  bundledCode: "#line 1 \"test/library-checker/system_of_linear_equations.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/system_of_linear_equations\"\
    \n\n#line 2 \"src/algebra/linear/lu.hpp\"\n\n/**\n * @file lu.hpp\n * @brief LU\
    \ decomposition\n */\n\n#include <numeric>\n\n#line 2 \"src/algebra/linear/matrix.hpp\"\
    \n\n/**\n * @file matrix.hpp\n * @brief Matrix\n * @date 2021-02-15\n *\n *\n\
    \ */\n\n#include <cassert>\n#include <valarray>\n\nnamespace workspace {\n\n/**\n\
    \ * @brief Fixed size matrix.\n *\n * @tparam _Scalar\n * @tparam _Rows Number\
    \ of rows\n * @tparam _Cols Number of columns\n */\ntemplate <class _Scalar, std::size_t\
    \ _Rows = 0, std::size_t _Cols = _Rows>\nclass matrix {\n public:\n  _Scalar __data[_Rows][_Cols]\
    \ = {};\n\n  using value_type = _Scalar;\n  using size_type = std::size_t;\n\n\
    \  constexpr static matrix eye() {\n    static_assert(_Rows == _Cols);\n\n   \
    \ matrix __e;\n    for (size_type __d = 0; __d != _Rows; ++__d) __e.__data[__d][__d]\
    \ = 1;\n    return __e;\n  }\n\n  constexpr operator decltype((__data))() { return\
    \ __data; }\n  constexpr operator decltype(std::declval<const matrix>().__data)\n\
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
    \n    return __os;\n  }\n};\n\n}  // namespace workspace\n#line 11 \"src/algebra/linear/lu.hpp\"\
    \n\nnamespace workspace {\n\ntemplate <class _Matrix> class lu_decomposition :\
    \ public _Matrix {\n public:\n  using value_type = typename _Matrix::value_type;\n\
    \  using size_type = typename _Matrix::size_type;\n\n  lu_decomposition() = default;\n\
    \  lu_decomposition(const _Matrix &__x) : _Matrix(__x) { run(); }\n  lu_decomposition(_Matrix\
    \ &&__x) : _Matrix(std::move(__x)) { run(); }\n\n protected:\n  std::vector<size_type>\
    \ __perm, __pivots;\n  bool sgn;\n\n  void run() {\n    __perm.resize(_Matrix::rows());\n\
    \    std::iota(__perm.begin(), __perm.end(), 0);\n    sgn = false;\n    __pivots.clear();\n\
    \n    for (size_type __c = 0;\n         __c != _Matrix::cols() && __pivots.size()\
    \ != _Matrix::rows(); ++__c) {\n      auto __max = (*this)[__pivots.size()][__c];\n\
    \      auto __pos = __pivots.size();\n\n      if constexpr (std::is_floating_point<\n\
    \                        value_type>::value) {  // Find the biggest absolute\n\
    \                                               // value in the column.\n    \
    \    for (size_type __r = __pivots.size() + 1; __r != _Matrix::rows(); ++__r)\n\
    \          if (std::abs(__max) < std::abs((*this)[__r][__c]))\n            __max\
    \ = (*this)[__pos = __r][__c];\n      }\n\n      else if (__max ==\n         \
    \      static_cast<value_type>(\n                   0))  // Find the first non-zero\
    \ element in the column.\n        for (size_type __r = __pivots.size() + 1; __r\
    \ != _Matrix::rows(); ++__r)\n          if ((__max = (*this)[__r][__c]) != static_cast<value_type>(0))\
    \ {\n            __pos = __r;\n            break;\n          }\n\n      if (__pos\
    \ != __pivots.size()) {  // Swap 2 rows.\n        sgn = !sgn;\n        std::swap(__perm[__pos],\
    \ __perm[__pivots.size()]);\n        std::swap((*this)[__pos], (*this)[__pivots.size()]);\n\
    \      }\n\n      if (__max != static_cast<value_type>(0)) {  // Forward elimination\n\
    \        for (size_type __r = __pivots.size() + 1; __r != _Matrix::rows();\n \
    \            ++__r) {\n          auto __m = (*this)[__r][__c] / __max;\n     \
    \     (*this)[__r][__c] = 0;\n          (*this)[__r][__pivots.size()] = __m;\n\
    \n          for (size_type __i = __c + 1; __i != _Matrix::cols(); ++__i)\n   \
    \         (*this)[__r][__i] -= (*this)[__pivots.size()][__i] * __m;\n        }\n\
    \n        __pivots.emplace_back(__c);\n      }\n    }\n  }\n\n public:\n  size_type\
    \ rank() const { return __pivots.size(); }\n\n  value_type det() const {\n   \
    \ assert(_Matrix::rows() == _Matrix::cols());\n\n    value_type __d = sgn ? -1\
    \ : 1;\n    for (size_type __i = 0; __i != _Matrix::rows(); ++__i)\n      __d\
    \ *= (*this)[__i][__i];\n    return __d;\n  }\n\n  _Matrix lower() const;\n\n\
    \  _Matrix upper() const;\n\n  _Matrix inverse() const {\n    assert(_Matrix::rows()\
    \ == _Matrix::cols());\n\n    _Matrix __inv;\n    // add solve(e_i) to __inv for\
    \ i=0, ..., rows()\n    return __inv;\n  }\n\n  // O(dim(ker) * size)\n  _Matrix\
    \ kernel() const {\n    _Matrix __ker(_Matrix::cols() - rank(), _Matrix::cols());\n\
    \n    for (size_type __c = 0, __i = 0; __c != _Matrix::cols(); ++__c) {\n    \
    \  if (__i != __pivots.size() && __pivots[__i] == __c) {\n        ++__i;\n   \
    \     continue;\n      }\n\n      auto &__v = __ker[__c - __i];\n      __v[__c]\
    \ = 1;\n      for (size_type __r = 0; __r != __i; ++__r) __v[__r] = -(*this)[__r][__c];\n\
    \n      for (size_type __j = __i; __j--;) {\n        auto __x = __v[__j] / (*this)[__j][__pivots[__j]];\n\
    \        __v[__j] = 0;\n        __v[__pivots[__j]] = __x;\n\n        for (size_type\
    \ __r = 0; __r != __j; ++__r)\n          __v[__r] -= (*this)[__r][__pivots[__j]]\
    \ * __x;\n      }\n    }\n\n    return __ker;\n  }\n\n  template <class _Vec>\
    \ std::pair<bool, _Vec> solve(const _Vec &__b) const {\n    assert(!(__b.size()\
    \ < _Matrix::rows()));\n\n    // Solution\n    _Vec __y(_Matrix::rows()), __x(_Matrix::cols());\n\
    \n    // Backward substitution with L\n    for (size_type __c = 0; __c != _Matrix::rows();\
    \ ++__c) {\n      __y[__c] += __b[__perm[__c]];\n\n      for (size_type __r =\
    \ __c + 1; __r != _Matrix::rows(); ++__r)\n        __y[__r] -= __y[__c] * (*this)[__r][__c];\n\
    \    }\n\n    // Backward substitution with U\n    for (size_type __i = rank();\
    \ __i != _Matrix::rows(); ++__i)\n      if (__y[__i] != static_cast<value_type>(0))\n\
    \        return std::make_pair(false, __x);\n\n    for (size_type __i = rank();\
    \ __i--;) {\n      auto __c = __pivots[__i];\n\n      __x[__c] = __y[__i] / (*this)[__i][__c];\n\
    \n      for (size_type __r = 0; __r != __i; ++__r)\n        __y[__r] -= __x[__c]\
    \ * (*this)[__r][__c];\n    }\n\n    return std::make_pair(true, __x);\n  }\n\
    };\n\n}  // namespace workspace\n#line 2 \"src/algebra/modint.hpp\"\n\n/**\n *\
    \ @file modint.hpp\n *\n * @brief Modular Arithmetic\n */\n\n#line 10 \"src/algebra/modint.hpp\"\
    \n#include <iostream>\n#include <vector>\n\n#line 2 \"src/number_theory/sqrt_mod.hpp\"\
    \n\n/**\n * @file sqrt_mod.hpp\n * @brief Tonelli-Shanks Algorithm\n */\n\n#line\
    \ 2 \"src/number_theory/pow_mod.hpp\"\n\n/**\n * @file mod_pow.hpp\n * @brief\
    \ Modular Exponentiation\n */\n\n#line 9 \"src/number_theory/pow_mod.hpp\"\n\n\
    #line 2 \"src/utils/sfinae.hpp\"\n\n/**\n * @file sfinae.hpp\n * @brief SFINAE\n\
    \ */\n\n#include <cstdint>\n#include <iterator>\n#include <type_traits>\n\n#ifndef\
    \ __INT128_DEFINED__\n\n#ifdef __SIZEOF_INT128__\n#define __INT128_DEFINED__ 1\n\
    #else\n#define __INT128_DEFINED__ 0\n#endif\n\n#endif\n\nnamespace std {\n\n#if\
    \ __INT128_DEFINED__\n\ntemplate <> struct make_signed<__uint128_t> { using type\
    \ = __int128_t; };\ntemplate <> struct make_signed<__int128_t> { using type =\
    \ __int128_t; };\n\ntemplate <> struct make_unsigned<__uint128_t> { using type\
    \ = __uint128_t; };\ntemplate <> struct make_unsigned<__int128_t> { using type\
    \ = __uint128_t; };\n\ntemplate <> struct is_signed<__uint128_t> : std::false_type\
    \ {};\ntemplate <> struct is_signed<__int128_t> : std::true_type {};\n\ntemplate\
    \ <> struct is_unsigned<__uint128_t> : std::true_type {};\ntemplate <> struct\
    \ is_unsigned<__int128_t> : std::false_type {};\n\n#endif\n\n}  // namespace std\n\
    \nnamespace workspace {\n\ntemplate <class Tp, class... Args> struct variadic_front\
    \ { using type = Tp; };\n\ntemplate <class... Args> struct variadic_back;\n\n\
    template <class Tp> struct variadic_back<Tp> { using type = Tp; };\n\ntemplate\
    \ <class Tp, class... Args> struct variadic_back<Tp, Args...> {\n  using type\
    \ = typename variadic_back<Args...>::type;\n};\n\ntemplate <class type, template\
    \ <class> class trait>\nusing enable_if_trait_type = typename std::enable_if<trait<type>::value>::type;\n\
    \n/**\n * @brief Return type of subscripting ( @c [] ) access.\n */\ntemplate\
    \ <class _Tp>\nusing subscripted_type =\n    typename std::decay<decltype(std::declval<_Tp&>()[0])>::type;\n\
    \ntemplate <class Container>\nusing element_type = typename std::decay<decltype(\n\
    \    *std::begin(std::declval<Container&>()))>::type;\n\ntemplate <class _Tp,\
    \ class = std::nullptr_t>\nstruct has_begin : std::false_type {};\n\ntemplate\
    \ <class _Tp>\nstruct has_begin<_Tp, decltype(std::begin(std::declval<_Tp>()),\
    \ nullptr)>\n    : std::true_type {};\n\ntemplate <class _Tp, class = void> struct\
    \ has_mod : std::false_type {};\n\ntemplate <class _Tp>\nstruct has_mod<_Tp, std::__void_t<decltype(_Tp::mod)>>\
    \ : std::true_type {};\n\ntemplate <class _Tp, class = void> struct is_integral_ext\
    \ : std::false_type {};\ntemplate <class _Tp>\nstruct is_integral_ext<\n    _Tp,\
    \ typename std::enable_if<std::is_integral<_Tp>::value>::type>\n    : std::true_type\
    \ {};\n\n#if __INT128_DEFINED__\n\ntemplate <> struct is_integral_ext<__int128_t>\
    \ : std::true_type {};\ntemplate <> struct is_integral_ext<__uint128_t> : std::true_type\
    \ {};\n\n#endif\n\n#if __cplusplus >= 201402\n\ntemplate <class _Tp>\nconstexpr\
    \ static bool is_integral_ext_v = is_integral_ext<_Tp>::value;\n\n#endif\n\ntemplate\
    \ <typename _Tp, typename = void> struct multiplicable_uint {\n  using type =\
    \ uint_least32_t;\n};\ntemplate <typename _Tp>\nstruct multiplicable_uint<\n \
    \   _Tp,\n    typename std::enable_if<(2 < sizeof(_Tp)) &&\n                 \
    \           (!__INT128_DEFINED__ || sizeof(_Tp) <= 4)>::type> {\n  using type\
    \ = uint_least64_t;\n};\n\n#if __INT128_DEFINED__\n\ntemplate <typename _Tp>\n\
    struct multiplicable_uint<_Tp,\n                          typename std::enable_if<(4\
    \ < sizeof(_Tp))>::type> {\n  using type = __uint128_t;\n};\n\n#endif\n\ntemplate\
    \ <typename _Tp> struct multiplicable_int {\n  using type =\n      typename std::make_signed<typename\
    \ multiplicable_uint<_Tp>::type>::type;\n};\n\ntemplate <typename _Tp> struct\
    \ multiplicable {\n  using type = std::conditional_t<\n      is_integral_ext<_Tp>::value,\n\
    \      std::conditional_t<std::is_signed<_Tp>::value,\n                      \
    \   typename multiplicable_int<_Tp>::type,\n                         typename\
    \ multiplicable_uint<_Tp>::type>,\n      _Tp>;\n};\n\ntemplate <class> struct\
    \ first_arg { using type = void; };\n\ntemplate <class _R, class _Tp, class...\
    \ _Args>\nstruct first_arg<_R(_Tp, _Args...)> {\n  using type = _Tp;\n};\n\ntemplate\
    \ <class _R, class _Tp, class... _Args>\nstruct first_arg<_R (*)(_Tp, _Args...)>\
    \ {\n  using type = _Tp;\n};\n\ntemplate <class _G, class _R, class _Tp, class...\
    \ _Args>\nstruct first_arg<_R (_G::*)(_Tp, _Args...)> {\n  using type = _Tp;\n\
    };\n\ntemplate <class _G, class _R, class _Tp, class... _Args>\nstruct first_arg<_R\
    \ (_G::*)(_Tp, _Args...) const> {\n  using type = _Tp;\n};\n\ntemplate <class\
    \ _Tp, class = void> struct parse_compare : first_arg<_Tp> {};\n\ntemplate <class\
    \ _Tp>\nstruct parse_compare<_Tp, std::__void_t<decltype(&_Tp::operator())>>\n\
    \    : first_arg<decltype(&_Tp::operator())> {};\n\n}  // namespace workspace\n\
    #line 11 \"src/number_theory/pow_mod.hpp\"\n\nnamespace workspace {\n\n/**\n *\
    \ @brief Compile time modular exponentiation.\n *\n * @param __x\n * @param __n\
    \ Exponent\n * @param __mod Modulus\n * @return\n */\ntemplate <class _Tp>\nconstexpr\
    \ std::enable_if_t<(is_integral_ext<_Tp>::value), _Tp> pow_mod(\n    _Tp __x,\
    \ _Tp __n, _Tp __mod) noexcept {\n  assert(__mod > 0);\n\n  using mul_type = typename\
    \ multiplicable_uint<_Tp>::type;\n\n  if ((__x %= __mod) < 0) __x += __mod;\n\n\
    \  mul_type __y{1};\n\n  while (__n) {\n    if (__n & 1) (__y *= __x) %= __mod;\n\
    \    __x = (mul_type)__x * __x % __mod;\n    __n >>= 1;\n  }\n\n  return __y;\n\
    };\n\n}  // namespace workspace\n#line 10 \"src/number_theory/sqrt_mod.hpp\"\n\
    \nnamespace workspace {\n\n/**\n * @brief Compile time modular square root.\n\
    \ *\n * @param __x\n * @param __mod Modulus\n * @return One if it exists. Otherwise\
    \ -1.\n */\ntemplate <class _Tp>\nconstexpr std::enable_if_t<(is_integral_ext<_Tp>::value),\
    \ _Tp> sqrt_mod(\n    _Tp __x, _Tp __mod) noexcept {\n  assert(__mod > 0);\n\n\
    \  using mul_type = typename multiplicable_uint<_Tp>::type;\n\n  if ((__x %= __mod)\
    \ < 0) __x += __mod;\n\n  if (!__x) return 0;\n\n  if (__mod == 2) return __x;\n\
    \n  if (pow_mod(__x, __mod >> 1, __mod) != 1) return -1;\n\n  _Tp __z = __builtin_ctz(__mod\
    \ - 1), __q = __mod >> __z;\n\n  mul_type __a = pow_mod(__x, (__q + 1) >> 1, __mod),\
    \ __b = 2;\n  while (pow_mod<_Tp>(__b, __mod >> 1, __mod) == 1) ++__b;\n  __b\
    \ = pow_mod<_Tp>(__b, __q, __mod);\n\n  _Tp __shift = 0;\n\n  for (auto __r =\
    \ __a * __a % __mod * pow_mod(__x, __mod - 2, __mod) % __mod;\n       __r != 1;\
    \ (__r *= (__b *= __b) %= __mod) %= __mod) {\n    auto __bsf = __z;\n\n    for\
    \ (auto __e = __r; __e != 1; --__bsf) (__e *= __e) %= __mod;\n\n    while (++__shift\
    \ != __bsf) (__b *= __b) %= __mod;\n\n    (__a *= __b) %= __mod;\n  }\n\n  return\
    \ __a;\n};\n\n}  // namespace workspace\n#line 15 \"src/algebra/modint.hpp\"\n\
    \nnamespace workspace {\n\nnamespace _modint_impl {\n\ntemplate <auto _Mod, unsigned\
    \ _Storage> struct modint {\n  static_assert(is_integral_ext<decltype(_Mod)>::value,\n\
    \                \"_Mod must be integral type.\");\n\n  using mod_type = std::make_signed_t<typename\
    \ std::conditional<\n      0 < _Mod, std::add_const_t<decltype(_Mod)>, decltype(_Mod)>::type>;\n\
    \n  using value_type = std::decay_t<mod_type>;\n\n  using mul_type = typename\
    \ multiplicable_uint<value_type>::type;\n\n  // Modulus\n  static mod_type mod;\n\
    \n  static unsigned storage;\n\n private:\n  value_type value = 0;\n\n  struct\
    \ direct_ctor_t {};\n  constexpr static direct_ctor_t direct_ctor_tag{};\n\n \
    \ // Direct constructor\n  template <class _Tp>\n  constexpr modint(_Tp __n, direct_ctor_t)\
    \ noexcept : value(__n) {}\n\n public:\n  constexpr modint() noexcept = default;\n\
    \n  template <class _Tp, class = std::enable_if_t<\n                         \
    \  std::is_convertible<_Tp, value_type>::value>>\n  constexpr modint(_Tp __n)\
    \ noexcept\n      : value((__n %= mod) < 0 ? __n + mod : __n) {}\n\n  constexpr\
    \ modint(bool __n) noexcept : value(__n) {}\n\n  constexpr operator value_type()\
    \ const noexcept { return value; }\n\n  // unary operators {{\n  constexpr modint\
    \ operator++(int) noexcept {\n    modint __t{*this};\n    operator++();\n    return\
    \ __t;\n  }\n\n  constexpr modint operator--(int) noexcept {\n    modint __t{*this};\n\
    \    operator--();\n    return __t;\n  }\n\n  constexpr modint &operator++() noexcept\
    \ {\n    if (++value == mod) value = 0;\n    return *this;\n  }\n\n  constexpr\
    \ modint &operator--() noexcept {\n    if (!value)\n      value = mod - 1;\n \
    \   else\n      --value;\n    return *this;\n  }\n\n  constexpr modint operator+()\
    \ const noexcept { return *this; }\n\n  constexpr modint operator-() const noexcept\
    \ {\n    return {value ? mod - value : 0, direct_ctor_tag};\n  }\n\n  // }} unary\
    \ operators\n\n  // operator+= {{\n\n  constexpr modint &operator+=(const modint\
    \ &__x) noexcept {\n    if ((value += __x.value) >= mod) value -= mod;\n    return\
    \ *this;\n  }\n\n  template <class _Tp>\n  constexpr std::enable_if_t<is_integral_ext<_Tp>::value,\
    \ modint> &operator+=(\n      _Tp __x) noexcept {\n    __x %= mod, value += __x;\n\
    \    if (value < 0)\n      value += mod;\n    else if (value >= mod)\n      value\
    \ -= mod;\n    return *this;\n  }\n\n  // }} operator+=\n\n  // operator+ {{\n\
    \n  template <class _Tp>\n  constexpr std::enable_if_t<is_integral_ext<_Tp>::value,\
    \ modint> operator+(\n      _Tp const &__x) const noexcept {\n    return modint{*this}\
    \ += __x;\n  }\n\n  constexpr modint operator+(modint __x) const noexcept { return\
    \ __x += *this; }\n\n  template <class _Tp>\n  constexpr friend std::enable_if_t<is_integral_ext<_Tp>::value,\
    \ modint>\n  operator+(_Tp const &__x, modint __y) noexcept {\n    return __y\
    \ += __x;\n  }\n\n  // }} operator+\n\n  // operator-= {{\n\n  constexpr modint\
    \ &operator-=(const modint &__x) noexcept {\n    if ((value -= __x.value) < 0)\
    \ value += mod;\n    return *this;\n  }\n\n  template <class _Tp>\n  constexpr\
    \ std::enable_if_t<is_integral_ext<_Tp>::value, modint> &operator-=(\n      _Tp\
    \ __x) noexcept {\n    __x %= mod, value -= __x;\n    if (value < 0)\n      value\
    \ += mod;\n    else if (value >= mod)\n      value -= mod;\n    return *this;\n\
    \  }\n\n  // }} operator-=\n\n  // operator- {{\n\n  template <class _Tp>\n  constexpr\
    \ std::enable_if_t<is_integral_ext<_Tp>::value, modint> operator-(\n      _Tp\
    \ const &__x) const noexcept {\n    return modint{*this} -= __x;\n  }\n\n  constexpr\
    \ modint operator-(const modint &__x) const noexcept {\n    return modint{*this}\
    \ -= __x;\n  }\n\n  template <class _Tp>\n  constexpr friend std::enable_if_t<is_integral_ext<_Tp>::value,\
    \ modint>\n  operator-(_Tp __x, const modint &__y) noexcept {\n    if (((__x -=\
    \ __y.value) %= mod) < 0) __x += mod;\n    return {__x, direct_ctor_tag};\n  }\n\
    \n  // }} operator-\n\n  // operator*= {{\n\n  constexpr modint &operator*=(const\
    \ modint &__x) noexcept {\n    value =\n        static_cast<value_type>(value\
    \ * static_cast<mul_type>(__x.value) % mod);\n    return *this;\n  }\n\n  template\
    \ <class _Tp>\n  constexpr std::enable_if_t<is_integral_ext<_Tp>::value, modint>\
    \ &operator*=(\n      _Tp __x) noexcept {\n    value = static_cast<value_type>(\n\
    \        value * mul_type((__x %= mod) < 0 ? __x + mod : __x) % mod);\n    return\
    \ *this;\n  }\n\n  // }} operator*=\n\n  // operator* {{\n\n  constexpr modint\
    \ operator*(const modint &__x) const noexcept {\n    return {static_cast<mul_type>(value)\
    \ * __x.value % mod, direct_ctor_tag};\n  }\n\n  template <class _Tp>\n  constexpr\
    \ std::enable_if_t<is_integral_ext<_Tp>::value, modint> operator*(\n      _Tp\
    \ __x) const noexcept {\n    __x %= mod;\n    if (__x < 0) __x += mod;\n    return\
    \ {static_cast<mul_type>(value) * __x % mod, direct_ctor_tag};\n  }\n\n  template\
    \ <class _Tp>\n  constexpr friend std::enable_if_t<is_integral_ext<_Tp>::value,\
    \ modint>\n  operator*(_Tp __x, const modint &__y) noexcept {\n    __x %= mod;\n\
    \    if (__x < 0) __x += mod;\n    return {static_cast<mul_type>(__x) * __y.value\
    \ % mod, direct_ctor_tag};\n  }\n\n  // }} operator*\n\n protected:\n  static\
    \ value_type _mem(value_type __x) {\n    static std::vector<value_type> __m{0,\
    \ 1};\n    static value_type __i = (__m.reserve(storage), 1);\n    while (__i\
    \ < __x) {\n      ++__i;\n      __m.emplace_back(mod - mul_type(mod / __i) * __m[mod\
    \ % __i] % mod);\n    }\n    return __m[__x];\n  }\n\n  static value_type _div(mul_type\
    \ __r, value_type __x) noexcept {\n    assert(__x != value_type(0));\n    if (!__r)\
    \ return 0;\n\n    std::make_signed_t<value_type> __v{};\n    bool __neg = __x\
    \ < 0 ? __x = -__x, true : false;\n\n    if (static_cast<decltype(storage)>(__x)\
    \ < storage)\n      __v = _mem(__x);\n    else {\n      value_type __y{mod}, __u{1},\
    \ __t;\n\n      while (__x)\n        __t = __y / __x, __y ^= __x ^= (__y -= __t\
    \ * __x) ^= __x,\n        __v ^= __u ^= (__v -= __t * __u) ^= __u;\n\n      if\
    \ (__y < 0) __neg ^= 1;\n    }\n\n    if (__neg)\n      __v = 0 < __v ? mod -\
    \ __v : -__v;\n    else if (__v < 0)\n      __v += mod;\n\n    return __r == mul_type(1)\
    \ ? static_cast<value_type>(__v)\n                              : static_cast<value_type>(__r\
    \ * __v % mod);\n  }\n\n public:\n  static void reserve(unsigned __n) noexcept\
    \ {\n    if (storage < __n) storage = __n;\n  }\n\n  // operator/= {{\n\n  constexpr\
    \ modint &operator/=(const modint &__x) noexcept {\n    if (value) value = _div(value,\
    \ __x.value);\n    return *this;\n  }\n\n  template <class _Tp>\n  constexpr std::enable_if_t<is_integral_ext<_Tp>::value,\
    \ modint> &operator/=(\n      _Tp __x) noexcept {\n    if (value) value = _div(value,\
    \ __x %= mod);\n    return *this;\n  }\n\n  // }} operator/=\n\n  // operator/\
    \ {{\n\n  constexpr modint operator/(const modint &__x) const noexcept {\n   \
    \ if (!value) return {};\n    return {_div(value, __x.value), direct_ctor_tag};\n\
    \  }\n\n  template <class _Tp>\n  constexpr std::enable_if_t<is_integral_ext<_Tp>::value,\
    \ modint> operator/(\n      _Tp __x) const noexcept {\n    if (!value) return\
    \ {};\n    return {_div(value, __x %= mod), direct_ctor_tag};\n  }\n\n  template\
    \ <class _Tp>\n  constexpr friend std::enable_if_t<is_integral_ext<_Tp>::value,\
    \ modint>\n  operator/(_Tp __x, const modint &__y) noexcept {\n    if (!__x) return\
    \ {};\n    if ((__x %= mod) < 0) __x += mod;\n    return {_div(__x, __y.value),\
    \ direct_ctor_tag};\n  }\n\n  // }} operator/\n\n  constexpr modint inv() const\
    \ noexcept { return _div(1, value); }\n\n  template <class _Tp>\n  constexpr std::enable_if_t<is_integral_ext<_Tp>::value,\
    \ modint> pow(\n      _Tp __e) const noexcept {\n    modint __r{mod != 1, direct_ctor_tag};\n\
    \n    for (modint __b{__e < 0 ? __e = -__e, _div(1, value) : value,\n        \
    \                      direct_ctor_tag};\n         __e; __e >>= 1, __b *= __b)\n\
    \      if (__e & 1) __r *= __b;\n\n    return __r;\n  }\n\n  template <class _Tp>\n\
    \  constexpr friend std::enable_if_t<is_integral_ext<_Tp>::value, modint> pow(\n\
    \      modint __b, _Tp __e) noexcept {\n    if (__e < 0) {\n      __e = -__e;\n\
    \      __b.value = _div(1, __b.value);\n    }\n\n    modint __r{mod != 1, direct_ctor_tag};\n\
    \n    for (; __e; __e >>= 1, __b *= __b)\n      if (__e & 1) __r *= __b;\n\n \
    \   return __r;\n  }\n\n  constexpr modint sqrt() const noexcept {\n    return\
    \ {sqrt_mod(value, mod), direct_ctor_tag};\n  }\n\n  friend constexpr modint sqrt(const\
    \ modint &__x) noexcept {\n    return {sqrt_mod(__x.value, mod), direct_ctor_tag};\n\
    \  }\n\n  friend std::istream &operator>>(std::istream &__is, modint &__x) noexcept\
    \ {\n    std::string __s;\n    __is >> __s;\n    bool __neg = false;\n    if (__s.front()\
    \ == '-') {\n      __neg = true;\n      __s.erase(__s.begin());\n    }\n    __x\
    \ = 0;\n    for (char __c : __s) __x = __x * 10 + (__c - '0');\n    if (__neg)\
    \ __x = -__x;\n    return __is;\n  }\n};\n\ntemplate <auto _Mod, unsigned _Storage>\n\
    typename modint<_Mod, _Storage>::mod_type modint<_Mod, _Storage>::mod =\n    _Mod\
    \ > 0 ? _Mod : 0;\n\ntemplate <auto _Mod, unsigned _Storage>\nunsigned modint<_Mod,\
    \ _Storage>::storage = _Storage;\n\n}  // namespace _modint_impl\n\ntemplate <auto\
    \ _Mod, unsigned _Storage = 0,\n          typename = std::enable_if_t<(_Mod >\
    \ 0)>>\nusing modint = _modint_impl::modint<_Mod, _Storage>;\n\ntemplate <unsigned\
    \ _Id = 0, unsigned _Storage = 0>\nusing runtime_modint = _modint_impl::modint<-(signed)_Id,\
    \ 0>;\n\ntemplate <unsigned _Id = 0, unsigned _Storage = 0>\nusing runtime_modint64\
    \ = _modint_impl::modint<-(int_least64_t)_Id, 0>;\n\n}  // namespace workspace\n\
    #line 2 \"src/utils/io/istream.hpp\"\n\n/**\n * @file istream.hpp\n * @brief Input\
    \ Stream\n */\n\n#include <cxxabi.h>\n\n#line 12 \"src/utils/io/istream.hpp\"\n\
    #include <tuple>\n\n#line 2 \"lib/cxx17\"\n\n#ifndef _CXX17_CONSTEXPR\n#if __cplusplus\
    \ >= 201703L\n#define _CXX17_CONSTEXPR constexpr\n#else\n#define _CXX17_CONSTEXPR\n\
    #endif\n#endif\n\n#ifndef _CXX17_STATIC_ASSERT\n#if __cplusplus >= 201703L\n#define\
    \ _CXX17_STATIC_ASSERT static_assert\n#else\n#define _CXX17_STATIC_ASSERT assert\n\
    #endif\n#endif\n\n#if __cplusplus < 201703L\n\nnamespace std {\n\n/**\n *  @brief\
    \  Return the size of a container.\n *  @param  __cont  Container.\n */\ntemplate\
    \ <typename _Container>\nconstexpr auto size(const _Container& __cont) noexcept(noexcept(__cont.size()))\n\
    \    -> decltype(__cont.size()) {\n  return __cont.size();\n}\n\n/**\n *  @brief\
    \  Return the size of an array.\n */\ntemplate <typename _Tp, size_t _Nm>\nconstexpr\
    \ size_t size(const _Tp (&)[_Nm]) noexcept {\n  return _Nm;\n}\n\n}  // namespace\
    \ std\n\n#endif\n#line 16 \"src/utils/io/istream.hpp\"\n\nnamespace workspace\
    \ {\n\nnamespace _istream_impl {\n\ntemplate <class _Tp, typename = void> struct\
    \ helper {\n  helper(std::istream &__is, _Tp &__x) {\n    if _CXX17_CONSTEXPR\
    \ (has_begin<_Tp &>::value)\n      for (auto &&__e : __x) helper<std::decay_t<decltype(__e)>>(__is,\
    \ __e);\n    else\n      static_assert(has_begin<_Tp>::value, \"istream unsupported\
    \ type.\");\n  }\n};\n\ntemplate <class _Tp>\nstruct helper<_Tp, std::__void_t<decltype(std::declval<std::istream\
    \ &>() >>\n                                          std::declval<_Tp &>())>>\
    \ {\n  helper(std::istream &__is, _Tp &__x) { __is >> __x; }\n};\n\n#ifdef __SIZEOF_INT128__\n\
    \ntemplate <> struct helper<__uint128_t, void> {\n  helper(std::istream &__is,\
    \ __uint128_t &__x) {\n    std::string __s;\n    __is >> __s;\n    bool __neg\
    \ = false;\n    if (__s.front() == '-') __neg = true, __s.erase(__s.begin());\n\
    \    __x = 0;\n    for (char __d : __s) {\n      __x *= 10;\n      __d -= '0';\n\
    \      if (__neg)\n        __x -= __d;\n      else\n        __x += __d;\n    }\n\
    \  }\n};\n\ntemplate <> struct helper<__int128_t, void> {\n  helper(std::istream\
    \ &__is, __int128_t &__x) {\n    std::string __s;\n    __is >> __s;\n    bool\
    \ __neg = false;\n    if (__s.front() == '-') __neg = true, __s.erase(__s.begin());\n\
    \    __x = 0;\n    for (char __d : __s) {\n      __x *= 10;\n      __d -= '0';\n\
    \      if (__neg)\n        __x -= __d;\n      else\n        __x += __d;\n    }\n\
    \  }\n};\n\n#endif  // INT128\n\ntemplate <class _T1, class _T2> struct helper<std::pair<_T1,\
    \ _T2>> {\n  helper(std::istream &__is, std::pair<_T1, _T2> &__x) {\n    helper<_T1>(__is,\
    \ __x.first), helper<_T2>(__is, __x.second);\n  }\n};\n\ntemplate <class... _Tp>\
    \ struct helper<std::tuple<_Tp...>> {\n  helper(std::istream &__is, std::tuple<_Tp...>\
    \ &__x) { iterate(__is, __x); }\n\n private:\n  template <class _Tuple, size_t\
    \ _Nm = 0>\n  void iterate(std::istream &__is, _Tuple &__x) {\n    if _CXX17_CONSTEXPR\
    \ (_Nm != std::tuple_size<_Tuple>::value) {\n      helper<typename std::tuple_element<_Nm,\
    \ _Tuple>::type>(\n          __is, std::get<_Nm>(__x)),\n          iterate<_Tuple,\
    \ _Nm + 1>(__is, __x);\n    }\n  }\n};\n\n}  // namespace _istream_impl\n\n/**\n\
    \ * @brief A wrapper class for std::istream.\n */\nclass istream : public std::istream\
    \ {\n public:\n  /**\n   * @brief Wrapped operator.\n   */\n  template <typename\
    \ _Tp> istream &operator>>(_Tp &__x) {\n    _istream_impl::helper<_Tp>(*this,\
    \ __x);\n    if (std::istream::fail()) {\n      static auto once = atexit([] {\n\
    \        std::cerr << \"\\n\\033[43m\\033[30mwarning: failed to read \\'\"\n \
    \                 << abi::__cxa_demangle(typeid(_Tp).name(), 0, 0, 0)\n      \
    \            << \"\\'.\\033[0m\\n\\n\";\n      });\n      assert(!once);\n   \
    \ }\n    return *this;\n  }\n};\n\ndecltype(auto) cin = static_cast<istream &>(std::cin);\n\
    \n}  // namespace workspace\n#line 2 \"src/utils/io/ostream.hpp\"\n\n/**\n * @file\
    \ ostream.hpp\n * @brief Output Stream\n */\n\n#line 9 \"src/utils/io/ostream.hpp\"\
    \n\n#line 11 \"src/utils/io/ostream.hpp\"\n\nnamespace workspace {\n\ntemplate\
    \ <class _Os> struct is_ostream {\n  template <typename... _Args>\n  static std::true_type\
    \ __test(std::basic_ostream<_Args...> *);\n  static std::false_type __test(void\
    \ *);\n  constexpr static bool value = decltype(__test(std::declval<_Os *>()))::value;\n\
    };\n\ntemplate <class _Os>\nusing ostream_ref =\n    typename std::enable_if<is_ostream<_Os>::value,\
    \ _Os &>::type;\n\n/**\n * @brief Stream insertion operator for C-style array.\n\
    \ *\n * @param __os Output stream\n * @param __a Array\n * @return Reference to\
    \ __os.\n */\ntemplate <class _Os, class _Tp, size_t _Nm>\ntypename std::enable_if<bool(sizeof(_Tp)\
    \ > 2), ostream_ref<_Os>>::type\noperator<<(_Os &__os, const _Tp (&__a)[_Nm])\
    \ {\n  if _CXX17_CONSTEXPR (_Nm) {\n    __os << *__a;\n    for (auto __i = __a\
    \ + 1, __e = __a + _Nm; __i != __e; ++__i)\n      __os << ' ' << *__i;\n  }\n\
    \  return __os;\n}\n\n/**\n * @brief Stream insertion operator for std::array.\n\
    \ *\n * @param __os Output stream\n * @param __a Array\n * @return Reference to\
    \ __os.\n */\ntemplate <class _Os, class _Tp, size_t _Nm>\nostream_ref<_Os> operator<<(_Os\
    \ &__os, const std::array<_Tp, _Nm> &__a) {\n  if _CXX17_CONSTEXPR (_Nm) {\n \
    \   __os << __a[0];\n    for (size_t __i = 1; __i != _Nm; ++__i) __os << ' ' <<\
    \ __a[__i];\n  }\n  return __os;\n}\n\n/**\n * @brief Stream insertion operator\
    \ for std::pair.\n *\n * @param __os Output stream\n * @param __p Pair\n * @return\
    \ Reference to __os.\n */\ntemplate <class _Os, class _T1, class _T2>\nostream_ref<_Os>\
    \ operator<<(_Os &__os, const std::pair<_T1, _T2> &__p) {\n  return __os << __p.first\
    \ << ' ' << __p.second;\n}\n\n/**\n * @brief Stream insertion operator for std::tuple.\n\
    \ *\n * @param __os Output stream\n * @param __t Tuple\n * @return Reference to\
    \ __os.\n */\ntemplate <class _Os, class _Tp, size_t _Nm = 0>\ntypename std::enable_if<bool(std::tuple_size<_Tp>::value\
    \ + 1),\n                        ostream_ref<_Os>>::type\noperator<<(_Os &__os,\
    \ const _Tp &__t) {\n  if _CXX17_CONSTEXPR (_Nm != std::tuple_size<_Tp>::value)\
    \ {\n    if _CXX17_CONSTEXPR (_Nm) __os << ' ';\n    __os << std::get<_Nm>(__t);\n\
    \    operator<<<_Os, _Tp, _Nm + 1>(__os, __t);\n  }\n  return __os;\n}\n\ntemplate\
    \ <class _Os, class _Container,\n          typename = decltype(std::begin(std::declval<_Container>()))>\n\
    typename std::enable_if<\n    !std::is_convertible<std::decay_t<_Container>, std::string>::value\
    \ &&\n        !std::is_convertible<std::decay_t<_Container>, char *>::value,\n\
    \    ostream_ref<_Os>>::type\noperator<<(_Os &__os, const _Container &__cont)\
    \ {\n  bool __h = true;\n  for (auto &&__e : __cont) __h ? __h = 0 : (__os <<\
    \ ' ', 0), __os << __e;\n  return __os;\n}\n\n#ifdef __SIZEOF_INT128__\n\n/**\n\
    \ * @brief Stream insertion operator for __int128_t.\n *\n * @param __os Output\
    \ Stream\n * @param __x 128-bit integer\n * @return Reference to __os.\n */\n\
    template <class _Os> ostream_ref<_Os> operator<<(_Os &__os, __int128_t __x) {\n\
    \  if (!__x) return __os << '0';\n  if (__x < 0) __os << '-';\n  char __s[40],\
    \ *__p = __s;\n  while (__x) {\n    auto __d = __x % 10;\n    *__p++ = '0' + (__x\
    \ < 0 ? -__d : __d);\n    __x /= 10;\n  }\n  *__p = 0;\n  for (char *__t = __s;\
    \ __t < --__p; ++__t) *__t ^= *__p ^= *__t ^= *__p;\n  return __os << __s;\n}\n\
    \n/**\n * @brief Stream insertion operator for __uint128_t.\n *\n * @param __os\
    \ Output Stream\n * @param __x 128-bit unsigned integer\n * @return Reference\
    \ to __os.\n */\ntemplate <class _Os> ostream_ref<_Os> operator<<(_Os &__os, __uint128_t\
    \ __x) {\n  if (!__x) return __os << '0';\n  char __s[40], *__p = __s;\n  while\
    \ (__x) *__p++ = '0' + __x % 10, __x /= 10;\n  *__p = 0;\n  for (char *__t = __s;\
    \ __t < --__p; ++__t) *__t ^= *__p ^= *__t ^= *__p;\n  return __os << __s;\n}\n\
    \n#endif\n\n}  // namespace workspace\n#line 7 \"test/library-checker/system_of_linear_equations.test.cpp\"\
    \n\nnamespace workspace {\n\nusing mint = modint<998244353>;\nusing mat = matrix<mint>;\n\
    \nvoid main() {\n  // start here!\n\n  size_t n, m;\n  cin >> n >> m;\n\n  lu_decomposition\
    \ lu = [&] {\n    mat a(n, m);\n    cin >> a;\n    return a;\n  }();\n\n  auto\
    \ res = lu.solve([&] {\n    std::vector<mint> b(n);\n    cin >> b;\n    return\
    \ b;\n  }());\n\n  if (!res.first) {\n    std::cout << \"-1\\n\";\n    return;\n\
    \  }\n\n  auto ker = lu.kernel();\n  std::cout << ker.size() << \"\\n\" << res.second\
    \ << \"\\n\";\n  for (auto &&v : ker) std::cout << v << \"\\n\";\n}\n\n}  // namespace\
    \ workspace\n\nint main() { workspace::main(); }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/system_of_linear_equations\"\
    \n\n#include \"src/algebra/linear/lu.hpp\"\n#include \"src/algebra/modint.hpp\"\
    \n#include \"src/utils/io/istream.hpp\"\n#include \"src/utils/io/ostream.hpp\"\
    \n\nnamespace workspace {\n\nusing mint = modint<998244353>;\nusing mat = matrix<mint>;\n\
    \nvoid main() {\n  // start here!\n\n  size_t n, m;\n  cin >> n >> m;\n\n  lu_decomposition\
    \ lu = [&] {\n    mat a(n, m);\n    cin >> a;\n    return a;\n  }();\n\n  auto\
    \ res = lu.solve([&] {\n    std::vector<mint> b(n);\n    cin >> b;\n    return\
    \ b;\n  }());\n\n  if (!res.first) {\n    std::cout << \"-1\\n\";\n    return;\n\
    \  }\n\n  auto ker = lu.kernel();\n  std::cout << ker.size() << \"\\n\" << res.second\
    \ << \"\\n\";\n  for (auto &&v : ker) std::cout << v << \"\\n\";\n}\n\n}  // namespace\
    \ workspace\n\nint main() { workspace::main(); }\n"
  dependsOn:
  - src/algebra/linear/lu.hpp
  - src/algebra/linear/matrix.hpp
  - src/algebra/modint.hpp
  - src/number_theory/sqrt_mod.hpp
  - src/number_theory/pow_mod.hpp
  - src/utils/sfinae.hpp
  - src/utils/io/istream.hpp
  - src/utils/io/ostream.hpp
  isVerificationFile: true
  path: test/library-checker/system_of_linear_equations.test.cpp
  requiredBy: []
  timestamp: '2021-07-25 20:09:18+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/library-checker/system_of_linear_equations.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/system_of_linear_equations.test.cpp
- /verify/test/library-checker/system_of_linear_equations.test.cpp.html
title: test/library-checker/system_of_linear_equations.test.cpp
---
