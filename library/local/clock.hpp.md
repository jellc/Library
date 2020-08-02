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


# :warning: local/clock.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f5ddaf0ca7929578b408c909429f68f2">local</a>
* <a href="{{ site.github.repository_url }}/blob/master/local/clock.hpp">View this file on GitHub</a>
    - Last commit date: 2020-02-10 09:13:07+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <chrono>
#include <iostream>
#include <string>

class
{
    std::chrono::system_clock::time_point built_pt, last_pt;
    int built_ln, last_ln;
    std::string built_func, last_func;
    bool is_built = false;

public:
    void build(int crt_ln, const std::string &crt_func)
    {
        is_built = true, last_pt = built_pt = std::chrono::system_clock::now(), last_ln = built_ln = crt_ln, last_func = built_func = crt_func;
    }

    void set(int crt_ln, const std::string &crt_func)
    {
        if(is_built) last_pt = std::chrono::system_clock::now(), last_ln = crt_ln, last_func = crt_func;
        else std::cerr << "[ " << crt_ln << " : " << crt_func << " ] " << "myclock_t::set failed (yet to be built!)\n";
    }

    void get(int crt_ln, const std::string &crt_func)
    {
        if(is_built)
        {
            std::chrono::system_clock::time_point crt_pt(std::chrono::system_clock::now());
            long long diff = std::chrono::duration_cast<std::chrono::milliseconds>(crt_pt - last_pt).count();
            std::cerr << diff << " ms elapsed from" << " [ " << last_ln << " : " << last_func << " ]";
            if(last_ln == built_ln) std::cerr << " (when built)";
            std::cerr << " to" << " [ " << crt_ln << " : " << crt_func << " ]" << "\n";
            last_pt = built_pt, last_ln = built_ln, last_func = built_func;
        }
        else
        {
            std::cerr << "[ " << crt_ln << " : " << crt_func << " ] " << "myclock_t::get failed (yet to be built!)\n";
        }
    }
} myclock; // unnamed class

#define build_clock() myclock.build(__LINE__, __func__)
#define set_clock() myclock.set(__LINE__, __func__)
#define get_clock() myclock.get(__LINE__, __func__)

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "local/clock.hpp"
#include <chrono>
#include <iostream>
#include <string>

class
{
    std::chrono::system_clock::time_point built_pt, last_pt;
    int built_ln, last_ln;
    std::string built_func, last_func;
    bool is_built = false;

public:
    void build(int crt_ln, const std::string &crt_func)
    {
        is_built = true, last_pt = built_pt = std::chrono::system_clock::now(), last_ln = built_ln = crt_ln, last_func = built_func = crt_func;
    }

    void set(int crt_ln, const std::string &crt_func)
    {
        if(is_built) last_pt = std::chrono::system_clock::now(), last_ln = crt_ln, last_func = crt_func;
        else std::cerr << "[ " << crt_ln << " : " << crt_func << " ] " << "myclock_t::set failed (yet to be built!)\n";
    }

    void get(int crt_ln, const std::string &crt_func)
    {
        if(is_built)
        {
            std::chrono::system_clock::time_point crt_pt(std::chrono::system_clock::now());
            long long diff = std::chrono::duration_cast<std::chrono::milliseconds>(crt_pt - last_pt).count();
            std::cerr << diff << " ms elapsed from" << " [ " << last_ln << " : " << last_func << " ]";
            if(last_ln == built_ln) std::cerr << " (when built)";
            std::cerr << " to" << " [ " << crt_ln << " : " << crt_func << " ]" << "\n";
            last_pt = built_pt, last_ln = built_ln, last_func = built_func;
        }
        else
        {
            std::cerr << "[ " << crt_ln << " : " << crt_func << " ] " << "myclock_t::get failed (yet to be built!)\n";
        }
    }
} myclock; // unnamed class

#define build_clock() myclock.build(__LINE__, __func__)
#define set_clock() myclock.set(__LINE__, __func__)
#define get_clock() myclock.get(__LINE__, __func__)

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

