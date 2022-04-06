---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: src/algebra/berlekamp_massey.hpp
    title: Berlekamp-Massey Algorithm
  - icon: ':heavy_check_mark:'
    path: src/algebra/fft.hpp
    title: Fast Fourier Transform
  - icon: ':heavy_check_mark:'
    path: src/algebra/interpolation.hpp
    title: Polynomial Interpolation
  - icon: ':heavy_check_mark:'
    path: src/algebra/polynomial.hpp
    title: Polynomial
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/library-checker/convolution_mod.test.cpp
    title: test/library-checker/convolution_mod.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/division_of_polynomials.test.cpp
    title: test/library-checker/division_of_polynomials.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/find_linear_recurrence.test.cpp
    title: test/library-checker/find_linear_recurrence.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/multipoint_evaluation.test.cpp
    title: test/library-checker/multipoint_evaluation.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/polynomial_interpolation.test.cpp
    title: test/library-checker/polynomial_interpolation.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/polynomial_taylor_shift.test.cpp
    title: test/library-checker/polynomial_taylor_shift.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Complex Number
    links: []
  bundledCode: "#line 2 \"src/algebra/complex.hpp\"\n\n/**\n * @file complex.hpp\n\
    \ * @brief Complex Number\n */\n\nnamespace workspace {\n\n// Complex number.\n\
    template <class _Tp> class complex {\n  _Tp re, im;\n\n  friend constexpr complex\
    \ conj(const complex &x) noexcept {\n    return {x.re, -x.im};\n  }\n\n  friend\
    \ constexpr _Tp abs(const complex &x) noexcept {\n    return hypot(x.re, x.im);\n\
    \  }\n\n  friend constexpr _Tp arg(const complex &x) noexcept {\n    return atan2(x.re,\
    \ x.im);\n  }\n\n  template <class _Is>\n  friend constexpr _Is &operator>>(_Is\
    \ &__is, complex &x) noexcept {\n    return __is >> x.re >> x.im;\n  }\n\n  template\
    \ <class _Os>\n  friend constexpr _Os &operator<<(_Os &__os, const complex &x)\
    \ noexcept {\n    return __os << x.re << ' ' << x.im;\n  }\n\n public:\n  constexpr\
    \ complex() noexcept : re{}, im{} {}\n  constexpr complex(_Tp _re) noexcept :\
    \ re{_re}, im{} {}\n  constexpr complex(_Tp _re, _Tp _im) noexcept : re{_re},\
    \ im{_im} {}\n\n  constexpr _Tp real() const noexcept { return re; }\n  constexpr\
    \ void real(_Tp _re) noexcept { re = _re; }\n\n  constexpr _Tp imag() const noexcept\
    \ { return im; }\n  constexpr void imag(_Tp _im) noexcept { im = _im; }\n\n  constexpr\
    \ complex operator+() const noexcept { return *this; }\n  constexpr complex operator-()\
    \ const noexcept { return {-re, -im}; }\n\n  constexpr complex &operator+=(const\
    \ complex &x) noexcept {\n    return re += x.re, im += x.im, *this;\n  }\n  constexpr\
    \ complex &operator-=(const complex &x) noexcept {\n    return re -= x.re, im\
    \ -= x.im, *this;\n  }\n  constexpr complex &operator*=(const complex &x) noexcept\
    \ {\n    _Tp _re{re * x.re - im * x.im};\n    return im = im * x.re + x.im * re,\
    \ re = _re, *this;\n  }\n  constexpr complex &operator*=(_Tp x) noexcept {\n \
    \   return re *= x, im *= x, *this;\n  }\n  constexpr complex &operator/=(const\
    \ complex &x) noexcept {\n    return (*this *= conj(x)) /= re * re + im * im;\n\
    \  }\n  constexpr complex &operator/=(_Tp x) noexcept {\n    return re /= x, im\
    \ /= x, *this;\n  }\n\n  constexpr complex operator+(const complex &x) const noexcept\
    \ {\n    return {re + x.re, im + x.im};\n  }\n  constexpr complex operator-(const\
    \ complex &x) const noexcept {\n    return {re - x.re, im - x.im};\n  }\n\n  constexpr\
    \ complex operator*(const complex &x) const noexcept {\n    return complex(*this)\
    \ *= x;\n  }\n\n  constexpr complex operator*(_Tp x) const noexcept { return {re\
    \ * x, im * x}; }\n\n  constexpr complex operator/(const complex &x) const noexcept\
    \ {\n    return complex(*this) /= x;\n  }\n\n  constexpr complex operator/(_Tp\
    \ x) const noexcept { return {re / x, im / x}; }\n};\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file complex.hpp\n * @brief Complex Number\n */\n\
    \nnamespace workspace {\n\n// Complex number.\ntemplate <class _Tp> class complex\
    \ {\n  _Tp re, im;\n\n  friend constexpr complex conj(const complex &x) noexcept\
    \ {\n    return {x.re, -x.im};\n  }\n\n  friend constexpr _Tp abs(const complex\
    \ &x) noexcept {\n    return hypot(x.re, x.im);\n  }\n\n  friend constexpr _Tp\
    \ arg(const complex &x) noexcept {\n    return atan2(x.re, x.im);\n  }\n\n  template\
    \ <class _Is>\n  friend constexpr _Is &operator>>(_Is &__is, complex &x) noexcept\
    \ {\n    return __is >> x.re >> x.im;\n  }\n\n  template <class _Os>\n  friend\
    \ constexpr _Os &operator<<(_Os &__os, const complex &x) noexcept {\n    return\
    \ __os << x.re << ' ' << x.im;\n  }\n\n public:\n  constexpr complex() noexcept\
    \ : re{}, im{} {}\n  constexpr complex(_Tp _re) noexcept : re{_re}, im{} {}\n\
    \  constexpr complex(_Tp _re, _Tp _im) noexcept : re{_re}, im{_im} {}\n\n  constexpr\
    \ _Tp real() const noexcept { return re; }\n  constexpr void real(_Tp _re) noexcept\
    \ { re = _re; }\n\n  constexpr _Tp imag() const noexcept { return im; }\n  constexpr\
    \ void imag(_Tp _im) noexcept { im = _im; }\n\n  constexpr complex operator+()\
    \ const noexcept { return *this; }\n  constexpr complex operator-() const noexcept\
    \ { return {-re, -im}; }\n\n  constexpr complex &operator+=(const complex &x)\
    \ noexcept {\n    return re += x.re, im += x.im, *this;\n  }\n  constexpr complex\
    \ &operator-=(const complex &x) noexcept {\n    return re -= x.re, im -= x.im,\
    \ *this;\n  }\n  constexpr complex &operator*=(const complex &x) noexcept {\n\
    \    _Tp _re{re * x.re - im * x.im};\n    return im = im * x.re + x.im * re, re\
    \ = _re, *this;\n  }\n  constexpr complex &operator*=(_Tp x) noexcept {\n    return\
    \ re *= x, im *= x, *this;\n  }\n  constexpr complex &operator/=(const complex\
    \ &x) noexcept {\n    return (*this *= conj(x)) /= re * re + im * im;\n  }\n \
    \ constexpr complex &operator/=(_Tp x) noexcept {\n    return re /= x, im /= x,\
    \ *this;\n  }\n\n  constexpr complex operator+(const complex &x) const noexcept\
    \ {\n    return {re + x.re, im + x.im};\n  }\n  constexpr complex operator-(const\
    \ complex &x) const noexcept {\n    return {re - x.re, im - x.im};\n  }\n\n  constexpr\
    \ complex operator*(const complex &x) const noexcept {\n    return complex(*this)\
    \ *= x;\n  }\n\n  constexpr complex operator*(_Tp x) const noexcept { return {re\
    \ * x, im * x}; }\n\n  constexpr complex operator/(const complex &x) const noexcept\
    \ {\n    return complex(*this) /= x;\n  }\n\n  constexpr complex operator/(_Tp\
    \ x) const noexcept { return {re / x, im / x}; }\n};\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/algebra/complex.hpp
  requiredBy:
  - src/algebra/interpolation.hpp
  - src/algebra/polynomial.hpp
  - src/algebra/fft.hpp
  - src/algebra/berlekamp_massey.hpp
  timestamp: '2022-04-06 14:50:38+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/division_of_polynomials.test.cpp
  - test/library-checker/find_linear_recurrence.test.cpp
  - test/library-checker/convolution_mod.test.cpp
  - test/library-checker/polynomial_taylor_shift.test.cpp
  - test/library-checker/multipoint_evaluation.test.cpp
  - test/library-checker/polynomial_interpolation.test.cpp
documentation_of: src/algebra/complex.hpp
layout: document
redirect_from:
- /library/src/algebra/complex.hpp
- /library/src/algebra/complex.hpp.html
title: Complex Number
---
