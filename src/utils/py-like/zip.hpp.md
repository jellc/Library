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
    links: []
  bundledCode: "#line 2 \"src/utils/py-like/zip.hpp\"\n\n/*\n * @file zip.hpp\n *\
    \ @breif Zip\n */\n\n#include <tuple>\n\n#if __cplusplus >= 201703L\n\nnamespace\
    \ workspace {\n\ntemplate <class> struct zipped_iter;\n\ntemplate <class... Args>\
    \ class zipped {\n  using ref_tuple = std::tuple<Args...>;\n  ref_tuple args;\n\
    \n  template <size_t N = 0> constexpr auto begin_cat() const {\n    if constexpr\
    \ (N != std::tuple_size<ref_tuple>::value) {\n      return std::tuple_cat(std::tuple(std::begin(std::get<N>(args))),\n\
    \                            begin_cat<N + 1>());\n    } else\n      return std::tuple<>();\n\
    \  }\n\n  template <size_t N = 0> constexpr auto end_cat() const {\n    if constexpr\
    \ (N != std::tuple_size<ref_tuple>::value) {\n      return std::tuple_cat(std::tuple(std::end(std::get<N>(args))),\n\
    \                            end_cat<N + 1>());\n    } else\n      return std::tuple<>();\n\
    \  }\n\n  using iter_tuple = decltype(std::declval<zipped>().begin_cat());\n\n\
    \ public:\n  zipped(Args &&... args) : args(args...) {}\n\n  class iterator {\n\
    \    zipped_iter<iter_tuple> iters;\n\n    template <size_t N = 0> constexpr bool\
    \ equal(const iterator &rhs) const {\n      if constexpr (N != std::tuple_size<iter_tuple>::value)\
    \ {\n        return std::get<N>(iters) == std::get<N>(rhs.iters) ||\n        \
    \       equal<N + 1>(rhs);\n      } else\n        return false;\n    }\n\n   \
    \ template <size_t N = 0> constexpr void increment() {\n      if constexpr (N\
    \ != std::tuple_size<iter_tuple>::value) {\n        ++std::get<N>(iters);\n  \
    \      increment<N + 1>();\n      }\n    }\n\n    template <size_t N = 0> constexpr\
    \ void decrement() {\n      if constexpr (N != std::tuple_size<iter_tuple>::value)\
    \ {\n        --std::get<N>(iters);\n        decrement<N + 1>();\n      }\n   \
    \ }\n\n   public:\n    using difference_type = std::ptrdiff_t;\n    using value_type\
    \ = zipped_iter<iter_tuple>;\n    using reference = zipped_iter<iter_tuple> &;\n\
    \    using pointer = iterator;\n    using iterator_category = std::bidirectional_iterator_tag;\n\
    \n    constexpr iterator() = default;\n    constexpr iterator(iter_tuple const\
    \ &iters) : iters(iters) {}\n\n    constexpr bool operator==(const iterator &rhs)\
    \ const { return equal(rhs); }\n    constexpr bool operator!=(const iterator &rhs)\
    \ const { return !equal(rhs); }\n\n    constexpr iterator &operator++() {\n  \
    \    increment();\n      return *this;\n    }\n    constexpr iterator &operator--()\
    \ {\n      decrement();\n      return *this;\n    }\n\n    constexpr auto &operator*()\
    \ { return iters; }\n  };\n\n  constexpr iterator begin() const { return iterator{begin_cat()};\
    \ }\n  constexpr iterator end() const { return iterator{end_cat()}; }\n\n  constexpr\
    \ std::reverse_iterator<iterator> rbegin() const {\n    return std::make_reverse_iterator(end());\n\
    \  }\n  constexpr std::reverse_iterator<iterator> rend() const {\n    return std::make_reverse_iterator(begin());\n\
    \  }\n};\n\ntemplate <class Iter_tuple> struct zipped_iter : Iter_tuple {\n  constexpr\
    \ zipped_iter(Iter_tuple const &__t) : Iter_tuple::tuple(__t) {}\n\n  template\
    \ <size_t N> friend constexpr auto &get(zipped_iter<Iter_tuple> &__z) {\n    return\
    \ *std::get<N>(__z);\n  }\n\n  template <size_t N> friend constexpr auto get(zipped_iter<Iter_tuple>\
    \ &&__z) {\n    return std::move(*std::get<N>(__z));\n  }\n};\n\n}  // namespace\
    \ workspace\n\nnamespace std {\n\ntemplate <size_t N, class Iter_tuple>\nstruct\
    \ tuple_element<N, workspace::zipped_iter<Iter_tuple>> {\n  using type = typename\
    \ remove_reference<typename iterator_traits<\n      typename tuple_element<N,\
    \ Iter_tuple>::type>::reference>::type;\n};\n\ntemplate <class Iter_tuple>\nstruct\
    \ tuple_size<workspace::zipped_iter<Iter_tuple>> : tuple_size<Iter_tuple> {\n\
    };\n\n}  // namespace std\n\nnamespace workspace {\n\ntemplate <class... Args>\
    \ constexpr auto zip(Args &&... args) {\n  return zipped<Args...>(std::forward<Args>(args)...);\n\
    }\n\ntemplate <class... Args>\nconstexpr auto zip(std::initializer_list<Args>\
    \ &&... args) {\n  return zipped<std::initializer_list<Args>...>(\n      std::forward<std::initializer_list<Args>>(args)...);\n\
    }\n\n}  // namespace workspace\n\n#endif\n"
  code: "#pragma once\n\n/*\n * @file zip.hpp\n * @breif Zip\n */\n\n#include <tuple>\n\
    \n#if __cplusplus >= 201703L\n\nnamespace workspace {\n\ntemplate <class> struct\
    \ zipped_iter;\n\ntemplate <class... Args> class zipped {\n  using ref_tuple =\
    \ std::tuple<Args...>;\n  ref_tuple args;\n\n  template <size_t N = 0> constexpr\
    \ auto begin_cat() const {\n    if constexpr (N != std::tuple_size<ref_tuple>::value)\
    \ {\n      return std::tuple_cat(std::tuple(std::begin(std::get<N>(args))),\n\
    \                            begin_cat<N + 1>());\n    } else\n      return std::tuple<>();\n\
    \  }\n\n  template <size_t N = 0> constexpr auto end_cat() const {\n    if constexpr\
    \ (N != std::tuple_size<ref_tuple>::value) {\n      return std::tuple_cat(std::tuple(std::end(std::get<N>(args))),\n\
    \                            end_cat<N + 1>());\n    } else\n      return std::tuple<>();\n\
    \  }\n\n  using iter_tuple = decltype(std::declval<zipped>().begin_cat());\n\n\
    \ public:\n  zipped(Args &&... args) : args(args...) {}\n\n  class iterator {\n\
    \    zipped_iter<iter_tuple> iters;\n\n    template <size_t N = 0> constexpr bool\
    \ equal(const iterator &rhs) const {\n      if constexpr (N != std::tuple_size<iter_tuple>::value)\
    \ {\n        return std::get<N>(iters) == std::get<N>(rhs.iters) ||\n        \
    \       equal<N + 1>(rhs);\n      } else\n        return false;\n    }\n\n   \
    \ template <size_t N = 0> constexpr void increment() {\n      if constexpr (N\
    \ != std::tuple_size<iter_tuple>::value) {\n        ++std::get<N>(iters);\n  \
    \      increment<N + 1>();\n      }\n    }\n\n    template <size_t N = 0> constexpr\
    \ void decrement() {\n      if constexpr (N != std::tuple_size<iter_tuple>::value)\
    \ {\n        --std::get<N>(iters);\n        decrement<N + 1>();\n      }\n   \
    \ }\n\n   public:\n    using difference_type = std::ptrdiff_t;\n    using value_type\
    \ = zipped_iter<iter_tuple>;\n    using reference = zipped_iter<iter_tuple> &;\n\
    \    using pointer = iterator;\n    using iterator_category = std::bidirectional_iterator_tag;\n\
    \n    constexpr iterator() = default;\n    constexpr iterator(iter_tuple const\
    \ &iters) : iters(iters) {}\n\n    constexpr bool operator==(const iterator &rhs)\
    \ const { return equal(rhs); }\n    constexpr bool operator!=(const iterator &rhs)\
    \ const { return !equal(rhs); }\n\n    constexpr iterator &operator++() {\n  \
    \    increment();\n      return *this;\n    }\n    constexpr iterator &operator--()\
    \ {\n      decrement();\n      return *this;\n    }\n\n    constexpr auto &operator*()\
    \ { return iters; }\n  };\n\n  constexpr iterator begin() const { return iterator{begin_cat()};\
    \ }\n  constexpr iterator end() const { return iterator{end_cat()}; }\n\n  constexpr\
    \ std::reverse_iterator<iterator> rbegin() const {\n    return std::make_reverse_iterator(end());\n\
    \  }\n  constexpr std::reverse_iterator<iterator> rend() const {\n    return std::make_reverse_iterator(begin());\n\
    \  }\n};\n\ntemplate <class Iter_tuple> struct zipped_iter : Iter_tuple {\n  constexpr\
    \ zipped_iter(Iter_tuple const &__t) : Iter_tuple::tuple(__t) {}\n\n  template\
    \ <size_t N> friend constexpr auto &get(zipped_iter<Iter_tuple> &__z) {\n    return\
    \ *std::get<N>(__z);\n  }\n\n  template <size_t N> friend constexpr auto get(zipped_iter<Iter_tuple>\
    \ &&__z) {\n    return std::move(*std::get<N>(__z));\n  }\n};\n\n}  // namespace\
    \ workspace\n\nnamespace std {\n\ntemplate <size_t N, class Iter_tuple>\nstruct\
    \ tuple_element<N, workspace::zipped_iter<Iter_tuple>> {\n  using type = typename\
    \ remove_reference<typename iterator_traits<\n      typename tuple_element<N,\
    \ Iter_tuple>::type>::reference>::type;\n};\n\ntemplate <class Iter_tuple>\nstruct\
    \ tuple_size<workspace::zipped_iter<Iter_tuple>> : tuple_size<Iter_tuple> {\n\
    };\n\n}  // namespace std\n\nnamespace workspace {\n\ntemplate <class... Args>\
    \ constexpr auto zip(Args &&... args) {\n  return zipped<Args...>(std::forward<Args>(args)...);\n\
    }\n\ntemplate <class... Args>\nconstexpr auto zip(std::initializer_list<Args>\
    \ &&... args) {\n  return zipped<std::initializer_list<Args>...>(\n      std::forward<std::initializer_list<Args>>(args)...);\n\
    }\n\n}  // namespace workspace\n\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: src/utils/py-like/zip.hpp
  requiredBy:
  - src/utils/py-like/enumerate.hpp
  timestamp: '2020-12-03 02:46:17+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/utils/py-like/zip.hpp
layout: document
redirect_from:
- /library/src/utils/py-like/zip.hpp
- /library/src/utils/py-like/zip.hpp.html
title: src/utils/py-like/zip.hpp
---
