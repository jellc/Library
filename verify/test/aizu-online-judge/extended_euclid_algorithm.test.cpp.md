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


# :heavy_check_mark: test/aizu-online-judge/extended_euclid_algorithm.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#8067ffd948dddbb51ecccf5f861740e7">test/aizu-online-judge</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/aizu-online-judge/extended_euclid_algorithm.test.cpp">View this file on GitHub</a>
    - Last commit date: 1970-01-01 00:00:00+00:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/1/NTL_1_E">https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/1/NTL_1_E</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/number_theory/ext_gcd.hpp.html">number_theory/ext_gcd.hpp</a>
* :heavy_check_mark: <a href="../../../library/utils/iostream_overload.hpp.html">utils/iostream_overload.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/1/NTL_1_E"
#include "number_theory/ext_gcd.hpp"
#include "utils/iostream_overload.hpp"

int main()
{
    int a,b;
    std::cin>>a>>b;
    auto [x,y]=ext_gcd(a,b);
    if(x>0) x-=b,y+=a;
    if((long long)(y-x)*2>a+b) x+=b,y-=a;
    std::cout<<x<<" "<<y<<"\n";
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aizu-online-judge/extended_euclid_algorithm.test.cpp"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/1/NTL_1_E"
#line 2 "number_theory/ext_gcd.hpp"
#include <tuple>
template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
constexpr std::pair<int_type, int_type> ext_gcd(int_type a, int_type b)
{
    bool neg_a = a < 0, neg_b = b < 0;
    int_type p{1}, q{}, r{}, s{1}, t{};
    while(b)
    {
        r ^= p ^= r ^= p -= (t = a / b) * r;
        s ^= q ^= s ^= q -= t * s;
        b ^= a ^= b ^= a %= b;
    }
    return {neg_a ? -p : p, neg_b ? -q : q};
}
#line 2 "utils/iostream_overload.hpp"
#include <iostream>
namespace std
{
    template <class T, class U> istream &operator>>(istream &is, pair<T, U> &p) { return is >> p.first >> p.second; }
    template <class T, class U> ostream &operator<<(ostream &os, const pair<T, U> &p) { return os << p.first << ' ' << p.second; }
    template <class tuple_t, size_t index> struct tuple_is { static istream &apply(istream &is, tuple_t &t) { tuple_is<tuple_t, index - 1>::apply(is, t); return is >> get<index>(t); } };
    template <class tuple_t> struct tuple_is<tuple_t, SIZE_MAX> { static istream &apply(istream &is, tuple_t &t) { return is; } };
    template <class... T> istream &operator>>(istream &is, tuple<T...> &t) { return tuple_is<tuple<T...>, tuple_size<tuple<T...>>::value - 1>::apply(is, t); }
    template <class tuple_t, size_t index> struct tuple_os { static ostream &apply(ostream &os, const tuple_t &t) { tuple_os<tuple_t, index - 1>::apply(os, t); return os << ' ' << get<index>(t); } };
    template <class tuple_t> struct tuple_os<tuple_t, 0> { static ostream &apply(ostream &os, const tuple_t &t) { return os << get<0>(t); } };
    template <class tuple_t> struct tuple_os<tuple_t, SIZE_MAX> { static ostream &apply(ostream &os, const tuple_t &t) { return os; } };
    template <class... T> ostream &operator<<(ostream &os, const tuple<T...> &t) { return tuple_os<tuple<T...>, tuple_size<tuple<T...>>::value - 1>::apply(os, t); }
    template <class Container, typename Value = typename Container::value_type, enable_if_t<!is_same<decay_t<Container>, string>::value, nullptr_t> = nullptr>
    istream& operator>>(istream& is, Container &cont) { for(auto&& e : cont) is >> e; return is; }
    template <class Container, typename Value = typename Container::value_type, enable_if_t<!is_same<decay_t<Container>, string>::value, nullptr_t> = nullptr>
    ostream& operator<<(ostream& os, const Container &cont) { bool flag = 1; for(auto&& e : cont) flag ? flag = 0 : (os << ' ', 0), os << e; return os; }
} // namespace std
#line 4 "test/aizu-online-judge/extended_euclid_algorithm.test.cpp"

int main()
{
    int a,b;
    std::cin>>a>>b;
    auto [x,y]=ext_gcd(a,b);
    if(x>0) x-=b,y+=a;
    if((long long)(y-x)*2>a+b) x+=b,y-=a;
    std::cout<<x<<" "<<y<<"\n";
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

