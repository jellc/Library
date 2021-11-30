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
    \ Cached\n */\n\n#line 2 \"src/utils/fixed_point.hpp\"\n\n/**\n * @file fixed_point.hpp\n\
    \ * @brief Fixed Point Combinator\n */\n\n#include <utility>\n\nnamespace workspace\
    \ {\n\n// Fixed Point Combinator.\ntemplate <class _F> class fixed_point {\n \
    \ struct _wrapper {\n    _F &__ref;\n\n    template <class... _Args>\n    decltype(auto)\
    \ operator()(_Args &&...__args) noexcept(\n        noexcept(__ref(*this, std::forward<_Args>(__args)...)))\
    \ {\n      return __ref(*this, std::forward<_Args>(__args)...);\n    }\n  };\n\
    \n  _F __fn;\n\n public:\n  // Construct a new fixed-point object.\n  fixed_point(_F\
    \ __x) noexcept : __fn(__x) {}\n\n  // Function call.\n  template <class... _Args>\n\
    \  decltype(auto) operator()(_Args &&...__args) noexcept(noexcept(_wrapper{\n\
    \      __fn}(std::forward<_Args>(__args)...))) {\n    return _wrapper{__fn}(std::forward<_Args>(__args)...);\n\
    \  }\n};\n\n}  // namespace workspace\n#line 2 \"lib/cxx17\"\n\n#line 2 \"lib/cxx14\"\
    \n\n#ifndef _CXX14_CONSTEXPR\n#if __cplusplus >= 201402L\n#define _CXX14_CONSTEXPR\
    \ constexpr\n#else\n#define _CXX14_CONSTEXPR\n#endif\n#endif\n#line 4 \"lib/cxx17\"\
    \n\n#ifndef _CXX17_CONSTEXPR\n#if __cplusplus >= 201703L\n#define _CXX17_CONSTEXPR\
    \ constexpr\n#else\n#define _CXX17_CONSTEXPR\n#endif\n#endif\n\n#ifndef _CXX17_STATIC_ASSERT\n\
    #if __cplusplus >= 201703L\n#define _CXX17_STATIC_ASSERT static_assert\n#else\n\
    #define _CXX17_STATIC_ASSERT assert\n#endif\n#endif\n\n#include <iterator>\n\n\
    #if __cplusplus < 201703L\n\nnamespace std {\n\n/**\n *  @brief  Return the size\
    \ of a container.\n *  @param  __cont  Container.\n */\ntemplate <typename _Container>\n\
    constexpr auto size(const _Container& __cont) noexcept(noexcept(__cont.size()))\n\
    \    -> decltype(__cont.size()) {\n  return __cont.size();\n}\n\n/**\n *  @brief\
    \  Return the size of an array.\n */\ntemplate <typename _Tp, size_t _Nm>\nconstexpr\
    \ size_t size(const _Tp (&)[_Nm]) noexcept {\n  return _Nm;\n}\n\n/**\n *  @brief\
    \  Return whether a container is empty.\n *  @param  __cont  Container.\n */\n\
    template <typename _Container>\n[[nodiscard]] constexpr auto empty(const _Container&\
    \ __cont) noexcept(\n    noexcept(__cont.empty())) -> decltype(__cont.empty())\
    \ {\n  return __cont.empty();\n}\n\n/**\n *  @brief  Return whether an array is\
    \ empty (always false).\n */\ntemplate <typename _Tp, size_t _Nm>\n[[nodiscard]]\
    \ constexpr bool empty(const _Tp (&)[_Nm]) noexcept {\n  return false;\n}\n\n\
    /**\n *  @brief  Return whether an initializer_list is empty.\n *  @param  __il\
    \  Initializer list.\n */\ntemplate <typename _Tp>\n[[nodiscard]] constexpr bool\
    \ empty(initializer_list<_Tp> __il) noexcept {\n  return __il.size() == 0;\n}\n\
    \nstruct monostate {};\n\n}  // namespace std\n\n#else\n\n#include <variant>\n\
    \n#endif\n#line 10 \"src/utils/cached.hpp\"\n\nnamespace workspace {\n\nnamespace\
    \ _cached_impl {\n\n// Convert keys to tuple.\ntemplate <class... _Args> struct\
    \ as_tuple {\n  using type = decltype(std::tuple_cat(\n      std::declval<std::tuple<std::conditional_t<\n\
    \          std::is_convertible<std::decay_t<_Args>, _Args>::value,\n         \
    \ std::decay_t<_Args>, _Args>>>()...));\n};\n\n// Associative array.\ntemplate\
    \ <class _Value, class... _Keys>\nstruct assoc\n    : std::integral_constant<int,\
    \ !std::is_void<_Value>::value>,\n      std::conditional_t<std::is_void<_Value>::value,\n\
    \                         std::set<typename as_tuple<_Keys...>::type>,\n     \
    \                    std::map<typename as_tuple<_Keys...>::type, _Value>> {\n\
    };\n\n// Non-resursive lambda type.\ntemplate <class _F, class = void> struct\
    \ is_recursive : std::false_type {};\n\n// Resursive lambda type.\ntemplate <class\
    \ _F>\nstruct is_recursive<\n    _F, std::__void_t<decltype(&_F::template operator()<fixed_point<_F>\
    \ &>)>>\n    : std::true_type {};\n\n// Recursive ver.\ntemplate <class _F> class\
    \ _recursive {\n  template <class...> struct _cache;\n\n  template <class _G,\
    \ class _R, class _H, class... _Args>\n  struct _cache<_R (_G::*)(_H, _Args...)>\
    \ : assoc<_R, _Args...> {};\n\n  template <class _G, class _R, class _H, class...\
    \ _Args>\n  struct _cache<_R (_G::*)(_H, _Args...) const> : assoc<_R, _Args...>\
    \ {};\n\n  template <class _G, class _R, class _H, class... _Args>\n  struct _cache<_R\
    \ (_G::*)(_H, _Args...) noexcept> : assoc<_R, _Args...> {};\n\n  template <class\
    \ _G, class _R, class _H, class... _Args>\n  struct _cache<_R (_G::*)(_H, _Args...)\
    \ const noexcept> : assoc<_R, _Args...> {\n  };\n\n public:\n  using cache_type\
    \ =\n      _cache<decltype(&_F::template operator()<_recursive<_F> &>)>;\n\n private:\n\
    \  _F __fn;\n  cache_type __c;\n\n  struct _wrapper {\n    _F &__fn;\n    cache_type\
    \ &__c;\n\n    template <class... _Args>\n    decltype(auto) operator()(_Args\
    \ &&...__args) noexcept(\n        noexcept(__fn(*this, std::forward<_Args>(__args)...)))\
    \ {\n      typename cache_type::key_type __key{__args...};\n      auto __i = __c.lower_bound(__key);\n\
    \n      if _CXX17_CONSTEXPR (cache_type::value) {\n        if (__i != __c.end()\
    \ && __i->first == __key) return __i->second;\n\n        return __c\n        \
    \    .emplace_hint(__i, std::move(__key),\n                          __fn(*this,\
    \ std::forward<_Args>(__args)...))\n            ->second;\n      }\n\n      else\
    \ if (__i == __c.end() || *__i != __key)\n        __c.emplace_hint(__i, std::move(__key)),\n\
    \            __fn(*this, std::forward<_Args>(__args)...);\n    }\n  };\n\n public:\n\
    \  _recursive(_F &&__x) noexcept : __fn(__x) {}\n\n  // Function call.\n  template\
    \ <class... _Args>\n  decltype(auto) operator()(_Args &&...__args) noexcept(noexcept(_wrapper{\n\
    \      __fn, __c}(std::forward<_Args>(__args)...))) {\n    return _wrapper{__fn,\
    \ __c}(std::forward<_Args>(__args)...);\n  }\n};\n\n// Non-recursive ver.\ntemplate\
    \ <class _F> class _non_recursive {\n  template <class _T, class = void> struct\
    \ _get_func { using type = _T; };\n\n  template <class _T>\n  struct _get_func<_T,\
    \ std::__void_t<decltype(&_T::operator())>> {\n    using type = decltype(&_T::operator());\n\
    \  };\n\n  template <class...> struct _cache;\n\n  template <class _R, class...\
    \ _Args>\n  struct _cache<_R(_Args...)> : assoc<_R, _Args...> {};\n\n  template\
    \ <class _R, class... _Args>\n  struct _cache<_R (*)(_Args...)> : assoc<_R, _Args...>\
    \ {};\n\n  template <class _G, class _R, class... _Args>\n  struct _cache<_R (_G::*)(_Args...)>\
    \ : assoc<_R, _Args...> {};\n\n  template <class _G, class _R, class... _Args>\n\
    \  struct _cache<_R (_G::*)(_Args...) const> : assoc<_R, _Args...> {};\n\n  template\
    \ <class _R, class... _Args>\n  struct _cache<_R(_Args...) noexcept> : assoc<_R,\
    \ _Args...> {};\n\n  template <class _R, class... _Args>\n  struct _cache<_R (*)(_Args...)\
    \ noexcept> : assoc<_R, _Args...> {};\n\n  template <class _G, class _R, class...\
    \ _Args>\n  struct _cache<_R (_G::*)(_Args...) noexcept> : assoc<_R, _Args...>\
    \ {};\n\n  template <class _G, class _R, class... _Args>\n  struct _cache<_R (_G::*)(_Args...)\
    \ const noexcept> : assoc<_R, _Args...> {};\n\n public:\n  using cache_type =\
    \ _cache<typename _get_func<_F>::type>;\n\n private:\n  _F __fn;\n  cache_type\
    \ __c;\n\n public:\n  _non_recursive(_F &&__x) noexcept : __fn(__x) {}\n\n  //\
    \ Function call.\n  template <class... _Args>\n  decltype(auto) operator()(_Args\
    \ &&...__args) noexcept(\n      noexcept(__fn(std::forward<_Args>(__args)...)))\
    \ {\n    typename cache_type::key_type __key{__args...};\n    auto __i = __c.lower_bound(__key);\n\
    \n    if _CXX17_CONSTEXPR (cache_type::value) {\n      if (__i != __c.end() &&\
    \ __i->first == __key) return __i->second;\n\n      return __c\n          .emplace_hint(__i,\
    \ std::move(__key),\n                        __fn(std::forward<_Args>(__args)...))\n\
    \          ->second;\n    }\n\n    else if (__i == __c.end() || *__i != __key)\n\
    \      __c.emplace_hint(__i, std::move(__key)),\n          __fn(std::forward<_Args>(__args)...);\n\
    \  }\n};\n\ntemplate <class _F>\nusing _cached = std::conditional_t<is_recursive<_F>::value,\
    \ _recursive<_F>,\n                                   _non_recursive<_F>>;\n\n\
    }  // namespace _cached_impl\n\n/**\n * @brief Cached caller of function\n */\n\
    template <class _F> class cached : public _cached_impl::_cached<_F> {\n public:\n\
    \  // Construct a new cached object.\n  cached() noexcept : _cached_impl::_cached<_F>(_F{})\
    \ {}\n\n  // Construct a new cached object.\n  cached(_F __x) noexcept : _cached_impl::_cached<_F>(std::move(__x))\
    \ {}\n};\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file cached.hpp\n * @brief Cached\n */\n\n#include\
    \ \"fixed_point.hpp\"\n#include \"lib/cxx17\"\n\nnamespace workspace {\n\nnamespace\
    \ _cached_impl {\n\n// Convert keys to tuple.\ntemplate <class... _Args> struct\
    \ as_tuple {\n  using type = decltype(std::tuple_cat(\n      std::declval<std::tuple<std::conditional_t<\n\
    \          std::is_convertible<std::decay_t<_Args>, _Args>::value,\n         \
    \ std::decay_t<_Args>, _Args>>>()...));\n};\n\n// Associative array.\ntemplate\
    \ <class _Value, class... _Keys>\nstruct assoc\n    : std::integral_constant<int,\
    \ !std::is_void<_Value>::value>,\n      std::conditional_t<std::is_void<_Value>::value,\n\
    \                         std::set<typename as_tuple<_Keys...>::type>,\n     \
    \                    std::map<typename as_tuple<_Keys...>::type, _Value>> {\n\
    };\n\n// Non-resursive lambda type.\ntemplate <class _F, class = void> struct\
    \ is_recursive : std::false_type {};\n\n// Resursive lambda type.\ntemplate <class\
    \ _F>\nstruct is_recursive<\n    _F, std::__void_t<decltype(&_F::template operator()<fixed_point<_F>\
    \ &>)>>\n    : std::true_type {};\n\n// Recursive ver.\ntemplate <class _F> class\
    \ _recursive {\n  template <class...> struct _cache;\n\n  template <class _G,\
    \ class _R, class _H, class... _Args>\n  struct _cache<_R (_G::*)(_H, _Args...)>\
    \ : assoc<_R, _Args...> {};\n\n  template <class _G, class _R, class _H, class...\
    \ _Args>\n  struct _cache<_R (_G::*)(_H, _Args...) const> : assoc<_R, _Args...>\
    \ {};\n\n  template <class _G, class _R, class _H, class... _Args>\n  struct _cache<_R\
    \ (_G::*)(_H, _Args...) noexcept> : assoc<_R, _Args...> {};\n\n  template <class\
    \ _G, class _R, class _H, class... _Args>\n  struct _cache<_R (_G::*)(_H, _Args...)\
    \ const noexcept> : assoc<_R, _Args...> {\n  };\n\n public:\n  using cache_type\
    \ =\n      _cache<decltype(&_F::template operator()<_recursive<_F> &>)>;\n\n private:\n\
    \  _F __fn;\n  cache_type __c;\n\n  struct _wrapper {\n    _F &__fn;\n    cache_type\
    \ &__c;\n\n    template <class... _Args>\n    decltype(auto) operator()(_Args\
    \ &&...__args) noexcept(\n        noexcept(__fn(*this, std::forward<_Args>(__args)...)))\
    \ {\n      typename cache_type::key_type __key{__args...};\n      auto __i = __c.lower_bound(__key);\n\
    \n      if _CXX17_CONSTEXPR (cache_type::value) {\n        if (__i != __c.end()\
    \ && __i->first == __key) return __i->second;\n\n        return __c\n        \
    \    .emplace_hint(__i, std::move(__key),\n                          __fn(*this,\
    \ std::forward<_Args>(__args)...))\n            ->second;\n      }\n\n      else\
    \ if (__i == __c.end() || *__i != __key)\n        __c.emplace_hint(__i, std::move(__key)),\n\
    \            __fn(*this, std::forward<_Args>(__args)...);\n    }\n  };\n\n public:\n\
    \  _recursive(_F &&__x) noexcept : __fn(__x) {}\n\n  // Function call.\n  template\
    \ <class... _Args>\n  decltype(auto) operator()(_Args &&...__args) noexcept(noexcept(_wrapper{\n\
    \      __fn, __c}(std::forward<_Args>(__args)...))) {\n    return _wrapper{__fn,\
    \ __c}(std::forward<_Args>(__args)...);\n  }\n};\n\n// Non-recursive ver.\ntemplate\
    \ <class _F> class _non_recursive {\n  template <class _T, class = void> struct\
    \ _get_func { using type = _T; };\n\n  template <class _T>\n  struct _get_func<_T,\
    \ std::__void_t<decltype(&_T::operator())>> {\n    using type = decltype(&_T::operator());\n\
    \  };\n\n  template <class...> struct _cache;\n\n  template <class _R, class...\
    \ _Args>\n  struct _cache<_R(_Args...)> : assoc<_R, _Args...> {};\n\n  template\
    \ <class _R, class... _Args>\n  struct _cache<_R (*)(_Args...)> : assoc<_R, _Args...>\
    \ {};\n\n  template <class _G, class _R, class... _Args>\n  struct _cache<_R (_G::*)(_Args...)>\
    \ : assoc<_R, _Args...> {};\n\n  template <class _G, class _R, class... _Args>\n\
    \  struct _cache<_R (_G::*)(_Args...) const> : assoc<_R, _Args...> {};\n\n  template\
    \ <class _R, class... _Args>\n  struct _cache<_R(_Args...) noexcept> : assoc<_R,\
    \ _Args...> {};\n\n  template <class _R, class... _Args>\n  struct _cache<_R (*)(_Args...)\
    \ noexcept> : assoc<_R, _Args...> {};\n\n  template <class _G, class _R, class...\
    \ _Args>\n  struct _cache<_R (_G::*)(_Args...) noexcept> : assoc<_R, _Args...>\
    \ {};\n\n  template <class _G, class _R, class... _Args>\n  struct _cache<_R (_G::*)(_Args...)\
    \ const noexcept> : assoc<_R, _Args...> {};\n\n public:\n  using cache_type =\
    \ _cache<typename _get_func<_F>::type>;\n\n private:\n  _F __fn;\n  cache_type\
    \ __c;\n\n public:\n  _non_recursive(_F &&__x) noexcept : __fn(__x) {}\n\n  //\
    \ Function call.\n  template <class... _Args>\n  decltype(auto) operator()(_Args\
    \ &&...__args) noexcept(\n      noexcept(__fn(std::forward<_Args>(__args)...)))\
    \ {\n    typename cache_type::key_type __key{__args...};\n    auto __i = __c.lower_bound(__key);\n\
    \n    if _CXX17_CONSTEXPR (cache_type::value) {\n      if (__i != __c.end() &&\
    \ __i->first == __key) return __i->second;\n\n      return __c\n          .emplace_hint(__i,\
    \ std::move(__key),\n                        __fn(std::forward<_Args>(__args)...))\n\
    \          ->second;\n    }\n\n    else if (__i == __c.end() || *__i != __key)\n\
    \      __c.emplace_hint(__i, std::move(__key)),\n          __fn(std::forward<_Args>(__args)...);\n\
    \  }\n};\n\ntemplate <class _F>\nusing _cached = std::conditional_t<is_recursive<_F>::value,\
    \ _recursive<_F>,\n                                   _non_recursive<_F>>;\n\n\
    }  // namespace _cached_impl\n\n/**\n * @brief Cached caller of function\n */\n\
    template <class _F> class cached : public _cached_impl::_cached<_F> {\n public:\n\
    \  // Construct a new cached object.\n  cached() noexcept : _cached_impl::_cached<_F>(_F{})\
    \ {}\n\n  // Construct a new cached object.\n  cached(_F __x) noexcept : _cached_impl::_cached<_F>(std::move(__x))\
    \ {}\n};\n\n}  // namespace workspace\n"
  dependsOn:
  - src/utils/fixed_point.hpp
  isVerificationFile: false
  path: src/utils/cached.hpp
  requiredBy: []
  timestamp: '2021-11-30 17:55:32+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/utils/cached.hpp
layout: document
redirect_from:
- /library/src/utils/cached.hpp
- /library/src/utils/cached.hpp.html
title: Cached
---
