---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/utils/iterator/category.hpp
    title: Iterator Category
  - icon: ':heavy_check_mark:'
    path: src/utils/iterator/reverse.hpp
    title: Reverse Iterator
  _extendedRequiredBy:
  - icon: ':warning:'
    path: src/utils/py-like/enumerate.hpp
    title: Enumerate
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/library-checker/number_of_substrings.test.cpp
    title: test/library-checker/number_of_substrings.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Zip
    links: []
  bundledCode: "#line 2 \"src/utils/py-like/zip.hpp\"\n\n/*\n * @file zip.hpp\n *\
    \ @brief Zip\n */\n\n#include <cstddef>\n#include <tuple>\n#include <vector>\n\
    \n#line 2 \"src/utils/iterator/category.hpp\"\n\n/*\n * @file category.hpp\n *\
    \ @brief Iterator Category\n */\n\n#line 10 \"src/utils/iterator/category.hpp\"\
    \n\nnamespace workspace {\n\n/*\n * @tparam Tuple Tuple of iterator types\n */\n\
    template <class Tuple, size_t N = std::tuple_size<Tuple>::value - 1>\nstruct common_iterator_category\
    \ {\n  using type = typename std::common_type<\n      typename common_iterator_category<Tuple,\
    \ N - 1>::type,\n      typename std::iterator_traits<typename std::tuple_element<\n\
    \          N, Tuple>::type>::iterator_category>::type;\n};\n\ntemplate <class\
    \ Tuple> struct common_iterator_category<Tuple, 0> {\n  using type = typename\
    \ std::iterator_traits<\n      typename std::tuple_element<0, Tuple>::type>::iterator_category;\n\
    };\n\n}  // namespace workspace\n#line 2 \"src/utils/iterator/reverse.hpp\"\n\n\
    /*\n * @file reverse_iterator.hpp\n * @brief Reverse Iterator\n */\n\n#if __cplusplus\
    \ >= 201703L\n\n#include <iterator>\n#include <optional>\n\nnamespace workspace\
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
    \n#endif\n#line 14 \"src/utils/py-like/zip.hpp\"\n\n#if __cplusplus >= 201703L\n\
    \nnamespace workspace {\n\ntemplate <class> struct zipped_iterator;\n\ntemplate\
    \ <class...> struct zipped_iterator_tuple;\n\ntemplate <class... Args> class zipped\
    \ {\n  using ref_tuple = std::tuple<Args...>;\n  ref_tuple args;\n\n  template\
    \ <size_t N = 0> constexpr auto begin_cat() const noexcept {\n    if constexpr\
    \ (N != std::tuple_size<ref_tuple>::value) {\n      return std::tuple_cat(std::tuple(std::begin(std::get<N>(args))),\n\
    \                            begin_cat<N + 1>());\n    } else\n      return std::tuple<>();\n\
    \  }\n\n  template <size_t N = 0> constexpr auto end_cat() const noexcept {\n\
    \    if constexpr (N != std::tuple_size<ref_tuple>::value) {\n      return std::tuple_cat(std::tuple(std::end(std::get<N>(args))),\n\
    \                            end_cat<N + 1>());\n    } else\n      return std::tuple<>();\n\
    \  }\n\n public:\n  constexpr zipped(Args &&... args) noexcept : args(args...)\
    \ {}\n\n  class iterator {\n    using base_tuple = typename zipped_iterator_tuple<Args...>::type;\n\
    \n   public:\n    using iterator_category =\n        typename common_iterator_category<base_tuple>::type;\n\
    \    using difference_type = std::ptrdiff_t;\n    using value_type = zipped_iterator<base_tuple>;\n\
    \    using reference = zipped_iterator<base_tuple> &;\n    using pointer = iterator;\n\
    \n   protected:\n    value_type current;\n\n    template <size_t N = 0>\n    constexpr\
    \ bool equal(const iterator &rhs) const noexcept {\n      if constexpr (N != std::tuple_size<base_tuple>::value)\
    \ {\n        return std::get<N>(current) == std::get<N>(rhs.current) ||\n    \
    \           equal<N + 1>(rhs);\n      } else\n        return false;\n    }\n\n\
    \    template <size_t N = 0> constexpr void increment() noexcept {\n      if constexpr\
    \ (N != std::tuple_size<base_tuple>::value) {\n        ++std::get<N>(current);\n\
    \        increment<N + 1>();\n      }\n    }\n\n    template <size_t N = 0> constexpr\
    \ void decrement() noexcept {\n      if constexpr (N != std::tuple_size<base_tuple>::value)\
    \ {\n        --std::get<N>(current);\n        decrement<N + 1>();\n      }\n \
    \   }\n\n   public:\n    constexpr iterator() noexcept = default;\n    constexpr\
    \ iterator(base_tuple const &current) noexcept : current(current) {}\n\n    constexpr\
    \ bool operator==(const iterator &rhs) const noexcept {\n      return equal(rhs);\n\
    \    }\n    constexpr bool operator!=(const iterator &rhs) const noexcept {\n\
    \      return !equal(rhs);\n    }\n\n    constexpr iterator &operator++() noexcept\
    \ {\n      increment();\n      return *this;\n    }\n    constexpr iterator &operator--()\
    \ noexcept {\n      decrement();\n      return *this;\n    }\n\n    constexpr\
    \ reference operator*() noexcept { return current; }\n  };\n\n  constexpr iterator\
    \ begin() const noexcept { return iterator{begin_cat()}; }\n  constexpr iterator\
    \ end() const noexcept { return iterator{end_cat()}; }\n\n  constexpr reverse_iterator<iterator>\
    \ rbegin() const noexcept {\n    return reverse_iterator<iterator>{end()};\n \
    \ }\n  constexpr reverse_iterator<iterator> rend() const noexcept {\n    return\
    \ reverse_iterator<iterator>{begin()};\n  }\n};\n\ntemplate <class Tp, class...\
    \ Args> struct zipped_iterator_tuple<Tp, Args...> {\n  using type = decltype(std::tuple_cat(\n\
    \      std::declval<std::tuple<decltype(std::begin(std::declval<Tp>()))>>(),\n\
    \      std::declval<typename zipped_iterator_tuple<Args...>::type>()));\n};\n\n\
    template <> struct zipped_iterator_tuple<> { using type = std::tuple<>; };\n\n\
    template <class Iter_tuple> struct zipped_iterator : Iter_tuple {\n  constexpr\
    \ zipped_iterator(Iter_tuple const &__t) noexcept\n      : Iter_tuple::tuple(__t)\
    \ {}\n\n  template <size_t N>\n  friend constexpr auto &get(zipped_iterator<Iter_tuple>\
    \ const &__z) noexcept {\n    return *std::get<N>(__z);\n  }\n\n  template <size_t\
    \ N>\n  friend constexpr auto get(zipped_iterator<Iter_tuple> const &&__z) noexcept\
    \ {\n    return std::move(*std::get<N>(__z));\n  }\n};\n\n}  // namespace workspace\n\
    \nnamespace std {\n\ntemplate <size_t N, class Iter_tuple>\nstruct tuple_element<N,\
    \ workspace::zipped_iterator<Iter_tuple>> {\n  using type = typename remove_reference<typename\
    \ iterator_traits<\n      typename tuple_element<N, Iter_tuple>::type>::reference>::type;\n\
    };\n\ntemplate <class Iter_tuple>\nstruct tuple_size<workspace::zipped_iterator<Iter_tuple>>\n\
    \    : tuple_size<Iter_tuple> {};\n\n}  // namespace std\n\nnamespace workspace\
    \ {\n\ntemplate <class... Args> constexpr auto zip(Args &&... args) noexcept {\n\
    \  return zipped<Args...>(std::forward<Args>(args)...);\n}\n\ntemplate <class...\
    \ Args>\nconstexpr auto zip(std::initializer_list<Args> const &... args) noexcept\
    \ {\n  return zipped<std::vector<Args>...>(args...);\n}\n\n}  // namespace workspace\n\
    \n#endif\n"
  code: "#pragma once\n\n/*\n * @file zip.hpp\n * @brief Zip\n */\n\n#include <cstddef>\n\
    #include <tuple>\n#include <vector>\n\n#include \"../iterator/category.hpp\"\n\
    #include \"../iterator/reverse.hpp\"\n\n#if __cplusplus >= 201703L\n\nnamespace\
    \ workspace {\n\ntemplate <class> struct zipped_iterator;\n\ntemplate <class...>\
    \ struct zipped_iterator_tuple;\n\ntemplate <class... Args> class zipped {\n \
    \ using ref_tuple = std::tuple<Args...>;\n  ref_tuple args;\n\n  template <size_t\
    \ N = 0> constexpr auto begin_cat() const noexcept {\n    if constexpr (N != std::tuple_size<ref_tuple>::value)\
    \ {\n      return std::tuple_cat(std::tuple(std::begin(std::get<N>(args))),\n\
    \                            begin_cat<N + 1>());\n    } else\n      return std::tuple<>();\n\
    \  }\n\n  template <size_t N = 0> constexpr auto end_cat() const noexcept {\n\
    \    if constexpr (N != std::tuple_size<ref_tuple>::value) {\n      return std::tuple_cat(std::tuple(std::end(std::get<N>(args))),\n\
    \                            end_cat<N + 1>());\n    } else\n      return std::tuple<>();\n\
    \  }\n\n public:\n  constexpr zipped(Args &&... args) noexcept : args(args...)\
    \ {}\n\n  class iterator {\n    using base_tuple = typename zipped_iterator_tuple<Args...>::type;\n\
    \n   public:\n    using iterator_category =\n        typename common_iterator_category<base_tuple>::type;\n\
    \    using difference_type = std::ptrdiff_t;\n    using value_type = zipped_iterator<base_tuple>;\n\
    \    using reference = zipped_iterator<base_tuple> &;\n    using pointer = iterator;\n\
    \n   protected:\n    value_type current;\n\n    template <size_t N = 0>\n    constexpr\
    \ bool equal(const iterator &rhs) const noexcept {\n      if constexpr (N != std::tuple_size<base_tuple>::value)\
    \ {\n        return std::get<N>(current) == std::get<N>(rhs.current) ||\n    \
    \           equal<N + 1>(rhs);\n      } else\n        return false;\n    }\n\n\
    \    template <size_t N = 0> constexpr void increment() noexcept {\n      if constexpr\
    \ (N != std::tuple_size<base_tuple>::value) {\n        ++std::get<N>(current);\n\
    \        increment<N + 1>();\n      }\n    }\n\n    template <size_t N = 0> constexpr\
    \ void decrement() noexcept {\n      if constexpr (N != std::tuple_size<base_tuple>::value)\
    \ {\n        --std::get<N>(current);\n        decrement<N + 1>();\n      }\n \
    \   }\n\n   public:\n    constexpr iterator() noexcept = default;\n    constexpr\
    \ iterator(base_tuple const &current) noexcept : current(current) {}\n\n    constexpr\
    \ bool operator==(const iterator &rhs) const noexcept {\n      return equal(rhs);\n\
    \    }\n    constexpr bool operator!=(const iterator &rhs) const noexcept {\n\
    \      return !equal(rhs);\n    }\n\n    constexpr iterator &operator++() noexcept\
    \ {\n      increment();\n      return *this;\n    }\n    constexpr iterator &operator--()\
    \ noexcept {\n      decrement();\n      return *this;\n    }\n\n    constexpr\
    \ reference operator*() noexcept { return current; }\n  };\n\n  constexpr iterator\
    \ begin() const noexcept { return iterator{begin_cat()}; }\n  constexpr iterator\
    \ end() const noexcept { return iterator{end_cat()}; }\n\n  constexpr reverse_iterator<iterator>\
    \ rbegin() const noexcept {\n    return reverse_iterator<iterator>{end()};\n \
    \ }\n  constexpr reverse_iterator<iterator> rend() const noexcept {\n    return\
    \ reverse_iterator<iterator>{begin()};\n  }\n};\n\ntemplate <class Tp, class...\
    \ Args> struct zipped_iterator_tuple<Tp, Args...> {\n  using type = decltype(std::tuple_cat(\n\
    \      std::declval<std::tuple<decltype(std::begin(std::declval<Tp>()))>>(),\n\
    \      std::declval<typename zipped_iterator_tuple<Args...>::type>()));\n};\n\n\
    template <> struct zipped_iterator_tuple<> { using type = std::tuple<>; };\n\n\
    template <class Iter_tuple> struct zipped_iterator : Iter_tuple {\n  constexpr\
    \ zipped_iterator(Iter_tuple const &__t) noexcept\n      : Iter_tuple::tuple(__t)\
    \ {}\n\n  template <size_t N>\n  friend constexpr auto &get(zipped_iterator<Iter_tuple>\
    \ const &__z) noexcept {\n    return *std::get<N>(__z);\n  }\n\n  template <size_t\
    \ N>\n  friend constexpr auto get(zipped_iterator<Iter_tuple> const &&__z) noexcept\
    \ {\n    return std::move(*std::get<N>(__z));\n  }\n};\n\n}  // namespace workspace\n\
    \nnamespace std {\n\ntemplate <size_t N, class Iter_tuple>\nstruct tuple_element<N,\
    \ workspace::zipped_iterator<Iter_tuple>> {\n  using type = typename remove_reference<typename\
    \ iterator_traits<\n      typename tuple_element<N, Iter_tuple>::type>::reference>::type;\n\
    };\n\ntemplate <class Iter_tuple>\nstruct tuple_size<workspace::zipped_iterator<Iter_tuple>>\n\
    \    : tuple_size<Iter_tuple> {};\n\n}  // namespace std\n\nnamespace workspace\
    \ {\n\ntemplate <class... Args> constexpr auto zip(Args &&... args) noexcept {\n\
    \  return zipped<Args...>(std::forward<Args>(args)...);\n}\n\ntemplate <class...\
    \ Args>\nconstexpr auto zip(std::initializer_list<Args> const &... args) noexcept\
    \ {\n  return zipped<std::vector<Args>...>(args...);\n}\n\n}  // namespace workspace\n\
    \n#endif\n"
  dependsOn:
  - src/utils/iterator/category.hpp
  - src/utils/iterator/reverse.hpp
  isVerificationFile: false
  path: src/utils/py-like/zip.hpp
  requiredBy:
  - src/utils/py-like/enumerate.hpp
  timestamp: '2020-12-05 12:12:40+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/number_of_substrings.test.cpp
documentation_of: src/utils/py-like/zip.hpp
layout: document
redirect_from:
- /library/src/utils/py-like/zip.hpp
- /library/src/utils/py-like/zip.hpp.html
title: Zip
---
