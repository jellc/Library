---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :warning: deprecated/SplayTree.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#54dac5afe1fcac2f65c059fc97b44a58">deprecated</a>
* <a href="{{ site.github.repository_url }}/blob/master/deprecated/SplayTree.cpp">View this file on GitHub</a>
    - Last commit date: 2020-08-08 03:27:57+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <bits/stdc++.h>


template< typename Monoid = int >
struct SplayTree {
  using F = function< Monoid(Monoid, Monoid) >;

  struct Node {
    Node *l, *r, *p;
    int idx;
    Monoid key, sum;
    int sz;

    bool is_root() {
      return !p || (p->l != this && p->r != this);
    }

    Node(int idx, const Monoid &key) :
        idx(idx), key(key), sum(key), sz(1),
        l(nullptr), r(nullptr), p(nullptr) {}
  };

  const F f;

  SplayTree() : SplayTree([](Monoid a, Monoid b) { return a + b; }, Monoid()) {}

  SplayTree(const F &f, const Monoid &M1) :
      SplayTree(f, M1) {}

  Node *make_node(int idx, const Monoid &v = Monoid()) {
    return new Node(idx, v);
  }

  void update(Node *t) {
    t->sz = 1;
    t->sum = t->key;
    if(t->l) t->sz += t->l->sz, t->sum = f(t->l->sum, t->sum);
    if(t->r) t->sz += t->r->sz, t->sum = f(t->sum, t->r->sum);
  }

  void rotr(Node *t) {
    auto *x = t->p, *y = x->p;
    if((x->l = t->r)) t->r->p = x;
    t->r = x, x->p = t;
    update(x), update(t);
    if((t->p = y)) {
      if(y->l == x) y->l = t;
      if(y->r == x) y->r = t;
      update(y);
    }
  }

  void rotl(Node *t) {
    auto *x = t->p, *y = x->p;
    if((x->r = t->l)) t->l->p = x;
    t->l = x, x->p = t;
    update(x), update(t);
    if((t->p = y)) {
      if(y->l == x) y->l = t;
      if(y->r == x) y->r = t;
      update(y);
    }
  }

  void splay(Node *t) {
    while(!t->is_root()) {
      auto *q = t->p;
      if(q->is_root()) {
        if(q->l == t) rotr(t);
        else rotl(t);
      } else {
        auto *r = q->p;
        if(r->l == q) {
          if(q->l == t) rotr(q), rotr(t);
          else rotl(t), rotr(t);
        } else {
          if(q->r == t) rotl(q), rotl(t);
          else rotr(t), rotl(t);
        }
      }
    }
  }
};



```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "deprecated/SplayTree.cpp"
#include <bits/stdc++.h>


template< typename Monoid = int >
struct SplayTree {
  using F = function< Monoid(Monoid, Monoid) >;

  struct Node {
    Node *l, *r, *p;
    int idx;
    Monoid key, sum;
    int sz;

    bool is_root() {
      return !p || (p->l != this && p->r != this);
    }

    Node(int idx, const Monoid &key) :
        idx(idx), key(key), sum(key), sz(1),
        l(nullptr), r(nullptr), p(nullptr) {}
  };

  const F f;

  SplayTree() : SplayTree([](Monoid a, Monoid b) { return a + b; }, Monoid()) {}

  SplayTree(const F &f, const Monoid &M1) :
      SplayTree(f, M1) {}

  Node *make_node(int idx, const Monoid &v = Monoid()) {
    return new Node(idx, v);
  }

  void update(Node *t) {
    t->sz = 1;
    t->sum = t->key;
    if(t->l) t->sz += t->l->sz, t->sum = f(t->l->sum, t->sum);
    if(t->r) t->sz += t->r->sz, t->sum = f(t->sum, t->r->sum);
  }

  void rotr(Node *t) {
    auto *x = t->p, *y = x->p;
    if((x->l = t->r)) t->r->p = x;
    t->r = x, x->p = t;
    update(x), update(t);
    if((t->p = y)) {
      if(y->l == x) y->l = t;
      if(y->r == x) y->r = t;
      update(y);
    }
  }

  void rotl(Node *t) {
    auto *x = t->p, *y = x->p;
    if((x->r = t->l)) t->l->p = x;
    t->l = x, x->p = t;
    update(x), update(t);
    if((t->p = y)) {
      if(y->l == x) y->l = t;
      if(y->r == x) y->r = t;
      update(y);
    }
  }

  void splay(Node *t) {
    while(!t->is_root()) {
      auto *q = t->p;
      if(q->is_root()) {
        if(q->l == t) rotr(t);
        else rotl(t);
      } else {
        auto *r = q->p;
        if(r->l == q) {
          if(q->l == t) rotr(q), rotr(t);
          else rotl(t), rotr(t);
        } else {
          if(q->r == t) rotl(q), rotl(t);
          else rotr(t), rotl(t);
        }
      }
    }
  }
};



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

