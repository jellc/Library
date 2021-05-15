#pragma once

/**
 * @file ntt.hpp
 * @brief Number Theoretic Transform
 * @date 2021-02-20
 *
 *
 */

#include "src/number_theory/ext_gcd.hpp"
#include "src/number_theory/primitive_root.hpp"

namespace workspace {

namespace ntt_impl {

/**
 * @see
 * https://github.com/atcoder/ac-library/blob/master/atcoder/convolution.hpp
 */

template <class _Tp> struct __coef {
  _Tp sum_e[30];  // sum_e[i] = ies[0] * ... * ies[i - 1] * es[i]

  constexpr __coef() : sum_e{} {
    if (_Tp::mod < 2) return;

    int cnt2 = __builtin_ctz(_Tp::mod - 1);
    _Tp e = 1;
    {
      auto p = (_Tp::mod - 1) >> cnt2;
      _Tp w = primitive_root(_Tp::mod);
      while (p) {
        if (p & 1) e *= w;
        p >>= 1;
        w *= w;
      }
    }

    _Tp ie = ext_gcd(decltype(_Tp::mod)(e), _Tp::mod).first;
    _Tp es[30] = {}, ies[30] = {};  // es[i]^(2^(2+i)) == 1
    for (int i = cnt2; i >= 2; i--) {
      // e^(2^i) == 1
      es[i - 2] = e;
      ies[i - 2] = ie;
      e *= e;
      ie *= ie;
    }

    _Tp now = 1;
    for (int i = 0; i <= cnt2 - 2; i++) {
      sum_e[i] = es[i] * now;
      now *= ies[i];
    }
  }
};

template <class _Tp> struct __icoef {
  _Tp sum_ie[30];  // sum_e[i] = ies[0] * ... * ies[i - 1] * es[i]

  constexpr __icoef() : sum_ie{} {
    if (_Tp::mod < 2) return;

    int cnt2 = __builtin_ctz(_Tp::mod - 1);
    _Tp e = 1;
    {
      auto p = (_Tp::mod - 1) >> cnt2;
      _Tp w = primitive_root(_Tp::mod);
      while (p) {
        if (p & 1) e *= w;
        p >>= 1;
        w *= w;
      }
    }

    _Tp ie = ext_gcd(decltype(_Tp::mod)(e), _Tp::mod).first;
    _Tp es[30] = {}, ies[30] = {};  // es[i]^(2^(2+i)) == 1
    for (int i = cnt2; i >= 2; i--) {
      // e^(2^i) == 1
      es[i - 2] = e;
      ies[i - 2] = ie;
      e *= e;
      ie *= ie;
    }

    _Tp now = 1;
    for (int i = 0; i <= cnt2 - 2; i++) {
      sum_ie[i] = ies[i] * now;
      now *= es[i];
    }
  }
};

template <class _Tp> struct __ipow2 {
  _Tp __ip2[30];
  constexpr __ipow2() : __ip2{1, (1 + _Tp::mod) / 2} {
    for (size_t __i = 1; __i + 1 != std::size(__ip2); ++__i)
      __ip2[__i + 1] = __ip2[__i] * __ip2[1];
  }
};

template <class _FIter>
constexpr void ntt(_FIter __first, _FIter __last) noexcept {
  using value_type = typename std::decay<decltype(*__first)>::type;
  constexpr __coef<value_type> _;

  auto __h = __builtin_ctz(std::distance(__first, __last));

  for (ptrdiff_t __p = 1 << __h; __p >>= 1;) {
    value_type now = -1;
    auto __l = __first;

    for (size_t __s = 1 << __h; __l != __last;
         now *= _.sum_e[__builtin_ctz(--__s)]) {
      auto __r = __l + __p;

      for (auto __mid = __r; __l != __mid; ++__l, ++__r) {
        auto __tmp = *__l;
        *__l -= *__r *= now;
        *__r += __tmp;
      }

      __l = __r;
    }
  }
}

template <class _A> constexpr void ntt(_A &a) noexcept {
  ntt(std::begin(a), std::end(a));
}

template <class _FIter>
constexpr void intt(_FIter __first, _FIter __last) noexcept {
  using value_type = typename std::decay<decltype(*__first)>::type;
  constexpr __icoef<value_type> _;

  auto __h = __builtin_ctz(std::distance(__first, __last));

  for (ptrdiff_t __p = 1; __p >> __h ^ 1; __p <<= 1) {
    value_type inow = 1;
    auto __l = __first;

    for (size_t __s = 1 << __h; __l != __last;
         inow *= _.sum_ie[__builtin_ctz(--__s)]) {
      auto __r = __l + __p;

      for (auto __mid = __r; __l != __mid; ++__l, ++__r) {
        auto __tmp = (*__l - *__r) * inow;
        *__l += *__r;
        *__r = __tmp;
      }

      __l = __r;
    }
  }

  constexpr __ipow2<value_type> __;
  while (__first != __last) *--__last *= __.__ip2[__h];
}  // namespace ntt_impl

template <class _A> constexpr void intt(_A &a) noexcept {
  intt(std::begin(a), std::end(a));
}

}  // namespace ntt_impl

using ntt_impl::intt;
using ntt_impl::ntt;

}  // namespace workspace
