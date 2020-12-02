---
data:
  _extendedDependsOn: []
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
    \ * @brief Range\n */\n\n#include <iterator>\n\nnamespace workspace {\n\ntemplate\
    \ <class Index> class range {\n  Index first, last;\n\n public:\n  class iterator\
    \ {\n    Index iter;\n\n   public:\n    using difference_type = std::ptrdiff_t;\n\
    \    using value_type = Index;\n    using reference = typename std::add_const<Index>::type\
    \ &;\n    using pointer = iterator;\n    using iterator_category = std::bidirectional_iterator_tag;\n\
    \n    constexpr iterator(Index iter = Index()) : iter(iter) {}\n\n    constexpr\
    \ bool operator==(iterator const &rhs) const {\n      return iter == rhs.iter;\n\
    \    }\n    constexpr bool operator!=(iterator const &rhs) const {\n      return\
    \ iter != rhs.iter;\n    }\n\n    constexpr iterator &operator++() {\n      ++iter;\n\
    \      return *this;\n    }\n    constexpr iterator &operator--() {\n      --iter;\n\
    \      return *this;\n    }\n\n    constexpr reference operator*() const { return\
    \ iter; }\n  };\n\n  range(Index first, Index last) : first(first), last(last)\
    \ {}\n  range(Index last) : first(), last(last) {}\n\n  constexpr iterator begin()\
    \ const { return iterator{first}; }\n  constexpr iterator end() const { return\
    \ iterator{last}; }\n\n  constexpr std::reverse_iterator<iterator> rbegin() const\
    \ {\n    return std::make_reverse_iterator(end());\n  }\n  constexpr std::reverse_iterator<iterator>\
    \ rend() const {\n    return std::make_reverse_iterator(begin());\n  }\n};\n\n\
    }  // namespace workspace\n"
  code: "#pragma once\n\n/*\n * @file range.hpp\n * @brief Range\n */\n\n#include\
    \ <iterator>\n\nnamespace workspace {\n\ntemplate <class Index> class range {\n\
    \  Index first, last;\n\n public:\n  class iterator {\n    Index iter;\n\n   public:\n\
    \    using difference_type = std::ptrdiff_t;\n    using value_type = Index;\n\
    \    using reference = typename std::add_const<Index>::type &;\n    using pointer\
    \ = iterator;\n    using iterator_category = std::bidirectional_iterator_tag;\n\
    \n    constexpr iterator(Index iter = Index()) : iter(iter) {}\n\n    constexpr\
    \ bool operator==(iterator const &rhs) const {\n      return iter == rhs.iter;\n\
    \    }\n    constexpr bool operator!=(iterator const &rhs) const {\n      return\
    \ iter != rhs.iter;\n    }\n\n    constexpr iterator &operator++() {\n      ++iter;\n\
    \      return *this;\n    }\n    constexpr iterator &operator--() {\n      --iter;\n\
    \      return *this;\n    }\n\n    constexpr reference operator*() const { return\
    \ iter; }\n  };\n\n  range(Index first, Index last) : first(first), last(last)\
    \ {}\n  range(Index last) : first(), last(last) {}\n\n  constexpr iterator begin()\
    \ const { return iterator{first}; }\n  constexpr iterator end() const { return\
    \ iterator{last}; }\n\n  constexpr std::reverse_iterator<iterator> rbegin() const\
    \ {\n    return std::make_reverse_iterator(end());\n  }\n  constexpr std::reverse_iterator<iterator>\
    \ rend() const {\n    return std::make_reverse_iterator(begin());\n  }\n};\n\n\
    }  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/utils/py-like/range.hpp
  requiredBy:
  - src/utils/py-like/enumerate.hpp
  timestamp: '2020-12-03 02:46:17+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/utils/py-like/range.hpp
layout: document
redirect_from:
- /library/src/utils/py-like/range.hpp
- /library/src/utils/py-like/range.hpp.html
title: Range
---
