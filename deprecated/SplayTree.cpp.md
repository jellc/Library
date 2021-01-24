---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"deprecated/SplayTree.cpp\"\n#include <bits/stdc++.h>\n\n\
    \ntemplate< typename Monoid = int >\nstruct SplayTree {\n  using F = function<\
    \ Monoid(Monoid, Monoid) >;\n\n  struct Node {\n    Node *l, *r, *p;\n    int\
    \ idx;\n    Monoid key, sum;\n    int sz;\n\n    bool is_root() {\n      return\
    \ !p || (p->l != this && p->r != this);\n    }\n\n    Node(int idx, const Monoid\
    \ &key) :\n        idx(idx), key(key), sum(key), sz(1),\n        l(nullptr), r(nullptr),\
    \ p(nullptr) {}\n  };\n\n  const F f;\n\n  SplayTree() : SplayTree([](Monoid a,\
    \ Monoid b) { return a + b; }, Monoid()) {}\n\n  SplayTree(const F &f, const Monoid\
    \ &M1) :\n      SplayTree(f, M1) {}\n\n  Node *make_node(int idx, const Monoid\
    \ &v = Monoid()) {\n    return new Node(idx, v);\n  }\n\n  void update(Node *t)\
    \ {\n    t->sz = 1;\n    t->sum = t->key;\n    if(t->l) t->sz += t->l->sz, t->sum\
    \ = f(t->l->sum, t->sum);\n    if(t->r) t->sz += t->r->sz, t->sum = f(t->sum,\
    \ t->r->sum);\n  }\n\n  void rotr(Node *t) {\n    auto *x = t->p, *y = x->p;\n\
    \    if((x->l = t->r)) t->r->p = x;\n    t->r = x, x->p = t;\n    update(x), update(t);\n\
    \    if((t->p = y)) {\n      if(y->l == x) y->l = t;\n      if(y->r == x) y->r\
    \ = t;\n      update(y);\n    }\n  }\n\n  void rotl(Node *t) {\n    auto *x =\
    \ t->p, *y = x->p;\n    if((x->r = t->l)) t->l->p = x;\n    t->l = x, x->p = t;\n\
    \    update(x), update(t);\n    if((t->p = y)) {\n      if(y->l == x) y->l = t;\n\
    \      if(y->r == x) y->r = t;\n      update(y);\n    }\n  }\n\n  void splay(Node\
    \ *t) {\n    while(!t->is_root()) {\n      auto *q = t->p;\n      if(q->is_root())\
    \ {\n        if(q->l == t) rotr(t);\n        else rotl(t);\n      } else {\n \
    \       auto *r = q->p;\n        if(r->l == q) {\n          if(q->l == t) rotr(q),\
    \ rotr(t);\n          else rotl(t), rotr(t);\n        } else {\n          if(q->r\
    \ == t) rotl(q), rotl(t);\n          else rotr(t), rotl(t);\n        }\n     \
    \ }\n    }\n  }\n};\n\n\n"
  code: "#include <bits/stdc++.h>\n\n\ntemplate< typename Monoid = int >\nstruct SplayTree\
    \ {\n  using F = function< Monoid(Monoid, Monoid) >;\n\n  struct Node {\n    Node\
    \ *l, *r, *p;\n    int idx;\n    Monoid key, sum;\n    int sz;\n\n    bool is_root()\
    \ {\n      return !p || (p->l != this && p->r != this);\n    }\n\n    Node(int\
    \ idx, const Monoid &key) :\n        idx(idx), key(key), sum(key), sz(1),\n  \
    \      l(nullptr), r(nullptr), p(nullptr) {}\n  };\n\n  const F f;\n\n  SplayTree()\
    \ : SplayTree([](Monoid a, Monoid b) { return a + b; }, Monoid()) {}\n\n  SplayTree(const\
    \ F &f, const Monoid &M1) :\n      SplayTree(f, M1) {}\n\n  Node *make_node(int\
    \ idx, const Monoid &v = Monoid()) {\n    return new Node(idx, v);\n  }\n\n  void\
    \ update(Node *t) {\n    t->sz = 1;\n    t->sum = t->key;\n    if(t->l) t->sz\
    \ += t->l->sz, t->sum = f(t->l->sum, t->sum);\n    if(t->r) t->sz += t->r->sz,\
    \ t->sum = f(t->sum, t->r->sum);\n  }\n\n  void rotr(Node *t) {\n    auto *x =\
    \ t->p, *y = x->p;\n    if((x->l = t->r)) t->r->p = x;\n    t->r = x, x->p = t;\n\
    \    update(x), update(t);\n    if((t->p = y)) {\n      if(y->l == x) y->l = t;\n\
    \      if(y->r == x) y->r = t;\n      update(y);\n    }\n  }\n\n  void rotl(Node\
    \ *t) {\n    auto *x = t->p, *y = x->p;\n    if((x->r = t->l)) t->l->p = x;\n\
    \    t->l = x, x->p = t;\n    update(x), update(t);\n    if((t->p = y)) {\n  \
    \    if(y->l == x) y->l = t;\n      if(y->r == x) y->r = t;\n      update(y);\n\
    \    }\n  }\n\n  void splay(Node *t) {\n    while(!t->is_root()) {\n      auto\
    \ *q = t->p;\n      if(q->is_root()) {\n        if(q->l == t) rotr(t);\n     \
    \   else rotl(t);\n      } else {\n        auto *r = q->p;\n        if(r->l ==\
    \ q) {\n          if(q->l == t) rotr(q), rotr(t);\n          else rotl(t), rotr(t);\n\
    \        } else {\n          if(q->r == t) rotl(q), rotl(t);\n          else rotr(t),\
    \ rotl(t);\n        }\n      }\n    }\n  }\n};\n\n\n"
  dependsOn: []
  isVerificationFile: false
  path: deprecated/SplayTree.cpp
  requiredBy: []
  timestamp: '2020-08-08 03:27:57+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: deprecated/SplayTree.cpp
layout: document
redirect_from:
- /library/deprecated/SplayTree.cpp
- /library/deprecated/SplayTree.cpp.html
title: deprecated/SplayTree.cpp
---
