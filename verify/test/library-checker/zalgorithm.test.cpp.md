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


# :heavy_check_mark: test/library-checker/zalgorithm.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#8a40f8ed03f4cdb6c2fe0a2d4731a143">test/library-checker</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/library-checker/zalgorithm.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-09 06:36:03+09:00


* see: <a href="https://judge.yosupo.jp/problem/zalgorithm">https://judge.yosupo.jp/problem/zalgorithm</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/string/z_algorithm.hpp.html">string/z_algorithm.hpp</a>
* :heavy_check_mark: <a href="../../../library/utils/sfinae.hpp.html">utils/sfinae.hpp</a>
* :heavy_check_mark: <a href="../../../library/utils/stream.hpp.html">utils/stream.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"
#include <bits/stdc++.h>

#include "string/z_algorithm.hpp"
#include "utils/stream.hpp"

int main() {
  std::string s;
  std::cin >> s;
  z_algorithm z(s);
  std::cout << z << "\n";
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/library-checker/zalgorithm.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"
#include <bits/stdc++.h>

#line 4 "string/z_algorithm.hpp"

template <class str_type = std::string> class z_algorithm {
  str_type key;
  std::vector<size_t> z;

  void make() {
    if (z.empty()) return;
    for (size_t i{1}, j{0}; i != size(); ++i) {
      if (z[i - j] + i < z[j] + j) {
        z[i] = z[i - j];
      } else {
        size_t k{z[j] + j > i ? z[j] + j - i : 0};
        while (k + i < size() && key[k] == key[k + i]) ++k;
        z[i] = k;
        j = i;
      }
    }
    z.front() = size();
  }

 public:
  z_algorithm(const str_type &key) : key(key), z(size()) { make(); }

  std::vector<size_t>::const_iterator begin() const { return z.begin(); }
  std::vector<size_t>::const_iterator end() const { return z.end(); }

  size_t size() const { return key.size(); }

  size_t operator[](size_t i) const {
    assert(i < size());
    return z[i];
  }

  std::vector<size_t> pattern_search(const str_type &str) const {
    str_type ccat(key);
    ccat.insert(end(ccat), begin(str), end(str));
    z_algorithm z(ccat);
    std::vector<size_t> res(z.begin() + size(), z.end());
    for (size_t &x : res)
      if (x > size()) x = size();
    return res;
  }
};
#line 4 "utils/stream.hpp"

#line 3 "utils/sfinae.hpp"
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

template <typename T, typename = void> struct multiplicable_uint {
  using type = uint_least32_t;
};
template <typename T>
struct multiplicable_uint<T, typename std::enable_if<(2 < sizeof(T))>::type> {
  using type = uint_least64_t;
};
template <typename T>
struct multiplicable_uint<T, typename std::enable_if<(4 < sizeof(T))>::type> {
  using type = __uint128_t;
};
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
#line 6 "test/library-checker/zalgorithm.test.cpp"

int main() {
  std::string s;
  std::cin >> s;
  z_algorithm z(s);
  std::cout << z << "\n";
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

