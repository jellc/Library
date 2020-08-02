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


# :warning: string/Manacher.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#b45cffe084dd3d20d928bee85e7b0f21">string</a>
* <a href="{{ site.github.repository_url }}/blob/master/string/Manacher.hpp">View this file on GitHub</a>
    - Last commit date: 2020-01-15 19:03:28+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// #line 2 "Manacher.hpp"
#ifndef Manacher_hpp
#define Manacher_hpp
#include <iostream>
#include <string>
#include <vector>

template <class str_type = std::string>
class Manacher
{
    const size_t len;
    std::vector<size_t> rad;
    friend std::ostream &operator<<(std::ostream &os, const Manacher &mana)
    {
        bool is_front = true;
        for(size_t r : mana.rad)
        {
            if(is_front) is_front = false;
            else os << " ";
            os << r;
        }
        return os;
    }
  public:
    Manacher(const str_type &str) : len(str.size()), rad(str.size())
    {
        for(size_t i = 0, c = 0; i != len; ++i)
        {
            int l = c * 2 - i;
            if(l >= 0 && c + rad[c] > i + rad[l]) rad[i] = rad[l];
            else
            {
                size_t j = c + rad[c] - i;
                while(i >= j && i + j != len && str[i - j] == str[i + j]) ++j;
                rad[c = i] = j;
            }
        }
    }
    size_t size() const { return rad.size(); }
    size_t operator[](size_t i) const { return rad[i]; }
}; // class Manacher

#endif // Manacher_hpp

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "string/Manacher.hpp"
// #line 2 "Manacher.hpp"
#ifndef Manacher_hpp
#define Manacher_hpp
#include <iostream>
#include <string>
#include <vector>

template <class str_type = std::string>
class Manacher
{
    const size_t len;
    std::vector<size_t> rad;
    friend std::ostream &operator<<(std::ostream &os, const Manacher &mana)
    {
        bool is_front = true;
        for(size_t r : mana.rad)
        {
            if(is_front) is_front = false;
            else os << " ";
            os << r;
        }
        return os;
    }
  public:
    Manacher(const str_type &str) : len(str.size()), rad(str.size())
    {
        for(size_t i = 0, c = 0; i != len; ++i)
        {
            int l = c * 2 - i;
            if(l >= 0 && c + rad[c] > i + rad[l]) rad[i] = rad[l];
            else
            {
                size_t j = c + rad[c] - i;
                while(i >= j && i + j != len && str[i - j] == str[i + j]) ++j;
                rad[c = i] = j;
            }
        }
    }
    size_t size() const { return rad.size(); }
    size_t operator[](size_t i) const { return rad[i]; }
}; // class Manacher

#endif // Manacher_hpp

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

