---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/algebra/system/monoid.hpp
    title: src/algebra/system/monoid.hpp
  - icon: ':heavy_check_mark:'
    path: src/data_structure/Mo.hpp
    title: Mo's Algorithm
  - icon: ':heavy_check_mark:'
    path: src/data_structure/compression.hpp
    title: Compression
  - icon: ':heavy_check_mark:'
    path: src/data_structure/segment_tree/basic.hpp
    title: Segment Tree
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/static_range_inversions_query
    links:
    - https://judge.yosupo.jp/problem/static_range_inversions_query
  bundledCode: "#line 1 \"test/library-checker/static_range_inversions_query.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_inversions_query\"\
    \n\n#include <cstdio>\n\n#line 2 \"src/data_structure/Mo.hpp\"\n\n/**\n * @file\
    \ Mo.hpp\n * @brief Mo's Algorithm\n */\n\n#include <cassert>\n#include <cmath>\n\
    #include <functional>\n#include <vector>\n\nnamespace workspace {\n\n/**\n * @brief\
    \ Mo's Alorithm. Process queries about contiguous subarrays.\n *\n * @tparam _Push_back\n\
    \ * @tparam _Pop_back\n * @tparam _Push_front Use `_Push_back` as default\n *\
    \ @tparam _Pop_front Use `_Pop_back` as default\n */\ntemplate <class _Push_back,\
    \ class _Pop_back, class _Push_front = _Push_back,\n          class _Pop_front\
    \ = _Pop_back>\nclass Mo {\n public:\n  using size_type = std::size_t;\n\n  struct\
    \ query {\n    size_type index;\n    size_type left, right;\n  };\n\n  using value_type\
    \ = query;\n  using reference = query&;\n  using container_type = std::vector<query>;\n\
    \n protected:\n  _Push_front push_front;\n  _Pop_front pop_front;\n  _Push_back\
    \ push_back;\n  _Pop_back pop_back;\n\n  container_type queries;\n\n public:\n\
    \  /**\n   * @brief Construct a new Mo object.\n   *\n   * @param push_back\n\
    \   * @param pop_back\n   */\n  Mo(_Push_back push_back, _Pop_back pop_back) noexcept\n\
    \      : Mo(push_back, pop_back, push_back, pop_back) {}\n\n  /**\n   * @brief\
    \ Construct a new Mo object.\n   *\n   * @param push_front\n   * @param pop_front\n\
    \   * @param push_back\n   * @param pop_back\n   */\n  Mo(_Push_front push_front,\
    \ _Pop_front pop_front, _Push_back push_back,\n     _Pop_back pop_back) noexcept\n\
    \      : push_front(push_front),\n        pop_front(pop_front),\n        push_back(push_back),\n\
    \        pop_back(pop_back) {}\n\n  /**\n   * @return Number of queries.\n   */\n\
    \  size_type size() const noexcept { return queries.size(); }\n\n  /**\n   * @brief\
    \ Add a query for the interval [l, r).\n   *\n   * @param __l Left end, inclusive\n\
    \   * @param __r Right end, exclusive\n   * @return Index of the query.\n   */\n\
    \  reference insert(size_type __l, size_type __r) noexcept {\n    assert(__l <=\
    \ __r);\n    queries.push_back({queries.size(), __l, __r});\n    return queries.back();\n\
    \  }\n\n  /**\n   * @brief Sort all queries.\n   */\n  void make() noexcept {\n\
    \    assert(size());\n    size_type __n = 0;\n    for (const auto& __q : queries)\
    \ __n = std::max(__n, __q.right);\n    size_type __width = ceil(__n / sqrt(size()));\n\
    \    std::sort(queries.begin(), queries.end(), [&](auto __x, auto __y) {\n   \
    \   if (__x.left / __width != __y.left / __width) return __x.left < __y.left;\n\
    \      return __x.right < __y.right;\n    });\n  }\n\n  class iterator : public\
    \ container_type::iterator {\n    using base = typename container_type::iterator;\n\
    \    Mo* __mo;\n\n    void fit(size_type __l1, size_type __r1, size_type __l2,\n\
    \             size_type __r2) const noexcept {\n      while (__l1 > __l2) __mo->push_front(--__l1);\n\
    \      while (__r1 < __r2) __mo->push_back(__r1++);\n      while (__l1 < __l2)\
    \ __mo->pop_front(__l1++);\n      while (__r1 > __r2) __mo->pop_back(--__r1);\n\
    \    }\n\n    void fit_from_empty(size_type __l, size_type __r) const noexcept\
    \ {\n      while (__l < __r) __mo->push_back(__l++);\n    }\n\n    void fit_to_empty(size_type\
    \ __l, size_type __r) const noexcept {\n      while (__l < __r) __mo->push_back(--__r);\n\
    \    }\n\n    bool at_end() const noexcept { return __mo->queries.end() == *this;\
    \ }\n\n   public:\n    iterator() = default;\n\n    iterator(Mo* __mo, base __i)\
    \ noexcept : base(__i), __mo(__mo) {\n      if (__i != __mo->queries.end()) fit_from_empty(__i->left,\
    \ __i->right);\n    }\n\n    iterator& operator++() noexcept {\n      auto __l\
    \ = (*this)->left, __r = (*this)->right;\n      base::operator++();\n      if\
    \ (at_end())\n        fit_to_empty(__l, __r);\n      else\n        fit(__l, __r,\
    \ (*this)->left, (*this)->right);\n      return *this;\n    }\n\n    iterator&\
    \ operator--() noexcept {\n      if (at_end()) {\n        base::operator--();\n\
    \        fit_from_empty((*this)->left, (*this)->right);\n      } else {\n    \
    \    size_type __l = (*this)->left, __r = (*this)->right;\n        base::operator--();\n\
    \        fit(__l, __r, (*this)->left, (*this)->right);\n      }\n      return\
    \ *this;\n    }\n\n    iterator operator++(int) noexcept {\n      auto __tmp =\
    \ *this;\n      operator++();\n      return __tmp;\n    }\n\n    iterator operator--(int)\
    \ noexcept {\n      auto __tmp = *this;\n      operator--();\n      return __tmp;\n\
    \    }\n  };\n\n  iterator begin() noexcept { return {this, queries.begin()};\
    \ }\n\n  iterator end() noexcept { return {this, queries.end()}; }\n};\n\n}  //\
    \ namespace workspace\n#line 2 \"src/data_structure/compression.hpp\"\n\n/**\n\
    \ * @file compression.hpp\n * @brief Compression\n */\n\n#include <algorithm>\n\
    #line 11 \"src/data_structure/compression.hpp\"\n\nnamespace workspace {\n\ntemplate\
    \ <class _Tp> class compression {\n  std::vector<_Tp> __vec;\n\n  decltype(auto)\
    \ begin() { return __vec.begin(); }\n\n  decltype(auto) end() { return __vec.end();\
    \ }\n\n public:\n  using size_type = typename std::vector<_Tp>::size_type;\n\n\
    \  /**\n   * @brief Construct a new compression object.\n   */\n  compression()\
    \ = default;\n\n  /**\n   * @brief Construct a new compression object.\n   *\n\
    \   * @param __first\n   * @param __last\n   */\n  template <class _IIter>\n \
    \ compression(_IIter __first, _IIter __last) noexcept : __vec(__first, __last)\
    \ {\n    make();\n  }\n\n  decltype(auto) begin() const noexcept { return __vec.begin();\
    \ }\n\n  decltype(auto) end() const noexcept { return __vec.end(); }\n\n  decltype(auto)\
    \ operator[](size_type __i) const noexcept {\n    assert(__i < size());\n    return\
    \ __vec[__i];\n  }\n\n  size_type size() const noexcept { return __vec.size();\
    \ }\n\n  template <class... _Args> decltype(auto) emplace(_Args&&... __args) noexcept\
    \ {\n    return __vec.emplace_back(std::forward<_Args>(__args)...);\n  }\n\n \
    \ template <class... _Args> void insert(_Args&&... __args) noexcept {\n    __vec.insert(end(),\
    \ std::forward<_Args>(__args)...);\n  }\n\n  /**\n   * @brief Sort and make unique.\n\
    \   * @return Number of different values.\n   */\n  size_type make() noexcept\
    \ {\n    std::sort(begin(), end());\n\n    __vec.erase(std::unique(begin(), end(),\n\
    \                            [](const _Tp& __l, const _Tp& __r) {\n          \
    \                    return !(__l < __r) && !(__r < __l);\n                  \
    \          }),\n                end());\n\n    return size();\n  }\n\n  size_type\
    \ lower_bound(const _Tp& __x) const noexcept {\n    return std::lower_bound(begin(),\
    \ end(), __x) - begin();\n  }\n\n  size_type upper_bound(const _Tp& __x) const\
    \ noexcept {\n    return std::upper_bound(begin(), end(), __x) - begin();\n  }\n\
    };\n\ntemplate <class _IIter>\ncompression(_IIter, _IIter)\n    -> compression<typename\
    \ std::iterator_traits<_IIter>::value_type>;\n\n}  // namespace workspace\n#line\
    \ 2 \"src/data_structure/segment_tree/basic.hpp\"\n\n/**\n * @file basic.hpp\n\
    \ * @brief Segment Tree\n */\n\n#line 10 \"src/data_structure/segment_tree/basic.hpp\"\
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
    \n\nint main() {\n  using i64 = long long;\n  int n, q;\n  scanf(\"%d%d\", &n,\
    \ &q);\n  std::vector<size_t> a(n);\n  for (auto &e : a) scanf(\"%d\", &e);\n\
    \  workspace::compression ccmp(begin(a), end(a));\n  ccmp.make();\n  for (auto\
    \ &&x : a) {\n    x = ccmp.lower_bound(x);\n  }\n  std::vector<int> cnt(ccmp.size());\n\
    \  workspace::segment_tree<int> seg(n);\n  i64 invs = 0;\n  auto addl = [&](int\
    \ i) -> auto {\n    i = a[i];\n    invs += seg.fold(0, i);\n    seg[i]++;\n  };\n\
    \  auto addr = [&](int i) -> auto {\n    i = a[i];\n    invs += seg.fold(i + 1,\
    \ n);\n    seg[i]++;\n  };\n  auto dell = [&](int i) -> auto {\n    i = a[i];\n\
    \    invs -= seg.fold(0, i);\n    seg[i]--;\n  };\n  auto delr = [&](int i) ->\
    \ auto {\n    i = a[i];\n    invs -= seg.fold(i + 1, n);\n    seg[i]--;\n  };\n\
    \  workspace::Mo mo(addl, dell, addr, delr);\n  for (int i = 0; i < q; i++) {\n\
    \    int l, r;\n    scanf(\"%d%d\", &l, &r);\n    mo.insert(l, r);\n  }\n  mo.make();\n\
    \  std::vector<i64> ans(q);\n  for (auto &&e : mo) {\n    ans[e.index] = invs;\n\
    \  }\n  for (i64 x : ans) printf(\"%lld\\n\", x);\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_inversions_query\"\
    \n\n#include <cstdio>\n\n#include \"src/data_structure/Mo.hpp\"\n#include \"src/data_structure/compression.hpp\"\
    \n#include \"src/data_structure/segment_tree/basic.hpp\"\n\nint main() {\n  using\
    \ i64 = long long;\n  int n, q;\n  scanf(\"%d%d\", &n, &q);\n  std::vector<size_t>\
    \ a(n);\n  for (auto &e : a) scanf(\"%d\", &e);\n  workspace::compression ccmp(begin(a),\
    \ end(a));\n  ccmp.make();\n  for (auto &&x : a) {\n    x = ccmp.lower_bound(x);\n\
    \  }\n  std::vector<int> cnt(ccmp.size());\n  workspace::segment_tree<int> seg(n);\n\
    \  i64 invs = 0;\n  auto addl = [&](int i) -> auto {\n    i = a[i];\n    invs\
    \ += seg.fold(0, i);\n    seg[i]++;\n  };\n  auto addr = [&](int i) -> auto {\n\
    \    i = a[i];\n    invs += seg.fold(i + 1, n);\n    seg[i]++;\n  };\n  auto dell\
    \ = [&](int i) -> auto {\n    i = a[i];\n    invs -= seg.fold(0, i);\n    seg[i]--;\n\
    \  };\n  auto delr = [&](int i) -> auto {\n    i = a[i];\n    invs -= seg.fold(i\
    \ + 1, n);\n    seg[i]--;\n  };\n  workspace::Mo mo(addl, dell, addr, delr);\n\
    \  for (int i = 0; i < q; i++) {\n    int l, r;\n    scanf(\"%d%d\", &l, &r);\n\
    \    mo.insert(l, r);\n  }\n  mo.make();\n  std::vector<i64> ans(q);\n  for (auto\
    \ &&e : mo) {\n    ans[e.index] = invs;\n  }\n  for (i64 x : ans) printf(\"%lld\\\
    n\", x);\n}\n"
  dependsOn:
  - src/data_structure/Mo.hpp
  - src/data_structure/compression.hpp
  - src/data_structure/segment_tree/basic.hpp
  - src/algebra/system/monoid.hpp
  isVerificationFile: true
  path: test/library-checker/static_range_inversions_query.test.cpp
  requiredBy: []
  timestamp: '2021-06-25 19:18:38+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/library-checker/static_range_inversions_query.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/static_range_inversions_query.test.cpp
- /verify/test/library-checker/static_range_inversions_query.test.cpp.html
title: test/library-checker/static_range_inversions_query.test.cpp
---
