---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: utils/sfinae.hpp
    title: utils/sfinae.hpp
  _extendedRequiredBy:
  - icon: ':warning:'
    path: template.cpp
    title: template.cpp
  - icon: ':warning:'
    path: utils.hpp
    title: utils.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/library-checker/associative_array.test.cpp
    title: test/library-checker/associative_array.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"utils/hash.hpp\"\n#include <ext/pb_ds/assoc_container.hpp>\n\
    #include <functional>\n#include <random>\n#include <unordered_set>\n\n#line 2\
    \ \"utils/sfinae.hpp\"\n#include <cstdint>\n#include <type_traits>\n\ntemplate\
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
    };\n#line 8 \"utils/hash.hpp\"\nnamespace workspace {\ntemplate <class T, class\
    \ = void> struct hash : std::hash<T> {};\n#if __cplusplus >= 201703L\ntemplate\
    \ <class Unique_bits_type>\nstruct hash<Unique_bits_type,\n            enable_if_trait_type<Unique_bits_type,\n\
    \                                 std::has_unique_object_representations>> {\n\
    \  size_t operator()(uint64_t x) const {\n    static const uint64_t m = std::random_device{}();\n\
    \    x ^= x >> 23;\n    x ^= m;\n    x ^= x >> 47;\n    return x - (x >> 32);\n\
    \  }\n};\n#endif\ntemplate <class Key> size_t hash_combine(const size_t &seed,\
    \ const Key &key) {\n  return seed ^\n         (hash<Key>()(key) + 0x9e3779b9\
    \ /* + (seed << 6) + (seed >> 2) */);\n}\ntemplate <class T1, class T2> struct\
    \ hash<std::pair<T1, T2>> {\n  size_t operator()(const std::pair<T1, T2> &pair)\
    \ const {\n    return hash_combine(hash<T1>()(pair.first), pair.second);\n  }\n\
    };\ntemplate <class... T> class hash<std::tuple<T...>> {\n  template <class Tuple,\
    \ size_t index = std::tuple_size<Tuple>::value - 1>\n  struct tuple_hash {\n \
    \   static uint64_t apply(const Tuple &t) {\n      return hash_combine(tuple_hash<Tuple,\
    \ index - 1>::apply(t),\n                          std::get<index>(t));\n    }\n\
    \  };\n  template <class Tuple> struct tuple_hash<Tuple, size_t(-1)> {\n    static\
    \ uint64_t apply(const Tuple &t) { return 0; }\n  };\n\n public:\n  uint64_t operator()(const\
    \ std::tuple<T...> &t) const {\n    return tuple_hash<std::tuple<T...>>::apply(t);\n\
    \  }\n};\ntemplate <class hash_table> struct hash_table_wrapper : hash_table {\n\
    \  using key_type = typename hash_table::key_type;\n  size_t count(const key_type\
    \ &key) const {\n    return hash_table::find(key) != hash_table::end();\n  }\n\
    \  template <class... Args> auto emplace(Args &&... args) {\n    return hash_table::insert(typename\
    \ hash_table::value_type(args...));\n  }\n};\ntemplate <class Key, class Mapped\
    \ = __gnu_pbds::null_type>\nusing cc_hash_table =\n    hash_table_wrapper<__gnu_pbds::cc_hash_table<Key,\
    \ Mapped, hash<Key>>>;\ntemplate <class Key, class Mapped = __gnu_pbds::null_type>\n\
    using gp_hash_table =\n    hash_table_wrapper<__gnu_pbds::gp_hash_table<Key, Mapped,\
    \ hash<Key>>>;\ntemplate <class Key, class Mapped>\nusing unordered_map = std::unordered_map<Key,\
    \ Mapped, hash<Key>>;\ntemplate <class Key> using unordered_set = std::unordered_set<Key,\
    \ hash<Key>>;\n}  // namespace workspace\n"
  code: "#pragma once\n#include <ext/pb_ds/assoc_container.hpp>\n#include <functional>\n\
    #include <random>\n#include <unordered_set>\n\n#include \"sfinae.hpp\"\nnamespace\
    \ workspace {\ntemplate <class T, class = void> struct hash : std::hash<T> {};\n\
    #if __cplusplus >= 201703L\ntemplate <class Unique_bits_type>\nstruct hash<Unique_bits_type,\n\
    \            enable_if_trait_type<Unique_bits_type,\n                        \
    \         std::has_unique_object_representations>> {\n  size_t operator()(uint64_t\
    \ x) const {\n    static const uint64_t m = std::random_device{}();\n    x ^=\
    \ x >> 23;\n    x ^= m;\n    x ^= x >> 47;\n    return x - (x >> 32);\n  }\n};\n\
    #endif\ntemplate <class Key> size_t hash_combine(const size_t &seed, const Key\
    \ &key) {\n  return seed ^\n         (hash<Key>()(key) + 0x9e3779b9 /* + (seed\
    \ << 6) + (seed >> 2) */);\n}\ntemplate <class T1, class T2> struct hash<std::pair<T1,\
    \ T2>> {\n  size_t operator()(const std::pair<T1, T2> &pair) const {\n    return\
    \ hash_combine(hash<T1>()(pair.first), pair.second);\n  }\n};\ntemplate <class...\
    \ T> class hash<std::tuple<T...>> {\n  template <class Tuple, size_t index = std::tuple_size<Tuple>::value\
    \ - 1>\n  struct tuple_hash {\n    static uint64_t apply(const Tuple &t) {\n \
    \     return hash_combine(tuple_hash<Tuple, index - 1>::apply(t),\n          \
    \                std::get<index>(t));\n    }\n  };\n  template <class Tuple> struct\
    \ tuple_hash<Tuple, size_t(-1)> {\n    static uint64_t apply(const Tuple &t) {\
    \ return 0; }\n  };\n\n public:\n  uint64_t operator()(const std::tuple<T...>\
    \ &t) const {\n    return tuple_hash<std::tuple<T...>>::apply(t);\n  }\n};\ntemplate\
    \ <class hash_table> struct hash_table_wrapper : hash_table {\n  using key_type\
    \ = typename hash_table::key_type;\n  size_t count(const key_type &key) const\
    \ {\n    return hash_table::find(key) != hash_table::end();\n  }\n  template <class...\
    \ Args> auto emplace(Args &&... args) {\n    return hash_table::insert(typename\
    \ hash_table::value_type(args...));\n  }\n};\ntemplate <class Key, class Mapped\
    \ = __gnu_pbds::null_type>\nusing cc_hash_table =\n    hash_table_wrapper<__gnu_pbds::cc_hash_table<Key,\
    \ Mapped, hash<Key>>>;\ntemplate <class Key, class Mapped = __gnu_pbds::null_type>\n\
    using gp_hash_table =\n    hash_table_wrapper<__gnu_pbds::gp_hash_table<Key, Mapped,\
    \ hash<Key>>>;\ntemplate <class Key, class Mapped>\nusing unordered_map = std::unordered_map<Key,\
    \ Mapped, hash<Key>>;\ntemplate <class Key> using unordered_set = std::unordered_set<Key,\
    \ hash<Key>>;\n}  // namespace workspace\n"
  dependsOn:
  - utils/sfinae.hpp
  isVerificationFile: false
  path: utils/hash.hpp
  requiredBy:
  - template.cpp
  - utils.hpp
  timestamp: '2020-09-25 13:36:45+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/associative_array.test.cpp
documentation_of: utils/hash.hpp
layout: document
redirect_from:
- /library/utils/hash.hpp
- /library/utils/hash.hpp.html
title: utils/hash.hpp
---
