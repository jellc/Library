---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/segment_tree/lazy.hpp
    title: data_structure/segment_tree/lazy.hpp
  - icon: ':heavy_check_mark:'
    path: utils/sfinae.hpp
    title: utils/sfinae.hpp
  - icon: ':heavy_check_mark:'
    path: modulus/modint.hpp
    title: modulus/modint.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/range_affine_range_sum
    links:
    - https://judge.yosupo.jp/problem/range_affine_range_sum
  bundledCode: "#line 1 \"test/library-checker/range_affine_range_sum.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/range_affine_range_sum\"\n#include\
    \ <cstdio>\n#include <vector>\n\n#line 2 \"data_structure/segment_tree/lazy.hpp\"\
    \n#include <cassert>\n#line 4 \"data_structure/segment_tree/lazy.hpp\"\n\n#line\
    \ 2 \"utils/sfinae.hpp\"\n#include <cstdint>\n#include <type_traits>\n\ntemplate\
    \ <class type, template <class> class trait>\nusing enable_if_trait_type = typename\
    \ std::enable_if<trait<type>::value>::type;\n\ntemplate <class Container>\nusing\
    \ element_type = typename std::decay<decltype(\n    *std::begin(std::declval<Container&>()))>::type;\n\
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
    };\n#line 6 \"data_structure/segment_tree/lazy.hpp\"\ntemplate <class Monoid,\
    \ class Endomorphism,\n          template <class...> class Container_tmpl = std::vector>\n\
    class lazy_segment_tree {\n  size_t size_orig, height, size_ext;\n  Container_tmpl<Monoid>\
    \ data;\n  Container_tmpl<Endomorphism> lazy;\n\n  static_assert(std::is_same<Monoid,\
    \ decltype(Monoid{} + Monoid{})>::value,\n                \"\\'Monoid\\' has no\
    \ proper binary operator+.\");\n\n  static_assert(std::is_same<Endomorphism,\n\
    \                             decltype(Endomorphism{} * Endomorphism{})>::value,\n\
    \                \"\\'Endomorphism\\' has no proper binary operator*.\");\n\n\
    \  static_assert(\n      std::is_same<Monoid, decltype(Monoid{} * Endomorphism{})>::value,\n\
    \      \"\\'Endomorphism\\' is not applicable to \\'Monoid\\'.\");\n\n  void pull(const\
    \ size_t &node) {\n    data[node] = data[node << 1] + data[node << 1 | 1];\n \
    \ }\n\n  void apply(const size_t &node, const Endomorphism &endo) {\n    data[node]\
    \ = data[node] * endo;\n    if (node < size_ext) lazy[node] = lazy[node] * endo;\n\
    \  }\n\n  void push(const size_t &node) {\n    if (node >= size_ext) return;\n\
    \    apply(node << 1, lazy[node]);\n    apply(node << 1 | 1, lazy[node]);\n  \
    \  lazy[node] = Endomorphism{};\n  }\n\n  template <class Pred>\n  size_t left_search_subtree(size_t\
    \ node, Pred pred, Monoid mono) {\n    assert(node);\n    while (node < size_ext)\
    \ {\n      push(node);\n      const Monoid &tmp = data[(node <<= 1) | 1] + mono;\n\
    \      if (pred(tmp))\n        mono = tmp;\n      else\n        ++node;\n    }\n\
    \    return ++node -= size_ext;\n  }\n\n  template <class Pred>\n  size_t right_search_subtree(size_t\
    \ node, Pred pred, Monoid mono) {\n    assert(node);\n    while (node < size_ext)\
    \ {\n      push(node);\n      const Monoid &tmp = mono + data[node <<= 1];\n \
    \     if (pred(tmp)) ++node, mono = tmp;\n    }\n    return (node -= size_ext)\
    \ < size_orig ? node : size_orig;\n  }\n\n public:\n  lazy_segment_tree(const\
    \ size_t n = 0)\n      : size_orig{n},\n        height(n > 1 ? 32 - __builtin_clz(n\
    \ - 1) : 0),\n        size_ext{1u << height},\n        data(size_ext << 1),\n\
    \        lazy(size_ext) {}\n\n  lazy_segment_tree(const size_t &n, const Monoid\
    \ &init)\n      : lazy_segment_tree(n) {\n    std::fill(std::next(std::begin(data),\
    \ size_ext), std::end(data), init);\n    for (size_t i{size_ext}; --i;) pull(i);\n\
    \  }\n\n  template <class iter_type, class value_type = typename std::iterator_traits<\n\
    \                                 iter_type>::value_type>\n  lazy_segment_tree(iter_type\
    \ first, iter_type last)\n      : size_orig(std::distance(first, last)),\n   \
    \     height(size_orig > 1 ? 32 - __builtin_clz(size_orig - 1) : 0),\n       \
    \ size_ext{1u << height},\n        data(size_ext << 1),\n        lazy(size_ext)\
    \ {\n    static_assert(std::is_constructible<Monoid, value_type>::value,\n   \
    \               \"Monoid(iter_type::value_type) is not constructible.\");\n  \
    \  for (auto iter{std::next(std::begin(data), size_ext)};\n         iter != std::end(data)\
    \ && first != last; ++iter, ++first)\n      *iter = Monoid(*first);\n    for (size_t\
    \ i{size_ext}; --i;) pull(i);\n  }\n\n  template <class Container, typename =\
    \ typename Container::value_type>\n  lazy_segment_tree(const Container &cont)\n\
    \      : lazy_segment_tree(std::begin(cont), std::end(cont)) {}\n\n  size_t size()\
    \ const { return size_orig; }\n  size_t capacity() const { return size_ext; }\n\
    \n  Monoid operator[](const size_t &index) { return fold(index, index + 1); }\n\
    \n  void update(const size_t &index, const Endomorphism &endo) {\n    update(index,\
    \ index + 1, endo);\n  }\n\n  void update(size_t first, size_t last, const Endomorphism\
    \ &endo) {\n    assert(last <= size_orig);\n    if (first >= last) return;\n \
    \   first += size_ext, last += size_ext - 1;\n    for (size_t i = height; i; --i)\
    \ push(first >> i), push(last >> i);\n    for (size_t l = first, r = last + 1;\
    \ last; l >>= 1, r >>= 1) {\n      if (l < r) {\n        if (l & 1) apply(l++,\
    \ endo);\n        if (r & 1) apply(--r, endo);\n      }\n      if (first >>= 1,\
    \ last >>= 1) {\n        pull(first), pull(last);\n      }\n    }\n  }\n\n  Monoid\
    \ fold() { return fold(0, size_orig); }\n\n  Monoid fold(size_t first, size_t\
    \ last) {\n    assert(last <= size_orig);\n    if (first >= last) return Monoid{};\n\
    \    first += size_ext, last += size_ext - 1;\n    Monoid left_val{}, right_val{};\n\
    \    for (size_t l = first, r = last + 1; last; l >>= 1, r >>= 1) {\n      if\
    \ (l < r) {\n        if (l & 1) left_val = left_val + data[l++];\n        if (r\
    \ & 1) right_val = data[--r] + right_val;\n      }\n      if (first >>= 1, last\
    \ >>= 1) {\n        left_val = left_val * lazy[first];\n        right_val = right_val\
    \ * lazy[last];\n      }\n    }\n    return left_val + right_val;\n  }\n\n  template\
    \ <class Pred> size_t left_search(size_t right, Pred pred) {\n    assert(right\
    \ <= size_orig);\n    right += size_ext - 1;\n    for (size_t i{height}; i; --i)\
    \ push(right >> i);\n    ++right;\n    Monoid mono{};\n    for (size_t left{size_ext};\
    \ left != right; left >>= 1, right >>= 1) {\n      if ((left & 1) != (right &\
    \ 1)) {\n        const Monoid &tmp = data[--right] + mono;\n        if (!pred(tmp))\
    \ return left_search_subtree(right, pred, mono);\n        mono = tmp;\n      }\n\
    \    }\n    return 0;\n  }\n\n  template <class Pred> size_t right_search(size_t\
    \ left, Pred pred) {\n    assert(left <= size_orig);\n    left += size_ext;\n\
    \    for (size_t i{height}; i; --i) push(left >> i);\n    Monoid mono{};\n   \
    \ for (size_t right{size_ext << 1}; left != right; left >>= 1, right >>= 1) {\n\
    \      if ((left & 1) != (right & 1)) {\n        const Monoid &tmp = mono + data[left];\n\
    \        if (!pred(tmp)) return right_search_subtree(left, pred, mono);\n    \
    \    mono = tmp;\n        ++left;\n      }\n    }\n    return size_orig;\n  }\n\
    };  // class lazy_segment_tree\n#line 3 \"modulus/modint.hpp\"\n#include <iostream>\n\
    \n#line 6 \"modulus/modint.hpp\"\n\ntemplate <auto Mod = 0, typename Mod_type\
    \ = decltype(Mod)> struct modint {\n  static_assert(is_integral_ext<decltype(Mod)>::value,\n\
    \                \"Mod must be integral type.\");\n  static_assert(!(Mod < 0),\
    \ \"Mod must be non-negative.\");\n\n  using mod_type = typename std::conditional<\n\
    \      Mod != 0, typename std::add_const<Mod_type>::type, Mod_type>::type;\n \
    \ static mod_type mod;\n\n  using value_type = typename std::decay<mod_type>::type;\n\
    \n  constexpr operator value_type() const noexcept { return value; }\n\n  constexpr\
    \ static modint one() noexcept { return 1; }\n\n  constexpr modint() noexcept\
    \ = default;\n\n  template <class int_type,\n            typename std::enable_if<is_integral_ext<int_type>::value>::type\
    \ * =\n                nullptr>\n  constexpr modint(int_type n) noexcept : value((n\
    \ %= mod) < 0 ? mod + n : n) {}\n\n  constexpr modint(bool n) noexcept : modint(int(n))\
    \ {}\n\n  constexpr modint operator++(int) noexcept {\n    modint t{*this};\n\
    \    return operator+=(1), t;\n  }\n\n  constexpr modint operator--(int) noexcept\
    \ {\n    modint t{*this};\n    return operator-=(1), t;\n  }\n\n  constexpr modint\
    \ &operator++() noexcept { return operator+=(1); }\n\n  constexpr modint &operator--()\
    \ noexcept { return operator-=(1); }\n\n  constexpr modint operator-() const noexcept\
    \ {\n    return value ? mod - value : 0;\n  }\n\n  constexpr modint &operator+=(const\
    \ modint &rhs) noexcept {\n    return (value += rhs.value) < mod ? 0 : value -=\
    \ mod, *this;\n  }\n\n  constexpr modint &operator-=(const modint &rhs) noexcept\
    \ {\n    return (value += mod - rhs.value) < mod ? 0 : value -= mod, *this;\n\
    \  }\n\n  constexpr modint &operator*=(const modint &rhs) noexcept {\n    return\
    \ value = (typename multiplicable_uint<value_type>::type)value *\n           \
    \        rhs.value % mod,\n           *this;\n  }\n\n  constexpr modint &operator/=(const\
    \ modint &rhs) noexcept {\n    return operator*=(rhs.inverse());\n  }\n\n  template\
    \ <class int_type>\n  constexpr\n      typename std::enable_if<is_integral_ext<int_type>::value,\
    \ modint>::type\n      operator+(const int_type &rhs) const noexcept {\n    return\
    \ modint{*this} += rhs;\n  }\n\n  constexpr modint operator+(const modint &rhs)\
    \ const noexcept {\n    return modint{*this} += rhs;\n  }\n\n  template <class\
    \ int_type>\n  constexpr\n      typename std::enable_if<is_integral_ext<int_type>::value,\
    \ modint>::type\n      operator-(const int_type &rhs) const noexcept {\n    return\
    \ modint{*this} -= rhs;\n  }\n\n  constexpr modint operator-(const modint &rhs)\
    \ const noexcept {\n    return modint{*this} -= rhs;\n  }\n\n  template <class\
    \ int_type>\n  constexpr\n      typename std::enable_if<is_integral_ext<int_type>::value,\
    \ modint>::type\n      operator*(const int_type &rhs) const noexcept {\n    return\
    \ modint{*this} *= rhs;\n  }\n\n  constexpr modint operator*(const modint &rhs)\
    \ const noexcept {\n    return modint{*this} *= rhs;\n  }\n\n  template <class\
    \ int_type>\n  constexpr\n      typename std::enable_if<is_integral_ext<int_type>::value,\
    \ modint>::type\n      operator/(const int_type &rhs) const noexcept {\n    return\
    \ modint{*this} /= rhs;\n  }\n\n  constexpr modint operator/(const modint &rhs)\
    \ const noexcept {\n    return modint{*this} /= rhs;\n  }\n\n  template <class\
    \ int_type>\n  constexpr friend\n      typename std::enable_if<is_integral_ext<int_type>::value,\
    \ modint>::type\n      operator+(const int_type &lhs, const modint &rhs) noexcept\
    \ {\n    return modint(lhs) + rhs;\n  }\n\n  template <class int_type>\n  constexpr\
    \ friend\n      typename std::enable_if<is_integral_ext<int_type>::value, modint>::type\n\
    \      operator-(const int_type &lhs, const modint &rhs) noexcept {\n    return\
    \ modint(lhs) - rhs;\n  }\n\n  template <class int_type>\n  constexpr friend\n\
    \      typename std::enable_if<is_integral_ext<int_type>::value, modint>::type\n\
    \      operator*(const int_type &lhs, const modint &rhs) noexcept {\n    return\
    \ modint(lhs) * rhs;\n  }\n\n  template <class int_type>\n  constexpr friend\n\
    \      typename std::enable_if<is_integral_ext<int_type>::value, modint>::type\n\
    \      operator/(const int_type &lhs, const modint &rhs) noexcept {\n    return\
    \ modint(lhs) / rhs;\n  }\n\n  constexpr modint inverse() const noexcept {\n \
    \   assert(value);\n    value_type a{mod}, b{value}, u{}, v{1}, t{};\n    while\
    \ (b)\n      t = a / b, a ^= b ^= (a -= t * b) ^= b, u ^= v ^= (u -= t * v) ^=\
    \ v;\n    return {u};\n  }\n\n  template <class int_type>\n  constexpr\n     \
    \ typename std::enable_if<is_integral_ext<int_type>::value, modint>::type\n  \
    \    power(int_type e) noexcept {\n    if (e < 0) e = e % (mod - 1) + mod - 1;\n\
    \    modint res{1}, p{*this};\n    for (modint p{value}; e; e >>= 1, p *= p) {\n\
    \      if (e & 1) res *= p;\n    }\n    return res;\n  }\n\n  friend std::ostream\
    \ &operator<<(std::ostream &os,\n                                  const modint\
    \ &rhs) noexcept {\n    return os << rhs.value;\n  }\n\n  friend std::istream\
    \ &operator>>(std::istream &is, modint &rhs) noexcept {\n    intmax_t value;\n\
    \    rhs = (is >> value, value);\n    return is;\n  }\n\n protected:\n  value_type\
    \ value = 0;\n};\n\ntemplate <auto Mod, typename Mod_type>\ntypename modint<Mod,\
    \ Mod_type>::mod_type modint<Mod, Mod_type>::mod = Mod;\n\nusing modint_runtime\
    \ = modint<0>;\n#line 7 \"test/library-checker/range_affine_range_sum.test.cpp\"\
    \n\nint main() {\n  using mint = modint<998244353>;\n  struct endo {\n    mint\
    \ a = 1, b;\n    endo operator*(endo rhs) { return {a * rhs.a, b * rhs.a + rhs.b};\
    \ }\n  };\n  struct mono {\n    mint v, c;\n    mono operator+(mono rhs) { return\
    \ {v + rhs.v, c + rhs.c}; }\n    mono operator*(endo rhs) { return {v * rhs.a\
    \ + c * rhs.b, c}; }\n  };\n\n  int n, q;\n  scanf(\"%d%d\", &n, &q);\n  lazy_segment_tree<mono,\
    \ endo> seg;\n  {\n    std::vector<mono> a(n);\n    for (auto &[v, c] : a) {\n\
    \      int _v;\n      scanf(\"%d\", &_v);\n      v = _v;\n      c = 1;\n    }\n\
    \    seg = a;\n  }\n  for (int t, l, r, a, b; q--;) {\n    scanf(\"%d%d%d\", &t,\
    \ &l, &r);\n    if (t) {\n      printf(\"%d\\n\", seg.fold(l, r).v);\n    } else\
    \ {\n      scanf(\"%d%d\", &a, &b);\n      seg.update(l, r, {a, b});\n    }\n\
    \  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_affine_range_sum\"\
    \n#include <cstdio>\n#include <vector>\n\n#include \"data_structure/segment_tree/lazy.hpp\"\
    \n#include \"modulus/modint.hpp\"\n\nint main() {\n  using mint = modint<998244353>;\n\
    \  struct endo {\n    mint a = 1, b;\n    endo operator*(endo rhs) { return {a\
    \ * rhs.a, b * rhs.a + rhs.b}; }\n  };\n  struct mono {\n    mint v, c;\n    mono\
    \ operator+(mono rhs) { return {v + rhs.v, c + rhs.c}; }\n    mono operator*(endo\
    \ rhs) { return {v * rhs.a + c * rhs.b, c}; }\n  };\n\n  int n, q;\n  scanf(\"\
    %d%d\", &n, &q);\n  lazy_segment_tree<mono, endo> seg;\n  {\n    std::vector<mono>\
    \ a(n);\n    for (auto &[v, c] : a) {\n      int _v;\n      scanf(\"%d\", &_v);\n\
    \      v = _v;\n      c = 1;\n    }\n    seg = a;\n  }\n  for (int t, l, r, a,\
    \ b; q--;) {\n    scanf(\"%d%d%d\", &t, &l, &r);\n    if (t) {\n      printf(\"\
    %d\\n\", seg.fold(l, r).v);\n    } else {\n      scanf(\"%d%d\", &a, &b);\n  \
    \    seg.update(l, r, {a, b});\n    }\n  }\n}\n"
  dependsOn:
  - data_structure/segment_tree/lazy.hpp
  - utils/sfinae.hpp
  - modulus/modint.hpp
  isVerificationFile: true
  path: test/library-checker/range_affine_range_sum.test.cpp
  requiredBy: []
  timestamp: '2020-09-17 16:18:47+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/library-checker/range_affine_range_sum.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/range_affine_range_sum.test.cpp
- /verify/test/library-checker/range_affine_range_sum.test.cpp.html
title: test/library-checker/range_affine_range_sum.test.cpp
---