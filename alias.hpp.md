---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: template.cpp
    title: template.cpp
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: '#line 2 "alias.hpp"

    #include <functional>

    #include <queue>

    #include <stack>

    #include <vector>

    namespace workspace {

    constexpr char eol = ''\n'';

    using namespace std;

    using i32 = int_least32_t;

    using i64 = int_least64_t;

    using i128 = __int128_t;

    using u32 = uint_least32_t;

    using u64 = uint_least64_t;

    using u128 = __uint128_t;

    template <class T, class Comp = less<T>>

    using priority_queue = std::priority_queue<T, vector<T>, Comp>;

    template <class T> using stack = std::stack<T, vector<T>>;

    constexpr i32 clz32(const u32 &n) noexcept { return __builtin_clz(n); }

    constexpr i32 clz64(const u64 &n) noexcept { return __builtin_clzll(n); }

    constexpr i32 ctz(const u64 &n) noexcept { return __builtin_ctzll(n); }

    constexpr i32 popcnt(const u64 &n) noexcept { return __builtin_popcountll(n);
    }

    }  // namespace workspace

    '
  code: '#pragma once

    #include <functional>

    #include <queue>

    #include <stack>

    #include <vector>

    namespace workspace {

    constexpr char eol = ''\n'';

    using namespace std;

    using i32 = int_least32_t;

    using i64 = int_least64_t;

    using i128 = __int128_t;

    using u32 = uint_least32_t;

    using u64 = uint_least64_t;

    using u128 = __uint128_t;

    template <class T, class Comp = less<T>>

    using priority_queue = std::priority_queue<T, vector<T>, Comp>;

    template <class T> using stack = std::stack<T, vector<T>>;

    constexpr i32 clz32(const u32 &n) noexcept { return __builtin_clz(n); }

    constexpr i32 clz64(const u64 &n) noexcept { return __builtin_clzll(n); }

    constexpr i32 ctz(const u64 &n) noexcept { return __builtin_ctzll(n); }

    constexpr i32 popcnt(const u64 &n) noexcept { return __builtin_popcountll(n);
    }

    }  // namespace workspace

    '
  dependsOn: []
  isVerificationFile: false
  path: alias.hpp
  requiredBy:
  - template.cpp
  timestamp: '2020-09-17 20:09:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: alias.hpp
layout: document
redirect_from:
- /library/alias.hpp
- /library/alias.hpp.html
title: alias.hpp
---
