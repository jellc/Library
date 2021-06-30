---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Dual Segment Tree
    links: []
  bundledCode: "#line 2 \"src/data_structure/segment_tree/dual.hpp\"\n\n/**\n * @file\
    \ dual.hpp\n * @brief Dual Segment Tree\n */\n\nnamespace workspace {\n\ntemplate\
    \ <class _Tp> class dual_segment_tree {\n public:\n  using container_type = std::vector<_Tp>;\n\
    \  using size_type = typename container_type::size_type;\n\n  dual_segment_tree()\
    \ noexcept = default;\n\n  dual_segment_tree(size_type __n) noexcept\n      :\
    \ __len(__n),\n        __data(2 << (__n > 1 ? 64 - __builtin_clzll(__n - 1) :\
    \ 0)) {}\n\n  dual_segment_tree(size_type __n, const _Tp &__x) noexcept\n    \
    \  : __len(__n),\n        __data(2 << (__n > 1 ? 64 - __builtin_clzll(__n - 1)\
    \ : 0), __x) {}\n\n  template <class _Op> void point(size_type __i, _Op &&__op)\
    \ {\n    assert(__i < __len);\n    for (__i += __data.size() >> 1; __i; __i >>=\
    \ 1) __op(__data[__i]);\n  }\n\n  template <class _Op> void range(size_type __l,\
    \ size_type __r, _Op &&__op) {\n    assert(__l <= __r), assert(__r <= __len);\n\
    \    for (__l += __data.size() >> 1, __r += __data.size() >> 1; __l != __r;\n\
    \         __l >>= 1, __r >>= 1) {\n      if (__l & 1) __op(__data[__l++]);\n \
    \     if (__r & 1) __op(__data[--__r]);\n    }\n  }\n\n private:\n  size_type\
    \ __len;\n  container_type __data;\n};\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file dual.hpp\n * @brief Dual Segment Tree\n */\n\
    \nnamespace workspace {\n\ntemplate <class _Tp> class dual_segment_tree {\n public:\n\
    \  using container_type = std::vector<_Tp>;\n  using size_type = typename container_type::size_type;\n\
    \n  dual_segment_tree() noexcept = default;\n\n  dual_segment_tree(size_type __n)\
    \ noexcept\n      : __len(__n),\n        __data(2 << (__n > 1 ? 64 - __builtin_clzll(__n\
    \ - 1) : 0)) {}\n\n  dual_segment_tree(size_type __n, const _Tp &__x) noexcept\n\
    \      : __len(__n),\n        __data(2 << (__n > 1 ? 64 - __builtin_clzll(__n\
    \ - 1) : 0), __x) {}\n\n  template <class _Op> void point(size_type __i, _Op &&__op)\
    \ {\n    assert(__i < __len);\n    for (__i += __data.size() >> 1; __i; __i >>=\
    \ 1) __op(__data[__i]);\n  }\n\n  template <class _Op> void range(size_type __l,\
    \ size_type __r, _Op &&__op) {\n    assert(__l <= __r), assert(__r <= __len);\n\
    \    for (__l += __data.size() >> 1, __r += __data.size() >> 1; __l != __r;\n\
    \         __l >>= 1, __r >>= 1) {\n      if (__l & 1) __op(__data[__l++]);\n \
    \     if (__r & 1) __op(__data[--__r]);\n    }\n  }\n\n private:\n  size_type\
    \ __len;\n  container_type __data;\n};\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/data_structure/segment_tree/dual.hpp
  requiredBy: []
  timestamp: '2021-07-01 02:13:07+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/data_structure/segment_tree/dual.hpp
layout: document
redirect_from:
- /library/src/data_structure/segment_tree/dual.hpp
- /library/src/data_structure/segment_tree/dual.hpp.html
title: Dual Segment Tree
---
