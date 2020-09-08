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


# :heavy_check_mark: test/library-checker/suffix_array.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#8a40f8ed03f4cdb6c2fe0a2d4731a143">test/library-checker</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/library-checker/suffix_array.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-09 05:57:31+09:00


* see: <a href="https://judge.yosupo.jp/problem/suffixarray">https://judge.yosupo.jp/problem/suffixarray</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/string/suffix_array.hpp.html">string/suffix_array.hpp</a>
* :heavy_check_mark: <a href="../../../library/utils/sfinae.hpp.html">utils/sfinae.hpp</a>
* :heavy_check_mark: <a href="../../../library/utils/stream.hpp.html">utils/stream.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"
#include <bits/stdc++.h>

#include "string/suffix_array.hpp"
#include "utils/stream.hpp"

using namespace std;

int main() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  string s;
  cin >> s;
  cout << suffix_array<string>(s) << "\n";
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/library-checker/suffix_array.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"
#include <bits/stdc++.h>

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
template <class T>
constexpr static bool is_integral_ext_v = is_integral_ext<T>::value;
#line 6 "string/suffix_array.hpp"
template <class str_type>
class suffix_array
{
    static constexpr size_t npos = -1;
    str_type str;
    std::vector<size_t> sa, rank, lcp;

    void construct_sa()
    {
        std::iota(sa.begin(), sa.end(), 0);
        std::sort(sa.begin(), sa.end(), [&](size_t i, size_t j){return str[i] < str[j];});

        for(size_t r{1}, c{}, *ptr{&sa.front()}, *tmp{ptr}; c != size(); ++r, ptr = tmp)
            while(c != size() && str[*ptr] == str[*tmp])
                ++c, rank[*tmp++] = r;

        for(size_t k{1}; k < size(); k <<= 1)
        {
            auto comp = [&](size_t i, size_t j) -> bool
            {
                if(rank[i] != rank[j]) return rank[i] < rank[j];
                return (i + k < size() ? rank[i + k] : 0) < (j + k < size() ? rank[j + k] : 0);
            };
            std::sort(sa.begin(), sa.end(), comp);

            std::vector<size_t> next_rank(size());
            for(size_t r{1}, c{}, *ptr{&sa.front()}, *tmp{ptr}; c != size(); ++r, ptr = tmp)
                while(c != size() && !comp(*ptr, *tmp))
                    ++c, next_rank[*tmp++] = r;
            rank.swap(next_rank);
        }

        sa.emplace(sa.begin(), size());
        rank.emplace_back(0);
    }

    void construct_lcp()
    {
        for(size_t i{}, h{}; i != size(); ++i, h = h ? h - 1 : 0)
        {
            for(size_t j{sa[rank[i] - 1] + h}; i + h != size() && j != size(); ++j, ++h)
                if(str[i + h] != str[j]) break;
            lcp[rank[i] - 1] = h;
        }
    }

public:
    using value_type = element_type<str_type>;

    std::vector<size_t>::const_iterator begin() const { return sa.begin() + 1; }
    std::vector<size_t>::const_iterator end() const { return sa.end(); }

    size_t operator[](size_t i) const { return sa[i + 1]; }

    size_t size() const { return std::size(str); }

    template <class type = str_type, typename = typename type::value_type>
    suffix_array(const str_type &_str) : str(_str), sa(size()), rank(size()), lcp(size())
    {
        construct_sa();
        construct_lcp();
    }

    template <class type = str_type, std::enable_if_t<std::is_array<type>::value, std::nullptr_t> = nullptr>
    suffix_array(const str_type &_str) : sa(size()), rank(size()), lcp(size())
    {
        std::copy(std::begin(_str), std::end(_str), str);
        construct_sa();
        construct_lcp();
    }

    size_t find(const str_type &key) const
    {
        using std::begin; using std::end;

        size_t lower{npos}, upper{size()};
        while(upper - lower > 1)
        {
            size_t mid = (lower + upper) >> 1;
            bool less = false;
            for(auto i{begin(str) + sa[mid]}, j{begin(key)}; j != end(key); ++i, ++j)
            {
                if(i == end(str) || *i < *j)
                {
                    less = true;
                    break;
                }
                if(*i > *j) break;
            }
            (less ? lower : upper) = mid;
        }

        if(upper == size()) return npos;
        for(auto i{begin(str) + sa[upper]}, j{begin(key)}; j != end(key); ++i, ++j)
            if(i == end(str) || *i != *j)
                return npos;
        return sa[upper];
    }

    const std::vector<size_t> &lcp_array() const { return lcp; }
}; // class suffix_array
#line 4 "utils/stream.hpp"

#line 6 "utils/stream.hpp"
namespace std {
template <class T, class U> istream &operator>>(istream &is, pair<T, U> &p) {
  return is >> p.first >> p.second;
}
template <class T, class U>
ostream &operator<<(ostream &os, const pair<T, U> &p) {
  return os << p.first << ' ' << p.second;
}
template <class tuple_t, size_t index> struct tuple_is {
  static istream &apply(istream &is, tuple_t &t) {
    tuple_is<tuple_t, index - 1>::apply(is, t);
    return is >> get<index>(t);
  }
};
template <class tuple_t> struct tuple_is<tuple_t, SIZE_MAX> {
  static istream &apply(istream &is, tuple_t &t) { return is; }
};
template <class... T> istream &operator>>(istream &is, tuple<T...> &t) {
  return tuple_is<tuple<T...>, tuple_size<tuple<T...>>::value - 1>::apply(is,
                                                                          t);
}
template <class tuple_t, size_t index> struct tuple_os {
  static ostream &apply(ostream &os, const tuple_t &t) {
    tuple_os<tuple_t, index - 1>::apply(os, t);
    return os << ' ' << get<index>(t);
  }
};
template <class tuple_t> struct tuple_os<tuple_t, 0> {
  static ostream &apply(ostream &os, const tuple_t &t) {
    return os << get<0>(t);
  }
};
template <class tuple_t> struct tuple_os<tuple_t, SIZE_MAX> {
  static ostream &apply(ostream &os, const tuple_t &t) { return os; }
};
template <class... T> ostream &operator<<(ostream &os, const tuple<T...> &t) {
  return tuple_os<tuple<T...>, tuple_size<tuple<T...>>::value - 1>::apply(os,
                                                                          t);
}
template <class Container, typename Value = element_type<Container>>
typename enable_if<!is_same<typename decay<Container>::type, string>::value &&
                       !is_same<typename decay<Container>::type, char *>::value,
                   istream &>::type
operator>>(istream &is, Container &cont) {
  for (auto &&e : cont) is >> e;
  return is;
}
template <class Container, typename Value = element_type<Container>>
typename enable_if<!is_same<typename decay<Container>::type, string>::value &&
                       !is_same<typename decay<Container>::type, char *>::value,
                   ostream &>::type
operator<<(ostream &os, const Container &cont) {
  bool head = true;
  for (auto &&e : cont) head ? head = 0 : (os << ' ', 0), os << e;
  return os;
}
}  // namespace std
#line 6 "test/library-checker/suffix_array.test.cpp"

using namespace std;

int main() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  string s;
  cin >> s;
  cout << suffix_array<string>(s) << "\n";
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

