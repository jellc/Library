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


# :x: test/library-checker/associative_array.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#8a40f8ed03f4cdb6c2fe0a2d4731a143">test/library-checker</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/library-checker/associative_array.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-08-25 00:15:06+09:00


* see: <a href="https://judge.yosupo.jp/problem/associative_array">https://judge.yosupo.jp/problem/associative_array</a>


## Depends on

* :x: <a href="../../../library/utils/sfinae.hpp.html">utils/sfinae.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/associative_array"
// #include "utils/hash.hpp"
#include "utils/sfinae.hpp"
#include <random>
#include <functional>
#include <ext/pb_ds/assoc_container.hpp>

namespace workspace {
template <class T> struct hash : std::hash<T> {};
struct std_hash_combine
{
    template <class Key>
    size_t operator()(size_t seed, const Key &key) const { return seed ^ (std::hash<Key>()(key) + 0x9e3779b9 + (seed << 6) + (seed >> 2)); }
};
template <class T1, class T2>
class hash<std::pair<T1, T2>>
{
    std_hash_combine comb;
public:
    size_t operator()(const std::pair<T1, T2> &pair) const { return comb(comb(0, pair.first), pair.second); }
};
template <class... T>
class hash<std::tuple<T...>>
{
    template <class Tuple, size_t index = std::tuple_size<Tuple>::value - 1> struct tuple_hasher { template <class Comb> static size_t apply(size_t seed, const Tuple &t, Comb comb = Comb()) { return comb(tuple_hasher<Tuple, index - 1>::apply(seed, t, comb), std::get<index>(t)); } };
    template <class Tuple> struct tuple_hasher<Tuple, 0> { template <class Comb> static size_t apply(size_t seed, const Tuple &t, Comb comb = Comb()) { return comb(seed, std::get<0>(t)); } };
    std_hash_combine comb;
public:
    size_t operator()(const std::tuple<T...> &t) const { return tuple_hasher<std::tuple<T...>>::apply(0, t, comb); }
};
template <class Key, class Mapped>
struct hashmap : public __gnu_pbds::gp_hash_table<Key, Mapped, hash<Key>>
{
    using base = __gnu_pbds::gp_hash_table<Key, Mapped, hash<Key>>;
    size_t count(const Key &key) const { return base::find(key) != base::end(); }
    template <class... Args> auto emplace(Args&&... args) { return base::insert(typename base::value_type(args...)); }
};
template <class Key> using hashset = hashmap<Key, __gnu_pbds::null_type>;
template <class int_type>
struct hash<enable_if_trait<int_type, std::is_integral>>
{
    const uint64_t seed[2], offset;
public:
    hash() : seed{std::random_device{}(), std::random_device{}()}, offset{std::random_device{}()} {}
    size_t operator()(const uint64_t &x) const { return (offset + x * seed[0] + (x >> 32) * seed[1]) >> 32; }
};
}

int main()
{
    int q; scanf("%d",&q);
    __gnu_pbds::gp_hash_table<long long, long long, workspace::hash<long long>> a;
    while(q--)
    {
        int t; long long k,v; scanf("%d%lld",&t,&k);
        if(t) printf("%lld\n",a[k]);
        else scanf("%lld",&v),a[k]=v;
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/library-checker/associative_array.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/associative_array"
// #include "utils/hash.hpp"
#line 2 "utils/sfinae.hpp"
#include <type_traits>
template <class type, template <class> class trait, typename = std::enable_if_t<trait<type>::value, void>>
using enable_if_trait = type;
#line 4 "test/library-checker/associative_array.test.cpp"
#include <random>
#include <functional>
#include <ext/pb_ds/assoc_container.hpp>

namespace workspace {
template <class T> struct hash : std::hash<T> {};
struct std_hash_combine
{
    template <class Key>
    size_t operator()(size_t seed, const Key &key) const { return seed ^ (std::hash<Key>()(key) + 0x9e3779b9 + (seed << 6) + (seed >> 2)); }
};
template <class T1, class T2>
class hash<std::pair<T1, T2>>
{
    std_hash_combine comb;
public:
    size_t operator()(const std::pair<T1, T2> &pair) const { return comb(comb(0, pair.first), pair.second); }
};
template <class... T>
class hash<std::tuple<T...>>
{
    template <class Tuple, size_t index = std::tuple_size<Tuple>::value - 1> struct tuple_hasher { template <class Comb> static size_t apply(size_t seed, const Tuple &t, Comb comb = Comb()) { return comb(tuple_hasher<Tuple, index - 1>::apply(seed, t, comb), std::get<index>(t)); } };
    template <class Tuple> struct tuple_hasher<Tuple, 0> { template <class Comb> static size_t apply(size_t seed, const Tuple &t, Comb comb = Comb()) { return comb(seed, std::get<0>(t)); } };
    std_hash_combine comb;
public:
    size_t operator()(const std::tuple<T...> &t) const { return tuple_hasher<std::tuple<T...>>::apply(0, t, comb); }
};
template <class Key, class Mapped>
struct hashmap : public __gnu_pbds::gp_hash_table<Key, Mapped, hash<Key>>
{
    using base = __gnu_pbds::gp_hash_table<Key, Mapped, hash<Key>>;
    size_t count(const Key &key) const { return base::find(key) != base::end(); }
    template <class... Args> auto emplace(Args&&... args) { return base::insert(typename base::value_type(args...)); }
};
template <class Key> using hashset = hashmap<Key, __gnu_pbds::null_type>;
template <class int_type>
struct hash<enable_if_trait<int_type, std::is_integral>>
{
    const uint64_t seed[2], offset;
public:
    hash() : seed{std::random_device{}(), std::random_device{}()}, offset{std::random_device{}()} {}
    size_t operator()(const uint64_t &x) const { return (offset + x * seed[0] + (x >> 32) * seed[1]) >> 32; }
};
}

int main()
{
    int q; scanf("%d",&q);
    __gnu_pbds::gp_hash_table<long long, long long, workspace::hash<long long>> a;
    while(q--)
    {
        int t; long long k,v; scanf("%d%lld",&t,&k);
        if(t) printf("%lld\n",a[k]);
        else scanf("%lld",&v),a[k]=v;
    }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

