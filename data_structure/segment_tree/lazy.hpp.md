---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 193, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: utils/sfinae.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n#include <cassert>\n#include <queue>\n#include <vector>\n\n\
    #include \"algebra/system/monoid.hpp\"\n#include \"utils/sfinae.hpp\"\n#include\
    \ \"waitlist.hpp\"\n\ntemplate <class Monoid, class Endomorphism,\n          class\
    \ Monoid_container = std::vector<Monoid>,\n          class Endomorphism_container\
    \ = std::vector<Endomorphism>>\nclass lazy_segment_tree {\n  static_assert(std::is_same<Monoid,\
    \ mapped_type<Monoid_container>>::value);\n\n  static_assert(\n      std::is_same<Endomorphism,\
    \ mapped_type<Endomorphism_container>>::value);\n\n  static_assert(std::is_same<Monoid,\
    \ decltype(Monoid{} + Monoid{})>::value,\n                \"\\'Monoid\\' has no\
    \ proper binary operator+.\");\n\n  static_assert(std::is_same<Endomorphism,\n\
    \                             decltype(Endomorphism{} * Endomorphism{})>::value,\n\
    \                \"\\'Endomorphism\\' has no proper binary operator*.\");\n\n\
    \  static_assert(\n      std::is_same<Monoid, decltype(Monoid{} * Endomorphism{})>::value,\n\
    \      \"\\'Endomorphism\\' is not applicable to \\'Monoid\\'.\");\n\n  size_t\
    \ size_orig, height, size_ext;\n  Monoid_container data;\n  Endomorphism_container\
    \ lazy;\n  internal::waitlist wait;\n\n  void repair() {\n    while (!wait.empty())\
    \ {\n      const size_t index = wait.pop() >> 1;\n      if (index && wait.push(index))\
    \ pull(index);\n    }\n  }\n\n  void apply(size_t node, const Endomorphism &endo)\
    \ {\n    data[node] = data[node] * endo;\n    if (node < size_ext) lazy[node]\
    \ = lazy[node] * endo;\n  }\n\n  void push(size_t node) {\n    if (!(node < size_ext))\
    \ return;\n    apply(node << 1, lazy[node]);\n    apply(node << 1 | 1, lazy[node]);\n\
    \    lazy[node] = Endomorphism{};\n  }\n\n  void pull(size_t node) { data[node]\
    \ = data[node << 1] + data[node << 1 | 1]; }\n\n  template <class Pred>\n  size_t\
    \ left_partition_subtree(size_t node, Pred pred, Monoid mono) {\n    assert(node);\n\
    \    while (node < size_ext) {\n      push(node);\n      const Monoid &tmp = data[(node\
    \ <<= 1) | 1] + mono;\n      if (pred(tmp))\n        mono = tmp;\n      else\n\
    \        ++node;\n    }\n    return ++node -= size_ext;\n  }\n\n  template <class\
    \ Pred>\n  size_t right_partition_subtree(size_t node, Pred pred, Monoid mono)\
    \ {\n    assert(node);\n    while (node < size_ext) {\n      push(node);\n   \
    \   const Monoid &tmp = mono + data[node <<= 1];\n      if (pred(tmp)) ++node,\
    \ mono = tmp;\n    }\n    return (node -= size_ext) < size_orig ? node : size_orig;\n\
    \  }\n\n public:\n  using value_type = Monoid;\n\n  lazy_segment_tree(size_t n\
    \ = 0)\n      : size_orig{n},\n        height(n > 1 ? 32 - __builtin_clz(n - 1)\
    \ : 0),\n        size_ext{1u << height},\n        data(size_ext << 1),\n     \
    \   lazy(size_ext),\n        wait(size_ext << 1) {}\n\n  lazy_segment_tree(size_t\
    \ n, const Monoid &init) : lazy_segment_tree(n) {\n    std::fill(std::next(std::begin(data),\
    \ size_ext), std::end(data), init);\n    for (size_t i{size_ext}; --i;) pull(i);\n\
    \  }\n\n  template <class iter_type, class value_type = typename std::iterator_traits<\n\
    \                                 iter_type>::value_type>\n  lazy_segment_tree(iter_type\
    \ first, iter_type last)\n      : size_orig(std::distance(first, last)),\n   \
    \     height(size_orig > 1 ? 32 - __builtin_clz(size_orig - 1) : 0),\n       \
    \ size_ext{1u << height},\n        data(size_ext << 1),\n        lazy(size_ext),\n\
    \        wait(size_ext << 1) {\n    static_assert(std::is_constructible<Monoid,\
    \ value_type>::value,\n                  \"Monoid(iter_type::value_type) is not\
    \ constructible.\");\n    for (auto iter{std::next(std::begin(data), size_ext)};\n\
    \         iter != std::end(data) && first != last; ++iter, ++first)\n      *iter\
    \ = Monoid(*first);\n    for (size_t i{size_ext}; --i;) pull(i);\n  }\n\n  template\
    \ <class Container, typename = element_type<Container>>\n  lazy_segment_tree(const\
    \ Container &cont)\n      : lazy_segment_tree(std::begin(cont), std::end(cont))\
    \ {}\n\n  size_t size() const { return size_orig; }\n\n  size_t capacity() const\
    \ { return size_ext; }\n\n  Monoid &operator[](size_t index) {\n    assert(index\
    \ < size_orig);\n    index |= size_ext;\n    wait.push(index);\n    for (size_t\
    \ i = height; i; --i) push(index >> i);\n    return data[index];\n  }\n\n  void\
    \ update(size_t index, const Endomorphism &endo) {\n    update(index, index +\
    \ 1, endo);\n  }\n\n  void update(size_t first, size_t last, const Endomorphism\
    \ &endo) {\n    assert(last <= size_orig);\n    repair();\n    if (first >= last)\
    \ return;\n    first += size_ext, last += size_ext - 1;\n    for (size_t i = height;\
    \ i; --i) push(first >> i), push(last >> i);\n    for (size_t l = first, r = last\
    \ + 1; last; l >>= 1, r >>= 1) {\n      if (l < r) {\n        if (l & 1) apply(l++,\
    \ endo);\n        if (r & 1) apply(--r, endo);\n      }\n      if (first >>= 1,\
    \ last >>= 1) {\n        pull(first), pull(last);\n      }\n    }\n  }\n\n  Monoid\
    \ fold() { return fold(0, size_orig); }\n\n  Monoid fold(size_t first, size_t\
    \ last) {\n    assert(last <= size_orig);\n    repair();\n    if (first >= last)\
    \ return Monoid{};\n    first += size_ext, last += size_ext - 1;\n    Monoid left_val{},\
    \ right_val{};\n    for (size_t l = first, r = last + 1; last; l >>= 1, r >>=\
    \ 1) {\n      if (l < r) {\n        if (l & 1) left_val = left_val + data[l++];\n\
    \        if (r & 1) right_val = data[--r] + right_val;\n      }\n      if (first\
    \ >>= 1, last >>= 1) {\n        left_val = left_val * lazy[first];\n        right_val\
    \ = right_val * lazy[last];\n      }\n    }\n    return left_val + right_val;\n\
    \  }\n\n  template <class Pred> size_t left_partition(size_t right, Pred pred)\
    \ {\n    assert(right <= size_orig);\n    repair();\n    right += size_ext - 1;\n\
    \    for (size_t i{height}; i; --i) push(right >> i);\n    ++right;\n    Monoid\
    \ mono{};\n    for (size_t left{size_ext}; left != right; left >>= 1, right >>=\
    \ 1) {\n      if ((left & 1) != (right & 1)) {\n        const Monoid &tmp = data[--right]\
    \ + mono;\n        if (!pred(tmp)) return left_partition_subtree(right, pred,\
    \ mono);\n        mono = tmp;\n      }\n    }\n    return 0;\n  }\n\n  template\
    \ <class Pred> size_t right_partition(size_t left, Pred pred) {\n    assert(left\
    \ <= size_orig);\n    repair();\n    left += size_ext;\n    for (size_t i{height};\
    \ i; --i) push(left >> i);\n    Monoid mono{};\n    for (size_t right{size_ext\
    \ << 1}; left != right; left >>= 1, right >>= 1) {\n      if ((left & 1) != (right\
    \ & 1)) {\n        const Monoid &tmp = mono + data[left];\n        if (!pred(tmp))\
    \ return right_partition_subtree(left, pred, mono);\n        mono = tmp;\n   \
    \     ++left;\n      }\n    }\n    return size_orig;\n  }\n};  // class lazy_segment_tree\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/segment_tree/lazy.hpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: data_structure/segment_tree/lazy.hpp
layout: document
redirect_from:
- /library/data_structure/segment_tree/lazy.hpp
- /library/data_structure/segment_tree/lazy.hpp.html
title: data_structure/segment_tree/lazy.hpp
---
