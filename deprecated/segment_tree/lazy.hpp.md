---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"deprecated/segment_tree/lazy.hpp\"\n#include <cassert>\n\
    #include <vector>\n\ntemplate <class monoid, class endomorphism> class lazy_segment_tree\
    \ {\n  using size_type = typename std::vector<monoid>::size_type;\n  template\
    \ <class T> using container_type = std::vector<T>;\n\n  size_type size_orig, height,\
    \ size_ext;\n  container_type<monoid> data;\n  container_type<endomorphism> lazy;\n\
    \n  void recalc(const size_type node) {\n    data[node] = data[node << 1] + data[node\
    \ << 1 | 1];\n  }\n\n  void apply(size_type index, const endomorphism &endo) {\n\
    \    endo.apply(data[index]);\n    if (index < size_ext) lazy[index] *= endo;\n\
    \  }\n\n  void push(size_type index) {\n    if (index >= size_ext) return;\n \
    \   apply(index << 1, lazy[index]);\n    apply(index << 1 | 1, lazy[index]);\n\
    \    lazy[index] = endomorphism{};\n  }\n\n  template <class pred_type>\n  size_type\
    \ left_search_subtree(size_type index, const pred_type pred,\n               \
    \                 monoid mono) {\n    assert(index);\n    while (index < size_ext)\
    \ {\n      push(index);\n      const monoid tmp = data[(index <<= 1) | 1] + mono;\n\
    \      if (pred(tmp))\n        mono = tmp;\n      else\n        ++index;\n   \
    \ }\n    return ++index -= size_ext;\n  }\n\n  template <class pred_type>\n  size_type\
    \ right_search_subtree(size_type index, const pred_type pred,\n              \
    \                   monoid mono) {\n    assert(index);\n    while (index < size_ext)\
    \ {\n      push(index);\n      const monoid tmp = mono + data[index <<= 1];\n\
    \      if (pred(tmp)) ++index, mono = tmp;\n    }\n    return (index -= size_ext)\
    \ < size_orig ? index : size_orig;\n  }\n\n public:\n  lazy_segment_tree(const\
    \ size_type n = 0)\n      : size_orig{n},\n        height(n > 1 ? 32 - __builtin_clz(n\
    \ - 1) : 0),\n        size_ext{1u << height},\n        data(size_ext << 1),\n\
    \        lazy(size_ext) {}\n\n  lazy_segment_tree(const size_type n, const monoid\
    \ &init)\n      : lazy_segment_tree(n) {\n    std::fill(std::next(std::begin(data),\
    \ size_ext), std::end(data), init);\n    for (size_type i{size_ext}; --i;) recalc(i);\n\
    \  }\n\n  template <class iter_type, class value_type = typename std::iterator_traits<\n\
    \                                 iter_type>::value_type>\n  lazy_segment_tree(iter_type\
    \ first, iter_type last)\n      : size_orig(std::distance(first, last)),\n   \
    \     height(size_orig > 1 ? 32 - __builtin_clz(size_orig - 1) : 0),\n       \
    \ size_ext{1u << height},\n        data(size_ext << 1),\n        lazy(size_ext)\
    \ {\n    static_assert(std::is_constructible<monoid, value_type>::value,\n   \
    \               \"monoid(iter_type::value_type) is not constructible.\");\n  \
    \  for (auto iter{std::next(std::begin(data), size_ext)};\n         iter != std::end(data)\
    \ && first != last; ++iter, ++first)\n      *iter = monoid(*first);\n    for (size_type\
    \ i{size_ext}; --i;) recalc(i);\n  }\n\n  template <class container_type,\n  \
    \          typename = typename container_type::value_type>\n  lazy_segment_tree(const\
    \ container_type &cont)\n      : lazy_segment_tree(std::begin(cont), std::end(cont))\
    \ {}\n\n  size_type size() const { return size_orig; }\n  size_type capacity()\
    \ const { return size_ext; }\n\n  monoid operator[](size_type index) { return\
    \ fold(index, index + 1); }\n\n  void update(const size_type index, const endomorphism\
    \ &endo) {\n    update(index, index + 1, endo);\n  }\n\n  void update(size_type\
    \ first, size_type last, const endomorphism &endo) {\n    assert(last <= size_orig);\n\
    \    if (first >= last) return;\n    first += size_ext, last += size_ext - 1;\n\
    \    for (size_type i = height; i; --i) push(first >> i), push(last >> i);\n \
    \   for (size_type l = first, r = last + 1; last; l >>= 1, r >>= 1) {\n      if\
    \ (l < r) {\n        if (l & 1) apply(l++, endo);\n        if (r & 1) apply(--r,\
    \ endo);\n      }\n      if (first >>= 1, last >>= 1) {\n        recalc(first),\
    \ recalc(last);\n      }\n    }\n  }\n\n  monoid fold() { return fold(0, size_orig);\
    \ }\n\n  monoid fold(size_type first, size_type last) {\n    assert(last <= size_orig);\n\
    \    if (first >= last) return monoid{};\n    first += size_ext, last += size_ext\
    \ - 1;\n    monoid left_val{}, right_val{};\n    for (size_type l = first, r =\
    \ last + 1; last; l >>= 1, r >>= 1) {\n      if (l < r) {\n        if (l & 1)\
    \ left_val = left_val + data[l++];\n        if (r & 1) right_val = data[--r] +\
    \ right_val;\n      }\n      if (first >>= 1, last >>= 1) {\n        lazy[first].apply(left_val);\n\
    \        lazy[last].apply(right_val);\n      }\n    }\n    return left_val + right_val;\n\
    \  }\n\n  template <class pred_type>\n  size_type left_search(size_type right,\
    \ pred_type pred) {\n    assert(right <= size_orig);\n    right += size_ext -\
    \ 1;\n    for (size_type i{height}; i; --i) push(right >> i);\n    ++right;\n\
    \    monoid mono{};\n    for (size_type left{size_ext}; left != right; left >>=\
    \ 1, right >>= 1) {\n      if ((left & 1) != (right & 1)) {\n        const monoid\
    \ tmp = data[--right] + mono;\n        if (!pred(tmp)) return left_search_subtree(right,\
    \ pred, mono);\n        mono = tmp;\n      }\n    }\n    return 0;\n  }\n\n  template\
    \ <class pred_type>\n  size_type right_search(size_type left, pred_type pred)\
    \ {\n    assert(left <= size_orig);\n    left += size_ext;\n    for (size_type\
    \ i{height}; i; --i) push(left >> i);\n    monoid mono{};\n    for (size_type\
    \ right{size_ext << 1}; left != right;\n         left >>= 1, right >>= 1) {\n\
    \      if ((left & 1) != (right & 1)) {\n        const monoid tmp = mono + data[left];\n\
    \        if (!pred(tmp)) return right_search_subtree(left, pred, mono);\n    \
    \    mono = tmp;\n        ++left;\n      }\n    }\n    return size_orig;\n  }\n\
    };  // class lazy_segment_tree\n"
  code: "#pragma once\n#include <cassert>\n#include <vector>\n\ntemplate <class monoid,\
    \ class endomorphism> class lazy_segment_tree {\n  using size_type = typename\
    \ std::vector<monoid>::size_type;\n  template <class T> using container_type =\
    \ std::vector<T>;\n\n  size_type size_orig, height, size_ext;\n  container_type<monoid>\
    \ data;\n  container_type<endomorphism> lazy;\n\n  void recalc(const size_type\
    \ node) {\n    data[node] = data[node << 1] + data[node << 1 | 1];\n  }\n\n  void\
    \ apply(size_type index, const endomorphism &endo) {\n    endo.apply(data[index]);\n\
    \    if (index < size_ext) lazy[index] *= endo;\n  }\n\n  void push(size_type\
    \ index) {\n    if (index >= size_ext) return;\n    apply(index << 1, lazy[index]);\n\
    \    apply(index << 1 | 1, lazy[index]);\n    lazy[index] = endomorphism{};\n\
    \  }\n\n  template <class pred_type>\n  size_type left_search_subtree(size_type\
    \ index, const pred_type pred,\n                                monoid mono) {\n\
    \    assert(index);\n    while (index < size_ext) {\n      push(index);\n    \
    \  const monoid tmp = data[(index <<= 1) | 1] + mono;\n      if (pred(tmp))\n\
    \        mono = tmp;\n      else\n        ++index;\n    }\n    return ++index\
    \ -= size_ext;\n  }\n\n  template <class pred_type>\n  size_type right_search_subtree(size_type\
    \ index, const pred_type pred,\n                                 monoid mono)\
    \ {\n    assert(index);\n    while (index < size_ext) {\n      push(index);\n\
    \      const monoid tmp = mono + data[index <<= 1];\n      if (pred(tmp)) ++index,\
    \ mono = tmp;\n    }\n    return (index -= size_ext) < size_orig ? index : size_orig;\n\
    \  }\n\n public:\n  lazy_segment_tree(const size_type n = 0)\n      : size_orig{n},\n\
    \        height(n > 1 ? 32 - __builtin_clz(n - 1) : 0),\n        size_ext{1u <<\
    \ height},\n        data(size_ext << 1),\n        lazy(size_ext) {}\n\n  lazy_segment_tree(const\
    \ size_type n, const monoid &init)\n      : lazy_segment_tree(n) {\n    std::fill(std::next(std::begin(data),\
    \ size_ext), std::end(data), init);\n    for (size_type i{size_ext}; --i;) recalc(i);\n\
    \  }\n\n  template <class iter_type, class value_type = typename std::iterator_traits<\n\
    \                                 iter_type>::value_type>\n  lazy_segment_tree(iter_type\
    \ first, iter_type last)\n      : size_orig(std::distance(first, last)),\n   \
    \     height(size_orig > 1 ? 32 - __builtin_clz(size_orig - 1) : 0),\n       \
    \ size_ext{1u << height},\n        data(size_ext << 1),\n        lazy(size_ext)\
    \ {\n    static_assert(std::is_constructible<monoid, value_type>::value,\n   \
    \               \"monoid(iter_type::value_type) is not constructible.\");\n  \
    \  for (auto iter{std::next(std::begin(data), size_ext)};\n         iter != std::end(data)\
    \ && first != last; ++iter, ++first)\n      *iter = monoid(*first);\n    for (size_type\
    \ i{size_ext}; --i;) recalc(i);\n  }\n\n  template <class container_type,\n  \
    \          typename = typename container_type::value_type>\n  lazy_segment_tree(const\
    \ container_type &cont)\n      : lazy_segment_tree(std::begin(cont), std::end(cont))\
    \ {}\n\n  size_type size() const { return size_orig; }\n  size_type capacity()\
    \ const { return size_ext; }\n\n  monoid operator[](size_type index) { return\
    \ fold(index, index + 1); }\n\n  void update(const size_type index, const endomorphism\
    \ &endo) {\n    update(index, index + 1, endo);\n  }\n\n  void update(size_type\
    \ first, size_type last, const endomorphism &endo) {\n    assert(last <= size_orig);\n\
    \    if (first >= last) return;\n    first += size_ext, last += size_ext - 1;\n\
    \    for (size_type i = height; i; --i) push(first >> i), push(last >> i);\n \
    \   for (size_type l = first, r = last + 1; last; l >>= 1, r >>= 1) {\n      if\
    \ (l < r) {\n        if (l & 1) apply(l++, endo);\n        if (r & 1) apply(--r,\
    \ endo);\n      }\n      if (first >>= 1, last >>= 1) {\n        recalc(first),\
    \ recalc(last);\n      }\n    }\n  }\n\n  monoid fold() { return fold(0, size_orig);\
    \ }\n\n  monoid fold(size_type first, size_type last) {\n    assert(last <= size_orig);\n\
    \    if (first >= last) return monoid{};\n    first += size_ext, last += size_ext\
    \ - 1;\n    monoid left_val{}, right_val{};\n    for (size_type l = first, r =\
    \ last + 1; last; l >>= 1, r >>= 1) {\n      if (l < r) {\n        if (l & 1)\
    \ left_val = left_val + data[l++];\n        if (r & 1) right_val = data[--r] +\
    \ right_val;\n      }\n      if (first >>= 1, last >>= 1) {\n        lazy[first].apply(left_val);\n\
    \        lazy[last].apply(right_val);\n      }\n    }\n    return left_val + right_val;\n\
    \  }\n\n  template <class pred_type>\n  size_type left_search(size_type right,\
    \ pred_type pred) {\n    assert(right <= size_orig);\n    right += size_ext -\
    \ 1;\n    for (size_type i{height}; i; --i) push(right >> i);\n    ++right;\n\
    \    monoid mono{};\n    for (size_type left{size_ext}; left != right; left >>=\
    \ 1, right >>= 1) {\n      if ((left & 1) != (right & 1)) {\n        const monoid\
    \ tmp = data[--right] + mono;\n        if (!pred(tmp)) return left_search_subtree(right,\
    \ pred, mono);\n        mono = tmp;\n      }\n    }\n    return 0;\n  }\n\n  template\
    \ <class pred_type>\n  size_type right_search(size_type left, pred_type pred)\
    \ {\n    assert(left <= size_orig);\n    left += size_ext;\n    for (size_type\
    \ i{height}; i; --i) push(left >> i);\n    monoid mono{};\n    for (size_type\
    \ right{size_ext << 1}; left != right;\n         left >>= 1, right >>= 1) {\n\
    \      if ((left & 1) != (right & 1)) {\n        const monoid tmp = mono + data[left];\n\
    \        if (!pred(tmp)) return right_search_subtree(left, pred, mono);\n    \
    \    mono = tmp;\n        ++left;\n      }\n    }\n    return size_orig;\n  }\n\
    };  // class lazy_segment_tree\n"
  dependsOn: []
  isVerificationFile: false
  path: deprecated/segment_tree/lazy.hpp
  requiredBy: []
  timestamp: '2020-09-10 02:20:46+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: deprecated/segment_tree/lazy.hpp
layout: document
redirect_from:
- /library/deprecated/segment_tree/lazy.hpp
- /library/deprecated/segment_tree/lazy.hpp.html
title: deprecated/segment_tree/lazy.hpp
---
