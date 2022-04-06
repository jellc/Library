---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/utils/iterator/category.hpp
    title: Iterator Category
  - icon: ':heavy_check_mark:'
    path: src/utils/iterator/reverse.hpp
    title: Reverse Iterator
  - icon: ':warning:'
    path: src/utils/py-like/range.hpp
    title: Range
  - icon: ':warning:'
    path: src/utils/py-like/reversed.hpp
    title: Reversed
  - icon: ':heavy_check_mark:'
    path: src/utils/py-like/zip.hpp
    title: Zip
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Enumerate
    links: []
  bundledCode: "#line 2 \"src/utils/py-like/enumerate.hpp\"\n\n/**\n * @file enumerate.hpp\n\
    \ * @brief Enumerate\n */\n\n#line 2 \"src/utils/py-like/range.hpp\"\n\n/**\n\
    \ * @file range.hpp\n * @brief Range\n */\n\n#line 2 \"src/utils/py-like/reversed.hpp\"\
    \n\n/**\n * @file reversed.hpp\n * @brief Reversed\n */\n\n#include <vector>\n\
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
    \n#include <variant>\n\n#endif\n#line 11 \"src/utils/py-like/reversed.hpp\"\n\n\
    namespace workspace {\n\n// Reversed container.\ntemplate <class _Container> class\
    \ reversed {\n  _Container __c;\n\n public:\n  template <class _Tp>\n  constexpr\
    \ reversed(_Tp &&__x) noexcept : __c(std::forward<_Container>(__x)) {}\n\n  template\
    \ <class _Tp>\n  constexpr reversed(std::initializer_list<_Tp> __x) noexcept :\
    \ __c(__x) {}\n\n  constexpr decltype(auto) begin() noexcept { return std::rbegin(__c);\
    \ }\n  constexpr decltype(auto) begin() const noexcept { return std::rbegin(__c);\
    \ }\n\n  constexpr decltype(auto) end() noexcept { return std::rend(__c); }\n\
    \  constexpr decltype(auto) end() const noexcept { return std::rend(__c); }\n\n\
    \  constexpr bool empty() const noexcept { return std::empty(__c); }\n\n  constexpr\
    \ decltype(auto) size() const noexcept { return std::size(__c); }\n\n  using iterator\
    \ = decltype(std::rbegin(__c));\n  using const_iterator = decltype(std::crbegin(__c));\n\
    \n  using size_type = decltype(std::size(__c));\n  using difference_type =\n \
    \     typename std::iterator_traits<iterator>::difference_type;\n  using value_type\
    \ = typename std::iterator_traits<iterator>::value_type;\n\n  using reference\
    \ = typename std::iterator_traits<iterator>::reference;\n  using const_reference\
    \ =\n      typename std::iterator_traits<const_iterator>::reference;\n};\n\n#if\
    \ __cpp_deduction_guides >= 201606L\n\ntemplate <class _Tp> reversed(_Tp &&) ->\
    \ reversed<_Tp>;\n\ntemplate <class _Tp>\nreversed(std::initializer_list<_Tp>)\
    \ -> reversed<std::initializer_list<_Tp>>;\n\n#endif\n\n}  // namespace workspace\n\
    #line 9 \"src/utils/py-like/range.hpp\"\n\nnamespace workspace {\n\ntemplate <class\
    \ _Index> class range {\n  _Index __first, __last;\n\n public:\n  class iterator\
    \ {\n    _Index __i;\n\n   public:\n    using difference_type = std::ptrdiff_t;\n\
    \    using value_type = _Index;\n    using pointer = void;\n    using reference\
    \ = value_type;\n    using iterator_category = std::random_access_iterator_tag;\n\
    \n    constexpr iterator() = default;\n    constexpr iterator(const _Index &__x)\
    \ noexcept : __i(__x) {}\n\n    constexpr bool operator==(const iterator &__x)\
    \ const noexcept {\n      return __i == __x.__i;\n    }\n    constexpr bool operator!=(const\
    \ iterator &__x) const noexcept {\n      return __i != __x.__i;\n    }\n\n   \
    \ constexpr bool operator<(const iterator &__x) const noexcept {\n      return\
    \ __i < __x.__i;\n    }\n    constexpr bool operator<=(const iterator &__x) const\
    \ noexcept {\n      return __i <= __x.__i;\n    }\n\n    constexpr bool operator>(const\
    \ iterator &__x) const noexcept {\n      return __i > __x.__i;\n    }\n    constexpr\
    \ bool operator>=(const iterator &__x) const noexcept {\n      return __i >= __x.__i;\n\
    \    }\n\n    constexpr iterator &operator++() noexcept {\n      ++__i;\n    \
    \  return *this;\n    }\n    constexpr iterator operator++(int) noexcept {\n \
    \     auto __tmp = *this;\n      ++__i;\n      return __tmp;\n    }\n\n    constexpr\
    \ iterator &operator--() noexcept {\n      --__i;\n      return *this;\n    }\n\
    \    constexpr iterator operator--(int) noexcept {\n      auto __tmp = *this;\n\
    \      --__i;\n      return __tmp;\n    }\n\n    constexpr difference_type operator-(const\
    \ iterator &__x) const noexcept {\n      return __i - __x.__i;\n    }\n\n    constexpr\
    \ iterator &operator+=(difference_type __x) noexcept {\n      __i += __x;\n  \
    \    return *this;\n    }\n    constexpr iterator operator+(difference_type __x)\
    \ const noexcept {\n      return iterator(*this) += __x;\n    }\n\n    constexpr\
    \ iterator &operator-=(difference_type __x) noexcept {\n      __i -= __x;\n  \
    \    return *this;\n    }\n    constexpr iterator operator-(difference_type __x)\
    \ const noexcept {\n      return iterator(*this) -= __x;\n    }\n\n    constexpr\
    \ reference operator*() const noexcept { return __i; }\n  };\n\n  using value_type\
    \ = _Index;\n  using reference = value_type;\n\n  using difference_type = std::ptrdiff_t;\n\
    \  using size_type = std::size_t;\n\n  using const_iterator = iterator;\n\n  using\
    \ reverse_iterator = std::reverse_iterator<iterator>;\n  using const_reverse_iterator\
    \ = reverse_iterator;\n\n  template <class _Tp1, class _Tp2>\n  constexpr range(const\
    \ _Tp1 &__first, const _Tp2 &__last) noexcept\n      : __first(__first), __last(__last)\
    \ {}\n\n  template <class _Tp>\n  constexpr range(const _Tp &__last) noexcept\
    \ : __first(), __last(__last) {}\n\n  constexpr iterator begin() const noexcept\
    \ { return {__first}; }\n  constexpr const_iterator cbegin() const noexcept {\
    \ return begin(); }\n\n  constexpr iterator end() const noexcept { return {__last};\
    \ }\n  constexpr const_iterator cend() const noexcept { return end(); }\n\n  constexpr\
    \ reverse_iterator rbegin() const noexcept {\n    return reverse_iterator{end()};\n\
    \  }\n  constexpr const_reverse_iterator crbegin() const noexcept { return rbegin();\
    \ }\n\n  constexpr reverse_iterator rend() const noexcept {\n    return reverse_iterator{begin()};\n\
    \  }\n  constexpr const_reverse_iterator crend() const noexcept { return rend();\
    \ }\n\n  constexpr size_type size() const noexcept { return __last - __first;\
    \ }\n};\n\n#if __cpp_deduction_guides >= 201606L\n\ntemplate <class _Tp1, class\
    \ _Tp2>\nrange(const _Tp1 &, const _Tp2 &)\n    -> range<std::decay_t<decltype(++std::declval<_Tp1\
    \ &>())>>;\n\ntemplate <class _Tp>\nrange(const _Tp &) -> range<std::decay_t<decltype(++std::declval<_Tp\
    \ &>())>>;\n\ntemplate <class... _Args>\nconstexpr decltype(auto) rrange(_Args\
    \ &&...__args) noexcept {\n  return reversed(range(std::forward<_Args>(__args)...));\n\
    }\n\n#endif\n\n}  // namespace workspace\n#line 2 \"src/utils/py-like/zip.hpp\"\
    \n\n/**\n * @file zip.hpp\n * @brief Zip\n */\n\n#include <cstddef>\n#include\
    \ <tuple>\n#line 11 \"src/utils/py-like/zip.hpp\"\n\n#line 2 \"src/utils/iterator/category.hpp\"\
    \n\n/*\n * @file category.hpp\n * @brief Iterator Category\n */\n\n#line 10 \"\
    src/utils/iterator/category.hpp\"\n\nnamespace workspace {\n\n/*\n * @tparam Tuple\
    \ Tuple of iterator types\n */\ntemplate <class Tuple, size_t N = std::tuple_size<Tuple>::value\
    \ - 1>\nstruct common_iterator_category {\n  using type = typename std::common_type<\n\
    \      typename common_iterator_category<Tuple, N - 1>::type,\n      typename\
    \ std::iterator_traits<typename std::tuple_element<\n          N, Tuple>::type>::iterator_category>::type;\n\
    };\n\ntemplate <class Tuple> struct common_iterator_category<Tuple, 0> {\n  using\
    \ type = typename std::iterator_traits<\n      typename std::tuple_element<0,\
    \ Tuple>::type>::iterator_category;\n};\n\n}  // namespace workspace\n#line 2\
    \ \"src/utils/iterator/reverse.hpp\"\n\n/*\n * @file reverse_iterator.hpp\n *\
    \ @brief Reverse Iterator\n */\n\n#if __cplusplus >= 201703L\n\n#line 11 \"src/utils/iterator/reverse.hpp\"\
    \n#include <optional>\n\nnamespace workspace {\n\n/*\n * @class reverse_iterator\n\
    \ * @brief Wrapper class for `std::reverse_iterator`.\n * @see http://gcc.gnu.org/PR51823\n\
    \ */\ntemplate <class Iterator>\nclass reverse_iterator : public std::reverse_iterator<Iterator>\
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
    \n#endif\n#line 15 \"src/utils/py-like/zip.hpp\"\n\nnamespace workspace {\n\n\
    template <class _Tuple> class zipped : protected _Tuple {\n public:\n  zipped(const\
    \ _Tuple &__x) : _Tuple(__x) {}\n\n  template <std::size_t _Nm> constexpr decltype(auto)\
    \ get() const &noexcept {\n    return *std::get<_Nm>(*this);\n  }\n\n  template\
    \ <std::size_t _Nm> constexpr decltype(auto) get() &&noexcept {\n    auto __tmp\
    \ = *std::get<_Nm>(*this);\n    return __tmp;\n  }\n};\n\ntemplate <class... _Containers>\
    \ class zip {\n  std::tuple<_Containers...> __c;\n\n  template <std::size_t _Nm\
    \ = 0>\n  constexpr decltype(auto) begin_cat() const noexcept {\n    if _CXX17_CONSTEXPR\
    \ (_Nm != sizeof...(_Containers)) {\n      return std::tuple_cat(std::tuple(std::begin(std::get<_Nm>(__c))),\n\
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
    \ : tuple_size<_Tuple> {};\n\n}  // namespace std\n#line 10 \"src/utils/py-like/enumerate.hpp\"\
    \n\n#if __cplusplus >= 201703L\n\nnamespace workspace {\n\nnamespace _enumerate_impl\
    \ {\n\nconstexpr size_t min_size() noexcept { return SIZE_MAX; }\n\ntemplate <class\
    \ _Container, class... _Args>\nconstexpr size_t min_size(_Container const &__cont,\n\
    \                          _Args &&... __args) noexcept {\n  return std::min(std::size(__cont),\
    \ min_size(std::forward<_Args>(__args)...));\n}\n\n}  // namespace _enumerate_impl\n\
    \ntemplate <class... _Args>\nconstexpr decltype(auto) enumerate(_Args &&... __args)\
    \ noexcept {\n  return zip(range(_enumerate_impl::min_size(__args...)),\n    \
    \         std::forward<_Args>(__args)...);\n}\n\ntemplate <class... _Args>\nconstexpr\
    \ decltype(auto) enumerate(\n    std::initializer_list<_Args> const &... __args)\
    \ noexcept {\n  return zip(range(_enumerate_impl::min_size(__args...)),\n    \
    \         std::vector(__args)...);\n}\n\n}  // namespace workspace\n\n#endif\n"
  code: "#pragma once\n\n/**\n * @file enumerate.hpp\n * @brief Enumerate\n */\n\n\
    #include \"range.hpp\"\n#include \"zip.hpp\"\n\n#if __cplusplus >= 201703L\n\n\
    namespace workspace {\n\nnamespace _enumerate_impl {\n\nconstexpr size_t min_size()\
    \ noexcept { return SIZE_MAX; }\n\ntemplate <class _Container, class... _Args>\n\
    constexpr size_t min_size(_Container const &__cont,\n                        \
    \  _Args &&... __args) noexcept {\n  return std::min(std::size(__cont), min_size(std::forward<_Args>(__args)...));\n\
    }\n\n}  // namespace _enumerate_impl\n\ntemplate <class... _Args>\nconstexpr decltype(auto)\
    \ enumerate(_Args &&... __args) noexcept {\n  return zip(range(_enumerate_impl::min_size(__args...)),\n\
    \             std::forward<_Args>(__args)...);\n}\n\ntemplate <class... _Args>\n\
    constexpr decltype(auto) enumerate(\n    std::initializer_list<_Args> const &...\
    \ __args) noexcept {\n  return zip(range(_enumerate_impl::min_size(__args...)),\n\
    \             std::vector(__args)...);\n}\n\n}  // namespace workspace\n\n#endif\n"
  dependsOn:
  - src/utils/py-like/range.hpp
  - src/utils/py-like/reversed.hpp
  - src/utils/py-like/zip.hpp
  - src/utils/iterator/category.hpp
  - src/utils/iterator/reverse.hpp
  isVerificationFile: false
  path: src/utils/py-like/enumerate.hpp
  requiredBy: []
  timestamp: '2022-04-06 16:00:36+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/utils/py-like/enumerate.hpp
layout: document
redirect_from:
- /library/src/utils/py-like/enumerate.hpp
- /library/src/utils/py-like/enumerate.hpp.html
title: Enumerate
---
