#pragma once

/**
 * @file Li_Chao_tree.hpp
 * @brief Li-Chao Tree
 */

#include <cassert>
#include <functional>

namespace workspace {

/**
 * @brief Li-Chao Tree
 *
 * @tparam F Ordered Field.
 * @tparam Comp Comparison function object type
 * @tparam Infinity Identity element for 'Comp'.
 * @tparam Eps Error tolerance
 */
template <class F, class Comp = std::less<F>,
          F Infinity = std::numeric_limits<F>::max() / 2, F Eps = 1>
struct Li_Chao_tree {
  constexpr static F infinity = Infinity;
  constexpr static F eps = Eps;

  struct line {
    F slope = 0, intercept = Infinity;
    F eval(F x) const { return slope * x + intercept; }
  };

  /**
   * @param begin Lower bound of domain
   * @param end Upper bound of domain
   * @param comp Comparison function object
   */
  Li_Chao_tree(const F begin, const F end, Comp comp = Comp())
      : begin(begin), end(end), comp(comp) {}

  ~Li_Chao_tree() { delete root; }

  bool empty() const { return !root; }

  /**
   * @brief Insert a line.
   * @param ln Line
   */
  void insert(line const &ln) { root = insert(root, begin, end, ln); }

  /**
   * @brief Insert a line.
   * @param slope Slope
   * @param intercept Intercept
   */
  void insert(const F slope, const F intercept) {
    insert(line{slope, intercept});
  }

  /**
   * @brief Insert a segment.
   * @param seg Segment
   * @param __begin Left end, inclusive
   * @param __end Right end, exclusive
   */
  void insert(line const &seg, const F __begin, const F __end) {
    if (__begin < __end) root = insert(root, begin, end, seg, __begin, __end);
  }

  /**
   * @brief Insert a segment.
   * @param slope Slope
   * @param intercept Intercept
   * @param __begin Left end, inclusive
   * @param __end Right end, exclusive
   */
  void insert(const F slope, const F intercept, const F __begin,
              const F __end) {
    insert(line{slope, intercept}, __begin, __end);
  }

  /**
   * @param x Position
   * @return The optimum at given position.
   */
  F eval(const F x) const {
    node *p = root;
    F l = begin, r = end, opt = Infinity;
    while (p) {
      const F nval = p->__line.eval(x);
      if (comp(nval, opt)) opt = nval;
      if (r - l <= Eps) break;
      const F mid = (l + r) / 2;
      if (x < mid) {
        p = p->__left;
        r = mid;
      } else {
        p = p->__right;
        l = mid;
      }
    }
    return opt;
  }

  /**
   * @param x Position
   * @return The line achieving the optimum at given position.
   */
  line get(const F x) const {
    assert(!empty());
    node *p = root, *arg = nullptr;
    F l = begin, r = end, opt = Infinity;
    while (p) {
      const F nval = p->__line.eval(x);
      if (comp(nval, opt)) opt = nval, arg = p;
      if (r - l <= Eps) break;
      const F mid = (l + r) / 2;
      if (x < mid) {
        p = p->__left;
        r = mid;
      } else {
        p = p->__right;
        l = mid;
      }
    }
    return arg->__line;
  }

 protected:
  struct node {
    line __line;
    node *__left = nullptr, *__right = nullptr;

    node(line const &__l = line{}) : __line(__l) {}

    node(node const &__x) : __line(__x.__line) {
      if (__x.__left) __left = new node{*__x.__left};
      if (__x.__right) __right = new node{*__x.__right};
    }

    node(node &&__x)
        : __line(__x.__line), __left(__x.__left), __right(__x.__right) {
      __x.__left = __x.__right = nullptr;
    }

    node &operator=(node const &__x) {
      __line = __x.__line;
      delete __left;
      delete __right;
      if (__x.__left) __left = new node{*__x.__left};
      if (__x.__right) __right = new node{*__x.__right};
    }

    node &operator=(node &&__x) {
      __line = __x.__line;
      std::swap(__left, __x.__left);
      std::swap(__right, __x.__right);
    }

    ~node() {
      delete __left;
      delete __right;
    }
  };

  F begin, end;
  Comp comp;
  node *root = nullptr;

 public:
  Li_Chao_tree(const Li_Chao_tree &__x)
      : begin(__x.begin), end(__x.end), comp(__x.comp) {
    if (__x.root) root = new node{*__x.root};
  }

  Li_Chao_tree(Li_Chao_tree &&__x)
      : begin(__x.begin), end(__x.end), comp(__x.comp), root(__x.root) {
    __x.root = nullptr;
  }

  Li_Chao_tree &operator=(const Li_Chao_tree &__x) {
    begin = __x.begin;
    end = __x.end;
    comp = __x.comp;
    if (__x.root) root = new node{*__x.root};
  }

  Li_Chao_tree &operator=(Li_Chao_tree &&__x) {
    begin = __x.begin;
    end = __x.end;
    comp = __x.comp;
    root = __x.root;
    __x.root = nullptr;
  }

 protected:
  node *insert(node *const p, const F l, const F r, line const &ln) {
    if (!p) return new node{ln};
    line &cur = p->__line;
    const bool left_low = comp(ln.eval(l), cur.eval(l));
    if (r - l <= Eps || left_low == comp(ln.eval(r), cur.eval(r))) {
      if (left_low) cur = ln;
      return p;
    }
    const F mid = (l + r) / 2;
    if (comp(ln.eval(mid), cur.eval(mid))) {
      if (left_low)
        p->__right = insert(p->__right, mid, r, cur);
      else
        p->__left = insert(p->__left, l, mid, cur);
      cur = ln;
    } else {
      if (left_low)
        p->__left = insert(p->__left, l, mid, ln);
      else
        p->__right = insert(p->__right, mid, r, ln);
    }
    return p;
  }

  node *insert(node *p, const F l, const F r, line const &seg, const F s,
               const F t) {
    if (s < l + Eps && r < t + Eps) return insert(p, l, r, seg);
    if (l < t && s < r) {
      if (!p) p = new node{};
      p->__left = insert(p->__left, l, (l + r) / 2, seg, s, t);
      p->__right = insert(p->__right, (l + r) / 2, r, seg, s, t);
    }
    return p;
  }
};

}  // namespace workspace
