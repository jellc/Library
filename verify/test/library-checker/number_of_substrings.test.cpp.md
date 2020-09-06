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


# :heavy_check_mark: test/library-checker/number_of_substrings.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#8a40f8ed03f4cdb6c2fe0a2d4731a143">test/library-checker</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/library-checker/number_of_substrings.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-07 03:51:28+09:00


* see: <a href="https://judge.yosupo.jp/problem/number_of_substrings">https://judge.yosupo.jp/problem/number_of_substrings</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/string/suffix_array.hpp.html">string/suffix_array.hpp</a>
* :heavy_check_mark: <a href="../../../library/utils/sfinae.hpp.html">utils/sfinae.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/number_of_substrings"
#include <iostream>

#include "string/suffix_array.hpp"

int main() {
  std::string s;
  std::cin >> s;
  suffix_array sa(s);
  long long ans = 0;
  for (size_t i = 0; i < s.size(); i++) {
    ans += s.size() - sa[i] - sa.lcp_array()[i];
  }
  printf("%lld\n", ans);
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/library-checker/number_of_substrings.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/number_of_substrings"
#include <iostream>

#line 2 "string/suffix_array.hpp"
#include <algorithm>
#include <vector>
#include <numeric>
#line 2 "utils/sfinae.hpp"
#include <type_traits>
template <class type, template <class> class trait>
using enable_if_trait_type = typename std::enable_if<trait<type>::value>::type;
template <class Container>
using element_type = typename std::decay<decltype(
    *std::begin(std::declval<Container&>()))>::type;
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
#line 5 "test/library-checker/number_of_substrings.test.cpp"

int main() {
  std::string s;
  std::cin >> s;
  suffix_array sa(s);
  long long ans = 0;
  for (size_t i = 0; i < s.size(); i++) {
    ans += s.size() - sa[i] - sa.lcp_array()[i];
  }
  printf("%lld\n", ans);
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>
