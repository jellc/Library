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
    links: []
  bundledCode: '#line 2 "alias.hpp"

    #include <cstdint>

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

    }  // namespace workspace

    '
  code: '#pragma once

    #include <cstdint>

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

    }  // namespace workspace

    '
  dependsOn: []
  isVerificationFile: false
  path: alias.hpp
  requiredBy:
  - template.cpp
  timestamp: '2020-09-25 13:06:28+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: alias.hpp
layout: document
redirect_from:
- /library/alias.hpp
- /library/alias.hpp.html
title: alias.hpp
---
