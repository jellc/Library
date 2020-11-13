---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: config.hpp
    title: Configuration
  - icon: ':heavy_check_mark:'
    path: utils/binary_search.hpp
    title: Binary Search
  - icon: ':warning:'
    path: utils/casefmt.hpp
    title: Case Output Format
  - icon: ':warning:'
    path: utils/chval.hpp
    title: Change Less/Greater
  - icon: ':heavy_check_mark:'
    path: utils/coordinate_compression.hpp
    title: utils/coordinate_compression.hpp
  - icon: ':warning:'
    path: utils/ejection.hpp
    title: Ejection
  - icon: ':warning:'
    path: utils/fixed_point.hpp
    title: Fixed Point Combinator
  - icon: ':heavy_check_mark:'
    path: utils/hash.hpp
    title: utils/hash.hpp
  - icon: ':warning:'
    path: utils/make_vector.hpp
    title: Multi-dimensional Vector
  - icon: ':heavy_check_mark:'
    path: utils/random_number_generator.hpp
    title: utils/random_number_generator.hpp
  - icon: ':heavy_check_mark:'
    path: utils/read.hpp
    title: utils/read.hpp
  - icon: ':warning:'
    path: utils/round_div.hpp
    title: Round Integer Division
  - icon: ':heavy_check_mark:'
    path: utils/sfinae.hpp
    title: utils/sfinae.hpp
  - icon: ':heavy_check_mark:'
    path: utils/stream.hpp
    title: utils/stream.hpp
  - icon: ':warning:'
    path: utils/trinary_search.hpp
    title: utils/trinary_search.hpp
  - icon: ':warning:'
    path: utils/wrapper.hpp
    title: utils/wrapper.hpp
  _extendedRequiredBy:
  - icon: ':warning:'
    path: template.cpp
    title: Template
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"utils.hpp\"\n\n/*\n * @file utils.hpp\n */\n\n#line 2 \"\
    utils/binary_search.hpp\"\n\n/*\n * @file binary_search.hpp\n * @brief Binary\
    \ Search\n */\n\n#if __cplusplus >= 201703L\n\n#include <cassert>\n#include <cmath>\n\
    #include <vector>\n\nnamespace workspace {\n\n/*\n * @fn binary_search\n * @brief\
    \ binary search on a discrete range.\n * @param ok pred(ok) is true\n * @param\
    \ ng pred(ng) is false\n * @param pred the predicate\n * @return the closest point\
    \ to (ng) where pred is true\n */\ntemplate <class iter_type, class pred_type>\n\
    std::enable_if_t<\n    std::is_convertible_v<std::invoke_result_t<pred_type, iter_type>,\
    \ bool>,\n    iter_type>\nbinary_search(iter_type ok, iter_type ng, pred_type\
    \ pred) {\n  assert(ok != ng);\n  std::make_signed_t<decltype(ng - ok)> dist(ng\
    \ - ok);\n  while (1 < dist || dist < -1) {\n    iter_type mid(ok + dist / 2);\n\
    \    if (pred(mid))\n      ok = mid, dist -= dist / 2;\n    else\n      ng = mid,\
    \ dist /= 2;\n  }\n  return ok;\n}\n\n/*\n * @fn parallel_binary_search\n * @brief\
    \ parallel binary search on discrete ranges.\n * @param ends a vector of pairs;\
    \ pred(first) is true, pred(second) is false\n * @param pred the predicate\n *\
    \ @return the closest points to (second) where pred is true\n */\ntemplate <class\
    \ iter_type, class pred_type>\nstd::enable_if_t<std::is_convertible_v<\n     \
    \                std::invoke_result_t<pred_type, std::vector<iter_type>>,\n  \
    \                   std::vector<bool>>,\n                 std::vector<iter_type>>\n\
    parallel_binary_search(std::vector<std::pair<iter_type, iter_type>> ends,\n  \
    \                     pred_type pred) {\n  std::vector<iter_type> mids(ends.size());\n\
    \  for (;;) {\n    bool all_found = true;\n    for (size_t i{}; i != ends.size();\
    \ ++i) {\n      auto [ok, ng] = ends[i];\n      iter_type mid(ok + (ng - ok) /\
    \ 2);\n      if (mids[i] != mid) {\n        all_found = false;\n        mids[i]\
    \ = mid;\n      }\n    }\n    if (all_found) break;\n    auto res = pred(mids);\n\
    \    for (size_t i{}; i != ends.size(); ++i) {\n      (res[i] ? ends[i].first\
    \ : ends[i].second) = mids[i];\n    }\n  }\n  return mids;\n}\n\n/*\n * @fn binary_search\n\
    \ * @brief binary search on the real number line.\n * @param ok pred(ok) is true\n\
    \ * @param ng pred(ng) is false\n * @param eps the error tolerance\n * @param\
    \ pred the predicate\n * @return the boundary point\n */\ntemplate <class real_type,\
    \ class pred_type>\nstd::enable_if_t<\n    std::is_convertible_v<std::invoke_result_t<pred_type,\
    \ real_type>, bool>,\n    real_type>\nbinary_search(real_type ok, real_type ng,\
    \ const real_type eps, pred_type pred) {\n  assert(ok != ng);\n  for (auto loops\
    \ = 0; loops != std::numeric_limits<real_type>::digits &&\n                  \
    \     (ok + eps < ng || ng + eps < ok);\n       ++loops) {\n    real_type mid{(ok\
    \ + ng) / 2};\n    (pred(mid) ? ok : ng) = mid;\n  }\n  return ok;\n}\n\n/*\n\
    \ * @fn parallel_binary_search\n * @brief parallel binary search on the real number\
    \ line.\n * @param ends a vector of pairs; pred(first) is true, pred(second) is\
    \ false\n * @param eps the error tolerance\n * @param pred the predicate\n * @return\
    \ the boundary points\n */\ntemplate <class real_type, class pred_type>\nstd::enable_if_t<std::is_convertible_v<\n\
    \                     std::invoke_result_t<pred_type, std::vector<real_type>>,\n\
    \                     std::vector<bool>>,\n                 std::vector<real_type>>\n\
    parallel_binary_search(std::vector<std::pair<real_type, real_type>> ends,\n  \
    \                     const real_type eps, pred_type pred) {\n  std::vector<real_type>\
    \ mids(ends.size());\n  for (auto loops = 0; loops != std::numeric_limits<real_type>::digits;\n\
    \       ++loops) {\n    bool all_found = true;\n    for (size_t i{}; i != ends.size();\
    \ ++i) {\n      auto [ok, ng] = ends[i];\n      if (ok + eps < ng || ng + eps\
    \ < ok) {\n        all_found = false;\n        mids[i] = (ok + ng) / 2;\n    \
    \  }\n    }\n    if (all_found) break;\n    auto res = pred(mids);\n    for (size_t\
    \ i{}; i != ends.size(); ++i) {\n      (res[i] ? ends[i].first : ends[i].second)\
    \ = mids[i];\n    }\n  }\n  return mids;\n}\n\n}  // namespace workspace\n\n#endif\n\
    #line 2 \"utils/casefmt.hpp\"\n\n/*\n * @file castfmt\n * @brief Case Output Format\n\
    \ */\n\n#line 2 \"config.hpp\"\n\n/*\n * @file config.hpp\n * @brief Configuration\n\
    \ */\n\n#include <chrono>\n#include <iomanip>\n#include <iostream>\n\nnamespace\
    \ config {\n\nconst auto start_time{std::chrono::system_clock::now()};\n\n/*\n\
    \ * @fn elapsed\n * @return elapsed time of the program\n */\nint64_t elapsed()\
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
    \  // namespace config\n#line 9 \"utils/casefmt.hpp\"\n\nnamespace workspace {\n\
    \n/*\n * @brief printf(\"Case #%u: \", config::caseid)\n * @param os reference\
    \ to ostream\n * @return os\n */\nstd::ostream& casefmt(std::ostream& os) {\n\
    \  return os << \"Case #\" << config::caseid << \": \";\n}\n\n}  // namespace\
    \ workspace\n#line 2 \"utils/chval.hpp\"\n\n/*\n * @file chval.hpp\n * @brief\
    \ Change Less/Greater\n */\n\n#include <functional>\n\nnamespace workspace {\n\
    \n/*\n * @fn chle\n * @brief Substitute y for x if comp(y, x) is true.\n * @param\
    \ x Reference\n * @param y Const reference\n * @param comp Compare function\n\
    \ * @return Whether or not x is updated\n */\ntemplate <class Tp, class Comp =\
    \ std::less<Tp>>\nbool chle(Tp &x, const Tp &y, Comp comp = Comp()) {\n  return\
    \ comp(y, x) ? x = y, true : false;\n}\n\n/*\n * @fn chge\n * @brief Substitute\
    \ y for x if comp(x, y) is true.\n * @param x Reference\n * @param y Const reference\n\
    \ * @param comp Compare function\n * @return Whether or not x is updated\n */\n\
    template <class Tp, class Comp = std::less<Tp>>\nbool chge(Tp &x, const Tp &y,\
    \ Comp comp = Comp()) {\n  return comp(x, y) ? x = y, true : false;\n}\n\n}  //\
    \ namespace workspace\n#line 2 \"utils/coordinate_compression.hpp\"\n#include\
    \ <algorithm>\n#include <cassert>\n#include <vector>\n\ntemplate <class T> class\
    \ coordinate_compression {\n  std::vector<T> uniquely;\n  std::vector<size_t>\
    \ compressed;\n\n public:\n  coordinate_compression(const std::vector<T> &raw)\n\
    \      : uniquely(raw), compressed(raw.size()) {\n    std::sort(uniquely.begin(),\
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
    \ }\n  auto rend() { return compressed.rend(); }\n};\n#line 2 \"utils/ejection.hpp\"\
    \n\n/*\n * @file ejection.hpp\n * @brief Ejection\n */\n\n#line 9 \"utils/ejection.hpp\"\
    \n\nnamespace workspace {\n\n/*\n * @brief eject from a try block, throw nullptr\n\
    \ * @param arg output\n */\ntemplate <class Tp> void eject(Tp const &arg) {\n\
    \  std::cout << arg << \"\\n\";\n  throw nullptr;\n}\n\n}  // namespace workspace\n\
    #line 2 \"utils/fixed_point.hpp\"\n\n/*\n * @file fixed_point.hpp\n * @brief Fixed\
    \ Point Combinator\n */\n\n#include <utility>\n\nnamespace workspace {\n\n/*\n\
    \ * @class fixed_point\n * @brief Recursive calling of lambda expression.\n */\n\
    template <class lambda_type> class fixed_point {\n  lambda_type func;\n\n public:\n\
    \  /*\n   * @param func 1st arg callable with the rest of args, and the return\
    \ type\n   * specified.\n   */\n  fixed_point(lambda_type &&func) : func(std::move(func))\
    \ {}\n\n  /*\n   * @brief Recursively apply *this to 1st arg of func.\n   * @param\
    \ args Arguments of the recursive method.\n   */\n  template <class... Args> auto\
    \ operator()(Args &&... args) const {\n    return func(*this, std::forward<Args>(args)...);\n\
    \  }\n};\n\n}  // namespace workspace\n#line 2 \"utils/hash.hpp\"\n#include <ext/pb_ds/assoc_container.hpp>\n\
    #line 4 \"utils/hash.hpp\"\n#include <random>\n#include <unordered_set>\n\n#line\
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
    };\n#line 8 \"utils/hash.hpp\"\nnamespace workspace {\ntemplate <class T, class\
    \ = void> struct hash : std::hash<T> {};\n#if __cplusplus >= 201703L\ntemplate\
    \ <class Unique_bits_type>\nstruct hash<Unique_bits_type,\n            enable_if_trait_type<Unique_bits_type,\n\
    \                                 std::has_unique_object_representations>> {\n\
    \  size_t operator()(uint64_t x) const {\n    static const uint64_t m = std::random_device{}();\n\
    \    x ^= x >> 23;\n    x ^= m;\n    x ^= x >> 47;\n    return x - (x >> 32);\n\
    \  }\n};\n#endif\ntemplate <class Key> size_t hash_combine(const size_t &seed,\
    \ const Key &key) {\n  return seed ^\n         (hash<Key>()(key) + 0x9e3779b9\
    \ /* + (seed << 6) + (seed >> 2) */);\n}\ntemplate <class T1, class T2> struct\
    \ hash<std::pair<T1, T2>> {\n  size_t operator()(const std::pair<T1, T2> &pair)\
    \ const {\n    return hash_combine(hash<T1>()(pair.first), pair.second);\n  }\n\
    };\ntemplate <class... T> class hash<std::tuple<T...>> {\n  template <class Tuple,\
    \ size_t index = std::tuple_size<Tuple>::value - 1>\n  struct tuple_hash {\n \
    \   static uint64_t apply(const Tuple &t) {\n      return hash_combine(tuple_hash<Tuple,\
    \ index - 1>::apply(t),\n                          std::get<index>(t));\n    }\n\
    \  };\n  template <class Tuple> struct tuple_hash<Tuple, size_t(-1)> {\n    static\
    \ uint64_t apply(const Tuple &t) { return 0; }\n  };\n\n public:\n  uint64_t operator()(const\
    \ std::tuple<T...> &t) const {\n    return tuple_hash<std::tuple<T...>>::apply(t);\n\
    \  }\n};\ntemplate <class hash_table> struct hash_table_wrapper : hash_table {\n\
    \  using key_type = typename hash_table::key_type;\n  size_t count(const key_type\
    \ &key) const {\n    return hash_table::find(key) != hash_table::end();\n  }\n\
    \  template <class... Args> auto emplace(Args &&... args) {\n    return hash_table::insert(typename\
    \ hash_table::value_type(args...));\n  }\n};\ntemplate <class Key, class Mapped\
    \ = __gnu_pbds::null_type>\nusing cc_hash_table =\n    hash_table_wrapper<__gnu_pbds::cc_hash_table<Key,\
    \ Mapped, hash<Key>>>;\ntemplate <class Key, class Mapped = __gnu_pbds::null_type>\n\
    using gp_hash_table =\n    hash_table_wrapper<__gnu_pbds::gp_hash_table<Key, Mapped,\
    \ hash<Key>>>;\ntemplate <class Key, class Mapped>\nusing unordered_map = std::unordered_map<Key,\
    \ Mapped, hash<Key>>;\ntemplate <class Key> using unordered_set = std::unordered_set<Key,\
    \ hash<Key>>;\n}  // namespace workspace\n#line 2 \"utils/make_vector.hpp\"\n\n\
    /*\n * @file make_vector.hpp\n * @brief Multi-dimensional Vector\n */\n\n#if __cplusplus\
    \ >= 201703L\n\n#include <tuple>\n#line 12 \"utils/make_vector.hpp\"\n\nnamespace\
    \ workspace {\n\n/*\n * @brief Make a multi-dimensional vector.\n * @tparam Tp\
    \ type of the elements\n * @tparam N dimension\n * @tparam S integer type\n *\
    \ @param sizes The size of each dimension\n * @param init The initial value\n\
    \ */\ntemplate <typename Tp, size_t N, typename S>\nconstexpr auto make_vector(S*\
    \ sizes, Tp const& init = Tp()) {\n  static_assert(std::is_convertible_v<S, size_t>);\n\
    \  if constexpr (N)\n    return std::vector(*sizes,\n                       make_vector<Tp,\
    \ N - 1, S>(std::next(sizes), init));\n  else\n    return init;\n}\n\n/*\n * @brief\
    \ Make a multi-dimensional vector.\n * @param sizes The size of each dimension\n\
    \ * @param init The initial value\n */\ntemplate <typename Tp, size_t N, typename\
    \ S>\nconstexpr auto make_vector(const S (&sizes)[N], Tp const& init = Tp()) {\n\
    \  return make_vector<Tp, N, S>((S*)sizes, init);\n}\n\n/*\n * @brief Make a multi-dimensional\
    \ vector.\n * @param sizes The size of each dimension\n * @param init The initial\
    \ value\n */\ntemplate <typename Tp, size_t N, typename S, size_t I = 0>\nconstexpr\
    \ auto make_vector(std::array<S, N> const& sizes,\n                          \
    \ Tp const& init = Tp()) {\n  static_assert(std::is_convertible_v<S, size_t>);\n\
    \  if constexpr (I == N)\n    return init;\n  else\n    return std::vector(sizes[I],\
    \ make_vector<Tp, N, S, I + 1>(sizes, init));\n}\n\n/*\n * @brief Make a multi-dimensional\
    \ vector.\n * @param sizes The size of each dimension\n * @param init The initial\
    \ value\n */\ntemplate <typename Tp, size_t N = SIZE_MAX, size_t I = 0, class...\
    \ Args>\nconstexpr auto make_vector(std::tuple<Args...> const& sizes,\n      \
    \                     Tp const& init = Tp()) {\n  using tuple_type = std::tuple<Args...>;\n\
    \  if constexpr (I == std::tuple_size_v<tuple_type> || I == N)\n    return init;\n\
    \  else {\n    static_assert(\n        std::is_convertible_v<std::tuple_element_t<I,\
    \ tuple_type>, size_t>);\n    return std::vector(std::get<I>(sizes),\n       \
    \                make_vector<Tp, N, I + 1>(sizes, init));\n  }\n}\n\n/*\n * @brief\
    \ Make a multi-dimensional vector.\n * @param sizes The size of each dimension\n\
    \ * @param init The initial value\n */\ntemplate <typename Tp, class Fst, class\
    \ Snd>\nconstexpr auto make_vector(std::pair<Fst, Snd> const& sizes,\n       \
    \                    Tp const& init = Tp()) {\n  static_assert(std::is_convertible_v<Fst,\
    \ size_t>);\n  static_assert(std::is_convertible_v<Snd, size_t>);\n  return make_vector({(size_t)sizes.first,\
    \ (size_t)sizes.second}, init);\n}\n\n}  // namespace workspace\n\n#endif\n#line\
    \ 3 \"utils/random_number_generator.hpp\"\ntemplate <typename num_type> class\
    \ random_number_generator {\n  typename std::conditional<std::is_integral<num_type>::value,\n\
    \                            std::uniform_int_distribution<num_type>,\n      \
    \                      std::uniform_real_distribution<num_type>>::type\n     \
    \ unif;\n\n  std::mt19937 engine;\n\n public:\n  random_number_generator(num_type\
    \ min = std::numeric_limits<num_type>::min(),\n                          num_type\
    \ max = std::numeric_limits<num_type>::max())\n      : unif(min, max), engine(std::random_device{}())\
    \ {}\n\n  num_type min() const { return unif.min(); }\n\n  num_type max() const\
    \ { return unif.max(); }\n\n  // generate a random number in [min(), max()].\n\
    \  num_type operator()() { return unif(engine); }\n};\n#line 3 \"utils/read.hpp\"\
    \nnamespace workspace {\n// read with std::cin.\ntemplate <class T = void>\nstruct\
    \ read\n{\n    typename std::remove_const<T>::type value;\n    template <class...\
    \ types>\n    read(types... args) : value(args...) { std::cin >> value; }\n  \
    \  operator T() const { return value; }\n};\ntemplate <>\nstruct read<void>\n\
    {\n    template <class T>\n    operator T() const { T value; std::cin >> value;\
    \ return value; }\n};\n} // namespace workspace\n#line 2 \"utils/round_div.hpp\"\
    \n\n/*\n * @file round_div.hpp\n * @brief Round Integer Division\n */\n\n#line\
    \ 9 \"utils/round_div.hpp\"\n\n#line 11 \"utils/round_div.hpp\"\n\nnamespace workspace\
    \ {\n\n/*\n * @fn floor_div\n * @brief floor of fraction.\n * @param x the numerator\n\
    \ * @param y the denominator\n * @return maximum integer z s.t. z <= x / y\n *\
    \ @note y must be nonzero.\n */\ntemplate <typename T1, typename T2>\nconstexpr\
    \ typename std::enable_if<(is_integral_ext<T1>::value &&\n                   \
    \                is_integral_ext<T2>::value),\n                              \
    \    typename std::common_type<T1, T2>::type>::type\nfloor_div(T1 x, T2 y) {\n\
    \  assert(y != 0);\n  if (y < 0) x = -x, y = -y;\n  return x < 0 ? (x - y + 1)\
    \ / y : x / y;\n}\n\n/*\n * @fn ceil_div\n * @brief ceil of fraction.\n * @param\
    \ x the numerator\n * @param y the denominator\n * @return minimum integer z s.t.\
    \ z >= x / y\n * @note y must be nonzero.\n */\ntemplate <typename T1, typename\
    \ T2>\nconstexpr typename std::enable_if<(is_integral_ext<T1>::value &&\n    \
    \                               is_integral_ext<T2>::value),\n               \
    \                   typename std::common_type<T1, T2>::type>::type\nceil_div(T1\
    \ x, T2 y) {\n  assert(y != 0);\n  if (y < 0) x = -x, y = -y;\n  return x < 0\
    \ ? x / y : (x + y - 1) / y;\n}\n\n}  // namespace workspace\n#line 3 \"utils/stream.hpp\"\
    \n#include <tuple>\n\n#line 6 \"utils/stream.hpp\"\nnamespace std {\ntemplate\
    \ <class T, class U> istream &operator>>(istream &is, pair<T, U> &p) {\n  return\
    \ is >> p.first >> p.second;\n}\ntemplate <class T, class U>\nostream &operator<<(ostream\
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
    \ // namespace std\n#line 4 \"utils/trinary_search.hpp\"\n// trinary search on\
    \ discrete range.\ntemplate <class iter_type, class comp_type>\niter_type trinary(iter_type\
    \ first, iter_type last, comp_type comp)\n{\n    assert(first < last);\n    intmax_t\
    \ dist(last - first);\n    while(dist > 2)\n    {\n        iter_type left(first\
    \ + dist / 3), right(first + dist * 2 / 3);\n        if(comp(left, right)) last\
    \ = right, dist = dist * 2 / 3;\n        else first = left, dist -= dist / 3;\n\
    \    }\n    if(dist > 1 && comp(first + 1, first)) ++first;\n    return first;\n\
    }\n// trinary search on real numbers.\ntemplate <class comp_type>\nlong double\
    \ trinary(long double first, long double last, const long double eps, comp_type\
    \ comp)\n{\n    assert(first < last);\n    while(last - first > eps)\n    {\n\
    \        long double left{(first * 2 + last) / 3}, right{(first + last * 2) /\
    \ 3};\n        if(comp(left, right)) last = right;\n        else first = left;\n\
    \    }\n    return first;\n}\n#line 2 \"utils/wrapper.hpp\"\ntemplate <class Container>\
    \ class reversed {\n  Container &ref, copy;\n\n public:\n  constexpr reversed(Container\
    \ &ref) : ref(ref) {}\n  constexpr reversed(Container &&ref = Container()) : ref(copy),\
    \ copy(ref) {}\n  constexpr auto begin() const { return ref.rbegin(); }\n  constexpr\
    \ auto end() const { return ref.rend(); }\n  constexpr operator Container() const\
    \ { return ref; }\n};\n#line 22 \"utils.hpp\"\n"
  code: "#pragma once\n\n/*\n * @file utils.hpp\n */\n\n#include \"utils/binary_search.hpp\"\
    \n#include \"utils/casefmt.hpp\"\n#include \"utils/chval.hpp\"\n#include \"utils/coordinate_compression.hpp\"\
    \n#include \"utils/ejection.hpp\"\n#include \"utils/fixed_point.hpp\"\n#include\
    \ \"utils/hash.hpp\"\n#include \"utils/make_vector.hpp\"\n#include \"utils/random_number_generator.hpp\"\
    \n#include \"utils/read.hpp\"\n#include \"utils/round_div.hpp\"\n#include \"utils/sfinae.hpp\"\
    \n#include \"utils/stream.hpp\"\n#include \"utils/trinary_search.hpp\"\n#include\
    \ \"utils/wrapper.hpp\"\n"
  dependsOn:
  - utils/binary_search.hpp
  - utils/casefmt.hpp
  - config.hpp
  - utils/chval.hpp
  - utils/coordinate_compression.hpp
  - utils/ejection.hpp
  - utils/fixed_point.hpp
  - utils/hash.hpp
  - utils/sfinae.hpp
  - utils/make_vector.hpp
  - utils/random_number_generator.hpp
  - utils/read.hpp
  - utils/round_div.hpp
  - utils/stream.hpp
  - utils/trinary_search.hpp
  - utils/wrapper.hpp
  isVerificationFile: false
  path: utils.hpp
  requiredBy:
  - template.cpp
  timestamp: '2020-11-14 01:17:16+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utils.hpp
layout: document
redirect_from:
- /library/utils.hpp
- /library/utils.hpp.html
title: utils.hpp
---
