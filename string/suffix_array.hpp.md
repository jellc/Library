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
    links: []
  bundledCode: "#line 2 \"string/suffix_array.hpp\"\n#include <algorithm>\n#include\
    \ <vector>\n#include <numeric>\n#line 2 \"utils/sfinae.hpp\"\n#include <cstdint>\n\
    #include <iterator>\n#include <type_traits>\n\ntemplate <class type, template\
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
    \ < sizeof(T))>::type> {\n  using type = __uint128_t;\n};\n#line 6 \"string/suffix_array.hpp\"\
    \ntemplate <class str_type>\nclass suffix_array\n{\n    static constexpr size_t\
    \ npos = -1;\n    str_type str;\n    std::vector<size_t> sa, rank, lcp;\n\n  \
    \  void construct_sa()\n    {\n        std::iota(sa.begin(), sa.end(), 0);\n \
    \       std::sort(sa.begin(), sa.end(), [&](size_t i, size_t j){return str[i]\
    \ < str[j];});\n\n        for(size_t r{1}, c{}, *ptr{&sa.front()}, *tmp{ptr};\
    \ c != size(); ++r, ptr = tmp)\n            while(c != size() && str[*ptr] ==\
    \ str[*tmp])\n                ++c, rank[*tmp++] = r;\n\n        for(size_t k{1};\
    \ k < size(); k <<= 1)\n        {\n            auto comp = [&](size_t i, size_t\
    \ j) -> bool\n            {\n                if(rank[i] != rank[j]) return rank[i]\
    \ < rank[j];\n                return (i + k < size() ? rank[i + k] : 0) < (j +\
    \ k < size() ? rank[j + k] : 0);\n            };\n            std::sort(sa.begin(),\
    \ sa.end(), comp);\n\n            std::vector<size_t> next_rank(size());\n   \
    \         for(size_t r{1}, c{}, *ptr{&sa.front()}, *tmp{ptr}; c != size(); ++r,\
    \ ptr = tmp)\n                while(c != size() && !comp(*ptr, *tmp))\n      \
    \              ++c, next_rank[*tmp++] = r;\n            rank.swap(next_rank);\n\
    \        }\n\n        sa.emplace(sa.begin(), size());\n        rank.emplace_back(0);\n\
    \    }\n\n    void construct_lcp()\n    {\n        for(size_t i{}, h{}; i != size();\
    \ ++i, h = h ? h - 1 : 0)\n        {\n            for(size_t j{sa[rank[i] - 1]\
    \ + h}; i + h != size() && j != size(); ++j, ++h)\n                if(str[i +\
    \ h] != str[j]) break;\n            lcp[rank[i] - 1] = h;\n        }\n    }\n\n\
    public:\n    using value_type = element_type<str_type>;\n\n    std::vector<size_t>::const_iterator\
    \ begin() const { return sa.begin() + 1; }\n    std::vector<size_t>::const_iterator\
    \ end() const { return sa.end(); }\n\n    size_t operator[](size_t i) const {\
    \ return sa[i + 1]; }\n\n    size_t size() const { return std::size(str); }\n\n\
    \    template <class type = str_type, typename = typename type::value_type>\n\
    \    suffix_array(const str_type &_str) : str(_str), sa(size()), rank(size()),\
    \ lcp(size())\n    {\n        construct_sa();\n        construct_lcp();\n    }\n\
    \n    template <class type = str_type, std::enable_if_t<std::is_array<type>::value,\
    \ std::nullptr_t> = nullptr>\n    suffix_array(const str_type &_str) : sa(size()),\
    \ rank(size()), lcp(size())\n    {\n        std::copy(std::begin(_str), std::end(_str),\
    \ str);\n        construct_sa();\n        construct_lcp();\n    }\n\n    size_t\
    \ find(const str_type &key) const\n    {\n        using std::begin; using std::end;\n\
    \n        size_t lower{npos}, upper{size()};\n        while(upper - lower > 1)\n\
    \        {\n            size_t mid = (lower + upper) >> 1;\n            bool less\
    \ = false;\n            for(auto i{begin(str) + sa[mid]}, j{begin(key)}; j !=\
    \ end(key); ++i, ++j)\n            {\n                if(i == end(str) || *i <\
    \ *j)\n                {\n                    less = true;\n                 \
    \   break;\n                }\n                if(*i > *j) break;\n          \
    \  }\n            (less ? lower : upper) = mid;\n        }\n\n        if(upper\
    \ == size()) return npos;\n        for(auto i{begin(str) + sa[upper]}, j{begin(key)};\
    \ j != end(key); ++i, ++j)\n            if(i == end(str) || *i != *j)\n      \
    \          return npos;\n        return sa[upper];\n    }\n\n    const std::vector<size_t>\
    \ &lcp_array() const { return lcp; }\n}; // class suffix_array\n"
  code: "#pragma once\n#include <algorithm>\n#include <vector>\n#include <numeric>\n\
    #include \"utils/sfinae.hpp\"\ntemplate <class str_type>\nclass suffix_array\n\
    {\n    static constexpr size_t npos = -1;\n    str_type str;\n    std::vector<size_t>\
    \ sa, rank, lcp;\n\n    void construct_sa()\n    {\n        std::iota(sa.begin(),\
    \ sa.end(), 0);\n        std::sort(sa.begin(), sa.end(), [&](size_t i, size_t\
    \ j){return str[i] < str[j];});\n\n        for(size_t r{1}, c{}, *ptr{&sa.front()},\
    \ *tmp{ptr}; c != size(); ++r, ptr = tmp)\n            while(c != size() && str[*ptr]\
    \ == str[*tmp])\n                ++c, rank[*tmp++] = r;\n\n        for(size_t\
    \ k{1}; k < size(); k <<= 1)\n        {\n            auto comp = [&](size_t i,\
    \ size_t j) -> bool\n            {\n                if(rank[i] != rank[j]) return\
    \ rank[i] < rank[j];\n                return (i + k < size() ? rank[i + k] : 0)\
    \ < (j + k < size() ? rank[j + k] : 0);\n            };\n            std::sort(sa.begin(),\
    \ sa.end(), comp);\n\n            std::vector<size_t> next_rank(size());\n   \
    \         for(size_t r{1}, c{}, *ptr{&sa.front()}, *tmp{ptr}; c != size(); ++r,\
    \ ptr = tmp)\n                while(c != size() && !comp(*ptr, *tmp))\n      \
    \              ++c, next_rank[*tmp++] = r;\n            rank.swap(next_rank);\n\
    \        }\n\n        sa.emplace(sa.begin(), size());\n        rank.emplace_back(0);\n\
    \    }\n\n    void construct_lcp()\n    {\n        for(size_t i{}, h{}; i != size();\
    \ ++i, h = h ? h - 1 : 0)\n        {\n            for(size_t j{sa[rank[i] - 1]\
    \ + h}; i + h != size() && j != size(); ++j, ++h)\n                if(str[i +\
    \ h] != str[j]) break;\n            lcp[rank[i] - 1] = h;\n        }\n    }\n\n\
    public:\n    using value_type = element_type<str_type>;\n\n    std::vector<size_t>::const_iterator\
    \ begin() const { return sa.begin() + 1; }\n    std::vector<size_t>::const_iterator\
    \ end() const { return sa.end(); }\n\n    size_t operator[](size_t i) const {\
    \ return sa[i + 1]; }\n\n    size_t size() const { return std::size(str); }\n\n\
    \    template <class type = str_type, typename = typename type::value_type>\n\
    \    suffix_array(const str_type &_str) : str(_str), sa(size()), rank(size()),\
    \ lcp(size())\n    {\n        construct_sa();\n        construct_lcp();\n    }\n\
    \n    template <class type = str_type, std::enable_if_t<std::is_array<type>::value,\
    \ std::nullptr_t> = nullptr>\n    suffix_array(const str_type &_str) : sa(size()),\
    \ rank(size()), lcp(size())\n    {\n        std::copy(std::begin(_str), std::end(_str),\
    \ str);\n        construct_sa();\n        construct_lcp();\n    }\n\n    size_t\
    \ find(const str_type &key) const\n    {\n        using std::begin; using std::end;\n\
    \n        size_t lower{npos}, upper{size()};\n        while(upper - lower > 1)\n\
    \        {\n            size_t mid = (lower + upper) >> 1;\n            bool less\
    \ = false;\n            for(auto i{begin(str) + sa[mid]}, j{begin(key)}; j !=\
    \ end(key); ++i, ++j)\n            {\n                if(i == end(str) || *i <\
    \ *j)\n                {\n                    less = true;\n                 \
    \   break;\n                }\n                if(*i > *j) break;\n          \
    \  }\n            (less ? lower : upper) = mid;\n        }\n\n        if(upper\
    \ == size()) return npos;\n        for(auto i{begin(str) + sa[upper]}, j{begin(key)};\
    \ j != end(key); ++i, ++j)\n            if(i == end(str) || *i != *j)\n      \
    \          return npos;\n        return sa[upper];\n    }\n\n    const std::vector<size_t>\
    \ &lcp_array() const { return lcp; }\n}; // class suffix_array\n"
  dependsOn:
  - utils/sfinae.hpp
  isVerificationFile: false
  path: string/suffix_array.hpp
  requiredBy: []
  timestamp: '2020-10-10 01:30:31+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/suffix_array.test.cpp
  - test/library-checker/number_of_substrings.test.cpp
documentation_of: string/suffix_array.hpp
layout: document
redirect_from:
- /library/string/suffix_array.hpp
- /library/string/suffix_array.hpp.html
title: string/suffix_array.hpp
---
