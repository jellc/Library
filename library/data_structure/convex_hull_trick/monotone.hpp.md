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


# :warning: data_structure/convex_hull_trick/monotone.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#85c1e2c9a6a68b0da546cc8076233cc6">data_structure/convex_hull_trick</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/convex_hull_trick/monotone.hpp">View this file on GitHub</a>
    - Last commit date: 2020-07-27 21:53:08+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <cassert>
#include <vector>

template <class T = long long>
class lower_convex_monotone
{
    struct line
    {
        T slop, icpt;
        T eval(const T x) const { return slop * x + icpt; }
    };

    std::vector<line> lines;
    typename std::vector<line>::iterator lp, rp;

    void realloc()
    {
        std::vector<line> cpy((rp - lp) * 2);
        cpy.swap(lines);
        rp = copy(lp, rp, lines.begin());
        lp = lines.begin();
    }

public:
    lower_convex_monotone() : lines(2), lp(lines.begin()), rp(lp) {}

    bool empty() const { return lp == rp; }

    void clear() { rp = lp = lines.begin(); }

    void add(const T a, const T b)
    {
        while(rp - lp > 1)
        {
            auto [a1, b1] = *(rp - 1);
            auto [a2, b2] = *(rp - 2);
            if((b - b1) * (a2 - a) > (b - b2) * (a1 - a)) break;
            --rp;
        }
        if(rp == lp) rp = lp = lines.begin();
        if(rp == lines.end()) realloc();
        *rp++ = {a, b};
    }

    T get(const T x)
    {
        assert(!empty());
        while(rp - lp > 1 && lp->eval(x) > (lp + 1)->eval(x)) ++lp;
        return lp->eval(x);
    }
}; // class lower_convex_monotone

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "data_structure/convex_hull_trick/monotone.hpp"
#include <cassert>
#include <vector>

template <class T = long long>
class lower_convex_monotone
{
    struct line
    {
        T slop, icpt;
        T eval(const T x) const { return slop * x + icpt; }
    };

    std::vector<line> lines;
    typename std::vector<line>::iterator lp, rp;

    void realloc()
    {
        std::vector<line> cpy((rp - lp) * 2);
        cpy.swap(lines);
        rp = copy(lp, rp, lines.begin());
        lp = lines.begin();
    }

public:
    lower_convex_monotone() : lines(2), lp(lines.begin()), rp(lp) {}

    bool empty() const { return lp == rp; }

    void clear() { rp = lp = lines.begin(); }

    void add(const T a, const T b)
    {
        while(rp - lp > 1)
        {
            auto [a1, b1] = *(rp - 1);
            auto [a2, b2] = *(rp - 2);
            if((b - b1) * (a2 - a) > (b - b2) * (a1 - a)) break;
            --rp;
        }
        if(rp == lp) rp = lp = lines.begin();
        if(rp == lines.end()) realloc();
        *rp++ = {a, b};
    }

    T get(const T x)
    {
        assert(!empty());
        while(rp - lp > 1 && lp->eval(x) > (lp + 1)->eval(x)) ++lp;
        return lp->eval(x);
    }
}; // class lower_convex_monotone

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

