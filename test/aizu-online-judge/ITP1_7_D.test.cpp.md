---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: src/algebra/linear/matrix.hpp
    title: Matrix
  - icon: ':question:'
    path: src/utils/io/istream.hpp
    title: Input Stream
  - icon: ':question:'
    path: src/utils/io/ostream.hpp
    title: Output Stream
  - icon: ':question:'
    path: src/utils/sfinae.hpp
    title: SFINAE
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/ITP1_7_D
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/ITP1_7_D
  bundledCode: "#line 1 \"test/aizu-online-judge/ITP1_7_D.test.cpp\"\n#define PROBLEM\
    \ \"https://onlinejudge.u-aizu.ac.jp/problems/ITP1_7_D\"\n\n#line 2 \"src/algebra/linear/matrix.hpp\"\
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
    \  return *this;\n  }\n\n  template <class _Scalar2, size_type _Cols2>\n  constexpr\
    \ auto operator*(const matrix<_Scalar2, _Cols, _Cols2>& __x) const {\n    matrix<_Scalar,\
    \ _Rows, _Cols2> __m;\n\n    auto __w = *__m.__data;\n    for (const auto& __r\
    \ : __data)\n      for (auto __v = *__x.__data, __end = __v + _Cols2; __v != __end;\
    \ ++__w) {\n        auto __i = __v++;\n        for (const auto& __e : __r) *__w\
    \ += __e * *__i, __i += _Cols2;\n      }\n\n    return __m;\n  }\n\n  template\
    \ <class _Matrix>\n  constexpr\n      typename std::enable_if<!std::is_convertible<_Matrix,\
    \ value_type>::value,\n                              matrix<_Scalar>>::type\n\
    \      operator*(const _Matrix& __x) const {\n    assert(_Cols <= __x.rows());\n\
    \n    matrix<_Scalar> __m(_Rows, __x.cols());\n\n    for (size_type __r = 0; __r\
    \ != _Rows; ++__r)\n      for (size_type __i = 0; __i != __x.cols(); ++__i)\n\
    \        for (size_type __c = 0; __c != _Cols; ++__c)\n          __m[__r][__i]\
    \ += __data[__r][__c] * __x[__c][__i];\n\n    return __m;\n  }\n\n  constexpr\
    \ matrix& operator*=(const value_type& __x) {\n    for (auto& __v : __data)\n\
    \      for (auto& __e : __v) __e *= __x;\n\n    return *this;\n  }\n\n  constexpr\
    \ matrix operator*(const value_type& __x) const {\n    return matrix(*this) *=\
    \ __x;\n  }\n\n  constexpr matrix& operator/=(const value_type& __x) {\n    assert(__x\
    \ != value_type(0));\n\n    for (auto& __v : __data)\n      for (auto& __e : __v)\
    \ __e /= __x;\n\n    return *this;\n  }\n\n  constexpr matrix operator/(const\
    \ value_type& __x) const {\n    return matrix(*this) /= __x;\n  }\n\n  template\
    \ <class _Int> constexpr matrix pow(_Int __e) const {\n    static_assert(_Rows\
    \ == _Cols);\n    assert(0 <= __e);\n\n    matrix __m = eye();\n    for (matrix\
    \ __cp = *this; __e; __cp *= __cp, __e >>= 1)\n      if (__e & 1) __m *= __cp;\n\
    \n    return __m;\n  }\n\n  template <class _Os>\n  constexpr friend _Os& operator<<(_Os&\
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
    \ __x) {\n    return operator=(operator*(std::forward<_Matrix>(__x)));\n  }\n\n\
    \  template <class _Matrix>\n  typename std::enable_if<!std::is_convertible<_Matrix,\
    \ value_type>::value,\n                          matrix>::type\n  operator*(const\
    \ _Matrix& __x) const {\n    assert(cols() <= __x.rows());\n\n    matrix __m(rows(),\
    \ __x.cols());\n\n    if constexpr (is_valarray_based<_Matrix>::value)\n     \
    \ for (size_type __r = 0; __r != rows(); ++__r)\n        for (size_type __c =\
    \ 0; __c != cols(); ++__c)\n          __m[__r] += operator[](__r)[__c] * __x[__c];\n\
    \n    else\n      for (size_type __r = 0; __r != rows(); ++__r)\n        for (size_type\
    \ __c = 0; __c != cols(); ++__c)\n          for (size_type __i = 0; __i != __x.cols();\
    \ ++__i)\n            __m[__r][__i] += operator[](__r)[__c] * __x[__c][__i];\n\
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
    \n    return __os;\n  }\n};\n\n}  // namespace workspace\n#line 2 \"src/utils/io/istream.hpp\"\
    \n\n/**\n * @file istream.hpp\n * @brief Input Stream\n */\n\n#include <cxxabi.h>\n\
    \n#line 11 \"src/utils/io/istream.hpp\"\n#include <iostream>\n#include <tuple>\n\
    \n#line 2 \"src/utils/sfinae.hpp\"\n\n/**\n * @file sfinae.hpp\n * @brief SFINAE\n\
    \ */\n\n#include <cstdint>\n#include <iterator>\n#include <type_traits>\n\n#ifndef\
    \ __INT128_DEFINED__\n\n#ifdef __SIZEOF_INT128__\n#define __INT128_DEFINED__ 1\n\
    #else\n#define __INT128_DEFINED__ 0\n#endif\n\n#endif\n\nnamespace std {\n\n#if\
    \ __INT128_DEFINED__\n\ntemplate <> struct make_signed<__uint128_t> { using type\
    \ = __int128_t; };\ntemplate <> struct make_signed<__int128_t> { using type =\
    \ __int128_t; };\n\ntemplate <> struct make_unsigned<__uint128_t> { using type\
    \ = __uint128_t; };\ntemplate <> struct make_unsigned<__int128_t> { using type\
    \ = __uint128_t; };\n\n#endif\n\n}  // namespace std\n\nnamespace workspace {\n\
    \ntemplate <class Tp, class... Args> struct variadic_front { using type = Tp;\
    \ };\n\ntemplate <class... Args> struct variadic_back;\n\ntemplate <class Tp>\
    \ struct variadic_back<Tp> { using type = Tp; };\n\ntemplate <class Tp, class...\
    \ Args> struct variadic_back<Tp, Args...> {\n  using type = typename variadic_back<Args...>::type;\n\
    };\n\ntemplate <class type, template <class> class trait>\nusing enable_if_trait_type\
    \ = typename std::enable_if<trait<type>::value>::type;\n\ntemplate <class Container>\n\
    using element_type = typename std::decay<decltype(\n    *std::begin(std::declval<Container&>()))>::type;\n\
    \ntemplate <class T, class = std::nullptr_t>\nstruct has_begin : std::false_type\
    \ {};\n\ntemplate <class T>\nstruct has_begin<T, decltype(std::begin(std::declval<T>()),\
    \ nullptr)>\n    : std::true_type {};\n\ntemplate <class T, class = int> struct\
    \ mapped_of {\n  using type = element_type<T>;\n};\ntemplate <class T>\nstruct\
    \ mapped_of<T,\n                 typename std::pair<int, typename T::mapped_type>::first_type>\
    \ {\n  using type = typename T::mapped_type;\n};\ntemplate <class T> using mapped_type\
    \ = typename mapped_of<T>::type;\n\ntemplate <class T, class = void> struct is_integral_ext\
    \ : std::false_type {};\ntemplate <class T>\nstruct is_integral_ext<\n    T, typename\
    \ std::enable_if<std::is_integral<T>::value>::type>\n    : std::true_type {};\n\
    \n#if __INT128_DEFINED__\n\ntemplate <> struct is_integral_ext<__int128_t> : std::true_type\
    \ {};\ntemplate <> struct is_integral_ext<__uint128_t> : std::true_type {};\n\n\
    #endif\n\n#if __cplusplus >= 201402\n\ntemplate <class T>\nconstexpr static bool\
    \ is_integral_ext_v = is_integral_ext<T>::value;\n\n#endif\n\ntemplate <typename\
    \ T, typename = void> struct multiplicable_uint {\n  using type = uint_least32_t;\n\
    };\ntemplate <typename T>\nstruct multiplicable_uint<\n    T, typename std::enable_if<(2\
    \ < sizeof(T)) &&\n                               (!__INT128_DEFINED__ || sizeof(T)\
    \ <= 4)>::type> {\n  using type = uint_least64_t;\n};\n\n#if __INT128_DEFINED__\n\
    \ntemplate <typename T>\nstruct multiplicable_uint<T, typename std::enable_if<(4\
    \ < sizeof(T))>::type> {\n  using type = __uint128_t;\n};\n\n#endif\n\ntemplate\
    \ <typename T> struct multiplicable_int {\n  using type =\n      typename std::make_signed<typename\
    \ multiplicable_uint<T>::type>::type;\n};\n\n}  // namespace workspace\n#line\
    \ 15 \"src/utils/io/istream.hpp\"\n\nnamespace workspace {\n\nnamespace internal\
    \ {\n\ntemplate <class Tp, typename = std::nullptr_t> struct istream_helper {\n\
    \  istream_helper(std::istream &is, Tp &x) {\n    if constexpr (has_begin<Tp>::value)\n\
    \      for (auto &&e : x)\n        istream_helper<typename std::decay<decltype(e)>::type>(is,\
    \ e);\n    else\n      static_assert(has_begin<Tp>::value, \"istream unsupported\
    \ type.\");\n  }\n};\n\ntemplate <class Tp>\nstruct istream_helper<\n    Tp,\n\
    \    decltype(std::declval<std::decay<decltype(std::declval<std::istream &>()\
    \ >>\n                                              std::declval<Tp &>())>>(),\n\
    \             nullptr)> {\n  istream_helper(std::istream &is, Tp &x) { is >> x;\
    \ }\n};\n\n#ifdef __SIZEOF_INT128__\n\ntemplate <> struct istream_helper<__uint128_t,\
    \ std::nullptr_t> {\n  istream_helper(std::istream &__is, __uint128_t &__x) {\n\
    \    std::string __s;\n    __is >> __s;\n    bool __neg = false;\n    if (__s.front()\
    \ == '-') __neg = true, __s.erase(__s.begin());\n    __x = 0;\n    for (char __d\
    \ : __s) {\n      __x *= 10;\n      __d -= '0';\n      if (__neg)\n        __x\
    \ -= __d;\n      else\n        __x += __d;\n    }\n  }\n};\n\ntemplate <> struct\
    \ istream_helper<__int128_t, std::nullptr_t> {\n  istream_helper(std::istream\
    \ &__is, __int128_t &__x) {\n    std::string __s;\n    __is >> __s;\n    bool\
    \ __neg = false;\n    if (__s.front() == '-') __neg = true, __s.erase(__s.begin());\n\
    \    __x = 0;\n    for (char __d : __s) {\n      __x *= 10;\n      __d -= '0';\n\
    \      if (__neg)\n        __x -= __d;\n      else\n        __x += __d;\n    }\n\
    \  }\n};\n\n#endif  // INT128\n\ntemplate <class T1, class T2> struct istream_helper<std::pair<T1,\
    \ T2>> {\n  istream_helper(std::istream &is, std::pair<T1, T2> &x) {\n    istream_helper<T1>(is,\
    \ x.first), istream_helper<T2>(is, x.second);\n  }\n};\n\ntemplate <class... Tps>\
    \ struct istream_helper<std::tuple<Tps...>> {\n  istream_helper(std::istream &is,\
    \ std::tuple<Tps...> &x) { iterate(is, x); }\n\n private:\n  template <class Tp,\
    \ size_t N = 0> void iterate(std::istream &is, Tp &x) {\n    if constexpr (N ==\
    \ std::tuple_size<Tp>::value)\n      return;\n    else\n      istream_helper<typename\
    \ std::tuple_element<N, Tp>::type>(is,\n                                     \
    \                          std::get<N>(x)),\n          iterate<Tp, N + 1>(is,\
    \ x);\n  }\n};\n\n}  // namespace internal\n\n/**\n * @brief A wrapper class for\
    \ std::istream.\n */\nclass istream : public std::istream {\n public:\n  /**\n\
    \   * @brief Wrapped operator.\n   */\n  template <typename Tp> istream &operator>>(Tp\
    \ &x) {\n    internal::istream_helper<Tp>(*this, x);\n    if (std::istream::fail())\
    \ {\n      static auto once = atexit([] {\n        std::cerr << \"\\n\\033[43m\\\
    033[30mwarning: failed to read \\'\"\n                  << abi::__cxa_demangle(typeid(Tp).name(),\
    \ 0, 0, 0)\n                  << \"\\'.\\033[0m\\n\\n\";\n      });\n      assert(!once);\n\
    \    }\n    return *this;\n  }\n};\n\ndecltype(auto) cin = static_cast<istream\
    \ &>(std::cin);\n\n}  // namespace workspace\n#line 2 \"src/utils/io/ostream.hpp\"\
    \n\n/**\n * @file ostream.hpp\n * @brief Output Stream\n */\n\n#line 9 \"src/utils/io/ostream.hpp\"\
    \n\nnamespace workspace {\n\ntemplate <class _Os> struct is_ostream {\n  template\
    \ <typename... _Args>\n  static std::true_type __test(std::basic_ostream<_Args...>\
    \ *);\n\n  static std::false_type __test(void *);\n\n  constexpr static bool value\
    \ = decltype(__test(std::declval<_Os *>()))::value;\n};\n\ntemplate <class _Os>\n\
    using ostream_ref =\n    typename std::enable_if<is_ostream<_Os>::value, _Os &>::type;\n\
    \n/**\n * @brief Stream insertion operator for C-style array.\n *\n * @param __os\
    \ Output stream\n * @param __a Array\n * @return Reference to __os.\n */\ntemplate\
    \ <class _Os, class _Tp, size_t _Nm>\ntypename std::enable_if<bool(sizeof(_Tp)\
    \ > 2), ostream_ref<_Os>>::type\noperator<<(_Os &__os, const _Tp (&__a)[_Nm])\
    \ {\n  if constexpr (_Nm) {\n    __os << *__a;\n    for (auto __i = __a + 1, __e\
    \ = __a + _Nm; __i != __e; ++__i)\n      __os << ' ' << *__i;\n  }\n  return __os;\n\
    }\n\n/**\n * @brief Stream insertion operator for std::pair.\n *\n * @param __os\
    \ Output stream\n * @param __p Pair\n * @return Reference to __os.\n */\ntemplate\
    \ <class _Os, class _T1, class _T2>\nostream_ref<_Os> operator<<(_Os &__os, const\
    \ std::pair<_T1, _T2> &__p) {\n  return __os << __p.first << ' ' << __p.second;\n\
    }\n\n/**\n * @brief Stream insertion operator for std::tuple.\n *\n * @param __os\
    \ Output stream\n * @param __t Tuple\n * @return Reference to __os.\n */\ntemplate\
    \ <class _Os, class _Tp, size_t _Nm = 0>\ntypename std::enable_if<bool(std::tuple_size<_Tp>::value\
    \ + 1),\n                        ostream_ref<_Os>>::type\noperator<<(_Os &__os,\
    \ const _Tp &__t) {\n  if constexpr (_Nm != std::tuple_size<_Tp>::value) {\n \
    \   if constexpr (_Nm) __os << ' ';\n    __os << std::get<_Nm>(__t);\n    operator<<<_Os,\
    \ _Tp, _Nm + 1>(__os, __t);\n  }\n  return __os;\n}\n\ntemplate <class _Os, class\
    \ _Container,\n          typename = decltype(std::begin(std::declval<_Container>()))>\n\
    typename std::enable_if<\n    !std::is_same<typename std::decay<_Container>::type,\
    \ std::string>::value &&\n        !std::is_same<typename std::decay<_Container>::type,\
    \ char *>::value,\n    ostream_ref<_Os>>::type\noperator<<(_Os &__os, const _Container\
    \ &__cont) {\n  bool __h = true;\n  for (auto &&__e : __cont) __h ? __h = 0 :\
    \ (__os << ' ', 0), __os << __e;\n  return __os;\n}\n\n#ifdef __SIZEOF_INT128__\n\
    \n/**\n * @brief Stream insertion operator for __int128_t.\n *\n * @param __os\
    \ Output Stream\n * @param __x 128-bit integer\n * @return Reference to __os.\n\
    \ */\ntemplate <class _Os> ostream_ref<_Os> operator<<(_Os &__os, __int128_t __x)\
    \ {\n  if (!__x) return __os << '0';\n  if (__x < 0) __os << '-';\n  char __s[40],\
    \ *__p = __s;\n  while (__x) {\n    auto __d = __x % 10;\n    *__p++ = '0' + (__x\
    \ < 0 ? -__d : __d);\n    __x /= 10;\n  }\n  *__p = 0;\n  for (char *__t = __s;\
    \ __t < --__p; ++__t) *__t ^= *__p ^= *__t ^= *__p;\n  return __os << __s;\n}\n\
    \n/**\n * @brief Stream insertion operator for __uint128_t.\n *\n * @param __os\
    \ Output Stream\n * @param __x 128-bit unsigned integer\n * @return Reference\
    \ to __os.\n */\ntemplate <class _Os> ostream_ref<_Os> operator<<(_Os &__os, __uint128_t\
    \ __x) {\n  if (!__x) return __os << '0';\n  char __s[40], *__p = __s;\n  while\
    \ (__x) *__p++ = '0' + __x % 10, __x /= 10;\n  *__p = 0;\n  for (char *__t = __s;\
    \ __t < --__p; ++__t) *__t ^= *__p ^= *__t ^= *__p;\n  return __os << __s;\n}\n\
    \n#endif\n\n}  // namespace workspace\n#line 6 \"test/aizu-online-judge/ITP1_7_D.test.cpp\"\
    \n\nint main() {\n  using namespace workspace;\n  int n, m, l;\n  cin >> n >>\
    \ m >> l;\n  matrix<long long> a(n, m), b(m, l);\n  cin >> a >> b;\n  std::cout\
    \ << (a *= b);\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/ITP1_7_D\"\n\n\
    #include \"src/algebra/linear/matrix.hpp\"\n#include \"src/utils/io/istream.hpp\"\
    \n#include \"src/utils/io/ostream.hpp\"\n\nint main() {\n  using namespace workspace;\n\
    \  int n, m, l;\n  cin >> n >> m >> l;\n  matrix<long long> a(n, m), b(m, l);\n\
    \  cin >> a >> b;\n  std::cout << (a *= b);\n}\n"
  dependsOn:
  - src/algebra/linear/matrix.hpp
  - src/utils/io/istream.hpp
  - src/utils/sfinae.hpp
  - src/utils/io/ostream.hpp
  isVerificationFile: true
  path: test/aizu-online-judge/ITP1_7_D.test.cpp
  requiredBy: []
  timestamp: '2021-02-22 16:43:34+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/aizu-online-judge/ITP1_7_D.test.cpp
layout: document
redirect_from:
- /verify/test/aizu-online-judge/ITP1_7_D.test.cpp
- /verify/test/aizu-online-judge/ITP1_7_D.test.cpp.html
title: test/aizu-online-judge/ITP1_7_D.test.cpp
---