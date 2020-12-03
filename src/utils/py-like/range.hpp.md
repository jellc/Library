---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: src/utils/reverse_iterator.hpp
    title: Reverse Iterator
  _extendedRequiredBy:
  - icon: ':warning:'
    path: src/utils/py-like/enumerate.hpp
    title: Enumerate
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Range
    links: []
  bundledCode: "#line 2 \"src/utils/py-like/range.hpp\"\n\n/*\n * @file range.hpp\n\
    \ * @brief Range\n */\n\n#include <iterator>\n\n#line 2 \"src/utils/reverse_iterator.hpp\"\
    \n\n/*\n * @file reverse_iterator.hpp\n * @brief Reverse Iterator\n */\n\n#line\
    \ 9 \"src/utils/reverse_iterator.hpp\"\n#include <optional>\n\nnamespace workspace\
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
    #line 11 \"src/utils/py-like/range.hpp\"\n\nnamespace workspace {\n\ntemplate\
    \ <class Index> class range {\n  Index first, last;\n\n public:\n  class iterator\
    \ {\n    Index iter;\n\n   public:\n    using difference_type = std::ptrdiff_t;\n\
    \    using value_type = Index;\n    using reference = typename std::add_const<Index>::type\
    \ &;\n    using pointer = iterator;\n    using iterator_category = std::bidirectional_iterator_tag;\n\
    \n    constexpr iterator(Index iter = Index()) noexcept : iter(iter) {}\n\n  \
    \  constexpr bool operator==(iterator const &rhs) const noexcept {\n      return\
    \ iter == rhs.iter;\n    }\n    constexpr bool operator!=(iterator const &rhs)\
    \ const noexcept {\n      return iter != rhs.iter;\n    }\n\n    constexpr iterator\
    \ &operator++() noexcept {\n      ++iter;\n      return *this;\n    }\n    constexpr\
    \ iterator &operator--() noexcept {\n      --iter;\n      return *this;\n    }\n\
    \n    constexpr reference operator*() const noexcept { return iter; }\n  };\n\n\
    \  constexpr range(Index first, Index last) noexcept\n      : first(first), last(last)\
    \ {}\n  constexpr range(Index last) noexcept : first(), last(last) {}\n\n  constexpr\
    \ iterator begin() const noexcept { return iterator{first}; }\n  constexpr iterator\
    \ end() const noexcept { return iterator{last}; }\n\n  constexpr reverse_iterator<iterator>\
    \ rbegin() const noexcept {\n    return reverse_iterator<iterator>(end());\n \
    \ }\n  constexpr reverse_iterator<iterator> rend() const noexcept {\n    return\
    \ reverse_iterator<iterator>(begin());\n  }\n};\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/*\n * @file range.hpp\n * @brief Range\n */\n\n#include\
    \ <iterator>\n\n#include \"../reverse_iterator.hpp\"\n\nnamespace workspace {\n\
    \ntemplate <class Index> class range {\n  Index first, last;\n\n public:\n  class\
    \ iterator {\n    Index iter;\n\n   public:\n    using difference_type = std::ptrdiff_t;\n\
    \    using value_type = Index;\n    using reference = typename std::add_const<Index>::type\
    \ &;\n    using pointer = iterator;\n    using iterator_category = std::bidirectional_iterator_tag;\n\
    \n    constexpr iterator(Index iter = Index()) noexcept : iter(iter) {}\n\n  \
    \  constexpr bool operator==(iterator const &rhs) const noexcept {\n      return\
    \ iter == rhs.iter;\n    }\n    constexpr bool operator!=(iterator const &rhs)\
    \ const noexcept {\n      return iter != rhs.iter;\n    }\n\n    constexpr iterator\
    \ &operator++() noexcept {\n      ++iter;\n      return *this;\n    }\n    constexpr\
    \ iterator &operator--() noexcept {\n      --iter;\n      return *this;\n    }\n\
    \n    constexpr reference operator*() const noexcept { return iter; }\n  };\n\n\
    \  constexpr range(Index first, Index last) noexcept\n      : first(first), last(last)\
    \ {}\n  constexpr range(Index last) noexcept : first(), last(last) {}\n\n  constexpr\
    \ iterator begin() const noexcept { return iterator{first}; }\n  constexpr iterator\
    \ end() const noexcept { return iterator{last}; }\n\n  constexpr reverse_iterator<iterator>\
    \ rbegin() const noexcept {\n    return reverse_iterator<iterator>(end());\n \
    \ }\n  constexpr reverse_iterator<iterator> rend() const noexcept {\n    return\
    \ reverse_iterator<iterator>(begin());\n  }\n};\n\n}  // namespace workspace\n"
  dependsOn:
  - src/utils/reverse_iterator.hpp
  isVerificationFile: false
  path: src/utils/py-like/range.hpp
  requiredBy:
  - src/utils/py-like/enumerate.hpp
  timestamp: '2020-12-04 02:14:28+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/utils/py-like/range.hpp
layout: document
redirect_from:
- /library/src/utils/py-like/range.hpp
- /library/src/utils/py-like/range.hpp.html
title: Range
---
