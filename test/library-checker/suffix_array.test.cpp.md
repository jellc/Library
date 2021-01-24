---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/string/suffix_array.hpp
    title: Suffix Array
  - icon: ':heavy_check_mark:'
    path: src/utils/io/ostream.hpp
    title: Output Stream
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
    PROBLEM: https://judge.yosupo.jp/problem/suffixarray
    links:
    - https://judge.yosupo.jp/problem/suffixarray
  bundledCode: "#line 1 \"test/library-checker/suffix_array.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/suffixarray\"\n\n#include <iostream>\n\n#line\
    \ 2 \"src/string/suffix_array.hpp\"\n\n/*\n * @file suffix_array.hpp\n * @brief\
    \ Suffix Array\n */\n\n#include <algorithm>\n#include <numeric>\n#include <vector>\n\
    \n#line 2 \"src/utils/sfinae.hpp\"\n\n/**\n * @file sfinae.hpp\n * @brief SFINAE\n\
    \ */\n\n#include <cstdint>\n#include <iterator>\n#include <type_traits>\n\n#ifndef\
    \ __INT128_DEFINED__\n\n#ifdef __SIZEOF_INT128__\n#define __INT128_DEFINED__ 1\n\
    #else\n#define __INT128_DEFINED__ 0\n#endif\n\n#endif\n\nnamespace std {\n\n#if\
    \ __INT128_DEFINED__\n\ntemplate <> struct make_signed<__uint128_t> { using type\
    \ = __int128_t; };\ntemplate <> struct make_signed<__int128_t> { using type =\
    \ __int128_t; };\n\ntemplate <> struct make_unsigned<__uint128_t> { using type\
    \ = __uint128_t; };\ntemplate <> struct make_unsigned<__int128_t> { using type\
    \ = __uint128_t; };\n\n#endif\n\n}  // namespace std\n\nnamespace workspace {\n\
    \ntemplate <class Tp, class... Args> struct variadic_front { using type = Tp;\
    \ };\n\ntemplate <class... Args> struct variadic_back;\n\ntemplate <class Tp>\
    \ struct variadic_back<Tp> { using type = Tp; };\n\ntemplate <class Tp, class...\
    \ Args> struct variadic_back<Tp, Args...> {\n  using type = typename variadic_back<Args...>::type;\n\
    };\n\ntemplate <class type, template <class> class trait>\nusing enable_if_trait_type\
    \ = typename std::enable_if<trait<type>::value>::type;\n\ntemplate <class Container>\n\
    using element_type = typename std::decay<decltype(\n    *std::begin(std::declval<Container&>()))>::type;\n\
    \ntemplate <class T, class = std::nullptr_t>\nstruct has_begin : std::false_type\
    \ {};\n\ntemplate <class T>\nstruct has_begin<T, decltype(std::begin(std::declval<T>()),\
    \ nullptr)>\n    : std::true_type {};\n\ntemplate <class T, class = int> struct\
    \ mapped_of {\n  using type = element_type<T>;\n};\ntemplate <class T>\nstruct\
    \ mapped_of<T,\n                 typename std::pair<int, typename T::mapped_type>::first_type>\
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
    \ 13 \"src/string/suffix_array.hpp\"\n\nnamespace workspace {\n\n/*\n * @class\
    \ suffix_array\n * @brief construct SA and LCP array.\n * @tparam str_type the\
    \ type of string\n */\ntemplate <class str_type> class suffix_array {\n  str_type\
    \ str;\n  std::vector<size_t> sa, rank, lcp;\n\n  void construct_sa() {\n    std::iota(sa.begin(),\
    \ sa.end(), 0);\n    std::sort(sa.begin(), sa.end(),\n              [&](size_t\
    \ i, size_t j) { return str[i] < str[j]; });\n\n    for (size_t r{1}, c{}, *ptr{&sa.front()},\
    \ *tmp{ptr}; c != size();\n         ++r, ptr = tmp)\n      while (c != size()\
    \ && str[*ptr] == str[*tmp]) ++c, rank[*tmp++] = r;\n\n    for (size_t k{1}; k\
    \ < size(); k <<= 1) {\n      auto comp = [&](size_t i, size_t j) -> bool {\n\
    \        if (rank[i] != rank[j]) return rank[i] < rank[j];\n        return (i\
    \ + k < size() ? rank[i + k] : 0) <\n               (j + k < size() ? rank[j +\
    \ k] : 0);\n      };\n      std::sort(sa.begin(), sa.end(), comp);\n\n      std::vector<size_t>\
    \ next_rank(size());\n      for (size_t r{1}, c{}, *ptr{&sa.front()}, *tmp{ptr};\
    \ c != size();\n           ++r, ptr = tmp)\n        while (c != size() && !comp(*ptr,\
    \ *tmp)) ++c, next_rank[*tmp++] = r;\n      rank.swap(next_rank);\n    }\n\n \
    \   sa.emplace(sa.begin(), size());\n    rank.emplace_back(0);\n  }\n\n  void\
    \ construct_lcp() {\n    for (size_t i{}, h{}; i != size(); ++i, h = h ? h - 1\
    \ : 0) {\n      for (size_t j{sa[rank[i] - 1] + h}; i + h != size() && j != size();\n\
    \           ++j, ++h)\n        if (str[i + h] != str[j]) break;\n      lcp[rank[i]\
    \ - 1] = h;\n    }\n  }\n\n public:\n  static constexpr size_t npos = -1;\n  using\
    \ char_type = element_type<str_type>;\n\n  std::vector<size_t>::const_iterator\
    \ begin() const { return sa.begin() + 1; }\n\n  std::vector<size_t>::const_iterator\
    \ end() const { return sa.end(); }\n\n  /*\n   * @fn operator[]\n   * @brief find\
    \ the i-th suffix\n   * @param i the rank\n   * @return index of the suffix\n\
    \   */\n  size_t operator[](size_t i) const { return sa[i + 1]; }\n\n  /*\n  \
    \ * @fn size\n   * @return length of the string\n   */\n  size_t size() const\
    \ { return std::size(str); }\n\n  template <class type = str_type, typename =\
    \ typename type::value_type>\n  suffix_array(const str_type &_str)\n      : str(_str),\
    \ sa(size()), rank(size()), lcp(size()) {\n    construct_sa();\n    construct_lcp();\n\
    \  }\n\n  template <class type = str_type, std::enable_if_t<std::is_array<type>::value,\n\
    \                                                    std::nullptr_t> = nullptr>\n\
    \  suffix_array(const str_type &_str) : sa(size()), rank(size()), lcp(size())\
    \ {\n    std::copy(std::begin(_str), std::end(_str), str);\n    construct_sa();\n\
    \    construct_lcp();\n  }\n\n  /*\n   * @fn find\n   * @brief find (key) as a\
    \ substring\n   * @param key\n   * @return index if found, npos if not found\n\
    \   */\n  size_t find(const str_type &key) const {\n    using std::begin;\n  \
    \  using std::end;\n\n    size_t lower{npos}, upper{size()};\n    while (upper\
    \ - lower > 1) {\n      size_t mid = (lower + upper) >> 1;\n      bool less =\
    \ false;\n      for (auto i{begin(str) + sa[mid]}, j{begin(key)}; j != end(key);\n\
    \           ++i, ++j) {\n        if (i == end(str) || *i < *j) {\n          less\
    \ = true;\n          break;\n        }\n        if (*i > *j) break;\n      }\n\
    \      (less ? lower : upper) = mid;\n    }\n\n    if (upper == size()) return\
    \ npos;\n    for (auto i{begin(str) + sa[upper]}, j{begin(key)}; j != end(key);\
    \ ++i, ++j)\n      if (i == end(str) || *i != *j) return npos;\n    return sa[upper];\n\
    \  }\n\n  /*\n   * @return lengths of LCP of each adjacent pairs in the suffix\n\
    \   * array\n   */\n  const std::vector<size_t> &lcp_array() const { return lcp;\
    \ }\n};\n\n}  // namespace workspace\n#line 2 \"src/utils/io/ostream.hpp\"\n\n\
    /**\n * @file ostream.hpp\n * @brief Output Stream\n */\n\n#include <tuple>\n\n\
    namespace workspace {\n\n/**\n * @brief Stream insertion operator for std::pair.\n\
    \ *\n * @param __os Output stream\n * @param __p Pair\n * @return Reference to\
    \ __os.\n */\ntemplate <class Os, class T1, class T2>\nOs &operator<<(Os &__os,\
    \ const std::pair<T1, T2> &__p) {\n  return __os << __p.first << ' ' << __p.second;\n\
    }\n\n/**\n * @brief Stream insertion operator for std::tuple.\n *\n * @param __os\
    \ Output stream\n * @param __t Tuple\n * @return Reference to __os.\n */\ntemplate\
    \ <class Os, class Tp, size_t N = 0>\ntypename std::enable_if<bool(std::tuple_size<Tp>::value\
    \ + 1), Os &>::type\noperator<<(Os &__os, const Tp &__t) {\n  if constexpr (N\
    \ != std::tuple_size<Tp>::value) {\n    if constexpr (N) __os << ' ';\n    __os\
    \ << std::get<N>(__t);\n    operator<<<Os, Tp, N + 1>(__os, __t);\n  }\n  return\
    \ __os;\n}\n\ntemplate <class Os, class Container,\n          typename = decltype(std::begin(std::declval<Container>()))>\n\
    typename std::enable_if<\n    !std::is_same<typename std::decay<Container>::type,\
    \ std::string>::value &&\n        !std::is_same<typename std::decay<Container>::type,\
    \ char *>::value,\n    Os &>::type\noperator<<(Os &__os, const Container &__cont)\
    \ {\n  bool __h = true;\n  for (auto &&__e : __cont) __h ? __h = 0 : (__os <<\
    \ ' ', 0), __os << __e;\n  return __os;\n}\n\n#ifdef __SIZEOF_INT128__\n\n/**\n\
    \ * @brief Stream insertion operator for __int128_t.\n *\n * @param __os Output\
    \ Stream\n * @param __x 128-bit integer\n * @return Reference to __os.\n */\n\
    template <class Os> Os &operator<<(Os &__os, __int128_t __x) {\n  if (!__x) return\
    \ __os << '0';\n  if (__x < 0) __os << '-';\n  char __s[40], *__p = __s;\n  while\
    \ (__x) {\n    auto __d = __x % 10;\n    *__p++ = '0' + (__x < 0 ? -__d : __d);\n\
    \    __x /= 10;\n  }\n  *__p = 0;\n  for (char *__t = __s; __t < --__p; ++__t)\
    \ *__t ^= *__p ^= *__t ^= *__p;\n  return __os << __s;\n}\n\n/**\n * @brief Stream\
    \ insertion operator for __uint128_t.\n *\n * @param __os Output Stream\n * @param\
    \ __x 128-bit unsigned integer\n * @return Reference to __os.\n */\ntemplate <class\
    \ Os> Os &operator<<(Os &__os, __uint128_t __x) {\n  if (!__x) return __os <<\
    \ '0';\n  char __s[40], *__p = __s;\n  while (__x) *__p++ = '0' + __x % 10, __x\
    \ /= 10;\n  *__p = 0;\n  for (char *__t = __s; __t < --__p; ++__t) *__t ^= *__p\
    \ ^= *__t ^= *__p;\n  return __os << __s;\n}\n\n#endif\n\n}  // namespace workspace\n\
    #line 7 \"test/library-checker/suffix_array.test.cpp\"\n\nint main() {\n  std::string\
    \ s;\n  std::cin >> s;\n  std::cout << workspace::suffix_array<std::string>(s)\
    \ << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/suffixarray\"\n\n#include\
    \ <iostream>\n\n#include \"src/string/suffix_array.hpp\"\n#include \"src/utils/io/ostream.hpp\"\
    \n\nint main() {\n  std::string s;\n  std::cin >> s;\n  std::cout << workspace::suffix_array<std::string>(s)\
    \ << \"\\n\";\n}\n"
  dependsOn:
  - src/string/suffix_array.hpp
  - src/utils/sfinae.hpp
  - src/utils/io/ostream.hpp
  isVerificationFile: true
  path: test/library-checker/suffix_array.test.cpp
  requiredBy: []
  timestamp: '2021-01-24 20:27:26+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/library-checker/suffix_array.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/suffix_array.test.cpp
- /verify/test/library-checker/suffix_array.test.cpp.html
title: test/library-checker/suffix_array.test.cpp
---
