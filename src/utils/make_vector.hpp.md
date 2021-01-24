---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Multi-dimensional Vector
    links: []
  bundledCode: "#line 2 \"src/utils/make_vector.hpp\"\n\n/*\n * @file make_vector.hpp\n\
    \ * @brief Multi-dimensional Vector\n */\n\n#if __cplusplus >= 201703L\n\n#include\
    \ <tuple>\n#include <vector>\n\nnamespace workspace {\n\n/*\n * @brief Make a\
    \ multi-dimensional vector.\n * @tparam Tp type of the elements\n * @tparam N\
    \ dimension\n * @tparam S integer type\n * @param sizes The size of each dimension\n\
    \ * @param init The initial value\n */\ntemplate <typename Tp, size_t N, typename\
    \ S>\nconstexpr auto make_vector([[maybe_unused]] S* sizes, Tp const& init = Tp())\
    \ {\n  static_assert(std::is_convertible_v<S, size_t>);\n  if constexpr (N)\n\
    \    return std::vector(*sizes,\n                       make_vector<Tp, N - 1,\
    \ S>(std::next(sizes), init));\n  else\n    return init;\n}\n\n/*\n * @brief Make\
    \ a multi-dimensional vector.\n * @param sizes The size of each dimension\n *\
    \ @param init The initial value\n */\ntemplate <typename Tp, size_t N, typename\
    \ S>\nconstexpr auto make_vector(const S (&sizes)[N], Tp const& init = Tp()) {\n\
    \  return make_vector<Tp, N, S>((S*)sizes, init);\n}\n\n/*\n * @brief Make a multi-dimensional\
    \ vector.\n * @param sizes The size of each dimension\n * @param init The initial\
    \ value\n */\ntemplate <typename Tp, size_t N, typename S, size_t I = 0>\nconstexpr\
    \ auto make_vector([[maybe_unused]] std::array<S, N> const& sizes,\n         \
    \                  Tp const& init = Tp()) {\n  static_assert(std::is_convertible_v<S,\
    \ size_t>);\n  if constexpr (I == N)\n    return init;\n  else\n    return std::vector(sizes[I],\
    \ make_vector<Tp, N, S, I + 1>(sizes, init));\n}\n\n/*\n * @brief Make a multi-dimensional\
    \ vector.\n * @param sizes The size of each dimension\n * @param init The initial\
    \ value\n */\ntemplate <typename Tp, size_t N = SIZE_MAX, size_t I = 0, class...\
    \ Args>\nconstexpr auto make_vector([[maybe_unused]] std::tuple<Args...> const&\
    \ sizes,\n                           Tp const& init = Tp()) {\n  using tuple_type\
    \ = std::tuple<Args...>;\n  if constexpr (I == std::tuple_size_v<tuple_type> ||\
    \ I == N)\n    return init;\n  else {\n    static_assert(\n        std::is_convertible_v<std::tuple_element_t<I,\
    \ tuple_type>, size_t>);\n    return std::vector(std::get<I>(sizes),\n       \
    \                make_vector<Tp, N, I + 1>(sizes, init));\n  }\n}\n\n/*\n * @brief\
    \ Make a multi-dimensional vector.\n * @param sizes The size of each dimension\n\
    \ * @param init The initial value\n */\ntemplate <typename Tp, class Fst, class\
    \ Snd>\nconstexpr auto make_vector(std::pair<Fst, Snd> const& sizes,\n       \
    \                    Tp const& init = Tp()) {\n  static_assert(std::is_convertible_v<Fst,\
    \ size_t>);\n  static_assert(std::is_convertible_v<Snd, size_t>);\n  return make_vector({(size_t)sizes.first,\
    \ (size_t)sizes.second}, init);\n}\n\n}  // namespace workspace\n\n#endif\n"
  code: "#pragma once\n\n/*\n * @file make_vector.hpp\n * @brief Multi-dimensional\
    \ Vector\n */\n\n#if __cplusplus >= 201703L\n\n#include <tuple>\n#include <vector>\n\
    \nnamespace workspace {\n\n/*\n * @brief Make a multi-dimensional vector.\n *\
    \ @tparam Tp type of the elements\n * @tparam N dimension\n * @tparam S integer\
    \ type\n * @param sizes The size of each dimension\n * @param init The initial\
    \ value\n */\ntemplate <typename Tp, size_t N, typename S>\nconstexpr auto make_vector([[maybe_unused]]\
    \ S* sizes, Tp const& init = Tp()) {\n  static_assert(std::is_convertible_v<S,\
    \ size_t>);\n  if constexpr (N)\n    return std::vector(*sizes,\n            \
    \           make_vector<Tp, N - 1, S>(std::next(sizes), init));\n  else\n    return\
    \ init;\n}\n\n/*\n * @brief Make a multi-dimensional vector.\n * @param sizes\
    \ The size of each dimension\n * @param init The initial value\n */\ntemplate\
    \ <typename Tp, size_t N, typename S>\nconstexpr auto make_vector(const S (&sizes)[N],\
    \ Tp const& init = Tp()) {\n  return make_vector<Tp, N, S>((S*)sizes, init);\n\
    }\n\n/*\n * @brief Make a multi-dimensional vector.\n * @param sizes The size\
    \ of each dimension\n * @param init The initial value\n */\ntemplate <typename\
    \ Tp, size_t N, typename S, size_t I = 0>\nconstexpr auto make_vector([[maybe_unused]]\
    \ std::array<S, N> const& sizes,\n                           Tp const& init =\
    \ Tp()) {\n  static_assert(std::is_convertible_v<S, size_t>);\n  if constexpr\
    \ (I == N)\n    return init;\n  else\n    return std::vector(sizes[I], make_vector<Tp,\
    \ N, S, I + 1>(sizes, init));\n}\n\n/*\n * @brief Make a multi-dimensional vector.\n\
    \ * @param sizes The size of each dimension\n * @param init The initial value\n\
    \ */\ntemplate <typename Tp, size_t N = SIZE_MAX, size_t I = 0, class... Args>\n\
    constexpr auto make_vector([[maybe_unused]] std::tuple<Args...> const& sizes,\n\
    \                           Tp const& init = Tp()) {\n  using tuple_type = std::tuple<Args...>;\n\
    \  if constexpr (I == std::tuple_size_v<tuple_type> || I == N)\n    return init;\n\
    \  else {\n    static_assert(\n        std::is_convertible_v<std::tuple_element_t<I,\
    \ tuple_type>, size_t>);\n    return std::vector(std::get<I>(sizes),\n       \
    \                make_vector<Tp, N, I + 1>(sizes, init));\n  }\n}\n\n/*\n * @brief\
    \ Make a multi-dimensional vector.\n * @param sizes The size of each dimension\n\
    \ * @param init The initial value\n */\ntemplate <typename Tp, class Fst, class\
    \ Snd>\nconstexpr auto make_vector(std::pair<Fst, Snd> const& sizes,\n       \
    \                    Tp const& init = Tp()) {\n  static_assert(std::is_convertible_v<Fst,\
    \ size_t>);\n  static_assert(std::is_convertible_v<Snd, size_t>);\n  return make_vector({(size_t)sizes.first,\
    \ (size_t)sizes.second}, init);\n}\n\n}  // namespace workspace\n\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: src/utils/make_vector.hpp
  requiredBy: []
  timestamp: '2020-12-27 01:19:45+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/utils/make_vector.hpp
layout: document
redirect_from:
- /library/src/utils/make_vector.hpp
- /library/src/utils/make_vector.hpp.html
title: Multi-dimensional Vector
---
