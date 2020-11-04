---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: utils/sfinae.hpp
    title: utils/sfinae.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/library-checker/number_of_substrings.test.cpp
    title: test/library-checker/number_of_substrings.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/suffix_array.test.cpp
    title: test/library-checker/suffix_array.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Suffix array
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 310, in update\n    raise BundleErrorAt(path, i + 1, \"#pragma once found\
    \ in a non-first line\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ string/suffix_array.hpp: line 6: #pragma once found in a non-first line\n"
  code: "/*\n * @file suffix_array.hpp\n * @brief Suffix array\n */\n\n#pragma once\n\
    #include <algorithm>\n#include <numeric>\n#include <vector>\n\n#include \"utils/sfinae.hpp\"\
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
  - utils/sfinae.hpp
  isVerificationFile: false
  path: string/suffix_array.hpp
  requiredBy: []
  timestamp: '2020-11-04 17:56:57+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/number_of_substrings.test.cpp
  - test/library-checker/suffix_array.test.cpp
documentation_of: string/suffix_array.hpp
layout: document
redirect_from:
- /library/string/suffix_array.hpp
- /library/string/suffix_array.hpp.html
title: Suffix array
---
