---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"variant/modular.hpp\"\n#include <cassert>\n#include <iostream>\n\
    // modulo individually set\nclass modular\n{\n    long long val;\n    int mod;\n\
    public:\n    friend constexpr bool mod_same(const modular &x, const modular &y)\
    \ { return x.mod == y.mod; }\n    constexpr modular(long long x) : val(x), mod{}\
    \ {}\n    constexpr modular(long long x, int _mod) noexcept : val((x %= _mod)\
    \ < 0 ? x + _mod : x), mod(_mod) {}\n    constexpr bool mod_set() const noexcept\
    \ { return mod; }\n    constexpr long long value() const noexcept { return val;\
    \ }\n    constexpr int modulo() const noexcept { return mod; }\n    constexpr\
    \ modular operator++(int) noexcept { modular t = *this; return ++val, t; }\n \
    \   constexpr modular &operator++() noexcept { return ++val, *this; }\n    constexpr\
    \ modular operator--(int) noexcept { modular t = *this; return --val, t; }\n \
    \   constexpr modular &operator--() noexcept { return --val, *this; }\n    constexpr\
    \ modular &operator=(long long other) noexcept { return val = (other %= mod) <\
    \ 0 ? other + mod : other, *this; }\n    constexpr modular &operator+=(long long\
    \ other) noexcept { return (val += other % mod) < mod ? 0 : val -= mod, *this;\
    \ }\n    constexpr modular &operator+=(const modular &other) noexcept { assert(mod_same(*this,\
    \ other)); return (val += other.val) < mod ? 0 : val -= mod, *this; }\n    constexpr\
    \ modular &operator-=(long long other) noexcept { return (val += mod - other %\
    \ mod) < mod ? 0 : val -= mod, *this; }\n    constexpr modular &operator-=(const\
    \ modular &other) noexcept { assert(mod_same(*this, other)); return (val += mod\
    \ - other.val) < mod ? 0 : val -= mod, *this; }\n    constexpr modular &operator*=(long\
    \ long other) noexcept { return (val *= other % mod) %= mod, *this; }\n    constexpr\
    \ modular &operator*=(const modular &other) noexcept { assert(mod_same(*this,\
    \ other)); return (val *= other.val) %= mod, *this; }\n    constexpr modular &operator/=(long\
    \ long other) noexcept { return *this *= inverse(modular{other, mod}); }\n   \
    \ constexpr modular &operator/=(const modular &other) noexcept { assert(mod_same(*this,\
    \ other)); return *this *= inverse(other); }\n    constexpr modular operator-()\
    \ const noexcept { return modular(-val); }\n    template <typename T> constexpr\
    \ modular operator+(const T &other) const noexcept { return modular(*this) +=\
    \ other; }\n    template <typename T> constexpr modular operator-(const T &other)\
    \ const noexcept { return modular(*this) -= other; }\n    template <typename T>\
    \ constexpr modular operator*(const T &other) const noexcept { return modular(*this)\
    \ *= other; }\n    template <typename T> constexpr modular operator/(const T &other)\
    \ const noexcept { return modular(*this) /= other; }\n    constexpr bool operator==(const\
    \ modular &other) const noexcept { assert(mod_same(*this, other)); return val\
    \ == other.val; }\n    constexpr bool operator!=(const modular &other) const noexcept\
    \ { assert(mod_same(*this, other)); return val != other.val; }\n    constexpr\
    \ bool operator!() const noexcept { return !val; }\n    friend constexpr modular\
    \ operator+(long long x, modular y) noexcept { return modular(x + y.val, y.mod);\
    \ }\n    friend constexpr modular operator-(long long x, modular y) noexcept {\
    \ return modular(x - y.val, y.mod); }\n    friend constexpr modular operator*(long\
    \ long x, modular y) noexcept { return modular(x % y.mod * y.val, y.mod); }\n\
    \    friend constexpr modular operator/(long long x, modular y) noexcept { return\
    \ modular(x % y.mod * inverse(y).val, y.mod); }\n    friend constexpr modular\
    \ inverse(const modular &other) noexcept\n    {\n        assert(other.mod && other.val);\n\
    \        long long a{other.mod}, b{other.val}, u{}, v{1}, t{};\n        while(b)\
    \ t = a / b, a ^= b ^= (a -= t * b) ^= b, u ^= v ^= (u -= t * v) ^= v;\n     \
    \   return {u, other.mod};\n    }\n    friend constexpr modular pow(modular other,\
    \ long long e) noexcept\n    {\n        if(e < 0) e = e % (other.mod - 1) + other.mod\
    \ - 1;\n        modular res{1, other.mod};\n        while(e) { if(e & 1) res *=\
    \ other; other *= other, e >>= 1; }\n        return res;\n    }\n    friend std::ostream\
    \ &operator<<(std::ostream &os, const modular &other) noexcept { return os <<\
    \ other.val; }\n    friend std::istream &operator>>(std::istream &is, modular\
    \ &other) noexcept { long long val; other = modular((is >> val, val)); return\
    \ is; }\n}; // class modular\n"
  code: "#include <cassert>\n#include <iostream>\n// modulo individually set\nclass\
    \ modular\n{\n    long long val;\n    int mod;\npublic:\n    friend constexpr\
    \ bool mod_same(const modular &x, const modular &y) { return x.mod == y.mod; }\n\
    \    constexpr modular(long long x) : val(x), mod{} {}\n    constexpr modular(long\
    \ long x, int _mod) noexcept : val((x %= _mod) < 0 ? x + _mod : x), mod(_mod)\
    \ {}\n    constexpr bool mod_set() const noexcept { return mod; }\n    constexpr\
    \ long long value() const noexcept { return val; }\n    constexpr int modulo()\
    \ const noexcept { return mod; }\n    constexpr modular operator++(int) noexcept\
    \ { modular t = *this; return ++val, t; }\n    constexpr modular &operator++()\
    \ noexcept { return ++val, *this; }\n    constexpr modular operator--(int) noexcept\
    \ { modular t = *this; return --val, t; }\n    constexpr modular &operator--()\
    \ noexcept { return --val, *this; }\n    constexpr modular &operator=(long long\
    \ other) noexcept { return val = (other %= mod) < 0 ? other + mod : other, *this;\
    \ }\n    constexpr modular &operator+=(long long other) noexcept { return (val\
    \ += other % mod) < mod ? 0 : val -= mod, *this; }\n    constexpr modular &operator+=(const\
    \ modular &other) noexcept { assert(mod_same(*this, other)); return (val += other.val)\
    \ < mod ? 0 : val -= mod, *this; }\n    constexpr modular &operator-=(long long\
    \ other) noexcept { return (val += mod - other % mod) < mod ? 0 : val -= mod,\
    \ *this; }\n    constexpr modular &operator-=(const modular &other) noexcept {\
    \ assert(mod_same(*this, other)); return (val += mod - other.val) < mod ? 0 :\
    \ val -= mod, *this; }\n    constexpr modular &operator*=(long long other) noexcept\
    \ { return (val *= other % mod) %= mod, *this; }\n    constexpr modular &operator*=(const\
    \ modular &other) noexcept { assert(mod_same(*this, other)); return (val *= other.val)\
    \ %= mod, *this; }\n    constexpr modular &operator/=(long long other) noexcept\
    \ { return *this *= inverse(modular{other, mod}); }\n    constexpr modular &operator/=(const\
    \ modular &other) noexcept { assert(mod_same(*this, other)); return *this *= inverse(other);\
    \ }\n    constexpr modular operator-() const noexcept { return modular(-val);\
    \ }\n    template <typename T> constexpr modular operator+(const T &other) const\
    \ noexcept { return modular(*this) += other; }\n    template <typename T> constexpr\
    \ modular operator-(const T &other) const noexcept { return modular(*this) -=\
    \ other; }\n    template <typename T> constexpr modular operator*(const T &other)\
    \ const noexcept { return modular(*this) *= other; }\n    template <typename T>\
    \ constexpr modular operator/(const T &other) const noexcept { return modular(*this)\
    \ /= other; }\n    constexpr bool operator==(const modular &other) const noexcept\
    \ { assert(mod_same(*this, other)); return val == other.val; }\n    constexpr\
    \ bool operator!=(const modular &other) const noexcept { assert(mod_same(*this,\
    \ other)); return val != other.val; }\n    constexpr bool operator!() const noexcept\
    \ { return !val; }\n    friend constexpr modular operator+(long long x, modular\
    \ y) noexcept { return modular(x + y.val, y.mod); }\n    friend constexpr modular\
    \ operator-(long long x, modular y) noexcept { return modular(x - y.val, y.mod);\
    \ }\n    friend constexpr modular operator*(long long x, modular y) noexcept {\
    \ return modular(x % y.mod * y.val, y.mod); }\n    friend constexpr modular operator/(long\
    \ long x, modular y) noexcept { return modular(x % y.mod * inverse(y).val, y.mod);\
    \ }\n    friend constexpr modular inverse(const modular &other) noexcept\n   \
    \ {\n        assert(other.mod && other.val);\n        long long a{other.mod},\
    \ b{other.val}, u{}, v{1}, t{};\n        while(b) t = a / b, a ^= b ^= (a -= t\
    \ * b) ^= b, u ^= v ^= (u -= t * v) ^= v;\n        return {u, other.mod};\n  \
    \  }\n    friend constexpr modular pow(modular other, long long e) noexcept\n\
    \    {\n        if(e < 0) e = e % (other.mod - 1) + other.mod - 1;\n        modular\
    \ res{1, other.mod};\n        while(e) { if(e & 1) res *= other; other *= other,\
    \ e >>= 1; }\n        return res;\n    }\n    friend std::ostream &operator<<(std::ostream\
    \ &os, const modular &other) noexcept { return os << other.val; }\n    friend\
    \ std::istream &operator>>(std::istream &is, modular &other) noexcept { long long\
    \ val; other = modular((is >> val, val)); return is; }\n}; // class modular\n"
  dependsOn: []
  isVerificationFile: false
  path: variant/modular.hpp
  requiredBy: []
  timestamp: '2020-11-28 14:35:40+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: variant/modular.hpp
layout: document
redirect_from:
- /library/variant/modular.hpp
- /library/variant/modular.hpp.html
title: variant/modular.hpp
---
