---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/string/suffix_array.hpp
    title: Suffix Array
  - icon: ':heavy_check_mark:'
    path: src/utils/iterator/category.hpp
    title: Iterator Category
  - icon: ':heavy_check_mark:'
    path: src/utils/iterator/reverse.hpp
    title: Reverse Iterator
  - icon: ':heavy_check_mark:'
    path: src/utils/py-like/zip.hpp
    title: Zip
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
    PROBLEM: https://judge.yosupo.jp/problem/number_of_substrings
    links:
    - https://judge.yosupo.jp/problem/number_of_substrings
  bundledCode: "#line 1 \"test/library-checker/number_of_substrings.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/number_of_substrings\"\n\n#include\
    \ <iostream>\n\n#line 2 \"src/string/suffix_array.hpp\"\n\n/*\n * @file suffix_array.hpp\n\
    \ * @brief Suffix Array\n */\n\n#include <algorithm>\n#include <numeric>\n#include\
    \ <vector>\n\n#line 2 \"src/utils/sfinae.hpp\"\n\n/**\n * @file sfinae.hpp\n *\
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
    }  // namespace workspace\n#line 13 \"src/string/suffix_array.hpp\"\n\nnamespace\
    \ workspace {\n\n/*\n * @class suffix_array\n * @brief construct SA and LCP array.\n\
    \ * @tparam str_type the type of string\n */\ntemplate <class str_type> class\
    \ suffix_array {\n  str_type str;\n  std::vector<size_t> sa, rank, lcp;\n\n  void\
    \ construct_sa() {\n    std::iota(sa.begin(), sa.end(), 0);\n    std::sort(sa.begin(),\
    \ sa.end(),\n              [&](size_t i, size_t j) { return str[i] < str[j]; });\n\
    \n    for (size_t r{1}, c{}, *ptr{&sa.front()}, *tmp{ptr}; c != size();\n    \
    \     ++r, ptr = tmp)\n      while (c != size() && str[*ptr] == str[*tmp]) ++c,\
    \ rank[*tmp++] = r;\n\n    for (size_t k{1}; k < size(); k <<= 1) {\n      auto\
    \ comp = [&](size_t i, size_t j) -> bool {\n        if (rank[i] != rank[j]) return\
    \ rank[i] < rank[j];\n        return (i + k < size() ? rank[i + k] : 0) <\n  \
    \             (j + k < size() ? rank[j + k] : 0);\n      };\n      std::sort(sa.begin(),\
    \ sa.end(), comp);\n\n      std::vector<size_t> next_rank(size());\n      for\
    \ (size_t r{1}, c{}, *ptr{&sa.front()}, *tmp{ptr}; c != size();\n           ++r,\
    \ ptr = tmp)\n        while (c != size() && !comp(*ptr, *tmp)) ++c, next_rank[*tmp++]\
    \ = r;\n      rank.swap(next_rank);\n    }\n\n    sa.emplace(sa.begin(), size());\n\
    \    rank.emplace_back(0);\n  }\n\n  void construct_lcp() {\n    for (size_t i{},\
    \ h{}; i != size(); ++i, h = h ? h - 1 : 0) {\n      for (size_t j{sa[rank[i]\
    \ - 1] + h}; i + h != size() && j != size();\n           ++j, ++h)\n        if\
    \ (str[i + h] != str[j]) break;\n      lcp[rank[i] - 1] = h;\n    }\n  }\n\n public:\n\
    \  static constexpr size_t npos = -1;\n  using char_type = element_type<str_type>;\n\
    \n  std::vector<size_t>::const_iterator begin() const { return sa.begin() + 1;\
    \ }\n\n  std::vector<size_t>::const_iterator end() const { return sa.end(); }\n\
    \n  /*\n   * @fn operator[]\n   * @brief find the i-th suffix\n   * @param i the\
    \ rank\n   * @return index of the suffix\n   */\n  size_t operator[](size_t i)\
    \ const { return sa[i + 1]; }\n\n  /*\n   * @fn size\n   * @return length of the\
    \ string\n   */\n  size_t size() const { return std::size(str); }\n\n  template\
    \ <class type = str_type, typename = typename type::value_type>\n  suffix_array(const\
    \ str_type &_str)\n      : str(_str), sa(size()), rank(size()), lcp(size()) {\n\
    \    construct_sa();\n    construct_lcp();\n  }\n\n  template <class type = str_type,\
    \ std::enable_if_t<std::is_array<type>::value,\n                             \
    \                       std::nullptr_t> = nullptr>\n  suffix_array(const str_type\
    \ &_str) : sa(size()), rank(size()), lcp(size()) {\n    std::copy(std::begin(_str),\
    \ std::end(_str), str);\n    construct_sa();\n    construct_lcp();\n  }\n\n  /*\n\
    \   * @fn find\n   * @brief find (key) as a substring\n   * @param key\n   * @return\
    \ index if found, npos if not found\n   */\n  size_t find(const str_type &key)\
    \ const {\n    using std::begin;\n    using std::end;\n\n    size_t lower{npos},\
    \ upper{size()};\n    while (upper - lower > 1) {\n      size_t mid = (lower +\
    \ upper) >> 1;\n      bool less = false;\n      for (auto i{begin(str) + sa[mid]},\
    \ j{begin(key)}; j != end(key);\n           ++i, ++j) {\n        if (i == end(str)\
    \ || *i < *j) {\n          less = true;\n          break;\n        }\n       \
    \ if (*i > *j) break;\n      }\n      (less ? lower : upper) = mid;\n    }\n\n\
    \    if (upper == size()) return npos;\n    for (auto i{begin(str) + sa[upper]},\
    \ j{begin(key)}; j != end(key); ++i, ++j)\n      if (i == end(str) || *i != *j)\
    \ return npos;\n    return sa[upper];\n  }\n\n  /*\n   * @return lengths of LCP\
    \ of each adjacent pairs in the suffix\n   * array\n   */\n  const std::vector<size_t>\
    \ &lcp_array() const { return lcp; }\n};\n\n}  // namespace workspace\n#line 2\
    \ \"src/utils/py-like/zip.hpp\"\n\n/**\n * @file zip.hpp\n * @brief Zip\n */\n\
    \n#include <cstddef>\n#include <tuple>\n#line 11 \"src/utils/py-like/zip.hpp\"\
    \n\n#line 2 \"src/utils/iterator/category.hpp\"\n\n/*\n * @file category.hpp\n\
    \ * @brief Iterator Category\n */\n\n#line 10 \"src/utils/iterator/category.hpp\"\
    \n\nnamespace workspace {\n\n/*\n * @tparam Tuple Tuple of iterator types\n */\n\
    template <class Tuple, size_t N = std::tuple_size<Tuple>::value - 1>\nstruct common_iterator_category\
    \ {\n  using type = typename std::common_type<\n      typename common_iterator_category<Tuple,\
    \ N - 1>::type,\n      typename std::iterator_traits<typename std::tuple_element<\n\
    \          N, Tuple>::type>::iterator_category>::type;\n};\n\ntemplate <class\
    \ Tuple> struct common_iterator_category<Tuple, 0> {\n  using type = typename\
    \ std::iterator_traits<\n      typename std::tuple_element<0, Tuple>::type>::iterator_category;\n\
    };\n\n}  // namespace workspace\n#line 2 \"src/utils/iterator/reverse.hpp\"\n\n\
    /*\n * @file reverse_iterator.hpp\n * @brief Reverse Iterator\n */\n\n#if __cplusplus\
    \ >= 201703L\n\n#line 11 \"src/utils/iterator/reverse.hpp\"\n#include <optional>\n\
    \nnamespace workspace {\n\n/*\n * @class reverse_iterator\n * @brief Wrapper class\
    \ for `std::reverse_iterator`.\n * @see http://gcc.gnu.org/PR51823\n */\ntemplate\
    \ <class Iterator>\nclass reverse_iterator : public std::reverse_iterator<Iterator>\
    \ {\n  using base_std = std::reverse_iterator<Iterator>;\n  std::optional<typename\
    \ base_std::value_type> deref;\n\n public:\n  using base_std::reverse_iterator;\n\
    \n  constexpr typename base_std::reference operator*() noexcept {\n    if (!deref)\
    \ {\n      Iterator tmp = base_std::current;\n      deref = *--tmp;\n    }\n \
    \   return deref.value();\n  }\n\n  constexpr reverse_iterator &operator++() noexcept\
    \ {\n    base_std::operator++();\n    deref.reset();\n    return *this;\n  }\n\
    \  constexpr reverse_iterator &operator--() noexcept {\n    base_std::operator++();\n\
    \    deref.reset();\n    return *this;\n  }\n  constexpr reverse_iterator operator++(int)\
    \ noexcept {\n    base_std::operator++();\n    deref.reset();\n    return *this;\n\
    \  }\n  constexpr reverse_iterator operator--(int) noexcept {\n    base_std::operator++();\n\
    \    deref.reset();\n    return *this;\n  }\n};\n\n}  // namespace workspace\n\
    \n#endif\n#line 2 \"lib/cxx17\"\n\n#line 2 \"lib/cxx14\"\n\n#ifndef _CXX14_CONSTEXPR\n\
    #if __cplusplus >= 201402L\n#define _CXX14_CONSTEXPR constexpr\n#else\n#define\
    \ _CXX14_CONSTEXPR\n#endif\n#endif\n#line 4 \"lib/cxx17\"\n\n#ifndef _CXX17_CONSTEXPR\n\
    #if __cplusplus >= 201703L\n#define _CXX17_CONSTEXPR constexpr\n#else\n#define\
    \ _CXX17_CONSTEXPR\n#endif\n#endif\n\n#ifndef _CXX17_STATIC_ASSERT\n#if __cplusplus\
    \ >= 201703L\n#define _CXX17_STATIC_ASSERT static_assert\n#else\n#define _CXX17_STATIC_ASSERT\
    \ assert\n#endif\n#endif\n\n#line 22 \"lib/cxx17\"\n\n#if __cplusplus < 201703L\n\
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
    \n#include <variant>\n\n#endif\n#line 15 \"src/utils/py-like/zip.hpp\"\n\nnamespace\
    \ workspace {\n\ntemplate <class _Tuple> class zipped : protected _Tuple {\n public:\n\
    \  zipped(const _Tuple &__x) : _Tuple(__x) {}\n\n  template <std::size_t _Nm>\
    \ constexpr decltype(auto) get() const &noexcept {\n    return *std::get<_Nm>(*this);\n\
    \  }\n\n  template <std::size_t _Nm> constexpr decltype(auto) get() &&noexcept\
    \ {\n    auto __tmp = *std::get<_Nm>(*this);\n    return __tmp;\n  }\n};\n\ntemplate\
    \ <class... _Containers> class zip {\n  std::tuple<_Containers...> __c;\n\n  template\
    \ <std::size_t _Nm = 0>\n  constexpr decltype(auto) begin_cat() const noexcept\
    \ {\n    if _CXX17_CONSTEXPR (_Nm != sizeof...(_Containers)) {\n      return std::tuple_cat(std::tuple(std::begin(std::get<_Nm>(__c))),\n\
    \                            begin_cat<_Nm + 1>());\n    } else\n      return\
    \ std::tuple<>();\n  }\n\n  template <std::size_t _Nm = 0>\n  constexpr decltype(auto)\
    \ end_cat() const noexcept {\n    if _CXX17_CONSTEXPR (_Nm != sizeof...(_Containers))\
    \ {\n      return std::tuple_cat(std::tuple(std::end(std::get<_Nm>(__c))),\n \
    \                           end_cat<_Nm + 1>());\n    } else\n      return std::tuple<>();\n\
    \  }\n\n  using _Iterator_tuple =\n      std::tuple<decltype(std::begin(std::declval<_Containers>()))...>;\n\
    \n public:\n  using size_type = std::size_t;\n\n  class iterator : public zipped<_Iterator_tuple>\
    \ {\n    using _Base = zipped<_Iterator_tuple>;\n\n   public:\n    using difference_type\
    \ = std::ptrdiff_t;\n    using value_type = _Base;\n    using pointer = void;\n\
    \    using reference = value_type &;\n    using iterator_category =\n        typename\
    \ common_iterator_category<_Iterator_tuple>::type;\n\n   protected:\n    template\
    \ <std::size_t _Nm = 0>\n    constexpr bool equal(const iterator &__x) const noexcept\
    \ {\n      if _CXX17_CONSTEXPR (_Nm != sizeof...(_Containers)) {\n        return\
    \ std::get<_Nm>(*this) == std::get<_Nm>(__x) ||\n               equal<_Nm + 1>(__x);\n\
    \      } else\n        return false;\n    }\n\n    template <std::size_t _Nm =\
    \ 0> constexpr void increment() noexcept {\n      if _CXX17_CONSTEXPR (_Nm !=\
    \ sizeof...(_Containers))\n        ++std::get<_Nm>(*this), increment<_Nm + 1>();\n\
    \    }\n\n    template <std::size_t _Nm = 0> constexpr void decrement() noexcept\
    \ {\n      if _CXX17_CONSTEXPR (_Nm != sizeof...(_Containers))\n        --std::get<_Nm>(*this),\
    \ decrement<_Nm + 1>();\n    }\n\n    template <std::size_t _Nm = 0>\n    constexpr\
    \ void advance(difference_type __d) noexcept {\n      if _CXX17_CONSTEXPR (_Nm\
    \ != sizeof...(_Containers))\n        std::get<_Nm>(*this) += __d, advance<_Nm\
    \ + 1>(__d);\n    }\n\n   public:\n    iterator(const _Iterator_tuple &__x) :\
    \ _Base(__x) {}\n\n    constexpr bool operator==(const iterator &__x) const noexcept\
    \ {\n      return equal(__x);\n    }\n    constexpr bool operator!=(const iterator\
    \ &__x) const noexcept {\n      return !equal(__x);\n    }\n\n    constexpr iterator\
    \ &operator++() noexcept {\n      increment();\n      return *this;\n    }\n \
    \   constexpr iterator operator++(int) noexcept {\n      auto __tmp = *this;\n\
    \      increment();\n      return __tmp;\n    }\n\n    constexpr iterator &operator--()\
    \ noexcept {\n      decrement();\n      return *this;\n    }\n    constexpr iterator\
    \ operator--(int) noexcept {\n      auto __tmp = *this;\n      decrement();\n\
    \      return __tmp;\n    }\n\n    constexpr bool operator<(const iterator &__x)\
    \ const noexcept {\n      return std::get<0>(*this) < std::get<0>(__x);\n    }\n\
    \    constexpr bool operator<=(const iterator &__x) const noexcept {\n      return\
    \ std::get<0>(*this) <= std::get<0>(__x);\n    }\n    constexpr bool operator>(const\
    \ iterator &__x) const noexcept {\n      return !operator<=(__x);\n    }\n   \
    \ constexpr bool operator>=(const iterator &__x) const noexcept {\n      return\
    \ !operator>(__x);\n    }\n\n    constexpr iterator &operator+=(difference_type\
    \ __d) noexcept {\n      advance(__d);\n      return *this;\n    }\n    constexpr\
    \ iterator &operator-=(difference_type __d) noexcept {\n      advance(-__d);\n\
    \      return *this;\n    }\n    constexpr iterator operator+(difference_type\
    \ __d) const noexcept {\n      return iterator{*this} += __d;\n    }\n    constexpr\
    \ iterator operator-(difference_type __d) const noexcept {\n      return iterator{*this}\
    \ -= __d;\n    }\n\n    constexpr difference_type operator-(const iterator &__x)\
    \ const noexcept {\n      return std::get<0>(*this) - std::get<0>(__x);\n    }\n\
    \n    constexpr reference operator*() noexcept { return {*this}; }\n  };\n\n \
    \ using const_iterator = iterator;\n\n  template <class... _Args>\n  constexpr\
    \ zip(_Args &&...__args) noexcept\n      : __c(std::forward<_Args>(__args)...)\
    \ {}\n\n  template <class... _Args>\n  constexpr zip(std::initializer_list<_Args>...\
    \ __args) noexcept\n      : __c(std::forward<_Args>(__args)...) {}\n\n  constexpr\
    \ iterator begin() const noexcept { return {begin_cat()}; }\n\n  constexpr iterator\
    \ end() const noexcept { return {end_cat()}; }\n\n  constexpr reverse_iterator<iterator>\
    \ rbegin() const noexcept {\n    return reverse_iterator<iterator>{end()};\n \
    \ }\n\n  constexpr reverse_iterator<iterator> rend() const noexcept {\n    return\
    \ reverse_iterator<iterator>{begin()};\n  }\n\n#if __cplusplus >= 201703L\n  constexpr\
    \ size_type size() const noexcept {\n    size_type __n = -1;\n    std::apply(\n\
    \        [&__n](auto &&__x) {\n          if (__n < __x.size()) __n = __x.size();\n\
    \        },\n        __c);\n    return __n;\n  }\n#endif\n};\n\n#if __cpp_deduction_guides\
    \ >= 201606L\n\ntemplate <class... _Args> zip(_Args &&...) -> zip<_Args...>;\n\
    \n// For gcc version < 10\n// https://gcc.gnu.org/bugzilla/show_bug.cgi?id=80438\n\
    template <class _Tp, class... _Args>\nzip(_Tp &&, _Args &&...) -> zip<_Tp, _Args...>;\n\
    \ntemplate <class... _Args>\nzip(std::initializer_list<_Args>...) -> zip<std::initializer_list<_Args>...>;\n\
    \n#endif\n\n}  // namespace workspace\n\nnamespace std {\n\ntemplate <size_t _Nm,\
    \ class _Tuple>\nstruct tuple_element<_Nm, workspace::zipped<_Tuple>> {\n  using\
    \ type = remove_reference_t<\n      typename iterator_traits<tuple_element_t<_Nm,\
    \ _Tuple>>::reference>;\n};\n\ntemplate <class _Tuple>\nstruct tuple_size<workspace::zipped<_Tuple>>\
    \ : tuple_size<_Tuple> {};\n\n}  // namespace std\n#line 7 \"test/library-checker/number_of_substrings.test.cpp\"\
    \n\nint main() {\n  std::string s;\n  std::cin >> s;\n  workspace::suffix_array\
    \ sa(s);\n  long long ans = 0;\n  for (auto &&[x, y] : workspace::zip(sa, sa.lcp_array()))\
    \ {\n    ans += s.size() - x - y;\n  }\n  printf(\"%lld\\n\", ans);\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/number_of_substrings\"\n\
    \n#include <iostream>\n\n#include \"src/string/suffix_array.hpp\"\n#include \"\
    src/utils/py-like/zip.hpp\"\n\nint main() {\n  std::string s;\n  std::cin >> s;\n\
    \  workspace::suffix_array sa(s);\n  long long ans = 0;\n  for (auto &&[x, y]\
    \ : workspace::zip(sa, sa.lcp_array())) {\n    ans += s.size() - x - y;\n  }\n\
    \  printf(\"%lld\\n\", ans);\n}\n"
  dependsOn:
  - src/string/suffix_array.hpp
  - src/utils/sfinae.hpp
  - src/utils/py-like/zip.hpp
  - src/utils/iterator/category.hpp
  - src/utils/iterator/reverse.hpp
  isVerificationFile: true
  path: test/library-checker/number_of_substrings.test.cpp
  requiredBy: []
  timestamp: '2022-04-06 16:00:36+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/library-checker/number_of_substrings.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/number_of_substrings.test.cpp
- /verify/test/library-checker/number_of_substrings.test.cpp.html
title: test/library-checker/number_of_substrings.test.cpp
---
