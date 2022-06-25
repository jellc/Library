---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/library-checker/line_add_get_min.test.cpp
    title: test/library-checker/line_add_get_min.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/segment_add_get_min.test.cpp
    title: test/library-checker/segment_add_get_min.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Li-Chao Tree
    links: []
  bundledCode: "#line 2 \"src/data_structure/convex_hull_trick/Li_Chao_tree.hpp\"\n\
    \n/**\n * @file Li_Chao_tree.hpp\n * @brief Li-Chao Tree\n */\n\n#include <cassert>\n\
    #include <functional>\n\nnamespace workspace {\n\n/**\n * @brief Li-Chao Tree\n\
    \ *\n * @tparam F Ordered Field.\n * @tparam Comp Comparison function object type\n\
    \ * @tparam Infinity Identity element for 'Comp'.\n * @tparam Eps Error tolerance\n\
    \ */\ntemplate <class F, class Comp = std::less<F>,\n          F Infinity = std::numeric_limits<F>::max()\
    \ / 2, F Eps = 1>\nstruct Li_Chao_tree {\n  constexpr static F infinity = Infinity;\n\
    \  constexpr static F eps = Eps;\n\n  struct line {\n    F slope = 0, intercept\
    \ = Infinity;\n    F eval(F x) const { return slope * x + intercept; }\n  };\n\
    \n  /**\n   * @param begin Lower bound of domain\n   * @param end Upper bound\
    \ of domain\n   * @param comp Comparison function object\n   */\n  Li_Chao_tree(const\
    \ F begin, const F end, Comp comp = Comp())\n      : begin(begin), end(end), comp(comp)\
    \ {}\n\n  ~Li_Chao_tree() { delete root; }\n\n  bool empty() const { return !root;\
    \ }\n\n  /**\n   * @brief Insert a line.\n   * @param ln Line\n   */\n  void insert(line\
    \ const &ln) { root = insert(root, begin, end, ln); }\n\n  /**\n   * @brief Insert\
    \ a line.\n   * @param slope Slope\n   * @param intercept Intercept\n   */\n \
    \ void insert(const F slope, const F intercept) {\n    insert(line{slope, intercept});\n\
    \  }\n\n  /**\n   * @brief Insert a segment.\n   * @param seg Segment\n   * @param\
    \ __begin Left end, inclusive\n   * @param __end Right end, exclusive\n   */\n\
    \  void insert(line const &seg, const F __begin, const F __end) {\n    if (__begin\
    \ < __end) root = insert(root, begin, end, seg, __begin, __end);\n  }\n\n  /**\n\
    \   * @brief Insert a segment.\n   * @param slope Slope\n   * @param intercept\
    \ Intercept\n   * @param __begin Left end, inclusive\n   * @param __end Right\
    \ end, exclusive\n   */\n  void insert(const F slope, const F intercept, const\
    \ F __begin,\n              const F __end) {\n    insert(line{slope, intercept},\
    \ __begin, __end);\n  }\n\n  /**\n   * @param x Position\n   * @return The optimum\
    \ at given position.\n   */\n  F eval(const F x) const {\n    node *p = root;\n\
    \    F l = begin, r = end, opt = Infinity;\n    while (p) {\n      const F nval\
    \ = p->__line.eval(x);\n      if (comp(nval, opt)) opt = nval;\n      if (r -\
    \ l <= Eps) break;\n      const F mid = (l + r) / 2;\n      if (x < mid) {\n \
    \       p = p->__left;\n        r = mid;\n      } else {\n        p = p->__right;\n\
    \        l = mid;\n      }\n    }\n    return opt;\n  }\n\n  /**\n   * @param\
    \ x Position\n   * @return The line achieving the optimum at given position.\n\
    \   */\n  line get(const F x) const {\n    assert(!empty());\n    node *p = root,\
    \ *arg = nullptr;\n    F l = begin, r = end, opt = Infinity;\n    while (p) {\n\
    \      const F nval = p->__line.eval(x);\n      if (comp(nval, opt)) opt = nval,\
    \ arg = p;\n      if (r - l <= Eps) break;\n      const F mid = (l + r) / 2;\n\
    \      if (x < mid) {\n        p = p->__left;\n        r = mid;\n      } else\
    \ {\n        p = p->__right;\n        l = mid;\n      }\n    }\n    return arg->__line;\n\
    \  }\n\n protected:\n  struct node {\n    line __line;\n    node *__left = nullptr,\
    \ *__right = nullptr;\n\n    node(line const &__l = line{}) : __line(__l) {}\n\
    \n    node(node const &__x) : __line(__x.__line) {\n      if (__x.__left) __left\
    \ = new node{*__x.__left};\n      if (__x.__right) __right = new node{*__x.__right};\n\
    \    }\n\n    node(node &&__x)\n        : __line(__x.__line), __left(__x.__left),\
    \ __right(__x.__right) {\n      __x.__left = __x.__right = nullptr;\n    }\n\n\
    \    node &operator=(node const &__x) {\n      __line = __x.__line;\n      delete\
    \ __left;\n      delete __right;\n      if (__x.__left) __left = new node{*__x.__left};\n\
    \      if (__x.__right) __right = new node{*__x.__right};\n    }\n\n    node &operator=(node\
    \ &&__x) {\n      __line = __x.__line;\n      std::swap(__left, __x.__left);\n\
    \      std::swap(__right, __x.__right);\n    }\n\n    ~node() {\n      delete\
    \ __left;\n      delete __right;\n    }\n  };\n\n  F begin, end;\n  Comp comp;\n\
    \  node *root = nullptr;\n\n public:\n  Li_Chao_tree(const Li_Chao_tree &__x)\n\
    \      : begin(__x.begin), end(__x.end), comp(__x.comp) {\n    if (__x.root) root\
    \ = new node{*__x.root};\n  }\n\n  Li_Chao_tree(Li_Chao_tree &&__x)\n      : begin(__x.begin),\
    \ end(__x.end), comp(__x.comp), root(__x.root) {\n    __x.root = nullptr;\n  }\n\
    \n  Li_Chao_tree &operator=(const Li_Chao_tree &__x) {\n    begin = __x.begin;\n\
    \    end = __x.end;\n    comp = __x.comp;\n    if (__x.root) root = new node{*__x.root};\n\
    \  }\n\n  Li_Chao_tree &operator=(Li_Chao_tree &&__x) {\n    begin = __x.begin;\n\
    \    end = __x.end;\n    comp = __x.comp;\n    root = __x.root;\n    __x.root\
    \ = nullptr;\n  }\n\n protected:\n  node *insert(node *const p, const F l, const\
    \ F r, line const &ln) {\n    if (!p) return new node{ln};\n    line &cur = p->__line;\n\
    \    const bool left_low = comp(ln.eval(l), cur.eval(l));\n    if (r - l <= Eps\
    \ || left_low == comp(ln.eval(r), cur.eval(r))) {\n      if (left_low) cur = ln;\n\
    \      return p;\n    }\n    const F mid = (l + r) / 2;\n    if (comp(ln.eval(mid),\
    \ cur.eval(mid))) {\n      if (left_low)\n        p->__right = insert(p->__right,\
    \ mid, r, cur);\n      else\n        p->__left = insert(p->__left, l, mid, cur);\n\
    \      cur = ln;\n    } else {\n      if (left_low)\n        p->__left = insert(p->__left,\
    \ l, mid, ln);\n      else\n        p->__right = insert(p->__right, mid, r, ln);\n\
    \    }\n    return p;\n  }\n\n  node *insert(node *p, const F l, const F r, line\
    \ const &seg, const F s,\n               const F t) {\n    if (s < l + Eps &&\
    \ r < t + Eps) return insert(p, l, r, seg);\n    if (l < t && s < r) {\n     \
    \ if (!p) p = new node{};\n      p->__left = insert(p->__left, l, (l + r) / 2,\
    \ seg, s, t);\n      p->__right = insert(p->__right, (l + r) / 2, r, seg, s, t);\n\
    \    }\n    return p;\n  }\n};\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file Li_Chao_tree.hpp\n * @brief Li-Chao Tree\n\
    \ */\n\n#include <cassert>\n#include <functional>\n\nnamespace workspace {\n\n\
    /**\n * @brief Li-Chao Tree\n *\n * @tparam F Ordered Field.\n * @tparam Comp\
    \ Comparison function object type\n * @tparam Infinity Identity element for 'Comp'.\n\
    \ * @tparam Eps Error tolerance\n */\ntemplate <class F, class Comp = std::less<F>,\n\
    \          F Infinity = std::numeric_limits<F>::max() / 2, F Eps = 1>\nstruct\
    \ Li_Chao_tree {\n  constexpr static F infinity = Infinity;\n  constexpr static\
    \ F eps = Eps;\n\n  struct line {\n    F slope = 0, intercept = Infinity;\n  \
    \  F eval(F x) const { return slope * x + intercept; }\n  };\n\n  /**\n   * @param\
    \ begin Lower bound of domain\n   * @param end Upper bound of domain\n   * @param\
    \ comp Comparison function object\n   */\n  Li_Chao_tree(const F begin, const\
    \ F end, Comp comp = Comp())\n      : begin(begin), end(end), comp(comp) {}\n\n\
    \  ~Li_Chao_tree() { delete root; }\n\n  bool empty() const { return !root; }\n\
    \n  /**\n   * @brief Insert a line.\n   * @param ln Line\n   */\n  void insert(line\
    \ const &ln) { root = insert(root, begin, end, ln); }\n\n  /**\n   * @brief Insert\
    \ a line.\n   * @param slope Slope\n   * @param intercept Intercept\n   */\n \
    \ void insert(const F slope, const F intercept) {\n    insert(line{slope, intercept});\n\
    \  }\n\n  /**\n   * @brief Insert a segment.\n   * @param seg Segment\n   * @param\
    \ __begin Left end, inclusive\n   * @param __end Right end, exclusive\n   */\n\
    \  void insert(line const &seg, const F __begin, const F __end) {\n    if (__begin\
    \ < __end) root = insert(root, begin, end, seg, __begin, __end);\n  }\n\n  /**\n\
    \   * @brief Insert a segment.\n   * @param slope Slope\n   * @param intercept\
    \ Intercept\n   * @param __begin Left end, inclusive\n   * @param __end Right\
    \ end, exclusive\n   */\n  void insert(const F slope, const F intercept, const\
    \ F __begin,\n              const F __end) {\n    insert(line{slope, intercept},\
    \ __begin, __end);\n  }\n\n  /**\n   * @param x Position\n   * @return The optimum\
    \ at given position.\n   */\n  F eval(const F x) const {\n    node *p = root;\n\
    \    F l = begin, r = end, opt = Infinity;\n    while (p) {\n      const F nval\
    \ = p->__line.eval(x);\n      if (comp(nval, opt)) opt = nval;\n      if (r -\
    \ l <= Eps) break;\n      const F mid = (l + r) / 2;\n      if (x < mid) {\n \
    \       p = p->__left;\n        r = mid;\n      } else {\n        p = p->__right;\n\
    \        l = mid;\n      }\n    }\n    return opt;\n  }\n\n  /**\n   * @param\
    \ x Position\n   * @return The line achieving the optimum at given position.\n\
    \   */\n  line get(const F x) const {\n    assert(!empty());\n    node *p = root,\
    \ *arg = nullptr;\n    F l = begin, r = end, opt = Infinity;\n    while (p) {\n\
    \      const F nval = p->__line.eval(x);\n      if (comp(nval, opt)) opt = nval,\
    \ arg = p;\n      if (r - l <= Eps) break;\n      const F mid = (l + r) / 2;\n\
    \      if (x < mid) {\n        p = p->__left;\n        r = mid;\n      } else\
    \ {\n        p = p->__right;\n        l = mid;\n      }\n    }\n    return arg->__line;\n\
    \  }\n\n protected:\n  struct node {\n    line __line;\n    node *__left = nullptr,\
    \ *__right = nullptr;\n\n    node(line const &__l = line{}) : __line(__l) {}\n\
    \n    node(node const &__x) : __line(__x.__line) {\n      if (__x.__left) __left\
    \ = new node{*__x.__left};\n      if (__x.__right) __right = new node{*__x.__right};\n\
    \    }\n\n    node(node &&__x)\n        : __line(__x.__line), __left(__x.__left),\
    \ __right(__x.__right) {\n      __x.__left = __x.__right = nullptr;\n    }\n\n\
    \    node &operator=(node const &__x) {\n      __line = __x.__line;\n      delete\
    \ __left;\n      delete __right;\n      if (__x.__left) __left = new node{*__x.__left};\n\
    \      if (__x.__right) __right = new node{*__x.__right};\n    }\n\n    node &operator=(node\
    \ &&__x) {\n      __line = __x.__line;\n      std::swap(__left, __x.__left);\n\
    \      std::swap(__right, __x.__right);\n    }\n\n    ~node() {\n      delete\
    \ __left;\n      delete __right;\n    }\n  };\n\n  F begin, end;\n  Comp comp;\n\
    \  node *root = nullptr;\n\n public:\n  Li_Chao_tree(const Li_Chao_tree &__x)\n\
    \      : begin(__x.begin), end(__x.end), comp(__x.comp) {\n    if (__x.root) root\
    \ = new node{*__x.root};\n  }\n\n  Li_Chao_tree(Li_Chao_tree &&__x)\n      : begin(__x.begin),\
    \ end(__x.end), comp(__x.comp), root(__x.root) {\n    __x.root = nullptr;\n  }\n\
    \n  Li_Chao_tree &operator=(const Li_Chao_tree &__x) {\n    begin = __x.begin;\n\
    \    end = __x.end;\n    comp = __x.comp;\n    if (__x.root) root = new node{*__x.root};\n\
    \  }\n\n  Li_Chao_tree &operator=(Li_Chao_tree &&__x) {\n    begin = __x.begin;\n\
    \    end = __x.end;\n    comp = __x.comp;\n    root = __x.root;\n    __x.root\
    \ = nullptr;\n  }\n\n protected:\n  node *insert(node *const p, const F l, const\
    \ F r, line const &ln) {\n    if (!p) return new node{ln};\n    line &cur = p->__line;\n\
    \    const bool left_low = comp(ln.eval(l), cur.eval(l));\n    if (r - l <= Eps\
    \ || left_low == comp(ln.eval(r), cur.eval(r))) {\n      if (left_low) cur = ln;\n\
    \      return p;\n    }\n    const F mid = (l + r) / 2;\n    if (comp(ln.eval(mid),\
    \ cur.eval(mid))) {\n      if (left_low)\n        p->__right = insert(p->__right,\
    \ mid, r, cur);\n      else\n        p->__left = insert(p->__left, l, mid, cur);\n\
    \      cur = ln;\n    } else {\n      if (left_low)\n        p->__left = insert(p->__left,\
    \ l, mid, ln);\n      else\n        p->__right = insert(p->__right, mid, r, ln);\n\
    \    }\n    return p;\n  }\n\n  node *insert(node *p, const F l, const F r, line\
    \ const &seg, const F s,\n               const F t) {\n    if (s < l + Eps &&\
    \ r < t + Eps) return insert(p, l, r, seg);\n    if (l < t && s < r) {\n     \
    \ if (!p) p = new node{};\n      p->__left = insert(p->__left, l, (l + r) / 2,\
    \ seg, s, t);\n      p->__right = insert(p->__right, (l + r) / 2, r, seg, s, t);\n\
    \    }\n    return p;\n  }\n};\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/data_structure/convex_hull_trick/Li_Chao_tree.hpp
  requiredBy: []
  timestamp: '2021-01-25 22:14:35+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/line_add_get_min.test.cpp
  - test/library-checker/segment_add_get_min.test.cpp
documentation_of: src/data_structure/convex_hull_trick/Li_Chao_tree.hpp
layout: document
redirect_from:
- /library/src/data_structure/convex_hull_trick/Li_Chao_tree.hpp
- /library/src/data_structure/convex_hull_trick/Li_Chao_tree.hpp.html
title: Li-Chao Tree
---
