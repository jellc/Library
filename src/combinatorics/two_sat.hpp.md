---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/library-checker/two_sat.test.cpp
    title: test/library-checker/two_sat.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: 2-SAT
    links: []
  bundledCode: "#line 2 \"src/combinatorics/two_sat.hpp\"\n\n/**\n * @file two_sat.hpp\n\
    \ * @brief 2-SAT\n */\n\n#include <cassert>\n#include <cstdint>\n#include <vector>\n\
    \nnamespace workspace {\n\n// Linear time 2-SAT solver.\nclass two_sat : std::vector<std::vector<uint_least32_t>>\
    \ {\n public:\n  using size_type = uint_least32_t;\n\n private:\n  using container_type\
    \ = std::vector<std::vector<size_type>>;\n\n  size_type *__tag = nullptr, *__top\
    \ = nullptr;\n\n  size_type node_size() const noexcept { return container_type::size();\
    \ }\n\n  size_type index(size_type __x) const noexcept {\n    return __x < ~__x\
    \ ? __x << 1 : ~__x << 1 | 1;\n  }\n\n  bool dfs(size_type __s, size_type __d)\
    \ noexcept {\n    if (~__tag[__s]) return __tag[__s];\n\n    __tag[ *__top++ =\
    \ __s] = --__d;\n    bool __ret = true;\n\n    for (size_type __t : container_type::operator[](__s))\
    \ {\n      if (!dfs(__t, __d)) __ret = false;\n      if (__tag[__s] < __tag[__t])\
    \ __tag[__s] = __tag[__t];\n    }\n\n    if (__tag[__s ^ 1] == 1) __ret = false;\n\
    \n    if (__tag[__s] == __d) do\n        __tag[*--__top] = __ret;\n      while\
    \ (*__top != __s);\n\n    return __ret;\n  }\n\n public:\n  two_sat() noexcept\
    \ {}\n\n  two_sat(size_type __n) noexcept : container_type(__n << 1) {}\n\n  ~two_sat()\
    \ {\n    delete[] __tag;\n    delete[] __top;\n  }\n\n  using container_type::empty;\n\
    \n  size_type size() const noexcept { return node_size() >> 1; }\n\n  size_type\
    \ add_variable() noexcept {\n    container_type::emplace_back(), container_type::emplace_back();\n\
    \    return size() - 1;\n  }\n\n  auto add_variables(size_type __n) noexcept {\n\
    \    container_type::reserve(node_size() + __n);\n    typename container_type::value_type\
    \ __vs(__n);\n\n    for (auto &__v : __vs) __v = add_variable();\n    return __vs;\n\
    \  }\n\n  void add_clause(size_type __x) noexcept {\n    __x = index(__x);\n \
    \   assert(__x < node_size());\n\n    container_type::operator[](__x ^ 1).emplace_back(__x);\n\
    \  }\n\n  void add_clause(size_type __x, size_type __y) noexcept {\n    __x =\
    \ index(__x), __y = index(__y);\n    assert(__x < node_size()), assert(__y < node_size());\n\
    \n    container_type::operator[](__x ^ 1).emplace_back(__y),\n        container_type::operator[](__y\
    \ ^ 1).emplace_back(__x);\n  }\n\n  template <class _Iterator>\n  size_type atmost_one(_Iterator\
    \ __first, _Iterator __last) noexcept {\n    container_type::reserve(node_size()\
    \ + std::distance(__first, __last) + 1);\n    auto __any = add_variable();\n\n\
    \    for (add_clause(~__any); __first != __last; ++__first) {\n      auto __next\
    \ = add_variable();\n      add_clause(~__any, ~*__first), add_clause(~__any, __next),\n\
    \          add_clause(~*__first, __next), __any = __next;\n    }\n\n    return\
    \ __any;\n  }\n\n  template <class _Iterator>\n  size_type exactly_one(_Iterator\
    \ __first, _Iterator __last) noexcept {\n    auto __any = atmost_one(__first,\
    \ __last);\n    add_clause(__any);\n    return __any;\n  }\n\n  bool run() noexcept\
    \ {\n    delete[] __tag;\n    delete[] __top;\n    __tag = new size_type[node_size()],\
    \ __top = new size_type[node_size()];\n\n    std::fill_n(__tag, node_size(), -1);\n\
    \    for (size_type __s = 0; __s != node_size(); ++__s) dfs(__s, -1);\n\n    for\
    \ (size_type __i = 0; __i != node_size(); __i += 2)\n      if (__tag[__i] == __tag[__i\
    \ ^ 1]) return false;\n\n    return true;\n  }\n\n  bool operator[](size_type\
    \ __i) const noexcept {\n    __i = index(__i);\n    assert(__i < node_size());\n\
    \n    return __tag[__i];\n  }\n};\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file two_sat.hpp\n * @brief 2-SAT\n */\n\n#include\
    \ <cassert>\n#include <cstdint>\n#include <vector>\n\nnamespace workspace {\n\n\
    // Linear time 2-SAT solver.\nclass two_sat : std::vector<std::vector<uint_least32_t>>\
    \ {\n public:\n  using size_type = uint_least32_t;\n\n private:\n  using container_type\
    \ = std::vector<std::vector<size_type>>;\n\n  size_type *__tag = nullptr, *__top\
    \ = nullptr;\n\n  size_type node_size() const noexcept { return container_type::size();\
    \ }\n\n  size_type index(size_type __x) const noexcept {\n    return __x < ~__x\
    \ ? __x << 1 : ~__x << 1 | 1;\n  }\n\n  bool dfs(size_type __s, size_type __d)\
    \ noexcept {\n    if (~__tag[__s]) return __tag[__s];\n\n    __tag[ *__top++ =\
    \ __s] = --__d;\n    bool __ret = true;\n\n    for (size_type __t : container_type::operator[](__s))\
    \ {\n      if (!dfs(__t, __d)) __ret = false;\n      if (__tag[__s] < __tag[__t])\
    \ __tag[__s] = __tag[__t];\n    }\n\n    if (__tag[__s ^ 1] == 1) __ret = false;\n\
    \n    if (__tag[__s] == __d) do\n        __tag[*--__top] = __ret;\n      while\
    \ (*__top != __s);\n\n    return __ret;\n  }\n\n public:\n  two_sat() noexcept\
    \ {}\n\n  two_sat(size_type __n) noexcept : container_type(__n << 1) {}\n\n  ~two_sat()\
    \ {\n    delete[] __tag;\n    delete[] __top;\n  }\n\n  using container_type::empty;\n\
    \n  size_type size() const noexcept { return node_size() >> 1; }\n\n  size_type\
    \ add_variable() noexcept {\n    container_type::emplace_back(), container_type::emplace_back();\n\
    \    return size() - 1;\n  }\n\n  auto add_variables(size_type __n) noexcept {\n\
    \    container_type::reserve(node_size() + __n);\n    typename container_type::value_type\
    \ __vs(__n);\n\n    for (auto &__v : __vs) __v = add_variable();\n    return __vs;\n\
    \  }\n\n  void add_clause(size_type __x) noexcept {\n    __x = index(__x);\n \
    \   assert(__x < node_size());\n\n    container_type::operator[](__x ^ 1).emplace_back(__x);\n\
    \  }\n\n  void add_clause(size_type __x, size_type __y) noexcept {\n    __x =\
    \ index(__x), __y = index(__y);\n    assert(__x < node_size()), assert(__y < node_size());\n\
    \n    container_type::operator[](__x ^ 1).emplace_back(__y),\n        container_type::operator[](__y\
    \ ^ 1).emplace_back(__x);\n  }\n\n  template <class _Iterator>\n  size_type atmost_one(_Iterator\
    \ __first, _Iterator __last) noexcept {\n    container_type::reserve(node_size()\
    \ + std::distance(__first, __last) + 1);\n    auto __any = add_variable();\n\n\
    \    for (add_clause(~__any); __first != __last; ++__first) {\n      auto __next\
    \ = add_variable();\n      add_clause(~__any, ~*__first), add_clause(~__any, __next),\n\
    \          add_clause(~*__first, __next), __any = __next;\n    }\n\n    return\
    \ __any;\n  }\n\n  template <class _Iterator>\n  size_type exactly_one(_Iterator\
    \ __first, _Iterator __last) noexcept {\n    auto __any = atmost_one(__first,\
    \ __last);\n    add_clause(__any);\n    return __any;\n  }\n\n  bool run() noexcept\
    \ {\n    delete[] __tag;\n    delete[] __top;\n    __tag = new size_type[node_size()],\
    \ __top = new size_type[node_size()];\n\n    std::fill_n(__tag, node_size(), -1);\n\
    \    for (size_type __s = 0; __s != node_size(); ++__s) dfs(__s, -1);\n\n    for\
    \ (size_type __i = 0; __i != node_size(); __i += 2)\n      if (__tag[__i] == __tag[__i\
    \ ^ 1]) return false;\n\n    return true;\n  }\n\n  bool operator[](size_type\
    \ __i) const noexcept {\n    __i = index(__i);\n    assert(__i < node_size());\n\
    \n    return __tag[__i];\n  }\n};\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/combinatorics/two_sat.hpp
  requiredBy: []
  timestamp: '2021-07-22 13:31:22+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/two_sat.test.cpp
documentation_of: src/combinatorics/two_sat.hpp
layout: document
redirect_from:
- /library/src/combinatorics/two_sat.hpp
- /library/src/combinatorics/two_sat.hpp.html
title: 2-SAT
---
