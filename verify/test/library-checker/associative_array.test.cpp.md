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
    - Last commit date: 2020-08-25 21:23:23+09:00


* see: <a href="https://judge.yosupo.jp/problem/associative_array">https://judge.yosupo.jp/problem/associative_array</a>


## Depends on

* :x: <a href="../../../library/utils/hash.hpp.html">utils/hash.hpp</a>
* :x: <a href="../../../library/utils/sfinae.hpp.html">utils/sfinae.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/associative_array"
#include "utils/hash.hpp"

int main()
{
    int q; scanf("%d",&q);
    workspace::hashmap<long long, long long> a;
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
#line 2 "utils/hash.hpp"
#include <ext/pb_ds/assoc_container.hpp>
#include <functional>
#include <random>
#line 2 "utils/sfinae.hpp"
#include <type_traits>
template <class type, template <class> class trait>
using enable_if_trait_type = typename std::enable_if<trait<type>::value>::type;
template <class Container>
using element_type = std::remove_const_t<std::remove_reference_t<decltype(*std::begin(std::declval<Container&>()))>>;
#line 6 "utils/hash.hpp"
namespace workspace {
template <class T, class = void>
struct hash : std::hash<T> {};
template <class int_type>
struct hash<int_type, enable_if_trait_type<int_type, std::is_integral>>
{
    const uint64_t seed[3];
public:
    template <class URBG = std::random_device> hash(URBG urbg = URBG()) : seed{urbg(), urbg(), urbg()} {}
    size_t operator()(const uint64_t &x) const { return (x * seed[0] + (x >> 32) * seed[1] + seed[2]) >> 32; }
};
template <class T1, class T2>
class hash<std::pair<T1, T2>>
{
    hash<T1> gen1; hash<T2> gen2;
public:
    size_t operator()(const std::pair<T1, T2> &pair) const
    {
        size_t seed = gen1(pair.first);
        return seed ^= gen2(pair.second) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
};
template <class... T>
class hash<std::tuple<T...>>
{
    template <class Key>
    static size_t join(const size_t &seed, const Key &key)
    {
        static hash<Key> gen;
        return seed ^ (gen(key) + 0x9e3779b9 + (seed << 6) + (seed >> 2));
    }
    template <class Tuple, size_t index = std::tuple_size<Tuple>::value - 1> struct tuple_hash { static size_t apply(const Tuple &t) { return join(tuple_hash<Tuple, index - 1>::apply(t), std::get<index>(t)); } };
    template <class Tuple> struct tuple_hash<Tuple, size_t(-1)> { static size_t apply(const Tuple &t) { return 0; } };
public:
    size_t operator()(const std::tuple<T...> &t) const { return tuple_hash<std::tuple<T...>>::apply(t); }
};
template <class Key, class Mapped>
struct hash_map : public __gnu_pbds::gp_hash_table<Key, Mapped, hash<Key>>
{
    using base = __gnu_pbds::gp_hash_table<Key, Mapped, hash<Key>>;
    size_t count(const Key &key) const { return base::find(key) != base::end(); }
    template <class... Args> auto emplace(Args&&... args) { return base::insert(typename base::value_type(args...)); }
};
template <class Key> using hash_set = hash_map<Key, __gnu_pbds::null_type>;
} // namespace workspace
#line 3 "test/library-checker/associative_array.test.cpp"

int main()
{
    int q; scanf("%d",&q);
    workspace::hashmap<long long, long long> a;
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

