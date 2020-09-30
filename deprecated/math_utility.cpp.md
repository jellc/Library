---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"deprecated/math_utility.cpp\"\n#include <bits/stdc++.h>\n\
    \nnamespace math\n{\n    template <class int_t> std::vector<int_t> prime_factorization(int_t\
    \ x)\n    {\n        std::vector<int_t> res(__builtin_ctzll(x), 2); x >>= __builtin_ctzll(x);\n\
    \        for(int_t p{3}; p * p <= x; p += 2) while(!(x % p)) x /= p, res.emplace_back(p);\n\
    \        if(x > 1) res.emplace_back(x); return res;\n    }\n    template <class\
    \ int_t> constexpr int_t gcd(int_t x, int_t y) { x = x > 0 ? x : -x, y = y > 0\
    \ ? y : -y; while(y) y ^= x ^= y ^= x %= y; return x; }\n    template <class int_t>\
    \ constexpr int_t lcm(int_t x, int_t y) { return x ? x / gcd(x, y) * y : 0; }\n\
    \    // a tuple (g, x, y) s.t. g = gcd(a, b) && ax + by = g.\n    template <class\
    \ int_t> constexpr std::tuple<int_t, int_t, int_t> ext_gcd(int_t a, int_t b)\n\
    \    {\n        int_t sgn_a{a >= 0 ? 1 : (a = -a, 0)}, sgn_b{b >= 0 ? 1 : (b =\
    \ -b, 0)};\n        int_t p{1}, q{}, r{}, s{1}, t{};\n        while(b)\n     \
    \   {\n            r ^= p ^= r ^= p -= (t = a / b) * r;\n            s ^= q ^=\
    \ s ^= q -= t * s;\n            b ^= a ^= b ^= a %= b;\n        }\n        return\
    \ std::tuple<int_t, int_t, int_t>(a, sgn_a ? p : -p, sgn_b ? q : -q);\n    }\n\
    \    // a pair (x, y) s.t. \"x mod y\" is true iff \"k mod m\" && \"l mod n\"\
    , (-1, -1) if not exist.\n    template <class int_t>\n    constexpr std::pair<int_t,\
    \ int_t> modulo_composition(int_t k, int_t m, int_t l, int_t n)\n    {\n     \
    \   assert(m > 0 and n > 0);\n        int_t g, x, y; std::tie(g, x, y) = ext_gcd(m,\
    \ n);\n        k += ((k %= m) < 0) * m, l += ((l %= n) < 0) * n;\n        int_t\
    \ s = k / g, t = l / g, r = k % g;\n        if(r != l % g) return std::pair<int_t,\
    \ int_t>{-1, -1};\n        int_t lcm = m / g * n;\n        return std::pair<int_t,\
    \ int_t>{(m * x % lcm * t % lcm + n * y % lcm * s % lcm + r + lcm * 2) % lcm,\
    \ lcm};\n    }\n} // namespace math\n"
  code: "#include <bits/stdc++.h>\n\nnamespace math\n{\n    template <class int_t>\
    \ std::vector<int_t> prime_factorization(int_t x)\n    {\n        std::vector<int_t>\
    \ res(__builtin_ctzll(x), 2); x >>= __builtin_ctzll(x);\n        for(int_t p{3};\
    \ p * p <= x; p += 2) while(!(x % p)) x /= p, res.emplace_back(p);\n        if(x\
    \ > 1) res.emplace_back(x); return res;\n    }\n    template <class int_t> constexpr\
    \ int_t gcd(int_t x, int_t y) { x = x > 0 ? x : -x, y = y > 0 ? y : -y; while(y)\
    \ y ^= x ^= y ^= x %= y; return x; }\n    template <class int_t> constexpr int_t\
    \ lcm(int_t x, int_t y) { return x ? x / gcd(x, y) * y : 0; }\n    // a tuple\
    \ (g, x, y) s.t. g = gcd(a, b) && ax + by = g.\n    template <class int_t> constexpr\
    \ std::tuple<int_t, int_t, int_t> ext_gcd(int_t a, int_t b)\n    {\n        int_t\
    \ sgn_a{a >= 0 ? 1 : (a = -a, 0)}, sgn_b{b >= 0 ? 1 : (b = -b, 0)};\n        int_t\
    \ p{1}, q{}, r{}, s{1}, t{};\n        while(b)\n        {\n            r ^= p\
    \ ^= r ^= p -= (t = a / b) * r;\n            s ^= q ^= s ^= q -= t * s;\n    \
    \        b ^= a ^= b ^= a %= b;\n        }\n        return std::tuple<int_t, int_t,\
    \ int_t>(a, sgn_a ? p : -p, sgn_b ? q : -q);\n    }\n    // a pair (x, y) s.t.\
    \ \"x mod y\" is true iff \"k mod m\" && \"l mod n\", (-1, -1) if not exist.\n\
    \    template <class int_t>\n    constexpr std::pair<int_t, int_t> modulo_composition(int_t\
    \ k, int_t m, int_t l, int_t n)\n    {\n        assert(m > 0 and n > 0);\n   \
    \     int_t g, x, y; std::tie(g, x, y) = ext_gcd(m, n);\n        k += ((k %= m)\
    \ < 0) * m, l += ((l %= n) < 0) * n;\n        int_t s = k / g, t = l / g, r =\
    \ k % g;\n        if(r != l % g) return std::pair<int_t, int_t>{-1, -1};\n   \
    \     int_t lcm = m / g * n;\n        return std::pair<int_t, int_t>{(m * x %\
    \ lcm * t % lcm + n * y % lcm * s % lcm + r + lcm * 2) % lcm, lcm};\n    }\n}\
    \ // namespace math\n"
  dependsOn: []
  isVerificationFile: false
  path: deprecated/math_utility.cpp
  requiredBy: []
  timestamp: '2020-08-08 03:26:46+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: deprecated/math_utility.cpp
layout: document
redirect_from:
- /library/deprecated/math_utility.cpp
- /library/deprecated/math_utility.cpp.html
title: deprecated/math_utility.cpp
---
