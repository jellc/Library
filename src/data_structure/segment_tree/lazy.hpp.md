---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/algebra/system/monoid.hpp
    title: src/algebra/system/monoid.hpp
  - icon: ':heavy_check_mark:'
    path: src/algebra/system/operation.hpp
    title: Operation Traits
  - icon: ':heavy_check_mark:'
    path: src/data_structure/segment_tree/waitings.hpp
    title: src/data_structure/segment_tree/waitings.hpp
  - icon: ':question:'
    path: src/utils/sfinae.hpp
    title: SFINAE
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/2450.test.cpp
    title: test/aizu-online-judge/2450.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/range_affine_range_sum.test.cpp
    title: test/library-checker/range_affine_range_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Lazy Segment Tree
    links: []
  bundledCode: "#line 2 \"src/data_structure/segment_tree/lazy.hpp\"\n\n/**\n * @file\
    \ lazy.hpp\n * @brief Lazy Segment Tree\n */\n\n#include <cassert>\n#include <queue>\n\
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
    \ E &rhs) const;\n};\n}\n#line 2 \"src/algebra/system/operation.hpp\"\n\n/**\n\
    \ * @file operation.hpp\n * @brief Operation Traits\n */\n\n#include <type_traits>\n\
    \n#line 2 \"lib/cxx17\"\n\n#line 2 \"lib/cxx14\"\n\n#ifndef _CXX14_CONSTEXPR\n\
    #if __cplusplus >= 201402L\n#define _CXX14_CONSTEXPR constexpr\n#else\n#define\
    \ _CXX14_CONSTEXPR\n#endif\n#endif\n#line 4 \"lib/cxx17\"\n\n#ifndef _CXX17_CONSTEXPR\n\
    #if __cplusplus >= 201703L\n#define _CXX17_CONSTEXPR constexpr\n#else\n#define\
    \ _CXX17_CONSTEXPR\n#endif\n#endif\n\n#ifndef _CXX17_STATIC_ASSERT\n#if __cplusplus\
    \ >= 201703L\n#define _CXX17_STATIC_ASSERT static_assert\n#else\n#define _CXX17_STATIC_ASSERT\
    \ assert\n#endif\n#endif\n\n#include <iterator>\n\n#if __cplusplus < 201703L\n\
    \nnamespace std {\n\n/**\n *  @brief  Return the size of a container.\n *  @param\
    \  __cont  Container.\n */\ntemplate <typename _Container>\nconstexpr auto size(const\
    \ _Container& __cont) noexcept(noexcept(__cont.size()))\n    -> decltype(__cont.size())\
    \ {\n  return __cont.size();\n}\n\n/**\n *  @brief  Return the size of an array.\n\
    \ */\ntemplate <typename _Tp, size_t _Nm>\nconstexpr size_t size(const _Tp (&)[_Nm])\
    \ noexcept {\n  return _Nm;\n}\n\n/**\n *  @brief  Return whether a container\
    \ is empty.\n *  @param  __cont  Container.\n */\ntemplate <typename _Container>\n\
    [[nodiscard]] constexpr auto empty(const _Container& __cont) noexcept(\n    noexcept(__cont.empty()))\
    \ -> decltype(__cont.empty()) {\n  return __cont.empty();\n}\n\n/**\n *  @brief\
    \  Return whether an array is empty (always false).\n */\ntemplate <typename _Tp,\
    \ size_t _Nm>\n[[nodiscard]] constexpr bool empty(const _Tp (&)[_Nm]) noexcept\
    \ {\n  return false;\n}\n\n/**\n *  @brief  Return whether an initializer_list\
    \ is empty.\n *  @param  __il  Initializer list.\n */\ntemplate <typename _Tp>\n\
    [[nodiscard]] constexpr bool empty(initializer_list<_Tp> __il) noexcept {\n  return\
    \ __il.size() == 0;\n}\n\nstruct monostate {};\n\n}  // namespace std\n\n#else\n\
    \n#include <variant>\n\n#endif\n#line 11 \"src/algebra/system/operation.hpp\"\n\
    \nnamespace workspace {\n\n// Unary `+`\ntemplate <class _Tp>\nusing require_unary_plus\
    \ = std::enable_if_t<\n    std::is_convertible<decltype(+std::declval<const _Tp\
    \ &>()), _Tp>::value>;\n\ntemplate <class _Tp, class = void> struct has_unary_plus\
    \ : std::false_type {};\n\ntemplate <class _Tp>\nstruct has_unary_plus<_Tp, require_unary_plus<_Tp>>\
    \ : std::true_type {};\n\n// Unary `-`\ntemplate <class _Tp>\nusing require_unary_minus\
    \ = std::enable_if_t<\n    std::is_convertible<decltype(-std::declval<const _Tp\
    \ &>()), _Tp>::value>;\n\ntemplate <class _Tp, class = void> struct has_unary_minus\
    \ : std::false_type {};\n\ntemplate <class _Tp>\nstruct has_unary_minus<_Tp, require_unary_minus<_Tp>>\
    \ : std::true_type {};\n\n// Binary `+`\ntemplate <class _Tp1, class _Tp2 = _Tp1>\n\
    using require_binary_plus =\n    std::enable_if_t<std::is_convertible<decltype(std::declval<const\
    \ _Tp1 &>() +\n                                                  std::declval<const\
    \ _Tp2 &>()),\n                                         _Tp1>::value>;\n\ntemplate\
    \ <class _Tp1, class _Tp2 = _Tp1, class = void>\nstruct has_binary_plus : std::false_type\
    \ {};\n\ntemplate <class _Tp1, class _Tp2>\nstruct has_binary_plus<_Tp1, _Tp2,\
    \ require_binary_plus<_Tp1, _Tp2>>\n    : std::true_type {};\n\n// Binary `-`\n\
    template <class _Tp1, class _Tp2 = _Tp1>\nusing require_binary_minus =\n    std::__void_t<decltype(std::declval<const\
    \ _Tp1 &>() -\n                           std::declval<const _Tp2 &>())>;\n\n\
    template <class _Tp1, class _Tp2 = _Tp1, class = void>\nstruct has_binary_minus\
    \ : std::false_type {};\n\ntemplate <class _Tp1, class _Tp2>\nstruct has_binary_minus<_Tp1,\
    \ _Tp2, require_binary_minus<_Tp1, _Tp2>>\n    : std::true_type {};\n\n// Binary\
    \ `*`\ntemplate <class _Tp1, class _Tp2 = _Tp1>\nusing require_binary_multiplies\
    \ =\n    std::enable_if_t<std::is_convertible<decltype(std::declval<const _Tp1\
    \ &>() *\n                                                  std::declval<const\
    \ _Tp2 &>()),\n                                         _Tp1>::value>;\n\ntemplate\
    \ <class _Tp1, class _Tp2 = _Tp1, class = void>\nstruct has_binary_multiplies\
    \ : std::false_type {};\n\ntemplate <class _Tp1, class _Tp2>\nstruct has_binary_multiplies<_Tp1,\
    \ _Tp2, require_binary_multiplies<_Tp1, _Tp2>>\n    : std::true_type {};\n\n//\
    \ Binary `/`\ntemplate <class _Tp1, class _Tp2 = _Tp1>\nusing require_binary_divides\
    \ =\n    std::enable_if_t<std::is_convertible<decltype(std::declval<const _Tp1\
    \ &>() /\n                                                  std::declval<const\
    \ _Tp2 &>()),\n                                         _Tp1>::value>;\n\ntemplate\
    \ <class _Tp1, class _Tp2 = _Tp1, class = void>\nstruct has_binary_divides : std::false_type\
    \ {};\n\ntemplate <class _Tp1, class _Tp2>\nstruct has_binary_divides<_Tp1, _Tp2,\
    \ require_binary_divides<_Tp1, _Tp2>>\n    : std::true_type {};\n\n// Binary `%`\n\
    template <class _Tp1, class _Tp2 = _Tp1>\nusing require_binary_modulus =\n   \
    \ std::enable_if_t<std::is_convertible<decltype(std::declval<const _Tp1 &>() %\n\
    \                                                  std::declval<const _Tp2 &>()),\n\
    \                                         _Tp1>::value>;\n\ntemplate <class _Tp1,\
    \ class _Tp2 = _Tp1, class = void>\nstruct has_binary_modulus : std::false_type\
    \ {};\n\ntemplate <class _Tp1, class _Tp2>\nstruct has_binary_modulus<_Tp1, _Tp2,\
    \ require_binary_modulus<_Tp1, _Tp2>>\n    : std::true_type {};\n\ntemplate <class\
    \ _Tp1, class _Tp2 = _Tp1, class = void, class = void,\n          class = void,\
    \ class = void>\nstruct has_arithmetic : std::false_type {};\n\ntemplate <class\
    \ _Tp1, class _Tp2>\nstruct has_arithmetic<_Tp1, _Tp2, require_binary_plus<_Tp1,\
    \ _Tp2>,\n                      require_binary_minus<_Tp1, _Tp2>,\n          \
    \            require_binary_multiplies<_Tp1, _Tp2>,\n                      require_binary_divides<_Tp1,\
    \ _Tp2>> : std::true_type {};\n\ntemplate <class _Tp1, class _Tp2 = _Tp1>\nusing\
    \ require_arithmetic = std::enable_if_t<has_arithmetic<_Tp1, _Tp2>::value>;\n\n\
    // Binary `<`\ntemplate <class _Tp, class = void> struct is_comparable : std::false_type\
    \ {};\n\ntemplate <class _Tp>\nstruct is_comparable<_Tp, std::__void_t<decltype(std::declval<const\
    \ _Tp &>() <\n                                                 std::declval<const\
    \ _Tp &>())>>\n    : std::true_type {};\n\ntemplate <class _Tp, bool _Default\
    \ = false> struct try_less : std::less<_Tp> {\n  constexpr bool operator()(const\
    \ _Tp &__x, const _Tp &__y) noexcept {\n    if _CXX17_CONSTEXPR (is_comparable<_Tp>::value)\n\
    \      return std::less<_Tp>::operator()(__x, __y);\n    else\n      return _Default;\n\
    \  }\n};\n\n}  // namespace workspace\n#line 2 \"src/utils/sfinae.hpp\"\n\n/**\n\
    \ * @file sfinae.hpp\n * @brief SFINAE\n */\n\n#include <cstdint>\n#line 11 \"\
    src/utils/sfinae.hpp\"\n\n#ifndef __INT128_DEFINED__\n\n#ifdef __SIZEOF_INT128__\n\
    #define __INT128_DEFINED__ 1\n#else\n#define __INT128_DEFINED__ 0\n#endif\n\n\
    #endif\n\nnamespace std {\n\n#if __INT128_DEFINED__\n\ntemplate <> struct make_signed<__uint128_t>\
    \ { using type = __int128_t; };\ntemplate <> struct make_signed<__int128_t> {\
    \ using type = __int128_t; };\n\ntemplate <> struct make_unsigned<__uint128_t>\
    \ { using type = __uint128_t; };\ntemplate <> struct make_unsigned<__int128_t>\
    \ { using type = __uint128_t; };\n\ntemplate <> struct is_signed<__uint128_t>\
    \ : std::false_type {};\ntemplate <> struct is_signed<__int128_t> : std::true_type\
    \ {};\n\ntemplate <> struct is_unsigned<__uint128_t> : std::true_type {};\ntemplate\
    \ <> struct is_unsigned<__int128_t> : std::false_type {};\n\n#endif\n\n}  // namespace\
    \ std\n\nnamespace workspace {\n\ntemplate <class Tp, class... Args> struct variadic_front\
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
    }  // namespace workspace\n#line 2 \"src/data_structure/segment_tree/waitings.hpp\"\
    \n\n#line 5 \"src/data_structure/segment_tree/waitings.hpp\"\n\nnamespace workspace\
    \ {\n\nnamespace internal {\n\nstruct waitings : std::queue<size_t> {\n  waitings(size_t\
    \ n) : in(n) {}\n\n  bool push(size_t index) {\n    // assert(index < in.size());\n\
    \    if (in[index]) return false;\n    emplace(index);\n    return (in[index]\
    \ = true);\n  }\n\n  size_t pop() {\n    // assert(!empty());\n    auto index\
    \ = front();\n    std::queue<size_t>::pop();\n    in[index] = false;\n    return\
    \ index;\n  }\n\n private:\n  std::vector<int_least8_t> in;\n};\n\n}  // namespace\
    \ internal\n\n}  // namespace workspace\n#line 16 \"src/data_structure/segment_tree/lazy.hpp\"\
    \n\nnamespace workspace {\n\ntemplate <class _Monoid, class _End,\n          class\
    \ Monoid_container = std::vector<_Monoid>,\n          class Endomorphism_container\
    \ = std::vector<_End>>\nclass lazy_segment_tree {\n  static_assert(\n      std::is_same<_Monoid,\
    \ typename Monoid_container::value_type>::value);\n\n  static_assert(\n      std::is_same<_End,\
    \ typename Endomorphism_container::value_type>::value);\n\n  static_assert(has_binary_plus<_Monoid>::value,\n\
    \                \"\\'_Monoid\\' has no proper binary \\'operator+\\'.\");\n\n\
    \  static_assert(has_binary_multiplies<_End>::value,\n                \"\\'_End\\\
    ' has no proper binary \\'operator*\\'.\");\n\n  static_assert(has_binary_multiplies<_Monoid,\
    \ _End>::value,\n                \"\\'_End\\' is not applicable to \\'_Monoid\\\
    '.\");\n\n  size_t size_orig, height, size_ext;\n  Monoid_container data;\n  Endomorphism_container\
    \ lazy;\n  internal::waitings wait;\n\n  void repair() {\n    while (!wait.empty())\
    \ {\n      const size_t __i = wait.pop() >> 1;\n      if (__i && wait.push(__i))\
    \ pull(__i);\n    }\n  }\n\n  void _apply(size_t node, const _End &__e) {\n  \
    \  data[node] = data[node] * __e;\n    if (node < size_ext) lazy[node] = lazy[node]\
    \ * __e;\n  }\n\n  void push(size_t node) {\n    _apply(node << 1, lazy[node]);\n\
    \    _apply(node << 1 | 1, lazy[node]);\n    lazy[node] = _End{};\n  }\n\n  void\
    \ pull(size_t node) { data[node] = data[node << 1] + data[node << 1 | 1]; }\n\n\
    \  template <class _Pred>\n  size_t left_partition_subtree(size_t node, _Monoid\
    \ mono, _Pred __pred) {\n    assert(node);\n    while (node < size_ext) {\n  \
    \    push(node);\n      const _Monoid __tmp = data[(node <<= 1) | 1] + mono;\n\
    \      if (__pred(__tmp))\n        mono = std::move(__tmp);\n      else\n    \
    \    ++node;\n    }\n    return ++node -= size_ext;\n  }\n\n  template <class\
    \ _Pred>\n  size_t right_partition_subtree(size_t node, _Monoid mono, _Pred __pred)\
    \ {\n    assert(node);\n    while (node < size_ext) {\n      push(node);\n   \
    \   const _Monoid __tmp = mono + data[node <<= 1];\n      if (__pred(__tmp)) ++node,\
    \ mono = std::move(__tmp);\n    }\n    return (node -= size_ext) < size_orig ?\
    \ node : size_orig;\n  }\n\n public:\n  class iterator {\n    lazy_segment_tree\
    \ *__p;\n    size_t __i;\n\n   public:\n    using difference_type = typename std::make_signed<size_t>::type;\n\
    \    using value_type = _Monoid;\n    using reference = _Monoid &;\n    using\
    \ pointer = iterator;\n    using iterator_category = std::random_access_iterator_tag;\n\
    \n    /**\n     * @brief Construct a new iterator object\n     *\n     */\n  \
    \  iterator() = default;\n\n    /**\n     * @brief Construct a new iterator object\n\
    \     *\n     * @param __p Pointer to a segment tree object\n     * @param __i\
    \ Index\n     */\n    iterator(lazy_segment_tree *__p, size_t __i) : __p(__p),\
    \ __i(__i) {}\n\n    bool operator==(iterator const &rhs) const {\n      return\
    \ __p == rhs.__p && __i == rhs.__i;\n    }\n    bool operator!=(iterator const\
    \ &rhs) const { return !operator==(rhs); }\n\n    bool operator<(iterator const\
    \ &rhs) const { return __i < rhs.__i; }\n    bool operator>(iterator const &rhs)\
    \ const { return __i > rhs.__i; }\n    bool operator<=(iterator const &rhs) const\
    \ { return __i <= rhs.__i; }\n    bool operator>=(iterator const &rhs) const {\
    \ return __i >= rhs.__i; }\n\n    iterator &operator++() { return ++__i, *this;\
    \ }\n    iterator &operator--() { return --__i, *this; }\n\n    difference_type\
    \ operator-(iterator const &rhs) const {\n      return __i - rhs.__i;\n    }\n\
    \n    /**\n     * @brief\n     *\n     * @return reference\n     */\n    reference\
    \ operator*() const { return __p->operator[](__i); }\n  };\n\n  using value_type\
    \ = typename iterator::value_type;\n  using reference = typename iterator::reference;\n\
    \n  iterator begin() { return {this, 0}; }\n  iterator end() { return {this, size_orig};\
    \ }\n\n  auto rbegin() { return std::make_reverse_iterator(end()); }\n  auto rend()\
    \ { return std::make_reverse_iterator(begin()); }\n\n  lazy_segment_tree(size_t\
    \ __n = 0)\n      : size_orig{__n},\n        height(__n > 1 ? 32 - __builtin_clz(__n\
    \ - 1) : 0),\n        size_ext{1u << height},\n        data(size_ext << 1),\n\
    \        lazy(size_ext),\n        wait(size_ext << 1) {}\n\n  lazy_segment_tree(size_t\
    \ __n, const _Monoid &init) : lazy_segment_tree(__n) {\n    std::fill_n(std::next(std::begin(data),\
    \ size_ext), __n, init);\n    for (size_t i{size_ext}; --i;) pull(i);\n  }\n\n\
    \  template <class iter_type, class value_type = typename std::iterator_traits<\n\
    \                                 iter_type>::value_type>\n  lazy_segment_tree(iter_type\
    \ first, iter_type last)\n      : size_orig(std::distance(first, last)),\n   \
    \     height(size_orig > 1 ? 32 - __builtin_clz(size_orig - 1) : 0),\n       \
    \ size_ext{1u << height},\n        data(size_ext << 1),\n        lazy(size_ext),\n\
    \        wait(size_ext << 1) {\n    static_assert(std::is_constructible<_Monoid,\
    \ value_type>::value,\n                  \"_Monoid(iter_type::value_type) is not\
    \ constructible.\");\n    for (auto iter{std::next(std::begin(data), size_ext)};\n\
    \         iter != std::end(data) && first != last; ++iter, ++first)\n      *iter\
    \ = _Monoid(*first);\n    for (size_t i{size_ext}; --i;) pull(i);\n  }\n\n  /**\n\
    \   * @return Number of elements.\n   */\n  size_t size() const { return size_orig;\
    \ }\n\n  /**\n   * @param __i Index of the element\n   * @return Reference to\
    \ the element.\n   */\n  _Monoid &operator[](size_t __i) {\n    assert(__i < size_orig);\n\
    \    __i |= size_ext;\n    wait.push(__i);\n    for (size_t i = height; i; --i)\
    \ push(__i >> i);\n    return data[__i];\n  }\n\n  void apply(const _End &__e)\
    \ { apply(0, size_orig, __e); }\n\n  void apply(size_t __i, const _End &__e) {\
    \ apply(__i, __i + 1, __e); }\n\n  void apply(size_t first, size_t last, const\
    \ _End &__e) {\n    assert(last <= size_orig);\n    repair();\n    if (first >=\
    \ last) return;\n    first += size_ext, last += size_ext;\n    --last;\n    for\
    \ (size_t i = height; i; --i) push(first >> i), push(last >> i);\n    ++last;\n\
    \    for (size_t l = first, r = last; l != r; l >>= 1, r >>= 1) {\n      if (l\
    \ & 1) _apply(l++, __e);\n      if (r & 1) _apply(--r, __e);\n    }\n    for (first\
    \ >>= __builtin_ffs(first); first; first >>= 1) pull(first);\n    for (last >>=\
    \ __builtin_ffs(last); last; last >>= 1) pull(last);\n  }\n\n  /**\n   * @param\
    \ first Left end, inclusive\n   * @param last Right end, exclusive\n   * @return\
    \ Sum of elements in the interval.\n   */\n  _Monoid fold(size_t first, size_t\
    \ last) {\n    assert(last <= size_orig);\n    repair();\n    if (first >= last)\
    \ return _Monoid{};\n    first += size_ext, last += size_ext - 1;\n    _Monoid\
    \ left_val{}, right_val{};\n    for (size_t l = first, r = last + 1; l != r; l\
    \ >>= 1, r >>= 1) {\n      if (l & 1) left_val = left_val + data[l++];\n     \
    \ if (r & 1) right_val = data[--r] + right_val;\n      left_val = left_val * lazy[first\
    \ >>= 1];\n      right_val = right_val * lazy[last >>= 1];\n    }\n    while (first\
    \ >>= 1, last >>= 1) {\n      left_val = left_val * lazy[first];\n      right_val\
    \ = right_val * lazy[last];\n    }\n    return left_val + right_val;\n  }\n\n\
    \  /**\n   * @return Sum of all elements.\n   */\n  _Monoid fold() {\n    repair();\n\
    \    return data[1];\n  }\n\n  /**\n   * @brief Binary search for the partition\
    \ point.\n   * @param __r Right fixed end of the interval, exclusive\n   * @param\
    \ __pred Predicate in the form of 'bool(_Monoid)'\n   * @return Left end of the\
    \ extremal interval satisfying the condition,\n   * inclusive.\n   */\n  template\
    \ <class _Pred> size_t left_partition(size_t __r, _Pred __pred) {\n    assert(__r\
    \ <= size_orig);\n    repair();\n    __r += size_ext - 1;\n    for (size_t i{height};\
    \ i; --i) push(__r >> i);\n    ++__r;\n    _Monoid mono{};\n    for (size_t __l{size_ext},\
    \ step{}; __l != __r;\n         __l >>= 1, __r >>= 1, ++step) {\n      if ((__l\
    \ & 1) != (__r & 1)) {\n        const _Monoid __tmp = data[--__r] + mono;\n  \
    \      if (!__pred(__tmp))\n          return left_partition_subtree(__r, std::move(mono),\
    \ __pred);\n        mono = std::move(__tmp);\n      }\n    }\n    return 0;\n\
    \  }\n\n  /**\n   * @brief Binary search for the partition point.\n   * @param\
    \ __l Left fixed end of the interval, inclusive\n   * @param __pred Predicate\
    \ in the form of 'bool(_Monoid)'\n   * @return Right end of the extremal interval\
    \ satisfying the condition,\n   * exclusive.\n   */\n  template <class _Pred>\
    \ size_t right_partition(size_t __l, _Pred __pred) {\n    assert(__l <= size_orig);\n\
    \    repair();\n    __l += size_ext;\n    for (size_t i{height}; i; --i) push(__l\
    \ >> i);\n    _Monoid mono{};\n    for (size_t __r{size_ext << 1}, step{}; __l\
    \ != __r;\n         __l >>= 1, __r >>= 1, ++step) {\n      if ((__l & 1) != (__r\
    \ & 1)) {\n        const _Monoid __tmp = mono + data[__l];\n        if (!__pred(__tmp))\n\
    \          return right_partition_subtree(__l, std::move(mono), __pred);\n   \
    \     mono = std::move(__tmp);\n        ++__l;\n      }\n    }\n    return size_orig;\n\
    \  }\n};\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file lazy.hpp\n * @brief Lazy Segment Tree\n */\n\
    \n#include <cassert>\n#include <queue>\n#include <vector>\n\n#include \"src/algebra/system/monoid.hpp\"\
    \n#include \"src/algebra/system/operation.hpp\"\n#include \"src/utils/sfinae.hpp\"\
    \n#include \"waitings.hpp\"\n\nnamespace workspace {\n\ntemplate <class _Monoid,\
    \ class _End,\n          class Monoid_container = std::vector<_Monoid>,\n    \
    \      class Endomorphism_container = std::vector<_End>>\nclass lazy_segment_tree\
    \ {\n  static_assert(\n      std::is_same<_Monoid, typename Monoid_container::value_type>::value);\n\
    \n  static_assert(\n      std::is_same<_End, typename Endomorphism_container::value_type>::value);\n\
    \n  static_assert(has_binary_plus<_Monoid>::value,\n                \"\\'_Monoid\\\
    ' has no proper binary \\'operator+\\'.\");\n\n  static_assert(has_binary_multiplies<_End>::value,\n\
    \                \"\\'_End\\' has no proper binary \\'operator*\\'.\");\n\n  static_assert(has_binary_multiplies<_Monoid,\
    \ _End>::value,\n                \"\\'_End\\' is not applicable to \\'_Monoid\\\
    '.\");\n\n  size_t size_orig, height, size_ext;\n  Monoid_container data;\n  Endomorphism_container\
    \ lazy;\n  internal::waitings wait;\n\n  void repair() {\n    while (!wait.empty())\
    \ {\n      const size_t __i = wait.pop() >> 1;\n      if (__i && wait.push(__i))\
    \ pull(__i);\n    }\n  }\n\n  void _apply(size_t node, const _End &__e) {\n  \
    \  data[node] = data[node] * __e;\n    if (node < size_ext) lazy[node] = lazy[node]\
    \ * __e;\n  }\n\n  void push(size_t node) {\n    _apply(node << 1, lazy[node]);\n\
    \    _apply(node << 1 | 1, lazy[node]);\n    lazy[node] = _End{};\n  }\n\n  void\
    \ pull(size_t node) { data[node] = data[node << 1] + data[node << 1 | 1]; }\n\n\
    \  template <class _Pred>\n  size_t left_partition_subtree(size_t node, _Monoid\
    \ mono, _Pred __pred) {\n    assert(node);\n    while (node < size_ext) {\n  \
    \    push(node);\n      const _Monoid __tmp = data[(node <<= 1) | 1] + mono;\n\
    \      if (__pred(__tmp))\n        mono = std::move(__tmp);\n      else\n    \
    \    ++node;\n    }\n    return ++node -= size_ext;\n  }\n\n  template <class\
    \ _Pred>\n  size_t right_partition_subtree(size_t node, _Monoid mono, _Pred __pred)\
    \ {\n    assert(node);\n    while (node < size_ext) {\n      push(node);\n   \
    \   const _Monoid __tmp = mono + data[node <<= 1];\n      if (__pred(__tmp)) ++node,\
    \ mono = std::move(__tmp);\n    }\n    return (node -= size_ext) < size_orig ?\
    \ node : size_orig;\n  }\n\n public:\n  class iterator {\n    lazy_segment_tree\
    \ *__p;\n    size_t __i;\n\n   public:\n    using difference_type = typename std::make_signed<size_t>::type;\n\
    \    using value_type = _Monoid;\n    using reference = _Monoid &;\n    using\
    \ pointer = iterator;\n    using iterator_category = std::random_access_iterator_tag;\n\
    \n    /**\n     * @brief Construct a new iterator object\n     *\n     */\n  \
    \  iterator() = default;\n\n    /**\n     * @brief Construct a new iterator object\n\
    \     *\n     * @param __p Pointer to a segment tree object\n     * @param __i\
    \ Index\n     */\n    iterator(lazy_segment_tree *__p, size_t __i) : __p(__p),\
    \ __i(__i) {}\n\n    bool operator==(iterator const &rhs) const {\n      return\
    \ __p == rhs.__p && __i == rhs.__i;\n    }\n    bool operator!=(iterator const\
    \ &rhs) const { return !operator==(rhs); }\n\n    bool operator<(iterator const\
    \ &rhs) const { return __i < rhs.__i; }\n    bool operator>(iterator const &rhs)\
    \ const { return __i > rhs.__i; }\n    bool operator<=(iterator const &rhs) const\
    \ { return __i <= rhs.__i; }\n    bool operator>=(iterator const &rhs) const {\
    \ return __i >= rhs.__i; }\n\n    iterator &operator++() { return ++__i, *this;\
    \ }\n    iterator &operator--() { return --__i, *this; }\n\n    difference_type\
    \ operator-(iterator const &rhs) const {\n      return __i - rhs.__i;\n    }\n\
    \n    /**\n     * @brief\n     *\n     * @return reference\n     */\n    reference\
    \ operator*() const { return __p->operator[](__i); }\n  };\n\n  using value_type\
    \ = typename iterator::value_type;\n  using reference = typename iterator::reference;\n\
    \n  iterator begin() { return {this, 0}; }\n  iterator end() { return {this, size_orig};\
    \ }\n\n  auto rbegin() { return std::make_reverse_iterator(end()); }\n  auto rend()\
    \ { return std::make_reverse_iterator(begin()); }\n\n  lazy_segment_tree(size_t\
    \ __n = 0)\n      : size_orig{__n},\n        height(__n > 1 ? 32 - __builtin_clz(__n\
    \ - 1) : 0),\n        size_ext{1u << height},\n        data(size_ext << 1),\n\
    \        lazy(size_ext),\n        wait(size_ext << 1) {}\n\n  lazy_segment_tree(size_t\
    \ __n, const _Monoid &init) : lazy_segment_tree(__n) {\n    std::fill_n(std::next(std::begin(data),\
    \ size_ext), __n, init);\n    for (size_t i{size_ext}; --i;) pull(i);\n  }\n\n\
    \  template <class iter_type, class value_type = typename std::iterator_traits<\n\
    \                                 iter_type>::value_type>\n  lazy_segment_tree(iter_type\
    \ first, iter_type last)\n      : size_orig(std::distance(first, last)),\n   \
    \     height(size_orig > 1 ? 32 - __builtin_clz(size_orig - 1) : 0),\n       \
    \ size_ext{1u << height},\n        data(size_ext << 1),\n        lazy(size_ext),\n\
    \        wait(size_ext << 1) {\n    static_assert(std::is_constructible<_Monoid,\
    \ value_type>::value,\n                  \"_Monoid(iter_type::value_type) is not\
    \ constructible.\");\n    for (auto iter{std::next(std::begin(data), size_ext)};\n\
    \         iter != std::end(data) && first != last; ++iter, ++first)\n      *iter\
    \ = _Monoid(*first);\n    for (size_t i{size_ext}; --i;) pull(i);\n  }\n\n  /**\n\
    \   * @return Number of elements.\n   */\n  size_t size() const { return size_orig;\
    \ }\n\n  /**\n   * @param __i Index of the element\n   * @return Reference to\
    \ the element.\n   */\n  _Monoid &operator[](size_t __i) {\n    assert(__i < size_orig);\n\
    \    __i |= size_ext;\n    wait.push(__i);\n    for (size_t i = height; i; --i)\
    \ push(__i >> i);\n    return data[__i];\n  }\n\n  void apply(const _End &__e)\
    \ { apply(0, size_orig, __e); }\n\n  void apply(size_t __i, const _End &__e) {\
    \ apply(__i, __i + 1, __e); }\n\n  void apply(size_t first, size_t last, const\
    \ _End &__e) {\n    assert(last <= size_orig);\n    repair();\n    if (first >=\
    \ last) return;\n    first += size_ext, last += size_ext;\n    --last;\n    for\
    \ (size_t i = height; i; --i) push(first >> i), push(last >> i);\n    ++last;\n\
    \    for (size_t l = first, r = last; l != r; l >>= 1, r >>= 1) {\n      if (l\
    \ & 1) _apply(l++, __e);\n      if (r & 1) _apply(--r, __e);\n    }\n    for (first\
    \ >>= __builtin_ffs(first); first; first >>= 1) pull(first);\n    for (last >>=\
    \ __builtin_ffs(last); last; last >>= 1) pull(last);\n  }\n\n  /**\n   * @param\
    \ first Left end, inclusive\n   * @param last Right end, exclusive\n   * @return\
    \ Sum of elements in the interval.\n   */\n  _Monoid fold(size_t first, size_t\
    \ last) {\n    assert(last <= size_orig);\n    repair();\n    if (first >= last)\
    \ return _Monoid{};\n    first += size_ext, last += size_ext - 1;\n    _Monoid\
    \ left_val{}, right_val{};\n    for (size_t l = first, r = last + 1; l != r; l\
    \ >>= 1, r >>= 1) {\n      if (l & 1) left_val = left_val + data[l++];\n     \
    \ if (r & 1) right_val = data[--r] + right_val;\n      left_val = left_val * lazy[first\
    \ >>= 1];\n      right_val = right_val * lazy[last >>= 1];\n    }\n    while (first\
    \ >>= 1, last >>= 1) {\n      left_val = left_val * lazy[first];\n      right_val\
    \ = right_val * lazy[last];\n    }\n    return left_val + right_val;\n  }\n\n\
    \  /**\n   * @return Sum of all elements.\n   */\n  _Monoid fold() {\n    repair();\n\
    \    return data[1];\n  }\n\n  /**\n   * @brief Binary search for the partition\
    \ point.\n   * @param __r Right fixed end of the interval, exclusive\n   * @param\
    \ __pred Predicate in the form of 'bool(_Monoid)'\n   * @return Left end of the\
    \ extremal interval satisfying the condition,\n   * inclusive.\n   */\n  template\
    \ <class _Pred> size_t left_partition(size_t __r, _Pred __pred) {\n    assert(__r\
    \ <= size_orig);\n    repair();\n    __r += size_ext - 1;\n    for (size_t i{height};\
    \ i; --i) push(__r >> i);\n    ++__r;\n    _Monoid mono{};\n    for (size_t __l{size_ext},\
    \ step{}; __l != __r;\n         __l >>= 1, __r >>= 1, ++step) {\n      if ((__l\
    \ & 1) != (__r & 1)) {\n        const _Monoid __tmp = data[--__r] + mono;\n  \
    \      if (!__pred(__tmp))\n          return left_partition_subtree(__r, std::move(mono),\
    \ __pred);\n        mono = std::move(__tmp);\n      }\n    }\n    return 0;\n\
    \  }\n\n  /**\n   * @brief Binary search for the partition point.\n   * @param\
    \ __l Left fixed end of the interval, inclusive\n   * @param __pred Predicate\
    \ in the form of 'bool(_Monoid)'\n   * @return Right end of the extremal interval\
    \ satisfying the condition,\n   * exclusive.\n   */\n  template <class _Pred>\
    \ size_t right_partition(size_t __l, _Pred __pred) {\n    assert(__l <= size_orig);\n\
    \    repair();\n    __l += size_ext;\n    for (size_t i{height}; i; --i) push(__l\
    \ >> i);\n    _Monoid mono{};\n    for (size_t __r{size_ext << 1}, step{}; __l\
    \ != __r;\n         __l >>= 1, __r >>= 1, ++step) {\n      if ((__l & 1) != (__r\
    \ & 1)) {\n        const _Monoid __tmp = mono + data[__l];\n        if (!__pred(__tmp))\n\
    \          return right_partition_subtree(__l, std::move(mono), __pred);\n   \
    \     mono = std::move(__tmp);\n        ++__l;\n      }\n    }\n    return size_orig;\n\
    \  }\n};\n\n}  // namespace workspace\n"
  dependsOn:
  - src/algebra/system/monoid.hpp
  - src/algebra/system/operation.hpp
  - src/utils/sfinae.hpp
  - src/data_structure/segment_tree/waitings.hpp
  isVerificationFile: false
  path: src/data_structure/segment_tree/lazy.hpp
  requiredBy: []
  timestamp: '2022-04-06 15:02:09+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/range_affine_range_sum.test.cpp
  - test/aizu-online-judge/2450.test.cpp
documentation_of: src/data_structure/segment_tree/lazy.hpp
layout: document
redirect_from:
- /library/src/data_structure/segment_tree/lazy.hpp
- /library/src/data_structure/segment_tree/lazy.hpp.html
title: Lazy Segment Tree
---
