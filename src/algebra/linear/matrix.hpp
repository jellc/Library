#pragma once

/**
 * @file matrix.hpp
 * @brief Matrix
 * @date 2021-02-15
 *
 *
 */

#include <cassert>
#include <valarray>

namespace workspace {

/**
 * @brief Fixed size matrix.
 *
 * @tparam _Scalar
 * @tparam _Rows Number of rows
 * @tparam _Cols Number of columns
 */
template <class _Scalar, std::size_t _Rows = 0, std::size_t _Cols = _Rows>
class matrix {
 public:
  _Scalar __data[_Rows][_Cols] = {};

  using value_type = _Scalar;
  using size_type = std::size_t;

  constexpr static matrix eye() {
    static_assert(_Rows == _Cols);

    matrix __e;
    for (size_type __d = 0; __d != _Rows; ++__d) __e.__data[__d][__d] = 1;
    return __e;
  }

  constexpr operator decltype((__data))() { return __data; }
  constexpr operator decltype(std::declval<const matrix>().__data)
      const&() const {
    return __data;
  }

  constexpr auto begin() { return __data; }
  constexpr auto begin() const { return __data; }

  constexpr auto end() { return __data + _Rows; }
  constexpr auto end() const { return __data + _Rows; }

  constexpr size_type rows() const { return _Rows; }

  constexpr size_type cols() const { return _Cols; }

  constexpr auto transpose() const {
    matrix<_Scalar, _Cols, _Rows> __t;

    for (size_type __r = 0; __r != _Rows; ++__r)
      for (size_type __c = 0; __c != _Cols; ++__c)
        __t.__data[__c][__r] = __data[__r][__c];

    return __t;
  }

  constexpr matrix operator+() const { return *this; }

  constexpr matrix operator-() const {
    matrix __cp = *this;

    for (auto& __v : __cp.__data)
      for (auto& __e : __v) __e = -__e;

    return __cp;
  }

  template <class _Matrix> constexpr matrix& operator+=(const _Matrix& __x) {
    auto __m = std::min(_Rows, __x.rows());
    auto __n = std::min(_Cols, __x.cols());

    for (size_type __r = 0; __r != __m; ++__r)
      for (size_type __c = 0; __c != __n; ++__c)
        __data[__r][__c] += __x[__r][__c];

    return *this;
  }

  template <class _Matrix>
  constexpr matrix operator+(const _Matrix& __x) const {
    return matrix(*this) += __x;
  }

  template <class _Matrix> constexpr matrix& operator-=(const _Matrix& __x) {
    auto __m = std::min(_Rows, __x.rows());
    auto __n = std::min(_Cols, __x.cols());

    for (size_type __r = 0; __r != __m; ++__r)
      for (size_type __c = 0; __c != __n; ++__c)
        __data[__r][__c] -= __x[__r][__c];

    return *this;
  }

  template <class _Matrix>
  constexpr matrix operator-(const _Matrix& __x) const {
    return matrix(*this) -= __x;
  }

  template <class _Scalar2>
  constexpr matrix& operator*=(const matrix<_Scalar2, _Cols, _Cols>& __x) {
    if (this == &__x) return operator=(operator*(__x));

    for (auto& __r : __data) {
      _Scalar __tmp[_Cols] = {};

      auto __v = *__x.__data;
      for (auto& __w : __tmp) {
        auto __i = __v++;
        for (const auto& __e : __r) __w += __e * *__i, __i += _Cols;
      }

      auto __w = __tmp;
      for (auto& __e : __r) __e = std::move(*__w++);
    }

    return *this;
  }

  template <class _Scalar2, size_type _Rows2, size_type _Cols2>
  constexpr auto operator*(const matrix<_Scalar2, _Rows2, _Cols2>& __x) const {
    matrix<typename std::common_type<_Scalar, _Scalar2>::type, _Rows, _Cols2>
        __m;

    auto __w = *__m.__data;
    for (const auto& __r : __data)
      for (auto __v = *__x.__data, __v_end = __v + _Cols2; __v != __v_end;
           ++__w) {
        auto __i = __v++;
        for (auto __e = __r; __e != __r + std::min(_Cols, _Rows2); ++__e)
          *__w += *__e * *__i, __i += _Cols2;
      }

    return __m;
  }

  template <class _Matrix>
  constexpr
      typename std::enable_if<!std::is_convertible<_Matrix, value_type>::value,
                              matrix<_Scalar>>::type
      operator*(const _Matrix& __x) const {
    matrix<_Scalar> __m(_Rows, __x.cols());

    for (size_type __r = 0; __r != _Rows; ++__r)
      for (size_type __i = 0; __i != __x.cols(); ++__i)
        for (size_type __c = 0; __c != std::min(_Cols, __x.rows()); ++__c)
          __m[__r][__i] += __data[__r][__c] * __x[__c][__i];

    return __m;
  }

  constexpr matrix& operator*=(const value_type& __x) {
    for (auto& __v : __data)
      for (auto& __e : __v) __e *= __x;

    return *this;
  }

  constexpr matrix operator*(const value_type& __x) const {
    return matrix(*this) *= __x;
  }

  constexpr matrix& operator/=(const value_type& __x) {
    assert(__x != value_type(0));

    for (auto& __v : __data)
      for (auto& __e : __v) __e /= __x;

    return *this;
  }

  constexpr matrix operator/(const value_type& __x) const {
    return matrix(*this) /= __x;
  }

  template <class _Int> constexpr matrix pow(_Int __e) const {
    assert(0 <= __e);

    matrix __m = eye();
    for (matrix __cp = *this; __e; __cp *= __cp, __e >>= 1)
      if (__e & 1) __m *= __cp;

    return __m;
  }

  template <class _Os>
  constexpr friend _Os& operator<<(_Os& __os, const matrix& __x) {
    for (auto __i = __x.begin(); __i != __x.end(); ++__i, __os << '\n')
      for (size_type __c = 0; __c != _Cols; ++__c)
        __c ? void(__os << ' ') : (void)0, __os << *(*__i + __c);

    return __os;
  }
};  // namespace workspace

/**
 * @brief Dynamic matrix.
 *
 * @tparam _Scalar
 * @tparam _Rows Number of rows
 * @tparam _Cols Number of columns
 */
template <class _Scalar>
class matrix<_Scalar, 0, 0> : public std::valarray<std::valarray<_Scalar>> {
  using base = std::valarray<std::valarray<_Scalar>>;
  using row_type = typename base::value_type;

 public:
  using value_type = _Scalar;
  using size_type = std::size_t;

  using base::operator[];

  static matrix eye(size_type __n) {
    matrix __e(__n, __n);
    for (size_type __d = 0; __d != __n; ++__d) __e[__d][__d] = 1;
    return __e;
  }

  matrix() = default;

  matrix(size_type __n) : matrix(__n, __n) {}

  matrix(size_type __m, size_type __n) : base(row_type(__n), __m) {}

  template <class _Tp, typename = typename std::enable_if<
                           std::is_constructible<base, _Tp>::value &&
                           !std::is_constructible<size_type, _Tp>::value>::type>
  matrix(_Tp&& __x) : base(__x) {}

  matrix(std::initializer_list<row_type> __x) : base(__x) {}

  size_type rows() const { return base::size(); }

  size_type cols() const { return rows() ? operator[](0).size() : 0; }

  matrix transpose() const {
    matrix __t(cols(), rows());

    for (size_type __r = 0; __r != rows(); ++__r)
      for (size_type __c = 0; __c != cols(); ++__c)
        __t[__c][__r] = operator[](__r)[__c];

    return __t;
  }

  void resize(size_type __m, size_type __n) {
    matrix __t(__m, __n);

    if (rows() < __m) __m = rows();
    if (cols() < __n) __n = cols();

    for (size_type __r = 0; __r != __m; ++__r)
      for (size_type __c = 0; __c != __n; ++__c)
        __t[__r][__c] = std::move(operator[](__r)[__c]);

    base::swap(__t);
  }

  // binary operators {{

  template <class _Matrix, typename = void>
  struct is_valarray_based : std::false_type {};

  template <class _Matrix>
  struct is_valarray_based<
      _Matrix,
      typename std::enable_if<std::is_same<
          row_type, typename std::decay<decltype(
                        std::declval<_Matrix>()[0])>::type>::value>::type>
      : std::true_type {};

  template <class _Matrix>
  typename std::enable_if<!std::is_convertible<_Matrix, value_type>::value,
                          matrix&>::type
  operator*=(_Matrix&& __x) {
    return *this = operator*(std::forward<_Matrix>(__x));
  }

  template <class _Matrix>
  typename std::enable_if<!std::is_convertible<_Matrix, value_type>::value,
                          matrix>::type
  operator*(const _Matrix& __x) const {
    matrix __m(rows(), __x.cols());

    if constexpr (is_valarray_based<_Matrix>::value)
      for (size_type __r = 0; __r != rows(); ++__r)
        for (size_type __c = 0; __c != std::min(cols(), __x.rows()); ++__c)
          __m[__r] += operator[](__r)[__c] * __x[__c];

    else
      for (size_type __r = 0; __r != rows(); ++__r)
        for (size_type __i = 0; __i != __x.cols(); ++__i)
          for (size_type __c = 0; __c != std::min(cols(), __x.rows()); ++__c)
            __m[__r][__i] += operator[](__r)[__c] * __x[__c][__i];

    return __m;
  }

  matrix& operator*=(const value_type& __x) {
    for (size_type __r = 0; __r != rows(); ++__r)
      operator[](__r).operator*=(__x);

    return *this;
  }

  matrix operator*(const value_type& __x) const { return matrix(*this) *= __x; }

  friend matrix operator*(const value_type& __x, matrix __i) {
    for (size_type __r = 0; __r != __i.rows(); ++__r)
      __i.operator[](__r) = __x * __i.operator[](__r);

    return __i;
  }

  matrix& operator/=(const value_type& __x) {
    assert(__x != value_type(0));

    for (size_type __r = 0; __r != rows(); ++__r)
      operator[](__r).operator/=(__x);

    return *this;
  }

  matrix operator/(const value_type& __x) const { return matrix(*this) /= __x; }

  // }} binary operators

  template <class _Int> matrix pow(_Int __e) const {
    assert(0 <= __e);

    matrix __m = eye(rows());
    for (matrix __cp = *this; __e; __cp *= __cp, __e >>= 1)
      if (__e & 1) __m *= __cp;

    return __m;
  }

  // template <class _Is> friend _Is& operator>>(_Is& __is, matrix& __x) {
  //   for (size_type __r = 0; __r != __x.rows(); ++__r)
  //     for (size_type __c = 0; __c != __x.cols(); ++__c)
  //       __is >> __x.operator[](__r).operator[](__c);

  //   return __is;
  // }

  template <class _Os> friend _Os& operator<<(_Os& __os, const matrix& __x) {
    for (size_type __r = 0; __r != __x.rows(); ++__r, __os << '\n')
      for (size_type __c = 0; __c != __x.cols(); ++__c)
        __c ? void(__os << ' ') : (void)0,
            __os << __x.operator[](__r).operator[](__c);

    return __os;
  }
};

}  // namespace workspace
