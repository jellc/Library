---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algebra/convolution/subset.hpp
    title: algebra/convolution/subset.hpp
  - icon: ':question:'
    path: modulus/modint.hpp
    title: modular arithmetic.
  - icon: ':question:'
    path: utils/sfinae.hpp
    title: utils/sfinae.hpp
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
    \n#line 1 \"algebra/convolution/subset.hpp\"\n#include <cassert>\n#include <vector>\n\
    \ntemplate <class Ring>\nstd::vector<Ring> subset_convolute(const std::vector<Ring>\
    \ &f, const std::vector<Ring> &g)\n{\n    assert(!f.empty()); assert(!g.empty());\n\
    \    const size_t n = __builtin_ctz(std::min(f.size(), g.size()));\n    std::vector\
    \ ff(n + 1, std::vector<Ring>(1 << n)), gg(ff);\n    ff[0] = f, gg[0] = g;\n \
    \   for(size_t k = 0; k != n; ++k)\n    {\n        for(size_t i = k + 1; ~i; --i)\n\
    \        {\n            for(size_t s = 0; s != 1u << n; ++s)\n            {\n\
    \                if(s >> k & 1)\n                {\n                    if(i)\n\
    \                    {\n                        ff[i][s] = ff[i - 1][s];\n   \
    \                     gg[i][s] = gg[i - 1][s];\n                    }\n      \
    \              else\n                    {\n                        ff[i][s] =\
    \ gg[i][s] = Ring{};\n                    }\n                    ff[i][s] += ff[i][s\
    \ ^ 1 << k];\n                    gg[i][s] += gg[i][s ^ 1 << k];\n           \
    \     }\n            }\n        }\n    }\n    for(size_t i = n; ~i; --i)\n   \
    \ {\n        for(size_t s = 0; s != 1u << n; ++s)\n        {\n            ff[i][s]\
    \ *= gg[0][s];\n            for(size_t j = i; j; --j)\n            {\n       \
    \         ff[i][s] += ff[i - j][s] * gg[j][s];\n            }\n        }\n   \
    \ }\n    for(size_t k = n - 1; ~k; --k)\n    {\n        for(size_t s = 0; s !=\
    \ 1u << n; ++s)\n        {\n            if(~s >> k & 1)\n            {\n     \
    \           for(size_t i = n; ~i; --i)\n                {\n                  \
    \  ff[i][s ^ 1 << k] -= ff[i][s];\n                    if(i) ff[i][s] = ff[i -\
    \ 1][s];\n                }\n            }\n        }\n    }\n    return ff[n];\n\
    }\n#line 4 \"modulus/modint.hpp\"\n\n#line 2 \"utils/sfinae.hpp\"\n#include <cstdint>\n\
    #include <iterator>\n#include <type_traits>\n\ntemplate <class type, template\
    \ <class> class trait>\nusing enable_if_trait_type = typename std::enable_if<trait<type>::value>::type;\n\
    \ntemplate <class Container>\nusing element_type = typename std::decay<decltype(\n\
    \    *std::begin(std::declval<Container&>()))>::type;\n\ntemplate <class T, class\
    \ = int> struct mapped_of {\n  using type = element_type<T>;\n};\ntemplate <class\
    \ T>\nstruct mapped_of<T,\n                 typename std::pair<int, typename T::mapped_type>::first_type>\
    \ {\n  using type = typename T::mapped_type;\n};\ntemplate <class T> using mapped_type\
    \ = typename mapped_of<T>::type;\n\ntemplate <class T, class = void> struct is_integral_ext\
    \ : std::false_type {};\ntemplate <class T>\nstruct is_integral_ext<\n    T, typename\
    \ std::enable_if<std::is_integral<T>::value>::type>\n    : std::true_type {};\n\
    template <> struct is_integral_ext<__int128_t> : std::true_type {};\ntemplate\
    \ <> struct is_integral_ext<__uint128_t> : std::true_type {};\n#if __cplusplus\
    \ >= 201402\ntemplate <class T>\nconstexpr static bool is_integral_ext_v = is_integral_ext<T>::value;\n\
    #endif\n\ntemplate <typename T, typename = void> struct multiplicable_uint {\n\
    \  using type = uint_least32_t;\n};\ntemplate <typename T>\nstruct multiplicable_uint<T,\
    \ typename std::enable_if<(2 < sizeof(T))>::type> {\n  using type = uint_least64_t;\n\
    };\ntemplate <typename T>\nstruct multiplicable_uint<T, typename std::enable_if<(4\
    \ < sizeof(T))>::type> {\n  using type = __uint128_t;\n};\n#line 6 \"modulus/modint.hpp\"\
    \n\nnamespace workspace {\n\nnamespace internal {\n\ntemplate <auto Mod = 0, typename\
    \ Mod_type = decltype(Mod)> struct modint_base {\n  static_assert(is_integral_ext<decltype(Mod)>::value,\n\
    \                \"Mod must be integral type.\");\n\n  using mod_type = typename\
    \ std::conditional<\n      0 < Mod, typename std::add_const<Mod_type>::type, Mod_type>::type;\n\
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
    \ is;\n  }\n\n protected:\n  value_type value = 0;\n};\n\ntemplate <auto Mod,\
    \ typename Mod_type>\ntypename modint_base<Mod, Mod_type>::mod_type modint_base<Mod,\
    \ Mod_type>::mod =\n    Mod;\n\n}  // namespace internal\n\n/*\n * @struct modint\n\
    \ * @brief modular arithmetic.\n * @tparam Mod modulus\n */\ntemplate <auto Mod>\
    \ struct modint : internal::modint_base<Mod> {\n  static_assert(Mod > 0);\n  using\
    \ internal::modint_base<Mod>::modint_base;\n};\n\n/*\n * @struct modint_runtime\n\
    \ * @brief runtime modular arithmetic.\n * @tparam type_id uniquely assigned\n\
    \ */\ntemplate <unsigned type_id = 0>\nstruct modint_runtime : internal::modint_base<-(signed)type_id>\
    \ {\n  using internal::modint_base<-(signed)type_id>::modint_base;\n};\n\n// #define\
    \ modint_newtype modint_runtime<__COUNTER__>\n\n}  // namespace workspace\n#line\
    \ 6 \"test/library-checker/subset_convolution.test.cpp\"\n\nint main() {\n  using\
    \ mint = workspace::modint<998244353>;\n  using std::cin;\n  int n;\n  cin >>\
    \ n;\n  std::vector<mint> a(1 << n), b(1 << n);\n  for (auto &x : a) cin >> x;\n\
    \  for (auto &x : b) cin >> x;\n  a = subset_convolute(a, b);\n  for (auto x :\
    \ a) printf(\"%d \", x);\n  puts(\"\");\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/subset_convolution\"\n\
    #include <iostream>\n\n#include \"algebra/convolution/subset.hpp\"\n#include \"\
    modulus/modint.hpp\"\n\nint main() {\n  using mint = workspace::modint<998244353>;\n\
    \  using std::cin;\n  int n;\n  cin >> n;\n  std::vector<mint> a(1 << n), b(1\
    \ << n);\n  for (auto &x : a) cin >> x;\n  for (auto &x : b) cin >> x;\n  a =\
    \ subset_convolute(a, b);\n  for (auto x : a) printf(\"%d \", x);\n  puts(\"\"\
    );\n}\n"
  dependsOn:
  - algebra/convolution/subset.hpp
  - modulus/modint.hpp
  - utils/sfinae.hpp
  isVerificationFile: true
  path: test/library-checker/subset_convolution.test.cpp
  requiredBy: []
  timestamp: '2020-11-03 18:50:43+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/library-checker/subset_convolution.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/subset_convolution.test.cpp
- /verify/test/library-checker/subset_convolution.test.cpp.html
title: test/library-checker/subset_convolution.test.cpp
---
