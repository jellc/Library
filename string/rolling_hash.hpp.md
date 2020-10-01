---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: utils/random_number_generator.hpp
    title: utils/random_number_generator.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/pattern_search.test.cpp
    title: test/aizu-online-judge/pattern_search.test.cpp
  - icon: ':x:'
    path: test/library-checker/zalgorithm_2.test.cpp
    title: test/library-checker/zalgorithm_2.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 2 \"string/rolling_hash.hpp\"\n#include <algorithm>\n#include\
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
    \ suffix{{}};\n};\n"
  code: "#pragma once\n#include <algorithm>\n#include <cassert>\n#include <vector>\n\
    \n#include \"utils/random_number_generator.hpp\"\n\nstruct rolling_hashed {\n\
    \  using u64 = uint_least64_t;\n  using u128 = __uint128_t;\n\n  constexpr static\
    \ u64 mod = (1ull << 61) - 1;\n  static u64 base;\n\n  u64 value = 0;\n  size_t\
    \ length = 0;\n\n  rolling_hashed() = default;\n\n  template <class char_type,\
    \ typename std::enable_if<std::is_convertible<\n                             \
    \    char_type, u64>::value>::type * = nullptr>\n  rolling_hashed(char_type c)\
    \ : value(u64(c) + 1), length(1) {}\n\n  rolling_hashed(u64 value, size_t length)\
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
    \ suffix{{}};\n};\n"
  dependsOn:
  - utils/random_number_generator.hpp
  isVerificationFile: false
  path: string/rolling_hash.hpp
  requiredBy: []
  timestamp: '2020-09-22 22:28:34+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/library-checker/zalgorithm_2.test.cpp
  - test/aizu-online-judge/pattern_search.test.cpp
documentation_of: string/rolling_hash.hpp
layout: document
redirect_from:
- /library/string/rolling_hash.hpp
- /library/string/rolling_hash.hpp.html
title: string/rolling_hash.hpp
---
