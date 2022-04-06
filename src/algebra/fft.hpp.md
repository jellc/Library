---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Fast Fourier Transform
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: src\\utils\\sfinae.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n\n/**\n * @file fft.hpp\n * @brief Fast Fourier Transform\n\
    \ */\n\n#include <vector>\n\n#include \"complex.hpp\"\n#include \"lib/cxx17\"\n\
    #include \"src/number_theory/ext_gcd.hpp\"\n#include \"src/number_theory/primitive_root.hpp\"\
    \n#include \"src\\utils\\sfinae.hpp\"\n\nnamespace workspace {\n\nnamespace _fft_impl\
    \ {\n\ntemplate <class _Tp, bool = std::is_floating_point<_Tp>::value, class =\
    \ void>\nstruct to_float {\n  using type = double;\n};\n\ntemplate <class _Tp>\
    \ struct to_float<_Tp, true> { using type = _Tp; };\n\n// template <class _Tp>\n\
    // struct to_float<_Tp, false, std::enable_if_t<sizeof(_Tp) <= sizeof(float)>>\
    \ {\n//   using type = float;\n// };\n\ntemplate <class _Tp>\nstruct to_float<_Tp,\
    \ false, std::enable_if_t<(sizeof(_Tp) > sizeof(double))>> {\n  using type = long\
    \ double;\n};\n\n// Assume ntt-friendly mod.\ntemplate <class _Tp> struct field\
    \ {\n  using type = std::conditional_t<has_mod<_Tp>::value, _Tp,\n           \
    \                       complex<typename to_float<_Tp>::type>>;\n};\n\ntemplate\
    \ <class _Tp> struct field<complex<_Tp>> : field<_Tp> {};\n\n// Modular\ntemplate\
    \ <class _Tp, int _Nm = 29, bool = has_mod<_Tp>::value> struct coef {\n  _Tp s[_Nm],\
    \ is[_Nm], ip2[_Nm];\n\n  _CXX14_CONSTEXPR coef() : s{}, is{}, ip2{1, (1 + _Tp::mod)\
    \ / 2} {\n    if (_Tp::mod < 2) return;\n\n    int cnt2 = std::min(__builtin_ctz(_Tp::mod\
    \ - 1), _Nm + 1);\n\n    _Tp e = 1;\n    _Tp w = primitive_root(_Tp::mod);\n \
    \   for (auto p = (_Tp::mod - 1) >> cnt2; p; p >>= 1, w *= w)\n      if (p & 1)\
    \ e *= w;\n\n    _Tp ie = ext_gcd(decltype(_Tp::mod)(e), _Tp::mod).first;\n  \
    \  _Tp es[_Nm]{}, ies[_Nm]{};\n\n    for (int i = cnt2; i >= 2; i--) {\n     \
    \ es[i - 2] = e, e *= e;\n      ies[i - 2] = ie, ie *= ie;\n    }\n\n    e = ie\
    \ = 1;\n    for (int i = 0; i < cnt2 - 1; i++) {\n      s[i] = es[i] * e, e *=\
    \ ies[i];\n      is[i] = ies[i] * ie, ie *= es[i];\n    }\n\n    for (int i =\
    \ 1; i < _Nm - 1; ++i) ip2[i + 1] = ip2[i] * ip2[1];\n  }\n};\n\n// Complex\n\
    template <class _Tp, int _Nm> struct coef<_Tp, _Nm, false> {\n  _Tp s[_Nm], is[_Nm],\
    \ ip2[_Nm];\n\n  static_assert(_Nm < 30);\n\n  _CXX14_CONSTEXPR static _Tp es[29]\
    \ = {\n      {0, 1},\n      {0.70710678118654752438189403651, 0.70710678118654752443610414514},\n\
    \      {0.92387953251128675610142140795, 0.38268343236508977172325753068},\n \
    \     {0.98078528040323044911909938781, 0.19509032201612826785692544201},\n  \
    \    {0.99518472667219688623102546998, 0.09801714032956060199569840382},\n   \
    \   {0.99879545620517239270077028412, 0.04906767432741801425693899119},\n    \
    \  {0.99969881869620422009748220149, 0.02454122852291228803212346128},\n     \
    \ {0.99992470183914454093764001552, 0.01227153828571992607945510345},\n      {0.99998117528260114264494415325,\
    \ 0.00613588464915447535972750246},\n      {0.99999529380957617150137498041, 0.00306795676296597627029751672},\n\
    \      {0.99999882345170190993313003025, 0.00153398018628476561237225788},\n \
    \     {0.99999970586288221914474799723, 0.00076699031874270452695124765},\n  \
    \    {0.99999992646571785113833452651, 0.00038349518757139558906815188},\n   \
    \   {0.99999998161642929381167504976, 0.00019174759731070330743679009},\n    \
    \  {0.99999999540410731290905263501, 0.00009587379909597734587360460},\n     \
    \ {0.99999999885102682753608427379, 0.00004793689960306688454884772},\n      {0.99999999971275670682981095982,\
    \ 0.00002396844980841821872882467},\n      {0.99999999992818917670745273995, 0.00001198422490506970642183282},\n\
    \      {0.99999999998204729416331065783, 0.00000599211245264242784278378},\n \
    \     {0.99999999999551182356793271877, 0.00000299605622633466075058210},\n  \
    \    {0.99999999999887795586487812538, 0.00000149802811316901122883643},\n   \
    \   {0.99999999999971948897977205850, 0.00000074901405658471572113723},\n    \
    \  {0.99999999999992987223139048746, 0.00000037450702829238412391495},\n     \
    \ {0.99999999999998246807140014902, 0.00000018725351414619534486931},\n      {0.99999999999999561700429751010,\
    \ 0.00000009362675707309808280024},\n      {0.99999999999999890425107437752, 0.00000004681337853654909269501},\n\
    \      {0.99999999999999972607632112153, 0.00000002340668926827455275977},\n \
    \     {0.99999999999999993153263280754, 0.00000001170334463413727718121},\n  \
    \    {0.99999999999999998286960567472, 0.00000000585167231706863869077}};\n\n\
    \  _CXX14_CONSTEXPR coef() : s{}, is{}, ip2{1, .5} {\n    _Tp ies[_Nm];\n    for\
    \ (int i = 0; i < _Nm; ++i) ies[i] = _Tp(1) / es[i];\n\n    _Tp e = 1, ie = 1;\n\
    \    for (int i = 0; i < _Nm; i++) {\n      s[i] = es[i] * e, e *= ies[i];\n \
    \     is[i] = ies[i] * ie, ie *= es[i];\n    }\n\n    for (int i = 1; i < _Nm\
    \ - 1; ++i) ip2[i + 1] = ip2[i] * ip2[1];\n  }\n};\n\n}  // namespace _fft_impl\n\
    \ntemplate <bool _Inverse = false, class _Iterator>\nvoid fft(_Iterator __first,\
    \ _Iterator __last) noexcept {\n  using value_type = typename std::iterator_traits<_Iterator>::value_type;\n\
    \  using difference_type =\n      typename std::iterator_traits<_Iterator>::difference_type;\n\
    \n  _CXX14_CONSTEXPR _fft_impl::coef<value_type> c;\n  auto __h = __builtin_ctz(std::distance(__first,\
    \ __last));\n\n  if _CXX17_CONSTEXPR (_Inverse) {\n    for (difference_type __p\
    \ = 1; __p >> __h ^ 1; __p <<= 1) {\n      value_type __iw = 1;\n      auto __l\
    \ = __first;\n\n      for (auto __i = 1 << __h; __l != __last;\n           __iw\
    \ *= c.is[__builtin_ctz(--__i)]) {\n        auto __r = std::next(__l, __p);\n\n\
    \        for (auto __mid = __r; __l != __mid; ++__l, ++__r) {\n          auto\
    \ __tmp = (*__l - *__r) * __iw;\n          *__l += *__r;\n          *__r = __tmp;\n\
    \        }\n\n        __l = __r;\n      }\n    }\n\n    while (__first != __last)\
    \ *--__last *= c.ip2[__h];\n  }\n\n  else {\n    for (difference_type __p = 1\
    \ << __h; __p >>= 1;) {\n      value_type __w = -1;\n      auto __l = __first;\n\
    \n      for (auto __i = 1 << __h; __l != __last;\n           __w *= c.s[__builtin_ctz(--__i)])\
    \ {\n        auto __r = std::next(__l, __p);\n\n        for (auto __mid = __r;\
    \ __l != __mid; ++__l, ++__r) {\n          auto __tmp = *__l;\n          *__l\
    \ -= *__r *= __w;\n          *__r += __tmp;\n        }\n\n        __l = __r;\n\
    \      }\n    }\n  }\n}\n\ntemplate <class _Iterator>\nvoid fft(_Iterator __first,\
    \ std::size_t __n) noexcept {\n  fft(__first, std::next(__first, __n));\n}\n\n\
    template <class _Iterator>\nvoid ifft(_Iterator __first, _Iterator __last) noexcept\
    \ {\n  fft<true>(__first, __last);\n}\n\ntemplate <class _Iterator>\nvoid ifft(_Iterator\
    \ __first, std::size_t __n) noexcept {\n  ifft(__first, std::next(__first, __n));\n\
    }\n\ntemplate <size_t _Nm, size_t _Dm, class _Container, class _Index>\ndecltype(auto)\
    \ access(_Container &__a, const _Index &__i) {\n  if _CXX17_CONSTEXPR (_Nm !=\
    \ _Dm)\n    return access<_Nm + 1, _Dm>(__a[__i[_Nm]], __i);\n  else\n    return\
    \ __a;\n}\n\ntemplate <bool _Inverse, size_t _Dm, class _Container, class _Tp,\
    \ class _Index>\nvoid dive(_Container &__a, const _Tp &__t, _Index &__i) {\n \
    \ if _CXX17_CONSTEXPR (has_size<_Tp>::value) {\n    for (__i.emplace_back(0);\
    \ __i.back() != std::size(__t); ++__i.back())\n      dive<_Inverse, _Dm + 1>(__a,\
    \ __t[__i.back()], __i);\n    __i.pop_back();\n  }\n\n  else {\n    static std::vector<_Tp>\
    \ __work;\n    // Resize to a power of 2.\n\n    size_t __len = 1 << (31 - __builtin_clz(std::size(__a)));\n\
    \    if (__work.size() < __len) __work.resize(__len);\n\n    for (size_t __k =\
    \ 0; __k != __len; ++__k)\n      __work[__k] = std::move(access<0, _Dm>(__a[__k],\
    \ __i));\n\n    fft<_Inverse>(__work.data(), __work.data() + __len);\n\n    for\
    \ (size_t __k = 0; __k != __len; ++__k)\n      access<0, _Dm>(__a[__k], __i) =\
    \ std::move(__work[__k]);\n  }\n}\n\ntemplate <bool _Inverse, class _Container>\
    \ void fft(_Container &__a) {\n  if _CXX17_CONSTEXPR (has_size<_Container>::value)\
    \ {\n    if _CXX17_CONSTEXPR (has_resize<_Container>::value)\n      // Resize\
    \ to a power of 2.\n      __a.resize(1 << (32 - __builtin_clz(__a.size() - 1)));\n\
    \n    std::vector<size_t> __i;\n    dive<_Inverse, 0>(__a, __a[0], __i);\n\n \
    \   for (size_t __k = 0; __k != std::size(__a); ++__k) fft<_Inverse>(__a[__k]);\n\
    \  }\n}\n\ntemplate <class _Container> auto conv_resize(_Container &__a, _Container\
    \ &__b) {\n  std::array<size_t, get_dimension<_Container>::value> __s;\n  rec(__a,\
    \ __s);\n  rec(__b, __s);\n  return __s;\n}\n\ntemplate <size_t _Nm, class _Container,\
    \ class _Size>\nvoid rec(const _Container &__a, _Size &__s) {\n  if _CXX17_CONSTEXPR\
    \ (_Nm != __s.size()) {\n    __s[_Nm] = std::max(__s[_Nm], std::size(__a));\n\
    \    for (auto &__x : __a) rec<_Nm + 1>(__x, __s);\n  }\n}\n\n}  // namespace\
    \ workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/algebra/fft.hpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/algebra/fft.hpp
layout: document
redirect_from:
- /library/src/algebra/fft.hpp
- /library/src/algebra/fft.hpp.html
title: Fast Fourier Transform
---
