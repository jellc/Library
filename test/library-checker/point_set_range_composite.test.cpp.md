---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/algebra/system/monoid.hpp
    title: src/algebra/system/monoid.hpp
  - icon: ':heavy_check_mark:'
    path: src/data_structure/segment_tree/basic.hpp
    title: Segment Tree
  - icon: ':heavy_check_mark:'
    path: src/modular/modint.hpp
    title: Modular Arithmetic
  - icon: ':heavy_check_mark:'
    path: src/utils/sfinae.hpp
    title: SFINAE
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
    \n\n#include <cstdio>\n\n#line 2 \"src/data_structure/segment_tree/basic.hpp\"\
    \n\n/**\n * @file basic.hpp\n * @brief Segment Tree\n */\n\n#include <cassert>\n\
    #include <vector>\n\n#line 2 \"src/algebra/system/monoid.hpp\"\n#include <limits>\n\
    \nnamespace workspace {\ntemplate <class T, class E = T> struct min_monoid {\n\
    \  using value_type = T;\n  static T min, max;\n  T value;\n  min_monoid() : value(max)\
    \ {}\n  min_monoid(const T &value) : value(value) {}\n  operator T() const { return\
    \ value; }\n  min_monoid operator+(const min_monoid &rhs) const {\n    return\
    \ value < rhs.value ? *this : rhs;\n  }\n  min_monoid operator*(const E &rhs)\
    \ const;\n};\n\ntemplate <class T, class E>\nT min_monoid<T, E>::min = std::numeric_limits<T>::min()\
    \ / 2;\ntemplate <class T, class E>\nT min_monoid<T, E>::max = std::numeric_limits<T>::max()\
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
    \ pass_args(\n      Pred pred, Monoid const &_1, size_type _2) {\n    return pred(_1);\n\
    \  }\n\n  template <class Pred>\n  static constexpr decltype(std::declval<Pred>()(Monoid{},\
    \ size_type{}))\n  pass_args(Pred pred, Monoid const &_1, size_type _2) {\n  \
    \  return pred(_1, _2);\n  }\n\n  template <class Pred>\n  size_type left_partition_subtree(size_type\
    \ __i, Monoid mono, size_type step,\n                                   Pred pred)\
    \ {\n    assert(__i);\n    while (__i < size_ext) {\n      const Monoid tmp =\
    \ pull((__i <<= 1) | 1) + mono;\n      if (pass_args(pred, tmp, ((__i | 1) <<\
    \ --step) ^ size_ext))\n        mono = tmp;\n      else\n        ++__i;\n    }\n\
    \    return ++__i -= size_ext;\n  }\n\n  template <class Pred>\n  size_type right_partition_subtree(size_type\
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
    \   return size_orig;\n  }\n};\n\n}  // namespace workspace\n#line 2 \"src/modular/modint.hpp\"\
    \n\n/*\n * @file modint.hpp\n * @brief Modular Arithmetic\n */\n\n#line 9 \"src/modular/modint.hpp\"\
    \n#include <iostream>\n\n#line 2 \"src/utils/sfinae.hpp\"\n\n/*\n * @file sfinae.hpp\n\
    \ * @brief SFINAE\n */\n\n#include <cstdint>\n#include <iterator>\n#include <type_traits>\n\
    \n#ifdef __SIZEOF_INT128__\n#define __INT128_DEFINED__ 1\n#else\n#define __INT128_DEFINED__\
    \ 0\n#endif\n\nnamespace std {\n\n#if __INT128_DEFINED__\n\ntemplate <> struct\
    \ make_signed<__uint128_t> { using type = __int128_t; };\ntemplate <> struct make_signed<__int128_t>\
    \ { using type = __int128_t; };\n\ntemplate <> struct make_unsigned<__uint128_t>\
    \ { using type = __uint128_t; };\ntemplate <> struct make_unsigned<__int128_t>\
    \ { using type = __uint128_t; };\n\n#endif\n\n}  // namespace std\n\nnamespace\
    \ workspace {\n\ntemplate <class type, template <class> class trait>\nusing enable_if_trait_type\
    \ = typename std::enable_if<trait<type>::value>::type;\n\ntemplate <class Container>\n\
    using element_type = typename std::decay<decltype(\n    *std::begin(std::declval<Container&>()))>::type;\n\
    \ntemplate <class T, class = std::nullptr_t>\nstruct has_begin : std::false_type\
    \ {};\n\ntemplate <class T>\nstruct has_begin<T, decltype(std::begin(std::declval<T>()),\
    \ nullptr)>\n    : std::true_type {};\n\ntemplate <class T, class = int> struct\
    \ mapped_of {\n  using type = element_type<T>;\n};\ntemplate <class T>\nstruct\
    \ mapped_of<T,\n                 typename std::pair<int, typename T::mapped_type>::first_type>\
    \ {\n  using type = typename T::mapped_type;\n};\ntemplate <class T> using mapped_type\
    \ = typename mapped_of<T>::type;\n\ntemplate <class T, class = void> struct is_integral_ext\
    \ : std::false_type {};\ntemplate <class T>\nstruct is_integral_ext<\n    T, typename\
    \ std::enable_if<std::is_integral<T>::value>::type>\n    : std::true_type {};\n\
    \n#if __INT128_DEFINED__\n\ntemplate <> struct is_integral_ext<__int128_t> : std::true_type\
    \ {};\ntemplate <> struct is_integral_ext<__uint128_t> : std::true_type {};\n\n\
    #endif\n\n#if __cplusplus >= 201402\n\ntemplate <class T>\nconstexpr static bool\
    \ is_integral_ext_v = is_integral_ext<T>::value;\n\n#endif\n\ntemplate <typename\
    \ T, typename = void> struct multiplicable_uint {\n  using type = uint_least32_t;\n\
    };\ntemplate <typename T>\nstruct multiplicable_uint<\n    T, typename std::enable_if<(2\
    \ < sizeof(T)) &&\n                               (!__INT128_DEFINED__ || sizeof(T)\
    \ <= 4)>::type> {\n  using type = uint_least64_t;\n};\n\n#if __INT128_DEFINED__\n\
    \ntemplate <typename T>\nstruct multiplicable_uint<T, typename std::enable_if<(4\
    \ < sizeof(T))>::type> {\n  using type = __uint128_t;\n};\n\n#endif\n\n}  // namespace\
    \ workspace\n#line 12 \"src/modular/modint.hpp\"\n\nnamespace workspace {\n\n\
    namespace internal {\n\n/*\n * @struct modint_base\n * @brief base of modular\
    \ arithmetic.\n * @tparam Mod identifier, which represents modulus if positive\n\
    \ */\ntemplate <auto Mod> struct modint_base {\n  static_assert(is_integral_ext<decltype(Mod)>::value,\n\
    \                \"Mod must be integral type.\");\n\n  using mod_type =\n    \
    \  typename std::conditional<0 < Mod,\n                                typename\
    \ std::add_const<decltype(Mod)>::type,\n                                decltype(Mod)>::type;\n\
    \  static mod_type mod;\n\n  using value_type = typename std::decay<mod_type>::type;\n\
    \n  constexpr operator value_type() const noexcept { return value; }\n\n  constexpr\
    \ static modint_base one() noexcept { return 1; }\n\n  constexpr modint_base()\
    \ noexcept = default;\n\n  template <class int_type,\n            typename std::enable_if<is_integral_ext<int_type>::value>::type\
    \ * =\n                nullptr>\n  constexpr modint_base(int_type n) noexcept\n\
    \      : value((n %= mod) < 0 ? mod + n : n) {}\n\n  constexpr modint_base(bool\
    \ n) noexcept : modint_base(int(n)) {}\n\n  constexpr modint_base operator++(int)\
    \ noexcept {\n    modint_base t{*this};\n    return operator+=(1), t;\n  }\n\n\
    \  constexpr modint_base operator--(int) noexcept {\n    modint_base t{*this};\n\
    \    return operator-=(1), t;\n  }\n\n  constexpr modint_base &operator++() noexcept\
    \ { return operator+=(1); }\n\n  constexpr modint_base &operator--() noexcept\
    \ { return operator-=(1); }\n\n  constexpr modint_base operator-() const noexcept\
    \ {\n    return value ? mod - value : 0;\n  }\n\n  constexpr modint_base &operator+=(const\
    \ modint_base &rhs) noexcept {\n    return (value += rhs.value) < mod ? 0 : value\
    \ -= mod, *this;\n  }\n\n  constexpr modint_base &operator-=(const modint_base\
    \ &rhs) noexcept {\n    return (value += mod - rhs.value) < mod ? 0 : value -=\
    \ mod, *this;\n  }\n\n  constexpr modint_base &operator*=(const modint_base &rhs)\
    \ noexcept {\n    return value = (typename multiplicable_uint<value_type>::type)value\
    \ *\n                   rhs.value % mod,\n           *this;\n  }\n\n  constexpr\
    \ modint_base &operator/=(const modint_base &rhs) noexcept {\n    return operator*=(rhs.inverse());\n\
    \  }\n\n  template <class int_type>\n  constexpr typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                    modint_base>::type\n  operator+(const int_type\
    \ &rhs) const noexcept {\n    return modint_base{*this} += rhs;\n  }\n\n  constexpr\
    \ modint_base operator+(const modint_base &rhs) const noexcept {\n    return modint_base{*this}\
    \ += rhs;\n  }\n\n  template <class int_type>\n  constexpr typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                    modint_base>::type\n  operator-(const int_type\
    \ &rhs) const noexcept {\n    return modint_base{*this} -= rhs;\n  }\n\n  constexpr\
    \ modint_base operator-(const modint_base &rhs) const noexcept {\n    return modint_base{*this}\
    \ -= rhs;\n  }\n\n  template <class int_type>\n  constexpr typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                    modint_base>::type\n  operator*(const int_type\
    \ &rhs) const noexcept {\n    return modint_base{*this} *= rhs;\n  }\n\n  constexpr\
    \ modint_base operator*(const modint_base &rhs) const noexcept {\n    return modint_base{*this}\
    \ *= rhs;\n  }\n\n  template <class int_type>\n  constexpr typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                    modint_base>::type\n  operator/(const int_type\
    \ &rhs) const noexcept {\n    return modint_base{*this} /= rhs;\n  }\n\n  constexpr\
    \ modint_base operator/(const modint_base &rhs) const noexcept {\n    return modint_base{*this}\
    \ /= rhs;\n  }\n\n  template <class int_type>\n  constexpr friend typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                           modint_base>::type\n  operator+(const\
    \ int_type &lhs, const modint_base &rhs) noexcept {\n    return modint_base(lhs)\
    \ + rhs;\n  }\n\n  template <class int_type>\n  constexpr friend typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                           modint_base>::type\n  operator-(const\
    \ int_type &lhs, const modint_base &rhs) noexcept {\n    return modint_base(lhs)\
    \ - rhs;\n  }\n\n  template <class int_type>\n  constexpr friend typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                           modint_base>::type\n  operator*(const\
    \ int_type &lhs, const modint_base &rhs) noexcept {\n    return modint_base(lhs)\
    \ * rhs;\n  }\n\n  template <class int_type>\n  constexpr friend typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                           modint_base>::type\n  operator/(const\
    \ int_type &lhs, const modint_base &rhs) noexcept {\n    return modint_base(lhs)\
    \ / rhs;\n  }\n\n  constexpr modint_base inverse() const noexcept {\n    assert(value);\n\
    \    value_type a{mod}, b{value}, u{}, v{1}, t{};\n    while (b)\n      t = a\
    \ / b, a ^= b ^= (a -= t * b) ^= b, u ^= v ^= (u -= t * v) ^= v;\n    return {u};\n\
    \  }\n\n  template <class int_type>\n  constexpr typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                    modint_base>::type\n  power(int_type e) noexcept\
    \ {\n    return pow(*this, e);\n  }\n\n  template <class int_type>\n  friend constexpr\
    \ typename std::enable_if<is_integral_ext<int_type>::value,\n                \
    \                           modint_base>::type\n  pow(modint_base b, int_type\
    \ e) noexcept {\n    modint_base res{1};\n    for (e < 0 ? b = b.inverse(), e\
    \ = -e : 0; e; e >>= 1, b *= b)\n      if (e & 1) res *= b;\n    return res;\n\
    \  }\n\n  friend std::ostream &operator<<(std::ostream &os,\n                \
    \                  const modint_base &rhs) noexcept {\n    return os << rhs.value;\n\
    \  }\n\n  friend std::istream &operator>>(std::istream &is, modint_base &rhs)\
    \ noexcept {\n    intmax_t value;\n    rhs = (is >> value, value);\n    return\
    \ is;\n  }\n\n protected:\n  value_type value = 0;\n};\n\ntemplate <auto Mod>\n\
    typename modint_base<Mod>::mod_type modint_base<Mod>::mod = Mod;\n\n}  // namespace\
    \ internal\n\n/*\n * @typedef modint\n * @brief modular arithmetic.\n * @tparam\
    \ Mod modulus\n */\ntemplate <auto Mod, typename std::enable_if<(Mod > 0)>::type\
    \ * = nullptr>\nusing modint = internal::modint_base<Mod>;\n\n/*\n * @typedef\
    \ modint_runtime\n * @brief runtime modular arithmetic.\n * @tparam type_id uniquely\
    \ assigned\n */\ntemplate <unsigned type_id = 0>\nusing modint_runtime = internal::modint_base<-(signed)type_id>;\n\
    \n// #define modint_newtype modint_runtime<__COUNTER__>\n\n}  // namespace workspace\n\
    #line 7 \"test/library-checker/point_set_range_composite.test.cpp\"\n\nint main()\
    \ {\n  using namespace workspace;\n  using mint = modint<998244353>;\n  int n,\
    \ q;\n  scanf(\"%d%d\", &n, &q);\n  struct mono {\n    mint c = 1, d;\n    mono\
    \ operator+(const mono& rhs) const {\n      return {rhs.c * c, rhs.c * d + rhs.d};\n\
    \    }\n    mint eval(mint x) const { return c * x + d; }\n  };\n  segment_tree<mono>\
    \ seg(n);\n  for (int i = 0; i < n; i++) {\n    int a, b;\n    scanf(\"%d%d\"\
    , &a, &b);\n    seg[i] = {a, b};\n  }\n  for (int t, a, b, c; q--;) {\n    scanf(\"\
    %d%d%d%d\", &t, &a, &b, &c);\n    if (t) {\n      printf(\"%d\\n\", seg.fold(a,\
    \ b).eval(c));\n    } else {\n      seg[a] = {b, c};\n    }\n  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_set_range_composite\"\
    \n\n#include <cstdio>\n\n#include \"src/data_structure/segment_tree/basic.hpp\"\
    \n#include \"src/modular/modint.hpp\"\n\nint main() {\n  using namespace workspace;\n\
    \  using mint = modint<998244353>;\n  int n, q;\n  scanf(\"%d%d\", &n, &q);\n\
    \  struct mono {\n    mint c = 1, d;\n    mono operator+(const mono& rhs) const\
    \ {\n      return {rhs.c * c, rhs.c * d + rhs.d};\n    }\n    mint eval(mint x)\
    \ const { return c * x + d; }\n  };\n  segment_tree<mono> seg(n);\n  for (int\
    \ i = 0; i < n; i++) {\n    int a, b;\n    scanf(\"%d%d\", &a, &b);\n    seg[i]\
    \ = {a, b};\n  }\n  for (int t, a, b, c; q--;) {\n    scanf(\"%d%d%d%d\", &t,\
    \ &a, &b, &c);\n    if (t) {\n      printf(\"%d\\n\", seg.fold(a, b).eval(c));\n\
    \    } else {\n      seg[a] = {b, c};\n    }\n  }\n}\n"
  dependsOn:
  - src/data_structure/segment_tree/basic.hpp
  - src/algebra/system/monoid.hpp
  - src/modular/modint.hpp
  - src/utils/sfinae.hpp
  isVerificationFile: true
  path: test/library-checker/point_set_range_composite.test.cpp
  requiredBy: []
  timestamp: '2020-12-21 17:31:55+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/library-checker/point_set_range_composite.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/point_set_range_composite.test.cpp
- /verify/test/library-checker/point_set_range_composite.test.cpp.html
title: test/library-checker/point_set_range_composite.test.cpp
---
