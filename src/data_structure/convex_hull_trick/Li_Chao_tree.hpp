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
 * @tparam T Ordered ring.
 * @tparam Comp Comparison function object type
 * @tparam Infinity Identity element for 'Comp'.
 * @tparam Eps Error tolerance
 */
template <class T, class Comp = std::less<T>,
          T Infinity = std::numeric_limits<T>::max() / 2, T Eps = 1>
struct Li_Chao_tree {
  constexpr static T infinity = Infinity;
  constexpr static T eps = Eps;

  struct line {
    T slope = 0, intercept = Infinity;
    T eval(const T x) const { return slope * x + intercept; }
  };

  /*
   * @param begin Lower bound of domain
   * @param end Upper bound of domain
   * @param comp Comparison function object
   */
  Li_Chao_tree(const T begin, const T end, Comp comp = Comp())
      : begin(begin), end(end), comp(comp) {}

  ~Li_Chao_tree() { delete root; }

  bool empty() const { return !root; }

  /*
   * @fn insert
   * @brief Insert a line.
   * @param ln Line
   */
  void insert(line ln) { root = insert(root, begin, end, ln); }

  /*
   * @fn insert
   * @brief Insert a line.
   * @param slope Slope
   * @param intercept Intercept
   */
  void insert(const T slope, const T intercept) {
    insert(line{slope, intercept});
  }

  /*
   * @fn insert
   * @brief Insert a segment.
   * @param seg Segment
   * @param __begin Left end, inclusive
   * @param __end Right end, exclusive
   */
  void insert(line seg, const T __begin, const T __end) {
    if (__begin < __end) root = insert(root, begin, end, seg, __begin, __end);
  }

  /*
   * @fn insert
   * @brief Insert a segment.
   * @param slope Slope
   * @param intercept Intercept
   * @param __begin Left end, inclusive
   * @param __end Right end, exclusive
   */
  void insert(const T slope, const T intercept, const T __begin,
              const T __end) {
    insert(line{slope, intercept}, __begin, __end);
  }

  /*
   * @fn eval
   * @param x Position
   * @return The optimum at given position.
   */
  T eval(const T x) const {
    node *p = root;
    T l = begin, r = end, opt = Infinity;
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
    T l = begin, r = end, opt = Infinity;
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

  const T begin, end;
  Comp comp;
  node *root = nullptr;

  node *insert(node *const p, const T l, const T r, line const &ln) {
    if (!p) return new node{ln};
    line &cur = p->__line;
    const bool left_low = comp(ln.eval(l), cur.eval(l));
    if (r - l <= Eps || left_low == comp(ln.eval(r), cur.eval(r))) {
      if (left_low) cur = ln;
      return p;
    }
    const T mid = (l + r) / 2;
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

  node *insert(node *p, const T l, const T r, line const &seg, const T s,
               const T t) {
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
