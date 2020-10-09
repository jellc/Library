---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algebra/system/monoid.hpp
    title: algebra/system/monoid.hpp
  - icon: ':heavy_check_mark:'
    path: data_structure/Mo.hpp
    title: data_structure/Mo.hpp
  - icon: ':heavy_check_mark:'
    path: data_structure/segment_tree/basic.hpp
    title: data_structure/segment_tree/basic.hpp
  - icon: ':heavy_check_mark:'
    path: data_structure/segment_tree/waitlist.hpp
    title: data_structure/segment_tree/waitlist.hpp
  - icon: ':heavy_check_mark:'
    path: utils/coordinate_compression.hpp
    title: utils/coordinate_compression.hpp
  - icon: ':heavy_check_mark:'
    path: utils/sfinae.hpp
    title: utils/sfinae.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/static_range_inversions_query
    links:
    - https://judge.yosupo.jp/problem/static_range_inversions_query
  bundledCode: "#line 1 \"test/library-checker/static_range_inversions_query.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_inversions_query\"\
    \n#include <cstdio>\n\n#line 1 \"data_structure/Mo.hpp\"\n#include <cassert>\n\
    #include <cmath>\n#include <functional>\n#include <vector>\n\ntemplate <class\
    \ Add, class Del>\nclass Mo\n{\n    Add add; Del del;\n    std::vector<size_t>\
    \ lft, rgt, ord;\n    std::vector<size_t>::iterator itr;\n    bool made;\n   \
    \ size_t width, nl, nr;\n\n    void make()\n    {\n        made = true;\n    \
    \    ord.resize(size());\n        for(size_t i = 0; i != size(); ++i) ord[i] =\
    \ i;\n        std::sort(ord.begin(), ord.end(),\n        [&](size_t x, size_t\
    \ y)\n        {\n            if(lft[x] / width != lft[y] / width) return lft[x]\
    \ < lft[y];\n            return rgt[x] < rgt[y];\n        });\n        itr = ord.begin();\n\
    \    }\n\npublic:\n    Mo(size_t n = 0, Add add = Add(), Del del = Del())\n  \
    \      : add(add), del(del), made(), width(sqrt(n)), nl(), nr() {}\n\n    size_t\
    \ size() const { return lft.size(); }\n\n    void set(size_t l, size_t r)\n  \
    \  {\n        assert(!made);\n        lft.emplace_back(l), rgt.emplace_back(r);\n\
    \    }\n\n    size_t process()\n    {\n        if(!made) make();\n        if(itr\
    \ == ord.end()) return ord.size();\n        const size_t id = *itr++, l = lft[id],\
    \ r = rgt[id];\n        while(nl > l) add(--nl);\n        while(nr < r) add(nr++);\n\
    \        while(nl < l) del(nl++);\n        while(nr > r) del(--nr);\n        return\
    \ id;\n    }\n};\n#line 3 \"data_structure/segment_tree/basic.hpp\"\n#include\
    \ <queue>\n#line 5 \"data_structure/segment_tree/basic.hpp\"\n\n#line 2 \"algebra/system/monoid.hpp\"\
    \n#include <limits>\n\nnamespace workspace {\ntemplate <class T, class E = T>\
    \ struct min_monoid {\n  using value_type = T;\n  static T min, max;\n  T value;\n\
    \  min_monoid() : value(max) {}\n  min_monoid(const T &value) : value(value) {}\n\
    \  operator T() const { return value; }\n  min_monoid operator+(const min_monoid\
    \ &rhs) const {\n    return value < rhs.value ? *this : rhs;\n  }\n  min_monoid\
    \ operator*(const E &rhs) const;\n};\n\ntemplate <class T, class E>\nT min_monoid<T,\
    \ E>::min = std::numeric_limits<T>::min() / 2;\ntemplate <class T, class E>\n\
    T min_monoid<T, E>::max = std::numeric_limits<T>::max() / 2;\n\ntemplate <class\
    \ T, class E = T> struct max_monoid : min_monoid<T, E> {\n  using base = min_monoid<T,\
    \ E>;\n  using base::min_monoid;\n  max_monoid() : base(base::min) {}\n  max_monoid\
    \ operator+(const max_monoid &rhs) const {\n    return !(base::value < rhs.value)\
    \ ? *this : rhs;\n  }\n  max_monoid operator*(const E &rhs) const;\n};\n}\n#line\
    \ 2 \"utils/sfinae.hpp\"\n#include <cstdint>\n#include <iterator>\n#include <type_traits>\n\
    \ntemplate <class type, template <class> class trait>\nusing enable_if_trait_type\
    \ = typename std::enable_if<trait<type>::value>::type;\n\ntemplate <class Container>\n\
    using element_type = typename std::decay<decltype(\n    *std::begin(std::declval<Container&>()))>::type;\n\
    \ntemplate <class T, class = int> struct mapped_of {\n  using type = element_type<T>;\n\
    };\ntemplate <class T>\nstruct mapped_of<T,\n                 typename std::pair<int,\
    \ typename T::mapped_type>::first_type> {\n  using type = typename T::mapped_type;\n\
    };\ntemplate <class T> using mapped_type = typename mapped_of<T>::type;\n\ntemplate\
    \ <class T, class = void> struct is_integral_ext : std::false_type {};\ntemplate\
    \ <class T>\nstruct is_integral_ext<\n    T, typename std::enable_if<std::is_integral<T>::value>::type>\n\
    \    : std::true_type {};\ntemplate <> struct is_integral_ext<__int128_t> : std::true_type\
    \ {};\ntemplate <> struct is_integral_ext<__uint128_t> : std::true_type {};\n\
    #if __cplusplus >= 201402\ntemplate <class T>\nconstexpr static bool is_integral_ext_v\
    \ = is_integral_ext<T>::value;\n#endif\n\ntemplate <typename T, typename = void>\
    \ struct multiplicable_uint {\n  using type = uint_least32_t;\n};\ntemplate <typename\
    \ T>\nstruct multiplicable_uint<T, typename std::enable_if<(2 < sizeof(T))>::type>\
    \ {\n  using type = uint_least64_t;\n};\ntemplate <typename T>\nstruct multiplicable_uint<T,\
    \ typename std::enable_if<(4 < sizeof(T))>::type> {\n  using type = __uint128_t;\n\
    };\n#line 3 \"data_structure/segment_tree/waitlist.hpp\"\n\nnamespace internal\
    \ {\nstruct waitlist : std::queue<size_t> {\n  waitlist(size_t n) : in(n) {}\n\
    \n  bool push(size_t index) {\n    assert(index < in.size());\n    if (in[index])\
    \ return false;\n    emplace(index);\n    return (in[index] = true);\n  }\n\n\
    \  size_t pop() {\n    assert(!empty());\n    auto index = front();\n    std::queue<size_t>::pop();\n\
    \    in[index] = false;\n    return index;\n  }\n\n private:\n  std::vector<int_least8_t>\
    \ in;\n};\n}\n#line 9 \"data_structure/segment_tree/basic.hpp\"\n\ntemplate <class\
    \ Monoid, class Container = std::vector<Monoid>>\nclass segment_tree {\n  static_assert(std::is_same<Monoid,\
    \ mapped_type<Container>>::value);\n\n  size_t size_orig, height, size_ext;\n\
    \  Container data;\n  internal::waitlist wait;\n\n  void repair() {\n    while\
    \ (!wait.empty()) {\n      const size_t index = wait.pop() >> 1;\n      if (index\
    \ && wait.push(index)) pull(index);\n    }\n  }\n\n  void pull(const size_t node)\
    \ {\n    data[node] = data[node << 1] + data[node << 1 | 1];\n  }\n\n  template\
    \ <class Pred>\n  size_t left_partition_subtree(size_t index, const Pred pred,\n\
    \                                Monoid mono) const {\n    assert(index);\n  \
    \  while (index < size_ext) {\n      const Monoid tmp = data[(index <<= 1) | 1]\
    \ + mono;\n      if (pred(tmp))\n        mono = tmp;\n      else\n        ++index;\n\
    \    }\n    return ++index -= size_ext;\n  }\n\n  template <class Pred>\n  size_t\
    \ right_partition_subtree(size_t index, const Pred pred,\n                   \
    \              Monoid mono) const {\n    assert(index);\n    while (index < size_ext)\
    \ {\n      const Monoid tmp = mono + data[index <<= 1];\n      if (pred(tmp))\
    \ ++index, mono = tmp;\n    }\n    return (index -= size_ext) < size_orig ? index\
    \ : size_orig;\n  }\n\n public:\n  using value_type = Monoid;\n\n  segment_tree(const\
    \ size_t n = 0)\n      : size_orig{n},\n        height(n > 1 ? 32 - __builtin_clz(n\
    \ - 1) : 0),\n        size_ext{1u << height},\n        data(size_ext << 1),\n\
    \        wait(size_ext << 1) {}\n\n  segment_tree(const size_t n, const Monoid\
    \ &init) : segment_tree(n) {\n    std::fill(std::next(std::begin(data), size_ext),\
    \ std::end(data), init);\n    for (size_t i{size_ext}; --i;) pull(i);\n  }\n\n\
    \  template <class iter_type, class value_type = typename std::iterator_traits<\n\
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
    \      }\n    }\n    return size_orig;\n  }\n};  // class segment_tree\n#line\
    \ 2 \"utils/coordinate_compression.hpp\"\n#include <algorithm>\n#line 5 \"utils/coordinate_compression.hpp\"\
    \n\ntemplate <class T> class coordinate_compression {\n  std::vector<T> uniquely;\n\
    \  std::vector<size_t> compressed;\n\n public:\n  coordinate_compression(const\
    \ std::vector<T> &raw)\n      : uniquely(raw), compressed(raw.size()) {\n    std::sort(uniquely.begin(),\
    \ uniquely.end());\n    uniquely.erase(std::unique(uniquely.begin(), uniquely.end()),\n\
    \                   uniquely.end());\n    for (size_t i = 0; i != size(); ++i)\n\
    \      compressed[i] =\n          std::lower_bound(uniquely.begin(), uniquely.end(),\
    \ raw[i]) -\n          uniquely.begin();\n  }\n\n  size_t operator[](const size_t\
    \ idx) const {\n    assert(idx < size());\n    return compressed[idx];\n  }\n\n\
    \  size_t size() const { return compressed.size(); }\n\n  size_t count() const\
    \ { return uniquely.size(); }\n\n  T value(const size_t ord) const {\n    assert(ord\
    \ < count());\n    return uniquely[ord];\n  }\n\n  size_t order(const T &value)\
    \ const {\n    return std::lower_bound(uniquely.begin(), uniquely.end(), value)\
    \ -\n           uniquely.begin();\n  }\n\n  auto begin() { return compressed.begin();\
    \ }\n  auto end() { return compressed.end(); }\n  auto rbegin() { return compressed.rbegin();\
    \ }\n  auto rend() { return compressed.rend(); }\n};\n#line 7 \"test/library-checker/static_range_inversions_query.test.cpp\"\
    \nusing i64 = int64_t;\n\nint main() {\n  int n, q;\n  scanf(\"%d%d\", &n, &q);\n\
    \  std::vector<int> a(n);\n  for (int &x : a) scanf(\"%d\", &x);\n  coordinate_compression\
    \ ccmp(a);\n  std::vector<int> cnt(ccmp.count());\n  segment_tree<int> seg(n);\n\
    \  int nl = 0, nr = 0;\n  i64 invs = 0;\n  auto add = [&](int i) {\n    int nv\
    \ = ccmp[i];\n    if (i < nl)  // left end\n    {\n      invs += seg.fold(0, nv);\n\
    \      nl--;\n    } else  // right end\n    {\n      invs += seg.fold(nv + 1,\
    \ n);\n      nr++;\n    }\n    seg[nv]++;\n  };\n  auto del = [&](int i) {\n \
    \   int nv = ccmp[i];\n    if (i == nl)  // left end\n    {\n      invs -= seg.fold(0,\
    \ nv);\n      nl++;\n    } else  // right end\n    {\n      assert(nr == i + 1);\n\
    \      invs -= seg.fold(nv + 1, n);\n      nr--;\n    }\n    seg[nv]--;\n  };\n\
    \  Mo mo(n, add, del);\n  for (int i = 0; i < q; i++) {\n    int l, r;\n    scanf(\"\
    %d%d\", &l, &r);\n    mo.set(l, r);\n  }\n  std::vector<i64> ans(q);\n  for (int\
    \ i = 0; i < q; i++) {\n    int id = mo.process();\n    ans[id] = invs;\n  }\n\
    \  for (i64 x : ans) printf(\"%lld\\n\", x);\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_inversions_query\"\
    \n#include <cstdio>\n\n#include \"data_structure/Mo.hpp\"\n#include \"data_structure/segment_tree/basic.hpp\"\
    \n#include \"utils/coordinate_compression.hpp\"\nusing i64 = int64_t;\n\nint main()\
    \ {\n  int n, q;\n  scanf(\"%d%d\", &n, &q);\n  std::vector<int> a(n);\n  for\
    \ (int &x : a) scanf(\"%d\", &x);\n  coordinate_compression ccmp(a);\n  std::vector<int>\
    \ cnt(ccmp.count());\n  segment_tree<int> seg(n);\n  int nl = 0, nr = 0;\n  i64\
    \ invs = 0;\n  auto add = [&](int i) {\n    int nv = ccmp[i];\n    if (i < nl)\
    \  // left end\n    {\n      invs += seg.fold(0, nv);\n      nl--;\n    } else\
    \  // right end\n    {\n      invs += seg.fold(nv + 1, n);\n      nr++;\n    }\n\
    \    seg[nv]++;\n  };\n  auto del = [&](int i) {\n    int nv = ccmp[i];\n    if\
    \ (i == nl)  // left end\n    {\n      invs -= seg.fold(0, nv);\n      nl++;\n\
    \    } else  // right end\n    {\n      assert(nr == i + 1);\n      invs -= seg.fold(nv\
    \ + 1, n);\n      nr--;\n    }\n    seg[nv]--;\n  };\n  Mo mo(n, add, del);\n\
    \  for (int i = 0; i < q; i++) {\n    int l, r;\n    scanf(\"%d%d\", &l, &r);\n\
    \    mo.set(l, r);\n  }\n  std::vector<i64> ans(q);\n  for (int i = 0; i < q;\
    \ i++) {\n    int id = mo.process();\n    ans[id] = invs;\n  }\n  for (i64 x :\
    \ ans) printf(\"%lld\\n\", x);\n}\n"
  dependsOn:
  - data_structure/Mo.hpp
  - data_structure/segment_tree/basic.hpp
  - algebra/system/monoid.hpp
  - utils/sfinae.hpp
  - data_structure/segment_tree/waitlist.hpp
  - utils/coordinate_compression.hpp
  isVerificationFile: true
  path: test/library-checker/static_range_inversions_query.test.cpp
  requiredBy: []
  timestamp: '2020-10-10 01:30:31+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/library-checker/static_range_inversions_query.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/static_range_inversions_query.test.cpp
- /verify/test/library-checker/static_range_inversions_query.test.cpp.html
title: test/library-checker/static_range_inversions_query.test.cpp
---
