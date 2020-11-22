#pragma once

/*
 * @file Li_Chao_tree.hpp
 * @brief Li-Chao Tree
 */

#include <cassert>
#include <functional>

namespace workspace {

/*
 * @struct Li_Chao_tree
 * @tparam T Scalar type.
 * @tparam Comp Comparison function object type
 * @tparam Infinity Identity element for 'Comp'.
 * @tparam Eps Error tolerance
 */
template <class T, class Comp = std::less<T>,
          T Infinity = std::numeric_limits<T>::max() / 2, T Eps = 1>
struct Li_Chao_tree {
  struct line {
    T slope = 0, intercept = Infinity;
    T eval(const T x) const { return slope * x + intercept; }
  };

  /*
   * @param lower Lower bound of domain
   * @param upper Upper bound of domain
   * @param comp Comparison function object
   */
  Li_Chao_tree(const T lower, const T upper, Comp comp = Comp())
      : lower(lower), upper(upper), comp(comp) {}

  ~Li_Chao_tree() { delete root; }

  bool empty() const { return !root; }

  T begin() const { return lower; }
  T end() const { return upper; }

  constexpr static T infinity = Infinity;
  constexpr static T eps = Eps;

  /*
   * @fn insert
   * @brief Insert a line.
   * @param slope Slope
   * @param intercept Intercept
   */
  void insert(const T slope, const T intercept) {
    root = insert(root, lower, upper, line{slope, intercept});
  }

  /*
   * @fn insert
   * @brief Insert a segment.
   * @param slope Slope
   * @param intercept Intercept
   * @param begin Left end, inclusive
   * @param end Right end, exclusive
   */
  void insert(const T slope, const T intercept, const T begin, const T end) {
    if (begin < end)
      root = insert(root, lower, upper, line{slope, intercept}, begin, end);
  }

  /*
   * @fn eval
   * @param x Position
   * @return The optimum at given position.
   */
  T eval(const T x) const {
    node *p = root;
    T l = lower, r = upper, opt = Infinity;
    while (p) {
      const T nval = p->__line.eval(x);
      if (comp(nval, opt)) opt = nval;
      if (r - l <= Eps) break;
      const T mid = (l + r) / 2;
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

  /*
   * @fn argmin
   * @param x Position
   * @return The line achieving the optimum at given position.
   */
  line get(const T x) const {
    assert(!empty());
    node *p = root, *arg = nullptr;
    T l = lower, r = upper, opt = Infinity;
    while (p) {
      const T nval = p->__line.eval(x);
      if (comp(nval, opt)) opt = nval, arg = p;
      if (r - l <= Eps) break;
      const T mid = (l + r) / 2;
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
    node(node const &) = delete;
    node &operator=(node const &) = delete;
    ~node() {
      delete __left;
      delete __right;
    }
  };

  T lower, upper;
  Comp comp;
  node *root = nullptr;

  node *insert(node *const p, const T l, const T r, line ln) {
    if (!p) return new node{ln};
    line &cur = p->__line;
    bool left_low = comp(ln.eval(l), cur.eval(l));
    bool right_low = comp(ln.eval(r - Eps), cur.eval(r - Eps));
    if (left_low == right_low) {
      if (left_low) cur = ln;
      return p;
    }
    if (r - l <= Eps) return p;
    T mid = (l + r) / 2;
    if (comp(ln.eval(mid), cur.eval(mid))) {
      std::swap(ln, cur);
      left_low = !left_low;
    }
    if (left_low)
      p->__left = insert(p->__left, l, mid, ln);
    else
      p->__right = insert(p->__right, mid, r, ln);
    return p;
  }

  node *insert(node *p, const T l, const T r, line ln, const T s, const T t) {
    if (t - Eps < l || r - Eps < s) return p;
    const T mid = (l + r) / 2;
    if (l < s || t < r) {
      if (!p) p = new node{};
      p->__left = insert(p->__left, l, mid, ln, s, t);
      p->__right = insert(p->__right, mid, r, ln, s, t);
      return p;
    }
    if (!p) return new node{ln};
    line &cur = p->__line;
    bool left_low = comp(ln.eval(l), cur.eval(l));
    bool right_low = comp(ln.eval(r - Eps), cur.eval(r - Eps));
    if (left_low == right_low) {
      if (left_low) cur = ln;
      return p;
    }
    if (r - l <= Eps) return p;
    if (comp(ln.eval(mid), cur.eval(mid))) {
      std::swap(ln, cur);
      left_low = !left_low;
    }
    if (left_low)
      p->__left = insert(p->__left, l, mid, ln);
    else
      p->__right = insert(p->__right, mid, r, ln);
    return p;
  }
};

}  // namespace workspace
