---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: config.hpp
    title: Configuration
  - icon: ':heavy_check_mark:'
    path: graph/directed/flow/base.hpp
    title: graph/directed/flow/base.hpp
  - icon: ':heavy_check_mark:'
    path: graph/directed/flow/min_cost_flow.hpp
    title: graph/directed/flow/min_cost_flow.hpp
  - icon: ':heavy_check_mark:'
    path: utils/io.hpp
    title: utils/io.hpp
  - icon: ':heavy_check_mark:'
    path: utils/io/casefmt.hpp
    title: Case Output Format
  - icon: ':heavy_check_mark:'
    path: utils/io/read.hpp
    title: utils/io/read.hpp
  - icon: ':heavy_check_mark:'
    path: utils/io/stream.hpp
    title: utils/io/stream.hpp
  - icon: ':heavy_check_mark:'
    path: utils/sfinae.hpp
    title: utils/sfinae.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/challenges/sources/VPC/RUPC/2815?year=2017
    links:
    - https://onlinejudge.u-aizu.ac.jp/challenges/sources/VPC/RUPC/2815?year=2017
  bundledCode: "#line 1 \"test/aizu-online-judge/aors_score.test.cpp\"\n#define PROBLEM\
    \ \\\n  \"https://onlinejudge.u-aizu.ac.jp/challenges/sources/VPC/RUPC/2815?year=2017\"\
    \n#line 2 \"graph/directed/flow/min_cost_flow.hpp\"\n#include <algorithm>\n#include\
    \ <queue>\n\n#line 2 \"graph/directed/flow/base.hpp\"\n#include <cassert>\n#include\
    \ <vector>\n// the base class of flow algorithms.\ntemplate <class cap_t, class\
    \ cost_t> struct flow_base {\n  struct edge_t {\n    size_t src, dst;\n    cap_t\
    \ cap;\n    cost_t cost;\n    edge_t *rev;\n    edge_t() = default;\n    edge_t(size_t\
    \ src, size_t dst, const cap_t &cap, edge_t *rev)\n        : src(src), dst(dst),\
    \ cap(cap), rev(rev) {}\n    edge_t(size_t src, size_t dst, const cap_t &cap,\
    \ const cost_t &cost,\n           edge_t *rev)\n        : src(src), dst(dst),\
    \ cap(cap), cost(cost), rev(rev) {}\n    const cap_t &flow(const cap_t &f = 0)\
    \ { return cap -= f, rev->cap += f; }\n    bool avbl() const { return static_cast<cap_t>(0)\
    \ < cap; }\n  };  // class edge_t\n\n  class adj_type {\n    edge_t *fst, *lst,\
    \ *clst;\n\n   public:\n    template <class... Args> edge_t *emplace(Args &&...\
    \ args) {\n      if (lst == clst) {\n        size_t len(clst - fst);\n       \
    \ edge_t *nfst = lst = new edge_t[len << 1];\n        for (edge_t *p{fst}; p !=\
    \ clst; ++p, ++lst)\n          p->rev->rev = lst, *lst = *p;\n        delete[]\
    \ fst;\n        fst = nfst;\n        clst = lst + len;\n      }\n      *lst =\
    \ edge_t(args...);\n      return lst++;\n    }\n    adj_type() : fst(new edge_t[1]),\
    \ lst(fst), clst(fst + 1) {}\n    ~adj_type() { delete[] fst; }\n    edge_t &operator[](size_t\
    \ i) {\n      assert(i < size());\n      return *(fst + i);\n    }\n    size_t\
    \ size() const { return lst - fst; }\n    edge_t *begin() const { return fst;\
    \ }\n    edge_t *end() const { return lst; }\n  };  // class adj_type\n\n  flow_base(size_t\
    \ n = 0) : adjs(n) {}\n\n  flow_base(const flow_base &other) : adjs(other.size())\
    \ {\n    for (size_t node{}; node != size(); ++node)\n      for (const auto &[src,\
    \ dst, cap, cost, rev] : other[node])\n        if (src == node) {\n          edge_t\
    \ *ptr = adjs[src].emplace(src, dst, cap, cost, nullptr);\n          ptr->rev\
    \ = adjs[dst].emplace(dst, src, rev->cap, -cost, ptr);\n          rev->src = nil;\n\
    \        } else {\n          rev->rev->src = node;\n        }\n  }\n\n  flow_base\
    \ &operator=(const flow_base &rhs) {\n    if (this != &rhs) adjs.swap(flow_base(rhs).adjs);\n\
    \    return *this;\n  }\n\n  size_t size() const { return adjs.size(); }\n\n \
    \ adj_type &operator[](size_t node) {\n    assert(node < size());\n    return\
    \ adjs[node];\n  }\n  const adj_type &operator[](size_t node) const {\n    assert(node\
    \ < size());\n    return adjs[node];\n  }\n\n  virtual edge_t *add_edge(size_t\
    \ src, size_t dst, const cap_t &cap,\n                           const cost_t\
    \ &cost) {\n    assert(src < size());\n    assert(dst < size());\n    assert(!(cap\
    \ < static_cast<cap_t>(0)));\n    if (!(static_cast<cap_t>(0) < cap) || src ==\
    \ dst) return nullptr;\n    edge_t *ptr = adjs[src].emplace(src, dst, cap, cost,\
    \ nullptr);\n    ptr->rev = adjs[dst].emplace(dst, src, 0, -cost, ptr);\n    return\
    \ ptr;\n  }\n\n protected:\n  constexpr static size_t nil = -1;\n  std::vector<adj_type>\
    \ adjs;\n};  // class flow_base\n#line 6 \"graph/directed/flow/min_cost_flow.hpp\"\
    \n// Successive shortest paths algorithm.\ntemplate <class cap_t, class cost_t,\
    \ bool density_tag = false>\nclass min_cost_flow : public flow_base<cap_t, cost_t>\
    \ {\n  using base = flow_base<cap_t, cost_t>;\n  using edge_t = typename base::edge_t;\n\
    \  using base::adjs;\n  using base::nil;\n\n  cost_t min_cost, total_cost;\n \
    \ std::vector<cap_t> supp;\n  std::vector<cost_t> ptnl;\n\n  void copy_member(const\
    \ min_cost_flow &other) {\n    min_cost = other.min_cost;\n    total_cost = other.total_cost;\n\
    \    supp = other.supp;\n    ptnl = other.ptnl;\n  }\n\n  void Dijkstra(std::vector<edge_t\
    \ *> &last) {\n    const cost_t infty(total_cost + 1);\n    std::vector<cost_t>\
    \ nptnl(size(), infty);\n    if constexpr (density_tag) {\n      // O(V^2)\n \
    \     std::vector<bool> used(size());\n      for (size_t src{}; src != size();\
    \ ++src) {\n        if (static_cast<cap_t>(0) < supp[src]) {\n          used[src]\
    \ = true;\n          nptnl[src] = 0;\n          for (edge_t &e : adjs[src]) {\n\
    \            if (static_cast<cap_t>(0) < supp[e.dst]) continue;\n            if\
    \ (e.avbl() && e.cost < nptnl[e.dst]) {\n              nptnl[e.dst] = e.cost;\n\
    \              last[e.dst] = &e;\n            }\n          }\n        }\n    \
    \  }\n      for (;;) {\n        size_t src{nil};\n        cost_t sp{infty};\n\
    \        for (size_t node{}; node != size(); ++node) {\n          if (used[node]\
    \ || nptnl[node] == infty) continue;\n          cost_t dist{nptnl[node] - ptnl[node]};\n\
    \          if (dist < sp) {\n            sp = dist;\n            src = node;\n\
    \          }\n        }\n        if (src == nil) break;\n        used[src] = true;\n\
    \        for (edge_t &e : adjs[src]) {\n          if (e.avbl() && nptnl[src] +\
    \ e.cost < nptnl[e.dst]) {\n            nptnl[e.dst] = nptnl[src] + e.cost;\n\
    \            last[e.dst] = &e;\n          }\n        }\n      }\n    } else {\n\
    \      // O((V + E)logV)\n      struct node_t {\n        size_t id;\n        cost_t\
    \ dist;\n        node_t(size_t id, cost_t dist) : id(id), dist(dist) {}\n    \
    \    bool operator<(const node_t &rhs) const { return rhs.dist < dist; }\n   \
    \   };\n      std::priority_queue<node_t> que;\n      for (size_t src{}; src !=\
    \ size(); ++src) {\n        if (supp[src] > static_cast<cap_t>(0)) {\n       \
    \   nptnl[src] = 0;\n          for (edge_t &e : adjs[src]) {\n            if (supp[e.dst]\
    \ > static_cast<cap_t>(0)) continue;\n            if (e.avbl() && nptnl[e.dst]\
    \ > e.cost) {\n              que.emplace(e.dst, (nptnl[e.dst] = e.cost) - ptnl[e.dst]);\n\
    \              last[e.dst] = &e;\n            }\n          }\n        }\n    \
    \  }\n      while (!que.empty()) {\n        auto [src, ndist] = que.top();\n \
    \       que.pop();\n        if (ndist + ptnl[src] != nptnl[src]) continue;\n \
    \       for (edge_t &e : adjs[src]) {\n          if (e.avbl() && nptnl[e.dst]\
    \ > nptnl[src] + e.cost) {\n            que.emplace(e.dst,\n                 \
    \       (nptnl[e.dst] = nptnl[src] + e.cost) - ptnl[e.dst]);\n            last[e.dst]\
    \ = &e;\n          }\n        }\n      }\n    }\n    ptnl.swap(nptnl);\n  }\n\n\
    \ public:\n  using base::size;\n\n  min_cost_flow(size_t n = 0)\n      : base::flow_base(n),\
    \ min_cost(0), total_cost(0), supp(n), ptnl(n) {}\n\n  min_cost_flow(const min_cost_flow\
    \ &other) : base::flow_base(other) {\n    copy_member(other);\n  }\n\n  min_cost_flow\
    \ &operator=(const min_cost_flow &other) {\n    base::operator=(other);\n    copy_member(other);\n\
    \    return *this;\n  }\n\n  edge_t *add_edge(size_t src, size_t dst, const cost_t\
    \ &cost);\n\n  edge_t *add_edge(size_t src, size_t dst, const cap_t &cap,\n  \
    \                 const cost_t &cost) override {\n    assert(src != dst);\n  \
    \  if (cost < static_cast<cost_t>(0)) {\n      supp[src] -= cap;\n      supp[dst]\
    \ += cap;\n      min_cost += cap * cost;\n      total_cost -= cap * cost;\n  \
    \    return base::add_edge(dst, src, cap, -cost);\n    }\n    total_cost += cap\
    \ * cost;\n    return base::add_edge(src, dst, cap, cost);\n  }\n\n  edge_t *add_edge(size_t\
    \ src, size_t dst, const cap_t &lower,\n                   const cap_t &upper,\
    \ const cost_t &cost) {\n    assert(!(upper < lower));\n    supp[src] -= lower;\n\
    \    supp[dst] += lower;\n    min_cost += lower * cost;\n    return add_edge(src,\
    \ dst, upper - lower, cost);\n  }\n\n  const cap_t &supply(size_t node, const\
    \ cap_t &vol = 0) {\n    assert(node < size());\n    return supp[node] += vol;\n\
    \  }\n\n  const cap_t &demand(size_t node, const cap_t &vol) {\n    return supply(node,\
    \ -vol);\n  }\n\n  bool flow() {\n    for (bool aug = true; aug;) {\n      aug\
    \ = false;\n      std::vector<edge_t *> last(size());\n      Dijkstra(last);\n\
    \      std::vector<bool> shut(size());\n      for (size_t dst{}; dst != size();\
    \ ++dst) {\n        if (supp[dst] < static_cast<cap_t>(0) and last[dst]) {\n \
    \         cap_t resid{-supp[dst]};\n          size_t src{dst}, block{nil};\n \
    \         while (last[src] && !shut[src]) {\n            if (!(resid < last[src]->cap))\
    \ resid = last[block = src]->cap;\n            src = last[src]->src;\n       \
    \   }\n          if (shut[src])\n            block = src;\n          else {\n\
    \            if (!(resid < supp[src])) {\n              resid = supp[src];\n \
    \             block = src;\n            }\n            for (edge_t *e{last[dst]};\
    \ e; e = last[e->src]) {\n              e->cap -= resid;\n              e->rev->cap\
    \ += resid;\n            }\n            supp[src] -= resid;\n            supp[dst]\
    \ += resid;\n            min_cost += ptnl[dst] * resid;\n            aug = true;\n\
    \          }\n          if (~block) {\n            for (size_t node{dst};; node\
    \ = last[node]->src) {\n              shut[node] = true;\n              if (node\
    \ == block) break;\n            }\n          }\n        }\n      }\n    }\n  \
    \  return std::none_of(begin(supp), end(supp),\n                        [](const\
    \ cap_t &s) { return s < 0 || 0 < s; });\n  }\n\n  cost_t optimal() {\n    assert(flow());\n\
    \    return min_cost;\n  }\n};  // class min_cost_flow\n#line 2 \"utils/io/casefmt.hpp\"\
    \n\n/*\n * @file castfmt\n * @brief Case Output Format\n */\n\n#line 2 \"config.hpp\"\
    \n\n/*\n * @file config.hpp\n * @brief Configuration\n */\n\n#include <chrono>\n\
    #include <iomanip>\n#include <iostream>\n\nnamespace config {\n\nconst auto start_time{std::chrono::system_clock::now()};\n\
    \n/*\n * @fn elapsed\n * @return elapsed time of the program\n */\nint64_t elapsed()\
    \ {\n  using namespace std::chrono;\n  const auto end_time{system_clock::now()};\n\
    \  return duration_cast<milliseconds>(end_time - start_time).count();\n}\n\n/*\n\
    \ * @fn setup\n * @brief setup I/O before main process.\n */\n__attribute__((constructor))\
    \ void setup() {\n  using namespace std;\n  ios::sync_with_stdio(false);\n  cin.tie(nullptr);\n\
    \  cout << fixed << setprecision(15);\n\n#ifdef _buffer_check\n  atexit([] {\n\
    \    char bufc;\n    if (cin >> bufc)\n      cerr << \"\\n\\033[43m\\033[30mwarning:\
    \ buffer not empty.\\033[0m\\n\\n\";\n  });\n#endif\n}\n\nunsigned cases(), caseid\
    \ = 1;  // current case number, 1-indexed\n\n/*\n * @fn loop\n * @brief iterate\
    \ cases.\n * @param main called once per case\n */\ntemplate <class F> void loop(F\
    \ main) {\n  for (const unsigned total = cases(); caseid <= total; ++caseid) {\n\
    \    try {\n      main();\n    } catch (std::nullptr_t) {\n    }\n  }\n}\n\n}\
    \  // namespace config\n#line 9 \"utils/io/casefmt.hpp\"\n\nnamespace workspace\
    \ {\n\n/*\n * @brief printf(\"Case #%u: \", config::caseid)\n * @param os reference\
    \ to ostream\n * @return os\n */\nstd::ostream& casefmt(std::ostream& os) {\n\
    \  return os << \"Case #\" << config::caseid << \": \";\n}\n\n}  // namespace\
    \ workspace\n#line 3 \"utils/io/read.hpp\"\nnamespace workspace {\n// read with\
    \ std::cin.\ntemplate <class T = void>\nstruct read\n{\n    typename std::remove_const<T>::type\
    \ value;\n    template <class... types>\n    read(types... args) : value(args...)\
    \ { std::cin >> value; }\n    operator T() const { return value; }\n};\ntemplate\
    \ <>\nstruct read<void>\n{\n    template <class T>\n    operator T() const { T\
    \ value; std::cin >> value; return value; }\n};\n} // namespace workspace\n#line\
    \ 3 \"utils/io/stream.hpp\"\n#include <tuple>\n\n#line 2 \"utils/sfinae.hpp\"\n\
    #include <cstdint>\n#include <iterator>\n#include <type_traits>\n\ntemplate <class\
    \ type, template <class> class trait>\nusing enable_if_trait_type = typename std::enable_if<trait<type>::value>::type;\n\
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
    \ < sizeof(T))>::type> {\n  using type = __uint128_t;\n};\n#line 6 \"utils/io/stream.hpp\"\
    \n\nnamespace std {\ntemplate <class T, class U> istream &operator>>(istream &is,\
    \ pair<T, U> &p) {\n  return is >> p.first >> p.second;\n}\ntemplate <class T,\
    \ class U>\nostream &operator<<(ostream &os, const pair<T, U> &p) {\n  return\
    \ os << p.first << ' ' << p.second;\n}\ntemplate <class tuple_t, size_t index>\
    \ struct tuple_is {\n  static istream &apply(istream &is, tuple_t &t) {\n    tuple_is<tuple_t,\
    \ index - 1>::apply(is, t);\n    return is >> get<index>(t);\n  }\n};\ntemplate\
    \ <class tuple_t> struct tuple_is<tuple_t, SIZE_MAX> {\n  static istream &apply(istream\
    \ &is, tuple_t &t) { return is; }\n};\ntemplate <class... T> istream &operator>>(istream\
    \ &is, tuple<T...> &t) {\n  return tuple_is<tuple<T...>, tuple_size<tuple<T...>>::value\
    \ - 1>::apply(is,\n                                                          \
    \                t);\n}\ntemplate <class tuple_t, size_t index> struct tuple_os\
    \ {\n  static ostream &apply(ostream &os, const tuple_t &t) {\n    tuple_os<tuple_t,\
    \ index - 1>::apply(os, t);\n    return os << ' ' << get<index>(t);\n  }\n};\n\
    template <class tuple_t> struct tuple_os<tuple_t, 0> {\n  static ostream &apply(ostream\
    \ &os, const tuple_t &t) {\n    return os << get<0>(t);\n  }\n};\ntemplate <class\
    \ tuple_t> struct tuple_os<tuple_t, SIZE_MAX> {\n  static ostream &apply(ostream\
    \ &os, const tuple_t &t) { return os; }\n};\ntemplate <class... T> ostream &operator<<(ostream\
    \ &os, const tuple<T...> &t) {\n  return tuple_os<tuple<T...>, tuple_size<tuple<T...>>::value\
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
    \ // namespace std\n#line 5 \"test/aizu-online-judge/aors_score.test.cpp\"\nusing\
    \ namespace workspace;\n\nint main() {\n  const int n = read<int>(), m = read<int>(),\
    \ k = read<int>();\n  const int total = n + m + 3;\n  const int dst = total -\
    \ 1;\n  const int dst2 = total - 2;\n  const int dst3 = total - 3;\n  min_cost_flow<int,\
    \ int> mcf(total);\n  mcf.supply(dst, -n);\n  mcf.add_edge(dst2, dst, n, 0);\n\
    \  mcf.add_edge(dst3, dst, n - k, 0);\n  for (int i = 0; i < n; ++i) {\n    mcf.supply(i,\
    \ 1);\n    mcf.add_edge(i, dst2, 1, -read<int>());\n  }\n  for (int j = 0; j <\
    \ m; j++) {\n    for (int i = 0; i < n; i++) {\n      mcf.add_edge(i, j + n, 1,\
    \ -read<int>());\n    }\n  }\n  for (int j = 0; j < m; j++) {\n    mcf.add_edge(j\
    \ + n, dst3, read<int>(), 0);\n  }\n  std::cout << -mcf.optimal() << \"\\n\";\n\
    }\n"
  code: "#define PROBLEM \\\n  \"https://onlinejudge.u-aizu.ac.jp/challenges/sources/VPC/RUPC/2815?year=2017\"\
    \n#include \"graph/directed/flow/min_cost_flow.hpp\"\n#include \"utils/io.hpp\"\
    \nusing namespace workspace;\n\nint main() {\n  const int n = read<int>(), m =\
    \ read<int>(), k = read<int>();\n  const int total = n + m + 3;\n  const int dst\
    \ = total - 1;\n  const int dst2 = total - 2;\n  const int dst3 = total - 3;\n\
    \  min_cost_flow<int, int> mcf(total);\n  mcf.supply(dst, -n);\n  mcf.add_edge(dst2,\
    \ dst, n, 0);\n  mcf.add_edge(dst3, dst, n - k, 0);\n  for (int i = 0; i < n;\
    \ ++i) {\n    mcf.supply(i, 1);\n    mcf.add_edge(i, dst2, 1, -read<int>());\n\
    \  }\n  for (int j = 0; j < m; j++) {\n    for (int i = 0; i < n; i++) {\n   \
    \   mcf.add_edge(i, j + n, 1, -read<int>());\n    }\n  }\n  for (int j = 0; j\
    \ < m; j++) {\n    mcf.add_edge(j + n, dst3, read<int>(), 0);\n  }\n  std::cout\
    \ << -mcf.optimal() << \"\\n\";\n}\n"
  dependsOn:
  - graph/directed/flow/min_cost_flow.hpp
  - graph/directed/flow/base.hpp
  - utils/io.hpp
  - utils/io/casefmt.hpp
  - config.hpp
  - utils/io/read.hpp
  - utils/io/stream.hpp
  - utils/sfinae.hpp
  isVerificationFile: true
  path: test/aizu-online-judge/aors_score.test.cpp
  requiredBy: []
  timestamp: '2020-11-14 01:43:56+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aizu-online-judge/aors_score.test.cpp
layout: document
redirect_from:
- /verify/test/aizu-online-judge/aors_score.test.cpp
- /verify/test/aizu-online-judge/aors_score.test.cpp.html
title: test/aizu-online-judge/aors_score.test.cpp
---
