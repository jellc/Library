---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"algebra/convolution/number_theoretic_transform.hpp\"\n\n\
    \n\n#include <algorithm>\n#include <cassert>\n#include <iostream>\n#include <vector>\n\
    \nnamespace number_theoretic_transform\n{\n    constexpr int mod = 998244353;\n\
    \    constexpr int primitive = 3;\n\n    class modint\n    {\n        int val;\n\
    \    public:\n        constexpr modint() noexcept : val{0} {}\n        constexpr\
    \ modint(long long x) noexcept : val((x %= mod) < 0 ? mod + x : x) {}\n      \
    \  constexpr long long value() const noexcept { return val; }\n        constexpr\
    \ modint operator++(int) noexcept { modint t = *this; return ++val, t; }\n   \
    \     constexpr modint operator--(int) noexcept { modint t = *this; return --val,\
    \ t; }\n        constexpr modint &operator++() noexcept { return ++val, *this;\
    \ }\n        constexpr modint &operator--() noexcept { return --val, *this; }\n\
    \        constexpr modint operator-() const noexcept { return modint(-val); }\n\
    \        constexpr modint &operator+=(const modint &other) noexcept { return (val\
    \ += other.val) < mod ? 0 : val -= mod, *this; }\n        constexpr modint &operator-=(const\
    \ modint &other) noexcept { return (val += mod - other.val) < mod ? 0 : val -=\
    \ mod, *this; }\n        constexpr modint &operator*=(const modint &other) noexcept\
    \ { return val = (long long)val * other.val % mod, *this; }\n        constexpr\
    \ modint &operator/=(const modint &other) noexcept { return *this *= inverse(other);\
    \ }\n        constexpr modint operator+(const modint &other) const noexcept {\
    \ return modint(*this) += other; }\n        constexpr modint operator-(const modint\
    \ &other) const noexcept { return modint(*this) -= other; }\n        constexpr\
    \ modint operator*(const modint &other) const noexcept { return modint(*this)\
    \ *= other; }\n        constexpr modint operator/(const modint &other) const noexcept\
    \ { return modint(*this) /= other; }\n        constexpr bool operator==(const\
    \ modint &other) const noexcept { return val == other.val; }\n        constexpr\
    \ bool operator!=(const modint &other) const noexcept { return val != other.val;\
    \ }\n        constexpr bool operator!() const noexcept { return !val; }\n    \
    \    friend constexpr modint operator+(long long x, modint y) noexcept { return\
    \ modint(x) + y; }\n        friend constexpr modint operator-(long long x, modint\
    \ y) noexcept { return modint(x) - y; }\n        friend constexpr modint operator*(long\
    \ long x, modint y) noexcept { return modint(x) * y; }\n        friend constexpr\
    \ modint operator/(long long x, modint y) noexcept { return modint(x) / y; }\n\
    \        static constexpr modint inverse(const modint &other) noexcept\n     \
    \   {\n            assert(other != 0);\n            int a{mod}, b{other.val},\
    \ u{}, v{1}, t{};\n            while(b) t = a / b, a ^= b ^= (a -= t * b) ^= b,\
    \ u ^= v ^= (u -= t * v) ^= v;\n            return {u};\n        }\n        static\
    \ constexpr modint pow(modint other, long long e) noexcept\n        {\n      \
    \      if(e < 0) e = e % (mod - 1) + mod - 1;\n            modint res{1};\n  \
    \          while(e) { if(e & 1) res *= other; other *= other, e >>= 1; }\n   \
    \         return res;\n        }\n        friend std::ostream &operator<<(std::ostream\
    \ &os, const modint &other) noexcept { return os << other.val; }\n        friend\
    \ std::istream &operator>>(std::istream &is, modint &other) noexcept { long long\
    \ val; other = {(is >> val, val)}; return is; }\n    }; // class modint\n\n  \
    \  class zeta_calc\n    {\n        static constexpr size_t n = __builtin_ctz(mod\
    \ - 1);\n        modint _zeta[n + 1];\n      public:\n        constexpr zeta_calc()\
    \ : _zeta{}\n        {\n            _zeta[n] = modint::pow(modint(primitive),\
    \ (mod - 1) / (1 << n));\n            for(size_t i{n}; i; --i) _zeta[i - 1] =\
    \ _zeta[i] * _zeta[i];\n        }\n        constexpr modint operator[](size_t\
    \ k) const { return _zeta[k]; }\n    }; // class zeta_calc\n    constexpr zeta_calc\
    \ zeta;\n\n    class inv_calc\n    {\n        static constexpr size_t n = __builtin_ctz(mod\
    \ - 1);\n        modint _inv[n + 1];\n      public:\n        constexpr inv_calc()\
    \ : _inv{1, (mod + 1) / 2} { for(size_t i{1}; i < n; ++i) _inv[i + 1] = _inv[i]\
    \ * _inv[1]; }\n        constexpr modint operator[](size_t k) const { return _inv[k];\
    \ }\n    }; // class inv_calc\n    constexpr inv_calc inv;\n\n    using poly_t\
    \ = std::vector<modint>;\n\n    void discrete_Fourier_transform(poly_t &f)\n \
    \   {\n        const size_t n{f.size()}, mask{n - 1};\n        assert(__builtin_popcount(n)\
    \ == 1); // degree of f must be a power of two.\n        static poly_t g; g.resize(n);\n\
    \        for(size_t i{n >> 1}, ii{1}; i; i >>= 1, ++ii, swap(f, g))\n        {\n\
    \            modint powzeta{1};\n            for(size_t j{}; j < n; powzeta *=\
    \ zeta[ii])\n            {\n                for(size_t k{}, x{mask & j << 1},\
    \ y{mask & (i + (j << 1))}; k < i; ++k, ++j, ++x, ++y)\n                {\n  \
    \                  g[j] = f[x] + powzeta * f[y];\n                }\n        \
    \    }\n        }\n    }\n\n    void inverse_discrete_Fourier_transform(poly_t\
    \ &f)\n    {\n        discrete_Fourier_transform(f), reverse(next(f.begin()),\
    \ f.end());\n        const size_t k = __builtin_ctz(f.size()); for(modint &e :\
    \ f) e *= inv[k];\n    }\n\n    poly_t convolute(poly_t f, poly_t g)\n    {\n\
    \        if(f.empty() || g.empty()) return poly_t();\n        const size_t deg_f{f.size()\
    \ - 1}, deg_g{g.size() - 1}, deg_h{deg_f + deg_g}, n(1u << (32 - __builtin_clz(deg_h)));\n\
    \        static poly_t h;\n        f.resize(n, 0), g.resize(n, 0), h.resize(n);\n\
    \        discrete_Fourier_transform(f), discrete_Fourier_transform(g);\n     \
    \   for(size_t i{}; i < n; ++i) h[i] = f[i] * g[i];\n        inverse_discrete_Fourier_transform(h);\
    \ h.resize(deg_h + 1);\n        return h;\n    }\n} // namespace Number_theoretic_transform\n\
    \n\n"
  code: "#ifndef number_theoretic_transform_hpp\n#define number_theoretic_transform_hpp\n\
    \n#include <algorithm>\n#include <cassert>\n#include <iostream>\n#include <vector>\n\
    \nnamespace number_theoretic_transform\n{\n    constexpr int mod = 998244353;\n\
    \    constexpr int primitive = 3;\n\n    class modint\n    {\n        int val;\n\
    \    public:\n        constexpr modint() noexcept : val{0} {}\n        constexpr\
    \ modint(long long x) noexcept : val((x %= mod) < 0 ? mod + x : x) {}\n      \
    \  constexpr long long value() const noexcept { return val; }\n        constexpr\
    \ modint operator++(int) noexcept { modint t = *this; return ++val, t; }\n   \
    \     constexpr modint operator--(int) noexcept { modint t = *this; return --val,\
    \ t; }\n        constexpr modint &operator++() noexcept { return ++val, *this;\
    \ }\n        constexpr modint &operator--() noexcept { return --val, *this; }\n\
    \        constexpr modint operator-() const noexcept { return modint(-val); }\n\
    \        constexpr modint &operator+=(const modint &other) noexcept { return (val\
    \ += other.val) < mod ? 0 : val -= mod, *this; }\n        constexpr modint &operator-=(const\
    \ modint &other) noexcept { return (val += mod - other.val) < mod ? 0 : val -=\
    \ mod, *this; }\n        constexpr modint &operator*=(const modint &other) noexcept\
    \ { return val = (long long)val * other.val % mod, *this; }\n        constexpr\
    \ modint &operator/=(const modint &other) noexcept { return *this *= inverse(other);\
    \ }\n        constexpr modint operator+(const modint &other) const noexcept {\
    \ return modint(*this) += other; }\n        constexpr modint operator-(const modint\
    \ &other) const noexcept { return modint(*this) -= other; }\n        constexpr\
    \ modint operator*(const modint &other) const noexcept { return modint(*this)\
    \ *= other; }\n        constexpr modint operator/(const modint &other) const noexcept\
    \ { return modint(*this) /= other; }\n        constexpr bool operator==(const\
    \ modint &other) const noexcept { return val == other.val; }\n        constexpr\
    \ bool operator!=(const modint &other) const noexcept { return val != other.val;\
    \ }\n        constexpr bool operator!() const noexcept { return !val; }\n    \
    \    friend constexpr modint operator+(long long x, modint y) noexcept { return\
    \ modint(x) + y; }\n        friend constexpr modint operator-(long long x, modint\
    \ y) noexcept { return modint(x) - y; }\n        friend constexpr modint operator*(long\
    \ long x, modint y) noexcept { return modint(x) * y; }\n        friend constexpr\
    \ modint operator/(long long x, modint y) noexcept { return modint(x) / y; }\n\
    \        static constexpr modint inverse(const modint &other) noexcept\n     \
    \   {\n            assert(other != 0);\n            int a{mod}, b{other.val},\
    \ u{}, v{1}, t{};\n            while(b) t = a / b, a ^= b ^= (a -= t * b) ^= b,\
    \ u ^= v ^= (u -= t * v) ^= v;\n            return {u};\n        }\n        static\
    \ constexpr modint pow(modint other, long long e) noexcept\n        {\n      \
    \      if(e < 0) e = e % (mod - 1) + mod - 1;\n            modint res{1};\n  \
    \          while(e) { if(e & 1) res *= other; other *= other, e >>= 1; }\n   \
    \         return res;\n        }\n        friend std::ostream &operator<<(std::ostream\
    \ &os, const modint &other) noexcept { return os << other.val; }\n        friend\
    \ std::istream &operator>>(std::istream &is, modint &other) noexcept { long long\
    \ val; other = {(is >> val, val)}; return is; }\n    }; // class modint\n\n  \
    \  class zeta_calc\n    {\n        static constexpr size_t n = __builtin_ctz(mod\
    \ - 1);\n        modint _zeta[n + 1];\n      public:\n        constexpr zeta_calc()\
    \ : _zeta{}\n        {\n            _zeta[n] = modint::pow(modint(primitive),\
    \ (mod - 1) / (1 << n));\n            for(size_t i{n}; i; --i) _zeta[i - 1] =\
    \ _zeta[i] * _zeta[i];\n        }\n        constexpr modint operator[](size_t\
    \ k) const { return _zeta[k]; }\n    }; // class zeta_calc\n    constexpr zeta_calc\
    \ zeta;\n\n    class inv_calc\n    {\n        static constexpr size_t n = __builtin_ctz(mod\
    \ - 1);\n        modint _inv[n + 1];\n      public:\n        constexpr inv_calc()\
    \ : _inv{1, (mod + 1) / 2} { for(size_t i{1}; i < n; ++i) _inv[i + 1] = _inv[i]\
    \ * _inv[1]; }\n        constexpr modint operator[](size_t k) const { return _inv[k];\
    \ }\n    }; // class inv_calc\n    constexpr inv_calc inv;\n\n    using poly_t\
    \ = std::vector<modint>;\n\n    void discrete_Fourier_transform(poly_t &f)\n \
    \   {\n        const size_t n{f.size()}, mask{n - 1};\n        assert(__builtin_popcount(n)\
    \ == 1); // degree of f must be a power of two.\n        static poly_t g; g.resize(n);\n\
    \        for(size_t i{n >> 1}, ii{1}; i; i >>= 1, ++ii, swap(f, g))\n        {\n\
    \            modint powzeta{1};\n            for(size_t j{}; j < n; powzeta *=\
    \ zeta[ii])\n            {\n                for(size_t k{}, x{mask & j << 1},\
    \ y{mask & (i + (j << 1))}; k < i; ++k, ++j, ++x, ++y)\n                {\n  \
    \                  g[j] = f[x] + powzeta * f[y];\n                }\n        \
    \    }\n        }\n    }\n\n    void inverse_discrete_Fourier_transform(poly_t\
    \ &f)\n    {\n        discrete_Fourier_transform(f), reverse(next(f.begin()),\
    \ f.end());\n        const size_t k = __builtin_ctz(f.size()); for(modint &e :\
    \ f) e *= inv[k];\n    }\n\n    poly_t convolute(poly_t f, poly_t g)\n    {\n\
    \        if(f.empty() || g.empty()) return poly_t();\n        const size_t deg_f{f.size()\
    \ - 1}, deg_g{g.size() - 1}, deg_h{deg_f + deg_g}, n(1u << (32 - __builtin_clz(deg_h)));\n\
    \        static poly_t h;\n        f.resize(n, 0), g.resize(n, 0), h.resize(n);\n\
    \        discrete_Fourier_transform(f), discrete_Fourier_transform(g);\n     \
    \   for(size_t i{}; i < n; ++i) h[i] = f[i] * g[i];\n        inverse_discrete_Fourier_transform(h);\
    \ h.resize(deg_h + 1);\n        return h;\n    }\n} // namespace Number_theoretic_transform\n\
    \n#endif // number_theoretic_transform_hpp\n"
  dependsOn: []
  isVerificationFile: false
  path: algebra/convolution/number_theoretic_transform.hpp
  requiredBy: []
  timestamp: '2020-06-27 01:08:32+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: algebra/convolution/number_theoretic_transform.hpp
layout: document
redirect_from:
- /library/algebra/convolution/number_theoretic_transform.hpp
- /library/algebra/convolution/number_theoretic_transform.hpp.html
title: algebra/convolution/number_theoretic_transform.hpp
---
