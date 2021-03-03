---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/utils/sfinae.hpp
    title: SFINAE
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/library-checker/number_of_substrings.test.cpp
    title: test/library-checker/number_of_substrings.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/suffix_array.test.cpp
    title: test/library-checker/suffix_array.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Suffix Array
    links: []
  bundledCode: "#line 2 \"src/string/suffix_array.hpp\"\n\n/*\n * @file suffix_array.hpp\n\
    \ * @brief Suffix Array\n */\n\n#include <algorithm>\n#include <numeric>\n#include\
    \ <vector>\n\n#line 2 \"src/utils/sfinae.hpp\"\n\n/**\n * @file sfinae.hpp\n *\
    \ @brief SFINAE\n */\n\n#include <cstdint>\n#include <iterator>\n#include <type_traits>\n\
    \n#ifndef __INT128_DEFINED__\n\n#ifdef __SIZEOF_INT128__\n#define __INT128_DEFINED__\
    \ 1\n#else\n#define __INT128_DEFINED__ 0\n#endif\n\n#endif\n\nnamespace std {\n\
    \n#if __INT128_DEFINED__\n\ntemplate <> struct make_signed<__uint128_t> { using\
    \ type = __int128_t; };\ntemplate <> struct make_signed<__int128_t> { using type\
    \ = __int128_t; };\n\ntemplate <> struct make_unsigned<__uint128_t> { using type\
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
    \ }\n};\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/*\n * @file suffix_array.hpp\n * @brief Suffix Array\n */\n\
    \n#include <algorithm>\n#include <numeric>\n#include <vector>\n\n#include \"../utils/sfinae.hpp\"\
    \n\nnamespace workspace {\n\n/*\n * @class suffix_array\n * @brief construct SA\
    \ and LCP array.\n * @tparam str_type the type of string\n */\ntemplate <class\
    \ str_type> class suffix_array {\n  str_type str;\n  std::vector<size_t> sa, rank,\
    \ lcp;\n\n  void construct_sa() {\n    std::iota(sa.begin(), sa.end(), 0);\n \
    \   std::sort(sa.begin(), sa.end(),\n              [&](size_t i, size_t j) { return\
    \ str[i] < str[j]; });\n\n    for (size_t r{1}, c{}, *ptr{&sa.front()}, *tmp{ptr};\
    \ c != size();\n         ++r, ptr = tmp)\n      while (c != size() && str[*ptr]\
    \ == str[*tmp]) ++c, rank[*tmp++] = r;\n\n    for (size_t k{1}; k < size(); k\
    \ <<= 1) {\n      auto comp = [&](size_t i, size_t j) -> bool {\n        if (rank[i]\
    \ != rank[j]) return rank[i] < rank[j];\n        return (i + k < size() ? rank[i\
    \ + k] : 0) <\n               (j + k < size() ? rank[j + k] : 0);\n      };\n\
    \      std::sort(sa.begin(), sa.end(), comp);\n\n      std::vector<size_t> next_rank(size());\n\
    \      for (size_t r{1}, c{}, *ptr{&sa.front()}, *tmp{ptr}; c != size();\n   \
    \        ++r, ptr = tmp)\n        while (c != size() && !comp(*ptr, *tmp)) ++c,\
    \ next_rank[*tmp++] = r;\n      rank.swap(next_rank);\n    }\n\n    sa.emplace(sa.begin(),\
    \ size());\n    rank.emplace_back(0);\n  }\n\n  void construct_lcp() {\n    for\
    \ (size_t i{}, h{}; i != size(); ++i, h = h ? h - 1 : 0) {\n      for (size_t\
    \ j{sa[rank[i] - 1] + h}; i + h != size() && j != size();\n           ++j, ++h)\n\
    \        if (str[i + h] != str[j]) break;\n      lcp[rank[i] - 1] = h;\n    }\n\
    \  }\n\n public:\n  static constexpr size_t npos = -1;\n  using char_type = element_type<str_type>;\n\
    \n  std::vector<size_t>::const_iterator begin() const { return sa.begin() + 1;\
    \ }\n\n  std::vector<size_t>::const_iterator end() const { return sa.end(); }\n\
    \n  /*\n   * @fn operator[]\n   * @brief find the i-th suffix\n   * @param i the\
    \ rank\n   * @return index of the suffix\n   */\n  size_t operator[](size_t i)\
    \ const { return sa[i + 1]; }\n\n  /*\n   * @fn size\n   * @return length of the\
    \ string\n   */\n  size_t size() const { return std::size(str); }\n\n  template\
    \ <class type = str_type, typename = typename type::value_type>\n  suffix_array(const\
    \ str_type &_str)\n      : str(_str), sa(size()), rank(size()), lcp(size()) {\n\
    \    construct_sa();\n    construct_lcp();\n  }\n\n  template <class type = str_type,\
    \ std::enable_if_t<std::is_array<type>::value,\n                             \
    \                       std::nullptr_t> = nullptr>\n  suffix_array(const str_type\
    \ &_str) : sa(size()), rank(size()), lcp(size()) {\n    std::copy(std::begin(_str),\
    \ std::end(_str), str);\n    construct_sa();\n    construct_lcp();\n  }\n\n  /*\n\
    \   * @fn find\n   * @brief find (key) as a substring\n   * @param key\n   * @return\
    \ index if found, npos if not found\n   */\n  size_t find(const str_type &key)\
    \ const {\n    using std::begin;\n    using std::end;\n\n    size_t lower{npos},\
    \ upper{size()};\n    while (upper - lower > 1) {\n      size_t mid = (lower +\
    \ upper) >> 1;\n      bool less = false;\n      for (auto i{begin(str) + sa[mid]},\
    \ j{begin(key)}; j != end(key);\n           ++i, ++j) {\n        if (i == end(str)\
    \ || *i < *j) {\n          less = true;\n          break;\n        }\n       \
    \ if (*i > *j) break;\n      }\n      (less ? lower : upper) = mid;\n    }\n\n\
    \    if (upper == size()) return npos;\n    for (auto i{begin(str) + sa[upper]},\
    \ j{begin(key)}; j != end(key); ++i, ++j)\n      if (i == end(str) || *i != *j)\
    \ return npos;\n    return sa[upper];\n  }\n\n  /*\n   * @return lengths of LCP\
    \ of each adjacent pairs in the suffix\n   * array\n   */\n  const std::vector<size_t>\
    \ &lcp_array() const { return lcp; }\n};\n\n}  // namespace workspace\n"
  dependsOn:
  - src/utils/sfinae.hpp
  isVerificationFile: false
  path: src/string/suffix_array.hpp
  requiredBy: []
  timestamp: '2021-01-22 09:52:55+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/suffix_array.test.cpp
  - test/library-checker/number_of_substrings.test.cpp
documentation_of: src/string/suffix_array.hpp
layout: document
redirect_from:
- /library/src/string/suffix_array.hpp
- /library/src/string/suffix_array.hpp.html
title: Suffix Array
---
