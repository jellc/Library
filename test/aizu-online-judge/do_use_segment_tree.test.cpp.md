---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/segment_tree/lazy.hpp
    title: data_structure/segment_tree/lazy.hpp
  - icon: ':heavy_check_mark:'
    path: data_structure/segment_tree/waitlist.hpp
    title: data_structure/segment_tree/waitlist.hpp
  - icon: ':heavy_check_mark:'
    path: graph/undirected/tree/heavy_light_decomposition.hpp
    title: graph/undirected/tree/heavy_light_decomposition.hpp
  - icon: ':heavy_check_mark:'
    path: utils/sfinae.hpp
    title: utils/sfinae.hpp
  - icon: ':heavy_check_mark:'
    path: utils/stream.hpp
    title: utils/stream.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/2450
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/2450
  bundledCode: "#line 1 \"test/aizu-online-judge/do_use_segment_tree.test.cpp\"\n\
    #define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/2450\"\n#include <algorithm>\n\
    \n#line 2 \"data_structure/segment_tree/lazy.hpp\"\n#include <cassert>\n#include\
    \ <queue>\n#include <vector>\n\n#line 2 \"utils/sfinae.hpp\"\n#include <cstdint>\n\
    #include <type_traits>\n\ntemplate <class type, template <class> class trait>\n\
    using enable_if_trait_type = typename std::enable_if<trait<type>::value>::type;\n\
    \ntemplate <class Container>\nusing element_type = typename std::decay<decltype(\n\
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
    \ < sizeof(T))>::type> {\n  using type = __uint128_t;\n};\n#line 3 \"data_structure/segment_tree/waitlist.hpp\"\
    \n\nnamespace internal {\nstruct waitlist : std::queue<size_t> {\n  waitlist(size_t\
    \ n) : in(n) {}\n\n  bool push(size_t index) {\n    assert(index < in.size());\n\
    \    if (in[index]) return false;\n    emplace(index);\n    return (in[index]\
    \ = true);\n  }\n\n  size_t pop() {\n    assert(!empty());\n    auto index = front();\n\
    \    std::queue<size_t>::pop();\n    in[index] = false;\n    return index;\n \
    \ }\n\n private:\n  std::vector<int_least8_t> in;\n};\n}\n#line 8 \"data_structure/segment_tree/lazy.hpp\"\
    \n\ntemplate <class Monoid, class Endomorphism,\n          class Monoid_container\
    \ = std::vector<Monoid>,\n          class Endomorphism_container = std::vector<Endomorphism>>\n\
    class lazy_segment_tree {\n  static_assert(std::is_same<Monoid, mapped_type<Monoid_container>>::value);\n\
    \n  static_assert(\n      std::is_same<Endomorphism, mapped_type<Endomorphism_container>>::value);\n\
    \n  static_assert(std::is_same<Monoid, decltype(Monoid{} + Monoid{})>::value,\n\
    \                \"\\'Monoid\\' has no proper binary operator+.\");\n\n  static_assert(std::is_same<Endomorphism,\n\
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
    \     ++left;\n      }\n    }\n    return size_orig;\n  }\n};  // class lazy_segment_tree\n\
    #line 3 \"graph/undirected/tree/heavy_light_decomposition.hpp\"\n#include <numeric>\n\
    #line 5 \"graph/undirected/tree/heavy_light_decomposition.hpp\"\n\nclass heavy_light_decomposition\
    \ {\n  std::vector<std::vector<size_t>> tree;\n  std::vector<size_t> sorted, in,\
    \ out, head;\n\n  size_t sort_children(size_t node, size_t prev) {\n    size_t\
    \ sum = 0, max_size = 0;\n    for (size_t &to : tree[node]) {\n      if (to ==\
    \ prev) continue;\n      size_t child_size = sort_children(to, node);\n      sum\
    \ += child_size;\n      if (max_size < child_size) {\n        max_size = child_size;\n\
    \        std::swap(tree[node].front(), to);\n      }\n    }\n    return sum +\
    \ 1;\n  }\n\n  void traverse(size_t node, size_t prev) {\n    in[node] = sorted.size();\n\
    \    sorted.emplace_back(node);\n    if (tree[node].front() != prev) {\n     \
    \ for (const size_t to : tree[node])\n        if (to != prev) head[to] = node\
    \ + size();\n      head[tree[node].front()] = head[node] < size() ? head[node]\
    \ : node;\n      for (const size_t to : tree[node])\n        if (to != prev) traverse(to,\
    \ node);\n    }\n    out[node] = sorted.size();\n  }\n\n public:\n  using interval\
    \ = std::pair<size_t, size_t>;\n\n  heavy_light_decomposition(size_t n) : tree(n),\
    \ in(n), out(n), head(n) {}\n\n  size_t size() const { return tree.size(); }\n\
    \n  size_t size(size_t node) const { return out[node] - in[node]; }\n\n  void\
    \ add_edge(size_t u, size_t v) {\n    assert(u < size());\n    assert(v < size());\n\
    \    tree[u].emplace_back(v);\n    tree[v].emplace_back(u);\n  }\n\n  const decltype(tree)\
    \ &graph() const { return tree; }\n\n  // O(n)\n  void make(size_t root) {\n \
    \   sorted.clear();\n    sort_children(root, root);\n    traverse(root, root);\n\
    \  }\n\n  size_t prev_node(size_t node) const {\n    assert(in[node]);\n    return\
    \ sorted[in[node] - 1];\n  }\n\n  size_t next_node(size_t node) const {\n    assert(in[node]\
    \ + 1 < size());\n    return sorted[in[node] + 1];\n  }\n\n  size_t index(size_t\
    \ node) const { return in[node]; }\n\n  size_t node(size_t index) const { return\
    \ sorted[index]; }\n\n  size_t root() const { return sorted.front(); }\n\n  interval\
    \ subtree(size_t root) const { return {in[root], out[root]}; }\n\n  size_t parent(size_t\
    \ node) const {\n    return head[node] < size() ? prev_node(node) : head[node]\
    \ - size();\n  }\n\n  size_t top(size_t node) const {\n    return head[node] <\
    \ size() ? head[node] : node;\n  }\n\n  // O(log(n))\n  size_t lca(size_t u, size_t\
    \ v) {\n    if (in[v] < in[u]) std::swap(u, v);\n    if (in[v] < out[u]) return\
    \ u;\n    while (in[u] < in[v]) v = parent(top(v));\n    return v;\n  }\n\n  //\
    \ O(log(n))\n  std::pair<std::vector<interval>, std::vector<interval>> path_decomposition(\n\
    \      size_t u, size_t v) const {\n    if (in[v] < in[u]) std::swap(u, v);\n\
    \    std::vector<interval> left, right;\n    size_t utop = top(u), vtop = top(v);\n\
    \    while (utop != vtop) {\n      left.emplace_back(in[vtop], in[v] + 1);\n \
    \     vtop = top(v = parent(vtop));\n      if (in[v] < in[u]) {\n        std::swap(u,\
    \ v);\n        std::swap(utop, vtop);\n        std::swap(left, right);\n     \
    \ }\n    }\n    left.emplace_back(in[u], in[v] + 1);\n    return std::make_pair(left,\
    \ right);\n  }\n\n  // O(log(n))\n  std::vector<interval> path_decomposition(size_t\
    \ node) const {\n    auto [left, right] = path_decomposition(root(), node);\n\
    \    assert(left.size() == 1);\n    right.insert(right.begin(), left.front());\n\
    \    return right;\n  }\n};\n#line 2 \"utils/stream.hpp\"\n#include <iostream>\n\
    #include <tuple>\n\n#line 6 \"utils/stream.hpp\"\nnamespace std {\ntemplate <class\
    \ T, class U> istream &operator>>(istream &is, pair<T, U> &p) {\n  return is >>\
    \ p.first >> p.second;\n}\ntemplate <class T, class U>\nostream &operator<<(ostream\
    \ &os, const pair<T, U> &p) {\n  return os << p.first << ' ' << p.second;\n}\n\
    template <class tuple_t, size_t index> struct tuple_is {\n  static istream &apply(istream\
    \ &is, tuple_t &t) {\n    tuple_is<tuple_t, index - 1>::apply(is, t);\n    return\
    \ is >> get<index>(t);\n  }\n};\ntemplate <class tuple_t> struct tuple_is<tuple_t,\
    \ SIZE_MAX> {\n  static istream &apply(istream &is, tuple_t &t) { return is; }\n\
    };\ntemplate <class... T> istream &operator>>(istream &is, tuple<T...> &t) {\n\
    \  return tuple_is<tuple<T...>, tuple_size<tuple<T...>>::value - 1>::apply(is,\n\
    \                                                                          t);\n\
    }\ntemplate <class tuple_t, size_t index> struct tuple_os {\n  static ostream\
    \ &apply(ostream &os, const tuple_t &t) {\n    tuple_os<tuple_t, index - 1>::apply(os,\
    \ t);\n    return os << ' ' << get<index>(t);\n  }\n};\ntemplate <class tuple_t>\
    \ struct tuple_os<tuple_t, 0> {\n  static ostream &apply(ostream &os, const tuple_t\
    \ &t) {\n    return os << get<0>(t);\n  }\n};\ntemplate <class tuple_t> struct\
    \ tuple_os<tuple_t, SIZE_MAX> {\n  static ostream &apply(ostream &os, const tuple_t\
    \ &t) { return os; }\n};\ntemplate <class... T> ostream &operator<<(ostream &os,\
    \ const tuple<T...> &t) {\n  return tuple_os<tuple<T...>, tuple_size<tuple<T...>>::value\
    \ - 1>::apply(os,\n                                                          \
    \                t);\n}\ntemplate <class Container, typename Value = element_type<Container>>\n\
    typename enable_if<!is_same<typename decay<Container>::type, string>::value &&\n\
    \                       !is_same<typename decay<Container>::type, char *>::value,\n\
    \                   istream &>::type\noperator>>(istream &is, Container &cont)\
    \ {\n  for (auto &&e : cont) is >> e;\n  return is;\n}\ntemplate <class Container,\
    \ typename Value = element_type<Container>>\ntypename enable_if<!is_same<typename\
    \ decay<Container>::type, string>::value &&\n                       !is_same<typename\
    \ decay<Container>::type, char *>::value,\n                   ostream &>::type\n\
    operator<<(ostream &os, const Container &cont) {\n  bool head = true;\n  for (auto\
    \ &&e : cont) head ? head = 0 : (os << ' ', 0), os << e;\n  return os;\n}\n} \
    \ // namespace std\n#line 7 \"test/aizu-online-judge/do_use_segment_tree.test.cpp\"\
    \n\nint main() {\n  struct endo {\n    bool assign = false;\n    int value;\n\
    \    endo() = default;\n    endo(int v) : assign(true), value(v) {}\n    endo\
    \ operator*(endo rhs) {\n      if (rhs.assign) return rhs;\n      return *this;\n\
    \    }\n  };\n  struct mono {\n    int cnt = 0;\n    int sum = 0;\n    int left\
    \ = 0;\n    int right = 0;\n    int max = 0;\n    int best = -10000;\n    mono\
    \ operator+(mono rhs) {\n      return {cnt + rhs.cnt,\n              sum + rhs.sum,\n\
    \              std::max(left, sum + rhs.left),\n              std::max(right +\
    \ rhs.sum, rhs.right),\n              std::max({max, rhs.max, right + rhs.left}),\n\
    \              std::max(best, rhs.best)};\n    }\n    mono operator*(endo rhs)\
    \ {\n      mono ret = *this;\n      if (rhs.assign) {\n        if (rhs.value <\
    \ 0) {\n          ret.sum = rhs.value * cnt;\n          ret.left = ret.right =\
    \ ret.max = 0;\n        } else {\n          ret.sum = ret.left = ret.right = ret.max\
    \ = cnt * rhs.value;\n        }\n        ret.best = rhs.value;\n      }\n    \
    \  return ret;\n    }\n  };\n\n  int n, q;\n  std::cin >> n >> q;\n  std::vector<int>\
    \ w(n);\n  std::cin >> w;\n  heavy_light_decomposition hld(n);\n  for (auto e\
    \ = 1; e != n; ++e) {\n    int u, v;\n    std::cin >> u >> v;\n    --u, --v;\n\
    \    hld.add_edge(u, v);\n  }\n  hld.make(0);\n  lazy_segment_tree<mono, endo>\
    \ seg(n);\n  for (auto v = 0; v != n; ++v) {\n    auto &now = seg[hld.index(v)];\n\
    \    now.cnt = 1;\n    now = now * endo{w[v]};\n  }\n  while (q--) {\n    int\
    \ tp, a, b, c;\n    std::cin >> tp >> a >> b >> c;\n    --a, --b;\n    auto [left,\
    \ right] = hld.path_decomposition(a, b);\n    if (tp == 1) {\n      for (auto\
    \ &&[l, r] : left) {\n        seg.update(l, r, c);\n      }\n      for (auto &&[l,\
    \ r] : right) {\n        seg.update(l, r, c);\n      }\n    } else {\n      mono\
    \ lv;\n      for (auto &&[l, r] : left) {\n        lv = seg.fold(l, r) + lv;\n\
    \      }\n      mono rv;\n      for (auto &&[l, r] : right) {\n        rv = seg.fold(l,\
    \ r) + rv;\n      }\n      std::swap(lv.left, lv.right);\n      auto all = lv\
    \ + rv;\n      if (all.max)\n        std::cout << all.max << '\\n';\n      else\n\
    \        std::cout << all.best << '\\n';\n    }\n  }\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/2450\"\n#include\
    \ <algorithm>\n\n#include \"data_structure/segment_tree/lazy.hpp\"\n#include \"\
    graph/undirected/tree/heavy_light_decomposition.hpp\"\n#include \"utils/stream.hpp\"\
    \n\nint main() {\n  struct endo {\n    bool assign = false;\n    int value;\n\
    \    endo() = default;\n    endo(int v) : assign(true), value(v) {}\n    endo\
    \ operator*(endo rhs) {\n      if (rhs.assign) return rhs;\n      return *this;\n\
    \    }\n  };\n  struct mono {\n    int cnt = 0;\n    int sum = 0;\n    int left\
    \ = 0;\n    int right = 0;\n    int max = 0;\n    int best = -10000;\n    mono\
    \ operator+(mono rhs) {\n      return {cnt + rhs.cnt,\n              sum + rhs.sum,\n\
    \              std::max(left, sum + rhs.left),\n              std::max(right +\
    \ rhs.sum, rhs.right),\n              std::max({max, rhs.max, right + rhs.left}),\n\
    \              std::max(best, rhs.best)};\n    }\n    mono operator*(endo rhs)\
    \ {\n      mono ret = *this;\n      if (rhs.assign) {\n        if (rhs.value <\
    \ 0) {\n          ret.sum = rhs.value * cnt;\n          ret.left = ret.right =\
    \ ret.max = 0;\n        } else {\n          ret.sum = ret.left = ret.right = ret.max\
    \ = cnt * rhs.value;\n        }\n        ret.best = rhs.value;\n      }\n    \
    \  return ret;\n    }\n  };\n\n  int n, q;\n  std::cin >> n >> q;\n  std::vector<int>\
    \ w(n);\n  std::cin >> w;\n  heavy_light_decomposition hld(n);\n  for (auto e\
    \ = 1; e != n; ++e) {\n    int u, v;\n    std::cin >> u >> v;\n    --u, --v;\n\
    \    hld.add_edge(u, v);\n  }\n  hld.make(0);\n  lazy_segment_tree<mono, endo>\
    \ seg(n);\n  for (auto v = 0; v != n; ++v) {\n    auto &now = seg[hld.index(v)];\n\
    \    now.cnt = 1;\n    now = now * endo{w[v]};\n  }\n  while (q--) {\n    int\
    \ tp, a, b, c;\n    std::cin >> tp >> a >> b >> c;\n    --a, --b;\n    auto [left,\
    \ right] = hld.path_decomposition(a, b);\n    if (tp == 1) {\n      for (auto\
    \ &&[l, r] : left) {\n        seg.update(l, r, c);\n      }\n      for (auto &&[l,\
    \ r] : right) {\n        seg.update(l, r, c);\n      }\n    } else {\n      mono\
    \ lv;\n      for (auto &&[l, r] : left) {\n        lv = seg.fold(l, r) + lv;\n\
    \      }\n      mono rv;\n      for (auto &&[l, r] : right) {\n        rv = seg.fold(l,\
    \ r) + rv;\n      }\n      std::swap(lv.left, lv.right);\n      auto all = lv\
    \ + rv;\n      if (all.max)\n        std::cout << all.max << '\\n';\n      else\n\
    \        std::cout << all.best << '\\n';\n    }\n  }\n}\n"
  dependsOn:
  - data_structure/segment_tree/lazy.hpp
  - utils/sfinae.hpp
  - data_structure/segment_tree/waitlist.hpp
  - graph/undirected/tree/heavy_light_decomposition.hpp
  - utils/stream.hpp
  isVerificationFile: true
  path: test/aizu-online-judge/do_use_segment_tree.test.cpp
  requiredBy: []
  timestamp: '2020-09-30 13:49:59+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aizu-online-judge/do_use_segment_tree.test.cpp
layout: document
redirect_from:
- /verify/test/aizu-online-judge/do_use_segment_tree.test.cpp
- /verify/test/aizu-online-judge/do_use_segment_tree.test.cpp.html
title: test/aizu-online-judge/do_use_segment_tree.test.cpp
---
