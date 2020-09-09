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


# :x: algebra/convolution/subset.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#3cd9fd076f2d75c19d145e9eb33bfef8">algebra/convolution</a>
* <a href="{{ site.github.repository_url }}/blob/master/algebra/convolution/subset.hpp">View this file on GitHub</a>
    - Last commit date: 2020-08-06 06:09:12+09:00




## Verified with

* :x: <a href="../../../verify/test/library-checker/subset_convolution.test.cpp.html">test/library-checker/subset_convolution.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <cassert>
#include <vector>

template <class Ring>
std::vector<Ring> subset_convolute(const std::vector<Ring> &f, const std::vector<Ring> &g)
{
    assert(!f.empty()); assert(!g.empty());
    const size_t n = __builtin_ctz(std::min(f.size(), g.size()));
    std::vector ff(n + 1, std::vector<Ring>(1 << n)), gg(ff);
    ff[0] = f, gg[0] = g;
    for(size_t k = 0; k != n; ++k)
    {
        for(size_t i = k + 1; ~i; --i)
        {
            for(size_t s = 0; s != 1u << n; ++s)
            {
                if(s >> k & 1)
                {
                    if(i)
                    {
                        ff[i][s] = ff[i - 1][s];
                        gg[i][s] = gg[i - 1][s];
                    }
                    else
                    {
                        ff[i][s] = gg[i][s] = Ring{};
                    }
                    ff[i][s] += ff[i][s ^ 1 << k];
                    gg[i][s] += gg[i][s ^ 1 << k];
                }
            }
        }
    }
    for(size_t i = n; ~i; --i)
    {
        for(size_t s = 0; s != 1u << n; ++s)
        {
            ff[i][s] *= gg[0][s];
            for(size_t j = i; j; --j)
            {
                ff[i][s] += ff[i - j][s] * gg[j][s];
            }
        }
    }
    for(size_t k = n - 1; ~k; --k)
    {
        for(size_t s = 0; s != 1u << n; ++s)
        {
            if(~s >> k & 1)
            {
                for(size_t i = n; ~i; --i)
                {
                    ff[i][s ^ 1 << k] -= ff[i][s];
                    if(i) ff[i][s] = ff[i - 1][s];
                }
            }
        }
    }
    return ff[n];
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "algebra/convolution/subset.hpp"
#include <cassert>
#include <vector>

template <class Ring>
std::vector<Ring> subset_convolute(const std::vector<Ring> &f, const std::vector<Ring> &g)
{
    assert(!f.empty()); assert(!g.empty());
    const size_t n = __builtin_ctz(std::min(f.size(), g.size()));
    std::vector ff(n + 1, std::vector<Ring>(1 << n)), gg(ff);
    ff[0] = f, gg[0] = g;
    for(size_t k = 0; k != n; ++k)
    {
        for(size_t i = k + 1; ~i; --i)
        {
            for(size_t s = 0; s != 1u << n; ++s)
            {
                if(s >> k & 1)
                {
                    if(i)
                    {
                        ff[i][s] = ff[i - 1][s];
                        gg[i][s] = gg[i - 1][s];
                    }
                    else
                    {
                        ff[i][s] = gg[i][s] = Ring{};
                    }
                    ff[i][s] += ff[i][s ^ 1 << k];
                    gg[i][s] += gg[i][s ^ 1 << k];
                }
            }
        }
    }
    for(size_t i = n; ~i; --i)
    {
        for(size_t s = 0; s != 1u << n; ++s)
        {
            ff[i][s] *= gg[0][s];
            for(size_t j = i; j; --j)
            {
                ff[i][s] += ff[i - j][s] * gg[j][s];
            }
        }
    }
    for(size_t k = n - 1; ~k; --k)
    {
        for(size_t s = 0; s != 1u << n; ++s)
        {
            if(~s >> k & 1)
            {
                for(size_t i = n; ~i; --i)
                {
                    ff[i][s ^ 1 << k] -= ff[i][s];
                    if(i) ff[i][s] = ff[i - 1][s];
                }
            }
        }
    }
    return ff[n];
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

