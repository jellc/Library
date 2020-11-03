---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/rolling_hash.hpp
    title: string/rolling_hash.hpp
  - icon: ':heavy_check_mark:'
    path: utils/random_number_generator.hpp
    title: utils/random_number_generator.hpp
  - icon: ':question:'
    path: utils/sfinae.hpp
    title: utils/sfinae.hpp
  - icon: ':heavy_check_mark:'
    path: utils/stream.hpp
    title: utils/stream.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_C
    links:
    - https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_C
  bundledCode: "#line 1 \"test/aizu-online-judge/pattern_search.test.cpp\"\n#define\
    \ PROBLEM \\\n  \"https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_C\"\
    \n#line 2 \"string/rolling_hash.hpp\"\n#include <algorithm>\n#include <cassert>\n\
    #include <vector>\n\n#line 2 \"utils/random_number_generator.hpp\"\n#include <random>\n\
    template <typename num_type> class random_number_generator {\n  typename std::conditional<std::is_integral<num_type>::value,\n\
    \                            std::uniform_int_distribution<num_type>,\n      \
    \                      std::uniform_real_distribution<num_type>>::type\n     \
    \ unif;\n\n  std::mt19937 engine;\n\n public:\n  random_number_generator(num_type\
    \ min = std::numeric_limits<num_type>::min(),\n                          num_type\
    \ max = std::numeric_limits<num_type>::max())\n      : unif(min, max), engine(std::random_device{}())\
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
    \ suffix{{}};\n};\n#line 2 \"utils/stream.hpp\"\n#include <iostream>\n#include\
    \ <tuple>\n\n#line 2 \"utils/sfinae.hpp\"\n#include <cstdint>\n#include <iterator>\n\
    #include <type_traits>\n\ntemplate <class type, template <class> class trait>\n\
    using enable_if_trait_type = typename std::enable_if<trait<type>::value>::type;\n\
    \ntemplate <class Container>\nusing element_type = typename std::decay<decltype(\n\
    \    *std::begin(std::declval<Container&>()))>::type;\n\ntemplate <class T, class\
    \ = int> struct mapped_of {\n  using type = element_type<T>;\n};\ntemplate <class\
    \ T>\nstruct mapped_of<T,\n                 typename std::pair<int, typename T::mapped_type>::first_type>\
    \ {\n  using type = typename T::mapped_type;\n};\ntemplate <class T> using mapped_type\
    \ = typename mapped_of<T>::type;\n\ntemplate <class T, class = void> struct is_integral_ext\
    \ : std::false_type {};\ntemplate <class T>\nstruct is_integral_ext<\n    T, typename\
    \ std::enable_if<std::is_integral<T>::value>::type>\n    : std::true_type {};\n\
    template <> struct is_integral_ext<__int128_t> : std::true_type {};\ntemplate\
    \ <> struct is_integral_ext<__uint128_t> : std::true_type {};\n#if __cplusplus\
    \ >= 201402\ntemplate <class T>\nconstexpr static bool is_integral_ext_v = is_integral_ext<T>::value;\n\
    #endif\n\ntemplate <typename T, typename = void> struct multiplicable_uint {\n\
    \  using type = uint_least32_t;\n};\ntemplate <typename T>\nstruct multiplicable_uint<T,\
    \ typename std::enable_if<(2 < sizeof(T))>::type> {\n  using type = uint_least64_t;\n\
    };\ntemplate <typename T>\nstruct multiplicable_uint<T, typename std::enable_if<(4\
    \ < sizeof(T))>::type> {\n  using type = __uint128_t;\n};\n#line 6 \"utils/stream.hpp\"\
    \nnamespace std {\ntemplate <class T, class U> istream &operator>>(istream &is,\
    \ pair<T, U> &p) {\n  return is >> p.first >> p.second;\n}\ntemplate <class T,\
    \ class U>\nostream &operator<<(ostream &os, const pair<T, U> &p) {\n  return\
    \ os << p.first << ' ' << p.second;\n}\ntemplate <class tuple_t, size_t index>\
    \ struct tuple_is {\n  static istream &apply(istream &is, tuple_t &t) {\n    tuple_is<tuple_t,\
    \ index - 1>::apply(is, t);\n    return is >> get<index>(t);\n  }\n};\ntemplate\
    \ <class tuple_t> struct tuple_is<tuple_t, SIZE_MAX> {\n  static istream &apply(istream\
    \ &is, tuple_t &t) { return is; }\n};\ntemplate <class... T> istream &operator>>(istream\
    \ &is, tuple<T...> &t) {\n  return tuple_is<tuple<T...>, tuple_size<tuple<T...>>::value\
    \ - 1>::apply(is,\n                                                          \
    \                t);\n}\ntemplate <class tuple_t, size_t index> struct tuple_os\
    \ {\n  static ostream &apply(ostream &os, const tuple_t &t) {\n    tuple_os<tuple_t,\
    \ index - 1>::apply(os, t);\n    return os << ' ' << get<index>(t);\n  }\n};\n\
    template <class tuple_t> struct tuple_os<tuple_t, 0> {\n  static ostream &apply(ostream\
    \ &os, const tuple_t &t) {\n    return os << get<0>(t);\n  }\n};\ntemplate <class\
    \ tuple_t> struct tuple_os<tuple_t, SIZE_MAX> {\n  static ostream &apply(ostream\
    \ &os, const tuple_t &t) { return os; }\n};\ntemplate <class... T> ostream &operator<<(ostream\
    \ &os, const tuple<T...> &t) {\n  return tuple_os<tuple<T...>, tuple_size<tuple<T...>>::value\
    \ - 1>::apply(os,\n                                                          \
    \                t);\n}\ntemplate <class Container, typename Value = element_type<Container>>\n\
    typename enable_if<!is_same<typename decay<Container>::type, string>::value &&\n\
    \                       !is_same<typename decay<Container>::type, char *>::value,\n\
    \                   istream &>::type\noperator>>(istream &is, Container &cont)\
    \ {\n  for (auto &&e : cont) is >> e;\n  return is;\n}\ntemplate <class Container,\
    \ typename Value = element_type<Container>>\ntypename enable_if<!is_same<typename\
    \ decay<Container>::type, string>::value &&\n                       !is_same<typename\
    \ decay<Container>::type, char *>::value,\n                   ostream &>::type\n\
    operator<<(ostream &os, const Container &cont) {\n  bool head = true;\n  for (auto\
    \ &&e : cont) head ? head = 0 : (os << ' ', 0), os << e;\n  return os;\n}\n} \
    \ // namespace std\n#line 5 \"test/aizu-online-judge/pattern_search.test.cpp\"\
    \n\nint main() {\n  std::ios::sync_with_stdio(0);\n  std::cin.tie(0);\n\n  size_t\
    \ h, w, r, c;\n\n  std::cin >> h >> w;\n  std::string transposed(h * w, '?');\n\
    \  for (size_t i = 0; i < h; ++i) {\n    for (size_t j = 0; j < w; ++j) {\n  \
    \    std::cin >> transposed[j * h + i];\n    }\n  }\n\n  std::cin >> r >> c;\n\
    \  std::string oneln(r * c, '?');\n  for (size_t i = 0; i < r; ++i) {\n    for\
    \ (size_t j = c; j--;) {\n      std::cin >> oneln[j * r + i];\n    }\n  }\n\n\
    \  rolling_hash_table grid_hash_table(transposed);\n  auto pattern_hash = rolling_hash_table(oneln).substr();\n\
    \n  for (size_t i = 0; i + r <= h; ++i) {\n    rolling_hashed hash;\n    for (size_t\
    \ j = 0; j < w; ++j) {\n      hash = grid_hash_table.substr(h * j + i, r) + hash;\n\
    \      if (j >= c) {\n        hash -= grid_hash_table.substr(h * (j - c) + i,\
    \ r);\n      }\n      if (hash == pattern_hash) std::cout << i << \" \" << j -\
    \ c + 1 << \"\\n\";\n    }\n  }\n}\n"
  code: "#define PROBLEM \\\n  \"https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_C\"\
    \n#include \"string/rolling_hash.hpp\"\n#include \"utils/stream.hpp\"\n\nint main()\
    \ {\n  std::ios::sync_with_stdio(0);\n  std::cin.tie(0);\n\n  size_t h, w, r,\
    \ c;\n\n  std::cin >> h >> w;\n  std::string transposed(h * w, '?');\n  for (size_t\
    \ i = 0; i < h; ++i) {\n    for (size_t j = 0; j < w; ++j) {\n      std::cin >>\
    \ transposed[j * h + i];\n    }\n  }\n\n  std::cin >> r >> c;\n  std::string oneln(r\
    \ * c, '?');\n  for (size_t i = 0; i < r; ++i) {\n    for (size_t j = c; j--;)\
    \ {\n      std::cin >> oneln[j * r + i];\n    }\n  }\n\n  rolling_hash_table grid_hash_table(transposed);\n\
    \  auto pattern_hash = rolling_hash_table(oneln).substr();\n\n  for (size_t i\
    \ = 0; i + r <= h; ++i) {\n    rolling_hashed hash;\n    for (size_t j = 0; j\
    \ < w; ++j) {\n      hash = grid_hash_table.substr(h * j + i, r) + hash;\n   \
    \   if (j >= c) {\n        hash -= grid_hash_table.substr(h * (j - c) + i, r);\n\
    \      }\n      if (hash == pattern_hash) std::cout << i << \" \" << j - c + 1\
    \ << \"\\n\";\n    }\n  }\n}\n"
  dependsOn:
  - string/rolling_hash.hpp
  - utils/random_number_generator.hpp
  - utils/stream.hpp
  - utils/sfinae.hpp
  isVerificationFile: true
  path: test/aizu-online-judge/pattern_search.test.cpp
  requiredBy: []
  timestamp: '2020-10-10 01:30:31+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aizu-online-judge/pattern_search.test.cpp
layout: document
redirect_from:
- /verify/test/aizu-online-judge/pattern_search.test.cpp
- /verify/test/aizu-online-judge/pattern_search.test.cpp.html
title: test/aizu-online-judge/pattern_search.test.cpp
---
