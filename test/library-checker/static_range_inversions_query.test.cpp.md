---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: src/algebra/system/monoid.hpp
    title: src/algebra/system/monoid.hpp
  - icon: ':x:'
    path: src/data_structure/Mo.hpp
    title: Mo's Algorithm
  - icon: ':x:'
    path: src/data_structure/coordinate_compression.hpp
    title: Coordinate Compression
  - icon: ':question:'
    path: src/data_structure/segment_tree/basic.hpp
    title: Segment Tree
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/static_range_inversions_query
    links:
    - https://judge.yosupo.jp/problem/static_range_inversions_query
  bundledCode: "#line 1 \"test/library-checker/static_range_inversions_query.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_inversions_query\"\
    \n\n#include <cstdio>\n\n#line 2 \"src/data_structure/Mo.hpp\"\n\n/**\n * @file\
    \ Mo.hpp\n * @brief Mo's Algorithm\n */\n\n#include <cassert>\n#include <cmath>\n\
    #include <functional>\n#include <numeric>\n#include <vector>\n\nnamespace workspace\
    \ {\n\n/**\n * @brief Mo's Alorithm. Process queries about contiguous subarrays.\n\
    \ *\n * @tparam Push_back\n * @tparam Pop_back\n * @tparam Push_front Use `Push_back`\
    \ as default\n * @tparam Pop_front Use `Pop_back` as default\n */\ntemplate <class\
    \ Push_back, class Pop_back, class Push_front = Push_back,\n          class Pop_front\
    \ = Pop_back>\nclass Mo {\n  Push_front push_front;\n  Pop_front pop_front;\n\
    \  Push_back push_back;\n  Pop_back pop_back;\n  std::vector<size_t> lft, rgt,\
    \ ord;\n  std::vector<size_t>::iterator iter;\n  size_t lpos, rpos;\n\n public:\n\
    \  /**\n   * @brief Construct a new Mo object.\n   *\n   * @param push_back\n\
    \   * @param pop_back\n   */\n  Mo(Push_back push_back, Pop_back pop_back)\n \
    \     : Mo(push_back, pop_back, push_back, pop_back) {}\n\n  /**\n   * @brief\
    \ Construct a new Mo object.\n   *\n   * @param push_front\n   * @param pop_front\n\
    \   * @param push_back\n   * @param pop_back\n   */\n  Mo(Push_front push_front,\
    \ Pop_front pop_front, Push_back push_back,\n     Pop_back pop_back)\n      :\
    \ push_front(push_front),\n        pop_front(pop_front),\n        push_back(push_back),\n\
    \        pop_back(pop_back),\n        lpos(),\n        rpos() {}\n\n  /**\n  \
    \ * @return Number of queries.\n   */\n  size_t size() const { return lft.size();\
    \ }\n\n  /**\n   * @brief Add a query for the interval [l, r).\n   *\n   * @param\
    \ __l Left end, inclusive\n   * @param __r Right end, exclusive\n   * @return\
    \ Index of the query.\n   */\n  size_t add_query(size_t __l, size_t __r) {\n \
    \   assert(__l <= __r);\n    lft.emplace_back(__l), rgt.emplace_back(__r);\n \
    \   return lft.size() - 1;\n  }\n\n  /**\n   * @brief Sort all queries.\n   */\n\
    \  void make() {\n    assert(size());\n    ord.resize(size());\n    std::iota(ord.begin(),\
    \ ord.end(), 0);\n    const size_t width =\n        ceil(*max_element(rgt.begin(),\
    \ rgt.end()) / sqrt(size()));\n    std::sort(ord.begin(), ord.end(), [&](size_t\
    \ x, size_t y) {\n      if (lft[x] / width != lft[y] / width) return lft[x] <\
    \ lft[y];\n      return rgt[x] < rgt[y];\n    });\n    iter = ord.begin();\n \
    \ }\n\n  /**\n   * @brief Process the next query.\n   * @return Index of the query.\n\
    \   */\n  size_t process() {\n    if (iter == ord.end()) return ord.size();\n\
    \    const size_t id = *iter++, l = lft[id], r = rgt[id];\n    while (lpos > l)\
    \ push_front(--lpos);\n    while (rpos < r) push_back(rpos++);\n    while (lpos\
    \ < l) pop_front(lpos++);\n    while (rpos > r) pop_back(--rpos);\n    return\
    \ id;\n  }\n};\n\n}  // namespace workspace\n#line 2 \"src/data_structure/coordinate_compression.hpp\"\
    \n\n/*\n * @file coordinate_compression.hpp\n * @brief Coordinate Compression\n\
    \ */\n\n#include <algorithm>\n#line 10 \"src/data_structure/coordinate_compression.hpp\"\
    \n\nnamespace workspace {\n\ntemplate <class Type, class Result = size_t>\nstruct\
    \ coordinate_compression : std::vector<Type> {\n  using std::vector<Type>::vector;\n\
    \  using std::vector<Type>::begin;\n  using std::vector<Type>::end;\n\n  using\
    \ result_type = Result;\n\n  void make() {\n    std::sort(begin(), end());\n \
    \   std::vector<Type>::erase(std::unique(begin(), end()), end());\n  }\n\n  result_type\
    \ compress(const Type &value) const {\n    return std::lower_bound(begin(), end(),\
    \ value) - begin();\n  }\n\n  template <class Iter>\n  std::vector<result_type>\
    \ compress(Iter first, Iter last) const {\n    static_assert(std::is_convertible<\n\
    \                  typename std::decay<decltype(*std::declval<Iter>())>::type,\n\
    \                  Type>::value);\n    std::vector<result_type> res;\n    for\
    \ (Iter iter = first; iter != last; ++iter)\n      res.emplace_back(compress(*iter));\n\
    \    return res;\n  }\n};\n\n}  // namespace workspace\n#line 2 \"src/data_structure/segment_tree/basic.hpp\"\
    \n\n/**\n * @file basic.hpp\n * @brief Segment Tree\n */\n\n#line 10 \"src/data_structure/segment_tree/basic.hpp\"\
    \n\n#line 2 \"src/algebra/system/monoid.hpp\"\n#include <limits>\n\nnamespace\
    \ workspace {\ntemplate <class T, class E = T> struct min_monoid {\n  using value_type\
    \ = T;\n  static T min, max;\n  T value;\n  min_monoid() : value(max) {}\n  min_monoid(const\
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
    \   return size_orig;\n  }\n};\n\n}  // namespace workspace\n#line 8 \"test/library-checker/static_range_inversions_query.test.cpp\"\
    \n\nint main() {\n  using i64 = int64_t;\n  int n, q;\n  scanf(\"%d%d\", &n, &q);\n\
    \  std::vector<size_t> a(n);\n  for (auto &e : a) scanf(\"%d\", &e);\n  workspace::coordinate_compression<int>\
    \ ccmp(a.begin(), a.end());\n  ccmp.make();\n  a = ccmp.compress(a.begin(), a.end());\n\
    \  std::vector<int> cnt(ccmp.size());\n  workspace::segment_tree<int> seg(n);\n\
    \  i64 invs = 0;\n  auto addl = [&](int i) -> auto {\n    i = a[i];\n    invs\
    \ += seg.fold(0, i);\n    seg[i]++;\n  };\n  auto addr = [&](int i) -> auto {\n\
    \    i = a[i];\n    invs += seg.fold(i + 1, n);\n    seg[i]++;\n  };\n  auto dell\
    \ = [&](int i) -> auto {\n    i = a[i];\n    invs -= seg.fold(0, i);\n    seg[i]--;\n\
    \  };\n  auto delr = [&](int i) -> auto {\n    i = a[i];\n    invs -= seg.fold(i\
    \ + 1, n);\n    seg[i]--;\n  };\n  workspace::Mo mo(addl, dell, addr, delr);\n\
    \  for (int i = 0; i < q; i++) {\n    int l, r;\n    scanf(\"%d%d\", &l, &r);\n\
    \    mo.set(l, r);\n  }\n  mo.make();\n  std::vector<i64> ans(q);\n  for (int\
    \ i = 0; i < q; i++) {\n    int id = mo.process();\n    ans[id] = invs;\n  }\n\
    \  for (i64 x : ans) printf(\"%lld\\n\", x);\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_inversions_query\"\
    \n\n#include <cstdio>\n\n#include \"src/data_structure/Mo.hpp\"\n#include \"src/data_structure/coordinate_compression.hpp\"\
    \n#include \"src/data_structure/segment_tree/basic.hpp\"\n\nint main() {\n  using\
    \ i64 = int64_t;\n  int n, q;\n  scanf(\"%d%d\", &n, &q);\n  std::vector<size_t>\
    \ a(n);\n  for (auto &e : a) scanf(\"%d\", &e);\n  workspace::coordinate_compression<int>\
    \ ccmp(a.begin(), a.end());\n  ccmp.make();\n  a = ccmp.compress(a.begin(), a.end());\n\
    \  std::vector<int> cnt(ccmp.size());\n  workspace::segment_tree<int> seg(n);\n\
    \  i64 invs = 0;\n  auto addl = [&](int i) -> auto {\n    i = a[i];\n    invs\
    \ += seg.fold(0, i);\n    seg[i]++;\n  };\n  auto addr = [&](int i) -> auto {\n\
    \    i = a[i];\n    invs += seg.fold(i + 1, n);\n    seg[i]++;\n  };\n  auto dell\
    \ = [&](int i) -> auto {\n    i = a[i];\n    invs -= seg.fold(0, i);\n    seg[i]--;\n\
    \  };\n  auto delr = [&](int i) -> auto {\n    i = a[i];\n    invs -= seg.fold(i\
    \ + 1, n);\n    seg[i]--;\n  };\n  workspace::Mo mo(addl, dell, addr, delr);\n\
    \  for (int i = 0; i < q; i++) {\n    int l, r;\n    scanf(\"%d%d\", &l, &r);\n\
    \    mo.set(l, r);\n  }\n  mo.make();\n  std::vector<i64> ans(q);\n  for (int\
    \ i = 0; i < q; i++) {\n    int id = mo.process();\n    ans[id] = invs;\n  }\n\
    \  for (i64 x : ans) printf(\"%lld\\n\", x);\n}\n"
  dependsOn:
  - src/data_structure/Mo.hpp
  - src/data_structure/coordinate_compression.hpp
  - src/data_structure/segment_tree/basic.hpp
  - src/algebra/system/monoid.hpp
  isVerificationFile: true
  path: test/library-checker/static_range_inversions_query.test.cpp
  requiredBy: []
  timestamp: '2021-03-26 17:16:39+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/library-checker/static_range_inversions_query.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/static_range_inversions_query.test.cpp
- /verify/test/library-checker/static_range_inversions_query.test.cpp.html
title: test/library-checker/static_range_inversions_query.test.cpp
---
