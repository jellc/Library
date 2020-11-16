---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/library-checker/line_add_get_min.test.cpp
    title: test/library-checker/line_add_get_min.test.cpp
  - icon: ':x:'
    path: test/library-checker/segment_add_get_min.test.cpp
    title: test/library-checker/segment_add_get_min.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"src/data_structure/convex_hull_trick/Li_Chao_tree.hpp\"\n\
    #include <cassert>\n#include <functional>\n\ntemplate <class T = long long, class\
    \ Comp = std::less<T>, T infty = std::numeric_limits<T>::max()>\nclass Li_Chao_tree\n\
    {\n    struct line\n    {\n        T slop = 0, icpt = infty;\n        line *lch\
    \ = nullptr, *rch = nullptr;\n        ~line() { delete lch; delete rch; }\n  \
    \      line *swap(line &rhs) { std::swap(slop, rhs.slop); std::swap(icpt, rhs.icpt);\
    \ return this; }\n        T eval(const T x) const { return slop * x + icpt; }\n\
    \    }; // struct line\n\n    T lower, upper, eps;\n    Comp comp;\n    line *root\
    \ = nullptr;\n\n    // // insert a line for the interval [l, r).\n    line *insert(line\
    \ *const p, const T l, const T r, line ln)\n    {\n        if(!p) return new line(ln);\n\
    \        bool lcmp = comp(ln.eval(l), p->eval(l));\n        bool rcmp = comp(ln.eval(r\
    \ - eps), p->eval(r - eps));\n        if(lcmp == rcmp) return lcmp ? p->swap(ln)\
    \ : p;\n        if(r - l <= eps) return p;\n        T mid = (l + r) / 2;\n   \
    \     if(comp(ln.eval(mid), p->eval(mid)))\n        {\n            p->swap(ln);\n\
    \            lcmp = !lcmp;\n        }\n        if(lcmp) p->lch = insert(p->lch,\
    \ l, mid, ln);\n        else p->rch = insert(p->rch, mid, r, ln);\n        return\
    \ p;\n    }\n\n    // // insert a segment for the interval [l, r).\n    line *insert(line\
    \ *const p, const T l, const T r, line ln, const T s, const T t)\n    {\n    \
    \    if(t - eps < l || r - eps < s) return p;\n        T mid = (l + r) / 2;\n\
    \        if(l < s or t < r)\n        {\n            line *np = p ? p : new line;\n\
    \            np->lch = insert(np->lch, l, mid, ln, s, t);\n            np->rch\
    \ = insert(np->rch, mid, r, ln, s, t);\n            return np;\n        }\n  \
    \      if(!p) return new line(ln);\n        bool lcmp = comp(ln.eval(l), p->eval(l));\n\
    \        bool rcmp = comp(ln.eval(r - eps), p->eval(r - eps));\n        if(lcmp\
    \ == rcmp) return lcmp ? p->swap(ln) : p;\n        if(r - l <= eps) return p;\n\
    \        if(comp(ln.eval(mid), p->eval(mid)))\n        {\n            p->swap(ln);\n\
    \            lcmp = !lcmp;\n        }\n        if(lcmp) p->lch = insert(p->lch,\
    \ l, mid, ln, s, t);\n        else p->rch = insert(p->rch, mid, r, ln, s, t);\n\
    \        return p;\n    }\n\npublic:\n    // domain set to be the interval [lower,\
    \ upper).\n    Li_Chao_tree(const T lower, const T upper, const T eps = 1, Comp\
    \ comp = Comp())\n        : lower(lower), upper(upper), eps(eps), comp(comp) {}\n\
    \n    ~Li_Chao_tree() { delete root; }\n\n    bool empty() const { return !root;\
    \ }\n\n    // insert a line whose slope is p and inception is q.\n    void insert(const\
    \ T p, const T q) { root = insert(root, lower, upper, line{p, q}); }\n\n    //\
    \ insert a line(segment) whose slope is p, inception is q,\n    // and domain\
    \ is the interval [s, t).\n    void insert(const T p, const T q, const T s, const\
    \ T t) { if(s < t) root = insert(root, lower, upper, line{p, q}, s, t); }\n\n\
    \    T get(const T x) const\n    {\n        line *p = root;\n        T l = lower,\
    \ r = upper;\n        T res = infty;\n        while(p)\n        {\n          \
    \  T nval = p->eval(x);\n            if(comp(nval, res)) res = nval;\n       \
    \     if(r - l <= eps) return res;\n            T mid = (l + r) / 2;\n       \
    \     if(x < mid)\n            {\n                p = p->lch;\n              \
    \  r = mid;\n            }\n            else\n            {\n                p\
    \ = p->rch;\n                l = mid;\n            }\n        }\n        return\
    \ res;\n    }\n}; // class Li_Chao_tree\n"
  code: "#include <cassert>\n#include <functional>\n\ntemplate <class T = long long,\
    \ class Comp = std::less<T>, T infty = std::numeric_limits<T>::max()>\nclass Li_Chao_tree\n\
    {\n    struct line\n    {\n        T slop = 0, icpt = infty;\n        line *lch\
    \ = nullptr, *rch = nullptr;\n        ~line() { delete lch; delete rch; }\n  \
    \      line *swap(line &rhs) { std::swap(slop, rhs.slop); std::swap(icpt, rhs.icpt);\
    \ return this; }\n        T eval(const T x) const { return slop * x + icpt; }\n\
    \    }; // struct line\n\n    T lower, upper, eps;\n    Comp comp;\n    line *root\
    \ = nullptr;\n\n    // // insert a line for the interval [l, r).\n    line *insert(line\
    \ *const p, const T l, const T r, line ln)\n    {\n        if(!p) return new line(ln);\n\
    \        bool lcmp = comp(ln.eval(l), p->eval(l));\n        bool rcmp = comp(ln.eval(r\
    \ - eps), p->eval(r - eps));\n        if(lcmp == rcmp) return lcmp ? p->swap(ln)\
    \ : p;\n        if(r - l <= eps) return p;\n        T mid = (l + r) / 2;\n   \
    \     if(comp(ln.eval(mid), p->eval(mid)))\n        {\n            p->swap(ln);\n\
    \            lcmp = !lcmp;\n        }\n        if(lcmp) p->lch = insert(p->lch,\
    \ l, mid, ln);\n        else p->rch = insert(p->rch, mid, r, ln);\n        return\
    \ p;\n    }\n\n    // // insert a segment for the interval [l, r).\n    line *insert(line\
    \ *const p, const T l, const T r, line ln, const T s, const T t)\n    {\n    \
    \    if(t - eps < l || r - eps < s) return p;\n        T mid = (l + r) / 2;\n\
    \        if(l < s or t < r)\n        {\n            line *np = p ? p : new line;\n\
    \            np->lch = insert(np->lch, l, mid, ln, s, t);\n            np->rch\
    \ = insert(np->rch, mid, r, ln, s, t);\n            return np;\n        }\n  \
    \      if(!p) return new line(ln);\n        bool lcmp = comp(ln.eval(l), p->eval(l));\n\
    \        bool rcmp = comp(ln.eval(r - eps), p->eval(r - eps));\n        if(lcmp\
    \ == rcmp) return lcmp ? p->swap(ln) : p;\n        if(r - l <= eps) return p;\n\
    \        if(comp(ln.eval(mid), p->eval(mid)))\n        {\n            p->swap(ln);\n\
    \            lcmp = !lcmp;\n        }\n        if(lcmp) p->lch = insert(p->lch,\
    \ l, mid, ln, s, t);\n        else p->rch = insert(p->rch, mid, r, ln, s, t);\n\
    \        return p;\n    }\n\npublic:\n    // domain set to be the interval [lower,\
    \ upper).\n    Li_Chao_tree(const T lower, const T upper, const T eps = 1, Comp\
    \ comp = Comp())\n        : lower(lower), upper(upper), eps(eps), comp(comp) {}\n\
    \n    ~Li_Chao_tree() { delete root; }\n\n    bool empty() const { return !root;\
    \ }\n\n    // insert a line whose slope is p and inception is q.\n    void insert(const\
    \ T p, const T q) { root = insert(root, lower, upper, line{p, q}); }\n\n    //\
    \ insert a line(segment) whose slope is p, inception is q,\n    // and domain\
    \ is the interval [s, t).\n    void insert(const T p, const T q, const T s, const\
    \ T t) { if(s < t) root = insert(root, lower, upper, line{p, q}, s, t); }\n\n\
    \    T get(const T x) const\n    {\n        line *p = root;\n        T l = lower,\
    \ r = upper;\n        T res = infty;\n        while(p)\n        {\n          \
    \  T nval = p->eval(x);\n            if(comp(nval, res)) res = nval;\n       \
    \     if(r - l <= eps) return res;\n            T mid = (l + r) / 2;\n       \
    \     if(x < mid)\n            {\n                p = p->lch;\n              \
    \  r = mid;\n            }\n            else\n            {\n                p\
    \ = p->rch;\n                l = mid;\n            }\n        }\n        return\
    \ res;\n    }\n}; // class Li_Chao_tree\n"
  dependsOn: []
  isVerificationFile: false
  path: src/data_structure/convex_hull_trick/Li_Chao_tree.hpp
  requiredBy: []
  timestamp: '2020-11-16 21:34:32+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/library-checker/segment_add_get_min.test.cpp
  - test/library-checker/line_add_get_min.test.cpp
documentation_of: src/data_structure/convex_hull_trick/Li_Chao_tree.hpp
layout: document
redirect_from:
- /library/src/data_structure/convex_hull_trick/Li_Chao_tree.hpp
- /library/src/data_structure/convex_hull_trick/Li_Chao_tree.hpp.html
title: src/data_structure/convex_hull_trick/Li_Chao_tree.hpp
---
