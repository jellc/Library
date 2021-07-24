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
    \ : 0), __x) {}\n\n  template <class _Op>\n  void point(size_type __i,\n     \
    \        _Op &&__op) noexcept(noexcept(__op(std::declval<_Tp &>()))) {\n    assert(__i\
    \ < __len);\n    for (__i += size_ext(); __i; __i >>= 1) __op(__data[__i]);\n\
    \  }\n\n  template <class _Op>\n  void range(size_type __l, size_type __r,\n \
    \            _Op &&__op) noexcept(noexcept(__op(std::declval<_Tp &>()))) {\n \
    \   assert(__l <= __r), assert(__r <= __len);\n    for (__l += size_ext(), __r\
    \ += size_ext(); __l != __r;\n         __l >>= 1, __r >>= 1) {\n      if (__l\
    \ & 1) __op(__data[__l++]);\n      if (__r & 1) __op(__data[--__r]);\n    }\n\
    \  }\n\n  template <class _Predicate>\n  size_type left_partition(size_type __r,\
    \ _Predicate &&__pred) noexcept(\n      noexcept(__pred(std::declval<_Tp &>())))\
    \ {\n    assert(__r <= __len);\n    __r += size_ext();\n    for (auto __l = size_ext();\
    \ __l != __r; __l >>= 1, __r >>= 1)\n      if ((__l & 1) != (__r & 1))\n     \
    \   if (!__pred(__data[--__r])) return left_partition_subtree(__r, __pred);\n\
    \    return 0;\n  }\n\n  template <class _Predicate>\n  size_type right_partition(size_type\
    \ __l, _Predicate &&__pred) noexcept(\n      noexcept(__pred(std::declval<_Tp\
    \ &>()))) {\n    assert(__l <= __len);\n    __l += size_ext();\n    for (auto\
    \ __r = __data.size(); __l != __r; ++__l >>= 1, __r >>= 1)\n      if ((__l & 1)\
    \ != (__r & 1))\n        if (!__pred(__data[__l])) return right_partition_subtree(__l,\
    \ __pred);\n    return __len;\n  }\n\n private:\n  template <class _Predicate>\n\
    \  size_type left_partition_subtree(size_type __i, _Predicate &&__pred) noexcept(\n\
    \      noexcept(__pred(std::declval<_Tp &>()))) {\n    while (__i < size_ext())\n\
    \      if (!__pred(__data[(__i <<= 1) | 1])) __i |= 1;\n    return ++__i -= size_ext();\n\
    \  }\n\n  template <class _Predicate>\n  size_type right_partition_subtree(\n\
    \      size_type __i,\n      _Predicate &&__pred) noexcept(noexcept(__pred(std::declval<_Tp\
    \ &>()))) {\n    while (__i < size_ext())\n      if (__pred(__data[__i <<= 1]))\
    \ __i |= 1;\n    return std::min(__i -= size_ext(), __len);\n  }\n\n  size_type\
    \ size_ext() const noexcept { return __data.size() >> 1; }\n\n  size_type __len;\n\
    \  container_type __data;\n};\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file dual.hpp\n * @brief Dual Segment Tree\n */\n\
    \nnamespace workspace {\n\ntemplate <class _Tp> class dual_segment_tree {\n public:\n\
    \  using container_type = std::vector<_Tp>;\n  using size_type = typename container_type::size_type;\n\
    \n  dual_segment_tree() noexcept = default;\n\n  dual_segment_tree(size_type __n)\
    \ noexcept\n      : __len(__n),\n        __data(2 << (__n > 1 ? 64 - __builtin_clzll(__n\
    \ - 1) : 0)) {}\n\n  dual_segment_tree(size_type __n, const _Tp &__x) noexcept\n\
    \      : __len(__n),\n        __data(2 << (__n > 1 ? 64 - __builtin_clzll(__n\
    \ - 1) : 0), __x) {}\n\n  template <class _Op>\n  void point(size_type __i,\n\
    \             _Op &&__op) noexcept(noexcept(__op(std::declval<_Tp &>()))) {\n\
    \    assert(__i < __len);\n    for (__i += size_ext(); __i; __i >>= 1) __op(__data[__i]);\n\
    \  }\n\n  template <class _Op>\n  void range(size_type __l, size_type __r,\n \
    \            _Op &&__op) noexcept(noexcept(__op(std::declval<_Tp &>()))) {\n \
    \   assert(__l <= __r), assert(__r <= __len);\n    for (__l += size_ext(), __r\
    \ += size_ext(); __l != __r;\n         __l >>= 1, __r >>= 1) {\n      if (__l\
    \ & 1) __op(__data[__l++]);\n      if (__r & 1) __op(__data[--__r]);\n    }\n\
    \  }\n\n  template <class _Predicate>\n  size_type left_partition(size_type __r,\
    \ _Predicate &&__pred) noexcept(\n      noexcept(__pred(std::declval<_Tp &>())))\
    \ {\n    assert(__r <= __len);\n    __r += size_ext();\n    for (auto __l = size_ext();\
    \ __l != __r; __l >>= 1, __r >>= 1)\n      if ((__l & 1) != (__r & 1))\n     \
    \   if (!__pred(__data[--__r])) return left_partition_subtree(__r, __pred);\n\
    \    return 0;\n  }\n\n  template <class _Predicate>\n  size_type right_partition(size_type\
    \ __l, _Predicate &&__pred) noexcept(\n      noexcept(__pred(std::declval<_Tp\
    \ &>()))) {\n    assert(__l <= __len);\n    __l += size_ext();\n    for (auto\
    \ __r = __data.size(); __l != __r; ++__l >>= 1, __r >>= 1)\n      if ((__l & 1)\
    \ != (__r & 1))\n        if (!__pred(__data[__l])) return right_partition_subtree(__l,\
    \ __pred);\n    return __len;\n  }\n\n private:\n  template <class _Predicate>\n\
    \  size_type left_partition_subtree(size_type __i, _Predicate &&__pred) noexcept(\n\
    \      noexcept(__pred(std::declval<_Tp &>()))) {\n    while (__i < size_ext())\n\
    \      if (!__pred(__data[(__i <<= 1) | 1])) __i |= 1;\n    return ++__i -= size_ext();\n\
    \  }\n\n  template <class _Predicate>\n  size_type right_partition_subtree(\n\
    \      size_type __i,\n      _Predicate &&__pred) noexcept(noexcept(__pred(std::declval<_Tp\
    \ &>()))) {\n    while (__i < size_ext())\n      if (__pred(__data[__i <<= 1]))\
    \ __i |= 1;\n    return std::min(__i -= size_ext(), __len);\n  }\n\n  size_type\
    \ size_ext() const noexcept { return __data.size() >> 1; }\n\n  size_type __len;\n\
    \  container_type __data;\n};\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/data_structure/segment_tree/dual.hpp
  requiredBy: []
  timestamp: '2021-07-24 20:17:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/data_structure/segment_tree/dual.hpp
layout: document
redirect_from:
- /library/src/data_structure/segment_tree/dual.hpp
- /library/src/data_structure/segment_tree/dual.hpp.html
title: Dual Segment Tree
---
