#pragma once

/**
 * @file lu.hpp
 * @brief LU decomposition
 */

#include <numeric>

#include "matrix.hpp"

namespace workspace {

template <class _Matrix> class lu_decomposition : public _Matrix {
 public:
  using value_type = typename _Matrix::value_type;
  using size_type = typename _Matrix::size_type;

  lu_decomposition() = default;
  lu_decomposition(const _Matrix &__x) : _Matrix(__x) { run(); }
  lu_decomposition(_Matrix &&__x) : _Matrix(std::move(__x)) { run(); }

 protected:
  std::vector<size_type> __perm, __pivots;
  bool sgn;

  void run() {
    __perm.resize(_Matrix::rows());
    std::iota(__perm.begin(), __perm.end(), 0);
    sgn = false;
    __pivots.clear();

    for (size_type __c = 0;
         __c != _Matrix::cols() && __pivots.size() != _Matrix::rows(); ++__c) {
      auto __max = (*this)[__pivots.size()][__c];
      auto __pos = __pivots.size();

      if constexpr (std::is_floating_point<
                        value_type>::value) {  // Find the biggest absolute
                                               // value in the column.
        for (size_type __r = __pivots.size() + 1; __r != _Matrix::rows(); ++__r)
          if (std::abs(__max) < std::abs((*this)[__r][__c]))
            __max = (*this)[__pos = __r][__c];
      }

      else if (__max ==
               static_cast<value_type>(
                   0))  // Find the first non-zero element in the column.
        for (size_type __r = __pivots.size() + 1; __r != _Matrix::rows(); ++__r)
          if ((__max = (*this)[__r][__c]) != static_cast<value_type>(0)) {
            __pos = __r;
            break;
          }

      if (__pos != __pivots.size()) {  // Swap 2 rows.
        sgn = !sgn;
        std::swap(__perm[__pos], __perm[__pivots.size()]);
        std::swap((*this)[__pos], (*this)[__pivots.size()]);
      }

      if (__max != static_cast<value_type>(0)) {  // Forward elimination
        for (size_type __r = __pivots.size() + 1; __r != _Matrix::rows();
             ++__r) {
          auto __m = (*this)[__r][__c] / __max;
          (*this)[__r][__c] = 0;
          (*this)[__r][__pivots.size()] = __m;

          for (size_type __i = __c + 1; __i != _Matrix::cols(); ++__i)
            (*this)[__r][__i] -= (*this)[__pivots.size()][__i] * __m;
        }

        __pivots.emplace_back(__c);
      }
    }
  }

 public:
  size_type rank() const { return __pivots.size(); }

  value_type det() const {
    assert(_Matrix::rows() == _Matrix::cols());

    value_type __d = sgn ? -1 : 1;
    for (size_type __i = 0; __i != _Matrix::rows(); ++__i)
      __d *= (*this)[__i][__i];
    return __d;
  }

  _Matrix lower() const;

  _Matrix upper() const;

  _Matrix inverse() const {
    assert(_Matrix::rows() == _Matrix::cols());

    _Matrix __inv;
    // add solve(e_i) to __inv for i=0, ..., rows()
    return __inv;
  }

  // O(dim(ker) * size)
  _Matrix kernel() const {
    _Matrix __ker(_Matrix::cols() - rank(), _Matrix::cols());

    for (size_type __c = 0, __i = 0; __c != _Matrix::cols(); ++__c) {
      if (__i != __pivots.size() && __pivots[__i] == __c) {
        ++__i;
        continue;
      }

      auto &__v = __ker[__c - __i];
      __v[__c] = 1;
      for (size_type __r = 0; __r != __i; ++__r) __v[__r] = -(*this)[__r][__c];

      for (size_type __j = __i; __j--;) {
        auto __x = __v[__j] / (*this)[__j][__pivots[__j]];
        __v[__j] = 0;
        __v[__pivots[__j]] = __x;

        for (size_type __r = 0; __r != __j; ++__r)
          __v[__r] -= (*this)[__r][__pivots[__j]] * __x;
      }
    }

    return __ker;
  }

  template <class _Vec> std::pair<bool, _Vec> solve(const _Vec &__b) const {
    assert(!(__b.size() < _Matrix::rows()));

    // Solution
    _Vec __y(_Matrix::rows()), __x(_Matrix::cols());

    // Backward substitution with L
    for (size_type __c = 0; __c != _Matrix::rows(); ++__c) {
      __y[__c] += __b[__perm[__c]];

      for (size_type __r = __c + 1; __r != _Matrix::rows(); ++__r)
        __y[__r] -= __y[__c] * (*this)[__r][__c];
    }

    // Backward substitution with U
    for (size_type __i = rank(); __i != _Matrix::rows(); ++__i)
      if (__y[__i] != static_cast<value_type>(0))
        return std::make_pair(false, __x);

    for (size_type __i = rank(); __i--;) {
      auto __c = __pivots[__i];

      __x[__c] = __y[__i] / (*this)[__i][__c];

      for (size_type __r = 0; __r != __i; ++__r)
        __y[__r] -= __x[__c] * (*this)[__r][__c];
    }

    return std::make_pair(true, __x);
  }
};

}  // namespace workspace
