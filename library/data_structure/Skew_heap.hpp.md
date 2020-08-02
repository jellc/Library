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


# :warning: data_structure/Skew_heap.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/Skew_heap.hpp">View this file on GitHub</a>
    - Last commit date: 2020-01-15 19:13:04+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// #line 2 "Skew_heap.hpp"
#ifndef Skew_heap_hpp
#define Skew_heap_hpp

template <class T>
class skew_heap
{
    const std::function<bool(const T&, const T&)> comp;
  public:
    struct node
    {
        node *lft, *rgt; T key;
        ~node() { delete lft; delete rgt; }
      private:
        friend skew_heap;
        void clear() { lft = rgt = nullptr; }
    }; // struct node

    skew_heap(const std::function<bool(const T&, const T&)> &f = std::less<T>()) : comp(f) {}

    node *make() const { return nullptr; }

    node *push(node *root, const T &key) const
    {
        return meld(root, new node{ nullptr, nullptr, key });
    }

    node* pop(node *root) const
    {
        node *nroot = meld(root->lft, root->rgt);
        return root->clear(), nroot;
    }

    node *meld(node *x, node *y) const
    {
        if(!x) return y;
        if(!y) return x;
        if(comp(x->key, y->key)) std::swap(x, y);
        x->rgt = meld(y, x->rgt);
        std::swap(x->lft, x->rgt);
        return x;
    }

    bool empty(node *root) const { return !root; }
}; // class skew_heap

#endif
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "data_structure/Skew_heap.hpp"
// #line 2 "Skew_heap.hpp"
#ifndef Skew_heap_hpp
#define Skew_heap_hpp

template <class T>
class skew_heap
{
    const std::function<bool(const T&, const T&)> comp;
  public:
    struct node
    {
        node *lft, *rgt; T key;
        ~node() { delete lft; delete rgt; }
      private:
        friend skew_heap;
        void clear() { lft = rgt = nullptr; }
    }; // struct node

    skew_heap(const std::function<bool(const T&, const T&)> &f = std::less<T>()) : comp(f) {}

    node *make() const { return nullptr; }

    node *push(node *root, const T &key) const
    {
        return meld(root, new node{ nullptr, nullptr, key });
    }

    node* pop(node *root) const
    {
        node *nroot = meld(root->lft, root->rgt);
        return root->clear(), nroot;
    }

    node *meld(node *x, node *y) const
    {
        if(!x) return y;
        if(!y) return x;
        if(comp(x->key, y->key)) std::swap(x, y);
        x->rgt = meld(y, x->rgt);
        std::swap(x->lft, x->rgt);
        return x;
    }

    bool empty(node *root) const { return !root; }
}; // class skew_heap

#endif

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

