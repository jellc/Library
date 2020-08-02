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


# :warning: string/Z-algorithm.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#b45cffe084dd3d20d928bee85e7b0f21">string</a>
* <a href="{{ site.github.repository_url }}/blob/master/string/Z-algorithm.hpp">View this file on GitHub</a>
    - Last commit date: 2020-01-15 19:00:20+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// #line 2 "Z_algorithm_hpp"
#ifndef Z_algorithm_hpp
#define Z_algorithm_hpp
#include <string>

template <class A = std::string>
class Z_algorithm
{
    const A key;
    const size_t len;
    std::vector<size_t> z;
    bool is_built;
  public:
    Z_algorithm(const A &_key) : key(_key), len(_key.size()), is_built(false) {}

    const std::vector<size_t> &build()
    {
        assert(len);
        is_built = true;
        z.assign(len, 0);
        for(size_t i{1}, j{0}; i != len; ++i)
        {
            if(z[i - j] + i < z[j] + j)
            {
                z[i] = z[i - j];
            }
            else
            {
                size_t k{z[j] + j > i ? z[j] + j - i : 0};
                while(k + i < len && key[k] == key[k + i]) ++k;
                z[i] = k;
                j = i;
            }
        }
        z.front() = len;
        return z;
    }

    size_t size() const { return len; }
    size_t operator[](size_t i) const { return build(), z[i]; }

    std::vector<size_t> pattern_search(const A &str) const
    {
        A tmp(key);
        tmp.insert(end(tmp), begin(str), end(str));
        Z_algorithm other(tmp);
        const auto &nz(other.build());
        std::vector<size_t> res(nz.begin() + len, nz.end());
        for(size_t &x : res) if(x > len) x = len;
        return res;
    }
};

#endif

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "string/Z-algorithm.hpp"
// #line 2 "Z_algorithm_hpp"
#ifndef Z_algorithm_hpp
#define Z_algorithm_hpp
#include <string>

template <class A = std::string>
class Z_algorithm
{
    const A key;
    const size_t len;
    std::vector<size_t> z;
    bool is_built;
  public:
    Z_algorithm(const A &_key) : key(_key), len(_key.size()), is_built(false) {}

    const std::vector<size_t> &build()
    {
        assert(len);
        is_built = true;
        z.assign(len, 0);
        for(size_t i{1}, j{0}; i != len; ++i)
        {
            if(z[i - j] + i < z[j] + j)
            {
                z[i] = z[i - j];
            }
            else
            {
                size_t k{z[j] + j > i ? z[j] + j - i : 0};
                while(k + i < len && key[k] == key[k + i]) ++k;
                z[i] = k;
                j = i;
            }
        }
        z.front() = len;
        return z;
    }

    size_t size() const { return len; }
    size_t operator[](size_t i) const { return build(), z[i]; }

    std::vector<size_t> pattern_search(const A &str) const
    {
        A tmp(key);
        tmp.insert(end(tmp), begin(str), end(str));
        Z_algorithm other(tmp);
        const auto &nz(other.build());
        std::vector<size_t> res(nz.begin() + len, nz.end());
        for(size_t &x : res) if(x > len) x = len;
        return res;
    }
};

#endif

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

