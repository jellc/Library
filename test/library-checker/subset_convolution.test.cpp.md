---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/algebra/convolution/subset.hpp
    title: Subset Convolution
  - icon: ':heavy_check_mark:'
    path: src/modular/modint.hpp
    title: Modular Arithmetic
  - icon: ':question:'
    path: src/utils/sfinae.hpp
    title: SFINAE
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/subset_convolution
    links:
    - https://judge.yosupo.jp/problem/subset_convolution
  bundledCode: "#line 1 \"test/library-checker/subset_convolution.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/subset_convolution\"\n#include <iostream>\n\
    \n#line 2 \"src/algebra/convolution/subset.hpp\"\n\n/*\n * @brief Subset Convolution\n\
    \ */\n\n#include <cassert>\n#include <vector>\n\n#line 1 \"lib/bit\"\n\n\n\n#include\
    \ <limits>\n#include <type_traits>\n\nnamespace std {\n\ntemplate <typename _Tp>\
    \ constexpr _Tp __rotl(_Tp __x, int __s) noexcept {\n  constexpr auto _Nd = numeric_limits<_Tp>::digits;\n\
    \  const int __r = __s % _Nd;\n  if (__r == 0)\n    return __x;\n  else if (__r\
    \ > 0)\n    return (__x << __r) | (__x >> ((_Nd - __r) % _Nd));\n  else\n    return\
    \ (__x >> -__r) | (__x << ((_Nd + __r) % _Nd));  // rotr(x, -r)\n}\n\ntemplate\
    \ <typename _Tp> constexpr _Tp __rotr(_Tp __x, int __s) noexcept {\n  constexpr\
    \ auto _Nd = numeric_limits<_Tp>::digits;\n  const int __r = __s % _Nd;\n  if\
    \ (__r == 0)\n    return __x;\n  else if (__r > 0)\n    return (__x >> __r) |\
    \ (__x << ((_Nd - __r) % _Nd));\n  else\n    return (__x << -__r) | (__x >> ((_Nd\
    \ + __r) % _Nd));  // rotl(x, -r)\n}\n\ntemplate <typename _Tp> constexpr int\
    \ __countl_zero(_Tp __x) noexcept {\n  constexpr auto _Nd = numeric_limits<_Tp>::digits;\n\
    \n  if (__x == 0) return _Nd;\n\n  constexpr auto _Nd_ull = numeric_limits<unsigned\
    \ long long>::digits;\n  constexpr auto _Nd_ul = numeric_limits<unsigned long>::digits;\n\
    \  constexpr auto _Nd_u = numeric_limits<unsigned>::digits;\n\n  if _GLIBCXX17_CONSTEXPR\
    \ (_Nd <= _Nd_u) {\n    constexpr int __diff = _Nd_u - _Nd;\n    return __builtin_clz(__x)\
    \ - __diff;\n  } else if _GLIBCXX17_CONSTEXPR (_Nd <= _Nd_ul) {\n    constexpr\
    \ int __diff = _Nd_ul - _Nd;\n    return __builtin_clzl(__x) - __diff;\n  } else\
    \ if _GLIBCXX17_CONSTEXPR (_Nd <= _Nd_ull) {\n    constexpr int __diff = _Nd_ull\
    \ - _Nd;\n    return __builtin_clzll(__x) - __diff;\n  } else  // (_Nd > _Nd_ull)\n\
    \  {\n    static_assert(_Nd <= (2 * _Nd_ull),\n                  \"Maximum supported\
    \ integer size is 128-bit\");\n\n    unsigned long long __high = __x >> _Nd_ull;\n\
    \    if (__high != 0) {\n      constexpr int __diff = (2 * _Nd_ull) - _Nd;\n \
    \     return __builtin_clzll(__high) - __diff;\n    }\n    constexpr auto __max_ull\
    \ = numeric_limits<unsigned long long>::max();\n    unsigned long long __low =\
    \ __x & __max_ull;\n    return (_Nd - _Nd_ull) + __builtin_clzll(__low);\n  }\n\
    }\n\ntemplate <typename _Tp> constexpr int __countl_one(_Tp __x) noexcept {\n\
    \  if (__x == numeric_limits<_Tp>::max()) return numeric_limits<_Tp>::digits;\n\
    \  return __countl_zero<_Tp>((_Tp)~__x);\n}\n\ntemplate <typename _Tp> constexpr\
    \ int __countr_zero(_Tp __x) noexcept {\n  constexpr auto _Nd = numeric_limits<_Tp>::digits;\n\
    \n  if (__x == 0) return _Nd;\n\n  constexpr auto _Nd_ull = numeric_limits<unsigned\
    \ long long>::digits;\n  constexpr auto _Nd_ul = numeric_limits<unsigned long>::digits;\n\
    \  constexpr auto _Nd_u = numeric_limits<unsigned>::digits;\n\n  if _GLIBCXX17_CONSTEXPR\
    \ (_Nd <= _Nd_u)\n    return __builtin_ctz(__x);\n  else if _GLIBCXX17_CONSTEXPR\
    \ (_Nd <= _Nd_ul)\n    return __builtin_ctzl(__x);\n  else if _GLIBCXX17_CONSTEXPR\
    \ (_Nd <= _Nd_ull)\n    return __builtin_ctzll(__x);\n  else  // (_Nd > _Nd_ull)\n\
    \  {\n    static_assert(_Nd <= (2 * _Nd_ull),\n                  \"Maximum supported\
    \ integer size is 128-bit\");\n\n    constexpr auto __max_ull = numeric_limits<unsigned\
    \ long long>::max();\n    unsigned long long __low = __x & __max_ull;\n    if\
    \ (__low != 0) return __builtin_ctzll(__low);\n    unsigned long long __high =\
    \ __x >> _Nd_ull;\n    return __builtin_ctzll(__high) + _Nd_ull;\n  }\n}\n\ntemplate\
    \ <typename _Tp> constexpr int __countr_one(_Tp __x) noexcept {\n  if (__x ==\
    \ numeric_limits<_Tp>::max()) return numeric_limits<_Tp>::digits;\n  return __countr_zero((_Tp)~__x);\n\
    }\n\ntemplate <typename _Tp> constexpr int __popcount(_Tp __x) noexcept {\n  constexpr\
    \ auto _Nd = numeric_limits<_Tp>::digits;\n\n  if (__x == 0) return 0;\n\n  constexpr\
    \ auto _Nd_ull = numeric_limits<unsigned long long>::digits;\n  constexpr auto\
    \ _Nd_ul = numeric_limits<unsigned long>::digits;\n  constexpr auto _Nd_u = numeric_limits<unsigned>::digits;\n\
    \n  if _GLIBCXX17_CONSTEXPR (_Nd <= _Nd_u)\n    return __builtin_popcount(__x);\n\
    \  else if _GLIBCXX17_CONSTEXPR (_Nd <= _Nd_ul)\n    return __builtin_popcountl(__x);\n\
    \  else if _GLIBCXX17_CONSTEXPR (_Nd <= _Nd_ull)\n    return __builtin_popcountll(__x);\n\
    \  else  // (_Nd > _Nd_ull)\n  {\n    static_assert(_Nd <= (2 * _Nd_ull),\n  \
    \                \"Maximum supported integer size is 128-bit\");\n\n    constexpr\
    \ auto __max_ull = numeric_limits<unsigned long long>::max();\n    unsigned long\
    \ long __low = __x & __max_ull;\n    unsigned long long __high = __x >> _Nd_ull;\n\
    \    return __builtin_popcountll(__low) + __builtin_popcountll(__high);\n  }\n\
    }\n\ntemplate <typename _Tp> constexpr bool __has_single_bit(_Tp __x) noexcept\
    \ {\n  return __popcount(__x) == 1;\n}\n\ntemplate <typename _Tp> constexpr _Tp\
    \ __bit_ceil(_Tp __x) noexcept {\n  constexpr auto _Nd = numeric_limits<_Tp>::digits;\n\
    \  if (__x == 0 || __x == 1) return 1;\n  auto __shift_exponent = _Nd - __countl_zero((_Tp)(__x\
    \ - 1u));\n#ifdef _GLIBCXX_HAVE_BUILTIN_IS_CONSTANT_EVALUATED\n  if (!__builtin_is_constant_evaluated())\
    \ {\n    __glibcxx_assert(__shift_exponent != numeric_limits<_Tp>::digits);\n\
    \  }\n#endif\n  using __promoted_type = decltype(__x << 1);\n  if _GLIBCXX17_CONSTEXPR\
    \ (!is_same<__promoted_type, _Tp>::value) {\n    const int __extra_exp = sizeof(__promoted_type)\
    \ / sizeof(_Tp) / 2;\n    __shift_exponent |= (__shift_exponent & _Nd) << __extra_exp;\n\
    \  }\n  return (_Tp)1u << __shift_exponent;\n}\n\ntemplate <typename _Tp> constexpr\
    \ _Tp __bit_floor(_Tp __x) noexcept {\n  constexpr auto _Nd = numeric_limits<_Tp>::digits;\n\
    \  if (__x == 0) return 0;\n  return (_Tp)1u << (_Nd - __countl_zero((_Tp)(__x\
    \ >> 1)));\n}\n\ntemplate <typename _Tp> constexpr _Tp __bit_width(_Tp __x) noexcept\
    \ {\n  constexpr auto _Nd = numeric_limits<_Tp>::digits;\n  return _Nd - __countl_zero(__x);\n\
    }\n\n}  // namespace std\n\n\n#line 11 \"src/algebra/convolution/subset.hpp\"\n\
    \nnamespace workspace {\n\ntemplate <class A> A subset_conv(const A &f, const\
    \ A &g) {\n  const size_t len = std::__bit_floor(std::size(f));\n  const size_t\
    \ n = std::__countr_zero(len);\n\n  std::vector<A> ff(n + 1, A(len)), gg(ff);\n\
    \  ff[0] = f, gg[0] = g;\n\n  for (size_t k = 0; k != n; ++k)\n    for (size_t\
    \ i = k + 1; ~i; --i)\n      for (size_t s = 0; s != len; ++s)\n        if (s\
    \ >> k & 1) {\n          if (i)\n            ff[i][s] = ff[i - 1][s], gg[i][s]\
    \ = gg[i - 1][s];\n          else\n            ff[i][s] = gg[i][s] = {};\n   \
    \       ff[i][s] += ff[i][s ^ 1 << k];\n          gg[i][s] += gg[i][s ^ 1 << k];\n\
    \        }\n\n  for (size_t i = n; ~i; --i)\n    for (size_t s = 0; s != len;\
    \ ++s) {\n      ff[i][s] *= gg[0][s];\n      for (size_t j = i; j; --j) ff[i][s]\
    \ += ff[i - j][s] * gg[j][s];\n    }\n\n  for (size_t k = n - 1; ~k; --k)\n  \
    \  for (size_t s = 0; s != len; ++s)\n      if (~s >> k & 1)\n        for (size_t\
    \ i = n; ~i; --i) {\n          ff[i][s ^ 1 << k] -= ff[i][s];\n          if (i)\
    \ ff[i][s] = ff[i - 1][s];\n        }\n\n  return ff[n];\n}\n\n}  // namespace\
    \ workspace\n#line 2 \"src/modular/modint.hpp\"\n\n/*\n * @file modint.hpp\n *\
    \ @brief Modular Arithmetic\n */\n\n#line 10 \"src/modular/modint.hpp\"\n\n#line\
    \ 2 \"src/utils/sfinae.hpp\"\n\n/*\n * @file sfinae.hpp\n * @brief SFINAE\n */\n\
    \n#include <cstdint>\n#include <iterator>\n#line 11 \"src/utils/sfinae.hpp\"\n\
    \nnamespace workspace {\n\ntemplate <class type, template <class> class trait>\n\
    using enable_if_trait_type = typename std::enable_if<trait<type>::value>::type;\n\
    \ntemplate <class Container>\nusing element_type = typename std::decay<decltype(\n\
    \    *std::begin(std::declval<Container&>()))>::type;\n\ntemplate <class T, class\
    \ = std::nullptr_t>\nstruct has_begin : std::false_type {};\n\ntemplate <class\
    \ T>\nstruct has_begin<T, decltype(std::begin(std::declval<T>()), nullptr)>\n\
    \    : std::true_type {};\n\ntemplate <class T, class = int> struct mapped_of\
    \ {\n  using type = element_type<T>;\n};\ntemplate <class T>\nstruct mapped_of<T,\n\
    \                 typename std::pair<int, typename T::mapped_type>::first_type>\
    \ {\n  using type = typename T::mapped_type;\n};\ntemplate <class T> using mapped_type\
    \ = typename mapped_of<T>::type;\n\ntemplate <class T, class = void> struct is_integral_ext\
    \ : std::false_type {};\ntemplate <class T>\nstruct is_integral_ext<\n    T, typename\
    \ std::enable_if<std::is_integral<T>::value>::type>\n    : std::true_type {};\n\
    \n#ifdef __SIZEOF_INT128__\ntemplate <> struct is_integral_ext<__int128_t> : std::true_type\
    \ {};\ntemplate <> struct is_integral_ext<__uint128_t> : std::true_type {};\n\
    #endif\n\n#if __cplusplus >= 201402\ntemplate <class T>\nconstexpr static bool\
    \ is_integral_ext_v = is_integral_ext<T>::value;\n#endif\n\ntemplate <typename\
    \ T, typename = void> struct multiplicable_uint {\n  using type = uint_least32_t;\n\
    };\ntemplate <typename T>\nstruct multiplicable_uint<T, typename std::enable_if<(2\
    \ < sizeof(T))>::type> {\n  using type = uint_least64_t;\n};\n\n#ifdef __SIZEOF_INT128__\n\
    template <typename T>\nstruct multiplicable_uint<T, typename std::enable_if<(4\
    \ < sizeof(T))>::type> {\n  using type = __uint128_t;\n};\n#endif\n\n}  // namespace\
    \ workspace\n#line 12 \"src/modular/modint.hpp\"\n\nnamespace workspace {\n\n\
    namespace internal {\n\n/*\n * @struct modint_base\n * @brief base of modular\
    \ arithmetic.\n * @tparam Mod identifier, which represents modulus if positive\n\
    \ */\ntemplate <auto Mod> struct modint_base {\n  static_assert(is_integral_ext<decltype(Mod)>::value,\n\
    \                \"Mod must be integral type.\");\n\n  using mod_type =\n    \
    \  typename std::conditional<0 < Mod,\n                                typename\
    \ std::add_const<decltype(Mod)>::type,\n                                decltype(Mod)>::type;\n\
    \  static mod_type mod;\n\n  using value_type = typename std::decay<mod_type>::type;\n\
    \n  constexpr operator value_type() const noexcept { return value; }\n\n  constexpr\
    \ static modint_base one() noexcept { return 1; }\n\n  constexpr modint_base()\
    \ noexcept = default;\n\n  template <class int_type,\n            typename std::enable_if<is_integral_ext<int_type>::value>::type\
    \ * =\n                nullptr>\n  constexpr modint_base(int_type n) noexcept\n\
    \      : value((n %= mod) < 0 ? mod + n : n) {}\n\n  constexpr modint_base(bool\
    \ n) noexcept : modint_base(int(n)) {}\n\n  constexpr modint_base operator++(int)\
    \ noexcept {\n    modint_base t{*this};\n    return operator+=(1), t;\n  }\n\n\
    \  constexpr modint_base operator--(int) noexcept {\n    modint_base t{*this};\n\
    \    return operator-=(1), t;\n  }\n\n  constexpr modint_base &operator++() noexcept\
    \ { return operator+=(1); }\n\n  constexpr modint_base &operator--() noexcept\
    \ { return operator-=(1); }\n\n  constexpr modint_base operator-() const noexcept\
    \ {\n    return value ? mod - value : 0;\n  }\n\n  constexpr modint_base &operator+=(const\
    \ modint_base &rhs) noexcept {\n    return (value += rhs.value) < mod ? 0 : value\
    \ -= mod, *this;\n  }\n\n  constexpr modint_base &operator-=(const modint_base\
    \ &rhs) noexcept {\n    return (value += mod - rhs.value) < mod ? 0 : value -=\
    \ mod, *this;\n  }\n\n  constexpr modint_base &operator*=(const modint_base &rhs)\
    \ noexcept {\n    return value = (typename multiplicable_uint<value_type>::type)value\
    \ *\n                   rhs.value % mod,\n           *this;\n  }\n\n  constexpr\
    \ modint_base &operator/=(const modint_base &rhs) noexcept {\n    return operator*=(rhs.inverse());\n\
    \  }\n\n  template <class int_type>\n  constexpr typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                    modint_base>::type\n  operator+(const int_type\
    \ &rhs) const noexcept {\n    return modint_base{*this} += rhs;\n  }\n\n  constexpr\
    \ modint_base operator+(const modint_base &rhs) const noexcept {\n    return modint_base{*this}\
    \ += rhs;\n  }\n\n  template <class int_type>\n  constexpr typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                    modint_base>::type\n  operator-(const int_type\
    \ &rhs) const noexcept {\n    return modint_base{*this} -= rhs;\n  }\n\n  constexpr\
    \ modint_base operator-(const modint_base &rhs) const noexcept {\n    return modint_base{*this}\
    \ -= rhs;\n  }\n\n  template <class int_type>\n  constexpr typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                    modint_base>::type\n  operator*(const int_type\
    \ &rhs) const noexcept {\n    return modint_base{*this} *= rhs;\n  }\n\n  constexpr\
    \ modint_base operator*(const modint_base &rhs) const noexcept {\n    return modint_base{*this}\
    \ *= rhs;\n  }\n\n  template <class int_type>\n  constexpr typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                    modint_base>::type\n  operator/(const int_type\
    \ &rhs) const noexcept {\n    return modint_base{*this} /= rhs;\n  }\n\n  constexpr\
    \ modint_base operator/(const modint_base &rhs) const noexcept {\n    return modint_base{*this}\
    \ /= rhs;\n  }\n\n  template <class int_type>\n  constexpr friend typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                           modint_base>::type\n  operator+(const\
    \ int_type &lhs, const modint_base &rhs) noexcept {\n    return modint_base(lhs)\
    \ + rhs;\n  }\n\n  template <class int_type>\n  constexpr friend typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                           modint_base>::type\n  operator-(const\
    \ int_type &lhs, const modint_base &rhs) noexcept {\n    return modint_base(lhs)\
    \ - rhs;\n  }\n\n  template <class int_type>\n  constexpr friend typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                           modint_base>::type\n  operator*(const\
    \ int_type &lhs, const modint_base &rhs) noexcept {\n    return modint_base(lhs)\
    \ * rhs;\n  }\n\n  template <class int_type>\n  constexpr friend typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                           modint_base>::type\n  operator/(const\
    \ int_type &lhs, const modint_base &rhs) noexcept {\n    return modint_base(lhs)\
    \ / rhs;\n  }\n\n  constexpr modint_base inverse() const noexcept {\n    assert(value);\n\
    \    value_type a{mod}, b{value}, u{}, v{1}, t{};\n    while (b)\n      t = a\
    \ / b, a ^= b ^= (a -= t * b) ^= b, u ^= v ^= (u -= t * v) ^= v;\n    return {u};\n\
    \  }\n\n  template <class int_type>\n  constexpr typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                    modint_base>::type\n  power(int_type e) noexcept\
    \ {\n    return pow(*this, e);\n  }\n\n  template <class int_type>\n  friend constexpr\
    \ typename std::enable_if<is_integral_ext<int_type>::value,\n                \
    \                           modint_base>::type\n  pow(modint_base b, int_type\
    \ e) noexcept {\n    modint_base res{1};\n    for (e < 0 ? b = b.inverse(), e\
    \ = -e : 0; e; e >>= 1, b *= b)\n      if (e & 1) res *= b;\n    return res;\n\
    \  }\n\n  friend std::ostream &operator<<(std::ostream &os,\n                \
    \                  const modint_base &rhs) noexcept {\n    return os << rhs.value;\n\
    \  }\n\n  friend std::istream &operator>>(std::istream &is, modint_base &rhs)\
    \ noexcept {\n    intmax_t value;\n    rhs = (is >> value, value);\n    return\
    \ is;\n  }\n\n protected:\n  value_type value = 0;\n};\n\ntemplate <auto Mod>\n\
    typename modint_base<Mod>::mod_type modint_base<Mod>::mod = Mod;\n\n}  // namespace\
    \ internal\n\n/*\n * @typedef modint\n * @brief modular arithmetic.\n * @tparam\
    \ Mod modulus\n */\ntemplate <auto Mod, typename std::enable_if<(Mod > 0)>::type\
    \ * = nullptr>\nusing modint = internal::modint_base<Mod>;\n\n/*\n * @typedef\
    \ modint_runtime\n * @brief runtime modular arithmetic.\n * @tparam type_id uniquely\
    \ assigned\n */\ntemplate <unsigned type_id = 0>\nusing modint_runtime = internal::modint_base<-(signed)type_id>;\n\
    \n// #define modint_newtype modint_runtime<__COUNTER__>\n\n}  // namespace workspace\n\
    #line 6 \"test/library-checker/subset_convolution.test.cpp\"\n\nint main() {\n\
    \  using mint = workspace::modint<998244353>;\n  using std::cin;\n  int n;\n \
    \ cin >> n;\n  std::vector<mint> a(1 << n), b(1 << n);\n  for (auto &x : a) cin\
    \ >> x;\n  for (auto &x : b) cin >> x;\n  a = workspace::subset_conv(a, b);\n\
    \  for (auto x : a) printf(\"%d \", x);\n  puts(\"\");\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/subset_convolution\"\n\
    #include <iostream>\n\n#include \"src/algebra/convolution/subset.hpp\"\n#include\
    \ \"src/modular/modint.hpp\"\n\nint main() {\n  using mint = workspace::modint<998244353>;\n\
    \  using std::cin;\n  int n;\n  cin >> n;\n  std::vector<mint> a(1 << n), b(1\
    \ << n);\n  for (auto &x : a) cin >> x;\n  for (auto &x : b) cin >> x;\n  a =\
    \ workspace::subset_conv(a, b);\n  for (auto x : a) printf(\"%d \", x);\n  puts(\"\
    \");\n}\n"
  dependsOn:
  - src/algebra/convolution/subset.hpp
  - src/modular/modint.hpp
  - src/utils/sfinae.hpp
  isVerificationFile: true
  path: test/library-checker/subset_convolution.test.cpp
  requiredBy: []
  timestamp: '2020-12-08 03:07:51+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/library-checker/subset_convolution.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/subset_convolution.test.cpp
- /verify/test/library-checker/subset_convolution.test.cpp.html
title: test/library-checker/subset_convolution.test.cpp
---