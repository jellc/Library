---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.8.6/x64/lib/python3.8/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.8.6/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.8.6/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 353, in update\n    raise BundleErrorAt(path, i + 1, \"found codes out\
    \ of include guard\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ deprecated/constexpr/binomial.hpp: line 53: found codes out of include guard\n"
  code: "#ifndef modint_hpp\n#define modint_hpp\n#include <cassert>\n#include <iostream>\n\
    \ntemplate <int mod>\nclass modint\n{\n    int val;\npublic:\n    constexpr modint()\
    \ noexcept : val{0} {}\n    constexpr modint(long long x) noexcept : val((x %=\
    \ mod) < 0 ? mod + x : x) {}\n    constexpr long long value() const noexcept {\
    \ return val; }\n    constexpr modint operator++(int) noexcept { modint t = *this;\
    \ return ++val, t; }\n    constexpr modint operator--(int) noexcept { modint t\
    \ = *this; return --val, t; }\n    constexpr modint &operator++() noexcept { return\
    \ ++val, *this; }\n    constexpr modint &operator--() noexcept { return --val,\
    \ *this; }\n    constexpr modint operator-() const noexcept { return modint(-val);\
    \ }\n    constexpr modint &operator+=(const modint &other) noexcept { return (val\
    \ += other.val) < mod ? 0 : val -= mod, *this; }\n    constexpr modint &operator-=(const\
    \ modint &other) noexcept { return (val += mod - other.val) < mod ? 0 : val -=\
    \ mod, *this; }\n    constexpr modint &operator*=(const modint &other) noexcept\
    \ { return val = (long long)val * other.val % mod, *this; }\n    constexpr modint\
    \ &operator/=(const modint &other) noexcept { return *this *= inverse(other);\
    \ }\n    constexpr modint operator+(const modint &other) const noexcept { return\
    \ modint(*this) += other; }\n    constexpr modint operator-(const modint &other)\
    \ const noexcept { return modint(*this) -= other; }\n    constexpr modint operator*(const\
    \ modint &other) const noexcept { return modint(*this) *= other; }\n    constexpr\
    \ modint operator/(const modint &other) const noexcept { return modint(*this)\
    \ /= other; }\n    constexpr bool operator==(const modint &other) const noexcept\
    \ { return val == other.val; }\n    constexpr bool operator!=(const modint &other)\
    \ const noexcept { return val != other.val; }\n    constexpr bool operator!()\
    \ const noexcept { return !val; }\n    friend constexpr modint operator+(long\
    \ long x, modint y) noexcept { return modint(x) + y; }\n    friend constexpr modint\
    \ operator-(long long x, modint y) noexcept { return modint(x) - y; }\n    friend\
    \ constexpr modint operator*(long long x, modint y) noexcept { return modint(x)\
    \ * y; }\n    friend constexpr modint operator/(long long x, modint y) noexcept\
    \ { return modint(x) / y; }\n    static constexpr modint inverse(const modint\
    \ &other) noexcept\n    {\n        assert(other != 0);\n        int a{mod}, b{other.val},\
    \ u{}, v{1}, t{};\n        while(b) t = a / b, a ^= b ^= (a -= t * b) ^= b, u\
    \ ^= v ^= (u -= t * v) ^= v;\n        return {u};\n    }\n    static constexpr\
    \ modint pow(modint other, long long e) noexcept\n    {\n        if(e < 0) e =\
    \ e % (mod - 1) + mod - 1;\n        modint res{1};\n        while(e) { if(e &\
    \ 1) res *= other; other *= other, e >>= 1; }\n        return res;\n    }\n  \
    \  friend std::ostream &operator<<(std::ostream &os, const modint &other) noexcept\
    \ { return os << other.val; }\n    friend std::istream &operator>>(std::istream\
    \ &is, modint &other) noexcept { long long val; other = {(is >> val, val)}; return\
    \ is; }\n}; // class modint\n\n#endif // modint_hpp\n\n#ifndef binomial_hpp\n\
    #define binomial_hpp\n\nnamespace binomial\n{\n    constexpr int mod = 1000000007;\n\
    \    using mint = modint<mod>;\n    namespace\n    {\n        namespace internal_helper\n\
    \        {\n            constexpr int N = 1 << 20;\n            constexpr int\
    \ loop_limit = 1 << 17;\n            struct fact_impl\n            {\n       \
    \         int _fact[N], _inv[N], _invfact[N];\n                constexpr fact_impl()\
    \ : _fact{1}, _inv{0, 1}, _invfact{1}\n                {\n                   \
    \ int itr = 1; while(itr < N) for(int j = 0; j < loop_limit && itr < N; ++itr,\
    \ ++j) _fact[itr] = (long long)_fact[itr - 1] * itr % mod;\n                 \
    \   itr = 2; while(itr < N) for(int j = 0; j < loop_limit && itr < N; ++itr, ++j)\
    \ _inv[itr] = mod - (long long)_inv[mod % itr] * (mod / itr) % mod;\n        \
    \            itr = 1; while(itr < N) for(int j = 0; j < loop_limit && itr < N;\
    \ ++itr, ++j) _invfact[itr] = (long long)_invfact[itr - 1] * _inv[itr] % mod;\n\
    \                }\n            }; // struct fact_impl\n            constexpr\
    \ fact_impl fact_impl_inst;\n            constexpr int fact_helper(int x) noexcept\
    \ { assert(x < (int)N); return x < 0 ? 0 : fact_impl_inst._fact[x]; }\n      \
    \      constexpr int invfact_helper(int x) noexcept { assert(x < (int)N); return\
    \ x < 0 ? 0 : fact_impl_inst._invfact[x]; }\n            constexpr int inv_helper(int\
    \ x) noexcept { assert(x < (int)N); return x < 0 ? 0 : fact_impl_inst._inv[x];\
    \ }\n        } // namespace internal_helper\n        constexpr mint fact(int x)\
    \ noexcept { return internal_helper::fact_helper(x); }\n        constexpr mint\
    \ invfact(int x) noexcept { return internal_helper::invfact_helper(x); }\n   \
    \ } // unnamed namespace\n    constexpr mint binom(int n, int k) noexcept { return\
    \ fact(n) * invfact(k) * invfact(n - k); }\n    constexpr mint fallfact(int n,\
    \ int k) noexcept { return fact(n) * invfact(n - k); }\n    constexpr mint risefact(int\
    \ n, int k) noexcept { return fallfact(n + k - 1, k); }\n    // time complexity:\
    \ O(min(n, k) * log(n))\n    constexpr mint stirling_2nd(int n, int k) noexcept\n\
    \    {\n        if(n < k) return 0;\n        mint res{};\n        for(int i{},\
    \ j{k}; j >= 0; ++i, --j)\n            if(i & 1) res -= mint::pow(j, n) * invfact(j)\
    \ * invfact(i);\n            else res += mint::pow(j, n) * invfact(j) * invfact(i);\n\
    \        return res;\n    };\n    // time complexity: O(min(n, k) * log(n))\n\
    \    constexpr mint bell(int n, int k) noexcept\n    {\n        if(n < k) k =\
    \ n;\n        mint res{}, alt{};\n        for(int i{}, j{k}; j >= 0; ++i, --j)\n\
    \        {\n            if(i & 1) alt -= invfact(i);\n            else alt +=\
    \ invfact(i);\n            res += alt * mint::pow(j, n) * invfact(j);\n      \
    \  }\n        return res;\n    }\n    namespace internal_helper {} // namespace\
    \ internal_helper\n} // namespace binomial\n\n#endif // binomial_hpp\n"
  dependsOn: []
  isVerificationFile: false
  path: deprecated/constexpr/binomial.hpp
  requiredBy: []
  timestamp: '2020-08-21 00:54:42+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: deprecated/constexpr/binomial.hpp
layout: document
redirect_from:
- /library/deprecated/constexpr/binomial.hpp
- /library/deprecated/constexpr/binomial.hpp.html
title: deprecated/constexpr/binomial.hpp
---
