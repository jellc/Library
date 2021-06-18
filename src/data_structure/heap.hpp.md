---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/utils/sfinae.hpp
    title: SFINAE
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Heap
    links: []
  bundledCode: "#line 2 \"src/data_structure/heap.hpp\"\n\n/**\n * @file heap.hpp\n\
    \ * @brief Heap\n */\n\n#include <queue>\n\n#line 2 \"lib/cxx17\"\n\n#ifndef _CXX17_CONSTEXPR\n\
    #if __cplusplus >= 201703L\n#define _CXX17_CONSTEXPR constexpr\n#else\n#define\
    \ _CXX17_CONSTEXPR\n#endif\n#endif\n\n#if __cplusplus < 201703L\n\nnamespace std\
    \ {\n\n/**\n *  @brief  Return the size of a container.\n *  @param  __cont  Container.\n\
    \ */\ntemplate <typename _Container>\nconstexpr auto size(const _Container& __cont)\
    \ noexcept(noexcept(__cont.size()))\n    -> decltype(__cont.size()) {\n  return\
    \ __cont.size();\n}\n\n/**\n *  @brief  Return the size of an array.\n */\ntemplate\
    \ <typename _Tp, size_t _Nm>\nconstexpr size_t size(const _Tp (&)[_Nm]) noexcept\
    \ {\n  return _Nm;\n}\n\n}  // namespace std\n\n#endif\n#line 2 \"src/utils/sfinae.hpp\"\
    \n\n/**\n * @file sfinae.hpp\n * @brief SFINAE\n */\n\n#include <cstdint>\n#include\
    \ <iterator>\n#include <type_traits>\n\n#ifndef __INT128_DEFINED__\n\n#ifdef __SIZEOF_INT128__\n\
    #define __INT128_DEFINED__ 1\n#else\n#define __INT128_DEFINED__ 0\n#endif\n\n\
    #endif\n\nnamespace std {\n\n#if __INT128_DEFINED__\n\ntemplate <> struct make_signed<__uint128_t>\
    \ { using type = __int128_t; };\ntemplate <> struct make_signed<__int128_t> {\
    \ using type = __int128_t; };\n\ntemplate <> struct make_unsigned<__uint128_t>\
    \ { using type = __uint128_t; };\ntemplate <> struct make_unsigned<__int128_t>\
    \ { using type = __uint128_t; };\n\ntemplate <> struct is_signed<__uint128_t>\
    \ : std::false_type {};\ntemplate <> struct is_signed<__int128_t> : std::true_type\
    \ {};\n\ntemplate <> struct is_unsigned<__uint128_t> : std::true_type {};\ntemplate\
    \ <> struct is_unsigned<__int128_t> : std::false_type {};\n\n#endif\n\n}  // namespace\
    \ std\n\nnamespace workspace {\n\ntemplate <class Tp, class... Args> struct variadic_front\
    \ { using type = Tp; };\n\ntemplate <class... Args> struct variadic_back;\n\n\
    template <class Tp> struct variadic_back<Tp> { using type = Tp; };\n\ntemplate\
    \ <class Tp, class... Args> struct variadic_back<Tp, Args...> {\n  using type\
    \ = typename variadic_back<Args...>::type;\n};\n\ntemplate <class type, template\
    \ <class> class trait>\nusing enable_if_trait_type = typename std::enable_if<trait<type>::value>::type;\n\
    \n/**\n * @brief Return type of subscripting ( @c [] ) access.\n */\ntemplate\
    \ <class _Tp>\nusing subscripted_type =\n    typename std::decay<decltype(std::declval<_Tp&>()[0])>::type;\n\
    \ntemplate <class Container>\nusing element_type = typename std::decay<decltype(\n\
    \    *std::begin(std::declval<Container&>()))>::type;\n\ntemplate <class _Tp,\
    \ class = std::nullptr_t>\nstruct has_begin : std::false_type {};\n\ntemplate\
    \ <class _Tp>\nstruct has_begin<_Tp, decltype(std::begin(std::declval<_Tp>()),\
    \ nullptr)>\n    : std::true_type {};\n\ntemplate <class _Tp, class = void> struct\
    \ has_mod : std::false_type {};\n\ntemplate <class _Tp>\nstruct has_mod<_Tp, std::__void_t<decltype(_Tp::mod)>>\
    \ : std::true_type {};\n\ntemplate <class _Tp, class = void> struct is_integral_ext\
    \ : std::false_type {};\ntemplate <class _Tp>\nstruct is_integral_ext<\n    _Tp,\
    \ typename std::enable_if<std::is_integral<_Tp>::value>::type>\n    : std::true_type\
    \ {};\n\n#if __INT128_DEFINED__\n\ntemplate <> struct is_integral_ext<__int128_t>\
    \ : std::true_type {};\ntemplate <> struct is_integral_ext<__uint128_t> : std::true_type\
    \ {};\n\n#endif\n\n#if __cplusplus >= 201402\n\ntemplate <class _Tp>\nconstexpr\
    \ static bool is_integral_ext_v = is_integral_ext<_Tp>::value;\n\n#endif\n\ntemplate\
    \ <typename _Tp, typename = void> struct multiplicable_uint {\n  using type =\
    \ uint_least32_t;\n};\ntemplate <typename _Tp>\nstruct multiplicable_uint<\n \
    \   _Tp,\n    typename std::enable_if<(2 < sizeof(_Tp)) &&\n                 \
    \           (!__INT128_DEFINED__ || sizeof(_Tp) <= 4)>::type> {\n  using type\
    \ = uint_least64_t;\n};\n\n#if __INT128_DEFINED__\n\ntemplate <typename _Tp>\n\
    struct multiplicable_uint<_Tp,\n                          typename std::enable_if<(4\
    \ < sizeof(_Tp))>::type> {\n  using type = __uint128_t;\n};\n\n#endif\n\ntemplate\
    \ <typename _Tp> struct multiplicable_int {\n  using type =\n      typename std::make_signed<typename\
    \ multiplicable_uint<_Tp>::type>::type;\n};\n\ntemplate <typename _Tp> struct\
    \ multiplicable {\n  using type = std::conditional_t<\n      is_integral_ext<_Tp>::value,\n\
    \      std::conditional_t<std::is_signed<_Tp>::value,\n                      \
    \   typename multiplicable_int<_Tp>::type,\n                         typename\
    \ multiplicable_uint<_Tp>::type>,\n      _Tp>;\n};\n\ntemplate <class> struct\
    \ first_arg { using type = void; };\n\ntemplate <class _R, class _Tp, class...\
    \ _Args>\nstruct first_arg<_R(_Tp, _Args...)> {\n  using type = _Tp;\n};\n\ntemplate\
    \ <class _R, class _Tp, class... _Args>\nstruct first_arg<_R (*)(_Tp, _Args...)>\
    \ {\n  using type = _Tp;\n};\n\ntemplate <class _G, class _R, class _Tp, class...\
    \ _Args>\nstruct first_arg<_R (_G::*)(_Tp, _Args...)> {\n  using type = _Tp;\n\
    };\n\ntemplate <class _G, class _R, class _Tp, class... _Args>\nstruct first_arg<_R\
    \ (_G::*)(_Tp, _Args...) const> {\n  using type = _Tp;\n};\n\ntemplate <class\
    \ _Tp, class = void> struct parse_compare : first_arg<_Tp> {};\n\ntemplate <class\
    \ _Tp>\nstruct parse_compare<_Tp, std::__void_t<decltype(&_Tp::operator())>>\n\
    \    : first_arg<decltype(&_Tp::operator())> {};\n\n}  // namespace workspace\n\
    #line 12 \"src/data_structure/heap.hpp\"\n\nnamespace workspace {\n\n/**\n * @brief\
    \ Wrapper class for std::priority_queue.\n */\ntemplate <class _Tp, class _Compare\
    \ = std::less<_Tp>>\nclass heap : public std::priority_queue<_Tp, std::vector<_Tp>,\
    \ _Compare> {\n public:\n  using container_type = std::priority_queue<_Tp, std::vector<_Tp>,\
    \ _Compare>;\n  using container_type::container_type;\n\n  heap(const _Compare\
    \ &__c) noexcept : container_type(__c) {}\n};\n\ntemplate <class _Compare>\nheap(const\
    \ _Compare &)\n    -> heap<std::decay_t<typename parse_compare<_Compare>::type>,\
    \ _Compare>;\n\ntemplate <class _Tp = void, class _Compare = std::less<_Tp>>\n\
    decltype(auto) make_heap(const _Compare &__c = _Compare{}) {\n  if _CXX17_CONSTEXPR\
    \ (std::is_void<_Tp>::value)\n    return heap(__c);\n  else\n    return heap<_Tp,\
    \ _Compare>(__c);\n}\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file heap.hpp\n * @brief Heap\n */\n\n#include <queue>\n\
    \n#include \"lib/cxx17\"\n#include \"src/utils/sfinae.hpp\"\n\nnamespace workspace\
    \ {\n\n/**\n * @brief Wrapper class for std::priority_queue.\n */\ntemplate <class\
    \ _Tp, class _Compare = std::less<_Tp>>\nclass heap : public std::priority_queue<_Tp,\
    \ std::vector<_Tp>, _Compare> {\n public:\n  using container_type = std::priority_queue<_Tp,\
    \ std::vector<_Tp>, _Compare>;\n  using container_type::container_type;\n\n  heap(const\
    \ _Compare &__c) noexcept : container_type(__c) {}\n};\n\ntemplate <class _Compare>\n\
    heap(const _Compare &)\n    -> heap<std::decay_t<typename parse_compare<_Compare>::type>,\
    \ _Compare>;\n\ntemplate <class _Tp = void, class _Compare = std::less<_Tp>>\n\
    decltype(auto) make_heap(const _Compare &__c = _Compare{}) {\n  if _CXX17_CONSTEXPR\
    \ (std::is_void<_Tp>::value)\n    return heap(__c);\n  else\n    return heap<_Tp,\
    \ _Compare>(__c);\n}\n\n}  // namespace workspace\n"
  dependsOn:
  - src/utils/sfinae.hpp
  isVerificationFile: false
  path: src/data_structure/heap.hpp
  requiredBy: []
  timestamp: '2021-06-18 17:34:10+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/data_structure/heap.hpp
layout: document
redirect_from:
- /library/src/data_structure/heap.hpp
- /library/src/data_structure/heap.hpp.html
title: Heap
---
