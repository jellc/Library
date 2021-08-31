---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Subsets
    links: []
  bundledCode: "#line 2 \"src/utils/subsets.hpp\"\n\n/**\n * @file subsets.hpp\n *\
    \ @brief Subsets\n */\n\n#include <vector>\n\nnamespace workspace {\n\nnamespace\
    \ _subsets_impl {\n\ntemplate <class _Int, bool = std::is_integral<_Int>::value>\
    \ class iterator {\n  _Int __a, __b;\n  bool __stop;\n\n public:\n  using difference_type\
    \ = std::ptrdiff_t;\n  using value_type = _Int;\n  using pointer = void;\n  using\
    \ reference = value_type;\n  using iterator_category = std::bidirectional_iterator_tag;\n\
    \n  constexpr iterator() = default;\n  constexpr iterator(_Int __x, bool __y)\
    \ noexcept\n      : __a(0), __b(__x), __stop(__y) {}\n\n  constexpr iterator &operator++()\
    \ noexcept {\n    assert(!__stop);\n    __stop = !(++(__a |= ~__b) &= __b);\n\
    \    return *this;\n  }\n  constexpr iterator operator++(int) noexcept {\n   \
    \ auto __tmp = *this;\n    operator++();\n    return __tmp;\n  }\n\n  constexpr\
    \ iterator &operator--() noexcept {\n    assert(__a || __stop);\n    --__a &=\
    \ __b, __stop = false;\n    return *this;\n  }\n  constexpr iterator operator--(int)\
    \ noexcept {\n    auto __tmp = *this;\n    operator--();\n    return __tmp;\n\
    \  }\n\n  constexpr value_type operator*() const noexcept {\n    assert(!__stop);\n\
    \    return __a;\n  }\n\n  constexpr bool operator==(const iterator &__x) const\
    \ noexcept {\n    return __a == __x.__a && __b == __x.__b && __stop == __x.__stop;\n\
    \  }\n  constexpr bool operator!=(const iterator &__x) const noexcept {\n    return\
    \ !operator==(__x);\n  }\n};\n\ntemplate <class _Container>\nclass iterator<_Container,\
    \ false> : public iterator<int> {\n  using _Base = iterator<int>;\n\n  decltype(std::begin(std::declval<_Container>()))\
    \ __p;\n\n public:\n  using difference_type = std::ptrdiff_t;\n  using value_type\
    \ = _Container;\n  using pointer = void;\n  using reference = value_type;\n  using\
    \ iterator_category = std::bidirectional_iterator_tag;\n\n  iterator() = default;\n\
    \  iterator(const _Container &__c, bool __stop) noexcept\n      : _Base((1 <<\
    \ __c.size()) - 1, __stop), __p(__c.begin()) {}\n\n  iterator &operator++() noexcept\
    \ {\n    _Base::operator++();\n    return *this;\n  }\n  iterator operator++(int)\
    \ noexcept {\n    auto __tmp = *this;\n    _Base::operator++();\n    return __tmp;\n\
    \  }\n\n  iterator &operator--() noexcept {\n    _Base::operator--();\n    return\
    \ *this;\n  }\n  iterator operator--(int) noexcept {\n    auto __tmp = *this;\n\
    \    _Base::operator--();\n    return __tmp;\n  }\n\n  value_type operator*()\
    \ const noexcept {\n    static std::vector<std::decay_t<decltype(*__p)>> __v;\n\
    \    __v.clear();\n\n    auto __n = _Base::operator*();\n    for (auto __i = __p;\
    \ __n; __n >>= 1, ++__i)\n      if (__n & 1) __v.emplace_back(*__i);\n\n    return\
    \ value_type(std::make_move_iterator(__v.begin()),\n                      std::make_move_iterator(__v.end()));\n\
    \  }\n\n  bool operator==(const iterator &__x) const noexcept {\n    return __p\
    \ == __x.__p && _Base::operator==(__x);\n  }\n  bool operator!=(const iterator\
    \ &__x) const noexcept {\n    return !operator==(__x);\n  }\n};\n\n}  // namespace\
    \ _subsets_impl\n\ntemplate <class _Container> class subsets {\n  _Container __c;\n\
    \n public:\n  using value_type = std::decay_t<_Container>;\n  using reference\
    \ = value_type;\n\n  using difference_type = std::ptrdiff_t;\n  using size_type\
    \ = std::size_t;\n\n  using iterator = _subsets_impl::iterator<value_type>;\n\
    \  using const_iterator = iterator;\n\n  using reverse_iterator = std::reverse_iterator<iterator>;\n\
    \  using const_reverse_iterator = reverse_iterator;\n\n  template <class _Tp>\n\
    \  constexpr subsets(_Tp &&__x) noexcept : __c(std::forward<_Tp>(__x)) {}\n\n\
    \  template <class _Tp>\n  constexpr subsets(std::initializer_list<_Tp> __x) noexcept\
    \ : __c(__x) {}\n\n  constexpr iterator begin() const noexcept { return {__c,\
    \ false}; }\n  constexpr const_iterator cbegin() const noexcept { return begin();\
    \ }\n\n  constexpr iterator end() const noexcept { return {__c, true}; }\n  constexpr\
    \ const_iterator cend() const noexcept { return end(); }\n\n  constexpr reverse_iterator\
    \ rbegin() const noexcept {\n    return reverse_iterator{end()};\n  }\n  constexpr\
    \ const_reverse_iterator crbegin() const noexcept { return rbegin(); }\n\n  constexpr\
    \ reverse_iterator rend() const noexcept {\n    return reverse_iterator{begin()};\n\
    \  }\n  constexpr const_reverse_iterator crend() const noexcept { return rend();\
    \ }\n\n  constexpr bool empty() const noexcept { return false; }\n\n#if __cplusplus\
    \ >= 201703L\n  constexpr size_type size() const noexcept {\n    if constexpr\
    \ (std::is_convertible<_Container, size_type>::value)\n      return 1 << __builtin_popcount(__c);\n\
    \    else\n      return 1 << __c.size();\n  }\n#endif\n};\n\n#if __cpp_deduction_guides\
    \ >= 201606L\n\ntemplate <class _Tp> subsets(_Tp &&) -> subsets<_Tp>;\n\ntemplate\
    \ <class _Tp>\nsubsets(std::initializer_list<_Tp>) -> subsets<std::vector<_Tp>>;\n\
    \n#endif\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file subsets.hpp\n * @brief Subsets\n */\n\n#include\
    \ <vector>\n\nnamespace workspace {\n\nnamespace _subsets_impl {\n\ntemplate <class\
    \ _Int, bool = std::is_integral<_Int>::value> class iterator {\n  _Int __a, __b;\n\
    \  bool __stop;\n\n public:\n  using difference_type = std::ptrdiff_t;\n  using\
    \ value_type = _Int;\n  using pointer = void;\n  using reference = value_type;\n\
    \  using iterator_category = std::bidirectional_iterator_tag;\n\n  constexpr iterator()\
    \ = default;\n  constexpr iterator(_Int __x, bool __y) noexcept\n      : __a(0),\
    \ __b(__x), __stop(__y) {}\n\n  constexpr iterator &operator++() noexcept {\n\
    \    assert(!__stop);\n    __stop = !(++(__a |= ~__b) &= __b);\n    return *this;\n\
    \  }\n  constexpr iterator operator++(int) noexcept {\n    auto __tmp = *this;\n\
    \    operator++();\n    return __tmp;\n  }\n\n  constexpr iterator &operator--()\
    \ noexcept {\n    assert(__a || __stop);\n    --__a &= __b, __stop = false;\n\
    \    return *this;\n  }\n  constexpr iterator operator--(int) noexcept {\n   \
    \ auto __tmp = *this;\n    operator--();\n    return __tmp;\n  }\n\n  constexpr\
    \ value_type operator*() const noexcept {\n    assert(!__stop);\n    return __a;\n\
    \  }\n\n  constexpr bool operator==(const iterator &__x) const noexcept {\n  \
    \  return __a == __x.__a && __b == __x.__b && __stop == __x.__stop;\n  }\n  constexpr\
    \ bool operator!=(const iterator &__x) const noexcept {\n    return !operator==(__x);\n\
    \  }\n};\n\ntemplate <class _Container>\nclass iterator<_Container, false> : public\
    \ iterator<int> {\n  using _Base = iterator<int>;\n\n  decltype(std::begin(std::declval<_Container>()))\
    \ __p;\n\n public:\n  using difference_type = std::ptrdiff_t;\n  using value_type\
    \ = _Container;\n  using pointer = void;\n  using reference = value_type;\n  using\
    \ iterator_category = std::bidirectional_iterator_tag;\n\n  iterator() = default;\n\
    \  iterator(const _Container &__c, bool __stop) noexcept\n      : _Base((1 <<\
    \ __c.size()) - 1, __stop), __p(__c.begin()) {}\n\n  iterator &operator++() noexcept\
    \ {\n    _Base::operator++();\n    return *this;\n  }\n  iterator operator++(int)\
    \ noexcept {\n    auto __tmp = *this;\n    _Base::operator++();\n    return __tmp;\n\
    \  }\n\n  iterator &operator--() noexcept {\n    _Base::operator--();\n    return\
    \ *this;\n  }\n  iterator operator--(int) noexcept {\n    auto __tmp = *this;\n\
    \    _Base::operator--();\n    return __tmp;\n  }\n\n  value_type operator*()\
    \ const noexcept {\n    static std::vector<std::decay_t<decltype(*__p)>> __v;\n\
    \    __v.clear();\n\n    auto __n = _Base::operator*();\n    for (auto __i = __p;\
    \ __n; __n >>= 1, ++__i)\n      if (__n & 1) __v.emplace_back(*__i);\n\n    return\
    \ value_type(std::make_move_iterator(__v.begin()),\n                      std::make_move_iterator(__v.end()));\n\
    \  }\n\n  bool operator==(const iterator &__x) const noexcept {\n    return __p\
    \ == __x.__p && _Base::operator==(__x);\n  }\n  bool operator!=(const iterator\
    \ &__x) const noexcept {\n    return !operator==(__x);\n  }\n};\n\n}  // namespace\
    \ _subsets_impl\n\ntemplate <class _Container> class subsets {\n  _Container __c;\n\
    \n public:\n  using value_type = std::decay_t<_Container>;\n  using reference\
    \ = value_type;\n\n  using difference_type = std::ptrdiff_t;\n  using size_type\
    \ = std::size_t;\n\n  using iterator = _subsets_impl::iterator<value_type>;\n\
    \  using const_iterator = iterator;\n\n  using reverse_iterator = std::reverse_iterator<iterator>;\n\
    \  using const_reverse_iterator = reverse_iterator;\n\n  template <class _Tp>\n\
    \  constexpr subsets(_Tp &&__x) noexcept : __c(std::forward<_Tp>(__x)) {}\n\n\
    \  template <class _Tp>\n  constexpr subsets(std::initializer_list<_Tp> __x) noexcept\
    \ : __c(__x) {}\n\n  constexpr iterator begin() const noexcept { return {__c,\
    \ false}; }\n  constexpr const_iterator cbegin() const noexcept { return begin();\
    \ }\n\n  constexpr iterator end() const noexcept { return {__c, true}; }\n  constexpr\
    \ const_iterator cend() const noexcept { return end(); }\n\n  constexpr reverse_iterator\
    \ rbegin() const noexcept {\n    return reverse_iterator{end()};\n  }\n  constexpr\
    \ const_reverse_iterator crbegin() const noexcept { return rbegin(); }\n\n  constexpr\
    \ reverse_iterator rend() const noexcept {\n    return reverse_iterator{begin()};\n\
    \  }\n  constexpr const_reverse_iterator crend() const noexcept { return rend();\
    \ }\n\n  constexpr bool empty() const noexcept { return false; }\n\n#if __cplusplus\
    \ >= 201703L\n  constexpr size_type size() const noexcept {\n    if constexpr\
    \ (std::is_convertible<_Container, size_type>::value)\n      return 1 << __builtin_popcount(__c);\n\
    \    else\n      return 1 << __c.size();\n  }\n#endif\n};\n\n#if __cpp_deduction_guides\
    \ >= 201606L\n\ntemplate <class _Tp> subsets(_Tp &&) -> subsets<_Tp>;\n\ntemplate\
    \ <class _Tp>\nsubsets(std::initializer_list<_Tp>) -> subsets<std::vector<_Tp>>;\n\
    \n#endif\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/utils/subsets.hpp
  requiredBy: []
  timestamp: '2021-08-31 15:53:46+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/utils/subsets.hpp
layout: document
redirect_from:
- /library/src/utils/subsets.hpp
- /library/src/utils/subsets.hpp.html
title: Subsets
---
