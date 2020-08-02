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


# :warning: utils/random_number_generator.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#2b3583e6e17721c54496bd04e57a0c15">utils</a>
* <a href="{{ site.github.repository_url }}/blob/master/utils/random_number_generator.hpp">View this file on GitHub</a>
    - Last commit date: 2020-06-29 00:17:37+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <random>

template <typename num_t>
class random_number_generator
{
    template <bool is_int, class = void>
    struct unif_t
    {
        std::uniform_int_distribution<num_t> unif;
        unif_t(num_t lower, num_t upper) : unif(lower, upper) {}
        num_t operator()(std::mt19937 &engine) { return unif(engine); }
    };
    template <class void_t>
    struct unif_t<false, void_t>
    {
        std::uniform_real_distribution<num_t> unif;
        unif_t(num_t lower, num_t upper) : unif(lower, upper) {}
        num_t operator()(std::mt19937 &engine) { return unif(engine); }
    };
    unif_t<std::is_integral<num_t>::value> unif;
    std::mt19937 engine;
  public:
    // generate random number in [lower, upper].
    random_number_generator(num_t lower = std::numeric_limits<num_t>::min(), num_t upper = std::numeric_limits<num_t>::max()) : unif(lower, upper), engine(std::random_device{}()) {}
    num_t operator()() { return unif(engine); }
}; // class random_number_generator 

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "utils/random_number_generator.hpp"
#include <random>

template <typename num_t>
class random_number_generator
{
    template <bool is_int, class = void>
    struct unif_t
    {
        std::uniform_int_distribution<num_t> unif;
        unif_t(num_t lower, num_t upper) : unif(lower, upper) {}
        num_t operator()(std::mt19937 &engine) { return unif(engine); }
    };
    template <class void_t>
    struct unif_t<false, void_t>
    {
        std::uniform_real_distribution<num_t> unif;
        unif_t(num_t lower, num_t upper) : unif(lower, upper) {}
        num_t operator()(std::mt19937 &engine) { return unif(engine); }
    };
    unif_t<std::is_integral<num_t>::value> unif;
    std::mt19937 engine;
  public:
    // generate random number in [lower, upper].
    random_number_generator(num_t lower = std::numeric_limits<num_t>::min(), num_t upper = std::numeric_limits<num_t>::max()) : unif(lower, upper), engine(std::random_device{}()) {}
    num_t operator()() { return unif(engine); }
}; // class random_number_generator 

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

