---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Segment Tree
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 193, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: algebra/system/monoid.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n\n/*\n * @file basic.hpp\n * @brief Segment Tree\n */\n\n#include\
    \ <cassert>\n#include <queue>\n#include <vector>\n\n#include \"algebra/system/monoid.hpp\"\
    \n#include \"src/utils/sfinae.hpp\"\n#include \"waitings.hpp\"\n\nnamespace workspace\
    \ {\n\ntemplate <class Monoid, class Container = std::vector<Monoid>>\nclass segment_tree\
    \ {\n  static_assert(std::is_same<Monoid, mapped_type<Container>>::value);\n\n\
    \  size_t size_orig, height, size_ext;\n  Container data;\n  internal::waitings\
    \ wait;\n\n  void repair() {\n    while (!wait.empty()) {\n      const size_t\
    \ index = wait.pop() >> 1;\n      if (index && wait.push(index)) pull(index);\n\
    \    }\n  }\n\n  void pull(const size_t node) {\n    data[node] = data[node <<\
    \ 1] + data[node << 1 | 1];\n  }\n\n  template <class Pred>\n  size_t left_partition_subtree(size_t\
    \ index, const Pred pred,\n                                Monoid mono) const\
    \ {\n    assert(index);\n    while (index < size_ext) {\n      const Monoid tmp\
    \ = data[(index <<= 1) | 1] + mono;\n      if (pred(tmp))\n        mono = tmp;\n\
    \      else\n        ++index;\n    }\n    return ++index -= size_ext;\n  }\n\n\
    \  template <class Pred>\n  size_t right_partition_subtree(size_t index, const\
    \ Pred pred,\n                                 Monoid mono) const {\n    assert(index);\n\
    \    while (index < size_ext) {\n      const Monoid tmp = mono + data[index <<=\
    \ 1];\n      if (pred(tmp)) ++index, mono = tmp;\n    }\n    return (index -=\
    \ size_ext) < size_orig ? index : size_orig;\n  }\n\n public:\n  using value_type\
    \ = Monoid;\n\n  segment_tree(const size_t n = 0)\n      : size_orig{n},\n   \
    \     height(n > 1 ? 32 - __builtin_clz(n - 1) : 0),\n        size_ext{1u << height},\n\
    \        data(size_ext << 1),\n        wait(size_ext << 1) {}\n\n  segment_tree(const\
    \ size_t n, const Monoid &init) : segment_tree(n) {\n    std::fill(std::next(std::begin(data),\
    \ size_ext), std::end(data), init);\n    for (size_t i{size_ext}; --i;) pull(i);\n\
    \  }\n\n  template <class iter_type, class value_type = typename std::iterator_traits<\n\
    \                                 iter_type>::value_type>\n  segment_tree(iter_type\
    \ first, iter_type last)\n      : size_orig(std::distance(first, last)),\n   \
    \     height(size_orig > 1 ? 32 - __builtin_clz(size_orig - 1) : 0),\n       \
    \ size_ext{1u << height},\n        data(size_ext << 1),\n        wait(size_ext\
    \ << 1) {\n    static_assert(std::is_constructible<Monoid, value_type>::value,\n\
    \                  \"Monoid(iter_type::value_type) is not constructible.\");\n\
    \    for (auto iter{std::next(std::begin(data), size_ext)};\n         iter !=\
    \ std::end(data) && first != last; ++iter, ++first)\n      *iter = Monoid{*first};\n\
    \    for (size_t i{size_ext}; --i;) pull(i);\n  }\n\n  template <class Cont, typename\
    \ = typename Cont::value_type>\n  segment_tree(const Cont &cont)\n      : segment_tree(std::begin(cont),\
    \ std::end(cont)) {}\n\n  size_t size() const { return size_orig; }\n  size_t\
    \ capacity() const { return size_ext; }\n\n  // reference to the element at the\
    \ index.\n  Monoid &operator[](size_t index) {\n    assert(index < size_orig);\n\
    \    wait.push(index |= size_ext);\n    return data[index];\n  }\n\n  // const\
    \ reference to the element at the index.\n  const Monoid &operator[](size_t index)\
    \ const {\n    assert(index < size_orig);\n    return data[index |= size_orig];\n\
    \  }\n\n  Monoid fold(size_t first, size_t last) {\n    assert(last <= size_orig);\n\
    \    repair();\n    Monoid leftval{}, rightval{};\n    first += size_ext, last\
    \ += size_ext;\n    while (first < last) {\n      if (first & 1) leftval = leftval\
    \ + data[first++];\n      if (last & 1) rightval = data[--last] + rightval;\n\
    \      first >>= 1, last >>= 1;\n    }\n    return leftval + rightval;\n  }\n\n\
    \  Monoid fold() { return fold(0, size_orig); }\n\n  template <class Pred> size_t\
    \ left_partition(size_t right, Pred pred) {\n    assert(right <= size_orig);\n\
    \    repair();\n    right += size_ext;\n    Monoid mono{};\n    for (size_t left{size_ext};\
    \ left != right; left >>= 1, right >>= 1) {\n      if ((left & 1) != (right &\
    \ 1)) {\n        const Monoid tmp = data[--right] + mono;\n        if (!pred(tmp))\
    \ return left_partition_subtree(right, pred, mono);\n        mono = tmp;\n   \
    \   }\n    }\n    return 0;\n  }\n\n  template <class Pred> size_t right_partition(size_t\
    \ left, Pred pred) {\n    assert(left <= size_orig);\n    repair();\n    left\
    \ += size_ext;\n    Monoid mono{};\n    for (size_t right{size_ext << 1}; left\
    \ != right; left >>= 1, right >>= 1) {\n      if ((left & 1) != (right & 1)) {\n\
    \        const Monoid tmp = mono + data[left];\n        if (!pred(tmp)) return\
    \ right_partition_subtree(left, pred, mono);\n        mono = tmp;\n        ++left;\n\
    \      }\n    }\n    return size_orig;\n  }\n};\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/data_structure/segment_tree/basic.hpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/data_structure/segment_tree/basic.hpp
layout: document
redirect_from:
- /library/src/data_structure/segment_tree/basic.hpp
- /library/src/data_structure/segment_tree/basic.hpp.html
title: Segment Tree
---
