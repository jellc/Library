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
  bundledCode: '#line 2 "gcc_builtin.hpp"

    #include <cstdint>

    namespace workspace {

    constexpr int clz32(const uint32_t &n) noexcept { return __builtin_clz(n); }

    constexpr int clz64(const uint64_t &n) noexcept{ return __builtin_clzll(n); }

    constexpr int ctz(const uint64_t &n) noexcept { return __builtin_ctzll(n); }

    constexpr int popcnt(const uint64_t &n) noexcept { return __builtin_popcountll(n);
    }

    } // namespace workspace

    '
  code: '#pragma once

    #include <cstdint>

    namespace workspace {

    constexpr int clz32(const uint32_t &n) noexcept { return __builtin_clz(n); }

    constexpr int clz64(const uint64_t &n) noexcept{ return __builtin_clzll(n); }

    constexpr int ctz(const uint64_t &n) noexcept { return __builtin_ctzll(n); }

    constexpr int popcnt(const uint64_t &n) noexcept { return __builtin_popcountll(n);
    }

    } // namespace workspace

    '
  dependsOn: []
  isVerificationFile: false
  path: gcc_builtin.hpp
  requiredBy:
  - template.cpp
  timestamp: '2020-08-25 21:59:09+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: gcc_builtin.hpp
layout: document
redirect_from:
- /library/gcc_builtin.hpp
- /library/gcc_builtin.hpp.html
title: gcc_builtin.hpp
---
