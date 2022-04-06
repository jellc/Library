---
data:
  _extendedDependsOn:
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
    \ * @brief Range\n */\n\n#line 2 \"src/utils/py-like/reversed.hpp\"\n\n/**\n *\
    \ @file reversed.hpp\n * @brief Reversed\n */\n\n#include <vector>\n\n#line 2\
    \ \"lib/cxx17\"\n\n#line 2 \"lib/cxx14\"\n\n#ifndef _CXX14_CONSTEXPR\n#if __cplusplus\
    \ >= 201402L\n#define _CXX14_CONSTEXPR constexpr\n#else\n#define _CXX14_CONSTEXPR\n\
    #endif\n#endif\n#line 4 \"lib/cxx17\"\n\n#ifndef _CXX17_CONSTEXPR\n#if __cplusplus\
    \ >= 201703L\n#define _CXX17_CONSTEXPR constexpr\n#else\n#define _CXX17_CONSTEXPR\n\
    #endif\n#endif\n\n#ifndef _CXX17_STATIC_ASSERT\n#if __cplusplus >= 201703L\n#define\
    \ _CXX17_STATIC_ASSERT static_assert\n#else\n#define _CXX17_STATIC_ASSERT assert\n\
    #endif\n#endif\n\n#include <iterator>\n\n#if __cplusplus < 201703L\n\nnamespace\
    \ std {\n\n/**\n *  @brief  Return the size of a container.\n *  @param  __cont\
    \  Container.\n */\ntemplate <typename _Container>\nconstexpr auto size(const\
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
    }\n\n#endif\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file range.hpp\n * @brief Range\n */\n\n#include\
    \ \"reversed.hpp\"\n\nnamespace workspace {\n\ntemplate <class _Index> class range\
    \ {\n  _Index __first, __last;\n\n public:\n  class iterator {\n    _Index __i;\n\
    \n   public:\n    using difference_type = std::ptrdiff_t;\n    using value_type\
    \ = _Index;\n    using pointer = void;\n    using reference = value_type;\n  \
    \  using iterator_category = std::random_access_iterator_tag;\n\n    constexpr\
    \ iterator() = default;\n    constexpr iterator(const _Index &__x) noexcept :\
    \ __i(__x) {}\n\n    constexpr bool operator==(const iterator &__x) const noexcept\
    \ {\n      return __i == __x.__i;\n    }\n    constexpr bool operator!=(const\
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
    }\n\n#endif\n\n}  // namespace workspace\n"
  dependsOn:
  - src/utils/py-like/reversed.hpp
  isVerificationFile: false
  path: src/utils/py-like/range.hpp
  requiredBy:
  - src/utils/py-like/enumerate.hpp
  timestamp: '2022-04-06 16:00:36+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/utils/py-like/range.hpp
layout: document
redirect_from:
- /library/src/utils/py-like/range.hpp
- /library/src/utils/py-like/range.hpp.html
title: Range
---
