---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/utils/iterator/category.hpp
    title: Iterator Category
  - icon: ':heavy_check_mark:'
    path: src/utils/iterator/reverse.hpp
    title: Reverse Iterator
  _extendedRequiredBy:
  - icon: ':warning:'
    path: src/utils/py-like/enumerate.hpp
    title: Enumerate
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/library-checker/number_of_substrings.test.cpp
    title: test/library-checker/number_of_substrings.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Zip
    links:
    - https://gcc.gnu.org/bugzilla/show_bug.cgi?id=80438
  bundledCode: "#line 2 \"src/utils/py-like/zip.hpp\"\n\n/**\n * @file zip.hpp\n *\
    \ @brief Zip\n */\n\n#include <cstddef>\n#include <tuple>\n#include <vector>\n\
    \n#line 2 \"src/utils/iterator/category.hpp\"\n\n/*\n * @file category.hpp\n *\
    \ @brief Iterator Category\n */\n\n#line 10 \"src/utils/iterator/category.hpp\"\
    \n\nnamespace workspace {\n\n/*\n * @tparam Tuple Tuple of iterator types\n */\n\
    template <class Tuple, size_t N = std::tuple_size<Tuple>::value - 1>\nstruct common_iterator_category\
    \ {\n  using type = typename std::common_type<\n      typename common_iterator_category<Tuple,\
    \ N - 1>::type,\n      typename std::iterator_traits<typename std::tuple_element<\n\
    \          N, Tuple>::type>::iterator_category>::type;\n};\n\ntemplate <class\
    \ Tuple> struct common_iterator_category<Tuple, 0> {\n  using type = typename\
    \ std::iterator_traits<\n      typename std::tuple_element<0, Tuple>::type>::iterator_category;\n\
    };\n\n}  // namespace workspace\n#line 2 \"src/utils/iterator/reverse.hpp\"\n\n\
    /*\n * @file reverse_iterator.hpp\n * @brief Reverse Iterator\n */\n\n#if __cplusplus\
    \ >= 201703L\n\n#include <iterator>\n#include <optional>\n\nnamespace workspace\
    \ {\n\n/*\n * @class reverse_iterator\n * @brief Wrapper class for `std::reverse_iterator`.\n\
    \ * @see http://gcc.gnu.org/PR51823\n */\ntemplate <class Iterator>\nclass reverse_iterator\
    \ : public std::reverse_iterator<Iterator> {\n  using base_std = std::reverse_iterator<Iterator>;\n\
    \  std::optional<typename base_std::value_type> deref;\n\n public:\n  using base_std::reverse_iterator;\n\
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
    \ : tuple_size<_Tuple> {};\n\n}  // namespace std\n"
  code: "#pragma once\n\n/**\n * @file zip.hpp\n * @brief Zip\n */\n\n#include <cstddef>\n\
    #include <tuple>\n#include <vector>\n\n#include \"../iterator/category.hpp\"\n\
    #include \"../iterator/reverse.hpp\"\n#include \"lib/cxx17\"\n\nnamespace workspace\
    \ {\n\ntemplate <class _Tuple> class zipped : protected _Tuple {\n public:\n \
    \ zipped(const _Tuple &__x) : _Tuple(__x) {}\n\n  template <std::size_t _Nm> constexpr\
    \ decltype(auto) get() const &noexcept {\n    return *std::get<_Nm>(*this);\n\
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
    \ : tuple_size<_Tuple> {};\n\n}  // namespace std\n"
  dependsOn:
  - src/utils/iterator/category.hpp
  - src/utils/iterator/reverse.hpp
  isVerificationFile: false
  path: src/utils/py-like/zip.hpp
  requiredBy:
  - src/utils/py-like/enumerate.hpp
  timestamp: '2022-04-06 16:00:36+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/number_of_substrings.test.cpp
documentation_of: src/utils/py-like/zip.hpp
layout: document
redirect_from:
- /library/src/utils/py-like/zip.hpp
- /library/src/utils/py-like/zip.hpp.html
title: Zip
---
