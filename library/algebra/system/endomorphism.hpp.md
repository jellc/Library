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


# :warning: algebra/system/endomorphism.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#c95c870e4534787ab6d160f2417ab752">algebra/system</a>
* <a href="{{ site.github.repository_url }}/blob/master/algebra/system/endomorphism.hpp">View this file on GitHub</a>
    - Last commit date: 2020-07-08 02:50:45+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
struct endo
{
    // compose.
    void operator*=(const endo& rhs);

    // apply self to an element of X.
    template <class X>
    void apply(X &rhs) const;
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "algebra/system/endomorphism.hpp"
struct endo
{
    // compose.
    void operator*=(const endo& rhs);

    // apply self to an element of X.
    template <class X>
    void apply(X &rhs) const;
};

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

