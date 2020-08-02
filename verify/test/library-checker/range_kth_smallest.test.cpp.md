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


# :heavy_check_mark: test/library-checker/range_kth_smallest.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#8a40f8ed03f4cdb6c2fe0a2d4731a143">test/library-checker</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/library-checker/range_kth_smallest.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-08-03 02:03:38+09:00


* see: <a href="https://judge.yosupo.jp/problem/range_kth_smallest">https://judge.yosupo.jp/problem/range_kth_smallest</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/data_structure/Mo.hpp.html">data_structure/Mo.hpp</a>
* :heavy_check_mark: <a href="../../../library/utils/coordinate_compression.hpp.html">utils/coordinate_compression.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"
#include "../../data_structure/Mo.hpp"
#include "../../utils/coordinate_compression.hpp"
#include <cstdio>

int main()
{
    int n,q;
    scanf("%d%d",&n,&q);
    std::vector<int> a(n);
    for(int &e: a) scanf("%d",&e);
    coordinate_compression ccmp(a);
    int bsize=std::sqrt(ccmp.count())+1;
    std::vector<int> cnt(ccmp.count()),bcnt(bsize);
    auto add=[&](int i)
    {
        int now=ccmp[i];
        cnt[now]++;
        bcnt[now/bsize]++;
    };
    auto del=[&](int i)
    {
        int now=ccmp[i];
        cnt[now]--;
        bcnt[now/bsize]--;
    };
    Mo mo(n,add,del);
    std::vector<int> k(q),ans(q);
    for(int l,r,i=0; i<q; i++)
    {
        scanf("%d%d%d",&l,&r,&k[i]);
        mo.set(l,r);
    }
    for(int t=0; t<q; t++)
    {
        int qid=mo.process();
        for(int i=0,j=0,nk=k[qid]; i<bsize; i++,j+=bsize)
        {
            if(bcnt[i]>nk)
            {
                int h;
                for(h=j; nk>=cnt[h]; h++)
                {
                    nk-=cnt[h];
                }
                ans[qid]=ccmp.value_of(h);
                break;
            }
            else
            {
                nk-=bcnt[i];
            }
        }
    }
    for(int e: ans) printf("%d\n",e);
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/library-checker/range_kth_smallest.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"
#line 1 "data_structure/Mo.hpp"
#include <cassert>
#include <cmath>
#include <functional>
#include <vector>
#include <numeric>

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
        ord.resize(lft.size());
        std::iota(ord.begin(), ord.end(), 0);
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

    void set(size_t l, size_t r)
    {
        assert(!made);
        lft.emplace_back(l), rgt.emplace_back(r);
    }

    size_t process()
    {
        if(!made) make();
        if(itr == ord.end()) return ord.size();
        size_t now = *itr++;
        while(nl > lft[now]) add(--nl);
        while(nr < rgt[now]) add(nr++);
        while(nl < lft[now]) del(nl++);
        while(nr > rgt[now]) del(--nr);
        return now;
    }
};
#line 1 "utils/coordinate_compression.hpp"
#include <algorithm>
#line 4 "utils/coordinate_compression.hpp"

template <class T>
class coordinate_compression
{
    std::vector<T> uniquely;
    std::vector<size_t> compressed;

public:
    coordinate_compression(const std::vector<T> &raw) : uniquely(raw), compressed(raw.size())
    {
        std::sort(uniquely.begin(), uniquely.end());
        uniquely.erase(std::unique(uniquely.begin(), uniquely.end()), uniquely.end());
        for(size_t i = 0; i != size(); ++i)
            compressed[i] = std::lower_bound(uniquely.begin(), uniquely.end(), raw[i]) - uniquely.begin();
    }

    size_t operator[](const size_t idx) const
    {
        assert(idx < size());
        return compressed[idx];
    }

    size_t size() const { return compressed.size(); }

    size_t count() const { return uniquely.size(); }

    T value_of(const size_t ord) const
    {
        assert(ord < count());
        return uniquely[ord];
    }

    size_t order_of(const T &val) const { return std::lower_bound(uniquely.begin(), uniquely.end(), val) - uniquely.begin(); }

    std::vector<size_t>::iterator begin() { return compressed.begin(); }
    std::vector<size_t>::iterator end() { return compressed.end(); }
    std::vector<size_t>::reverse_iterator rbegin() { return compressed.rbegin(); }
    std::vector<size_t>::reverse_iterator rend() { return compressed.rend(); }
};
#line 4 "test/library-checker/range_kth_smallest.test.cpp"
#include <cstdio>

int main()
{
    int n,q;
    scanf("%d%d",&n,&q);
    std::vector<int> a(n);
    for(int &e: a) scanf("%d",&e);
    coordinate_compression ccmp(a);
    int bsize=std::sqrt(ccmp.count())+1;
    std::vector<int> cnt(ccmp.count()),bcnt(bsize);
    auto add=[&](int i)
    {
        int now=ccmp[i];
        cnt[now]++;
        bcnt[now/bsize]++;
    };
    auto del=[&](int i)
    {
        int now=ccmp[i];
        cnt[now]--;
        bcnt[now/bsize]--;
    };
    Mo mo(n,add,del);
    std::vector<int> k(q),ans(q);
    for(int l,r,i=0; i<q; i++)
    {
        scanf("%d%d%d",&l,&r,&k[i]);
        mo.set(l,r);
    }
    for(int t=0; t<q; t++)
    {
        int qid=mo.process();
        for(int i=0,j=0,nk=k[qid]; i<bsize; i++,j+=bsize)
        {
            if(bcnt[i]>nk)
            {
                int h;
                for(h=j; nk>=cnt[h]; h++)
                {
                    nk-=cnt[h];
                }
                ans[qid]=ccmp.value_of(h);
                break;
            }
            else
            {
                nk-=bcnt[i];
            }
        }
    }
    for(int e: ans) printf("%d\n",e);
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

