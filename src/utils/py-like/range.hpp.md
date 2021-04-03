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
    \ * @brief Reversed\n */\n\n#include <initializer_list>\n#line 10 \"src/utils/py-like/reversed.hpp\"\
    \n\nnamespace workspace {\n\nnamespace _reversed_impl {\n\ntemplate <class _Container>\
    \ class reversed {\n  _Container __cont;\n\n public:\n  constexpr reversed(_Container\
    \ &&__cont) noexcept : __cont(__cont) {}\n\n  constexpr decltype(auto) begin()\
    \ noexcept { return std::rbegin(__cont); }\n  constexpr decltype(auto) begin()\
    \ const noexcept {\n    return std::rbegin(__cont);\n  }\n\n  constexpr decltype(auto)\
    \ end() noexcept { return std::rend(__cont); }\n  constexpr decltype(auto) end()\
    \ const noexcept { return std::rend(__cont); }\n\n  constexpr decltype(auto) size()\
    \ const noexcept { return std::size(__cont); }\n};\n\n}  // namespace _reversed_impl\n\
    \ntemplate <class _Container>\nconstexpr decltype(auto) reversed(_Container &&__cont)\
    \ noexcept {\n  return _reversed_impl::reversed<_Container>{std::forward<_Container>(__cont)};\n\
    }\n\ntemplate <class _Tp>\nconstexpr decltype(auto) reversed(\n    std::initializer_list<_Tp>\
    \ &&__cont) noexcept {\n  return _reversed_impl::reversed<std::initializer_list<_Tp>>{\n\
    \      std::forward<std::initializer_list<_Tp>>(__cont)};\n}\n\n}  // namespace\
    \ workspace\n#line 12 \"src/utils/py-like/range.hpp\"\n\n#if __cplusplus >= 201703L\n\
    \nnamespace workspace {\n\ntemplate <class Index> class range {\n  Index first,\
    \ last;\n\n public:\n  class iterator {\n    Index current;\n\n   public:\n  \
    \  using difference_type = std::ptrdiff_t;\n    using value_type = Index;\n  \
    \  using reference = typename std::add_const<Index>::type &;\n    using pointer\
    \ = iterator;\n    using iterator_category = std::bidirectional_iterator_tag;\n\
    \n    constexpr iterator(Index const &__i = Index()) noexcept : current(__i) {}\n\
    \n    constexpr bool operator==(iterator const &rhs) const noexcept {\n      return\
    \ current == rhs.current;\n    }\n    constexpr bool operator!=(iterator const\
    \ &rhs) const noexcept {\n      return current != rhs.current;\n    }\n\n    constexpr\
    \ iterator &operator++() noexcept {\n      ++current;\n      return *this;\n \
    \   }\n    constexpr iterator &operator--() noexcept {\n      --current;\n   \
    \   return *this;\n    }\n\n    constexpr reference operator*() const noexcept\
    \ { return current; }\n  };\n\n  constexpr range(Index first, Index last) noexcept\n\
    \      : first(first), last(last) {}\n  constexpr range(Index last) noexcept :\
    \ first(), last(last) {}\n\n  constexpr iterator begin() const noexcept { return\
    \ iterator{first}; }\n  constexpr iterator end() const noexcept { return iterator{last};\
    \ }\n\n  constexpr reverse_iterator<iterator> rbegin() const noexcept {\n    return\
    \ reverse_iterator<iterator>(end());\n  }\n  constexpr reverse_iterator<iterator>\
    \ rend() const noexcept {\n    return reverse_iterator<iterator>(begin());\n \
    \ }\n};\n\ntemplate <class... Args> constexpr auto rrange(Args &&... args) noexcept\
    \ {\n  return internal::reversed(range(std::forward<Args>(args)...));\n}\n\n}\
    \  // namespace workspace\n\n#endif\n"
  code: "#pragma once\n\n/**\n * @file range.hpp\n * @brief Range\n */\n\n#include\
    \ <iterator>\n\n#include \"../iterator/reverse.hpp\"\n#include \"reversed.hpp\"\
    \n\n#if __cplusplus >= 201703L\n\nnamespace workspace {\n\ntemplate <class Index>\
    \ class range {\n  Index first, last;\n\n public:\n  class iterator {\n    Index\
    \ current;\n\n   public:\n    using difference_type = std::ptrdiff_t;\n    using\
    \ value_type = Index;\n    using reference = typename std::add_const<Index>::type\
    \ &;\n    using pointer = iterator;\n    using iterator_category = std::bidirectional_iterator_tag;\n\
    \n    constexpr iterator(Index const &__i = Index()) noexcept : current(__i) {}\n\
    \n    constexpr bool operator==(iterator const &rhs) const noexcept {\n      return\
    \ current == rhs.current;\n    }\n    constexpr bool operator!=(iterator const\
    \ &rhs) const noexcept {\n      return current != rhs.current;\n    }\n\n    constexpr\
    \ iterator &operator++() noexcept {\n      ++current;\n      return *this;\n \
    \   }\n    constexpr iterator &operator--() noexcept {\n      --current;\n   \
    \   return *this;\n    }\n\n    constexpr reference operator*() const noexcept\
    \ { return current; }\n  };\n\n  constexpr range(Index first, Index last) noexcept\n\
    \      : first(first), last(last) {}\n  constexpr range(Index last) noexcept :\
    \ first(), last(last) {}\n\n  constexpr iterator begin() const noexcept { return\
    \ iterator{first}; }\n  constexpr iterator end() const noexcept { return iterator{last};\
    \ }\n\n  constexpr reverse_iterator<iterator> rbegin() const noexcept {\n    return\
    \ reverse_iterator<iterator>(end());\n  }\n  constexpr reverse_iterator<iterator>\
    \ rend() const noexcept {\n    return reverse_iterator<iterator>(begin());\n \
    \ }\n};\n\ntemplate <class... Args> constexpr auto rrange(Args &&... args) noexcept\
    \ {\n  return internal::reversed(range(std::forward<Args>(args)...));\n}\n\n}\
    \  // namespace workspace\n\n#endif\n"
  dependsOn:
  - src/utils/iterator/reverse.hpp
  - src/utils/py-like/reversed.hpp
  isVerificationFile: false
  path: src/utils/py-like/range.hpp
  requiredBy:
  - src/utils/py-like/enumerate.hpp
  timestamp: '2021-04-03 14:10:18+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/utils/py-like/range.hpp
layout: document
redirect_from:
- /library/src/utils/py-like/range.hpp
- /library/src/utils/py-like/range.hpp.html
title: Range
---
