---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: combinatorics/factorial.hpp
    title: combinatorics/factorial.hpp
  - icon: ':x:'
    path: modulus/inverse.hpp
    title: modulus/inverse.hpp
  - icon: ':question:'
    path: modulus/modint.hpp
    title: modular arithmetic.
  - icon: ':question:'
    path: utils/sfinae.hpp
    title: utils/sfinae.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/aizu-online-judge/balls_and_boxes_4.test.cpp
    title: test/aizu-online-judge/balls_and_boxes_4.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 2 \"combinatorics/factorial.hpp\"\n#include <functional>\n#include\
    \ <vector>\ntemplate <class T, class Op = std::multiplies<T>>\nclass factorial\n\
    {\n    std::vector<T> fact;\n    Op op;\npublic:\n    factorial(T init = 1, Op\
    \ op = Op()) : fact{init}, op{op} {}\n    T operator()(const int &n)\n    {\n\
    \        if(n < 0) return 0;\n        for(int m(fact.size()); m <= n; ++m) fact.emplace_back(op(fact.back(),\
    \ m));\n        return fact[n];\n    }\n}; // class factorial\n#line 3 \"modulus/inverse.hpp\"\
    \n\n#line 2 \"modulus/modint.hpp\"\n#include <cassert>\n#include <iostream>\n\n\
    #line 2 \"utils/sfinae.hpp\"\n#include <cstdint>\n#include <iterator>\n#include\
    \ <type_traits>\n\ntemplate <class type, template <class> class trait>\nusing\
    \ enable_if_trait_type = typename std::enable_if<trait<type>::value>::type;\n\n\
    template <class Container>\nusing element_type = typename std::decay<decltype(\n\
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
    \ struct modint : internal::modint_base<Mod> {\n  static_assert(Mod > 0);\n};\n\
    \n/*\n * @struct modint_runtime\n * @brief runtime modular arithmetic.\n * @tparam\
    \ type_id uniquely assigned\n */\ntemplate <unsigned type_id = 0>\nstruct modint_runtime\
    \ : internal::modint_base<-(signed)type_id> {};\n\n// #define modint_newtype modint_runtime<__COUNTER__>\n\
    \n}  // namespace workspace\n#line 5 \"modulus/inverse.hpp\"\ntemplate <class,\
    \ class = int> struct inverse;\n// mod must be prime.\ntemplate <class Modint>\n\
    struct inverse<Modint, decltype((void *)Modint::mod, 0)> {\n  using value_type\
    \ = Modint;\n  constexpr value_type operator()(int n) const {\n    constexpr int_fast64_t\
    \ mod = value_type::mod;\n    assert(n %= mod);\n    if (n < 0) n += mod;\n  \
    \  if (inv.empty()) inv = {1, mod != 1};\n    for (int m(inv.size()); m <= n;\
    \ ++m)\n      inv.emplace_back(mod / m * -inv[mod % m]);\n    return inv[n];\n\
    \  }\n\n private:\n  static std::vector<value_type> inv;\n};\ntemplate <class\
    \ Modint>\nstd::vector<Modint> inverse<Modint, decltype((void *)Modint::mod, 0)>::inv;\n\
    #line 5 \"combinatorics/binomial.hpp\"\ntemplate <class, class = int> struct binomial;\n\
    template <class Modint>\nstruct binomial<Modint, decltype((void *)Modint::mod,\
    \ 0)> {\n  using value_type = Modint;\n  struct mulinv_Op {\n    value_type operator()(const\
    \ value_type &f, const size_t &n) const {\n      return f * inv(n);\n    }\n \
    \ };\n  static inverse<value_type> inv;\n  static factorial<value_type, mulinv_Op>\
    \ fact_inv;\n  static factorial<value_type> fact;\n  value_type operator()(const\
    \ int &n, const int &k) {\n    return fact_inv(k) * fact_inv(n - k) * fact(n);\n\
    \  }\n};\ntemplate <class Modint>\ninverse<Modint> binomial<Modint, decltype((void\
    \ *)Modint::mod, 0)>::inv;\ntemplate <class Modint>\nfactorial<Modint,\n     \
    \     class binomial<Modint, decltype((void *)Modint::mod, 0)>::mulinv_Op>\n \
    \   binomial<Modint, decltype((void *)Modint::mod, 0)>::fact_inv;\ntemplate <class\
    \ Modint>\nfactorial<Modint> binomial<Modint, decltype((void *)Modint::mod, 0)>::fact;\n"
  code: "#pragma once\n#include \"factorial.hpp\"\n#include \"modulus/inverse.hpp\"\
    \n#include \"modulus/modint.hpp\"\ntemplate <class, class = int> struct binomial;\n\
    template <class Modint>\nstruct binomial<Modint, decltype((void *)Modint::mod,\
    \ 0)> {\n  using value_type = Modint;\n  struct mulinv_Op {\n    value_type operator()(const\
    \ value_type &f, const size_t &n) const {\n      return f * inv(n);\n    }\n \
    \ };\n  static inverse<value_type> inv;\n  static factorial<value_type, mulinv_Op>\
    \ fact_inv;\n  static factorial<value_type> fact;\n  value_type operator()(const\
    \ int &n, const int &k) {\n    return fact_inv(k) * fact_inv(n - k) * fact(n);\n\
    \  }\n};\ntemplate <class Modint>\ninverse<Modint> binomial<Modint, decltype((void\
    \ *)Modint::mod, 0)>::inv;\ntemplate <class Modint>\nfactorial<Modint,\n     \
    \     class binomial<Modint, decltype((void *)Modint::mod, 0)>::mulinv_Op>\n \
    \   binomial<Modint, decltype((void *)Modint::mod, 0)>::fact_inv;\ntemplate <class\
    \ Modint>\nfactorial<Modint> binomial<Modint, decltype((void *)Modint::mod, 0)>::fact;\n"
  dependsOn:
  - combinatorics/factorial.hpp
  - modulus/inverse.hpp
  - modulus/modint.hpp
  - utils/sfinae.hpp
  isVerificationFile: false
  path: combinatorics/binomial.hpp
  requiredBy: []
  timestamp: '2020-11-03 18:40:56+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/aizu-online-judge/balls_and_boxes_4.test.cpp
documentation_of: combinatorics/binomial.hpp
layout: document
redirect_from:
- /library/combinatorics/binomial.hpp
- /library/combinatorics/binomial.hpp.html
title: combinatorics/binomial.hpp
---
