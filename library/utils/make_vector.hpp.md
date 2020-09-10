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


# :warning: utils/make_vector.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#2b3583e6e17721c54496bd04e57a0c15">utils</a>
* <a href="{{ site.github.repository_url }}/blob/master/utils/make_vector.hpp">View this file on GitHub</a>
    - Last commit date: 2020-09-11 03:22:24+09:00




## Required by

* :warning: <a href="../template.cpp.html">template.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <vector>
namespace workspace {
template <typename T, size_t N>
constexpr auto make_vector(size_t* sizes, T const& init = T()) {
  if constexpr (N) {
    return std::vector(*sizes, make_vector<T, N - 1>(std::next(sizes), init));
  } else {
    return std::vector(*sizes, init);
  }
}
template <typename T, size_t N>
constexpr auto make_vector(const size_t (&sizes)[N], T const& init = T()) {
  return make_vector<T, N - 1>((size_t*)sizes, init);
}
}  // namespace workspace

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "utils/make_vector.hpp"
#include <vector>
namespace workspace {
template <typename T, size_t N>
constexpr auto make_vector(size_t* sizes, T const& init = T()) {
  if constexpr (N) {
    return std::vector(*sizes, make_vector<T, N - 1>(std::next(sizes), init));
  } else {
    return std::vector(*sizes, init);
  }
}
template <typename T, size_t N>
constexpr auto make_vector(const size_t (&sizes)[N], T const& init = T()) {
  return make_vector<T, N - 1>((size_t*)sizes, init);
}
}  // namespace workspace

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

