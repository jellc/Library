---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Fixed Point Combinator
    links: []
  bundledCode: "#line 2 \"src/utils/fixed_point.hpp\"\n\n/**\n * @file fixed_point.hpp\n\
    \ * @brief Fixed Point Combinator\n */\n\n#include <map>\n\nnamespace workspace\
    \ {\n\n/**\n * @brief Fixed Point Combinator\n */\ntemplate <class _F> class fixed_point\
    \ {\n  _F __fn;\n\n public:\n  /**\n   * @param __fn 1st argument callable with\
    \ the rest of its arguments, and the\n   * return type specified.\n   */\n  fixed_point(_F\
    \ &&__fn) noexcept : __fn(std::forward<_F>(__fn)) {}\n\n  /**\n   * @brief Apply\
    \ *this to 1st argument.\n   * @param __args Rest of arguments.\n   */\n  template\
    \ <class... _Args>\n  decltype(auto) operator()(_Args &&... __args) const noexcept\
    \ {\n    return __fn(*this, std::forward<_Args>(__args)...);\n  }\n};\n\n/**\n\
    \ * @brief Cached version of Fixed Point Combinator\n */\ntemplate <class _F>\
    \ class fixed_point_cached {\n  template <class...> struct _cache;\n\n  template\
    \ <class _G, class _R, class _H, class... _Args>\n  struct _cache<_R (_G::*)(_H,\
    \ _Args...) const>\n      : std::map<std::tuple<_Args...>, _R> {};\n\n  using\
    \ cache =\n      _cache<decltype(&_F::template operator()<fixed_point_cached<_F>\
    \ &>)>;\n\n  _F __fn;\n  cache __ca;\n\n public:\n  /**\n   * @param __fn 1st\
    \ argument callable with the rest of its arguments, and the\n   * return type\
    \ specified.\n   */\n  fixed_point_cached(_F &&__fn) noexcept : __fn(std::forward<_F>(__fn))\
    \ {}\n\n  /**\n   * @brief Apply *this to 1st argument.\n   * @param __args Rest\
    \ of arguments.\n   */\n  template <class... _Args>\n  decltype(auto) operator()(_Args\
    \ &&... __args) noexcept {\n    typename cache::key_type __key(__args...);\n\n\
    \    if (auto __i = __ca.lower_bound(__key);\n        __i != __ca.end() && __i->first\
    \ == __key)\n      return __i->second;\n\n    else\n      return __ca\n      \
    \    .emplace_hint(__i, std::move(__key),\n                        __fn(*this,\
    \ std::forward<_Args>(__args)...))\n          ->second;\n  }\n};\n\n}  // namespace\
    \ workspace\n"
  code: "#pragma once\n\n/**\n * @file fixed_point.hpp\n * @brief Fixed Point Combinator\n\
    \ */\n\n#include <map>\n\nnamespace workspace {\n\n/**\n * @brief Fixed Point\
    \ Combinator\n */\ntemplate <class _F> class fixed_point {\n  _F __fn;\n\n public:\n\
    \  /**\n   * @param __fn 1st argument callable with the rest of its arguments,\
    \ and the\n   * return type specified.\n   */\n  fixed_point(_F &&__fn) noexcept\
    \ : __fn(std::forward<_F>(__fn)) {}\n\n  /**\n   * @brief Apply *this to 1st argument.\n\
    \   * @param __args Rest of arguments.\n   */\n  template <class... _Args>\n \
    \ decltype(auto) operator()(_Args &&... __args) const noexcept {\n    return __fn(*this,\
    \ std::forward<_Args>(__args)...);\n  }\n};\n\n/**\n * @brief Cached version of\
    \ Fixed Point Combinator\n */\ntemplate <class _F> class fixed_point_cached {\n\
    \  template <class...> struct _cache;\n\n  template <class _G, class _R, class\
    \ _H, class... _Args>\n  struct _cache<_R (_G::*)(_H, _Args...) const>\n     \
    \ : std::map<std::tuple<_Args...>, _R> {};\n\n  using cache =\n      _cache<decltype(&_F::template\
    \ operator()<fixed_point_cached<_F> &>)>;\n\n  _F __fn;\n  cache __ca;\n\n public:\n\
    \  /**\n   * @param __fn 1st argument callable with the rest of its arguments,\
    \ and the\n   * return type specified.\n   */\n  fixed_point_cached(_F &&__fn)\
    \ noexcept : __fn(std::forward<_F>(__fn)) {}\n\n  /**\n   * @brief Apply *this\
    \ to 1st argument.\n   * @param __args Rest of arguments.\n   */\n  template <class...\
    \ _Args>\n  decltype(auto) operator()(_Args &&... __args) noexcept {\n    typename\
    \ cache::key_type __key(__args...);\n\n    if (auto __i = __ca.lower_bound(__key);\n\
    \        __i != __ca.end() && __i->first == __key)\n      return __i->second;\n\
    \n    else\n      return __ca\n          .emplace_hint(__i, std::move(__key),\n\
    \                        __fn(*this, std::forward<_Args>(__args)...))\n      \
    \    ->second;\n  }\n};\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/utils/fixed_point.hpp
  requiredBy: []
  timestamp: '2021-02-02 14:18:47+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/utils/fixed_point.hpp
layout: document
redirect_from:
- /library/src/utils/fixed_point.hpp
- /library/src/utils/fixed_point.hpp.html
title: Fixed Point Combinator
---
