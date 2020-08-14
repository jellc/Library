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


# :warning: utils/binary_search.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#2b3583e6e17721c54496bd04e57a0c15">utils</a>
* <a href="{{ site.github.repository_url }}/blob/master/utils/binary_search.hpp">View this file on GitHub</a>
    - Last commit date: 2020-08-14 18:02:25+09:00




## Required by

* :warning: <a href="../template.cpp.html">template.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <cassert>
#include <cstdint>
#include <cmath>
namespace workspace {
// binary search on discrete range.
template <class iter_type, class pred_type, std::enable_if_t<std::is_convertible_v<std::invoke_result_t<pred_type, iter_type>, bool>, nullptr_t> = nullptr>
iter_type binary_search(iter_type ok, iter_type ng, pred_type pred)
{
    assert(ok != ng);
    intmax_t dist(ng - ok);
    while(std::abs(dist) > 1)
    {
        iter_type mid(ok + dist / 2);
        if(pred(mid)) ok = mid, dist -= dist / 2;
        else ng = mid, dist /= 2;
    }
    return ok;
}
// binary search on real numbers.
template <class real_type, class pred_type, std::enable_if_t<std::is_convertible_v<std::invoke_result_t<pred_type, real_type>, bool>, nullptr_t> = nullptr>
real_type binary_search(real_type ok, real_type ng, const real_type eps, pred_type pred)
{
    assert(ok != ng);
    while(std::abs(ok - ng) > eps)
    {
        real_type mid{(ok + ng) / 2};
        (pred(mid) ? ok : ng) = mid;
    }
    return ok;
}
} // namespace workspace

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "utils/binary_search.hpp"
#include <cassert>
#include <cstdint>
#include <cmath>
namespace workspace {
// binary search on discrete range.
template <class iter_type, class pred_type, std::enable_if_t<std::is_convertible_v<std::invoke_result_t<pred_type, iter_type>, bool>, nullptr_t> = nullptr>
iter_type binary_search(iter_type ok, iter_type ng, pred_type pred)
{
    assert(ok != ng);
    intmax_t dist(ng - ok);
    while(std::abs(dist) > 1)
    {
        iter_type mid(ok + dist / 2);
        if(pred(mid)) ok = mid, dist -= dist / 2;
        else ng = mid, dist /= 2;
    }
    return ok;
}
// binary search on real numbers.
template <class real_type, class pred_type, std::enable_if_t<std::is_convertible_v<std::invoke_result_t<pred_type, real_type>, bool>, nullptr_t> = nullptr>
real_type binary_search(real_type ok, real_type ng, const real_type eps, pred_type pred)
{
    assert(ok != ng);
    while(std::abs(ok - ng) > eps)
    {
        real_type mid{(ok + ng) / 2};
        (pred(mid) ? ok : ng) = mid;
    }
    return ok;
}
} // namespace workspace

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

