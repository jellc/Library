---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Reference List
    links: []
  bundledCode: "#line 2 \"src/utils/reference_list.hpp\"\n\n/**\n * @file reference_list.hpp\n\
    \ * @brief Reference List\n */\n\n#include <vector>\n\nnamespace workspace {\n\
    \n/**\n * @brief Reference list.\n */\ntemplate <class _Tp>\nclass reference_list\
    \ : public std::vector<std::reference_wrapper<_Tp>> {\n public:\n  using container_type\
    \ = std::vector<std::reference_wrapper<_Tp>>;\n\n  reference_list() noexcept =\
    \ default;\n\n  template <class... _Args>\n  reference_list(_Tp &__x, _Args &&...__args)\
    \ noexcept\n      : container_type{__x, __args...} {}\n\n  class iterator : public\
    \ container_type::iterator {\n    using base_iterator = typename container_type::iterator;\n\
    \n   public:\n    using reference = _Tp &;\n\n    iterator() noexcept = default;\n\
    \    iterator(const base_iterator &__x) noexcept : base_iterator(__x) {}\n\n \
    \   decltype(auto) operator*() const noexcept {\n      return base_iterator::operator*().get();\n\
    \    }\n\n    decltype(auto) operator->() const noexcept {\n      return std::addressof(operator*());\n\
    \    }\n  };\n\n  class const_iterator : public container_type::const_iterator\
    \ {\n    using base_iterator = typename container_type::const_iterator;\n\n  \
    \ public:\n    using reference = const _Tp &;\n\n    const_iterator() noexcept\
    \ = default;\n    const_iterator(const base_iterator &__x) noexcept : base_iterator(__x)\
    \ {}\n\n    decltype(auto) operator*() const noexcept {\n      return base_iterator::operator*().get();\n\
    \    }\n\n    decltype(auto) operator->() const noexcept {\n      return std::addressof(operator*());\n\
    \    }\n  };\n\n  decltype(auto) begin() noexcept { return iterator(container_type::begin());\
    \ }\n  decltype(auto) begin() const noexcept {\n    return const_iterator(container_type::begin());\n\
    \  }\n\n  decltype(auto) end() noexcept { return iterator(container_type::end());\
    \ }\n  decltype(auto) end() const noexcept {\n    return const_iterator(container_type::end());\n\
    \  }\n\n  decltype(auto) front() noexcept { return container_type::front().get();\
    \ }\n\n  decltype(auto) back() noexcept { return container_type::back().get();\
    \ }\n\n  decltype(auto) operator[](typename container_type::size_type __i) noexcept\
    \ {\n    return container_type::operator[](__i).get();\n  }\n\n  using value_type\
    \ = typename iterator::value_type;\n  using reference = typename iterator::reference;\n\
    };\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file reference_list.hpp\n * @brief Reference List\n\
    \ */\n\n#include <vector>\n\nnamespace workspace {\n\n/**\n * @brief Reference\
    \ list.\n */\ntemplate <class _Tp>\nclass reference_list : public std::vector<std::reference_wrapper<_Tp>>\
    \ {\n public:\n  using container_type = std::vector<std::reference_wrapper<_Tp>>;\n\
    \n  reference_list() noexcept = default;\n\n  template <class... _Args>\n  reference_list(_Tp\
    \ &__x, _Args &&...__args) noexcept\n      : container_type{__x, __args...} {}\n\
    \n  class iterator : public container_type::iterator {\n    using base_iterator\
    \ = typename container_type::iterator;\n\n   public:\n    using reference = _Tp\
    \ &;\n\n    iterator() noexcept = default;\n    iterator(const base_iterator &__x)\
    \ noexcept : base_iterator(__x) {}\n\n    decltype(auto) operator*() const noexcept\
    \ {\n      return base_iterator::operator*().get();\n    }\n\n    decltype(auto)\
    \ operator->() const noexcept {\n      return std::addressof(operator*());\n \
    \   }\n  };\n\n  class const_iterator : public container_type::const_iterator\
    \ {\n    using base_iterator = typename container_type::const_iterator;\n\n  \
    \ public:\n    using reference = const _Tp &;\n\n    const_iterator() noexcept\
    \ = default;\n    const_iterator(const base_iterator &__x) noexcept : base_iterator(__x)\
    \ {}\n\n    decltype(auto) operator*() const noexcept {\n      return base_iterator::operator*().get();\n\
    \    }\n\n    decltype(auto) operator->() const noexcept {\n      return std::addressof(operator*());\n\
    \    }\n  };\n\n  decltype(auto) begin() noexcept { return iterator(container_type::begin());\
    \ }\n  decltype(auto) begin() const noexcept {\n    return const_iterator(container_type::begin());\n\
    \  }\n\n  decltype(auto) end() noexcept { return iterator(container_type::end());\
    \ }\n  decltype(auto) end() const noexcept {\n    return const_iterator(container_type::end());\n\
    \  }\n\n  decltype(auto) front() noexcept { return container_type::front().get();\
    \ }\n\n  decltype(auto) back() noexcept { return container_type::back().get();\
    \ }\n\n  decltype(auto) operator[](typename container_type::size_type __i) noexcept\
    \ {\n    return container_type::operator[](__i).get();\n  }\n\n  using value_type\
    \ = typename iterator::value_type;\n  using reference = typename iterator::reference;\n\
    };\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/utils/reference_list.hpp
  requiredBy: []
  timestamp: '2021-05-28 00:29:58+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/utils/reference_list.hpp
layout: document
redirect_from:
- /library/src/utils/reference_list.hpp
- /library/src/utils/reference_list.hpp.html
title: Reference List
---
