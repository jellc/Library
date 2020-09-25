---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/rolling_hash.hpp
    title: string/rolling_hash.hpp
  - icon: ':heavy_check_mark:'
    path: utils/random_number_generator.hpp
    title: utils/random_number_generator.hpp
  - icon: ':heavy_check_mark:'
    path: utils/binary_search.hpp
    title: utils/binary_search.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/zalgorithm
    links:
    - https://judge.yosupo.jp/problem/zalgorithm
  bundledCode: "#line 1 \"test/library-checker/zalgorithm_2.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/zalgorithm\"\n#include <iostream>\n#include\
    \ <string>\n\n#line 2 \"string/rolling_hash.hpp\"\n#include <algorithm>\n#include\
    \ <cassert>\n#include <vector>\n\n#line 2 \"utils/random_number_generator.hpp\"\
    \n#include <random>\ntemplate <typename num_type> class random_number_generator\
    \ {\n  typename std::conditional<std::is_integral<num_type>::value,\n        \
    \                    std::uniform_int_distribution<num_type>,\n              \
    \              std::uniform_real_distribution<num_type>>::type\n      unif;\n\n\
    \  std::mt19937 engine;\n\n public:\n  random_number_generator(num_type min =\
    \ std::numeric_limits<num_type>::min(),\n                          num_type max\
    \ = std::numeric_limits<num_type>::max())\n      : unif(min, max), engine(std::random_device{}())\
    \ {}\n\n  num_type min() const { return unif.min(); }\n\n  num_type max() const\
    \ { return unif.max(); }\n\n  // generate a random number in [min(), max()].\n\
    \  num_type operator()() { return unif(engine); }\n};\n#line 7 \"string/rolling_hash.hpp\"\
    \n\nstruct rolling_hashed {\n  using u64 = uint_least64_t;\n  using u128 = __uint128_t;\n\
    \n  constexpr static u64 mod = (1ull << 61) - 1;\n  static u64 base;\n\n  u64\
    \ value = 0;\n  size_t length = 0;\n\n  rolling_hashed() = default;\n\n  template\
    \ <class char_type, typename std::enable_if<std::is_convertible<\n           \
    \                      char_type, u64>::value>::type * = nullptr>\n  rolling_hashed(char_type\
    \ c) : value(u64(c) + 1), length(1) {}\n\n  rolling_hashed(u64 value, size_t length)\
    \ : value(value), length(length) {}\n\n  operator std::pair<u64, size_t>() const\
    \ { return {value, length}; }\n\n  bool operator==(const rolling_hashed &rhs)\
    \ const {\n    return value == rhs.value && length == rhs.length;\n  }\n\n  bool\
    \ operator!=(const rolling_hashed &rhs) const { return !operator==(rhs); }\n\n\
    \  rolling_hashed operator+(const rolling_hashed &rhs) const {\n    return {plus(value,\
    \ mult(rhs.value, base_pow(length))),\n            length + rhs.length};\n  }\n\
    \n  rolling_hashed operator+=(const rolling_hashed &rhs) {\n    return *this =\
    \ operator+(rhs);\n  }\n\n  rolling_hashed operator-(const rolling_hashed &rhs)\
    \ const {\n    assert(!(length < rhs.length));\n    return {minus(value, mult(rhs.value,\
    \ base_pow(length - rhs.length))),\n            length - rhs.length};\n  }\n\n\
    \  rolling_hashed operator-=(const rolling_hashed &rhs) {\n    return *this =\
    \ operator-(rhs);\n  }\n\n  static u64 base_pow(size_t exp) {\n    static std::vector<u64>\
    \ pow{1};\n    while (pow.size() <= exp) {\n      pow.emplace_back(mult(pow.back(),\
    \ base));\n    }\n    return pow[exp];\n  }\n\n private:\n  static u64 plus(u64\
    \ lhs, u64 rhs) {\n    return (lhs += rhs) < mod ? lhs : lhs - mod;\n  }\n\n \
    \ static u64 minus(u64 lhs, u64 rhs) {\n    return (lhs -= rhs) < mod ? lhs :\
    \ lhs + mod;\n  }\n\n  static u64 mult(u128 lhs, u64 rhs) {\n    lhs *= rhs;\n\
    \    lhs = (lhs >> 61) + (lhs & mod);\n    return lhs < mod ? lhs : lhs - mod;\n\
    \  }\n};\n\nrolling_hashed::u64 rolling_hashed::base =\n    random_number_generator<u64>(1\
    \ << 30, mod - 1)();\n\ntemplate <class str_type> struct rolling_hash_table {\n\
    \  constexpr static size_t npos = -1;\n\n  rolling_hash_table() = default;\n\n\
    \  rolling_hash_table(str_type str) {\n    std::reverse(std::begin(str), std::end(str));\n\
    \    for (auto &&c : str) suffix.emplace_back(rolling_hashed{c} + suffix.back());\n\
    \    std::reverse(suffix.begin(), suffix.end());\n  }\n\n  size_t size() const\
    \ { return suffix.size() - 1; }\n\n  rolling_hashed substr(size_t pos = 0, size_t\
    \ n = npos) const {\n    assert(!(size() < pos));\n    return suffix[pos] - suffix[pos\
    \ + std::min(n, size() - pos)];\n  }\n\n private:\n  std::vector<rolling_hashed>\
    \ suffix{{}};\n};\n#line 2 \"utils/binary_search.hpp\"\n#if __cplusplus >= 201703L\n\
    #line 4 \"utils/binary_search.hpp\"\n#include <cmath>\n#line 6 \"utils/binary_search.hpp\"\
    \nnamespace workspace {\n// binary search on discrete range.\ntemplate <class\
    \ iter_type, class pred_type>\nstd::enable_if_t<\n    std::is_convertible_v<std::invoke_result_t<pred_type,\
    \ iter_type>, bool>,\n    iter_type>\nbinary_search(iter_type ok, iter_type ng,\
    \ pred_type pred) {\n  assert(ok != ng);\n  __int128_t dist(ng - ok);\n  while\
    \ (dist > 1 || dist < -1) {\n    iter_type mid(ok + dist / 2);\n    if (pred(mid))\n\
    \      ok = mid, dist -= dist / 2;\n    else\n      ng = mid, dist /= 2;\n  }\n\
    \  return ok;\n}\n// parallel binary search on discrete range.\ntemplate <class\
    \ iter_type, class pred_type>\nstd::enable_if_t<std::is_convertible_v<\n     \
    \                std::invoke_result_t<pred_type, std::vector<iter_type>>,\n  \
    \                   std::vector<bool>>,\n                 std::vector<iter_type>>\n\
    binary_search(std::vector<std::pair<iter_type, iter_type>> ends,\n           \
    \   pred_type pred) {\n  std::vector<iter_type> mids(ends.size());\n  for (;;)\
    \ {\n    bool all_found = true;\n    for (size_t i{}; i != ends.size(); ++i) {\n\
    \      auto [ok, ng] = ends[i];\n      iter_type mid(ok + (ng - ok) / 2);\n  \
    \    if (mids[i] != mid) {\n        all_found = false;\n        mids[i] = mid;\n\
    \      }\n    }\n    if (all_found) break;\n    auto res = pred(mids);\n    for\
    \ (size_t i{}; i != ends.size(); ++i) {\n      (res[i] ? ends[i].first : ends[i].second)\
    \ = mids[i];\n    }\n  }\n  return mids;\n}\n// binary search on real numbers.\n\
    template <class real_type, class pred_type>\nstd::enable_if_t<\n    std::is_convertible_v<std::invoke_result_t<pred_type,\
    \ real_type>, bool>,\n    real_type>\nbinary_search(real_type ok, real_type ng,\
    \ const real_type eps, pred_type pred) {\n  assert(ok != ng);\n  while (ok + eps\
    \ < ng || ng + eps < ok) {\n    real_type mid{(ok + ng) / 2};\n    (pred(mid)\
    \ ? ok : ng) = mid;\n  }\n  return ok;\n}\n// parallel binary search on real numbers.\n\
    template <class real_type, class pred_type>\nstd::enable_if_t<std::is_convertible_v<\n\
    \                     std::invoke_result_t<pred_type, std::vector<real_type>>,\n\
    \                     std::vector<bool>>,\n                 std::vector<real_type>>\n\
    binary_search(std::vector<std::pair<real_type, real_type>> ends,\n           \
    \   const real_type eps, pred_type pred) {\n  std::vector<real_type> mids(ends.size());\n\
    \  for (;;) {\n    bool all_found = true;\n    for (size_t i{}; i != ends.size();\
    \ ++i) {\n      auto [ok, ng] = ends[i];\n      if (ok + eps < ng || ng + eps\
    \ < ok) {\n        all_found = false;\n        mids[i] = (ok + ng) / 2;\n    \
    \  }\n    }\n    if (all_found) break;\n    auto res = pred(mids);\n    for (size_t\
    \ i{}; i != ends.size(); ++i) {\n      (res[i] ? ends[i].first : ends[i].second)\
    \ = mids[i];\n    }\n  }\n  return mids;\n}\n}  // namespace workspace\n#endif\n\
    #line 7 \"test/library-checker/zalgorithm_2.test.cpp\"\n\nint main() {\n  std::string\
    \ s;\n  std::cin >> s;\n  rolling_hash_table hash(s);\n  for (size_t i = 0; i\
    \ < size(s); ++i) {\n    if (i) std::cout << \" \";\n    std::cout << workspace::binary_search(\n\
    \        size_t(0), size(s) + 1, [&](size_t len) -> bool {\n          return hash.substr(0,\
    \ len) == hash.substr(i, len);\n        });\n  }\n  std::cout << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/zalgorithm\"\n#include\
    \ <iostream>\n#include <string>\n\n#include \"string/rolling_hash.hpp\"\n#include\
    \ \"utils/binary_search.hpp\"\n\nint main() {\n  std::string s;\n  std::cin >>\
    \ s;\n  rolling_hash_table hash(s);\n  for (size_t i = 0; i < size(s); ++i) {\n\
    \    if (i) std::cout << \" \";\n    std::cout << workspace::binary_search(\n\
    \        size_t(0), size(s) + 1, [&](size_t len) -> bool {\n          return hash.substr(0,\
    \ len) == hash.substr(i, len);\n        });\n  }\n  std::cout << \"\\n\";\n}\n"
  dependsOn:
  - string/rolling_hash.hpp
  - utils/random_number_generator.hpp
  - utils/binary_search.hpp
  isVerificationFile: true
  path: test/library-checker/zalgorithm_2.test.cpp
  requiredBy: []
  timestamp: '2020-09-25 13:36:45+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/library-checker/zalgorithm_2.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/zalgorithm_2.test.cpp
- /verify/test/library-checker/zalgorithm_2.test.cpp.html
title: test/library-checker/zalgorithm_2.test.cpp
---
