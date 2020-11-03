---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: template.cpp
    title: template.cpp
  - icon: ':warning:'
    path: utils.hpp
    title: utils.hpp
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: make a multi-dimensional vector.
    links: []
  bundledCode: "#line 2 \"utils/make_vector.hpp\"\n\n#if __cplusplus >= 201703L\n\n\
    #include <tuple>\n#include <vector>\n\nnamespace workspace {\n\n/*\n * @brief\
    \ make a multi-dimensional vector.\n * @tparam Tp type of the elements\n * @tparam\
    \ S integer type\n * @tparam N dimension\n * @param sizes size of each dimension\n\
    \ * @param init initial value\n */\ntemplate <typename Tp, typename S, size_t\
    \ N>\nconstexpr auto make_vector(S* sizes, Tp const& init = Tp()) {\n  static_assert(std::is_convertible_v<S,\
    \ size_t>);\n  if constexpr (N)\n    return std::vector(*sizes,\n            \
    \           make_vector<Tp, S, N - 1>(std::next(sizes), init));\n  else\n    return\
    \ init;\n}\n\n/*\n * @brief make a multi-dimensional vector.\n * @param sizes\
    \ size of each dimension\n * @param init initial value\n */\ntemplate <typename\
    \ Tp, typename S, size_t N>\nconstexpr auto make_vector(const S (&sizes)[N], Tp\
    \ const& init = Tp()) {\n  return make_vector<Tp, S, N>((S*)sizes, init);\n}\n\
    \n/*\n * @brief make a multi-dimensional vector.\n * @param sizes size of each\
    \ dimension\n * @param init initial value\n */\ntemplate <typename Tp, typename\
    \ S, size_t N, size_t I = 0>\nconstexpr auto make_vector(std::array<S, N> const&\
    \ sizes,\n                           Tp const& init = Tp()) {\n  static_assert(std::is_convertible_v<S,\
    \ size_t>);\n  if constexpr (I == N)\n    return init;\n  else\n    return std::vector(sizes[I],\
    \ make_vector<Tp, S, N, I + 1>(sizes, init));\n}\n\n/*\n * @brief make a multi-dimensional\
    \ vector.\n * @param sizes size of each dimension\n * @param init initial value\n\
    \ */\ntemplate <typename Tp, size_t I = 0, class... Args>\nconstexpr auto make_vector(std::tuple<Args...>\
    \ const& sizes,\n                           Tp const& init = Tp()) {\n  using\
    \ tuple_type = std::tuple<Args...>;\n  if constexpr (I == tuple_size_v<tuple_type>)\n\
    \    return init;\n  else {\n    static_assert(\n        std::is_convertible_v<tuple_element_t<I,\
    \ tuple_type>, size_t>);\n    return std::vector(get<I>(sizes), make_vector<Tp,\
    \ I + 1>(sizes, init));\n  }\n}\n\n/*\n * @brief make a multi-dimensional vector.\n\
    \ * @param sizes size of each dimension\n * @param init initial value\n */\ntemplate\
    \ <typename Tp, class Fst, class Snd>\nconstexpr auto make_vector(std::pair<Fst,\
    \ Snd> const& sizes,\n                           Tp const& init = Tp()) {\n  static_assert(std::is_convertible_v<Fst,\
    \ size_t>);\n  static_assert(std::is_convertible_v<Snd, size_t>);\n  return make_vector({(size_t)sizes.first,\
    \ (size_t)sizes.second}, init);\n}\n\n}  // namespace workspace\n\n#endif\n"
  code: "#pragma once\n\n#if __cplusplus >= 201703L\n\n#include <tuple>\n#include\
    \ <vector>\n\nnamespace workspace {\n\n/*\n * @brief make a multi-dimensional\
    \ vector.\n * @tparam Tp type of the elements\n * @tparam S integer type\n * @tparam\
    \ N dimension\n * @param sizes size of each dimension\n * @param init initial\
    \ value\n */\ntemplate <typename Tp, typename S, size_t N>\nconstexpr auto make_vector(S*\
    \ sizes, Tp const& init = Tp()) {\n  static_assert(std::is_convertible_v<S, size_t>);\n\
    \  if constexpr (N)\n    return std::vector(*sizes,\n                       make_vector<Tp,\
    \ S, N - 1>(std::next(sizes), init));\n  else\n    return init;\n}\n\n/*\n * @brief\
    \ make a multi-dimensional vector.\n * @param sizes size of each dimension\n *\
    \ @param init initial value\n */\ntemplate <typename Tp, typename S, size_t N>\n\
    constexpr auto make_vector(const S (&sizes)[N], Tp const& init = Tp()) {\n  return\
    \ make_vector<Tp, S, N>((S*)sizes, init);\n}\n\n/*\n * @brief make a multi-dimensional\
    \ vector.\n * @param sizes size of each dimension\n * @param init initial value\n\
    \ */\ntemplate <typename Tp, typename S, size_t N, size_t I = 0>\nconstexpr auto\
    \ make_vector(std::array<S, N> const& sizes,\n                           Tp const&\
    \ init = Tp()) {\n  static_assert(std::is_convertible_v<S, size_t>);\n  if constexpr\
    \ (I == N)\n    return init;\n  else\n    return std::vector(sizes[I], make_vector<Tp,\
    \ S, N, I + 1>(sizes, init));\n}\n\n/*\n * @brief make a multi-dimensional vector.\n\
    \ * @param sizes size of each dimension\n * @param init initial value\n */\ntemplate\
    \ <typename Tp, size_t I = 0, class... Args>\nconstexpr auto make_vector(std::tuple<Args...>\
    \ const& sizes,\n                           Tp const& init = Tp()) {\n  using\
    \ tuple_type = std::tuple<Args...>;\n  if constexpr (I == tuple_size_v<tuple_type>)\n\
    \    return init;\n  else {\n    static_assert(\n        std::is_convertible_v<tuple_element_t<I,\
    \ tuple_type>, size_t>);\n    return std::vector(get<I>(sizes), make_vector<Tp,\
    \ I + 1>(sizes, init));\n  }\n}\n\n/*\n * @brief make a multi-dimensional vector.\n\
    \ * @param sizes size of each dimension\n * @param init initial value\n */\ntemplate\
    \ <typename Tp, class Fst, class Snd>\nconstexpr auto make_vector(std::pair<Fst,\
    \ Snd> const& sizes,\n                           Tp const& init = Tp()) {\n  static_assert(std::is_convertible_v<Fst,\
    \ size_t>);\n  static_assert(std::is_convertible_v<Snd, size_t>);\n  return make_vector({(size_t)sizes.first,\
    \ (size_t)sizes.second}, init);\n}\n\n}  // namespace workspace\n\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: utils/make_vector.hpp
  requiredBy:
  - template.cpp
  - utils.hpp
  timestamp: '2020-11-03 17:34:35+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utils/make_vector.hpp
layout: document
redirect_from:
- /library/utils/make_vector.hpp
- /library/utils/make_vector.hpp.html
title: make a multi-dimensional vector.
---
