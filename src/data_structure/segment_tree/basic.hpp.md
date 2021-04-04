---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: src/algebra/system/monoid.hpp
    title: src/algebra/system/monoid.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/DSL_2_A.test.cpp
    title: test/aizu-online-judge/DSL_2_A.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/point_add_range_sum.test.cpp
    title: test/library-checker/point_add_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/point_set_range_composite.test.cpp
    title: test/library-checker/point_set_range_composite.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/static_range_inversions_query.test.cpp
    title: test/library-checker/static_range_inversions_query.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Segment Tree
    links: []
  bundledCode: "#line 2 \"src/data_structure/segment_tree/basic.hpp\"\n\n/**\n * @file\
    \ basic.hpp\n * @brief Segment Tree\n */\n\n#include <cassert>\n#include <vector>\n\
    \n#line 2 \"src/algebra/system/monoid.hpp\"\n#include <limits>\n\nnamespace workspace\
    \ {\ntemplate <class T, class E = T> struct min_monoid {\n  using value_type =\
    \ T;\n  static T min, max;\n  T value;\n  min_monoid() : value(max) {}\n  min_monoid(const\
    \ T &value) : value(value) {}\n  operator T() const { return value; }\n  min_monoid\
    \ operator+(const min_monoid &rhs) const {\n    return value < rhs.value ? *this\
    \ : rhs;\n  }\n  min_monoid operator*(const E &rhs) const;\n};\n\ntemplate <class\
    \ T, class E>\nT min_monoid<T, E>::min = std::numeric_limits<T>::min() / 2;\n\
    template <class T, class E>\nT min_monoid<T, E>::max = std::numeric_limits<T>::max()\
    \ / 2;\n\ntemplate <class T, class E = T> struct max_monoid : min_monoid<T, E>\
    \ {\n  using base = min_monoid<T, E>;\n  using base::min_monoid;\n  max_monoid()\
    \ : base(base::min) {}\n  max_monoid operator+(const max_monoid &rhs) const {\n\
    \    return !(base::value < rhs.value) ? *this : rhs;\n  }\n  max_monoid operator*(const\
    \ E &rhs) const;\n};\n}\n#line 12 \"src/data_structure/segment_tree/basic.hpp\"\
    \n\nnamespace workspace {\n\n/**\n * @tparam Monoid `operator+`\n * @tparam Container_tmpl\
    \ `operator[]`, `size_type`\n */\ntemplate <class Monoid, template <class...>\
    \ class Container_tmpl = std::vector>\nclass segment_tree {\n  static_assert(\n\
    \      std::is_same<Monoid, decltype(std::declval<const Monoid>() +\n        \
    \                            std::declval<const Monoid>())>::value,\n      \"\\\
    'Monoid\\' has no proper binary \\'operator+\\'.\");\n\n  struct node {\n    Monoid\
    \ value{};\n    bool latest{true};\n  };\n\n  using container_type = Container_tmpl<node>;\n\
    \n public:\n  using size_type = typename container_type::size_type;\n\n  class\
    \ iterator {\n    segment_tree *__p;\n    size_type __i;\n\n   public:\n    using\
    \ difference_type = typename std::make_signed<size_type>::type;\n    using value_type\
    \ = Monoid;\n    using reference = Monoid &;\n    using pointer = iterator;\n\
    \    using iterator_category = std::random_access_iterator_tag;\n\n    /**\n \
    \    * @brief Construct a new iterator object\n     *\n     */\n    iterator()\
    \ = default;\n\n    /**\n     * @brief Construct a new iterator object\n     *\n\
    \     * @param __p Pointer to a segment tree object\n     * @param __i Index\n\
    \     */\n    iterator(segment_tree *__p, size_type __i) : __p(__p), __i(__i)\
    \ {}\n\n    bool operator==(iterator const &rhs) const {\n      return __p ==\
    \ rhs.__p && __i == rhs.__i;\n    }\n    bool operator!=(iterator const &rhs)\
    \ const { return !operator==(rhs); }\n\n    bool operator<(iterator const &rhs)\
    \ const { return __i < rhs.__i; }\n    bool operator>(iterator const &rhs) const\
    \ { return __i > rhs.__i; }\n    bool operator<=(iterator const &rhs) const {\
    \ return __i <= rhs.__i; }\n    bool operator>=(iterator const &rhs) const { return\
    \ __i >= rhs.__i; }\n\n    iterator &operator++() { return ++__i, *this; }\n \
    \   iterator &operator--() { return --__i, *this; }\n\n    difference_type operator-(iterator\
    \ const &rhs) const {\n      return __i - rhs.__i;\n    }\n\n    /**\n     * @brief\n\
    \     *\n     * @return reference\n     */\n    reference operator*() const {\
    \ return __p->operator[](__i); }\n  };\n\n  using value_type = typename iterator::value_type;\n\
    \  using reference = typename iterator::reference;\n\n  iterator begin() { return\
    \ {this, 0}; }\n  iterator end() { return {this, size_orig}; }\n\n  auto rbegin()\
    \ { return std::make_reverse_iterator(end()); }\n  auto rend() { return std::make_reverse_iterator(begin());\
    \ }\n\n protected:\n  size_type size_orig, height, size_ext;\n  container_type\
    \ data;\n\n  Monoid const &pull(size_type __i) noexcept {\n    if (!data[__i].latest)\n\
    \      data[__i] = {pull(__i << 1) + pull(__i << 1 | 1), true};\n    return data[__i].value;\n\
    \  }\n\n  template <class Pred>\n  static constexpr decltype(std::declval<Pred>()(Monoid{}))\
    \ pass_args(\n      Pred pred, Monoid const &_1, [[maybe_unused]] size_type _2)\
    \ {\n    return pred(_1);\n  }\n\n  template <class Pred>\n  static constexpr\
    \ decltype(std::declval<Pred>()(Monoid{}, size_type{}))\n  pass_args(Pred pred,\
    \ Monoid const &_1, size_type _2) {\n    return pred(_1, _2);\n  }\n\n  template\
    \ <class Pred>\n  size_type left_partition_subtree(size_type __i, Monoid mono,\
    \ size_type step,\n                                   Pred pred) {\n    assert(__i);\n\
    \    while (__i < size_ext) {\n      const Monoid tmp = pull((__i <<= 1) | 1)\
    \ + mono;\n      if (pass_args(pred, tmp, ((__i | 1) << --step) ^ size_ext))\n\
    \        mono = tmp;\n      else\n        ++__i;\n    }\n    return ++__i -= size_ext;\n\
    \  }\n\n  template <class Pred>\n  size_type right_partition_subtree(size_type\
    \ __i, Monoid mono, size_type step,\n                                    Pred\
    \ pred) {\n    assert(__i);\n    while (__i < size_ext) {\n      const Monoid\
    \ tmp = mono + pull(__i <<= 1);\n      if (pass_args(pred, tmp, ((__i | 1) <<\
    \ --step) ^ size_ext))\n        ++__i, mono = tmp;\n    }\n    return (__i -=\
    \ size_ext) < size_orig ? __i : size_orig;\n  }\n\n public:\n  /**\n   * @brief\
    \ Construct a new segment tree object\n   *\n   * @param __n Number of elements.\n\
    \   */\n  segment_tree(size_type __n = 0)\n      : size_orig{__n},\n        height(__n\
    \ > 1 ? 64 - __builtin_clzll(__n - 1) : 0),\n        size_ext{size_type{1} <<\
    \ height} {\n    if constexpr (std::is_constructible_v<container_type, size_t>)\n\
    \      data = container_type(size_ext << 1);\n  }\n\n  /**\n   * @brief Construct\
    \ a new segment tree object\n   *\n   * @tparam Tp\n   * @param __n Number of\
    \ elements.\n   * @param init\n   */\n  template <class Tp,\n            std::enable_if_t<std::is_convertible_v<Tp,\
    \ Monoid>> * = nullptr>\n  segment_tree(size_type __n, Tp const &init) : segment_tree(__n)\
    \ {\n    for (auto i = begin(); i != end(); ++i) *i = init;\n  }\n\n  /**\n  \
    \ * @brief Construct a new segment tree object\n   *\n   * @tparam Iterator\n\
    \   * @param __first\n   * @param __last\n   */\n  template <class Iterator,\n\
    \            std::enable_if_t<std::is_convertible_v<\n                typename\
    \ std::iterator_traits<Iterator>::value_type, Monoid>>\n                * = nullptr>\n\
    \  segment_tree(Iterator __first, Iterator __last)\n      : segment_tree(std::distance(__first,\
    \ __last)) {\n    for (auto i = begin(); __first != __last; ++i, ++__first) *i\
    \ = *__first;\n  }\n\n  /**\n   * @return Number of elements.\n   */\n  size_type\
    \ size() const { return size_orig; }\n\n  /**\n   * @param __i Index of the element\n\
    \   * @return Reference to the element.\n   */\n  reference operator[](size_type\
    \ __i) {\n    assert(__i < size_orig);\n    __i |= size_ext;\n    for (size_type\
    \ __j{__i >> 1}; __j && data[__j].latest; __j >>= 1)\n      data[__j].latest =\
    \ false;\n    return data[__i].value;\n  }\n\n  /**\n   * @param first Left end,\
    \ inclusive\n   * @param last Right end, exclusive\n   * @return Sum of elements\
    \ in the interval.\n   */\n  value_type fold(size_type first, size_type last)\
    \ {\n    assert(last <= size_orig);\n    Monoid left{}, right{};\n    first +=\
    \ size_ext, last += size_ext;\n    while (first < last) {\n      if (first & 1)\
    \ left = left + pull(first++);\n      if (last & 1) right = pull(--last) + right;\n\
    \      first >>= 1, last >>= 1;\n    }\n    return left + right;\n  }\n\n  /**\n\
    \   * @return The whole sum.\n   */\n  value_type fold() { return fold(0, size_orig);\
    \ }\n\n  /**\n   * @brief Binary search for the partition point.\n   * @param\
    \ right Right fixed end of the interval, exclusive\n   * @param pred Predicate\
    \ in the form of either 'bool(Monoid)' or 'bool(Monoid,\n   * size_type)'\n  \
    \ * @return Left end of the extremal interval satisfying the condition,\n   *\
    \ inclusive.\n   */\n  template <class Pred> size_type left_partition(size_type\
    \ right, Pred pred) {\n    assert(right <= size_orig);\n    right += size_ext;\n\
    \    Monoid mono{};\n    for (size_type left{size_ext}, step{}; left != right;\n\
    \         left >>= 1, right >>= 1, ++step) {\n      if ((left & 1) != (right &\
    \ 1)) {\n        const Monoid tmp = pull(--right) + mono;\n        if (!pass_args(pred,\
    \ tmp, (right << step) ^ size_ext))\n          return left_partition_subtree(right,\
    \ mono, step, pred);\n        mono = tmp;\n      }\n    }\n    return 0;\n  }\n\
    \n  /**\n   * @brief Binary search for the partition point.\n   * @param left\
    \ Left fixed end of the interval, inclusive\n   * @param pred Predicate in the\
    \ form of either 'bool(Monoid)' or 'bool(Monoid,\n   * size_type)'\n   * @return\
    \ Right end of the extremal interval satisfying the condition,\n   * exclusive.\n\
    \   */\n  template <class Pred> size_type right_partition(size_type left, Pred\
    \ pred) {\n    assert(left <= size_orig);\n    left += size_ext;\n    Monoid mono{};\n\
    \    for (size_type right{size_ext << 1}, step{}; left != right;\n         left\
    \ >>= 1, right >>= 1, ++step) {\n      if ((left & 1) != (right & 1)) {\n    \
    \    const Monoid tmp = mono + pull(left);\n        if (!pass_args(pred, tmp,\
    \ ((left + 1) << step) ^ size_ext))\n          return right_partition_subtree(left,\
    \ mono, step, pred);\n        mono = tmp;\n        ++left;\n      }\n    }\n \
    \   return size_orig;\n  }\n};\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file basic.hpp\n * @brief Segment Tree\n */\n\n\
    #include <cassert>\n#include <vector>\n\n#include \"src/algebra/system/monoid.hpp\"\
    \n\nnamespace workspace {\n\n/**\n * @tparam Monoid `operator+`\n * @tparam Container_tmpl\
    \ `operator[]`, `size_type`\n */\ntemplate <class Monoid, template <class...>\
    \ class Container_tmpl = std::vector>\nclass segment_tree {\n  static_assert(\n\
    \      std::is_same<Monoid, decltype(std::declval<const Monoid>() +\n        \
    \                            std::declval<const Monoid>())>::value,\n      \"\\\
    'Monoid\\' has no proper binary \\'operator+\\'.\");\n\n  struct node {\n    Monoid\
    \ value{};\n    bool latest{true};\n  };\n\n  using container_type = Container_tmpl<node>;\n\
    \n public:\n  using size_type = typename container_type::size_type;\n\n  class\
    \ iterator {\n    segment_tree *__p;\n    size_type __i;\n\n   public:\n    using\
    \ difference_type = typename std::make_signed<size_type>::type;\n    using value_type\
    \ = Monoid;\n    using reference = Monoid &;\n    using pointer = iterator;\n\
    \    using iterator_category = std::random_access_iterator_tag;\n\n    /**\n \
    \    * @brief Construct a new iterator object\n     *\n     */\n    iterator()\
    \ = default;\n\n    /**\n     * @brief Construct a new iterator object\n     *\n\
    \     * @param __p Pointer to a segment tree object\n     * @param __i Index\n\
    \     */\n    iterator(segment_tree *__p, size_type __i) : __p(__p), __i(__i)\
    \ {}\n\n    bool operator==(iterator const &rhs) const {\n      return __p ==\
    \ rhs.__p && __i == rhs.__i;\n    }\n    bool operator!=(iterator const &rhs)\
    \ const { return !operator==(rhs); }\n\n    bool operator<(iterator const &rhs)\
    \ const { return __i < rhs.__i; }\n    bool operator>(iterator const &rhs) const\
    \ { return __i > rhs.__i; }\n    bool operator<=(iterator const &rhs) const {\
    \ return __i <= rhs.__i; }\n    bool operator>=(iterator const &rhs) const { return\
    \ __i >= rhs.__i; }\n\n    iterator &operator++() { return ++__i, *this; }\n \
    \   iterator &operator--() { return --__i, *this; }\n\n    difference_type operator-(iterator\
    \ const &rhs) const {\n      return __i - rhs.__i;\n    }\n\n    /**\n     * @brief\n\
    \     *\n     * @return reference\n     */\n    reference operator*() const {\
    \ return __p->operator[](__i); }\n  };\n\n  using value_type = typename iterator::value_type;\n\
    \  using reference = typename iterator::reference;\n\n  iterator begin() { return\
    \ {this, 0}; }\n  iterator end() { return {this, size_orig}; }\n\n  auto rbegin()\
    \ { return std::make_reverse_iterator(end()); }\n  auto rend() { return std::make_reverse_iterator(begin());\
    \ }\n\n protected:\n  size_type size_orig, height, size_ext;\n  container_type\
    \ data;\n\n  Monoid const &pull(size_type __i) noexcept {\n    if (!data[__i].latest)\n\
    \      data[__i] = {pull(__i << 1) + pull(__i << 1 | 1), true};\n    return data[__i].value;\n\
    \  }\n\n  template <class Pred>\n  static constexpr decltype(std::declval<Pred>()(Monoid{}))\
    \ pass_args(\n      Pred pred, Monoid const &_1, [[maybe_unused]] size_type _2)\
    \ {\n    return pred(_1);\n  }\n\n  template <class Pred>\n  static constexpr\
    \ decltype(std::declval<Pred>()(Monoid{}, size_type{}))\n  pass_args(Pred pred,\
    \ Monoid const &_1, size_type _2) {\n    return pred(_1, _2);\n  }\n\n  template\
    \ <class Pred>\n  size_type left_partition_subtree(size_type __i, Monoid mono,\
    \ size_type step,\n                                   Pred pred) {\n    assert(__i);\n\
    \    while (__i < size_ext) {\n      const Monoid tmp = pull((__i <<= 1) | 1)\
    \ + mono;\n      if (pass_args(pred, tmp, ((__i | 1) << --step) ^ size_ext))\n\
    \        mono = tmp;\n      else\n        ++__i;\n    }\n    return ++__i -= size_ext;\n\
    \  }\n\n  template <class Pred>\n  size_type right_partition_subtree(size_type\
    \ __i, Monoid mono, size_type step,\n                                    Pred\
    \ pred) {\n    assert(__i);\n    while (__i < size_ext) {\n      const Monoid\
    \ tmp = mono + pull(__i <<= 1);\n      if (pass_args(pred, tmp, ((__i | 1) <<\
    \ --step) ^ size_ext))\n        ++__i, mono = tmp;\n    }\n    return (__i -=\
    \ size_ext) < size_orig ? __i : size_orig;\n  }\n\n public:\n  /**\n   * @brief\
    \ Construct a new segment tree object\n   *\n   * @param __n Number of elements.\n\
    \   */\n  segment_tree(size_type __n = 0)\n      : size_orig{__n},\n        height(__n\
    \ > 1 ? 64 - __builtin_clzll(__n - 1) : 0),\n        size_ext{size_type{1} <<\
    \ height} {\n    if constexpr (std::is_constructible_v<container_type, size_t>)\n\
    \      data = container_type(size_ext << 1);\n  }\n\n  /**\n   * @brief Construct\
    \ a new segment tree object\n   *\n   * @tparam Tp\n   * @param __n Number of\
    \ elements.\n   * @param init\n   */\n  template <class Tp,\n            std::enable_if_t<std::is_convertible_v<Tp,\
    \ Monoid>> * = nullptr>\n  segment_tree(size_type __n, Tp const &init) : segment_tree(__n)\
    \ {\n    for (auto i = begin(); i != end(); ++i) *i = init;\n  }\n\n  /**\n  \
    \ * @brief Construct a new segment tree object\n   *\n   * @tparam Iterator\n\
    \   * @param __first\n   * @param __last\n   */\n  template <class Iterator,\n\
    \            std::enable_if_t<std::is_convertible_v<\n                typename\
    \ std::iterator_traits<Iterator>::value_type, Monoid>>\n                * = nullptr>\n\
    \  segment_tree(Iterator __first, Iterator __last)\n      : segment_tree(std::distance(__first,\
    \ __last)) {\n    for (auto i = begin(); __first != __last; ++i, ++__first) *i\
    \ = *__first;\n  }\n\n  /**\n   * @return Number of elements.\n   */\n  size_type\
    \ size() const { return size_orig; }\n\n  /**\n   * @param __i Index of the element\n\
    \   * @return Reference to the element.\n   */\n  reference operator[](size_type\
    \ __i) {\n    assert(__i < size_orig);\n    __i |= size_ext;\n    for (size_type\
    \ __j{__i >> 1}; __j && data[__j].latest; __j >>= 1)\n      data[__j].latest =\
    \ false;\n    return data[__i].value;\n  }\n\n  /**\n   * @param first Left end,\
    \ inclusive\n   * @param last Right end, exclusive\n   * @return Sum of elements\
    \ in the interval.\n   */\n  value_type fold(size_type first, size_type last)\
    \ {\n    assert(last <= size_orig);\n    Monoid left{}, right{};\n    first +=\
    \ size_ext, last += size_ext;\n    while (first < last) {\n      if (first & 1)\
    \ left = left + pull(first++);\n      if (last & 1) right = pull(--last) + right;\n\
    \      first >>= 1, last >>= 1;\n    }\n    return left + right;\n  }\n\n  /**\n\
    \   * @return The whole sum.\n   */\n  value_type fold() { return fold(0, size_orig);\
    \ }\n\n  /**\n   * @brief Binary search for the partition point.\n   * @param\
    \ right Right fixed end of the interval, exclusive\n   * @param pred Predicate\
    \ in the form of either 'bool(Monoid)' or 'bool(Monoid,\n   * size_type)'\n  \
    \ * @return Left end of the extremal interval satisfying the condition,\n   *\
    \ inclusive.\n   */\n  template <class Pred> size_type left_partition(size_type\
    \ right, Pred pred) {\n    assert(right <= size_orig);\n    right += size_ext;\n\
    \    Monoid mono{};\n    for (size_type left{size_ext}, step{}; left != right;\n\
    \         left >>= 1, right >>= 1, ++step) {\n      if ((left & 1) != (right &\
    \ 1)) {\n        const Monoid tmp = pull(--right) + mono;\n        if (!pass_args(pred,\
    \ tmp, (right << step) ^ size_ext))\n          return left_partition_subtree(right,\
    \ mono, step, pred);\n        mono = tmp;\n      }\n    }\n    return 0;\n  }\n\
    \n  /**\n   * @brief Binary search for the partition point.\n   * @param left\
    \ Left fixed end of the interval, inclusive\n   * @param pred Predicate in the\
    \ form of either 'bool(Monoid)' or 'bool(Monoid,\n   * size_type)'\n   * @return\
    \ Right end of the extremal interval satisfying the condition,\n   * exclusive.\n\
    \   */\n  template <class Pred> size_type right_partition(size_type left, Pred\
    \ pred) {\n    assert(left <= size_orig);\n    left += size_ext;\n    Monoid mono{};\n\
    \    for (size_type right{size_ext << 1}, step{}; left != right;\n         left\
    \ >>= 1, right >>= 1, ++step) {\n      if ((left & 1) != (right & 1)) {\n    \
    \    const Monoid tmp = mono + pull(left);\n        if (!pass_args(pred, tmp,\
    \ ((left + 1) << step) ^ size_ext))\n          return right_partition_subtree(left,\
    \ mono, step, pred);\n        mono = tmp;\n        ++left;\n      }\n    }\n \
    \   return size_orig;\n  }\n};\n\n}  // namespace workspace\n"
  dependsOn:
  - src/algebra/system/monoid.hpp
  isVerificationFile: false
  path: src/data_structure/segment_tree/basic.hpp
  requiredBy: []
  timestamp: '2020-12-23 18:52:56+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aizu-online-judge/DSL_2_A.test.cpp
  - test/library-checker/point_add_range_sum.test.cpp
  - test/library-checker/static_range_inversions_query.test.cpp
  - test/library-checker/point_set_range_composite.test.cpp
documentation_of: src/data_structure/segment_tree/basic.hpp
layout: document
redirect_from:
- /library/src/data_structure/segment_tree/basic.hpp
- /library/src/data_structure/segment_tree/basic.hpp.html
title: Segment Tree
---
