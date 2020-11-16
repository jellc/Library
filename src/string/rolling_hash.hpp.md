---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: src/utils/random_number_generator.hpp
    title: src/utils/random_number_generator.hpp
  - icon: ':question:'
    path: src/utils/sfinae.hpp
    title: src/utils/sfinae.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/aizu-online-judge/ALDS1_14_C.test.cpp
    title: test/aizu-online-judge/ALDS1_14_C.test.cpp
  - icon: ':x:'
    path: test/library-checker/zalgorithm_2.test.cpp
    title: test/library-checker/zalgorithm_2.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: Rolling Hash
    links: []
  bundledCode: "#line 2 \"src/string/rolling_hash.hpp\"\n\n/*\n * @file rolling_hash.hpp\n\
    \ * @brief Rolling Hash\n */\n\n#include <algorithm>\n#include <cassert>\n#include\
    \ <vector>\n\n#line 2 \"src/utils/random_number_generator.hpp\"\n#include <random>\n\
    template <typename num_type> class random_number_generator {\n  typename std::conditional<std::is_integral<num_type>::value,\n\
    \                            std::uniform_int_distribution<num_type>,\n      \
    \                      std::uniform_real_distribution<num_type>>::type\n     \
    \ unif;\n\n  std::mt19937 engine;\n\n public:\n  random_number_generator(num_type\
    \ min = std::numeric_limits<num_type>::min(),\n                          num_type\
    \ max = std::numeric_limits<num_type>::max())\n      : unif(min, max), engine(std::random_device{}())\
    \ {}\n\n  num_type min() const { return unif.min(); }\n\n  num_type max() const\
    \ { return unif.max(); }\n\n  // generate a random number in [min(), max()].\n\
    \  num_type operator()() { return unif(engine); }\n};\n#line 2 \"src/utils/sfinae.hpp\"\
    \n#include <cstdint>\n#include <iterator>\n#include <type_traits>\n\ntemplate\
    \ <class type, template <class> class trait>\nusing enable_if_trait_type = typename\
    \ std::enable_if<trait<type>::value>::type;\n\ntemplate <class Container>\nusing\
    \ element_type = typename std::decay<decltype(\n    *std::begin(std::declval<Container&>()))>::type;\n\
    \ntemplate <class T, class = int> struct mapped_of {\n  using type = element_type<T>;\n\
    };\ntemplate <class T>\nstruct mapped_of<T,\n                 typename std::pair<int,\
    \ typename T::mapped_type>::first_type> {\n  using type = typename T::mapped_type;\n\
    };\ntemplate <class T> using mapped_type = typename mapped_of<T>::type;\n\ntemplate\
    \ <class T, class = void> struct is_integral_ext : std::false_type {};\ntemplate\
    \ <class T>\nstruct is_integral_ext<\n    T, typename std::enable_if<std::is_integral<T>::value>::type>\n\
    \    : std::true_type {};\ntemplate <> struct is_integral_ext<__int128_t> : std::true_type\
    \ {};\ntemplate <> struct is_integral_ext<__uint128_t> : std::true_type {};\n\
    #if __cplusplus >= 201402\ntemplate <class T>\nconstexpr static bool is_integral_ext_v\
    \ = is_integral_ext<T>::value;\n#endif\n\ntemplate <typename T, typename = void>\
    \ struct multiplicable_uint {\n  using type = uint_least32_t;\n};\ntemplate <typename\
    \ T>\nstruct multiplicable_uint<T, typename std::enable_if<(2 < sizeof(T))>::type>\
    \ {\n  using type = uint_least64_t;\n};\ntemplate <typename T>\nstruct multiplicable_uint<T,\
    \ typename std::enable_if<(4 < sizeof(T))>::type> {\n  using type = __uint128_t;\n\
    };\n#line 14 \"src/string/rolling_hash.hpp\"\n\nnamespace workspace {\n\n/*\n\
    \ * @struct rolling_hashed\n * @brief hash data of a string.\n */\nstruct rolling_hashed\
    \ {\n  using u64 = uint_least64_t;\n  using u128 = __uint128_t;\n\n  /*\n   *\
    \ @var mod\n   * @brief modulus used for hashing.\n   */\n  constexpr static u64\
    \ mod = (1ull << 61) - 1;\n\n  const static u64 base;\n\n  /*\n   * @var value\n\
    \   * @brief hash value.\n   */\n  u64 value = 0;\n\n  /*\n   * @var lenght\n\
    \   * @brief length of the string.\n   */\n  size_t length = 0;\n\n  rolling_hashed()\
    \ = default;\n\n  /*\n   * @brief construct hash data from one character.\n  \
    \ * @param c a character\n   */\n  template <class char_type, typename std::enable_if<std::is_convertible<\n\
    \                                 char_type, u64>::value>::type * = nullptr>\n\
    \  rolling_hashed(char_type c) : value(u64(c) + 1), length(1) {}\n\n  rolling_hashed(u64\
    \ value, size_t length) : value(value), length(length) {}\n\n  operator std::pair<u64,\
    \ size_t>() const { return {value, length}; }\n\n  /*\n   * @return whether or\
    \ not (*this) and (rhs) are equal\n   * @param rhs\n   */\n  bool operator==(const\
    \ rolling_hashed &rhs) const {\n    return value == rhs.value && length == rhs.length;\n\
    \  }\n\n  /*\n   * @return whether or not (*this) and (rhs) are distinct\n   *\
    \ @param rhs\n   */\n  bool operator!=(const rolling_hashed &rhs) const { return\
    \ !operator==(rhs); }\n\n  /*\n   * @param rhs the right operand\n   * @return\
    \ hash data of concatenated string\n   */\n  rolling_hashed operator+(const rolling_hashed\
    \ &rhs) const {\n    return {plus(value, mult(rhs.value, base_pow(length))),\n\
    \            length + rhs.length};\n  }\n\n  /*\n   * @param rhs appended to right\
    \ end\n   * @return reference to updated hash data\n   */\n  rolling_hashed operator+=(const\
    \ rolling_hashed &rhs) {\n    return *this = operator+(rhs);\n  }\n\n  /*\n  \
    \ * @param rhs the erased suffix\n   * @return hash data of erased string\n  \
    \ */\n  rolling_hashed operator-(const rolling_hashed &rhs) const {\n    assert(!(length\
    \ < rhs.length));\n    return {minus(value, mult(rhs.value, base_pow(length -\
    \ rhs.length))),\n            length - rhs.length};\n  }\n\n  /*\n   * @param\
    \ rhs erased from right end\n   * @return reference to updated hash data\n   */\n\
    \  rolling_hashed operator-=(const rolling_hashed &rhs) {\n    return *this =\
    \ operator-(rhs);\n  }\n\n  /*\n   * @fn base_pow\n   * @param exp the exponent\n\
    \   * @return base ** pow\n   */\n  static u64 base_pow(size_t exp) {\n    static\
    \ std::vector<u64> pow{1};\n    while (pow.size() <= exp) {\n      pow.emplace_back(mult(pow.back(),\
    \ base));\n    }\n    return pow[exp];\n  }\n\n private:\n  static u64 plus(u64\
    \ lhs, u64 rhs) {\n    return (lhs += rhs) < mod ? lhs : lhs - mod;\n  }\n\n \
    \ static u64 minus(u64 lhs, u64 rhs) {\n    return (lhs -= rhs) < mod ? lhs :\
    \ lhs + mod;\n  }\n\n  static u64 mult(u128 lhs, u64 rhs) {\n    lhs *= rhs;\n\
    \    lhs = (lhs >> 61) + (lhs & mod);\n    return lhs < mod ? lhs : lhs - mod;\n\
    \  }\n};\n\n/*\n * @var base\n * @brief base used for hashing\n */\nconst rolling_hashed::u64\
    \ rolling_hashed::base =\n    random_number_generator<u64>(1 << 30, mod - 1)();\n\
    \n/*\n * @struct rolling_hash_table\n * @brief make hash data table of suffix.\n\
    \ */\ntemplate <class str_type> struct rolling_hash_table {\n  constexpr static\
    \ size_t npos = -1;\n\n  rolling_hash_table() = default;\n\n  rolling_hash_table(str_type\
    \ str) {\n    std::reverse(std::begin(str), std::end(str));\n    for (auto &&c\
    \ : str) suffix.emplace_back(rolling_hashed{c} + suffix.back());\n    std::reverse(suffix.begin(),\
    \ suffix.end());\n  }\n\n  /*\n   * @return length of the string\n   */\n  size_t\
    \ size() const { return suffix.size() - 1; }\n\n  /*\n   * @param pos start position\n\
    \   * @param n length of the substring\n   * @return hash data of the substring\n\
    \   */\n  rolling_hashed substr(size_t pos = 0, size_t n = npos) const {\n   \
    \ assert(!(size() < pos));\n    return suffix[pos] - suffix[pos + std::min(n,\
    \ size() - pos)];\n  }\n\n  /*\n   * @param rhs\n   * @return length of the longest\
    \ common prefix\n   */\n  size_t lcp(rolling_hash_table const &rhs) const {\n\
    \    auto n = std::min(size(), rhs.size());\n    return binary_search<size_t>(\n\
    \        0, n + 1, [&](size_t l) { return substr(0, l) == rhs.substr(0, l); });\n\
    \  }\n\n private:\n  std::vector<rolling_hashed> suffix{{}};\n};\n\n}  // namespace\
    \ workspace\n"
  code: "#pragma once\n\n/*\n * @file rolling_hash.hpp\n * @brief Rolling Hash\n */\n\
    \n#include <algorithm>\n#include <cassert>\n#include <vector>\n\n#include \"src/utils/random_number_generator.hpp\"\
    \n#include \"src/utils/sfinae.hpp\"\n\nnamespace workspace {\n\n/*\n * @struct\
    \ rolling_hashed\n * @brief hash data of a string.\n */\nstruct rolling_hashed\
    \ {\n  using u64 = uint_least64_t;\n  using u128 = __uint128_t;\n\n  /*\n   *\
    \ @var mod\n   * @brief modulus used for hashing.\n   */\n  constexpr static u64\
    \ mod = (1ull << 61) - 1;\n\n  const static u64 base;\n\n  /*\n   * @var value\n\
    \   * @brief hash value.\n   */\n  u64 value = 0;\n\n  /*\n   * @var lenght\n\
    \   * @brief length of the string.\n   */\n  size_t length = 0;\n\n  rolling_hashed()\
    \ = default;\n\n  /*\n   * @brief construct hash data from one character.\n  \
    \ * @param c a character\n   */\n  template <class char_type, typename std::enable_if<std::is_convertible<\n\
    \                                 char_type, u64>::value>::type * = nullptr>\n\
    \  rolling_hashed(char_type c) : value(u64(c) + 1), length(1) {}\n\n  rolling_hashed(u64\
    \ value, size_t length) : value(value), length(length) {}\n\n  operator std::pair<u64,\
    \ size_t>() const { return {value, length}; }\n\n  /*\n   * @return whether or\
    \ not (*this) and (rhs) are equal\n   * @param rhs\n   */\n  bool operator==(const\
    \ rolling_hashed &rhs) const {\n    return value == rhs.value && length == rhs.length;\n\
    \  }\n\n  /*\n   * @return whether or not (*this) and (rhs) are distinct\n   *\
    \ @param rhs\n   */\n  bool operator!=(const rolling_hashed &rhs) const { return\
    \ !operator==(rhs); }\n\n  /*\n   * @param rhs the right operand\n   * @return\
    \ hash data of concatenated string\n   */\n  rolling_hashed operator+(const rolling_hashed\
    \ &rhs) const {\n    return {plus(value, mult(rhs.value, base_pow(length))),\n\
    \            length + rhs.length};\n  }\n\n  /*\n   * @param rhs appended to right\
    \ end\n   * @return reference to updated hash data\n   */\n  rolling_hashed operator+=(const\
    \ rolling_hashed &rhs) {\n    return *this = operator+(rhs);\n  }\n\n  /*\n  \
    \ * @param rhs the erased suffix\n   * @return hash data of erased string\n  \
    \ */\n  rolling_hashed operator-(const rolling_hashed &rhs) const {\n    assert(!(length\
    \ < rhs.length));\n    return {minus(value, mult(rhs.value, base_pow(length -\
    \ rhs.length))),\n            length - rhs.length};\n  }\n\n  /*\n   * @param\
    \ rhs erased from right end\n   * @return reference to updated hash data\n   */\n\
    \  rolling_hashed operator-=(const rolling_hashed &rhs) {\n    return *this =\
    \ operator-(rhs);\n  }\n\n  /*\n   * @fn base_pow\n   * @param exp the exponent\n\
    \   * @return base ** pow\n   */\n  static u64 base_pow(size_t exp) {\n    static\
    \ std::vector<u64> pow{1};\n    while (pow.size() <= exp) {\n      pow.emplace_back(mult(pow.back(),\
    \ base));\n    }\n    return pow[exp];\n  }\n\n private:\n  static u64 plus(u64\
    \ lhs, u64 rhs) {\n    return (lhs += rhs) < mod ? lhs : lhs - mod;\n  }\n\n \
    \ static u64 minus(u64 lhs, u64 rhs) {\n    return (lhs -= rhs) < mod ? lhs :\
    \ lhs + mod;\n  }\n\n  static u64 mult(u128 lhs, u64 rhs) {\n    lhs *= rhs;\n\
    \    lhs = (lhs >> 61) + (lhs & mod);\n    return lhs < mod ? lhs : lhs - mod;\n\
    \  }\n};\n\n/*\n * @var base\n * @brief base used for hashing\n */\nconst rolling_hashed::u64\
    \ rolling_hashed::base =\n    random_number_generator<u64>(1 << 30, mod - 1)();\n\
    \n/*\n * @struct rolling_hash_table\n * @brief make hash data table of suffix.\n\
    \ */\ntemplate <class str_type> struct rolling_hash_table {\n  constexpr static\
    \ size_t npos = -1;\n\n  rolling_hash_table() = default;\n\n  rolling_hash_table(str_type\
    \ str) {\n    std::reverse(std::begin(str), std::end(str));\n    for (auto &&c\
    \ : str) suffix.emplace_back(rolling_hashed{c} + suffix.back());\n    std::reverse(suffix.begin(),\
    \ suffix.end());\n  }\n\n  /*\n   * @return length of the string\n   */\n  size_t\
    \ size() const { return suffix.size() - 1; }\n\n  /*\n   * @param pos start position\n\
    \   * @param n length of the substring\n   * @return hash data of the substring\n\
    \   */\n  rolling_hashed substr(size_t pos = 0, size_t n = npos) const {\n   \
    \ assert(!(size() < pos));\n    return suffix[pos] - suffix[pos + std::min(n,\
    \ size() - pos)];\n  }\n\n  /*\n   * @param rhs\n   * @return length of the longest\
    \ common prefix\n   */\n  size_t lcp(rolling_hash_table const &rhs) const {\n\
    \    auto n = std::min(size(), rhs.size());\n    return binary_search<size_t>(\n\
    \        0, n + 1, [&](size_t l) { return substr(0, l) == rhs.substr(0, l); });\n\
    \  }\n\n private:\n  std::vector<rolling_hashed> suffix{{}};\n};\n\n}  // namespace\
    \ workspace\n"
  dependsOn:
  - src/utils/random_number_generator.hpp
  - src/utils/sfinae.hpp
  isVerificationFile: false
  path: src/string/rolling_hash.hpp
  requiredBy: []
  timestamp: '2020-11-16 22:50:09+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/library-checker/zalgorithm_2.test.cpp
  - test/aizu-online-judge/ALDS1_14_C.test.cpp
documentation_of: src/string/rolling_hash.hpp
layout: document
redirect_from:
- /library/src/string/rolling_hash.hpp
- /library/src/string/rolling_hash.hpp.html
title: Rolling Hash
---
