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


# :heavy_check_mark: test/library-checker/unionfind.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#8a40f8ed03f4cdb6c2fe0a2d4731a143">test/library-checker</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/library-checker/unionfind.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-08-30 00:35:46+09:00


* see: <a href="https://judge.yosupo.jp/problem/unionfind">https://judge.yosupo.jp/problem/unionfind</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/data_structure/union_find/basic.hpp.html">data_structure/union_find/basic.hpp</a>
* :heavy_check_mark: <a href="../../../library/data_structure/union_find/unbalanced.hpp.html">data_structure/union_find/unbalanced.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"
#include "data_structure/union_find/unbalanced.hpp"
#include <cstdio>

int main()
{
    int n,q; scanf("%d%d",&n,&q);
    union_find uf(n);
    union_find_unbalanced ufu(n);
    while(q--)
    {
        int t,l,r; scanf("%d%d%d",&t,&l,&r);
        if(t)
        {
            printf("%d\n",uf.same(l,r));
            assert(uf.same(l,r)==ufu.same(l,r));
        }
        else
        {
            uf.unite(l,r);
            ufu.unite(l,r);
        }
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/library-checker/unionfind.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"
#line 2 "data_structure/union_find/basic.hpp"
#include <cassert>
#include <vector>
struct union_find
{
    union_find(const size_t &n = 0) : link(n, -1) {}

    size_t find(const size_t &x)
    {
        assert(x < size());
        return link[x] < 0 ? x : (link[x] = find(link[x]));
    }

    size_t size() const { return link.size(); }

    size_t size(const size_t &x)
    {
        assert(x < size());
        return -link[find(x)];
    }

    bool same(const size_t &x, const size_t &y)
    {
        assert(x < size() && y < size());
        return find(x) == find(y);
    }

    virtual bool unite(size_t x, size_t y)
    {
        assert(x < size() && y < size());
        x = find(x), y = find(y);
        if(x == y) return false;
        if(link[x] > link[y]) std::swap(x, y);
        link[x] += link[y];
        link[y] = x;
        return true;
    }

protected:
    std::vector<int> link;
}; // class union_find
#line 3 "data_structure/union_find/unbalanced.hpp"
struct union_find_unbalanced : union_find
{
    using union_find::union_find;
    
    bool unite(size_t x, size_t y) override
    {
        assert(x < size() && y < size());
        x = find(x), y = find(y);
        if(x == y) return false;
        link[x] += link[y];
        link[y] = x;
        return true;
    }
}; // class union_find_unbalanced
#line 3 "test/library-checker/unionfind.test.cpp"
#include <cstdio>

int main()
{
    int n,q; scanf("%d%d",&n,&q);
    union_find uf(n);
    union_find_unbalanced ufu(n);
    while(q--)
    {
        int t,l,r; scanf("%d%d%d",&t,&l,&r);
        if(t)
        {
            printf("%d\n",uf.same(l,r));
            assert(uf.same(l,r)==ufu.same(l,r));
        }
        else
        {
            uf.unite(l,r);
            ufu.unite(l,r);
        }
    }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

