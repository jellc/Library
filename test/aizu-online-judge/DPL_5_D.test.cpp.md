---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/combinatorics/binomial.hpp
    title: Binomial Coefficient
  - icon: ':heavy_check_mark:'
    path: src/combinatorics/factorial.hpp
    title: Factorial
  - icon: ':heavy_check_mark:'
    path: src/modular/inverse.hpp
    title: Inverse Table
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
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/DPL_5_D
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/DPL_5_D
  bundledCode: "#line 1 \"test/aizu-online-judge/DPL_5_D.test.cpp\"\n#define PROBLEM\
    \ \"https://onlinejudge.u-aizu.ac.jp/problems/DPL_5_D\"\n\n#include <cstdio>\n\
    \n#line 2 \"src/combinatorics/binomial.hpp\"\n\n/*\n * @file binomial.hpp\n *\
    \ @brief Binomial Coefficient\n */\n\n#line 2 \"src/modular/inverse.hpp\"\n\n\
    /*\n * @file inverse.hpp\n * @brief Inverse Table\n */\n\n#include <vector>\n\n\
    #line 2 \"src/modular/modint.hpp\"\n\n/*\n * @file modint.hpp\n * @brief Modular\
    \ Arithmetic\n */\n\n#include <cassert>\n#include <iostream>\n\n#line 2 \"src/utils/sfinae.hpp\"\
    \n\n/*\n * @file sfinae.hpp\n * @brief SFINAE\n */\n\n#include <cstdint>\n#include\
    \ <iterator>\n#include <type_traits>\n\nnamespace workspace {\n\ntemplate <class\
    \ type, template <class> class trait>\nusing enable_if_trait_type = typename std::enable_if<trait<type>::value>::type;\n\
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
    #line 11 \"src/modular/inverse.hpp\"\n\nnamespace workspace {\n\n// Modulus must\
    \ be prime.\ntemplate <class Modint> struct inverse_table {\n  static_assert(std::is_same<std::nullptr_t,\n\
    \                             decltype((void *)Modint::mod, nullptr)>::value);\n\
    \n  using value_type = Modint;\n\n  constexpr value_type operator()(int n) const\
    \ {\n    constexpr int_fast64_t mod = value_type::mod;\n    assert(n %= mod);\n\
    \    if (n < 0) n += mod;\n    if (inv.empty()) inv = {1, mod != 1};\n    for\
    \ (int m(inv.size()); m <= n; ++m)\n      inv.emplace_back(mod / m * -inv[mod\
    \ % m]);\n    return inv[n];\n  }\n\n private:\n  static std::vector<value_type>\
    \ inv;\n};\n\ntemplate <class Modint> std::vector<Modint> inverse_table<Modint>::inv;\n\
    \n}  // namespace workspace\n#line 2 \"src/combinatorics/factorial.hpp\"\n\n/*\n\
    \ * @brief Factorial\n */\n\n#include <functional>\n#line 9 \"src/combinatorics/factorial.hpp\"\
    \n\nnamespace workspace {\n\ntemplate <class Tp, class Op = std::multiplies<Tp>>\
    \ class factorial {\n  std::vector<Tp> fact;\n  Op op;\n\n public:\n  factorial(Tp\
    \ init = 1, Op op = Op()) : fact{init}, op{op} {}\n\n  Tp operator()(int_least32_t\
    \ n) {\n    if (n < 0) return 0;\n    for (int_least32_t m(fact.size()); m <=\
    \ n; ++m)\n      fact.emplace_back(op(fact.back(), m));\n    return fact[n];\n\
    \  }\n};\n\n}  // namespace workspace\n#line 11 \"src/combinatorics/binomial.hpp\"\
    \n\nnamespace workspace {\n\ntemplate <class, class = int> struct binomial;\n\
    template <class Modint> struct binomial<Modint> {\n  static_assert(std::is_same<std::nullptr_t,\n\
    \                             decltype((void *)Modint::mod, nullptr)>::value);\n\
    \n  using value_type = Modint;\n  struct mulinv_Op {\n    value_type operator()(const\
    \ value_type &f, const size_t &n) const {\n      return f * inv(n);\n    }\n \
    \ };\n\n  static inverse_table<value_type> inv;\n  static factorial<value_type,\
    \ mulinv_Op> fact_inv;\n  static factorial<value_type> fact;\n\n  value_type operator()(int_least32_t\
    \ n, int_least32_t k) {\n    return fact_inv(k) * fact_inv(n - k) * fact(n);\n\
    \  }\n};\n\ntemplate <class Modint> inverse_table<Modint> binomial<Modint>::inv;\n\
    template <class Modint>\nfactorial<Modint, class binomial<Modint>::mulinv_Op>\
    \ binomial<Modint>::fact_inv;\ntemplate <class Modint> factorial<Modint> binomial<Modint>::fact;\n\
    \n}  // namespace workspace\n#line 6 \"test/aizu-online-judge/DPL_5_D.test.cpp\"\
    \n\nint main() {\n  using namespace workspace;\n  int n, k;\n  scanf(\"%d%d\"\
    , &n, &k);\n  printf(\"%d\\n\", binomial<modint<1000000007>>()(n + k - 1, n));\n\
    }\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/DPL_5_D\"\n\n\
    #include <cstdio>\n\n#include \"src/combinatorics/binomial.hpp\"\n\nint main()\
    \ {\n  using namespace workspace;\n  int n, k;\n  scanf(\"%d%d\", &n, &k);\n \
    \ printf(\"%d\\n\", binomial<modint<1000000007>>()(n + k - 1, n));\n}\n"
  dependsOn:
  - src/combinatorics/binomial.hpp
  - src/modular/inverse.hpp
  - src/modular/modint.hpp
  - src/utils/sfinae.hpp
  - src/combinatorics/factorial.hpp
  isVerificationFile: true
  path: test/aizu-online-judge/DPL_5_D.test.cpp
  requiredBy: []
  timestamp: '2020-12-08 19:06:53+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aizu-online-judge/DPL_5_D.test.cpp
layout: document
redirect_from:
- /verify/test/aizu-online-judge/DPL_5_D.test.cpp
- /verify/test/aizu-online-judge/DPL_5_D.test.cpp.html
title: test/aizu-online-judge/DPL_5_D.test.cpp
---
