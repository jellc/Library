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


# :x: test/library-checker/static_range_inversions_query.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#8a40f8ed03f4cdb6c2fe0a2d4731a143">test/library-checker</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/library-checker/static_range_inversions_query.test.cpp">View this file on GitHub</a>
    - Last commit date: 1970-01-01 00:00:00+00:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/static_range_inversions_query"
#include "../../data_structure/Mo.hpp"
#include "../../utils/coordinate_compression.hpp"
#include "../../data_structure/segment_tree/segment_tree.hpp"
#include <cstdio>
using i64=int64_t;

int main()
{
    int n,q;
    scanf("%d%d",&n,&q);
    std::vector<int> a(n);
    for(int &x: a) scanf("%d",&x);
    coordinate_compression ccmp(a);
    std::vector<int> cnt(ccmp.count());
    segment_tree<int> seg(n);
    int nl=0,nr=0;
    i64 invs=0;
    auto add=[&](int i)
    {
        int nv=ccmp[i];
        if(i<nl) // left end
        {
            invs+=seg.fold(0,nv);
            nl--;
        }
        else // right end
        {
            invs+=seg.fold(nv+1,n);
            nr++;
        }
        seg[nv]++;
    };
    auto del=[&](int i)
    {
        int nv=ccmp[i];
        if(i==nl) // left end
        {
            invs-=seg.fold(0,nv);
            nl++;
        }
        else // right end
        {
            assert(nr==i+1);
            invs-=seg.fold(nv+1,n);
            nr--;
        }
        seg[nv]--;
    };
    Mo mo(n,add,del);
    for(int i=0; i<q; i++)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        mo.set(l,r);
    }
    std::vector<i64> ans(q);
    for(int i=0; i<q; i++)
    {
        int id=mo.process();
        ans[id]=invs;
    }
    for(i64 x: ans) printf("%lld\n",x);
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
Traceback (most recent call last):
  File "/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/docs.py", line 349, in write_contents
    bundled_code = language.bundle(self.file_class.file_path, basedir=pathlib.Path.cwd())
  File "/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py", line 185, in bundle
    bundler.update(path)
  File "/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 399, in update
    self.update(self._resolve(pathlib.Path(included), included_from=path))
  File "/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 258, in _resolve
    raise BundleErrorAt(path, -1, "no such header")
onlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: ../../data_structure/segment_tree/segment_tree.hpp: line -1: no such header

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

