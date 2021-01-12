---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/utils/hash.hpp
    title: src/utils/hash.hpp
  - icon: ':heavy_check_mark:'
    path: src/utils/sfinae.hpp
    title: SFINAE
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/associative_array
    links:
    - https://judge.yosupo.jp/problem/associative_array
  bundledCode: "#line 1 \"test/library-checker/associative_array.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/associative_array\"\n\n#line 2 \"\
    src/utils/hash.hpp\"\n#include <ext/pb_ds/assoc_container.hpp>\n#include <functional>\n\
    #include <random>\n#include <unordered_set>\n\n#line 2 \"src/utils/sfinae.hpp\"\
    \n\n/**\n * @file sfinae.hpp\n * @brief SFINAE\n */\n\n#include <cstdint>\n#include\
    \ <iterator>\n#include <type_traits>\n\n#ifdef __SIZEOF_INT128__\n#define __INT128_DEFINED__\
    \ 1\n#else\n#define __INT128_DEFINED__ 0\n#endif\n\nnamespace std {\n\n#if __INT128_DEFINED__\n\
    \ntemplate <> struct make_signed<__uint128_t> { using type = __int128_t; };\n\
    template <> struct make_signed<__int128_t> { using type = __int128_t; };\n\ntemplate\
    \ <> struct make_unsigned<__uint128_t> { using type = __uint128_t; };\ntemplate\
    \ <> struct make_unsigned<__int128_t> { using type = __uint128_t; };\n\n#endif\n\
    \n}  // namespace std\n\nnamespace workspace {\n\ntemplate <class type, template\
    \ <class> class trait>\nusing enable_if_trait_type = typename std::enable_if<trait<type>::value>::type;\n\
    \ntemplate <class Container>\nusing element_type = typename std::decay<decltype(\n\
    \    *std::begin(std::declval<Container&>()))>::type;\n\ntemplate <class T, class\
    \ = std::nullptr_t>\nstruct has_begin : std::false_type {};\n\ntemplate <class\
    \ T>\nstruct has_begin<T, decltype(std::begin(std::declval<T>()), nullptr)>\n\
    \    : std::true_type {};\n\ntemplate <class T, class = int> struct mapped_of\
    \ {\n  using type = element_type<T>;\n};\ntemplate <class T>\nstruct mapped_of<T,\n\
    \                 typename std::pair<int, typename T::mapped_type>::first_type>\
    \ {\n  using type = typename T::mapped_type;\n};\ntemplate <class T> using mapped_type\
    \ = typename mapped_of<T>::type;\n\ntemplate <class T, class = void> struct is_integral_ext\
    \ : std::false_type {};\ntemplate <class T>\nstruct is_integral_ext<\n    T, typename\
    \ std::enable_if<std::is_integral<T>::value>::type>\n    : std::true_type {};\n\
    \n#if __INT128_DEFINED__\n\ntemplate <> struct is_integral_ext<__int128_t> : std::true_type\
    \ {};\ntemplate <> struct is_integral_ext<__uint128_t> : std::true_type {};\n\n\
    #endif\n\n#if __cplusplus >= 201402\n\ntemplate <class T>\nconstexpr static bool\
    \ is_integral_ext_v = is_integral_ext<T>::value;\n\n#endif\n\ntemplate <typename\
    \ T, typename = void> struct multiplicable_uint {\n  using type = uint_least32_t;\n\
    };\ntemplate <typename T>\nstruct multiplicable_uint<\n    T, typename std::enable_if<(2\
    \ < sizeof(T)) &&\n                               (!__INT128_DEFINED__ || sizeof(T)\
    \ <= 4)>::type> {\n  using type = uint_least64_t;\n};\n\n#if __INT128_DEFINED__\n\
    \ntemplate <typename T>\nstruct multiplicable_uint<T, typename std::enable_if<(4\
    \ < sizeof(T))>::type> {\n  using type = __uint128_t;\n};\n\n#endif\n\ntemplate\
    \ <typename T> struct multiplicable_int {\n  using type =\n      typename std::make_signed<typename\
    \ multiplicable_uint<T>::type>::type;\n};\n\n}  // namespace workspace\n#line\
    \ 8 \"src/utils/hash.hpp\"\nnamespace workspace {\ntemplate <class T, class =\
    \ void> struct hash : std::hash<T> {};\n#if __cplusplus >= 201703L\ntemplate <class\
    \ Unique_bits_type>\nstruct hash<Unique_bits_type,\n            enable_if_trait_type<Unique_bits_type,\n\
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
    \ hash<Key>>;\n}  // namespace workspace\n#line 4 \"test/library-checker/associative_array.test.cpp\"\
    \n\nusing namespace workspace;\n\nint main() {\n  int q;\n  scanf(\"%d\", &q);\n\
    \  unordered_map<long long, long long> a;\n  gp_hash_table<long long, long long>\
    \ b;\n  cc_hash_table<long long, long long> c;\n\n  while (q--) {\n    int t;\n\
    \    long long k, v;\n    scanf(\"%d%lld\", &t, &k);\n    if (t) {\n      printf(\"\
    %lld\\n\", a[k]);\n      assert(a[k] == b[k] && a[k] == c[k]);\n    } else {\n\
    \      scanf(\"%lld\", &v);\n      a[k] = b[k] = c[k] = v;\n    }\n  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/associative_array\"\n\n\
    #include \"src/utils/hash.hpp\"\n\nusing namespace workspace;\n\nint main() {\n\
    \  int q;\n  scanf(\"%d\", &q);\n  unordered_map<long long, long long> a;\n  gp_hash_table<long\
    \ long, long long> b;\n  cc_hash_table<long long, long long> c;\n\n  while (q--)\
    \ {\n    int t;\n    long long k, v;\n    scanf(\"%d%lld\", &t, &k);\n    if (t)\
    \ {\n      printf(\"%lld\\n\", a[k]);\n      assert(a[k] == b[k] && a[k] == c[k]);\n\
    \    } else {\n      scanf(\"%lld\", &v);\n      a[k] = b[k] = c[k] = v;\n   \
    \ }\n  }\n}\n"
  dependsOn:
  - src/utils/hash.hpp
  - src/utils/sfinae.hpp
  isVerificationFile: true
  path: test/library-checker/associative_array.test.cpp
  requiredBy: []
  timestamp: '2021-01-13 00:11:06+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/library-checker/associative_array.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/associative_array.test.cpp
- /verify/test/library-checker/associative_array.test.cpp.html
title: test/library-checker/associative_array.test.cpp
---
