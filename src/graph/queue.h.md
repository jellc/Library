---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: src/graph/base.h
    title: Base
  - icon: ':heavy_check_mark:'
    path: src/graph/digraph.h
    title: Digraph
  - icon: ':heavy_check_mark:'
    path: src/graph/forest.h
    title: Forest
  - icon: ':heavy_check_mark:'
    path: src/graph/graph.h
    title: Graph
  - icon: ':heavy_check_mark:'
    path: src/graph/scc.h
    title: Strongly Connected Component
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/GRL_1_A.test.cpp
    title: test/aizu-online-judge/GRL_1_A.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/GRL_2_A.test.cpp
    title: test/aizu-online-judge/GRL_2_A.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/GRL_3_C.test.cpp
    title: test/aizu-online-judge/GRL_3_C.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/GRL_4_A.test.cpp
    title: test/aizu-online-judge/GRL_4_A.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/GRL_5_A.test.cpp
    title: test/aizu-online-judge/GRL_5_A.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/scc.test.cpp
    title: test/library-checker/scc.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/shortest_path.test.cpp
    title: test/library-checker/shortest_path.test.cpp
  _isVerificationFailed: false
  _pathExtension: h
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Queue
    links: []
  bundledCode: "#line 2 \"src/graph/queue.h\"\n\n/**\n * @file queue.h\n * @brief\
    \ Queue\n */\n\n#include <queue>\n#include <stack>\n\nnamespace workspace {\n\n\
    namespace _graph_impl {\n\ntemplate <class _Base, class = void> struct stl_queue\
    \ : _Base {\n  auto pop() noexcept {\n    auto __tmp = std::move(_Base::front());\n\
    \    _Base::pop();\n    return __tmp;\n  }\n};\n\ntemplate <class _Base>\nstruct\
    \ stl_queue<_Base, std::__void_t<decltype(std::declval<_Base>().top())>>\n   \
    \ : _Base {\n  auto pop() noexcept {\n    auto __tmp = std::move(_Base::top());\n\
    \    _Base::pop();\n    return __tmp;\n  }\n};\n\n}  // namespace _graph_impl\n\
    \n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file queue.h\n * @brief Queue\n */\n\n#include <queue>\n\
    #include <stack>\n\nnamespace workspace {\n\nnamespace _graph_impl {\n\ntemplate\
    \ <class _Base, class = void> struct stl_queue : _Base {\n  auto pop() noexcept\
    \ {\n    auto __tmp = std::move(_Base::front());\n    _Base::pop();\n    return\
    \ __tmp;\n  }\n};\n\ntemplate <class _Base>\nstruct stl_queue<_Base, std::__void_t<decltype(std::declval<_Base>().top())>>\n\
    \    : _Base {\n  auto pop() noexcept {\n    auto __tmp = std::move(_Base::top());\n\
    \    _Base::pop();\n    return __tmp;\n  }\n};\n\n}  // namespace _graph_impl\n\
    \n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/graph/queue.h
  requiredBy:
  - src/graph/scc.h
  - src/graph/base.h
  - src/graph/graph.h
  - src/graph/forest.h
  - src/graph/digraph.h
  timestamp: '2021-10-09 10:54:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aizu-online-judge/GRL_1_A.test.cpp
  - test/aizu-online-judge/GRL_3_C.test.cpp
  - test/aizu-online-judge/GRL_5_A.test.cpp
  - test/aizu-online-judge/GRL_2_A.test.cpp
  - test/aizu-online-judge/GRL_4_A.test.cpp
  - test/library-checker/shortest_path.test.cpp
  - test/library-checker/scc.test.cpp
documentation_of: src/graph/queue.h
layout: document
redirect_from:
- /library/src/graph/queue.h
- /library/src/graph/queue.h.html
title: Queue
---
