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


# :warning: utils/Prime_factorizer.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#2b3583e6e17721c54496bd04e57a0c15">utils</a>
* <a href="{{ site.github.repository_url }}/blob/master/utils/Prime_factorizer.hpp">View this file on GitHub</a>
    - Last commit date: 2020-01-16 17:19:59+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef Prime_factorizer_hpp
#define Prime_factorizer_hpp

// calculate the least prime factor for positive integers less than N in compile time.
template <int N>
class prime_factorizer
{
    constexpr static int loop_limit = 1 << 17;
    int least[N], primes[N >> 3];
    int n = 0;

  public:
    constexpr prime_factorizer() : least{1}, primes{}, n{}
    {
        for(int i = 2; i < N; )
        {
            for(int j = 0; j < loop_limit && i < N; ++j, ++i)
            {
                if(!least[i]) primes[n++] = least[i] = i;
                int *p = primes;

                while(*p && *p <= least[i] && *p * i < N)
                {
                    for(int k = 0; k < loop_limit && *p && *p <= least[i] && *p * i < N; ++k, ++p)
                    {
                        least[*p * i] = *p;
                    }
                }
            }
        }
    }

    constexpr bool prime(int x) const { assert(0 <= x && x < N); return least[x] == x; }

    constexpr int least_prime_factor(int x) const { assert(0 < x && x < N); return least[x]; }
}; // class prime_factorizer

#endif // Prime_factorizer_hpp
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "utils/Prime_factorizer.hpp"



// calculate the least prime factor for positive integers less than N in compile time.
template <int N>
class prime_factorizer
{
    constexpr static int loop_limit = 1 << 17;
    int least[N], primes[N >> 3];
    int n = 0;

  public:
    constexpr prime_factorizer() : least{1}, primes{}, n{}
    {
        for(int i = 2; i < N; )
        {
            for(int j = 0; j < loop_limit && i < N; ++j, ++i)
            {
                if(!least[i]) primes[n++] = least[i] = i;
                int *p = primes;

                while(*p && *p <= least[i] && *p * i < N)
                {
                    for(int k = 0; k < loop_limit && *p && *p <= least[i] && *p * i < N; ++k, ++p)
                    {
                        least[*p * i] = *p;
                    }
                }
            }
        }
    }

    constexpr bool prime(int x) const { assert(0 <= x && x < N); return least[x] == x; }

    constexpr int least_prime_factor(int x) const { assert(0 < x && x < N); return least[x]; }
}; // class prime_factorizer



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

