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


# :heavy_check_mark: data_structure/Mo.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/Mo.hpp">View this file on GitHub</a>
    - Last commit date: 2020-08-03 02:47:43+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/library-checker/range_kth_smallest.test.cpp.html">test/library-checker/range_kth_smallest.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/library-checker/static_range_inversions_query.test.cpp.html">test/library-checker/static_range_inversions_query.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <cassert>
#include <cmath>
#include <functional>
#include <vector>

template <class Add, class Del>
class Mo
{
    Add add; Del del;
    std::vector<size_t> lft, rgt, ord;
    std::vector<size_t>::iterator itr;
    bool made;
    size_t width, nl, nr;

    void make()
    {
        made = true;
        ord.resize(size());
        for(size_t i = 0; i != size(); ++i) ord[i] = i;
        std::sort(ord.begin(), ord.end(),
        [&](size_t x, size_t y)
        {
            if(lft[x] / width != lft[y] / width) return lft[x] < lft[y];
            return rgt[x] < rgt[y];
        });
        itr = ord.begin();
    }

public:
    Mo(size_t n = 0, Add add = Add(), Del del = Del())
        : add(add), del(del), made(), width(sqrt(n)), nl(), nr() {}

    size_t size() const { return lft.size(); }

    void set(size_t l, size_t r)
    {
        assert(!made);
        lft.emplace_back(l), rgt.emplace_back(r);
    }

    size_t process()
    {
        if(!made) make();
        if(itr == ord.end()) return ord.size();
        const size_t id = *itr++, l = lft[id], r = rgt[id];
        while(nl > l) add(--nl);
        while(nr < r) add(nr++);
        while(nl < l) del(nl++);
        while(nr > r) del(--nr);
        return id;
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "data_structure/Mo.hpp"
#include <cassert>
#include <cmath>
#include <functional>
#include <vector>

template <class Add, class Del>
class Mo
{
    Add add; Del del;
    std::vector<size_t> lft, rgt, ord;
    std::vector<size_t>::iterator itr;
    bool made;
    size_t width, nl, nr;

    void make()
    {
        made = true;
        ord.resize(size());
        for(size_t i = 0; i != size(); ++i) ord[i] = i;
        std::sort(ord.begin(), ord.end(),
        [&](size_t x, size_t y)
        {
            if(lft[x] / width != lft[y] / width) return lft[x] < lft[y];
            return rgt[x] < rgt[y];
        });
        itr = ord.begin();
    }

public:
    Mo(size_t n = 0, Add add = Add(), Del del = Del())
        : add(add), del(del), made(), width(sqrt(n)), nl(), nr() {}

    size_t size() const { return lft.size(); }

    void set(size_t l, size_t r)
    {
        assert(!made);
        lft.emplace_back(l), rgt.emplace_back(r);
    }

    size_t process()
    {
        if(!made) make();
        if(itr == ord.end()) return ord.size();
        const size_t id = *itr++, l = lft[id], r = rgt[id];
        while(nl > l) add(--nl);
        while(nr < r) add(nr++);
        while(nl < l) del(nl++);
        while(nr > r) del(--nr);
        return id;
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

