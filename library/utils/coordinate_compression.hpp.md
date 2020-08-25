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


# :heavy_check_mark: utils/coordinate_compression.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#2b3583e6e17721c54496bd04e57a0c15">utils</a>
* <a href="{{ site.github.repository_url }}/blob/master/utils/coordinate_compression.hpp">View this file on GitHub</a>
    - Last commit date: 2020-08-03 02:03:38+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/library-checker/range_kth_smallest.test.cpp.html">test/library-checker/range_kth_smallest.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/library-checker/static_range_inversions_query.test.cpp.html">test/library-checker/static_range_inversions_query.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <algorithm>
#include <cassert>
#include <vector>

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
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "utils/coordinate_compression.hpp"
#include <algorithm>
#include <cassert>
#include <vector>

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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

