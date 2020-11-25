---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"deprecated/Skew_heap.hpp\"\n// #line 2 \"Skew_heap.hpp\"\
    \n#ifndef Skew_heap_hpp\n#define Skew_heap_hpp\n\ntemplate <class T>\nclass skew_heap\n\
    {\n    const std::function<bool(const T&, const T&)> comp;\n  public:\n    struct\
    \ node\n    {\n        node *lft, *rgt; T key;\n        ~node() { delete lft;\
    \ delete rgt; }\n      private:\n        friend skew_heap;\n        void clear()\
    \ { lft = rgt = nullptr; }\n    }; // struct node\n\n    skew_heap(const std::function<bool(const\
    \ T&, const T&)> &f = std::less<T>()) : comp(f) {}\n\n    node *make() const {\
    \ return nullptr; }\n\n    node *push(node *root, const T &key) const\n    {\n\
    \        return meld(root, new node{ nullptr, nullptr, key });\n    }\n\n    node*\
    \ pop(node *root) const\n    {\n        node *nroot = meld(root->lft, root->rgt);\n\
    \        return root->clear(), nroot;\n    }\n\n    node *meld(node *x, node *y)\
    \ const\n    {\n        if(!x) return y;\n        if(!y) return x;\n        if(comp(x->key,\
    \ y->key)) std::swap(x, y);\n        x->rgt = meld(y, x->rgt);\n        std::swap(x->lft,\
    \ x->rgt);\n        return x;\n    }\n\n    bool empty(node *root) const { return\
    \ !root; }\n}; // class skew_heap\n\n#endif\n"
  code: "// #line 2 \"Skew_heap.hpp\"\n#ifndef Skew_heap_hpp\n#define Skew_heap_hpp\n\
    \ntemplate <class T>\nclass skew_heap\n{\n    const std::function<bool(const T&,\
    \ const T&)> comp;\n  public:\n    struct node\n    {\n        node *lft, *rgt;\
    \ T key;\n        ~node() { delete lft; delete rgt; }\n      private:\n      \
    \  friend skew_heap;\n        void clear() { lft = rgt = nullptr; }\n    }; //\
    \ struct node\n\n    skew_heap(const std::function<bool(const T&, const T&)> &f\
    \ = std::less<T>()) : comp(f) {}\n\n    node *make() const { return nullptr; }\n\
    \n    node *push(node *root, const T &key) const\n    {\n        return meld(root,\
    \ new node{ nullptr, nullptr, key });\n    }\n\n    node* pop(node *root) const\n\
    \    {\n        node *nroot = meld(root->lft, root->rgt);\n        return root->clear(),\
    \ nroot;\n    }\n\n    node *meld(node *x, node *y) const\n    {\n        if(!x)\
    \ return y;\n        if(!y) return x;\n        if(comp(x->key, y->key)) std::swap(x,\
    \ y);\n        x->rgt = meld(y, x->rgt);\n        std::swap(x->lft, x->rgt);\n\
    \        return x;\n    }\n\n    bool empty(node *root) const { return !root;\
    \ }\n}; // class skew_heap\n\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: deprecated/Skew_heap.hpp
  requiredBy: []
  timestamp: '2020-11-21 16:53:21+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: deprecated/Skew_heap.hpp
layout: document
redirect_from:
- /library/deprecated/Skew_heap.hpp
- /library/deprecated/Skew_heap.hpp.html
title: deprecated/Skew_heap.hpp
---
