---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: utils/sfinae.hpp
    title: utils/sfinae.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/library-checker/range_affine_range_sum.test.cpp
    title: test/library-checker/range_affine_range_sum.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 2 \"data_structure/segment_tree/lazy.hpp\"\n#include <cassert>\n\
    #include <vector>\n\n#line 2 \"utils/sfinae.hpp\"\n#include <cstdint>\n#include\
    \ <type_traits>\n\ntemplate <class type, template <class> class trait>\nusing\
    \ enable_if_trait_type = typename std::enable_if<trait<type>::value>::type;\n\n\
    template <class Container>\nusing element_type = typename std::decay<decltype(\n\
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
    \ < sizeof(T))>::type> {\n  using type = __uint128_t;\n};\n#line 6 \"data_structure/segment_tree/lazy.hpp\"\
    \ntemplate <class Monoid, class Endomorphism,\n          template <class...> class\
    \ Container_tmpl = std::vector>\nclass lazy_segment_tree {\n  size_t size_orig,\
    \ height, size_ext;\n  Container_tmpl<Monoid> data;\n  Container_tmpl<Endomorphism>\
    \ lazy;\n\n  static_assert(std::is_same<Monoid, decltype(Monoid{} + Monoid{})>::value,\n\
    \                \"\\'Monoid\\' has no proper binary operator+.\");\n\n  static_assert(std::is_same<Endomorphism,\n\
    \                             decltype(Endomorphism{} * Endomorphism{})>::value,\n\
    \                \"\\'Endomorphism\\' has no proper binary operator*.\");\n\n\
    \  static_assert(\n      std::is_same<Monoid, decltype(Monoid{} * Endomorphism{})>::value,\n\
    \      \"\\'Endomorphism\\' is not applicable to \\'Monoid\\'.\");\n\n  void pull(const\
    \ size_t &node) {\n    data[node] = data[node << 1] + data[node << 1 | 1];\n \
    \ }\n\n  void apply(const size_t &node, const Endomorphism &endo) {\n    data[node]\
    \ = data[node] * endo;\n    if (node < size_ext) lazy[node] = lazy[node] * endo;\n\
    \  }\n\n  void push(const size_t &node) {\n    if (node >= size_ext) return;\n\
    \    apply(node << 1, lazy[node]);\n    apply(node << 1 | 1, lazy[node]);\n  \
    \  lazy[node] = Endomorphism{};\n  }\n\n  template <class Pred>\n  size_t left_search_subtree(size_t\
    \ node, Pred pred, Monoid mono) {\n    assert(node);\n    while (node < size_ext)\
    \ {\n      push(node);\n      const Monoid &tmp = data[(node <<= 1) | 1] + mono;\n\
    \      if (pred(tmp))\n        mono = tmp;\n      else\n        ++node;\n    }\n\
    \    return ++node -= size_ext;\n  }\n\n  template <class Pred>\n  size_t right_search_subtree(size_t\
    \ node, Pred pred, Monoid mono) {\n    assert(node);\n    while (node < size_ext)\
    \ {\n      push(node);\n      const Monoid &tmp = mono + data[node <<= 1];\n \
    \     if (pred(tmp)) ++node, mono = tmp;\n    }\n    return (node -= size_ext)\
    \ < size_orig ? node : size_orig;\n  }\n\n public:\n  lazy_segment_tree(const\
    \ size_t n = 0)\n      : size_orig{n},\n        height(n > 1 ? 32 - __builtin_clz(n\
    \ - 1) : 0),\n        size_ext{1u << height},\n        data(size_ext << 1),\n\
    \        lazy(size_ext) {}\n\n  lazy_segment_tree(const size_t &n, const Monoid\
    \ &init)\n      : lazy_segment_tree(n) {\n    std::fill(std::next(std::begin(data),\
    \ size_ext), std::end(data), init);\n    for (size_t i{size_ext}; --i;) pull(i);\n\
    \  }\n\n  template <class iter_type, class value_type = typename std::iterator_traits<\n\
    \                                 iter_type>::value_type>\n  lazy_segment_tree(iter_type\
    \ first, iter_type last)\n      : size_orig(std::distance(first, last)),\n   \
    \     height(size_orig > 1 ? 32 - __builtin_clz(size_orig - 1) : 0),\n       \
    \ size_ext{1u << height},\n        data(size_ext << 1),\n        lazy(size_ext)\
    \ {\n    static_assert(std::is_constructible<Monoid, value_type>::value,\n   \
    \               \"Monoid(iter_type::value_type) is not constructible.\");\n  \
    \  for (auto iter{std::next(std::begin(data), size_ext)};\n         iter != std::end(data)\
    \ && first != last; ++iter, ++first)\n      *iter = Monoid(*first);\n    for (size_t\
    \ i{size_ext}; --i;) pull(i);\n  }\n\n  template <class Container, typename =\
    \ typename Container::value_type>\n  lazy_segment_tree(const Container &cont)\n\
    \      : lazy_segment_tree(std::begin(cont), std::end(cont)) {}\n\n  size_t size()\
    \ const { return size_orig; }\n  size_t capacity() const { return size_ext; }\n\
    \n  Monoid operator[](const size_t &index) { return fold(index, index + 1); }\n\
    \n  void update(const size_t &index, const Endomorphism &endo) {\n    update(index,\
    \ index + 1, endo);\n  }\n\n  void update(size_t first, size_t last, const Endomorphism\
    \ &endo) {\n    assert(last <= size_orig);\n    if (first >= last) return;\n \
    \   first += size_ext, last += size_ext - 1;\n    for (size_t i = height; i; --i)\
    \ push(first >> i), push(last >> i);\n    for (size_t l = first, r = last + 1;\
    \ last; l >>= 1, r >>= 1) {\n      if (l < r) {\n        if (l & 1) apply(l++,\
    \ endo);\n        if (r & 1) apply(--r, endo);\n      }\n      if (first >>= 1,\
    \ last >>= 1) {\n        pull(first), pull(last);\n      }\n    }\n  }\n\n  Monoid\
    \ fold() { return fold(0, size_orig); }\n\n  Monoid fold(size_t first, size_t\
    \ last) {\n    assert(last <= size_orig);\n    if (first >= last) return Monoid{};\n\
    \    first += size_ext, last += size_ext - 1;\n    Monoid left_val{}, right_val{};\n\
    \    for (size_t l = first, r = last + 1; last; l >>= 1, r >>= 1) {\n      if\
    \ (l < r) {\n        if (l & 1) left_val = left_val + data[l++];\n        if (r\
    \ & 1) right_val = data[--r] + right_val;\n      }\n      if (first >>= 1, last\
    \ >>= 1) {\n        left_val = left_val * lazy[first];\n        right_val = right_val\
    \ * lazy[last];\n      }\n    }\n    return left_val + right_val;\n  }\n\n  template\
    \ <class Pred> size_t left_search(size_t right, Pred pred) {\n    assert(right\
    \ <= size_orig);\n    right += size_ext - 1;\n    for (size_t i{height}; i; --i)\
    \ push(right >> i);\n    ++right;\n    Monoid mono{};\n    for (size_t left{size_ext};\
    \ left != right; left >>= 1, right >>= 1) {\n      if ((left & 1) != (right &\
    \ 1)) {\n        const Monoid &tmp = data[--right] + mono;\n        if (!pred(tmp))\
    \ return left_search_subtree(right, pred, mono);\n        mono = tmp;\n      }\n\
    \    }\n    return 0;\n  }\n\n  template <class Pred> size_t right_search(size_t\
    \ left, Pred pred) {\n    assert(left <= size_orig);\n    left += size_ext;\n\
    \    for (size_t i{height}; i; --i) push(left >> i);\n    Monoid mono{};\n   \
    \ for (size_t right{size_ext << 1}; left != right; left >>= 1, right >>= 1) {\n\
    \      if ((left & 1) != (right & 1)) {\n        const Monoid &tmp = mono + data[left];\n\
    \        if (!pred(tmp)) return right_search_subtree(left, pred, mono);\n    \
    \    mono = tmp;\n        ++left;\n      }\n    }\n    return size_orig;\n  }\n\
    };  // class lazy_segment_tree\n"
  code: "#pragma once\n#include <cassert>\n#include <vector>\n\n#include \"utils/sfinae.hpp\"\
    \ntemplate <class Monoid, class Endomorphism,\n          template <class...> class\
    \ Container_tmpl = std::vector>\nclass lazy_segment_tree {\n  size_t size_orig,\
    \ height, size_ext;\n  Container_tmpl<Monoid> data;\n  Container_tmpl<Endomorphism>\
    \ lazy;\n\n  static_assert(std::is_same<Monoid, decltype(Monoid{} + Monoid{})>::value,\n\
    \                \"\\'Monoid\\' has no proper binary operator+.\");\n\n  static_assert(std::is_same<Endomorphism,\n\
    \                             decltype(Endomorphism{} * Endomorphism{})>::value,\n\
    \                \"\\'Endomorphism\\' has no proper binary operator*.\");\n\n\
    \  static_assert(\n      std::is_same<Monoid, decltype(Monoid{} * Endomorphism{})>::value,\n\
    \      \"\\'Endomorphism\\' is not applicable to \\'Monoid\\'.\");\n\n  void pull(const\
    \ size_t &node) {\n    data[node] = data[node << 1] + data[node << 1 | 1];\n \
    \ }\n\n  void apply(const size_t &node, const Endomorphism &endo) {\n    data[node]\
    \ = data[node] * endo;\n    if (node < size_ext) lazy[node] = lazy[node] * endo;\n\
    \  }\n\n  void push(const size_t &node) {\n    if (node >= size_ext) return;\n\
    \    apply(node << 1, lazy[node]);\n    apply(node << 1 | 1, lazy[node]);\n  \
    \  lazy[node] = Endomorphism{};\n  }\n\n  template <class Pred>\n  size_t left_search_subtree(size_t\
    \ node, Pred pred, Monoid mono) {\n    assert(node);\n    while (node < size_ext)\
    \ {\n      push(node);\n      const Monoid &tmp = data[(node <<= 1) | 1] + mono;\n\
    \      if (pred(tmp))\n        mono = tmp;\n      else\n        ++node;\n    }\n\
    \    return ++node -= size_ext;\n  }\n\n  template <class Pred>\n  size_t right_search_subtree(size_t\
    \ node, Pred pred, Monoid mono) {\n    assert(node);\n    while (node < size_ext)\
    \ {\n      push(node);\n      const Monoid &tmp = mono + data[node <<= 1];\n \
    \     if (pred(tmp)) ++node, mono = tmp;\n    }\n    return (node -= size_ext)\
    \ < size_orig ? node : size_orig;\n  }\n\n public:\n  lazy_segment_tree(const\
    \ size_t n = 0)\n      : size_orig{n},\n        height(n > 1 ? 32 - __builtin_clz(n\
    \ - 1) : 0),\n        size_ext{1u << height},\n        data(size_ext << 1),\n\
    \        lazy(size_ext) {}\n\n  lazy_segment_tree(const size_t &n, const Monoid\
    \ &init)\n      : lazy_segment_tree(n) {\n    std::fill(std::next(std::begin(data),\
    \ size_ext), std::end(data), init);\n    for (size_t i{size_ext}; --i;) pull(i);\n\
    \  }\n\n  template <class iter_type, class value_type = typename std::iterator_traits<\n\
    \                                 iter_type>::value_type>\n  lazy_segment_tree(iter_type\
    \ first, iter_type last)\n      : size_orig(std::distance(first, last)),\n   \
    \     height(size_orig > 1 ? 32 - __builtin_clz(size_orig - 1) : 0),\n       \
    \ size_ext{1u << height},\n        data(size_ext << 1),\n        lazy(size_ext)\
    \ {\n    static_assert(std::is_constructible<Monoid, value_type>::value,\n   \
    \               \"Monoid(iter_type::value_type) is not constructible.\");\n  \
    \  for (auto iter{std::next(std::begin(data), size_ext)};\n         iter != std::end(data)\
    \ && first != last; ++iter, ++first)\n      *iter = Monoid(*first);\n    for (size_t\
    \ i{size_ext}; --i;) pull(i);\n  }\n\n  template <class Container, typename =\
    \ typename Container::value_type>\n  lazy_segment_tree(const Container &cont)\n\
    \      : lazy_segment_tree(std::begin(cont), std::end(cont)) {}\n\n  size_t size()\
    \ const { return size_orig; }\n  size_t capacity() const { return size_ext; }\n\
    \n  Monoid operator[](const size_t &index) { return fold(index, index + 1); }\n\
    \n  void update(const size_t &index, const Endomorphism &endo) {\n    update(index,\
    \ index + 1, endo);\n  }\n\n  void update(size_t first, size_t last, const Endomorphism\
    \ &endo) {\n    assert(last <= size_orig);\n    if (first >= last) return;\n \
    \   first += size_ext, last += size_ext - 1;\n    for (size_t i = height; i; --i)\
    \ push(first >> i), push(last >> i);\n    for (size_t l = first, r = last + 1;\
    \ last; l >>= 1, r >>= 1) {\n      if (l < r) {\n        if (l & 1) apply(l++,\
    \ endo);\n        if (r & 1) apply(--r, endo);\n      }\n      if (first >>= 1,\
    \ last >>= 1) {\n        pull(first), pull(last);\n      }\n    }\n  }\n\n  Monoid\
    \ fold() { return fold(0, size_orig); }\n\n  Monoid fold(size_t first, size_t\
    \ last) {\n    assert(last <= size_orig);\n    if (first >= last) return Monoid{};\n\
    \    first += size_ext, last += size_ext - 1;\n    Monoid left_val{}, right_val{};\n\
    \    for (size_t l = first, r = last + 1; last; l >>= 1, r >>= 1) {\n      if\
    \ (l < r) {\n        if (l & 1) left_val = left_val + data[l++];\n        if (r\
    \ & 1) right_val = data[--r] + right_val;\n      }\n      if (first >>= 1, last\
    \ >>= 1) {\n        left_val = left_val * lazy[first];\n        right_val = right_val\
    \ * lazy[last];\n      }\n    }\n    return left_val + right_val;\n  }\n\n  template\
    \ <class Pred> size_t left_search(size_t right, Pred pred) {\n    assert(right\
    \ <= size_orig);\n    right += size_ext - 1;\n    for (size_t i{height}; i; --i)\
    \ push(right >> i);\n    ++right;\n    Monoid mono{};\n    for (size_t left{size_ext};\
    \ left != right; left >>= 1, right >>= 1) {\n      if ((left & 1) != (right &\
    \ 1)) {\n        const Monoid &tmp = data[--right] + mono;\n        if (!pred(tmp))\
    \ return left_search_subtree(right, pred, mono);\n        mono = tmp;\n      }\n\
    \    }\n    return 0;\n  }\n\n  template <class Pred> size_t right_search(size_t\
    \ left, Pred pred) {\n    assert(left <= size_orig);\n    left += size_ext;\n\
    \    for (size_t i{height}; i; --i) push(left >> i);\n    Monoid mono{};\n   \
    \ for (size_t right{size_ext << 1}; left != right; left >>= 1, right >>= 1) {\n\
    \      if ((left & 1) != (right & 1)) {\n        const Monoid &tmp = mono + data[left];\n\
    \        if (!pred(tmp)) return right_search_subtree(left, pred, mono);\n    \
    \    mono = tmp;\n        ++left;\n      }\n    }\n    return size_orig;\n  }\n\
    };  // class lazy_segment_tree\n"
  dependsOn:
  - utils/sfinae.hpp
  isVerificationFile: false
  path: data_structure/segment_tree/lazy.hpp
  requiredBy: []
  timestamp: '2020-09-17 16:18:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/range_affine_range_sum.test.cpp
documentation_of: data_structure/segment_tree/lazy.hpp
layout: document
redirect_from:
- /library/data_structure/segment_tree/lazy.hpp
- /library/data_structure/segment_tree/lazy.hpp.html
title: data_structure/segment_tree/lazy.hpp
---
