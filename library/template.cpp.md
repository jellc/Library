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
<script type="text/javascript" src="../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../assets/css/copy-button.css" />


# :warning: template.cpp

<a href="../index.html">Back to top page</a>

* category: <a href="../index.html#5058f1af8388633f609cadb75a75dc9d">.</a>
* <a href="{{ site.github.repository_url }}/blob/master/template.cpp">View this file on GitHub</a>
    - Last commit date: 2020-08-24 16:18:54+09:00




## Depends on

* :warning: <a href="alias.hpp.html">alias.hpp</a>
* :warning: <a href="config.hpp.html">config.hpp</a>
* :warning: <a href="gcc_option.hpp.html">gcc_option.hpp</a>
* :warning: <a href="utils/binary_search.hpp.html">utils/binary_search.hpp</a>
* :warning: <a href="utils/casefmt.hpp.html">utils/casefmt.hpp</a>
* :warning: <a href="utils/chval.hpp.html">utils/chval.hpp</a>
* :warning: <a href="utils/fixed_point.hpp.html">utils/fixed_point.hpp</a>
* :warning: <a href="utils/hash.hpp.html">utils/hash.hpp</a>
* :heavy_check_mark: <a href="utils/iostream_overload.hpp.html">utils/iostream_overload.hpp</a>
* :warning: <a href="utils/read.hpp.html">utils/read.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "gcc_option.hpp"
#include <bits/extc++.h>
#include "config.hpp"
#include "utils/binary_search.hpp"
#include "utils/casefmt.hpp"
#include "utils/chval.hpp"
#include "utils/fixed_point.hpp"
#include "utils/hash.hpp"
#include "utils/iostream_overload.hpp"
#include "utils/read.hpp"
#include "alias.hpp"
namespace workspace { struct solver; } int main() { config::main<workspace::solver>(); }
unsigned config::cases() {
    // return -1; // not specify
    // int t; std::cin >> t; return t; // given
    return 1;
}

struct workspace::solver { // start here!

solver()
{
    
}};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "gcc_option.hpp"
#ifdef LOCAL
    #define _GLIBCXX_DEBUG
#else
    #pragma GCC optimize("O3")
    #pragma GCC target("avx,avx2")
    #pragma GCC optimize("unroll-loops")
#endif
#line 2 "template.cpp"
#include <bits/extc++.h>
#line 5 "config.hpp"
namespace config
{
    const auto start_time{std::chrono::system_clock::now()};
    int64_t elapsed()
    {
        using namespace std::chrono;
        const auto end_time{system_clock::now()};
        return duration_cast<milliseconds>(end_time - start_time).count();
    }
    __attribute__((constructor)) void setup()
    {
        using namespace std;
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout << fixed << setprecision(15);
    #ifdef _buffer_check
        atexit([]{ ofstream cnsl("CON"); char bufc; if(cin >> bufc) cnsl << "\n\033[1;35mwarning\033[0m: buffer not empty.\n\n"; });
    #endif
    }
    unsigned cases(void), caseid = 1;
    template <class C> void main() { for(const unsigned total = cases(); caseid <= total; ++caseid) C(); }
} // namespace config
#line 5 "utils/binary_search.hpp"
namespace workspace {
// binary search on discrete range.
template <class iter_type, class pred_type, std::enable_if_t<std::is_convertible_v<std::invoke_result_t<pred_type, iter_type>, bool>, std::nullptr_t> = nullptr>
iter_type binary_search(iter_type ok, iter_type ng, pred_type pred)
{
    assert(ok != ng);
    intmax_t dist(ng - ok);
    while(std::abs(dist) > 1)
    {
        iter_type mid(ok + dist / 2);
        if(pred(mid)) ok = mid, dist -= dist / 2;
        else ng = mid, dist /= 2;
    }
    return ok;
}
// binary search on real numbers.
template <class real_type, class pred_type, std::enable_if_t<std::is_convertible_v<std::invoke_result_t<pred_type, real_type>, bool>, std::nullptr_t> = nullptr>
real_type binary_search(real_type ok, real_type ng, const real_type eps, pred_type pred)
{
    assert(ok != ng);
    while(std::abs(ok - ng) > eps)
    {
        real_type mid{(ok + ng) / 2};
        (pred(mid) ? ok : ng) = mid;
    }
    return ok;
}
} // namespace workspace
#line 3 "utils/casefmt.hpp"
namespace workspace {
std::ostream &casefmt(std::ostream& os) { return os << "Case #" << config::caseid << ": "; }
} // namespace workspace
#line 3 "utils/chval.hpp"
namespace workspace {
template <class T, class Comp = std::less<T>> bool chle(T &x, const T &y, Comp comp = Comp()) { return comp(y, x) ? x = y, true : false; }
template <class T, class Comp = std::less<T>> bool chge(T &x, const T &y, Comp comp = Comp()) { return comp(x, y) ? x = y, true : false; }
} // namespace workspace
#line 3 "utils/fixed_point.hpp"
namespace workspace {
// specify the return type of lambda.
template <class lambda_type>
class fixed_point
{
    lambda_type func;
public:
    fixed_point(lambda_type &&f) : func(std::move(f)) {}
    template <class... Args> auto operator()(Args &&... args) const { return func(*this, std::forward<Args>(args)...); }
};
} // namespace workspace
#line 3 "utils/hash.hpp"
namespace workspace {
template <class T> class hash : std::hash<T> { size_t operator()(const T&) const; };
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
} // namespace workspace
#line 3 "utils/iostream_overload.hpp"
namespace std
{
    template <class T, class U> istream &operator>>(istream &is, pair<T, U> &p) { return is >> p.first >> p.second; }
    template <class T, class U> ostream &operator<<(ostream &os, const pair<T, U> &p) { return os << p.first << ' ' << p.second; }
    template <class tuple_t, size_t index> struct tupleis { static istream &apply(istream &is, tuple_t &t) { tupleis<tuple_t, index - 1>::apply(is, t); return is >> get<index>(t); } };
    template <class tuple_t> struct tupleis<tuple_t, SIZE_MAX> { static istream &apply(istream &is, tuple_t &t) { return is; } };
    template <class... T> istream &operator>>(istream &is, tuple<T...> &t) { return tupleis<tuple<T...>, tuple_size<tuple<T...>>::value - 1>::apply(is, t); }
    template <> istream &operator>>(istream &is, tuple<> &t) { return is; }
    template <class tuple_t, size_t index> struct tupleos { static ostream &apply(ostream &os, const tuple_t &t) { tupleos<tuple_t, index - 1>::apply(os, t); return os << ' ' << get<index>(t); } };
    template <class tuple_t> struct tupleos<tuple_t, 0> { static ostream &apply(ostream &os, const tuple_t &t) { return os << get<0>(t); } };
    template <class... T> ostream &operator<<(ostream &os, const tuple<T...> &t) { return tupleos<tuple<T...>, tuple_size<tuple<T...>>::value - 1>::apply(os, t); }
    template <> ostream &operator<<(ostream &os, const tuple<> &t) { return os; }
    template <class Container, typename Value = typename Container::value_type, enable_if_t<!is_same<decay_t<Container>, string>::value, nullptr_t> = nullptr>
    istream& operator>>(istream& is, Container &cont) { for(auto&& e : cont) is >> e; return is; }
    template <class Container, typename Value = typename Container::value_type, enable_if_t<!is_same<decay_t<Container>, string>::value, nullptr_t> = nullptr>
    ostream& operator<<(ostream& os, const Container &cont) { bool flag = 1; for(auto&& e : cont) flag ? flag = 0 : (os << ' ', 0), os << e; return os; }
} // namespace std
#line 3 "utils/read.hpp"
namespace workspace {
// read with std::cin.
template <class T = void>
struct read
{
    typename std::remove_const<T>::type value;
    template <class... types>
    read(types... args) : value(args...) { std::cin >> value; }
    operator T() const { return value; }
};
template <>
struct read<void>
{
    template <class T>
    operator T() const { T value; std::cin >> value; return value; }
};
} // namespace workspace
#line 2 "alias.hpp"
using namespace std; using namespace __gnu_cxx;
using i32 = int_least32_t; using i64 = int_least64_t;
using p32 = pair<i32, i32>; using p64 = pair<i64, i64>;
template <class T, class Comp = less<T>> using heap = priority_queue<T, vector<T>, Comp>;
template <class T> using hashset = unordered_set<T>;
template <class Key, class Value> using hashmap = unordered_map<Key, Value>;
#line 12 "template.cpp"
namespace workspace { struct solver; } int main() { config::main<workspace::solver>(); }
unsigned config::cases() {
    // return -1; // not specify
    // int t; std::cin >> t; return t; // given
    return 1;
}

struct workspace::solver { // start here!

solver()
{
    
}};

```
{% endraw %}

<a href="../index.html">Back to top page</a>
