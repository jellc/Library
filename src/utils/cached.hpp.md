---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: src/utils/fixed_point.hpp
    title: Fixed Point Combinator
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Cached
    links: []
  bundledCode: "#line 2 \"src/utils/cached.hpp\"\n\n/**\n * @file cached.hpp\n * @brief\
    \ Cached\n */\n\n#include <map>\n#include <memory>\n\n#line 2 \"src/utils/fixed_point.hpp\"\
    \n\n/**\n * @file fixed_point.hpp\n * @brief Fixed Point Combinator\n */\n\n#line\
    \ 9 \"src/utils/fixed_point.hpp\"\n\nnamespace workspace {\n\n/**\n * @brief Fixed\
    \ Point Combinator\n */\ntemplate <class _F> class fixed_point {\n  _F __fn;\n\
    \n public:\n  /**\n   * @brief Construct a new fixed point object\n   *\n   *\
    \ @param __fn 1st argument callable with the rest of its arguments.\n   * Return\
    \ type specified.\n   */\n  fixed_point(_F __fn) noexcept : __fn(std::forward<_F>(__fn))\
    \ {}\n\n  /**\n   * @brief Apply *this to 1st argument.\n   * @param __args Rest\
    \ of arguments.\n   */\n  template <class... _Args>\n  decltype(auto) operator()(_Args\
    \ &&...__args) const noexcept {\n    return __fn(*this, std::forward<_Args>(__args)...);\n\
    \  }\n};\n\n}  // namespace workspace\n#line 12 \"src/utils/cached.hpp\"\n\nnamespace\
    \ workspace {\n\nnamespace _cached_impl {\n\n// Convert keys to tuple.\ntemplate\
    \ <class... _Args> struct get_tuple {\n  using type = decltype(\n      std::tuple_cat(std::declval<std::tuple<std::conditional_t<\n\
    \                         std::is_convertible<std::decay_t<_Args>, _Args>::value,\n\
    \                         std::decay_t<_Args>, _Args>>>()...));\n};\n\n// Associative\
    \ array.\ntemplate <class _Value, class... _Keys>\nstruct assoc\n    : std::integral_constant<int,\
    \ !std::is_void<_Value>::value>,\n      std::conditional_t<std::is_void<_Value>::value,\n\
    \                         std::set<typename get_tuple<_Keys...>::type>,\n    \
    \                     std::map<typename get_tuple<_Keys...>::type, _Value>> {\n\
    };\n\n// Non-resursive lambda type.\ntemplate <class _F, class = void> struct\
    \ is_recursive : std::false_type {};\n\n// Resursive lambda type.\ntemplate <class\
    \ _F>\nstruct is_recursive<\n    _F, std::__void_t<decltype(&_F::template operator()<fixed_point<_F>\
    \ &>)>>\n    : std::true_type {};\n\n// Recursive ver.\ntemplate <class _F> class\
    \ _recursive {\n  template <class...> struct _cache;\n\n  template <class _G,\
    \ class _R, class _H, class... _Args>\n  struct _cache<_R (_G::*)(_H, _Args...)>\
    \ : assoc<_R, _Args...> {};\n\n  template <class _G, class _R, class _H, class...\
    \ _Args>\n  struct _cache<_R (_G::*)(_H, _Args...) const> : assoc<_R, _Args...>\
    \ {};\n\n public:\n  using cache = _cache<decltype(&_F::template operator()<_recursive<_F>\
    \ &>)>;\n\n  _recursive(_F __x) noexcept : __fn(__x), __cptr(new cache) {}\n\n\
    \  /**\n   * @brief Apply `*this` to 1st argument of the lambda.\n   * @param\
    \ __args Rest of arguments.\n   */\n  template <class... _Args>\n  decltype(auto)\
    \ operator()(_Args &&...__args) noexcept {\n    typename cache::key_type __key{__args...};\n\
    \n    if constexpr (cache::value) {\n      if (auto __i = __cptr->lower_bound(__key);\n\
    \          __i != __cptr->end() && __i->first == __key)\n        return __i->second;\n\
    \n      else\n        return __cptr\n            ->emplace_hint(__i, std::move(__key),\n\
    \                           __fn(*this, std::forward<_Args>(__args)...))\n   \
    \         ->second;\n    }\n\n    else if (auto __i = __cptr->lower_bound(__key);\n\
    \             __i == __cptr->end() || *__i != __key)\n      __cptr->emplace_hint(__i,\
    \ std::move(__key)),\n          __fn(*this, std::forward<_Args>(__args)...);\n\
    \  }\n\n private:\n  _F __fn;\n  std::shared_ptr<cache> __cptr;\n};\n\n// Non-recursive\
    \ ver.\ntemplate <class _F> class _non_recursive {\n  template <class _T, class\
    \ = void> struct _get_func { using type = _T; };\n\n  template <class _T>\n  struct\
    \ _get_func<_T, std::__void_t<decltype(&_T::operator())>> {\n    using type =\
    \ decltype(&_T::operator());\n  };\n\n  template <class...> struct _cache;\n\n\
    \  template <class _R, class... _Args>\n  struct _cache<_R(_Args...)> : assoc<_R,\
    \ _Args...> {};\n\n  template <class _R, class... _Args>\n  struct _cache<_R (*)(_Args...)>\
    \ : assoc<_R, _Args...> {};\n\n  template <class _G, class _R, class... _Args>\n\
    \  struct _cache<_R (_G::*)(_Args...)> : assoc<_R, _Args...> {};\n\n  template\
    \ <class _G, class _R, class... _Args>\n  struct _cache<_R (_G::*)(_Args...) const>\
    \ : assoc<_R, _Args...> {};\n\n public:\n  using cache = _cache<typename _get_func<_F>::type>;\n\
    \n  _non_recursive(_F __x) noexcept : __fn(__x), __cptr(new cache) {}\n\n  /**\n\
    \   * @param __args\n   */\n  template <class... _Args>\n  decltype(auto) operator()(_Args\
    \ &&...__args) noexcept {\n    typename cache::key_type __key{__args...};\n\n\
    \    if constexpr (cache::value) {\n      if (auto __i = __cptr->lower_bound(__key);\n\
    \          __i != __cptr->end() && __i->first == __key)\n        return __i->second;\n\
    \n      else\n        return __cptr\n            ->emplace_hint(__i, std::move(__key),\n\
    \                           __fn(std::forward<_Args>(__args)...))\n          \
    \  ->second;\n    }\n\n    else if (auto __i = __cptr->lower_bound(__key);\n \
    \            __i == __cptr->end() || *__i != __key)\n      __cptr->emplace_hint(__i,\
    \ std::move(__key)),\n          __fn(std::forward<_Args>(__args)...);\n  }\n\n\
    \ private:\n  _F __fn;\n  std::shared_ptr<cache> __cptr;\n};\n\ntemplate <class\
    \ _F>\nusing _cached = std::conditional_t<is_recursive<_F>::value, _recursive<_F>,\n\
    \                                   _non_recursive<_F>>;\n\n}  // namespace _cached_impl\n\
    \n/**\n * @brief Cached caller of function\n */\ntemplate <class _F> class cached\
    \ : public _cached_impl::_cached<_F> {\n public:\n  /**\n   * @brief Construct\
    \ a new cached object\n   */\n  cached() noexcept : _cached_impl::_cached<_F>(_F{})\
    \ {}\n\n  /**\n   * @brief Construct a new cached object\n   *\n   * @param __x\
    \ Function\n   */\n  cached(_F __x) noexcept : _cached_impl::_cached<_F>(__x)\
    \ {}\n};\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file cached.hpp\n * @brief Cached\n */\n\n#include\
    \ <map>\n#include <memory>\n\n#include \"fixed_point.hpp\"\n\nnamespace workspace\
    \ {\n\nnamespace _cached_impl {\n\n// Convert keys to tuple.\ntemplate <class...\
    \ _Args> struct get_tuple {\n  using type = decltype(\n      std::tuple_cat(std::declval<std::tuple<std::conditional_t<\n\
    \                         std::is_convertible<std::decay_t<_Args>, _Args>::value,\n\
    \                         std::decay_t<_Args>, _Args>>>()...));\n};\n\n// Associative\
    \ array.\ntemplate <class _Value, class... _Keys>\nstruct assoc\n    : std::integral_constant<int,\
    \ !std::is_void<_Value>::value>,\n      std::conditional_t<std::is_void<_Value>::value,\n\
    \                         std::set<typename get_tuple<_Keys...>::type>,\n    \
    \                     std::map<typename get_tuple<_Keys...>::type, _Value>> {\n\
    };\n\n// Non-resursive lambda type.\ntemplate <class _F, class = void> struct\
    \ is_recursive : std::false_type {};\n\n// Resursive lambda type.\ntemplate <class\
    \ _F>\nstruct is_recursive<\n    _F, std::__void_t<decltype(&_F::template operator()<fixed_point<_F>\
    \ &>)>>\n    : std::true_type {};\n\n// Recursive ver.\ntemplate <class _F> class\
    \ _recursive {\n  template <class...> struct _cache;\n\n  template <class _G,\
    \ class _R, class _H, class... _Args>\n  struct _cache<_R (_G::*)(_H, _Args...)>\
    \ : assoc<_R, _Args...> {};\n\n  template <class _G, class _R, class _H, class...\
    \ _Args>\n  struct _cache<_R (_G::*)(_H, _Args...) const> : assoc<_R, _Args...>\
    \ {};\n\n public:\n  using cache = _cache<decltype(&_F::template operator()<_recursive<_F>\
    \ &>)>;\n\n  _recursive(_F __x) noexcept : __fn(__x), __cptr(new cache) {}\n\n\
    \  /**\n   * @brief Apply `*this` to 1st argument of the lambda.\n   * @param\
    \ __args Rest of arguments.\n   */\n  template <class... _Args>\n  decltype(auto)\
    \ operator()(_Args &&...__args) noexcept {\n    typename cache::key_type __key{__args...};\n\
    \n    if constexpr (cache::value) {\n      if (auto __i = __cptr->lower_bound(__key);\n\
    \          __i != __cptr->end() && __i->first == __key)\n        return __i->second;\n\
    \n      else\n        return __cptr\n            ->emplace_hint(__i, std::move(__key),\n\
    \                           __fn(*this, std::forward<_Args>(__args)...))\n   \
    \         ->second;\n    }\n\n    else if (auto __i = __cptr->lower_bound(__key);\n\
    \             __i == __cptr->end() || *__i != __key)\n      __cptr->emplace_hint(__i,\
    \ std::move(__key)),\n          __fn(*this, std::forward<_Args>(__args)...);\n\
    \  }\n\n private:\n  _F __fn;\n  std::shared_ptr<cache> __cptr;\n};\n\n// Non-recursive\
    \ ver.\ntemplate <class _F> class _non_recursive {\n  template <class _T, class\
    \ = void> struct _get_func { using type = _T; };\n\n  template <class _T>\n  struct\
    \ _get_func<_T, std::__void_t<decltype(&_T::operator())>> {\n    using type =\
    \ decltype(&_T::operator());\n  };\n\n  template <class...> struct _cache;\n\n\
    \  template <class _R, class... _Args>\n  struct _cache<_R(_Args...)> : assoc<_R,\
    \ _Args...> {};\n\n  template <class _R, class... _Args>\n  struct _cache<_R (*)(_Args...)>\
    \ : assoc<_R, _Args...> {};\n\n  template <class _G, class _R, class... _Args>\n\
    \  struct _cache<_R (_G::*)(_Args...)> : assoc<_R, _Args...> {};\n\n  template\
    \ <class _G, class _R, class... _Args>\n  struct _cache<_R (_G::*)(_Args...) const>\
    \ : assoc<_R, _Args...> {};\n\n public:\n  using cache = _cache<typename _get_func<_F>::type>;\n\
    \n  _non_recursive(_F __x) noexcept : __fn(__x), __cptr(new cache) {}\n\n  /**\n\
    \   * @param __args\n   */\n  template <class... _Args>\n  decltype(auto) operator()(_Args\
    \ &&...__args) noexcept {\n    typename cache::key_type __key{__args...};\n\n\
    \    if constexpr (cache::value) {\n      if (auto __i = __cptr->lower_bound(__key);\n\
    \          __i != __cptr->end() && __i->first == __key)\n        return __i->second;\n\
    \n      else\n        return __cptr\n            ->emplace_hint(__i, std::move(__key),\n\
    \                           __fn(std::forward<_Args>(__args)...))\n          \
    \  ->second;\n    }\n\n    else if (auto __i = __cptr->lower_bound(__key);\n \
    \            __i == __cptr->end() || *__i != __key)\n      __cptr->emplace_hint(__i,\
    \ std::move(__key)),\n          __fn(std::forward<_Args>(__args)...);\n  }\n\n\
    \ private:\n  _F __fn;\n  std::shared_ptr<cache> __cptr;\n};\n\ntemplate <class\
    \ _F>\nusing _cached = std::conditional_t<is_recursive<_F>::value, _recursive<_F>,\n\
    \                                   _non_recursive<_F>>;\n\n}  // namespace _cached_impl\n\
    \n/**\n * @brief Cached caller of function\n */\ntemplate <class _F> class cached\
    \ : public _cached_impl::_cached<_F> {\n public:\n  /**\n   * @brief Construct\
    \ a new cached object\n   */\n  cached() noexcept : _cached_impl::_cached<_F>(_F{})\
    \ {}\n\n  /**\n   * @brief Construct a new cached object\n   *\n   * @param __x\
    \ Function\n   */\n  cached(_F __x) noexcept : _cached_impl::_cached<_F>(__x)\
    \ {}\n};\n\n}  // namespace workspace\n"
  dependsOn:
  - src/utils/fixed_point.hpp
  isVerificationFile: false
  path: src/utils/cached.hpp
  requiredBy: []
  timestamp: '2021-04-04 23:33:06+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/utils/cached.hpp
layout: document
redirect_from:
- /library/src/utils/cached.hpp
- /library/src/utils/cached.hpp.html
title: Cached
---