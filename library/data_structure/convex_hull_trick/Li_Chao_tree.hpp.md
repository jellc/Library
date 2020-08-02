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
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :warning: data_structure/convex_hull_trick/Li_Chao_tree.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#85c1e2c9a6a68b0da546cc8076233cc6">data_structure/convex_hull_trick</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/convex_hull_trick/Li_Chao_tree.hpp">View this file on GitHub</a>
    - Last commit date: 2020-07-28 00:32:46+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <cassert>
#include <functional>

template <class T = long long, class Comp = std::less<T>>
class Li_Chao_tree
{
    struct line
    {
        T slop, icpt;
        line *lch = nullptr, *rch = nullptr;
        ~line() { delete lch; delete rch; }
        line *swap(line &rhs) { std::swap(slop, rhs.slop); std::swap(icpt, rhs.icpt); return this; }
        T eval(const T x) const { return slop * x + icpt; }
    }; // struct line

    T lower, upper, eps;
    Comp comp;
    line *root = nullptr;

    // // insert a line for the interval [l, r).
    line *insert(line *const p, const T l, const T r, line ln)
    {
        if(!p) return new line(ln);
        bool lcmp = comp(ln.eval(l), p->eval(l));
        bool rcmp = comp(ln.eval(r - eps), p->eval(r - eps));
        if(lcmp == rcmp) return lcmp ? p->swap(ln) : p;
        if(r - l <= eps) return p;
        T mid = (l + r) / 2;
        if(comp(ln.eval(mid), p->eval(mid)))
        {
            p->swap(ln);
            lcmp = !lcmp;
        }
        if(lcmp) p->lch = insert(p->lch, l, mid, ln);
        else p->rch = insert(p->rch, mid, r, ln);
        return p;
    }

    // // insert a segment for the interval [l, r).
    line *insert(line *const p, const T l, const T r, line ln, const T s, const T t)
    {
        if(t - eps < l || r - eps < s) return p;
        T mid = (l + r) / 2;
        if(l < s or t < r)
        {
            p->lch = insert(p->lch, l, mid, ln, s, t);
            p->rch = insert(p->rch, mid, r, ln, s, t);
            return p;
        }
        if(!p) return new line(ln);
        bool lcmp = comp(ln.eval(l), p->eval(l));
        bool rcmp = comp(ln.eval(r - eps), p->eval(r - eps));
        if(lcmp == rcmp) return lcmp ? p->swap(ln) : p;
        if(r - l <= eps) return p;
        if(comp(ln.eval(mid), p->eval(mid)))
        {
            p->swap(ln);
            lcmp = !lcmp;
        }
        if(lcmp) p->lch = insert(p->lch, l, mid, ln, s, t);
        else p->rch = insert(p->rch, mid, r, ln, s, t);
        return p;
    }

public:
    // domain set to be the interval [lower, upper).
    Li_Chao_tree(const T lower, const T upper, const T eps = 1, Comp comp = Comp())
        : lower(lower), upper(upper), eps(eps), comp(comp) {}

    ~Li_Chao_tree() { delete root; }

    bool empty() const { return !root; }

    // insert a line whose slope is p and inception is q.
    void insert(const T p, const T q) { root = insert(root, lower, upper, line{p, q}); }

    // insert a line(segment) whose slope is p, inception is q,
    // and domain is the interval [s, t).
    void insert(const T p, const T q, const T s, const T t) { if(s < t) root = insert(root, lower, upper, line{p, q}, s, t); }

    T get(const T x) const
    {
        assert(!empty());
        line *p = root;
        T l = lower, r = upper;
        T res = p->eval(x);
        while(p)
        {
            T nval = p->eval(x);
            if(comp(nval, res)) res = nval;
            if(r - l <= eps) return res;
            T mid = (l + r) / 2;
            if(x < mid)
            {
                p = p->lch;
                r = mid;
            }
            else
            {
                p = p->rch;
                l = mid;
            }
        }
        return res;
    }
}; // class Li_Chao_tree

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "data_structure/convex_hull_trick/Li_Chao_tree.hpp"
#include <cassert>
#include <functional>

template <class T = long long, class Comp = std::less<T>>
class Li_Chao_tree
{
    struct line
    {
        T slop, icpt;
        line *lch = nullptr, *rch = nullptr;
        ~line() { delete lch; delete rch; }
        line *swap(line &rhs) { std::swap(slop, rhs.slop); std::swap(icpt, rhs.icpt); return this; }
        T eval(const T x) const { return slop * x + icpt; }
    }; // struct line

    T lower, upper, eps;
    Comp comp;
    line *root = nullptr;

    // // insert a line for the interval [l, r).
    line *insert(line *const p, const T l, const T r, line ln)
    {
        if(!p) return new line(ln);
        bool lcmp = comp(ln.eval(l), p->eval(l));
        bool rcmp = comp(ln.eval(r - eps), p->eval(r - eps));
        if(lcmp == rcmp) return lcmp ? p->swap(ln) : p;
        if(r - l <= eps) return p;
        T mid = (l + r) / 2;
        if(comp(ln.eval(mid), p->eval(mid)))
        {
            p->swap(ln);
            lcmp = !lcmp;
        }
        if(lcmp) p->lch = insert(p->lch, l, mid, ln);
        else p->rch = insert(p->rch, mid, r, ln);
        return p;
    }

    // // insert a segment for the interval [l, r).
    line *insert(line *const p, const T l, const T r, line ln, const T s, const T t)
    {
        if(t - eps < l || r - eps < s) return p;
        T mid = (l + r) / 2;
        if(l < s or t < r)
        {
            p->lch = insert(p->lch, l, mid, ln, s, t);
            p->rch = insert(p->rch, mid, r, ln, s, t);
            return p;
        }
        if(!p) return new line(ln);
        bool lcmp = comp(ln.eval(l), p->eval(l));
        bool rcmp = comp(ln.eval(r - eps), p->eval(r - eps));
        if(lcmp == rcmp) return lcmp ? p->swap(ln) : p;
        if(r - l <= eps) return p;
        if(comp(ln.eval(mid), p->eval(mid)))
        {
            p->swap(ln);
            lcmp = !lcmp;
        }
        if(lcmp) p->lch = insert(p->lch, l, mid, ln, s, t);
        else p->rch = insert(p->rch, mid, r, ln, s, t);
        return p;
    }

public:
    // domain set to be the interval [lower, upper).
    Li_Chao_tree(const T lower, const T upper, const T eps = 1, Comp comp = Comp())
        : lower(lower), upper(upper), eps(eps), comp(comp) {}

    ~Li_Chao_tree() { delete root; }

    bool empty() const { return !root; }

    // insert a line whose slope is p and inception is q.
    void insert(const T p, const T q) { root = insert(root, lower, upper, line{p, q}); }

    // insert a line(segment) whose slope is p, inception is q,
    // and domain is the interval [s, t).
    void insert(const T p, const T q, const T s, const T t) { if(s < t) root = insert(root, lower, upper, line{p, q}, s, t); }

    T get(const T x) const
    {
        assert(!empty());
        line *p = root;
        T l = lower, r = upper;
        T res = p->eval(x);
        while(p)
        {
            T nval = p->eval(x);
            if(comp(nval, res)) res = nval;
            if(r - l <= eps) return res;
            T mid = (l + r) / 2;
            if(x < mid)
            {
                p = p->lch;
                r = mid;
            }
            else
            {
                p = p->rch;
                l = mid;
            }
        }
        return res;
    }
}; // class Li_Chao_tree

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

