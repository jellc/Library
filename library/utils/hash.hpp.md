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


# :heavy_check_mark: utils/hash.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#2b3583e6e17721c54496bd04e57a0c15">utils</a>
* <a href="{{ site.github.repository_url }}/blob/master/utils/hash.hpp">View this file on GitHub</a>
    - Last commit date: 2020-09-09 04:49:26+09:00




## Depends on

* :heavy_check_mark: <a href="sfinae.hpp.html">utils/sfinae.hpp</a>


## Required by

* :warning: <a href="../template.cpp.html">template.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/library-checker/associative_array.test.cpp.html">test/library-checker/associative_array.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <ext/pb_ds/assoc_container.hpp>
#include <functional>
#include <random>
#include <unordered_set>
#include "sfinae.hpp"
namespace workspace {
template <class T, class = void>
struct hash : std::hash<T> {};
template <class Unique_bits_type>
struct hash<Unique_bits_type, enable_if_trait_type<Unique_bits_type, std::has_unique_object_representations>>
{
    size_t operator()(uint64_t x) const
    {
        static const uint64_t m = std::random_device{}();
        x ^= x >> 23;
        // x *= 0x2127599bf4325c37ULL;
        x ^= m;
        x ^= x >> 47;
        return x - (x >> 32);
    }
};
template <class Key>
size_t hash_combine(const size_t &seed, const Key &key)
{
    return seed ^ (hash<Key>()(key) + 0x9e3779b9 /* + (seed << 6) + (seed >> 2) */ );
}
template <class T1, class T2>
struct hash<std::pair<T1, T2>>
{
    size_t operator()(const std::pair<T1, T2> &pair) const
    {
        return hash_combine(hash<T1>()(pair.first), pair.second);
    }
};
template <class... T>
class hash<std::tuple<T...>>
{
    template <class Tuple, size_t index = std::tuple_size<Tuple>::value - 1> struct tuple_hash { static uint64_t apply(const Tuple &t) { return hash_combine(tuple_hash<Tuple, index - 1>::apply(t), std::get<index>(t)); } };
    template <class Tuple> struct tuple_hash<Tuple, size_t(-1)> { static uint64_t apply(const Tuple &t) { return 0; } };
public:
    uint64_t operator()(const std::tuple<T...> &t) const { return tuple_hash<std::tuple<T...>>::apply(t); }
};
template <class hash_table>
struct hash_table_wrapper : hash_table
{
    using key_type = typename hash_table::key_type;
    size_t count(const key_type &key) const { return hash_table::find(key) != hash_table::end(); }
    template <class... Args> auto emplace(Args&&... args) { return hash_table::insert(typename hash_table::value_type(args...)); }
};
template <class Key, class Mapped = __gnu_pbds::null_type>
using cc_hash_table = hash_table_wrapper<__gnu_pbds::cc_hash_table<Key, Mapped, hash<Key>>>;
template <class Key, class Mapped = __gnu_pbds::null_type>
using gp_hash_table = hash_table_wrapper<__gnu_pbds::gp_hash_table<Key, Mapped, hash<Key>>>;
template <class Key, class Mapped>
using unordered_map = std::unordered_map<Key, Mapped, hash<Key>>;
template <class Key>
using unordered_set = std::unordered_set<Key, hash<Key>>;
} // namespace workspace

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "utils/hash.hpp"
#include <ext/pb_ds/assoc_container.hpp>
#include <functional>
#include <random>
#include <unordered_set>
#line 2 "utils/sfinae.hpp"
#include <type_traits>
template <class type, template <class> class trait>
using enable_if_trait_type = typename std::enable_if<trait<type>::value>::type;
template <class Container>
using element_type = typename std::decay<decltype(
    *std::begin(std::declval<Container&>()))>::type;
template <class T, class = void> struct is_integral_ext : std::false_type {};
template <class T>
struct is_integral_ext<
    T, typename std::enable_if<std::is_integral<T>::value>::type>
    : std::true_type {};
template <> struct is_integral_ext<__int128_t> : std::true_type {};
template <> struct is_integral_ext<__uint128_t> : std::true_type {};
#line 7 "utils/hash.hpp"
namespace workspace {
template <class T, class = void>
struct hash : std::hash<T> {};
template <class Unique_bits_type>
struct hash<Unique_bits_type, enable_if_trait_type<Unique_bits_type, std::has_unique_object_representations>>
{
    size_t operator()(uint64_t x) const
    {
        static const uint64_t m = std::random_device{}();
        x ^= x >> 23;
        // x *= 0x2127599bf4325c37ULL;
        x ^= m;
        x ^= x >> 47;
        return x - (x >> 32);
    }
};
template <class Key>
size_t hash_combine(const size_t &seed, const Key &key)
{
    return seed ^ (hash<Key>()(key) + 0x9e3779b9 /* + (seed << 6) + (seed >> 2) */ );
}
template <class T1, class T2>
struct hash<std::pair<T1, T2>>
{
    size_t operator()(const std::pair<T1, T2> &pair) const
    {
        return hash_combine(hash<T1>()(pair.first), pair.second);
    }
};
template <class... T>
class hash<std::tuple<T...>>
{
    template <class Tuple, size_t index = std::tuple_size<Tuple>::value - 1> struct tuple_hash { static uint64_t apply(const Tuple &t) { return hash_combine(tuple_hash<Tuple, index - 1>::apply(t), std::get<index>(t)); } };
    template <class Tuple> struct tuple_hash<Tuple, size_t(-1)> { static uint64_t apply(const Tuple &t) { return 0; } };
public:
    uint64_t operator()(const std::tuple<T...> &t) const { return tuple_hash<std::tuple<T...>>::apply(t); }
};
template <class hash_table>
struct hash_table_wrapper : hash_table
{
    using key_type = typename hash_table::key_type;
    size_t count(const key_type &key) const { return hash_table::find(key) != hash_table::end(); }
    template <class... Args> auto emplace(Args&&... args) { return hash_table::insert(typename hash_table::value_type(args...)); }
};
template <class Key, class Mapped = __gnu_pbds::null_type>
using cc_hash_table = hash_table_wrapper<__gnu_pbds::cc_hash_table<Key, Mapped, hash<Key>>>;
template <class Key, class Mapped = __gnu_pbds::null_type>
using gp_hash_table = hash_table_wrapper<__gnu_pbds::gp_hash_table<Key, Mapped, hash<Key>>>;
template <class Key, class Mapped>
using unordered_map = std::unordered_map<Key, Mapped, hash<Key>>;
template <class Key>
using unordered_set = std::unordered_set<Key, hash<Key>>;
} // namespace workspace

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

