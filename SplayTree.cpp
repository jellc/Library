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


