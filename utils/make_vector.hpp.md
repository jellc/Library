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
    links: []
  bundledCode: "#line 2 \"utils/make_vector.hpp\"\n#if __cplusplus >= 201703L\n#include\
    \ <tuple>\n#include <vector>\nnamespace workspace {\ntemplate <typename T, typename\
    \ S, size_t N>\nconstexpr auto make_vector(S* sizes, T const& init = T()) {\n\
    \  if constexpr (N)\n    return std::vector(*sizes,\n                       make_vector<T,\
    \ S, N - 1>(std::next(sizes), init));\n  else\n    return init;\n}\ntemplate <typename\
    \ T, typename S, size_t N,\n          std::enable_if_t<std::is_convertible_v<S,\
    \ size_t>>* = nullptr>\nconstexpr auto make_vector(const S (&sizes)[N], T const&\
    \ init = T()) {\n  return make_vector<T, S, N>((S*)sizes, init);\n}\ntemplate\
    \ <typename T, size_t N, size_t I = 0>\nconstexpr auto make_vector(std::array<size_t,\
    \ N> const& array,\n                           T const& init = T()) {\n  if constexpr\
    \ (I == N)\n    return init;\n  else\n    return std::vector(array[I], make_vector<T,\
    \ N, I + 1>(array, init));\n}\ntemplate <typename T, size_t I = 0, class... Args>\n\
    constexpr auto make_vector(std::tuple<Args...> const& tuple,\n               \
    \            T const& init = T()) {\n  using tuple_type = std::tuple<Args...>;\n\
    \  if constexpr (I == tuple_size_v<tuple_type>)\n    return init;\n  else {\n\
    \    static_assert(\n        std::is_convertible_v<tuple_element_t<I, tuple_type>,\
    \ size_t>);\n    return std::vector(get<I>(tuple), make_vector<T, I + 1>(tuple,\
    \ init));\n  }\n}\ntemplate <typename T, class Fst, class Snd>\nconstexpr auto\
    \ make_vector(std::pair<Fst, Snd> const& pair,\n                           T const&\
    \ init = T()) {\n  return make_vector((size_t[2]){pair.first, pair.second}, init);\n\
    }\n}  // namespace workspace\n#endif\n"
  code: "#pragma once\n#if __cplusplus >= 201703L\n#include <tuple>\n#include <vector>\n\
    namespace workspace {\ntemplate <typename T, typename S, size_t N>\nconstexpr\
    \ auto make_vector(S* sizes, T const& init = T()) {\n  if constexpr (N)\n    return\
    \ std::vector(*sizes,\n                       make_vector<T, S, N - 1>(std::next(sizes),\
    \ init));\n  else\n    return init;\n}\ntemplate <typename T, typename S, size_t\
    \ N,\n          std::enable_if_t<std::is_convertible_v<S, size_t>>* = nullptr>\n\
    constexpr auto make_vector(const S (&sizes)[N], T const& init = T()) {\n  return\
    \ make_vector<T, S, N>((S*)sizes, init);\n}\ntemplate <typename T, size_t N, size_t\
    \ I = 0>\nconstexpr auto make_vector(std::array<size_t, N> const& array,\n   \
    \                        T const& init = T()) {\n  if constexpr (I == N)\n   \
    \ return init;\n  else\n    return std::vector(array[I], make_vector<T, N, I +\
    \ 1>(array, init));\n}\ntemplate <typename T, size_t I = 0, class... Args>\nconstexpr\
    \ auto make_vector(std::tuple<Args...> const& tuple,\n                       \
    \    T const& init = T()) {\n  using tuple_type = std::tuple<Args...>;\n  if constexpr\
    \ (I == tuple_size_v<tuple_type>)\n    return init;\n  else {\n    static_assert(\n\
    \        std::is_convertible_v<tuple_element_t<I, tuple_type>, size_t>);\n   \
    \ return std::vector(get<I>(tuple), make_vector<T, I + 1>(tuple, init));\n  }\n\
    }\ntemplate <typename T, class Fst, class Snd>\nconstexpr auto make_vector(std::pair<Fst,\
    \ Snd> const& pair,\n                           T const& init = T()) {\n  return\
    \ make_vector((size_t[2]){pair.first, pair.second}, init);\n}\n}  // namespace\
    \ workspace\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: utils/make_vector.hpp
  requiredBy:
  - utils.hpp
  - template.cpp
  timestamp: '2020-10-18 14:24:41+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utils/make_vector.hpp
layout: document
redirect_from:
- /library/utils/make_vector.hpp
- /library/utils/make_vector.hpp.html
title: utils/make_vector.hpp
---
