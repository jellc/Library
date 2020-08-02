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


# :warning: local/dump.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f5ddaf0ca7929578b408c909429f68f2">local</a>
* <a href="{{ site.github.repository_url }}/blob/master/local/dump.hpp">View this file on GitHub</a>
    - Last commit date: 2020-02-10 09:12:50+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <iostream>

#define dump(...) std::cerr << "[ " << __LINE__ << " : " << __FUNCTION__ << " ]\n", dump_func(#__VA_ARGS__, __VA_ARGS__)

template <class T> void dump_func(const char *ptr, const T &x)
{
    std::cerr << '\t';
    for(char c = *ptr; c != '\0'; c = *++ptr) if(c != ' ' && c != '\t') std::cerr << c;
    std::cerr << " : " << x << '\n';
}

template <class T, class... types> void dump_func(const char *ptr, const T &x, types... rest)
{
    std::cerr << '\t';
    for(char c = *ptr; c != ','; c = *++ptr) if(c != ' ' && c != '\t') std::cerr << c;
    std::cerr << " : " << x << ",\n"; dump_func(++ptr, rest...);
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "local/dump.hpp"
#include <iostream>

#define dump(...) std::cerr << "[ " << __LINE__ << " : " << __FUNCTION__ << " ]\n", dump_func(#__VA_ARGS__, __VA_ARGS__)

template <class T> void dump_func(const char *ptr, const T &x)
{
    std::cerr << '\t';
    for(char c = *ptr; c != '\0'; c = *++ptr) if(c != ' ' && c != '\t') std::cerr << c;
    std::cerr << " : " << x << '\n';
}

template <class T, class... types> void dump_func(const char *ptr, const T &x, types... rest)
{
    std::cerr << '\t';
    for(char c = *ptr; c != ','; c = *++ptr) if(c != ' ' && c != '\t') std::cerr << c;
    std::cerr << " : " << x << ",\n"; dump_func(++ptr, rest...);
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

