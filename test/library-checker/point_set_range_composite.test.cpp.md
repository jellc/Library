---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/segment_tree/basic.hpp
    title: data_structure/segment_tree/basic.hpp
  - icon: ':heavy_check_mark:'
    path: algebra/system/monoid.hpp
    title: algebra/system/monoid.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/point_set_range_composite
    links:
    - https://judge.yosupo.jp/problem/point_set_range_composite
  bundledCode: "#line 1 \"test/library-checker/point_set_range_composite.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/point_set_range_composite\"\
    \n#line 2 \"data_structure/segment_tree/basic.hpp\"\n#include <cassert>\n#include\
    \ <vector>\n\n#line 2 \"algebra/system/monoid.hpp\"\n#include <limits>\ntemplate\
    \ <class T>\nstruct min_monoid\n{\n    using value_type = T;\n    static T min,\
    \ max;\n    T value;\n    min_monoid() : value(max) {}\n    min_monoid(const T\
    \ &value) : value(value) {}\n    operator T() const { return value; }\n    min_monoid\
    \ operator+(const min_monoid &rhs) const\n    {\n        return value < rhs.value\
    \ ? *this : rhs;\n    }\n};\ntemplate <class T> T min_monoid<T>::min = std::numeric_limits<T>::min();\n\
    template <class T> T min_monoid<T>::max = std::numeric_limits<T>::max();\ntemplate\
    \ <class T>\nstruct max_monoid : min_monoid<T>\n{\n    using base = min_monoid<T>;\n\
    \    using base::min_monoid;\n    max_monoid() : base(base::min) {}\n    max_monoid\
    \ operator+(const max_monoid &rhs) const\n    {\n        return !(base::value\
    \ < rhs.value) ? *this : rhs;\n    }\n};\n#line 2 \"utils/sfinae.hpp\"\n#include\
    \ <cstdint>\n#include <type_traits>\n\ntemplate <class type, template <class>\
    \ class trait>\nusing enable_if_trait_type = typename std::enable_if<trait<type>::value>::type;\n\
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
    \ < sizeof(T))>::type> {\n  using type = __uint128_t;\n};\n#line 7 \"data_structure/segment_tree/basic.hpp\"\
    \ntemplate <class Monoid, class Container = std::vector<Monoid>>\nclass segment_tree\
    \ {\n  static_assert(std::is_same<Monoid, mapped_type<Container>>::value);\n\n\
    \  class unique_queue {\n    size_t *que, *begin, *end;\n    bool *in;\n\n   public:\n\
    \    unique_queue(size_t n)\n        : que(new size_t[n]), begin(que), end(que),\
    \ in(new bool[n]{}) {}\n\n    ~unique_queue() {\n      delete[] que;\n      delete[]\
    \ in;\n    }\n\n    void clear() { begin = end = que; }\n\n    bool empty() const\
    \ { return begin == end; }\n\n    bool push(size_t index) {\n      if (in[index])\
    \ return false;\n      return in[*end++ = index] = true;\n    }\n\n    size_t\
    \ pop() { return in[*begin] = false, *begin++; }\n  };  // struct unique_queue\n\
    \n  size_t size_orig, height, size_ext;\n  Container data;\n  unique_queue que;\n\
    \n  void repair() {\n    while (!que.empty()) {\n      const size_t index = que.pop()\
    \ >> 1;\n      if (index && que.push(index)) pull(index);\n    }\n    que.clear();\n\
    \  }\n\n  void pull(const size_t node) {\n    data[node] = data[node << 1] + data[node\
    \ << 1 | 1];\n  }\n\n  template <class Pred>\n  size_t left_search_subtree(size_t\
    \ index, const Pred pred, Monoid mono) const {\n    assert(index);\n    while\
    \ (index < size_ext) {\n      const Monoid tmp = data[(index <<= 1) | 1] + mono;\n\
    \      if (pred(tmp))\n        mono = tmp;\n      else\n        ++index;\n   \
    \ }\n    return ++index -= size_ext;\n  }\n\n  template <class Pred>\n  size_t\
    \ right_search_subtree(size_t index, const Pred pred,\n                      \
    \        Monoid mono) const {\n    assert(index);\n    while (index < size_ext)\
    \ {\n      const Monoid tmp = mono + data[index <<= 1];\n      if (pred(tmp))\
    \ ++index, mono = tmp;\n    }\n    return (index -= size_ext) < size_orig ? index\
    \ : size_orig;\n  }\n\n public:\n  using value_type = Monoid;\n\n  segment_tree(const\
    \ size_t n = 0)\n      : size_orig{n},\n        height(n > 1 ? 32 - __builtin_clz(n\
    \ - 1) : 0),\n        size_ext{1u << height},\n        data(size_ext << 1),\n\
    \        que(size_ext << 1) {}\n\n  segment_tree(const size_t n, const Monoid\
    \ &init) : segment_tree(n) {\n    std::fill(std::next(std::begin(data), size_ext),\
    \ std::end(data), init);\n    for (size_t i{size_ext}; --i;) pull(i);\n  }\n\n\
    \  template <class iter_type, class value_type = typename std::iterator_traits<\n\
    \                                 iter_type>::value_type>\n  segment_tree(iter_type\
    \ first, iter_type last)\n      : size_orig(std::distance(first, last)),\n   \
    \     height(size_orig > 1 ? 32 - __builtin_clz(size_orig - 1) : 0),\n       \
    \ size_ext{1u << height},\n        data(size_ext << 1),\n        que(size_ext\
    \ << 1) {\n    static_assert(std::is_constructible<Monoid, value_type>::value,\n\
    \                  \"Monoid(iter_type::value_type) is not constructible.\");\n\
    \    for (auto iter{std::next(std::begin(data), size_ext)};\n         iter !=\
    \ std::end(data) && first != last; ++iter, ++first)\n      *iter = Monoid{*first};\n\
    \    for (size_t i{size_ext}; --i;) pull(i);\n  }\n\n  template <class Cont, typename\
    \ = typename Cont::value_type>\n  segment_tree(const Cont &cont)\n      : segment_tree(std::begin(cont),\
    \ std::end(cont)) {}\n\n  size_t size() const { return size_orig; }\n  size_t\
    \ capacity() const { return size_ext; }\n\n  // reference to the element at the\
    \ index.\n  Monoid &operator[](size_t index) {\n    assert(index < size_orig);\n\
    \    que.push(index |= size_ext);\n    return data[index];\n  }\n\n  // const\
    \ reference to the element at the index.\n  const Monoid &operator[](size_t index)\
    \ const {\n    assert(index < size_orig);\n    return data[index |= size_orig];\n\
    \  }\n\n  Monoid fold(size_t first, size_t last) {\n    assert(last <= size_orig);\n\
    \    repair();\n    Monoid leftval{}, rightval{};\n    first += size_ext, last\
    \ += size_ext;\n    while (first < last) {\n      if (first & 1) leftval = leftval\
    \ + data[first++];\n      if (last & 1) rightval = data[--last] + rightval;\n\
    \      first >>= 1, last >>= 1;\n    }\n    return leftval + rightval;\n  }\n\n\
    \  Monoid fold() { return fold(0, size_orig); }\n\n  template <class Pred> size_t\
    \ left_search(size_t right, Pred pred) {\n    assert(right <= size_orig);\n  \
    \  repair();\n    right += size_ext;\n    Monoid mono{};\n    for (size_t left{size_ext};\
    \ left != right; left >>= 1, right >>= 1) {\n      if ((left & 1) != (right &\
    \ 1)) {\n        const Monoid tmp = data[--right] + mono;\n        if (!pred(tmp))\
    \ return left_search_subtree(right, pred, mono);\n        mono = tmp;\n      }\n\
    \    }\n    return 0;\n  }\n\n  template <class Pred> size_t right_search(size_t\
    \ left, Pred pred) {\n    assert(left <= size_orig);\n    repair();\n    left\
    \ += size_ext;\n    Monoid mono{};\n    for (size_t right{size_ext << 1}; left\
    \ != right; left >>= 1, right >>= 1) {\n      if ((left & 1) != (right & 1)) {\n\
    \        const Monoid tmp = mono + data[left];\n        if (!pred(tmp)) return\
    \ right_search_subtree(left, pred, mono);\n        mono = tmp;\n        ++left;\n\
    \      }\n    }\n    return size_orig;\n  }\n};  // class segment_tree\n#line\
    \ 3 \"modulus/modint.hpp\"\n#include <iostream>\n\n#line 6 \"modulus/modint.hpp\"\
    \n\n// A non-positive Mod corresponds a runtime type of modint.\ntemplate <auto\
    \ Mod = 0, typename Mod_type = decltype(Mod)> struct modint {\n  static_assert(is_integral_ext<decltype(Mod)>::value,\n\
    \                \"Mod must be integral type.\");\n\n  using mod_type = typename\
    \ std::conditional<\n      0 < Mod, typename std::add_const<Mod_type>::type, Mod_type>::type;\n\
    \  static mod_type mod;\n\n  using value_type = typename std::decay<mod_type>::type;\n\
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
    \    modint res{1};\n    for (modint p{value}; e; e >>= 1, p *= p) {\n      if\
    \ (e & 1) res *= p;\n    }\n    return res;\n  }\n\n  template <class int_type>\n\
    \  friend constexpr\n      typename std::enable_if<is_integral_ext<int_type>::value,\
    \ modint>::type\n      pow(modint b, int_type e) noexcept {\n    modint res{1};\n\
    \    for ((e %= mod - 1) < 0 ? e += mod - 1 : 0; e; e >>= 1, b *= b)\n      if\
    \ (e & 1) res *= b;\n    return res;\n  }\n\n  friend std::ostream &operator<<(std::ostream\
    \ &os,\n                                  const modint &rhs) noexcept {\n    return\
    \ os << rhs.value;\n  }\n\n  friend std::istream &operator>>(std::istream &is,\
    \ modint &rhs) noexcept {\n    intmax_t value;\n    rhs = (is >> value, value);\n\
    \    return is;\n  }\n\n protected:\n  value_type value = 0;\n};\n\ntemplate <auto\
    \ Mod, typename Mod_type>\ntypename modint<Mod, Mod_type>::mod_type modint<Mod,\
    \ Mod_type>::mod = Mod;\n\ntemplate <unsigned type_id = 0> using modint_runtime\
    \ = modint<-(signed)type_id>;\n// #define modint_newtype modint<-__COUNTER__>\n\
    #line 4 \"test/library-checker/point_set_range_composite.test.cpp\"\n#include\
    \ <cstdio>\n\nint main()\n{\n    using mint=modint<998244353>;\n    int n,q;\n\
    \    scanf(\"%d%d\",&n,&q);\n    struct mono\n    {\n        mint c=1,d;\n   \
    \     mono operator+(const mono& rhs)\n        {\n            return {rhs.c*c,rhs.c*d+rhs.d};\n\
    \        }\n        mint eval(mint x) const\n        {\n            return c*x+d;\n\
    \        }\n    };\n    segment_tree<mono> seg(n);\n    for(int i=0; i<n; i++)\n\
    \    {\n        int a,b;\n        scanf(\"%d%d\",&a,&b);\n        seg[i]={a,b};\n\
    \    }\n    for(int t,a,b,c; q--;)\n    {\n        scanf(\"%d%d%d%d\",&t,&a,&b,&c);\n\
    \        if(t)\n        {\n            printf(\"%d\\n\",seg.fold(a,b).eval(c));\n\
    \        }\n        else\n        {\n            seg[a]={b,c};\n        }\n  \
    \  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_set_range_composite\"\
    \n#include \"data_structure/segment_tree/basic.hpp\"\n#include \"modulus/modint.hpp\"\
    \n#include <cstdio>\n\nint main()\n{\n    using mint=modint<998244353>;\n    int\
    \ n,q;\n    scanf(\"%d%d\",&n,&q);\n    struct mono\n    {\n        mint c=1,d;\n\
    \        mono operator+(const mono& rhs)\n        {\n            return {rhs.c*c,rhs.c*d+rhs.d};\n\
    \        }\n        mint eval(mint x) const\n        {\n            return c*x+d;\n\
    \        }\n    };\n    segment_tree<mono> seg(n);\n    for(int i=0; i<n; i++)\n\
    \    {\n        int a,b;\n        scanf(\"%d%d\",&a,&b);\n        seg[i]={a,b};\n\
    \    }\n    for(int t,a,b,c; q--;)\n    {\n        scanf(\"%d%d%d%d\",&t,&a,&b,&c);\n\
    \        if(t)\n        {\n            printf(\"%d\\n\",seg.fold(a,b).eval(c));\n\
    \        }\n        else\n        {\n            seg[a]={b,c};\n        }\n  \
    \  }\n}\n"
  dependsOn:
  - data_structure/segment_tree/basic.hpp
  - algebra/system/monoid.hpp
  - utils/sfinae.hpp
  - modulus/modint.hpp
  isVerificationFile: true
  path: test/library-checker/point_set_range_composite.test.cpp
  requiredBy: []
  timestamp: '2020-09-25 00:26:35+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/library-checker/point_set_range_composite.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/point_set_range_composite.test.cpp
- /verify/test/library-checker/point_set_range_composite.test.cpp.html
title: test/library-checker/point_set_range_composite.test.cpp
---
