---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: src/string/suffix_array.hpp
    title: Suffix Array
  - icon: ':question:'
    path: src/utils/io/stream.hpp
    title: src/utils/io/stream.hpp
  - icon: ':question:'
    path: src/utils/sfinae.hpp
    title: src/utils/sfinae.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/suffixarray
    links:
    - https://judge.yosupo.jp/problem/suffixarray
  bundledCode: "#line 1 \"test/library-checker/suffix_array.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/suffixarray\"\n#include <bits/stdc++.h>\n\n\
    #line 2 \"src/string/suffix_array.hpp\"\n\n/*\n * @file suffix_array.hpp\n * @brief\
    \ Suffix Array\n */\n\n#line 11 \"src/string/suffix_array.hpp\"\n\n#line 4 \"\
    src/utils/sfinae.hpp\"\n#include <type_traits>\n\ntemplate <class type, template\
    \ <class> class trait>\nusing enable_if_trait_type = typename std::enable_if<trait<type>::value>::type;\n\
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
    \ < sizeof(T))>::type> {\n  using type = __uint128_t;\n};\n#line 13 \"src/string/suffix_array.hpp\"\
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
    \ &lcp_array() const { return lcp; }\n};\n\n}  // namespace workspace\n#line 4\
    \ \"src/utils/io/stream.hpp\"\n\n#line 6 \"src/utils/io/stream.hpp\"\n\nnamespace\
    \ std {\ntemplate <class T, class U> istream &operator>>(istream &is, pair<T,\
    \ U> &p) {\n  return is >> p.first >> p.second;\n}\ntemplate <class T, class U>\n\
    ostream &operator<<(ostream &os, const pair<T, U> &p) {\n  return os << p.first\
    \ << ' ' << p.second;\n}\ntemplate <class tuple_t, size_t index> struct tuple_is\
    \ {\n  static istream &apply(istream &is, tuple_t &t) {\n    tuple_is<tuple_t,\
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
    \ // namespace std\n#line 6 \"test/library-checker/suffix_array.test.cpp\"\n\n\
    int main() {\n  std::string s;\n  std::cin >> s;\n  std::cout << workspace::suffix_array<std::string>(s)\
    \ << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/suffixarray\"\n#include\
    \ <bits/stdc++.h>\n\n#include \"src/string/suffix_array.hpp\"\n#include \"src/utils/io/stream.hpp\"\
    \n\nint main() {\n  std::string s;\n  std::cin >> s;\n  std::cout << workspace::suffix_array<std::string>(s)\
    \ << \"\\n\";\n}\n"
  dependsOn:
  - src/string/suffix_array.hpp
  - src/utils/sfinae.hpp
  - src/utils/io/stream.hpp
  isVerificationFile: true
  path: test/library-checker/suffix_array.test.cpp
  requiredBy: []
  timestamp: '2020-11-16 22:30:50+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/library-checker/suffix_array.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/suffix_array.test.cpp
- /verify/test/library-checker/suffix_array.test.cpp.html
title: test/library-checker/suffix_array.test.cpp
---
