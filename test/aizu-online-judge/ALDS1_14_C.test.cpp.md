---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/opt/binary_search.hpp
    title: Binary Search
  - icon: ':heavy_check_mark:'
    path: src/string/rolling_hash.hpp
    title: Rolling Hash
  - icon: ':heavy_check_mark:'
    path: src/utils/rand/rng.hpp
    title: Random Number Generator
  - icon: ':heavy_check_mark:'
    path: src/utils/sfinae.hpp
    title: SFINAE
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_C
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_C
  bundledCode: "#line 1 \"test/aizu-online-judge/ALDS1_14_C.test.cpp\"\n#define PROBLEM\
    \ \"https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_C\"\n\n#include <iostream>\n\
    \n#line 2 \"src/string/rolling_hash.hpp\"\n\n/**\n * @file rolling_hash.hpp\n\
    \ * @brief Rolling Hash\n */\n\n#include <algorithm>\n#include <cassert>\n#include\
    \ <vector>\n\n#line 2 \"src/opt/binary_search.hpp\"\n\n/*\n * @file binary_search.hpp\n\
    \ * @brief Binary Search\n */\n\n#line 9 \"src/opt/binary_search.hpp\"\n#include\
    \ <limits>\n#include <tuple>\n#line 12 \"src/opt/binary_search.hpp\"\n\nnamespace\
    \ workspace {\n\n/*\n * @fn binary_search\n * @brief binary search on a discrete\
    \ range.\n * @param ok pred(ok) is true\n * @param ng pred(ng) is false\n * @param\
    \ pred the predicate\n * @return the closest point to (ng) where pred is true\n\
    \ */\ntemplate <class Iter, class Pred>\ntypename std::enable_if<\n    std::is_convertible<decltype(std::declval<Pred>()(std::declval<Iter>())),\n\
    \                        bool>::value,\n    Iter>::type\nbinary_search(Iter ok,\
    \ Iter ng, Pred pred) {\n  assert(ok != ng);\n  typename std::make_signed<decltype(ng\
    \ - ok)>::type dist(ng - ok);\n  while (1 < dist || dist < -1) {\n    const Iter\
    \ mid(ok + dist / 2);\n    if (pred(mid))\n      ok = mid, dist -= dist / 2;\n\
    \    else\n      ng = mid, dist /= 2;\n  }\n  return ok;\n}\n\n/*\n * @fn binary_search\n\
    \ * @brief binary search on the real number line.\n * @param ok pred(ok) is true\n\
    \ * @param ng pred(ng) is false\n * @param eps the error tolerance\n * @param\
    \ pred the predicate\n * @return the boundary point\n */\ntemplate <class Real,\
    \ class Pred>\ntypename std::enable_if<\n    std::is_convertible<decltype(std::declval<Pred>()(std::declval<Real>())),\n\
    \                        bool>::value,\n    Real>::type\nbinary_search(Real ok,\
    \ Real ng, const Real eps, Pred pred) {\n  assert(ok != ng);\n  for (auto loops\
    \ = 0; loops != std::numeric_limits<Real>::digits &&\n                       (ok\
    \ + eps < ng || ng + eps < ok);\n       ++loops) {\n    const Real mid{(ok + ng)\
    \ / 2};\n    (pred(mid) ? ok : ng) = mid;\n  }\n  return ok;\n}\n\n/*\n * @fn\
    \ parallel_binary_search\n * @brief parallel binary search on discrete ranges.\n\
    \ * @param ends a vector of pairs; pred(first) is true, pred(second) is false\n\
    \ * @param pred the predicate\n * @return the closest points to (second) where\
    \ pred is true\n */\ntemplate <class Array,\n          class Iter = typename std::decay<\n\
    \              decltype(std::get<0>(std::declval<Array>()[0]))>::type,\n     \
    \     class Pred>\ntypename std::enable_if<\n    std::is_convertible<\n      \
    \  decltype(std::declval<Pred>()(std::declval<std::vector<Iter>>())[0]),\n   \
    \     bool>::value,\n    std::vector<Iter>>::type\nparallel_binary_search(Array\
    \ ends, Pred pred) {\n  std::vector<Iter> mids(std::size(ends));\n  for (;;) {\n\
    \    bool all_found = true;\n    for (size_t i{}; i != std::size(ends); ++i) {\n\
    \      const Iter &ok = std::get<0>(ends[i]);\n      const Iter &ng = std::get<1>(ends[i]);\n\
    \      const Iter mid(\n          ok + typename std::make_signed<decltype(ng -\
    \ ok)>::type(ng - ok) / 2);\n      if (mids[i] != mid) {\n        all_found =\
    \ false;\n        mids[i] = mid;\n      }\n    }\n    if (all_found) break;\n\
    \    const auto res = pred(mids);\n    for (size_t i{}; i != std::size(ends);\
    \ ++i) {\n      (res[i] ? std::get<0>(ends[i]) : std::get<1>(ends[i])) = mids[i];\n\
    \    }\n  }\n  return mids;\n}\n\n/*\n * @fn parallel_binary_search\n * @brief\
    \ parallel binary search on the real number line.\n * @param ends a vector of\
    \ pairs; pred(first) is true, pred(second) is false\n * @param eps the error tolerance\n\
    \ * @param pred the predicate\n * @return the boundary points\n */\ntemplate <class\
    \ Array,\n          class Real = typename std::decay<\n              decltype(std::get<0>(std::declval<Array>()[0]))>::type,\n\
    \          class Pred>\ntypename std::enable_if<\n    std::is_convertible<\n \
    \       decltype(std::declval<Pred>()(std::declval<std::vector<Real>>())[0]),\n\
    \        bool>::value,\n    std::vector<Real>>::type\nparallel_binary_search(Array\
    \ ends, const Real eps, Pred pred) {\n  std::vector<Real> mids(std::size(ends));\n\
    \  for (auto loops = 0; loops != std::numeric_limits<Real>::digits; ++loops) {\n\
    \    bool all_found = true;\n    for (size_t i{}; i != std::size(ends); ++i) {\n\
    \      const Real ok = std::get<0>(ends[i]);\n      const Real ng = std::get<1>(ends[i]);\n\
    \      if (ok + eps < ng || ng + eps < ok) {\n        all_found = false;\n   \
    \     mids[i] = (ok + ng) / 2;\n      }\n    }\n    if (all_found) break;\n  \
    \  const auto res = pred(mids);\n    for (size_t i{}; i != std::size(ends); ++i)\
    \ {\n      (res[i] ? std::get<0>(ends[i]) : std::get<1>(ends[i])) = mids[i];\n\
    \    }\n  }\n  return mids;\n}\n\n}  // namespace workspace\n#line 2 \"src/utils/rand/rng.hpp\"\
    \n\n/**\n * @file rng.hpp\n * @brief Random Number Generator\n */\n\n#include\
    \ <random>\n\nnamespace workspace {\n\ntemplate <typename _Arithmetic>\nusing\
    \ uniform_distribution = typename std::conditional<\n    std::is_integral<_Arithmetic>::value,\n\
    \    std::uniform_int_distribution<_Arithmetic>,\n    std::uniform_real_distribution<_Arithmetic>>::type;\n\
    \ntemplate <typename _Arithmetic, class _Engine = std::mt19937>\nclass random_number_generator\
    \ : uniform_distribution<_Arithmetic> {\n  using base = uniform_distribution<_Arithmetic>;\n\
    \n  _Engine __engine;\n\n public:\n  random_number_generator(_Arithmetic __min,\
    \ _Arithmetic __max)\n      : base(__min, __max), __engine(std::random_device{}())\
    \ {}\n\n  random_number_generator(_Arithmetic __max = 1)\n      : random_number_generator(0,\
    \ __max) {}\n\n  random_number_generator(typename base::param_type const& __param)\n\
    \      : base(__param), __engine(std::random_device{}()) {}\n\n  decltype(auto)\
    \ operator()() noexcept { return base::operator()(__engine); }\n};\n\n}  // namespace\
    \ workspace\n#line 2 \"src/utils/sfinae.hpp\"\n\n/**\n * @file sfinae.hpp\n *\
    \ @brief SFINAE\n */\n\n#include <cstdint>\n#include <iterator>\n#include <type_traits>\n\
    \n#ifndef __INT128_DEFINED__\n\n#ifdef __SIZEOF_INT128__\n#define __INT128_DEFINED__\
    \ 1\n#else\n#define __INT128_DEFINED__ 0\n#endif\n\n#endif\n\nnamespace std {\n\
    \n#if __INT128_DEFINED__\n\ntemplate <> struct make_signed<__uint128_t> { using\
    \ type = __int128_t; };\ntemplate <> struct make_signed<__int128_t> { using type\
    \ = __int128_t; };\n\ntemplate <> struct make_unsigned<__uint128_t> { using type\
    \ = __uint128_t; };\ntemplate <> struct make_unsigned<__int128_t> { using type\
    \ = __uint128_t; };\n\ntemplate <> struct is_signed<__uint128_t> : std::false_type\
    \ {};\ntemplate <> struct is_signed<__int128_t> : std::true_type {};\n\ntemplate\
    \ <> struct is_unsigned<__uint128_t> : std::true_type {};\ntemplate <> struct\
    \ is_unsigned<__int128_t> : std::false_type {};\n\n#endif\n\n}  // namespace std\n\
    \nnamespace workspace {\n\ntemplate <class Tp, class... Args> struct variadic_front\
    \ { using type = Tp; };\n\ntemplate <class... Args> struct variadic_back;\n\n\
    template <class Tp> struct variadic_back<Tp> { using type = Tp; };\n\ntemplate\
    \ <class Tp, class... Args> struct variadic_back<Tp, Args...> {\n  using type\
    \ = typename variadic_back<Args...>::type;\n};\n\ntemplate <class type, template\
    \ <class> class trait>\nusing enable_if_trait_type = typename std::enable_if<trait<type>::value>::type;\n\
    \n/**\n * @brief Return type of subscripting ( @c [] ) access.\n */\ntemplate\
    \ <class _Tp>\nusing subscripted_type =\n    typename std::decay<decltype(std::declval<_Tp&>()[0])>::type;\n\
    \ntemplate <class Container>\nusing element_type = typename std::decay<decltype(*std::begin(\n\
    \    std::declval<Container&>()))>::type;\n\ntemplate <class _Tp, class = void>\
    \ struct has_begin : std::false_type {};\n\ntemplate <class _Tp>\nstruct has_begin<\n\
    \    _Tp, std::__void_t<decltype(std::begin(std::declval<const _Tp&>()))>>\n \
    \   : std::true_type {\n  using type = decltype(std::begin(std::declval<const\
    \ _Tp&>()));\n};\n\ntemplate <class _Tp, class = void> struct has_size : std::false_type\
    \ {};\n\ntemplate <class _Tp>\nstruct has_size<_Tp, std::__void_t<decltype(std::size(std::declval<_Tp>()))>>\n\
    \    : std::true_type {};\n\ntemplate <class _Tp, class = void> struct has_resize\
    \ : std::false_type {};\n\ntemplate <class _Tp>\nstruct has_resize<_Tp, std::__void_t<decltype(std::declval<_Tp>().resize(\n\
    \                           std::declval<size_t>()))>> : std::true_type {};\n\n\
    template <class _Tp, class = void> struct has_mod : std::false_type {};\n\ntemplate\
    \ <class _Tp>\nstruct has_mod<_Tp, std::__void_t<decltype(_Tp::mod)>> : std::true_type\
    \ {};\n\ntemplate <class _Tp, class = void> struct is_integral_ext : std::false_type\
    \ {};\ntemplate <class _Tp>\nstruct is_integral_ext<\n    _Tp, typename std::enable_if<std::is_integral<_Tp>::value>::type>\n\
    \    : std::true_type {};\n\n#if __INT128_DEFINED__\n\ntemplate <> struct is_integral_ext<__int128_t>\
    \ : std::true_type {};\ntemplate <> struct is_integral_ext<__uint128_t> : std::true_type\
    \ {};\n\n#endif\n\n#if __cplusplus >= 201402\n\ntemplate <class _Tp>\nconstexpr\
    \ static bool is_integral_ext_v = is_integral_ext<_Tp>::value;\n\n#endif\n\ntemplate\
    \ <typename _Tp, typename = void> struct multiplicable_uint {\n  using type =\
    \ uint_least32_t;\n};\ntemplate <typename _Tp>\nstruct multiplicable_uint<\n \
    \   _Tp,\n    typename std::enable_if<(2 < sizeof(_Tp)) &&\n                 \
    \           (!__INT128_DEFINED__ || sizeof(_Tp) <= 4)>::type> {\n  using type\
    \ = uint_least64_t;\n};\n\n#if __INT128_DEFINED__\n\ntemplate <typename _Tp>\n\
    struct multiplicable_uint<_Tp,\n                          typename std::enable_if<(4\
    \ < sizeof(_Tp))>::type> {\n  using type = __uint128_t;\n};\n\n#endif\n\ntemplate\
    \ <typename _Tp> struct multiplicable_int {\n  using type =\n      typename std::make_signed<typename\
    \ multiplicable_uint<_Tp>::type>::type;\n};\n\ntemplate <typename _Tp> struct\
    \ multiplicable {\n  using type = std::conditional_t<\n      is_integral_ext<_Tp>::value,\n\
    \      std::conditional_t<std::is_signed<_Tp>::value,\n                      \
    \   typename multiplicable_int<_Tp>::type,\n                         typename\
    \ multiplicable_uint<_Tp>::type>,\n      _Tp>;\n};\n\ntemplate <class> struct\
    \ first_arg { using type = void; };\n\ntemplate <class _R, class _Tp, class...\
    \ _Args>\nstruct first_arg<_R(_Tp, _Args...)> {\n  using type = _Tp;\n};\n\ntemplate\
    \ <class _R, class _Tp, class... _Args>\nstruct first_arg<_R (*)(_Tp, _Args...)>\
    \ {\n  using type = _Tp;\n};\n\ntemplate <class _G, class _R, class _Tp, class...\
    \ _Args>\nstruct first_arg<_R (_G::*)(_Tp, _Args...)> {\n  using type = _Tp;\n\
    };\n\ntemplate <class _G, class _R, class _Tp, class... _Args>\nstruct first_arg<_R\
    \ (_G::*)(_Tp, _Args...) const> {\n  using type = _Tp;\n};\n\ntemplate <class\
    \ _Tp, class = void> struct parse_compare : first_arg<_Tp> {};\n\ntemplate <class\
    \ _Tp>\nstruct parse_compare<_Tp, std::__void_t<decltype(&_Tp::operator())>>\n\
    \    : first_arg<decltype(&_Tp::operator())> {};\n\ntemplate <class _Container,\
    \ class = void> struct get_dimension {\n  static constexpr size_t value = 0;\n\
    };\n\ntemplate <class _Container>\nstruct get_dimension<_Container,\n        \
    \             std::enable_if_t<has_begin<_Container>::value>> {\n  static constexpr\
    \ size_t value =\n      1 + get_dimension<typename std::iterator_traits<\n   \
    \           typename has_begin<_Container>::type>::value_type>::value;\n};\n\n\
    }  // namespace workspace\n#line 15 \"src/string/rolling_hash.hpp\"\n\nnamespace\
    \ workspace {\n\n/**\n * @struct rolling_hashed\n * @brief hash data of a string.\n\
    \ */\nstruct rolling_hashed {\n  using u64 = uint_least64_t;\n  using u128 = __uint128_t;\n\
    \n  /**\n   * @brief modulus used for hashing.\n   */\n  constexpr static u64\
    \ mod = (1ull << 61) - 1;\n\n  const static u64 base;\n\n  /**\n   * @brief hash\
    \ value.\n   */\n  u64 value = 0;\n\n  /**\n   * @brief length of the string.\n\
    \   */\n  size_t length = 0;\n\n  rolling_hashed() = default;\n\n  /**\n   * @brief\
    \ construct hash data from one character.\n   * @param c a character\n   */\n\
    \  template <class char_type, typename std::enable_if<std::is_convertible<\n \
    \                                char_type, u64>::value>::type * = nullptr>\n\
    \  rolling_hashed(char_type c) : value(u64(c) + 1), length(1) {}\n\n  rolling_hashed(u64\
    \ value, size_t length) : value(value), length(length) {}\n\n  operator std::pair<u64,\
    \ size_t>() const { return {value, length}; }\n\n  operator u64() const { return\
    \ value; }\n\n  /**\n   * @return whether or not (*this) and (rhs) are equal\n\
    \   * @param rhs\n   */\n  bool operator==(const rolling_hashed &rhs) const {\n\
    \    return value == rhs.value && length == rhs.length;\n  }\n\n  /**\n   * @return\
    \ whether or not (*this) and (rhs) are distinct\n   * @param rhs\n   */\n  bool\
    \ operator!=(const rolling_hashed &rhs) const { return !operator==(rhs); }\n\n\
    \  /**\n   * @param rhs the right operand\n   * @return hash data of concatenated\
    \ string\n   */\n  rolling_hashed operator+(const rolling_hashed &rhs) const {\n\
    \    return {plus(value, mult(rhs.value, base_pow(length))),\n            length\
    \ + rhs.length};\n  }\n\n  /**\n   * @param rhs appended to right end\n   * @return\
    \ reference to updated hash data\n   */\n  rolling_hashed operator+=(const rolling_hashed\
    \ &rhs) {\n    return *this = operator+(rhs);\n  }\n\n  /**\n   * @param rhs the\
    \ erased suffix\n   * @return hash data of erased string\n   */\n  rolling_hashed\
    \ operator-(const rolling_hashed &rhs) const {\n    assert(!(length < rhs.length));\n\
    \    return {minus(value, mult(rhs.value, base_pow(length - rhs.length))),\n \
    \           length - rhs.length};\n  }\n\n  /**\n   * @param rhs erased from right\
    \ end\n   * @return reference to updated hash data\n   */\n  rolling_hashed operator-=(const\
    \ rolling_hashed &rhs) {\n    return *this = operator-(rhs);\n  }\n\n  /**\n \
    \  * @fn base_pow\n   * @param exp the exponent\n   * @return base ** pow\n  \
    \ */\n  static u64 base_pow(size_t exp) {\n    static std::vector<u64> pow{1};\n\
    \    while (pow.size() <= exp) {\n      pow.emplace_back(mult(pow.back(), base));\n\
    \    }\n    return pow[exp];\n  }\n\n private:\n  static u64 plus(u64 lhs, u64\
    \ rhs) {\n    return (lhs += rhs) < mod ? lhs : lhs - mod;\n  }\n\n  static u64\
    \ minus(u64 lhs, u64 rhs) {\n    return (lhs -= rhs) < mod ? lhs : lhs + mod;\n\
    \  }\n\n  static u64 mult(u128 lhs, u64 rhs) {\n    lhs *= rhs;\n    lhs = (lhs\
    \ >> 61) + (lhs & mod);\n    return lhs < mod ? lhs : lhs - mod;\n  }\n};\n\n\
    /**\n * @brief base used for hashing\n */\nconst rolling_hashed::u64 rolling_hashed::base\
    \ =\n    random_number_generator<u64>(1 << 30, mod - 1)();\n\n/**\n * @struct\
    \ rolling_hash_table\n * @brief make hash data table of suffix.\n */\ntemplate\
    \ <class str_type> struct rolling_hash_table {\n  constexpr static size_t npos\
    \ = -1;\n\n  rolling_hash_table() = default;\n\n  rolling_hash_table(str_type\
    \ str) {\n    std::reverse(std::begin(str), std::end(str));\n    for (auto &&c\
    \ : str) suffix.emplace_back(rolling_hashed{c} + suffix.back());\n    std::reverse(suffix.begin(),\
    \ suffix.end());\n  }\n\n  template <class Tp, typename = typename std::enable_if<\n\
    \                          std::is_convertible<rolling_hashed, Tp>::value>::type>\n\
    \  operator Tp() const {\n    return substr();\n  }\n\n  operator rolling_hashed()\
    \ const { return substr(); }\n\n  /**\n   * @return length of the string\n   */\n\
    \  size_t size() const { return suffix.size() - 1; }\n\n  /**\n   * @param pos\
    \ start position\n   * @param n length of the substring\n   * @return hash data\
    \ of the substring\n   */\n  rolling_hashed substr(size_t pos = 0, size_t n =\
    \ npos) const {\n    assert(!(size() < pos));\n    return suffix[pos] - suffix[pos\
    \ + std::min(n, size() - pos)];\n  }\n\n  /**\n   * @param rhs\n   * @return length\
    \ of the longest common prefix\n   */\n  size_t lcp(rolling_hash_table const &rhs)\
    \ const {\n    auto n = std::min(size(), rhs.size());\n    return binary_search<size_t>(\n\
    \        0, n + 1, [&](size_t l) { return substr(0, l) == rhs.substr(0, l); });\n\
    \  }\n\n private:\n  std::vector<rolling_hashed> suffix{{}};\n};\n\n}  // namespace\
    \ workspace\n#line 6 \"test/aizu-online-judge/ALDS1_14_C.test.cpp\"\n\nint main()\
    \ {\n  size_t h, w, r, c;\n\n  std::cin >> h >> w;\n  std::string transposed(h\
    \ * w, '?');\n  for (size_t i = 0; i < h; ++i) {\n    for (size_t j = 0; j < w;\
    \ ++j) {\n      std::cin >> transposed[j * h + i];\n    }\n  }\n\n  std::cin >>\
    \ r >> c;\n  std::string oneln(r * c, '?');\n  for (size_t i = 0; i < r; ++i)\
    \ {\n    for (size_t j = c; j--;) {\n      std::cin >> oneln[j * r + i];\n   \
    \ }\n  }\n\n  workspace::rolling_hash_table grid_hash_table(transposed);\n  auto\
    \ pattern_hash = workspace::rolling_hash_table(oneln).substr();\n\n  for (size_t\
    \ i = 0; i + r <= h; ++i) {\n    workspace::rolling_hashed hash;\n    for (size_t\
    \ j = 0; j < w; ++j) {\n      hash = grid_hash_table.substr(h * j + i, r) + hash;\n\
    \      if (j >= c) {\n        hash -= grid_hash_table.substr(h * (j - c) + i,\
    \ r);\n      }\n      if (hash == pattern_hash) std::cout << i << \" \" << j -\
    \ c + 1 << \"\\n\";\n    }\n  }\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_C\"\n\
    \n#include <iostream>\n\n#include \"src/string/rolling_hash.hpp\"\n\nint main()\
    \ {\n  size_t h, w, r, c;\n\n  std::cin >> h >> w;\n  std::string transposed(h\
    \ * w, '?');\n  for (size_t i = 0; i < h; ++i) {\n    for (size_t j = 0; j < w;\
    \ ++j) {\n      std::cin >> transposed[j * h + i];\n    }\n  }\n\n  std::cin >>\
    \ r >> c;\n  std::string oneln(r * c, '?');\n  for (size_t i = 0; i < r; ++i)\
    \ {\n    for (size_t j = c; j--;) {\n      std::cin >> oneln[j * r + i];\n   \
    \ }\n  }\n\n  workspace::rolling_hash_table grid_hash_table(transposed);\n  auto\
    \ pattern_hash = workspace::rolling_hash_table(oneln).substr();\n\n  for (size_t\
    \ i = 0; i + r <= h; ++i) {\n    workspace::rolling_hashed hash;\n    for (size_t\
    \ j = 0; j < w; ++j) {\n      hash = grid_hash_table.substr(h * j + i, r) + hash;\n\
    \      if (j >= c) {\n        hash -= grid_hash_table.substr(h * (j - c) + i,\
    \ r);\n      }\n      if (hash == pattern_hash) std::cout << i << \" \" << j -\
    \ c + 1 << \"\\n\";\n    }\n  }\n}\n"
  dependsOn:
  - src/string/rolling_hash.hpp
  - src/opt/binary_search.hpp
  - src/utils/rand/rng.hpp
  - src/utils/sfinae.hpp
  isVerificationFile: true
  path: test/aizu-online-judge/ALDS1_14_C.test.cpp
  requiredBy: []
  timestamp: '2022-04-06 15:02:09+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aizu-online-judge/ALDS1_14_C.test.cpp
layout: document
redirect_from:
- /verify/test/aizu-online-judge/ALDS1_14_C.test.cpp
- /verify/test/aizu-online-judge/ALDS1_14_C.test.cpp.html
title: test/aizu-online-judge/ALDS1_14_C.test.cpp
---
