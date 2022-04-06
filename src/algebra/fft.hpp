#pragma once

/**
 * @file fft.hpp
 * @brief Fast Fourier Transform
 */

#include <vector>

#include "complex.hpp"
#include "lib/cxx17"
#include "src/number_theory/ext_gcd.hpp"
#include "src/number_theory/primitive_root.hpp"
#include "src/utils/sfinae.hpp"

namespace workspace {

namespace _fft_impl {

template <class _Tp, bool = std::is_floating_point<_Tp>::value, class = void>
struct to_float {
  using type = double;
};

template <class _Tp> struct to_float<_Tp, true> { using type = _Tp; };

// template <class _Tp>
// struct to_float<_Tp, false, std::enable_if_t<sizeof(_Tp) <= sizeof(float)>> {
//   using type = float;
// };

template <class _Tp>
struct to_float<_Tp, false, std::enable_if_t<(sizeof(_Tp) > sizeof(double))>> {
  using type = long double;
};

// Assume ntt-friendly mod.
template <class _Tp> struct field {
  using type = std::conditional_t<has_mod<_Tp>::value, _Tp,
                                  complex<typename to_float<_Tp>::type>>;
};

template <class _Tp> struct field<complex<_Tp>> : field<_Tp> {};

// Modular
template <class _Tp, int _Nm = 29, bool = has_mod<_Tp>::value> struct coef {
  _Tp s[_Nm], is[_Nm], ip2[_Nm];

  _CXX14_CONSTEXPR coef() : s{}, is{}, ip2{1, (1 + _Tp::mod) / 2} {
    if (_Tp::mod < 2) return;

    int cnt2 = std::min(__builtin_ctz(_Tp::mod - 1), _Nm + 1);

    _Tp e = 1;
    _Tp w = primitive_root(_Tp::mod);
    for (auto p = (_Tp::mod - 1) >> cnt2; p; p >>= 1, w *= w)
      if (p & 1) e *= w;

    _Tp ie = ext_gcd(decltype(_Tp::mod)(e), _Tp::mod).first;
    _Tp es[_Nm]{}, ies[_Nm]{};

    for (int i = cnt2; i >= 2; i--) {
      es[i - 2] = e, e *= e;
      ies[i - 2] = ie, ie *= ie;
    }

    e = ie = 1;
    for (int i = 0; i < cnt2 - 1; i++) {
      s[i] = es[i] * e, e *= ies[i];
      is[i] = ies[i] * ie, ie *= es[i];
    }

    for (int i = 1; i < _Nm - 1; ++i) ip2[i + 1] = ip2[i] * ip2[1];
  }
};

// Complex
template <class _Tp, int _Nm> struct coef<_Tp, _Nm, false> {
  _Tp s[_Nm], is[_Nm], ip2[_Nm];

  static_assert(_Nm < 30);

  _CXX14_CONSTEXPR static _Tp es[29] = {
      {0, 1},
      {0.70710678118654752438189403651, 0.70710678118654752443610414514},
      {0.92387953251128675610142140795, 0.38268343236508977172325753068},
      {0.98078528040323044911909938781, 0.19509032201612826785692544201},
      {0.99518472667219688623102546998, 0.09801714032956060199569840382},
      {0.99879545620517239270077028412, 0.04906767432741801425693899119},
      {0.99969881869620422009748220149, 0.02454122852291228803212346128},
      {0.99992470183914454093764001552, 0.01227153828571992607945510345},
      {0.99998117528260114264494415325, 0.00613588464915447535972750246},
      {0.99999529380957617150137498041, 0.00306795676296597627029751672},
      {0.99999882345170190993313003025, 0.00153398018628476561237225788},
      {0.99999970586288221914474799723, 0.00076699031874270452695124765},
      {0.99999992646571785113833452651, 0.00038349518757139558906815188},
      {0.99999998161642929381167504976, 0.00019174759731070330743679009},
      {0.99999999540410731290905263501, 0.00009587379909597734587360460},
      {0.99999999885102682753608427379, 0.00004793689960306688454884772},
      {0.99999999971275670682981095982, 0.00002396844980841821872882467},
      {0.99999999992818917670745273995, 0.00001198422490506970642183282},
      {0.99999999998204729416331065783, 0.00000599211245264242784278378},
      {0.99999999999551182356793271877, 0.00000299605622633466075058210},
      {0.99999999999887795586487812538, 0.00000149802811316901122883643},
      {0.99999999999971948897977205850, 0.00000074901405658471572113723},
      {0.99999999999992987223139048746, 0.00000037450702829238412391495},
      {0.99999999999998246807140014902, 0.00000018725351414619534486931},
      {0.99999999999999561700429751010, 0.00000009362675707309808280024},
      {0.99999999999999890425107437752, 0.00000004681337853654909269501},
      {0.99999999999999972607632112153, 0.00000002340668926827455275977},
      {0.99999999999999993153263280754, 0.00000001170334463413727718121},
      {0.99999999999999998286960567472, 0.00000000585167231706863869077}};

  _CXX14_CONSTEXPR coef() : s{}, is{}, ip2{1, .5} {
    _Tp ies[_Nm];
    for (int i = 0; i < _Nm; ++i) ies[i] = _Tp(1) / es[i];

    _Tp e = 1, ie = 1;
    for (int i = 0; i < _Nm; i++) {
      s[i] = es[i] * e, e *= ies[i];
      is[i] = ies[i] * ie, ie *= es[i];
    }

    for (int i = 1; i < _Nm - 1; ++i) ip2[i + 1] = ip2[i] * ip2[1];
  }
};

}  // namespace _fft_impl

template <bool _Inverse = false, class _Iterator>
void fft(_Iterator __first, _Iterator __last) noexcept {
  using value_type = typename std::iterator_traits<_Iterator>::value_type;
  using difference_type =
      typename std::iterator_traits<_Iterator>::difference_type;

  _CXX14_CONSTEXPR _fft_impl::coef<value_type> c;
  auto __h = __builtin_ctz(std::distance(__first, __last));

  if _CXX17_CONSTEXPR (_Inverse) {
    for (difference_type __p = 1; __p >> __h ^ 1; __p <<= 1) {
      value_type __iw = 1;
      auto __l = __first;

      for (auto __i = 1 << __h; __l != __last;
           __iw *= c.is[__builtin_ctz(--__i)]) {
        auto __r = std::next(__l, __p);

        for (auto __mid = __r; __l != __mid; ++__l, ++__r) {
          auto __tmp = (*__l - *__r) * __iw;
          *__l += *__r;
          *__r = __tmp;
        }

        __l = __r;
      }
    }

    while (__first != __last) *--__last *= c.ip2[__h];
  }

  else {
    for (difference_type __p = 1 << __h; __p >>= 1;) {
      value_type __w = -1;
      auto __l = __first;

      for (auto __i = 1 << __h; __l != __last;
           __w *= c.s[__builtin_ctz(--__i)]) {
        auto __r = std::next(__l, __p);

        for (auto __mid = __r; __l != __mid; ++__l, ++__r) {
          auto __tmp = *__l;
          *__l -= *__r *= __w;
          *__r += __tmp;
        }

        __l = __r;
      }
    }
  }
}

template <class _Iterator>
void fft(_Iterator __first, std::size_t __n) noexcept {
  fft(__first, std::next(__first, __n));
}

template <class _Iterator>
void ifft(_Iterator __first, _Iterator __last) noexcept {
  fft<true>(__first, __last);
}

template <class _Iterator>
void ifft(_Iterator __first, std::size_t __n) noexcept {
  ifft(__first, std::next(__first, __n));
}

template <size_t _Nm, size_t _Dm, class _Container, class _Index>
decltype(auto) access(_Container &__a, const _Index &__i) {
  if _CXX17_CONSTEXPR (_Nm != _Dm)
    return access<_Nm + 1, _Dm>(__a[__i[_Nm]], __i);
  else
    return __a;
}

template <bool _Inverse, size_t _Dm, class _Container, class _Tp, class _Index>
void dive(_Container &__a, const _Tp &__t, _Index &__i) {
  if _CXX17_CONSTEXPR (has_size<_Tp>::value) {
    for (__i.emplace_back(0); __i.back() != std::size(__t); ++__i.back())
      dive<_Inverse, _Dm + 1>(__a, __t[__i.back()], __i);
    __i.pop_back();
  }

  else {
    static std::vector<_Tp> __work;
    // Resize to a power of 2.

    size_t __len = 1 << (31 - __builtin_clz(std::size(__a)));
    if (__work.size() < __len) __work.resize(__len);

    for (size_t __k = 0; __k != __len; ++__k)
      __work[__k] = std::move(access<0, _Dm>(__a[__k], __i));

    fft<_Inverse>(__work.data(), __work.data() + __len);

    for (size_t __k = 0; __k != __len; ++__k)
      access<0, _Dm>(__a[__k], __i) = std::move(__work[__k]);
  }
}

template <bool _Inverse, class _Container> void fft(_Container &__a) {
  if _CXX17_CONSTEXPR (has_size<_Container>::value) {
    if _CXX17_CONSTEXPR (has_resize<_Container>::value)
      // Resize to a power of 2.
      __a.resize(1 << (32 - __builtin_clz(__a.size() - 1)));

    std::vector<size_t> __i;
    dive<_Inverse, 0>(__a, __a[0], __i);

    for (size_t __k = 0; __k != std::size(__a); ++__k) fft<_Inverse>(__a[__k]);
  }
}

template <class _Container> auto conv_resize(_Container &__a, _Container &__b) {
  std::array<size_t, get_dimension<_Container>::value> __s;
  rec(__a, __s);
  rec(__b, __s);
  return __s;
}

template <size_t _Nm, class _Container, class _Size>
void rec(const _Container &__a, _Size &__s) {
  if _CXX17_CONSTEXPR (_Nm != __s.size()) {
    __s[_Nm] = std::max(__s[_Nm], std::size(__a));
    for (auto &__x : __a) rec<_Nm + 1>(__x, __s);
  }
}

}  // namespace workspace
