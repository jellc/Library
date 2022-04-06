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
  _isVerificationFailed: false
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
    \ <iterator>\n#include <type_traits>\n\n#ifndef __INT128_DEFINED__\n\n#ifdef __SIZEOF_INT128__\n\
    #define __INT128_DEFINED__ 1\n#else\n#define __INT128_DEFINED__ 0\n#endif\n\n\
    #endif\n\nnamespace std {\n\n#if __INT128_DEFINED__\n\ntemplate <> struct make_signed<__uint128_t>\
    \ { using type = __int128_t; };\ntemplate <> struct make_signed<__int128_t> {\
    \ using type = __int128_t; };\n\ntemplate <> struct make_unsigned<__uint128_t>\
    \ { using type = __uint128_t; };\ntemplate <> struct make_unsigned<__int128_t>\
    \ { using type = __uint128_t; };\n\ntemplate <> struct is_signed<__uint128_t>\
    \ : std::false_type {};\ntemplate <> struct is_signed<__int128_t> : std::true_type\
    \ {};\n\ntemplate <> struct is_unsigned<__uint128_t> : std::true_type {};\ntemplate\
    \ <> struct is_unsigned<__int128_t> : std::false_type {};\n\n#endif\n\n}  // namespace\
    \ std\n\nnamespace workspace {\n\ntemplate <class Tp, class... Args> struct variadic_front\
    \ { using type = Tp; };\n\ntemplate <class... Args> struct variadic_back;\n\n\
    template <class Tp> struct variadic_back<Tp> { using type = Tp; };\n\ntemplate\
    \ <class Tp, class... Args> struct variadic_back<Tp, Args...> {\n  using type\
    \ = typename variadic_back<Args...>::type;\n};\n\ntemplate <class type, template\
    \ <class> class trait>\nusing enable_if_trait_type = typename std::enable_if<trait<type>::value>::type;\n\
    \n/**\n * @brief Return type of subscripting ( @c [] ) access.\n */\ntemplate\
    \ <class _Tp>\nusing subscripted_type =\n    typename std::decay<decltype(std::declval<_Tp&>()[0])>::type;\n\
    \ntemplate <class Container>\nusing element_type = typename std::decay<decltype(*std::begin(\n\
    \    std::declval<Container&>()))>::type;\n\ntemplate <class _Tp, class = void>\
    \ struct has_begin : std::false_type {};\n\ntemplate <class _Tp>\nstruct has_begin<\n\
    \    _Tp, std::__void_t<decltype(std::begin(std::declval<const _Tp&>()))>>\n \
    \   : std::true_type {\n  using type = decltype(std::begin(std::declval<const\
    \ _Tp&>()));\n};\n\ntemplate <class _Tp, class = void> struct has_size : std::false_type\
    \ {};\n\ntemplate <class _Tp>\nstruct has_size<_Tp, std::__void_t<decltype(std::size(std::declval<_Tp>()))>>\n\
    \    : std::true_type {};\n\ntemplate <class _Tp, class = void> struct has_resize\
    \ : std::false_type {};\n\ntemplate <class _Tp>\nstruct has_resize<_Tp, std::__void_t<decltype(std::declval<_Tp>().resize(\n\
    \                           std::declval<size_t>()))>> : std::true_type {};\n\n\
    template <class _Tp, class = void> struct has_mod : std::false_type {};\n\ntemplate\
    \ <class _Tp>\nstruct has_mod<_Tp, std::__void_t<decltype(_Tp::mod)>> : std::true_type\
    \ {};\n\ntemplate <class _Tp, class = void> struct is_integral_ext : std::false_type\
    \ {};\ntemplate <class _Tp>\nstruct is_integral_ext<\n    _Tp, typename std::enable_if<std::is_integral<_Tp>::value>::type>\n\
    \    : std::true_type {};\n\n#if __INT128_DEFINED__\n\ntemplate <> struct is_integral_ext<__int128_t>\
    \ : std::true_type {};\ntemplate <> struct is_integral_ext<__uint128_t> : std::true_type\
    \ {};\n\n#endif\n\n#if __cplusplus >= 201402\n\ntemplate <class _Tp>\nconstexpr\
    \ static bool is_integral_ext_v = is_integral_ext<_Tp>::value;\n\n#endif\n\ntemplate\
    \ <typename _Tp, typename = void> struct multiplicable_uint {\n  using type =\
    \ uint_least32_t;\n};\ntemplate <typename _Tp>\nstruct multiplicable_uint<\n \
    \   _Tp,\n    typename std::enable_if<(2 < sizeof(_Tp)) &&\n                 \
    \           (!__INT128_DEFINED__ || sizeof(_Tp) <= 4)>::type> {\n  using type\
    \ = uint_least64_t;\n};\n\n#if __INT128_DEFINED__\n\ntemplate <typename _Tp>\n\
    struct multiplicable_uint<_Tp,\n                          typename std::enable_if<(4\
    \ < sizeof(_Tp))>::type> {\n  using type = __uint128_t;\n};\n\n#endif\n\ntemplate\
    \ <typename _Tp> struct multiplicable_int {\n  using type =\n      typename std::make_signed<typename\
    \ multiplicable_uint<_Tp>::type>::type;\n};\n\ntemplate <typename _Tp> struct\
    \ multiplicable {\n  using type = std::conditional_t<\n      is_integral_ext<_Tp>::value,\n\
    \      std::conditional_t<std::is_signed<_Tp>::value,\n                      \
    \   typename multiplicable_int<_Tp>::type,\n                         typename\
    \ multiplicable_uint<_Tp>::type>,\n      _Tp>;\n};\n\ntemplate <class> struct\
    \ first_arg { using type = void; };\n\ntemplate <class _R, class _Tp, class...\
    \ _Args>\nstruct first_arg<_R(_Tp, _Args...)> {\n  using type = _Tp;\n};\n\ntemplate\
    \ <class _R, class _Tp, class... _Args>\nstruct first_arg<_R (*)(_Tp, _Args...)>\
    \ {\n  using type = _Tp;\n};\n\ntemplate <class _G, class _R, class _Tp, class...\
    \ _Args>\nstruct first_arg<_R (_G::*)(_Tp, _Args...)> {\n  using type = _Tp;\n\
    };\n\ntemplate <class _G, class _R, class _Tp, class... _Args>\nstruct first_arg<_R\
    \ (_G::*)(_Tp, _Args...) const> {\n  using type = _Tp;\n};\n\ntemplate <class\
    \ _Tp, class = void> struct parse_compare : first_arg<_Tp> {};\n\ntemplate <class\
    \ _Tp>\nstruct parse_compare<_Tp, std::__void_t<decltype(&_Tp::operator())>>\n\
    \    : first_arg<decltype(&_Tp::operator())> {};\n\ntemplate <class _Container,\
    \ class = void> struct get_dimension {\n  static constexpr size_t value = 0;\n\
    };\n\ntemplate <class _Container>\nstruct get_dimension<_Container,\n        \
    \             std::enable_if_t<has_begin<_Container>::value>> {\n  static constexpr\
    \ size_t value =\n      1 + get_dimension<typename std::iterator_traits<\n   \
    \           typename has_begin<_Container>::type>::value_type>::value;\n};\n\n\
    }  // namespace workspace\n#line 8 \"src/utils/hash.hpp\"\nnamespace workspace\
    \ {\ntemplate <class T, class = void> struct hash : std::hash<T> {};\n#if __cplusplus\
    \ >= 201703L\ntemplate <class Unique_bits_type>\nstruct hash<Unique_bits_type,\n\
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
  timestamp: '2022-04-06 15:02:09+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/library-checker/associative_array.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/associative_array.test.cpp
- /verify/test/library-checker/associative_array.test.cpp.html
title: test/library-checker/associative_array.test.cpp
---
