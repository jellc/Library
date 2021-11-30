---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/utils/iterator/reverse.hpp
    title: Reverse Iterator
  - icon: ':warning:'
    path: src/utils/py-like/reversed.hpp
    title: Reversed
  _extendedRequiredBy:
  - icon: ':warning:'
    path: src/utils/py-like/enumerate.hpp
    title: Enumerate
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Range
    links: []
  bundledCode: "#line 2 \"src/utils/py-like/range.hpp\"\n\n/**\n * @file range.hpp\n\
    \ * @brief Range\n */\n\n#include <iterator>\n\n#line 2 \"src/utils/iterator/reverse.hpp\"\
    \n\n/*\n * @file reverse_iterator.hpp\n * @brief Reverse Iterator\n */\n\n#if\
    \ __cplusplus >= 201703L\n\n#line 11 \"src/utils/iterator/reverse.hpp\"\n#include\
    \ <optional>\n\nnamespace workspace {\n\n/*\n * @class reverse_iterator\n * @brief\
    \ Wrapper class for `std::reverse_iterator`.\n * @see http://gcc.gnu.org/PR51823\n\
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
    \n#endif\n#line 2 \"src/utils/py-like/reversed.hpp\"\n\n/**\n * @file reversed.hpp\n\
    \ * @brief Reversed\n */\n\n#include <vector>\n\n#line 2 \"lib/cxx17\"\n\n#line\
    \ 2 \"lib/cxx14\"\n\n#ifndef _CXX14_CONSTEXPR\n#if __cplusplus >= 201402L\n#define\
    \ _CXX14_CONSTEXPR constexpr\n#else\n#define _CXX14_CONSTEXPR\n#endif\n#endif\n\
    #line 4 \"lib/cxx17\"\n\n#ifndef _CXX17_CONSTEXPR\n#if __cplusplus >= 201703L\n\
    #define _CXX17_CONSTEXPR constexpr\n#else\n#define _CXX17_CONSTEXPR\n#endif\n\
    #endif\n\n#ifndef _CXX17_STATIC_ASSERT\n#if __cplusplus >= 201703L\n#define _CXX17_STATIC_ASSERT\
    \ static_assert\n#else\n#define _CXX17_STATIC_ASSERT assert\n#endif\n#endif\n\n\
    #line 22 \"lib/cxx17\"\n\n#if __cplusplus < 201703L\n\nnamespace std {\n\n/**\n\
    \ *  @brief  Return the size of a container.\n *  @param  __cont  Container.\n\
    \ */\ntemplate <typename _Container>\nconstexpr auto size(const _Container& __cont)\
    \ noexcept(noexcept(__cont.size()))\n    -> decltype(__cont.size()) {\n  return\
    \ __cont.size();\n}\n\n/**\n *  @brief  Return the size of an array.\n */\ntemplate\
    \ <typename _Tp, size_t _Nm>\nconstexpr size_t size(const _Tp (&)[_Nm]) noexcept\
    \ {\n  return _Nm;\n}\n\n/**\n *  @brief  Return whether a container is empty.\n\
    \ *  @param  __cont  Container.\n */\ntemplate <typename _Container>\n[[nodiscard]]\
    \ constexpr auto empty(const _Container& __cont) noexcept(\n    noexcept(__cont.empty()))\
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
    #line 12 \"src/utils/py-like/range.hpp\"\n\n#if __cplusplus >= 201703L\n\nnamespace\
    \ workspace {\n\ntemplate <class _Index> class range {\n  _Index __first, __last;\n\
    \n public:\n  class iterator {\n    _Index current;\n\n   public:\n    using difference_type\
    \ = std::ptrdiff_t;\n    using value_type = _Index;\n    using reference = typename\
    \ std::add_const<_Index>::type &;\n    using pointer = iterator;\n    using iterator_category\
    \ = std::random_access_iterator_tag;\n\n    constexpr iterator(const _Index &__i\
    \ = _Index()) noexcept : current(__i) {}\n\n    constexpr bool operator==(const\
    \ iterator &__x) const noexcept {\n      return current == __x.current;\n    }\n\
    \    constexpr bool operator!=(const iterator &__x) const noexcept {\n      return\
    \ current != __x.current;\n    }\n\n    constexpr bool operator<(const iterator\
    \ &__x) const noexcept {\n      return current < __x.current;\n    }\n    constexpr\
    \ bool operator<=(const iterator &__x) const noexcept {\n      return current\
    \ <= __x.current;\n    }\n\n    constexpr bool operator>(const iterator &__x)\
    \ const noexcept {\n      return current > __x.current;\n    }\n    constexpr\
    \ bool operator>=(const iterator &__x) const noexcept {\n      return current\
    \ >= __x.current;\n    }\n\n    constexpr iterator &operator++() noexcept {\n\
    \      ++current;\n      return *this;\n    }\n    constexpr iterator &operator++(int)\
    \ noexcept {\n      auto __tmp = *this;\n      ++current;\n      return __tmp;\n\
    \    }\n\n    constexpr iterator &operator--() noexcept {\n      --current;\n\
    \      return *this;\n    }\n    constexpr iterator &operator--(int) noexcept\
    \ {\n      auto __tmp = *this;\n      --current;\n      return __tmp;\n    }\n\
    \n    constexpr difference_type operator-(const iterator &__x) const noexcept\
    \ {\n      return current - __x.current;\n    }\n\n    constexpr iterator &operator+=(difference_type\
    \ __x) noexcept {\n      current += __x;\n      return *this;\n    }\n    constexpr\
    \ iterator operator+(difference_type __x) const noexcept {\n      return iterator(*this)\
    \ += __x;\n    }\n\n    constexpr iterator &operator-=(difference_type __x) noexcept\
    \ {\n      current -= __x;\n      return *this;\n    }\n    constexpr iterator\
    \ operator-(difference_type __x) const noexcept {\n      return iterator(*this)\
    \ -= __x;\n    }\n\n    constexpr reference operator*() const noexcept { return\
    \ current; }\n  };\n\n  template <class _Tp1, class _Tp2>\n  constexpr range(const\
    \ _Tp1 &__first, const _Tp2 &__last) noexcept\n      : __first(__first), __last(__last)\
    \ {}\n\n  template <class _Tp>\n  constexpr range(const _Tp &__last) noexcept\
    \ : __first(), __last(__last) {}\n\n  constexpr iterator begin() const noexcept\
    \ { return iterator{__first}; }\n  constexpr iterator end() const noexcept { return\
    \ iterator{__last}; }\n\n  constexpr reverse_iterator<iterator> rbegin() const\
    \ noexcept {\n    return reverse_iterator<iterator>(end());\n  }\n  constexpr\
    \ reverse_iterator<iterator> rend() const noexcept {\n    return reverse_iterator<iterator>(begin());\n\
    \  }\n\n  constexpr size_t size() const noexcept {\n    return std::distance(__first,\
    \ __last);\n  }\n};\n\ntemplate <class _Tp1, class _Tp2>\nrange(const _Tp1 &,\
    \ const _Tp2 &)\n    -> range<std::decay_t<decltype(++std::declval<_Tp1 &>())>>;\n\
    \ntemplate <class _Tp>\nrange(const _Tp &) -> range<std::decay_t<decltype(++std::declval<_Tp\
    \ &>())>>;\n\ntemplate <class... _Args>\nconstexpr decltype(auto) rrange(_Args\
    \ &&...__args) noexcept {\n  return reversed(range(std::forward<_Args>(__args)...));\n\
    }\n\ntemplate <class _Container>\nconstexpr decltype(auto) iterate(_Container\
    \ &&__cont) noexcept {\n  return range(std::begin(__cont), std::end(__cont));\n\
    }\n\ntemplate <class _Container>\nconstexpr decltype(auto) riterate(_Container\
    \ &&__cont) noexcept {\n  return range(std::rbegin(__cont), std::rend(__cont));\n\
    }\n\n}  // namespace workspace\n\n#endif\n"
  code: "#pragma once\n\n/**\n * @file range.hpp\n * @brief Range\n */\n\n#include\
    \ <iterator>\n\n#include \"../iterator/reverse.hpp\"\n#include \"reversed.hpp\"\
    \n\n#if __cplusplus >= 201703L\n\nnamespace workspace {\n\ntemplate <class _Index>\
    \ class range {\n  _Index __first, __last;\n\n public:\n  class iterator {\n \
    \   _Index current;\n\n   public:\n    using difference_type = std::ptrdiff_t;\n\
    \    using value_type = _Index;\n    using reference = typename std::add_const<_Index>::type\
    \ &;\n    using pointer = iterator;\n    using iterator_category = std::random_access_iterator_tag;\n\
    \n    constexpr iterator(const _Index &__i = _Index()) noexcept : current(__i)\
    \ {}\n\n    constexpr bool operator==(const iterator &__x) const noexcept {\n\
    \      return current == __x.current;\n    }\n    constexpr bool operator!=(const\
    \ iterator &__x) const noexcept {\n      return current != __x.current;\n    }\n\
    \n    constexpr bool operator<(const iterator &__x) const noexcept {\n      return\
    \ current < __x.current;\n    }\n    constexpr bool operator<=(const iterator\
    \ &__x) const noexcept {\n      return current <= __x.current;\n    }\n\n    constexpr\
    \ bool operator>(const iterator &__x) const noexcept {\n      return current >\
    \ __x.current;\n    }\n    constexpr bool operator>=(const iterator &__x) const\
    \ noexcept {\n      return current >= __x.current;\n    }\n\n    constexpr iterator\
    \ &operator++() noexcept {\n      ++current;\n      return *this;\n    }\n   \
    \ constexpr iterator &operator++(int) noexcept {\n      auto __tmp = *this;\n\
    \      ++current;\n      return __tmp;\n    }\n\n    constexpr iterator &operator--()\
    \ noexcept {\n      --current;\n      return *this;\n    }\n    constexpr iterator\
    \ &operator--(int) noexcept {\n      auto __tmp = *this;\n      --current;\n \
    \     return __tmp;\n    }\n\n    constexpr difference_type operator-(const iterator\
    \ &__x) const noexcept {\n      return current - __x.current;\n    }\n\n    constexpr\
    \ iterator &operator+=(difference_type __x) noexcept {\n      current += __x;\n\
    \      return *this;\n    }\n    constexpr iterator operator+(difference_type\
    \ __x) const noexcept {\n      return iterator(*this) += __x;\n    }\n\n    constexpr\
    \ iterator &operator-=(difference_type __x) noexcept {\n      current -= __x;\n\
    \      return *this;\n    }\n    constexpr iterator operator-(difference_type\
    \ __x) const noexcept {\n      return iterator(*this) -= __x;\n    }\n\n    constexpr\
    \ reference operator*() const noexcept { return current; }\n  };\n\n  template\
    \ <class _Tp1, class _Tp2>\n  constexpr range(const _Tp1 &__first, const _Tp2\
    \ &__last) noexcept\n      : __first(__first), __last(__last) {}\n\n  template\
    \ <class _Tp>\n  constexpr range(const _Tp &__last) noexcept : __first(), __last(__last)\
    \ {}\n\n  constexpr iterator begin() const noexcept { return iterator{__first};\
    \ }\n  constexpr iterator end() const noexcept { return iterator{__last}; }\n\n\
    \  constexpr reverse_iterator<iterator> rbegin() const noexcept {\n    return\
    \ reverse_iterator<iterator>(end());\n  }\n  constexpr reverse_iterator<iterator>\
    \ rend() const noexcept {\n    return reverse_iterator<iterator>(begin());\n \
    \ }\n\n  constexpr size_t size() const noexcept {\n    return std::distance(__first,\
    \ __last);\n  }\n};\n\ntemplate <class _Tp1, class _Tp2>\nrange(const _Tp1 &,\
    \ const _Tp2 &)\n    -> range<std::decay_t<decltype(++std::declval<_Tp1 &>())>>;\n\
    \ntemplate <class _Tp>\nrange(const _Tp &) -> range<std::decay_t<decltype(++std::declval<_Tp\
    \ &>())>>;\n\ntemplate <class... _Args>\nconstexpr decltype(auto) rrange(_Args\
    \ &&...__args) noexcept {\n  return reversed(range(std::forward<_Args>(__args)...));\n\
    }\n\ntemplate <class _Container>\nconstexpr decltype(auto) iterate(_Container\
    \ &&__cont) noexcept {\n  return range(std::begin(__cont), std::end(__cont));\n\
    }\n\ntemplate <class _Container>\nconstexpr decltype(auto) riterate(_Container\
    \ &&__cont) noexcept {\n  return range(std::rbegin(__cont), std::rend(__cont));\n\
    }\n\n}  // namespace workspace\n\n#endif\n"
  dependsOn:
  - src/utils/iterator/reverse.hpp
  - src/utils/py-like/reversed.hpp
  isVerificationFile: false
  path: src/utils/py-like/range.hpp
  requiredBy:
  - src/utils/py-like/enumerate.hpp
  timestamp: '2021-11-30 17:55:32+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/utils/py-like/range.hpp
layout: document
redirect_from:
- /library/src/utils/py-like/range.hpp
- /library/src/utils/py-like/range.hpp.html
title: Range
---
