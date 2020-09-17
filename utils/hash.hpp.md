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
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/library-checker/associative_array.test.cpp
    title: test/library-checker/associative_array.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 2 \"utils/hash.hpp\"\n#include <ext/pb_ds/assoc_container.hpp>\n\
    #include <functional>\n#include <random>\n#include <unordered_set>\n#line 2 \"\
    utils/sfinae.hpp\"\n#include <cstdint>\n#include <type_traits>\n\ntemplate <class\
    \ type, template <class> class trait>\nusing enable_if_trait_type = typename std::enable_if<trait<type>::value>::type;\n\
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
    \ < sizeof(T))>::type> {\n  using type = __uint128_t;\n};\n#line 7 \"utils/hash.hpp\"\
    \nnamespace workspace {\ntemplate <class T, class = void>\nstruct hash : std::hash<T>\
    \ {};\ntemplate <class Unique_bits_type>\nstruct hash<Unique_bits_type, enable_if_trait_type<Unique_bits_type,\
    \ std::has_unique_object_representations>>\n{\n    size_t operator()(uint64_t\
    \ x) const\n    {\n        static const uint64_t m = std::random_device{}();\n\
    \        x ^= x >> 23;\n        // x *= 0x2127599bf4325c37ULL;\n        x ^= m;\n\
    \        x ^= x >> 47;\n        return x - (x >> 32);\n    }\n};\ntemplate <class\
    \ Key>\nsize_t hash_combine(const size_t &seed, const Key &key)\n{\n    return\
    \ seed ^ (hash<Key>()(key) + 0x9e3779b9 /* + (seed << 6) + (seed >> 2) */ );\n\
    }\ntemplate <class T1, class T2>\nstruct hash<std::pair<T1, T2>>\n{\n    size_t\
    \ operator()(const std::pair<T1, T2> &pair) const\n    {\n        return hash_combine(hash<T1>()(pair.first),\
    \ pair.second);\n    }\n};\ntemplate <class... T>\nclass hash<std::tuple<T...>>\n\
    {\n    template <class Tuple, size_t index = std::tuple_size<Tuple>::value - 1>\
    \ struct tuple_hash { static uint64_t apply(const Tuple &t) { return hash_combine(tuple_hash<Tuple,\
    \ index - 1>::apply(t), std::get<index>(t)); } };\n    template <class Tuple>\
    \ struct tuple_hash<Tuple, size_t(-1)> { static uint64_t apply(const Tuple &t)\
    \ { return 0; } };\npublic:\n    uint64_t operator()(const std::tuple<T...> &t)\
    \ const { return tuple_hash<std::tuple<T...>>::apply(t); }\n};\ntemplate <class\
    \ hash_table>\nstruct hash_table_wrapper : hash_table\n{\n    using key_type =\
    \ typename hash_table::key_type;\n    size_t count(const key_type &key) const\
    \ { return hash_table::find(key) != hash_table::end(); }\n    template <class...\
    \ Args> auto emplace(Args&&... args) { return hash_table::insert(typename hash_table::value_type(args...));\
    \ }\n};\ntemplate <class Key, class Mapped = __gnu_pbds::null_type>\nusing cc_hash_table\
    \ = hash_table_wrapper<__gnu_pbds::cc_hash_table<Key, Mapped, hash<Key>>>;\ntemplate\
    \ <class Key, class Mapped = __gnu_pbds::null_type>\nusing gp_hash_table = hash_table_wrapper<__gnu_pbds::gp_hash_table<Key,\
    \ Mapped, hash<Key>>>;\ntemplate <class Key, class Mapped>\nusing unordered_map\
    \ = std::unordered_map<Key, Mapped, hash<Key>>;\ntemplate <class Key>\nusing unordered_set\
    \ = std::unordered_set<Key, hash<Key>>;\n} // namespace workspace\n"
  code: "#pragma once\n#include <ext/pb_ds/assoc_container.hpp>\n#include <functional>\n\
    #include <random>\n#include <unordered_set>\n#include \"sfinae.hpp\"\nnamespace\
    \ workspace {\ntemplate <class T, class = void>\nstruct hash : std::hash<T> {};\n\
    template <class Unique_bits_type>\nstruct hash<Unique_bits_type, enable_if_trait_type<Unique_bits_type,\
    \ std::has_unique_object_representations>>\n{\n    size_t operator()(uint64_t\
    \ x) const\n    {\n        static const uint64_t m = std::random_device{}();\n\
    \        x ^= x >> 23;\n        // x *= 0x2127599bf4325c37ULL;\n        x ^= m;\n\
    \        x ^= x >> 47;\n        return x - (x >> 32);\n    }\n};\ntemplate <class\
    \ Key>\nsize_t hash_combine(const size_t &seed, const Key &key)\n{\n    return\
    \ seed ^ (hash<Key>()(key) + 0x9e3779b9 /* + (seed << 6) + (seed >> 2) */ );\n\
    }\ntemplate <class T1, class T2>\nstruct hash<std::pair<T1, T2>>\n{\n    size_t\
    \ operator()(const std::pair<T1, T2> &pair) const\n    {\n        return hash_combine(hash<T1>()(pair.first),\
    \ pair.second);\n    }\n};\ntemplate <class... T>\nclass hash<std::tuple<T...>>\n\
    {\n    template <class Tuple, size_t index = std::tuple_size<Tuple>::value - 1>\
    \ struct tuple_hash { static uint64_t apply(const Tuple &t) { return hash_combine(tuple_hash<Tuple,\
    \ index - 1>::apply(t), std::get<index>(t)); } };\n    template <class Tuple>\
    \ struct tuple_hash<Tuple, size_t(-1)> { static uint64_t apply(const Tuple &t)\
    \ { return 0; } };\npublic:\n    uint64_t operator()(const std::tuple<T...> &t)\
    \ const { return tuple_hash<std::tuple<T...>>::apply(t); }\n};\ntemplate <class\
    \ hash_table>\nstruct hash_table_wrapper : hash_table\n{\n    using key_type =\
    \ typename hash_table::key_type;\n    size_t count(const key_type &key) const\
    \ { return hash_table::find(key) != hash_table::end(); }\n    template <class...\
    \ Args> auto emplace(Args&&... args) { return hash_table::insert(typename hash_table::value_type(args...));\
    \ }\n};\ntemplate <class Key, class Mapped = __gnu_pbds::null_type>\nusing cc_hash_table\
    \ = hash_table_wrapper<__gnu_pbds::cc_hash_table<Key, Mapped, hash<Key>>>;\ntemplate\
    \ <class Key, class Mapped = __gnu_pbds::null_type>\nusing gp_hash_table = hash_table_wrapper<__gnu_pbds::gp_hash_table<Key,\
    \ Mapped, hash<Key>>>;\ntemplate <class Key, class Mapped>\nusing unordered_map\
    \ = std::unordered_map<Key, Mapped, hash<Key>>;\ntemplate <class Key>\nusing unordered_set\
    \ = std::unordered_set<Key, hash<Key>>;\n} // namespace workspace\n"
  dependsOn:
  - utils/sfinae.hpp
  isVerificationFile: false
  path: utils/hash.hpp
  requiredBy:
  - template.cpp
  timestamp: '2020-09-17 16:18:47+09:00'
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
