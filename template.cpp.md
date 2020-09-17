---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: config.hpp
    title: config.hpp
  - icon: ':warning:'
    path: gcc_builtin.hpp
    title: gcc_builtin.hpp
  - icon: ':warning:'
    path: gcc_option.hpp
    title: gcc_option.hpp
  - icon: ':heavy_check_mark:'
    path: utils/binary_search.hpp
    title: utils/binary_search.hpp
  - icon: ':warning:'
    path: utils/casefmt.hpp
    title: utils/casefmt.hpp
  - icon: ':warning:'
    path: utils/chval.hpp
    title: utils/chval.hpp
  - icon: ':warning:'
    path: utils/fixed_point.hpp
    title: utils/fixed_point.hpp
  - icon: ':heavy_check_mark:'
    path: utils/hash.hpp
    title: utils/hash.hpp
  - icon: ':heavy_check_mark:'
    path: utils/sfinae.hpp
    title: utils/sfinae.hpp
  - icon: ':warning:'
    path: utils/make_vector.hpp
    title: utils/make_vector.hpp
  - icon: ':heavy_check_mark:'
    path: utils/read.hpp
    title: utils/read.hpp
  - icon: ':heavy_check_mark:'
    path: utils/stream.hpp
    title: utils/stream.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 1 \"template.cpp\"\n#include <bits/extc++.h>\n\n#line 5 \"config.hpp\"\
    \nnamespace config {\nconst auto start_time{std::chrono::system_clock::now()};\n\
    int64_t elapsed() {\n  using namespace std::chrono;\n  const auto end_time{system_clock::now()};\n\
    \  return duration_cast<milliseconds>(end_time - start_time).count();\n}\n__attribute__((constructor))\
    \ void setup() {\n  using namespace std;\n  ios::sync_with_stdio(false);\n  cin.tie(nullptr);\n\
    \  cout << fixed << setprecision(15);\n#ifdef _buffer_check\n  atexit([] {\n \
    \   char bufc;\n    if (cin >> bufc)\n      cerr << \"\\n\\033[43m\\033[30mwarning:\
    \ buffer not empty.\\033[0m\\n\\n\";\n  });\n#endif\n}\nunsigned cases(void),\
    \ caseid = 1;\ntemplate <class C> void main() {\n  for (const unsigned total =\
    \ cases(); caseid <= total; ++caseid) C();\n}\n}  // namespace config\n#line 3\
    \ \"gcc_builtin.hpp\"\nnamespace workspace {\nconstexpr int clz32(const uint32_t\
    \ &n) noexcept { return __builtin_clz(n); }\nconstexpr int clz64(const uint64_t\
    \ &n) noexcept{ return __builtin_clzll(n); }\nconstexpr int ctz(const uint64_t\
    \ &n) noexcept { return __builtin_ctzll(n); }\nconstexpr int popcnt(const uint64_t\
    \ &n) noexcept { return __builtin_popcountll(n); }\n} // namespace workspace\n\
    #line 2 \"gcc_option.hpp\"\n#ifdef ONLINE_JUDGE\n    #pragma GCC optimize(\"O3\"\
    )\n    #pragma GCC target(\"avx,avx2\")\n    #pragma GCC optimize(\"unroll-loops\"\
    )\n#endif\n#line 5 \"utils/binary_search.hpp\"\nnamespace workspace {\n// binary\
    \ search on discrete range.\ntemplate <class iter_type, class pred_type>\nstd::enable_if_t<\n\
    \    std::is_convertible_v<std::invoke_result_t<pred_type, iter_type>, bool>,\n\
    \    iter_type>\nbinary_search(iter_type ok, iter_type ng, pred_type pred) {\n\
    \  assert(ok != ng);\n  __int128_t dist(ng - ok);\n  while (dist > 1 || dist <\
    \ -1) {\n    iter_type mid(ok + dist / 2);\n    if (pred(mid))\n      ok = mid,\
    \ dist -= dist / 2;\n    else\n      ng = mid, dist /= 2;\n  }\n  return ok;\n\
    }\n// parallel binary search on discrete range.\ntemplate <class iter_type, class\
    \ pred_type>\nstd::enable_if_t<std::is_convertible_v<\n                     std::invoke_result_t<pred_type,\
    \ std::vector<iter_type>>,\n                     std::vector<bool>>,\n       \
    \          std::vector<iter_type>>\nbinary_search(std::vector<std::pair<iter_type,\
    \ iter_type>> ends,\n              pred_type pred) {\n  std::vector<iter_type>\
    \ mids(ends.size());\n  for (;;) {\n    bool all_found = true;\n    for (size_t\
    \ i{}; i != ends.size(); ++i) {\n      auto [ok, ng] = ends[i];\n      iter_type\
    \ mid(ok + (ng - ok) / 2);\n      if (mids[i] != mid) {\n        all_found = false;\n\
    \        mids[i] = mid;\n      }\n    }\n    if (all_found) break;\n    auto res\
    \ = pred(mids);\n    for (size_t i{}; i != ends.size(); ++i) {\n      (res[i]\
    \ ? ends[i].first : ends[i].second) = mids[i];\n    }\n  }\n  return mids;\n}\n\
    // binary search on real numbers.\ntemplate <class real_type, class pred_type>\n\
    std::enable_if_t<\n    std::is_convertible_v<std::invoke_result_t<pred_type, real_type>,\
    \ bool>,\n    real_type>\nbinary_search(real_type ok, real_type ng, const real_type\
    \ eps, pred_type pred) {\n  assert(ok != ng);\n  while (ok + eps < ng || ng +\
    \ eps < ok) {\n    real_type mid{(ok + ng) / 2};\n    (pred(mid) ? ok : ng) =\
    \ mid;\n  }\n  return ok;\n}\n// parallel binary search on real numbers.\ntemplate\
    \ <class real_type, class pred_type>\nstd::enable_if_t<std::is_convertible_v<\n\
    \                     std::invoke_result_t<pred_type, std::vector<real_type>>,\n\
    \                     std::vector<bool>>,\n                 std::vector<real_type>>\n\
    binary_search(std::vector<std::pair<real_type, real_type>> ends,\n           \
    \   const real_type eps, pred_type pred) {\n  std::vector<real_type> mids(ends.size());\n\
    \  for (;;) {\n    bool all_found = true;\n    for (size_t i{}; i != ends.size();\
    \ ++i) {\n      auto [ok, ng] = ends[i];\n      if (ok + eps < ng || ng + eps\
    \ < ok) {\n        all_found = false;\n        mids[i] = (ok + ng) / 2;\n    \
    \  }\n    }\n    if (all_found) break;\n    auto res = pred(mids);\n    for (size_t\
    \ i{}; i != ends.size(); ++i) {\n      (res[i] ? ends[i].first : ends[i].second)\
    \ = mids[i];\n    }\n  }\n  return mids;\n}\n}  // namespace workspace\n#line\
    \ 3 \"utils/casefmt.hpp\"\nnamespace workspace {\nstd::ostream &casefmt(std::ostream&\
    \ os) { return os << \"Case #\" << config::caseid << \": \"; }\n} // namespace\
    \ workspace\n#line 3 \"utils/chval.hpp\"\nnamespace workspace {\ntemplate <class\
    \ T, class Comp = std::less<T>> bool chle(T &x, const T &y, Comp comp = Comp())\
    \ { return comp(y, x) ? x = y, true : false; }\ntemplate <class T, class Comp\
    \ = std::less<T>> bool chge(T &x, const T &y, Comp comp = Comp()) { return comp(x,\
    \ y) ? x = y, true : false; }\n} // namespace workspace\n#line 3 \"utils/fixed_point.hpp\"\
    \nnamespace workspace {\n// specify the return type of lambda.\ntemplate <class\
    \ lambda_type>\nclass fixed_point\n{\n    lambda_type func;\npublic:\n    fixed_point(lambda_type\
    \ &&f) : func(std::move(f)) {}\n    template <class... Args> auto operator()(Args\
    \ &&... args) const { return func(*this, std::forward<Args>(args)...); }\n};\n\
    } // namespace workspace\n#line 3 \"utils/sfinae.hpp\"\n#include <type_traits>\n\
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
    };\n#line 7 \"utils/hash.hpp\"\nnamespace workspace {\ntemplate <class T, class\
    \ = void>\nstruct hash : std::hash<T> {};\ntemplate <class Unique_bits_type>\n\
    struct hash<Unique_bits_type, enable_if_trait_type<Unique_bits_type, std::has_unique_object_representations>>\n\
    {\n    size_t operator()(uint64_t x) const\n    {\n        static const uint64_t\
    \ m = std::random_device{}();\n        x ^= x >> 23;\n        // x *= 0x2127599bf4325c37ULL;\n\
    \        x ^= m;\n        x ^= x >> 47;\n        return x - (x >> 32);\n    }\n\
    };\ntemplate <class Key>\nsize_t hash_combine(const size_t &seed, const Key &key)\n\
    {\n    return seed ^ (hash<Key>()(key) + 0x9e3779b9 /* + (seed << 6) + (seed >>\
    \ 2) */ );\n}\ntemplate <class T1, class T2>\nstruct hash<std::pair<T1, T2>>\n\
    {\n    size_t operator()(const std::pair<T1, T2> &pair) const\n    {\n       \
    \ return hash_combine(hash<T1>()(pair.first), pair.second);\n    }\n};\ntemplate\
    \ <class... T>\nclass hash<std::tuple<T...>>\n{\n    template <class Tuple, size_t\
    \ index = std::tuple_size<Tuple>::value - 1> struct tuple_hash { static uint64_t\
    \ apply(const Tuple &t) { return hash_combine(tuple_hash<Tuple, index - 1>::apply(t),\
    \ std::get<index>(t)); } };\n    template <class Tuple> struct tuple_hash<Tuple,\
    \ size_t(-1)> { static uint64_t apply(const Tuple &t) { return 0; } };\npublic:\n\
    \    uint64_t operator()(const std::tuple<T...> &t) const { return tuple_hash<std::tuple<T...>>::apply(t);\
    \ }\n};\ntemplate <class hash_table>\nstruct hash_table_wrapper : hash_table\n\
    {\n    using key_type = typename hash_table::key_type;\n    size_t count(const\
    \ key_type &key) const { return hash_table::find(key) != hash_table::end(); }\n\
    \    template <class... Args> auto emplace(Args&&... args) { return hash_table::insert(typename\
    \ hash_table::value_type(args...)); }\n};\ntemplate <class Key, class Mapped =\
    \ __gnu_pbds::null_type>\nusing cc_hash_table = hash_table_wrapper<__gnu_pbds::cc_hash_table<Key,\
    \ Mapped, hash<Key>>>;\ntemplate <class Key, class Mapped = __gnu_pbds::null_type>\n\
    using gp_hash_table = hash_table_wrapper<__gnu_pbds::gp_hash_table<Key, Mapped,\
    \ hash<Key>>>;\ntemplate <class Key, class Mapped>\nusing unordered_map = std::unordered_map<Key,\
    \ Mapped, hash<Key>>;\ntemplate <class Key>\nusing unordered_set = std::unordered_set<Key,\
    \ hash<Key>>;\n} // namespace workspace\n#line 3 \"utils/make_vector.hpp\"\nnamespace\
    \ workspace {\ntemplate <typename T, size_t N>\nconstexpr auto make_vector(size_t*\
    \ sizes, T const& init = T()) {\n  if constexpr (N)\n    return std::vector(*sizes,\
    \ make_vector<T, N - 1>(std::next(sizes), init));\n  else\n    return init;\n\
    }\ntemplate <typename T, size_t N>\nconstexpr auto make_vector(const size_t (&sizes)[N],\
    \ T const& init = T()) {\n  return make_vector<T, N>((size_t*)sizes, init);\n\
    }\n}  // namespace workspace\n#line 3 \"utils/read.hpp\"\nnamespace workspace\
    \ {\n// read with std::cin.\ntemplate <class T = void>\nstruct read\n{\n    typename\
    \ std::remove_const<T>::type value;\n    template <class... types>\n    read(types...\
    \ args) : value(args...) { std::cin >> value; }\n    operator T() const { return\
    \ value; }\n};\ntemplate <>\nstruct read<void>\n{\n    template <class T>\n  \
    \  operator T() const { T value; std::cin >> value; return value; }\n};\n} //\
    \ namespace workspace\n#line 4 \"utils/stream.hpp\"\n\n#line 6 \"utils/stream.hpp\"\
    \nnamespace std {\ntemplate <class T, class U> istream &operator>>(istream &is,\
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
    \ // namespace std\n#line 14 \"template.cpp\"\nnamespace workspace {\nconstexpr\
    \ char eol = '\\n';\nusing namespace std;\nusing i32 = int_least32_t;\nusing i64\
    \ = int_least64_t;\nusing i128 = __int128_t;\nusing u32 = uint_least32_t;\nusing\
    \ u64 = uint_least64_t;\nusing u128 = __uint128_t;\ntemplate <class T, class Comp\
    \ = std::less<T>>\nusing priority_queue = std::priority_queue<T, std::vector<T>,\
    \ Comp>;\ntemplate <class T> using stack = std::stack<T, std::vector<T>>;\nstruct\
    \ solver;\n}  // namespace workspace\nint main() { config::main<workspace::solver>();\
    \ }\nunsigned config::cases() {\n  // return -1; // not specified\n  // int t;\
    \ std::cin >> t; return t; // given\n  return 1;\n}\n\nstruct workspace::solver\
    \ {\n  solver() {\n    // start here!\n  }\n};\n"
  code: "#include <bits/extc++.h>\n\n#include \"config.hpp\"\n#include \"gcc_builtin.hpp\"\
    \n#include \"gcc_option.hpp\"\n#include \"utils/binary_search.hpp\"\n#include\
    \ \"utils/casefmt.hpp\"\n#include \"utils/chval.hpp\"\n#include \"utils/fixed_point.hpp\"\
    \n#include \"utils/hash.hpp\"\n#include \"utils/make_vector.hpp\"\n#include \"\
    utils/read.hpp\"\n#include \"utils/stream.hpp\"\nnamespace workspace {\nconstexpr\
    \ char eol = '\\n';\nusing namespace std;\nusing i32 = int_least32_t;\nusing i64\
    \ = int_least64_t;\nusing i128 = __int128_t;\nusing u32 = uint_least32_t;\nusing\
    \ u64 = uint_least64_t;\nusing u128 = __uint128_t;\ntemplate <class T, class Comp\
    \ = std::less<T>>\nusing priority_queue = std::priority_queue<T, std::vector<T>,\
    \ Comp>;\ntemplate <class T> using stack = std::stack<T, std::vector<T>>;\nstruct\
    \ solver;\n}  // namespace workspace\nint main() { config::main<workspace::solver>();\
    \ }\nunsigned config::cases() {\n  // return -1; // not specified\n  // int t;\
    \ std::cin >> t; return t; // given\n  return 1;\n}\n\nstruct workspace::solver\
    \ {\n  solver() {\n    // start here!\n  }\n};\n"
  dependsOn:
  - config.hpp
  - gcc_builtin.hpp
  - gcc_option.hpp
  - utils/binary_search.hpp
  - utils/casefmt.hpp
  - utils/chval.hpp
  - utils/fixed_point.hpp
  - utils/hash.hpp
  - utils/sfinae.hpp
  - utils/make_vector.hpp
  - utils/read.hpp
  - utils/stream.hpp
  isVerificationFile: false
  path: template.cpp
  requiredBy: []
  timestamp: '2020-09-17 16:18:47+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: template.cpp
layout: document
redirect_from:
- /library/template.cpp
- /library/template.cpp.html
title: template.cpp
---
