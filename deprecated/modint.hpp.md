---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 2 \"deprecated/modint.hpp\"\n#include <cassert>\n#include <iostream>\n\
    template <int_fast64_t mod = 0> // compile-time defined modulo.\nstruct modint\n\
    {\n    static_assert(mod > 0);\n    template <bool i32, class = void> struct modif\
    \ { using value_type = int_least32_t; };\n    template <class void_t> struct modif<false,\
    \ void_t> { using value_type = int_least64_t; };\n    using value_type = typename\
    \ modif<mod < (1 << 30)>::value_type;\n    constexpr static modint one() noexcept\
    \ { return 1; }\n    constexpr operator value_type() const noexcept { return value;\
    \ }\n    constexpr modint() noexcept = default;\n    template <class int_type,\
    \ std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>\n\
    \    constexpr modint(int_type n) noexcept : value((n %= mod) < 0 ? mod + n :\
    \ n) {}\n    constexpr modint operator++(int) noexcept { modint t{*this}; return\
    \ operator+=(1), t; }\n    constexpr modint operator--(int) noexcept { modint\
    \ t{*this}; return operator-=(1), t; }\n    constexpr modint &operator++() noexcept\
    \ { return operator+=(1); }\n    constexpr modint &operator--() noexcept { return\
    \ operator-=(1); }\n    constexpr modint operator-() const noexcept { return value\
    \ ? mod - value : 0; }\n    constexpr modint &operator+=(const modint &rhs) noexcept\
    \ { return (value += rhs.value) < mod ? 0 : value -= mod, *this; }\n    constexpr\
    \ modint &operator-=(const modint &rhs) noexcept { return (value += mod - rhs.value)\
    \ < mod ? 0 : value -= mod, *this; }\n    constexpr modint &operator*=(const modint\
    \ &rhs) noexcept { return value = (int_fast64_t)value * rhs.value % mod, *this;\
    \ }\n    constexpr modint &operator/=(const modint &rhs) noexcept { return operator*=(rhs.inverse());\
    \ }\n    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value,\
    \ std::nullptr_t> = nullptr>\n    constexpr modint operator+(const int_type &rhs)\
    \ const noexcept { return modint{*this} += rhs; }\n    constexpr modint operator+(const\
    \ modint &rhs) const noexcept { return modint{*this} += rhs; }\n    template <class\
    \ int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t>\
    \ = nullptr>\n    constexpr modint operator-(const int_type &rhs) const noexcept\
    \ { return modint{*this} -= rhs; }\n    constexpr modint operator-(const modint\
    \ &rhs) const noexcept { return modint{*this} -= rhs; }\n    template <class int_type,\
    \ std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>\n\
    \    constexpr modint operator*(const int_type &rhs) const noexcept { return modint{*this}\
    \ *= rhs; }\n    constexpr modint operator*(const modint &rhs) const noexcept\
    \ { return modint{*this} *= rhs; }\n    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value,\
    \ std::nullptr_t> = nullptr>\n    constexpr modint operator/(const int_type &rhs)\
    \ const noexcept { return modint{*this} /= rhs; }\n    constexpr modint operator/(const\
    \ modint &rhs) const noexcept { return modint{*this} /= rhs; }\n    template <class\
    \ int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t>\
    \ = nullptr>\n    constexpr friend modint operator+(const int_type &lhs, const\
    \ modint &rhs) noexcept { return modint(lhs) + rhs; }\n    template <class int_type,\
    \ std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>\n\
    \    constexpr friend modint operator-(const int_type &lhs, const modint &rhs)\
    \ noexcept { return modint(lhs) - rhs; }\n    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value,\
    \ std::nullptr_t> = nullptr>\n    constexpr friend modint operator*(const int_type\
    \ &lhs, const modint &rhs) noexcept { return modint(lhs) * rhs; }\n    template\
    \ <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t>\
    \ = nullptr>\n    constexpr friend modint operator/(const int_type &lhs, const\
    \ modint &rhs) noexcept { return modint(lhs) / rhs; }\n    constexpr modint inverse()\
    \ const noexcept\n    {\n        assert(value);\n        value_type a{mod}, b{value},\
    \ u{}, v{1}, t{};\n        while(b) t = a / b, a ^= b ^= (a -= t * b) ^= b, u\
    \ ^= v ^= (u -= t * v) ^= v;\n        return {u};\n    }\n    constexpr static\
    \ modint pow(modint rhs, int_fast64_t e) noexcept\n    {\n        if(e < 0) e\
    \ = e % (mod - 1) + mod - 1;\n        modint res{1};\n        while(e) { if(e\
    \ & 1) res *= rhs; rhs *= rhs, e >>= 1; }\n        return res;\n    }\n    friend\
    \ std::ostream &operator<<(std::ostream &os, const modint &rhs) noexcept { return\
    \ os << rhs.value; }\n    friend std::istream &operator>>(std::istream &is, modint\
    \ &rhs) noexcept { int_fast64_t value; rhs = (is >> value, value); return is;\
    \ }\nprotected:\n    value_type value = 0;\n}; // class modint\ntemplate <> //\
    \ runtime defined modulo as default(mod = 0).\nstruct modint<0>\n{\n    using\
    \ value_type = int_fast64_t;\n    static value_type &mod() noexcept { static value_type\
    \ mod{}; return mod; }\n    static modint one() noexcept { return 1; }\n    operator\
    \ value_type() const noexcept { return value; }\n    modint() noexcept = default;\n\
    \    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value,\
    \ std::nullptr_t> = nullptr>\n    modint(int_type n) noexcept : value{ (assert(mod()),\
    \ n %= mod() < 0 ? n + mod() : n) } {}\n    modint operator++(int) noexcept {\
    \ modint t{*this}; return operator+=(1), t; }\n    modint operator--(int) noexcept\
    \ { modint t{*this}; return operator-=(1), t; }\n    modint &operator++() noexcept\
    \ { return operator+=(1); }\n    modint &operator--() noexcept { return operator-=(1);\
    \ }\n    modint operator-() const noexcept { return value ? mod() - value : 0;\
    \ }\n    modint &operator+=(const modint &rhs) noexcept { return (value += rhs.value)\
    \ < mod() ? 0 : value -= mod(), *this; }\n    modint &operator-=(const modint\
    \ &rhs) noexcept { return (value += mod() - rhs.value) < mod() ? 0 : value -=\
    \ mod(), *this; }\n    modint &operator*=(const modint &rhs) noexcept { return\
    \ (value *= rhs.value) %= mod(), *this; }\n    modint &operator/=(const modint\
    \ &rhs) noexcept { return operator*=(rhs.inverse()); }\n    template <class int_type,\
    \ std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>\n\
    \    modint operator+(const int_type &rhs) const noexcept { return modint{*this}\
    \ += rhs; }\n    modint operator+(const modint &rhs) const noexcept { return modint{*this}\
    \ += rhs; }\n    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value,\
    \ std::nullptr_t> = nullptr>\n    modint operator-(const int_type &rhs) const\
    \ noexcept { return modint{*this} -= rhs; }\n    modint operator-(const modint\
    \ &rhs) const noexcept { return modint{*this} -= rhs; }\n    template <class int_type,\
    \ std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>\n\
    \    modint operator*(const int_type &rhs) const noexcept { return modint{*this}\
    \ *= rhs; }\n    modint operator*(const modint &rhs) const noexcept { return modint{*this}\
    \ *= rhs; }\n    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value,\
    \ std::nullptr_t> = nullptr>\n    modint operator/(const int_type &rhs) const\
    \ noexcept { return modint{*this} /= rhs; }\n    modint operator/(const modint\
    \ &rhs) const noexcept { return modint{*this} /= rhs; }\n    template <class int_type,\
    \ std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>\n\
    \    friend modint operator+(const int_type &lhs, const modint &rhs) noexcept\
    \ { return modint(lhs) + rhs; }\n    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value,\
    \ std::nullptr_t> = nullptr>\n    friend modint operator-(const int_type &lhs,\
    \ const modint &rhs) noexcept { return modint(lhs) - rhs; }\n    template <class\
    \ int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t>\
    \ = nullptr>\n    friend modint operator*(const int_type &lhs, const modint &rhs)\
    \ noexcept { return modint(lhs) * rhs; }\n    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value,\
    \ std::nullptr_t> = nullptr>\n    friend modint operator/(const int_type &lhs,\
    \ const modint &rhs) noexcept { return modint(lhs) / rhs; }\n    modint inverse()\
    \ const noexcept\n    {\n        assert(mod() && value);\n        value_type a{mod()},\
    \ b{value}, u{}, v{1}, t{};\n        while(b) t = a / b, a ^= b ^= (a -= t * b)\
    \ ^= b, u ^= v ^= (u -= t * v) ^= v;\n        return {u};\n    }\n    static modint\
    \ pow(modint rhs, int_fast64_t e) noexcept\n    {\n        if(e < 0) e = e % (mod()\
    \ - 1) + mod() - 1;\n        modint res{1};\n        while(e) { if(e & 1) res\
    \ *= rhs; rhs *= rhs, e >>= 1; }\n        return res;\n    }\n    friend std::ostream\
    \ &operator<<(std::ostream &os, const modint &rhs) noexcept { return os << rhs.value;\
    \ }\n    friend std::istream &operator>>(std::istream &is, modint &rhs) noexcept\
    \ { int_fast64_t value; rhs = modint((is >> value, value)); return is; }\nprotected:\n\
    \    value_type value = 0;\n}; // class modint<0>\nusing modint_runtime = modint<0>;\n"
  code: "#pragma once\n#include <cassert>\n#include <iostream>\ntemplate <int_fast64_t\
    \ mod = 0> // compile-time defined modulo.\nstruct modint\n{\n    static_assert(mod\
    \ > 0);\n    template <bool i32, class = void> struct modif { using value_type\
    \ = int_least32_t; };\n    template <class void_t> struct modif<false, void_t>\
    \ { using value_type = int_least64_t; };\n    using value_type = typename modif<mod\
    \ < (1 << 30)>::value_type;\n    constexpr static modint one() noexcept { return\
    \ 1; }\n    constexpr operator value_type() const noexcept { return value; }\n\
    \    constexpr modint() noexcept = default;\n    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value,\
    \ std::nullptr_t> = nullptr>\n    constexpr modint(int_type n) noexcept : value((n\
    \ %= mod) < 0 ? mod + n : n) {}\n    constexpr modint operator++(int) noexcept\
    \ { modint t{*this}; return operator+=(1), t; }\n    constexpr modint operator--(int)\
    \ noexcept { modint t{*this}; return operator-=(1), t; }\n    constexpr modint\
    \ &operator++() noexcept { return operator+=(1); }\n    constexpr modint &operator--()\
    \ noexcept { return operator-=(1); }\n    constexpr modint operator-() const noexcept\
    \ { return value ? mod - value : 0; }\n    constexpr modint &operator+=(const\
    \ modint &rhs) noexcept { return (value += rhs.value) < mod ? 0 : value -= mod,\
    \ *this; }\n    constexpr modint &operator-=(const modint &rhs) noexcept { return\
    \ (value += mod - rhs.value) < mod ? 0 : value -= mod, *this; }\n    constexpr\
    \ modint &operator*=(const modint &rhs) noexcept { return value = (int_fast64_t)value\
    \ * rhs.value % mod, *this; }\n    constexpr modint &operator/=(const modint &rhs)\
    \ noexcept { return operator*=(rhs.inverse()); }\n    template <class int_type,\
    \ std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>\n\
    \    constexpr modint operator+(const int_type &rhs) const noexcept { return modint{*this}\
    \ += rhs; }\n    constexpr modint operator+(const modint &rhs) const noexcept\
    \ { return modint{*this} += rhs; }\n    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value,\
    \ std::nullptr_t> = nullptr>\n    constexpr modint operator-(const int_type &rhs)\
    \ const noexcept { return modint{*this} -= rhs; }\n    constexpr modint operator-(const\
    \ modint &rhs) const noexcept { return modint{*this} -= rhs; }\n    template <class\
    \ int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t>\
    \ = nullptr>\n    constexpr modint operator*(const int_type &rhs) const noexcept\
    \ { return modint{*this} *= rhs; }\n    constexpr modint operator*(const modint\
    \ &rhs) const noexcept { return modint{*this} *= rhs; }\n    template <class int_type,\
    \ std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>\n\
    \    constexpr modint operator/(const int_type &rhs) const noexcept { return modint{*this}\
    \ /= rhs; }\n    constexpr modint operator/(const modint &rhs) const noexcept\
    \ { return modint{*this} /= rhs; }\n    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value,\
    \ std::nullptr_t> = nullptr>\n    constexpr friend modint operator+(const int_type\
    \ &lhs, const modint &rhs) noexcept { return modint(lhs) + rhs; }\n    template\
    \ <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t>\
    \ = nullptr>\n    constexpr friend modint operator-(const int_type &lhs, const\
    \ modint &rhs) noexcept { return modint(lhs) - rhs; }\n    template <class int_type,\
    \ std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>\n\
    \    constexpr friend modint operator*(const int_type &lhs, const modint &rhs)\
    \ noexcept { return modint(lhs) * rhs; }\n    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value,\
    \ std::nullptr_t> = nullptr>\n    constexpr friend modint operator/(const int_type\
    \ &lhs, const modint &rhs) noexcept { return modint(lhs) / rhs; }\n    constexpr\
    \ modint inverse() const noexcept\n    {\n        assert(value);\n        value_type\
    \ a{mod}, b{value}, u{}, v{1}, t{};\n        while(b) t = a / b, a ^= b ^= (a\
    \ -= t * b) ^= b, u ^= v ^= (u -= t * v) ^= v;\n        return {u};\n    }\n \
    \   constexpr static modint pow(modint rhs, int_fast64_t e) noexcept\n    {\n\
    \        if(e < 0) e = e % (mod - 1) + mod - 1;\n        modint res{1};\n    \
    \    while(e) { if(e & 1) res *= rhs; rhs *= rhs, e >>= 1; }\n        return res;\n\
    \    }\n    friend std::ostream &operator<<(std::ostream &os, const modint &rhs)\
    \ noexcept { return os << rhs.value; }\n    friend std::istream &operator>>(std::istream\
    \ &is, modint &rhs) noexcept { int_fast64_t value; rhs = (is >> value, value);\
    \ return is; }\nprotected:\n    value_type value = 0;\n}; // class modint\ntemplate\
    \ <> // runtime defined modulo as default(mod = 0).\nstruct modint<0>\n{\n   \
    \ using value_type = int_fast64_t;\n    static value_type &mod() noexcept { static\
    \ value_type mod{}; return mod; }\n    static modint one() noexcept { return 1;\
    \ }\n    operator value_type() const noexcept { return value; }\n    modint()\
    \ noexcept = default;\n    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value,\
    \ std::nullptr_t> = nullptr>\n    modint(int_type n) noexcept : value{ (assert(mod()),\
    \ n %= mod() < 0 ? n + mod() : n) } {}\n    modint operator++(int) noexcept {\
    \ modint t{*this}; return operator+=(1), t; }\n    modint operator--(int) noexcept\
    \ { modint t{*this}; return operator-=(1), t; }\n    modint &operator++() noexcept\
    \ { return operator+=(1); }\n    modint &operator--() noexcept { return operator-=(1);\
    \ }\n    modint operator-() const noexcept { return value ? mod() - value : 0;\
    \ }\n    modint &operator+=(const modint &rhs) noexcept { return (value += rhs.value)\
    \ < mod() ? 0 : value -= mod(), *this; }\n    modint &operator-=(const modint\
    \ &rhs) noexcept { return (value += mod() - rhs.value) < mod() ? 0 : value -=\
    \ mod(), *this; }\n    modint &operator*=(const modint &rhs) noexcept { return\
    \ (value *= rhs.value) %= mod(), *this; }\n    modint &operator/=(const modint\
    \ &rhs) noexcept { return operator*=(rhs.inverse()); }\n    template <class int_type,\
    \ std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>\n\
    \    modint operator+(const int_type &rhs) const noexcept { return modint{*this}\
    \ += rhs; }\n    modint operator+(const modint &rhs) const noexcept { return modint{*this}\
    \ += rhs; }\n    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value,\
    \ std::nullptr_t> = nullptr>\n    modint operator-(const int_type &rhs) const\
    \ noexcept { return modint{*this} -= rhs; }\n    modint operator-(const modint\
    \ &rhs) const noexcept { return modint{*this} -= rhs; }\n    template <class int_type,\
    \ std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>\n\
    \    modint operator*(const int_type &rhs) const noexcept { return modint{*this}\
    \ *= rhs; }\n    modint operator*(const modint &rhs) const noexcept { return modint{*this}\
    \ *= rhs; }\n    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value,\
    \ std::nullptr_t> = nullptr>\n    modint operator/(const int_type &rhs) const\
    \ noexcept { return modint{*this} /= rhs; }\n    modint operator/(const modint\
    \ &rhs) const noexcept { return modint{*this} /= rhs; }\n    template <class int_type,\
    \ std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>\n\
    \    friend modint operator+(const int_type &lhs, const modint &rhs) noexcept\
    \ { return modint(lhs) + rhs; }\n    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value,\
    \ std::nullptr_t> = nullptr>\n    friend modint operator-(const int_type &lhs,\
    \ const modint &rhs) noexcept { return modint(lhs) - rhs; }\n    template <class\
    \ int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t>\
    \ = nullptr>\n    friend modint operator*(const int_type &lhs, const modint &rhs)\
    \ noexcept { return modint(lhs) * rhs; }\n    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value,\
    \ std::nullptr_t> = nullptr>\n    friend modint operator/(const int_type &lhs,\
    \ const modint &rhs) noexcept { return modint(lhs) / rhs; }\n    modint inverse()\
    \ const noexcept\n    {\n        assert(mod() && value);\n        value_type a{mod()},\
    \ b{value}, u{}, v{1}, t{};\n        while(b) t = a / b, a ^= b ^= (a -= t * b)\
    \ ^= b, u ^= v ^= (u -= t * v) ^= v;\n        return {u};\n    }\n    static modint\
    \ pow(modint rhs, int_fast64_t e) noexcept\n    {\n        if(e < 0) e = e % (mod()\
    \ - 1) + mod() - 1;\n        modint res{1};\n        while(e) { if(e & 1) res\
    \ *= rhs; rhs *= rhs, e >>= 1; }\n        return res;\n    }\n    friend std::ostream\
    \ &operator<<(std::ostream &os, const modint &rhs) noexcept { return os << rhs.value;\
    \ }\n    friend std::istream &operator>>(std::istream &is, modint &rhs) noexcept\
    \ { int_fast64_t value; rhs = modint((is >> value, value)); return is; }\nprotected:\n\
    \    value_type value = 0;\n}; // class modint<0>\nusing modint_runtime = modint<0>;\n"
  dependsOn: []
  isVerificationFile: false
  path: deprecated/modint.hpp
  requiredBy: []
  timestamp: '2020-09-09 07:00:40+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: deprecated/modint.hpp
layout: document
redirect_from:
- /library/deprecated/modint.hpp
- /library/deprecated/modint.hpp.html
title: deprecated/modint.hpp
---
