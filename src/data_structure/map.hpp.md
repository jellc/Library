---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: src/data_structure/set.hpp
    title: Set
  - icon: ':heavy_check_mark:'
    path: src/utils/sfinae.hpp
    title: SFINAE
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Map
    links: []
  bundledCode: "#line 2 \"src/data_structure/map.hpp\"\n\n/**\n * @file map.hpp\n\
    \ * @brief Map\n */\n\n#include <map>\n\n#line 2 \"src/data_structure/set.hpp\"\
    \n\n/**\n * @file set.hpp\n * @brief Set\n */\n\n#include <set>\n\n#line 2 \"\
    src/utils/sfinae.hpp\"\n\n/**\n * @file sfinae.hpp\n * @brief SFINAE\n */\n\n\
    #include <cstdint>\n#include <iterator>\n#include <type_traits>\n\n#ifndef __INT128_DEFINED__\n\
    \n#ifdef __SIZEOF_INT128__\n#define __INT128_DEFINED__ 1\n#else\n#define __INT128_DEFINED__\
    \ 0\n#endif\n\n#endif\n\nnamespace std {\n\n#if __INT128_DEFINED__\n\ntemplate\
    \ <> struct make_signed<__uint128_t> { using type = __int128_t; };\ntemplate <>\
    \ struct make_signed<__int128_t> { using type = __int128_t; };\n\ntemplate <>\
    \ struct make_unsigned<__uint128_t> { using type = __uint128_t; };\ntemplate <>\
    \ struct make_unsigned<__int128_t> { using type = __uint128_t; };\n\ntemplate\
    \ <> struct is_signed<__uint128_t> : std::false_type {};\ntemplate <> struct is_signed<__int128_t>\
    \ : std::true_type {};\n\ntemplate <> struct is_unsigned<__uint128_t> : std::true_type\
    \ {};\ntemplate <> struct is_unsigned<__int128_t> : std::false_type {};\n\n#endif\n\
    \n}  // namespace std\n\nnamespace workspace {\n\ntemplate <class Tp, class...\
    \ Args> struct variadic_front { using type = Tp; };\n\ntemplate <class... Args>\
    \ struct variadic_back;\n\ntemplate <class Tp> struct variadic_back<Tp> { using\
    \ type = Tp; };\n\ntemplate <class Tp, class... Args> struct variadic_back<Tp,\
    \ Args...> {\n  using type = typename variadic_back<Args...>::type;\n};\n\ntemplate\
    \ <class type, template <class> class trait>\nusing enable_if_trait_type = typename\
    \ std::enable_if<trait<type>::value>::type;\n\n/**\n * @brief Return type of subscripting\
    \ ( @c [] ) access.\n */\ntemplate <class _Tp>\nusing subscripted_type =\n   \
    \ typename std::decay<decltype(std::declval<_Tp&>()[0])>::type;\n\ntemplate <class\
    \ Container>\nusing element_type = typename std::decay<decltype(\n    *std::begin(std::declval<Container&>()))>::type;\n\
    \ntemplate <class _Tp, class = std::nullptr_t>\nstruct has_begin : std::false_type\
    \ {};\n\ntemplate <class _Tp>\nstruct has_begin<_Tp, decltype(std::begin(std::declval<_Tp>()),\
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
    #line 11 \"src/data_structure/set.hpp\"\n\nnamespace workspace {\n\n/**\n * @brief\
    \ Wrapper class for std::set.\n */\ntemplate <class _Key, class _Compare>\nclass\
    \ set : public std::set<_Key, _Compare> {\n public:\n  using container_type =\
    \ std::set<_Key, _Compare>;\n  using container_type::container_type;\n\n  set(const\
    \ _Compare &__c) noexcept : container_type(__c) {}\n\n  decltype(auto) front()\
    \ noexcept { return *container_type::begin(); }\n  decltype(auto) front() const\
    \ noexcept { return *container_type::begin(); }\n\n  decltype(auto) back() noexcept\
    \ { return *std::prev(container_type::end()); }\n  decltype(auto) back() const\
    \ noexcept {\n    return *std::prev(container_type::end());\n  }\n\n  decltype(auto)\
    \ erase_front() noexcept {\n    return container_type::erase(container_type::begin());\n\
    \  }\n  decltype(auto) erase_back() noexcept {\n    return container_type::erase(std::prev(container_type::end()));\n\
    \  }\n};\n\ntemplate <class _Compare>\nset(const _Compare &)\n    -> set<std::decay_t<typename\
    \ parse_compare<_Compare>::type>, _Compare>;\n\ntemplate <class _Key = void, class\
    \ _Compare = std::less<_Key>>\ndecltype(auto) make_set(const _Compare &__c = _Compare{})\
    \ {\n  if constexpr (std::is_void<_Key>::value)\n    return set(__c);\n  else\n\
    \    return set<_Key, _Compare>(__c);\n}\n\n}  // namespace workspace\n#line 11\
    \ \"src/data_structure/map.hpp\"\n\nnamespace workspace {\n\n/**\n * @brief Wrapper\
    \ class for std::map.\n */\ntemplate <class _Key, class _Value = void, class _Compare\
    \ = std::less<_Key>>\nclass map : public std::map<_Key, _Value, _Compare> {\n\
    \  _Value __init{};\n\n public:\n  using container_type = std::map<_Key, _Value,\
    \ _Compare>;\n  using container_type::container_type;\n\n  map(const _Value &__x)\
    \ noexcept : __init(__x) {}\n  map(const _Value &__x, const _Compare &__c) noexcept\n\
    \      : container_type(__c), __init(__x) {}\n\n  _Value &operator[](const _Key\
    \ &__x) noexcept {\n    auto __i = container_type::lower_bound(__x);\n\n    if\
    \ (__i == container_type::end() ||\n        container_type::key_comp()(__x, __i->first))\n\
    \      __i = container_type::emplace_hint(__i, __x, __init);\n\n    return __i->second;\n\
    \  }\n\n  decltype(auto) front() noexcept { return *container_type::begin(); }\n\
    \  decltype(auto) front() const noexcept { return *container_type::begin(); }\n\
    \n  decltype(auto) back() noexcept { return *std::prev(container_type::end());\
    \ }\n  decltype(auto) back() const noexcept {\n    return *std::prev(container_type::end());\n\
    \  }\n\n  decltype(auto) erase_front() noexcept {\n    return container_type::erase(container_type::begin());\n\
    \  }\n  decltype(auto) erase_back() noexcept {\n    return container_type::erase(std::prev(container_type::end()));\n\
    \  }\n};\n\ntemplate <class _Key, class _Compare>\nclass map<_Key, void, _Compare>\
    \ : public set<_Key, _Compare> {\n  using set<_Key, _Compare>::set;\n};\n\ntemplate\
    \ <class _Value, class _Compare>\nmap(const _Value &__x, const _Compare &)\n \
    \   -> map<std::decay_t<typename parse_compare<_Compare>::type>, _Value,\n   \
    \        _Compare>;\n\ntemplate <class _Compare>\nmap(const _Compare &)\n    ->\
    \ map<std::decay_t<typename parse_compare<_Compare>::type>, void,\n          \
    \ _Compare>;\n\ntemplate <class _Key = void, class _Value, class _Compare = std::less<_Key>>\n\
    decltype(auto) make_map(const _Value &__x, const _Compare &__c = _Compare{}) {\n\
    \  if constexpr (std::is_void<_Key>::value)\n    return map(__x, __c);\n  else\n\
    \    return map<_Key, _Value, _Compare>(__x, __c);\n}\n\ntemplate <class _Key,\
    \ class _Value, class _Compare = std::less<_Key>>\ndecltype(auto) make_map(const\
    \ _Compare &__c = _Compare{}) {\n  if constexpr (std::is_void<_Value>::value)\n\
    \    return make_set(__c);\n  else\n    return map(_Value{}, __c);\n}\n\n}  //\
    \ namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file map.hpp\n * @brief Map\n */\n\n#include <map>\n\
    \n#include \"set.hpp\"\n\nnamespace workspace {\n\n/**\n * @brief Wrapper class\
    \ for std::map.\n */\ntemplate <class _Key, class _Value = void, class _Compare\
    \ = std::less<_Key>>\nclass map : public std::map<_Key, _Value, _Compare> {\n\
    \  _Value __init{};\n\n public:\n  using container_type = std::map<_Key, _Value,\
    \ _Compare>;\n  using container_type::container_type;\n\n  map(const _Value &__x)\
    \ noexcept : __init(__x) {}\n  map(const _Value &__x, const _Compare &__c) noexcept\n\
    \      : container_type(__c), __init(__x) {}\n\n  _Value &operator[](const _Key\
    \ &__x) noexcept {\n    auto __i = container_type::lower_bound(__x);\n\n    if\
    \ (__i == container_type::end() ||\n        container_type::key_comp()(__x, __i->first))\n\
    \      __i = container_type::emplace_hint(__i, __x, __init);\n\n    return __i->second;\n\
    \  }\n\n  decltype(auto) front() noexcept { return *container_type::begin(); }\n\
    \  decltype(auto) front() const noexcept { return *container_type::begin(); }\n\
    \n  decltype(auto) back() noexcept { return *std::prev(container_type::end());\
    \ }\n  decltype(auto) back() const noexcept {\n    return *std::prev(container_type::end());\n\
    \  }\n\n  decltype(auto) erase_front() noexcept {\n    return container_type::erase(container_type::begin());\n\
    \  }\n  decltype(auto) erase_back() noexcept {\n    return container_type::erase(std::prev(container_type::end()));\n\
    \  }\n};\n\ntemplate <class _Key, class _Compare>\nclass map<_Key, void, _Compare>\
    \ : public set<_Key, _Compare> {\n  using set<_Key, _Compare>::set;\n};\n\ntemplate\
    \ <class _Value, class _Compare>\nmap(const _Value &__x, const _Compare &)\n \
    \   -> map<std::decay_t<typename parse_compare<_Compare>::type>, _Value,\n   \
    \        _Compare>;\n\ntemplate <class _Compare>\nmap(const _Compare &)\n    ->\
    \ map<std::decay_t<typename parse_compare<_Compare>::type>, void,\n          \
    \ _Compare>;\n\ntemplate <class _Key = void, class _Value, class _Compare = std::less<_Key>>\n\
    decltype(auto) make_map(const _Value &__x, const _Compare &__c = _Compare{}) {\n\
    \  if constexpr (std::is_void<_Key>::value)\n    return map(__x, __c);\n  else\n\
    \    return map<_Key, _Value, _Compare>(__x, __c);\n}\n\ntemplate <class _Key,\
    \ class _Value, class _Compare = std::less<_Key>>\ndecltype(auto) make_map(const\
    \ _Compare &__c = _Compare{}) {\n  if constexpr (std::is_void<_Value>::value)\n\
    \    return make_set(__c);\n  else\n    return map(_Value{}, __c);\n}\n\n}  //\
    \ namespace workspace\n"
  dependsOn:
  - src/data_structure/set.hpp
  - src/utils/sfinae.hpp
  isVerificationFile: false
  path: src/data_structure/map.hpp
  requiredBy: []
  timestamp: '2021-05-25 17:32:10+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/data_structure/map.hpp
layout: document
redirect_from:
- /library/src/data_structure/map.hpp
- /library/src/data_structure/map.hpp.html
title: Map
---
