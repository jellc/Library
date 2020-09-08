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


# :heavy_check_mark: test/library-checker/point_set_range_composite.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#8a40f8ed03f4cdb6c2fe0a2d4731a143">test/library-checker</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/library-checker/point_set_range_composite.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-09 07:00:40+09:00


* see: <a href="https://judge.yosupo.jp/problem/point_set_range_composite">https://judge.yosupo.jp/problem/point_set_range_composite</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/algebra/system/monoid.hpp.html">algebra/system/monoid.hpp</a>
* :heavy_check_mark: <a href="../../../library/data_structure/segment_tree/basic.hpp.html">data_structure/segment_tree/basic.hpp</a>
* :question: <a href="../../../library/modulus/modint.hpp.html">modulus/modint.hpp</a>
* :question: <a href="../../../library/utils/sfinae.hpp.html">utils/sfinae.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"
#include "data_structure/segment_tree/basic.hpp"
#include "modulus/modint.hpp"
#include <cstdio>

int main()
{
    using mint=modint<998244353>;
    int n,q;
    scanf("%d%d",&n,&q);
    struct mono
    {
        mint c=1,d;
        mono operator+(const mono& rhs)
        {
            return {rhs.c*c,rhs.c*d+rhs.d};
        }
        mint eval(mint x) const
        {
            return c*x+d;
        }
    };
    segment_tree<mono> seg(n);
    for(int i=0; i<n; i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        seg[i]={a,b};
    }
    for(int t,a,b,c; q--;)
    {
        scanf("%d%d%d%d",&t,&a,&b,&c);
        if(t)
        {
            printf("%d\n",seg.fold(a,b).eval(c));
        }
        else
        {
            seg[a]={b,c};
        }
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/library-checker/point_set_range_composite.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"
#line 2 "data_structure/segment_tree/basic.hpp"
#include <cassert>
#include <vector>

#line 2 "algebra/system/monoid.hpp"
#include <limits>
template <class T>
struct min_monoid
{
    using value_type = T;
    static T min, max;
    T value;
    min_monoid() : value(max) {}
    min_monoid(const T &value) : value(value) {}
    operator T() const { return value; }
    min_monoid operator+(const min_monoid &rhs) const
    {
        return value < rhs.value ? *this : rhs;
    }
};
template <class T> T min_monoid<T>::min = std::numeric_limits<T>::min();
template <class T> T min_monoid<T>::max = std::numeric_limits<T>::max();
template <class T>
struct max_monoid : min_monoid<T>
{
    using base = min_monoid<T>;
    using base::min_monoid;
    max_monoid() : base(base::min) {}
    max_monoid operator+(const max_monoid &rhs) const
    {
        return !(base::value < rhs.value) ? *this : rhs;
    }
};
#line 2 "utils/sfinae.hpp"
#include <cstdint>
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
#line 7 "data_structure/segment_tree/basic.hpp"
template <class Monoid, class Container = std::vector<Monoid>>
class segment_tree {
  static_assert(std::is_same<Monoid, element_type<Container>>::value);

  class unique_queue {
    size_t *que, *begin, *end;
    bool *in;

   public:
    unique_queue(size_t n)
        : que(new size_t[n]), begin(que), end(que), in(new bool[n]{}) {}
    ~unique_queue() {
      delete[] que;
      delete[] in;
    }
    void clear() { begin = end = que; }
    bool empty() const { return begin == end; }
    bool push(size_t index) {
      if (in[index]) return false;
      return in[*end++ = index] = true;
    }
    size_t pop() { return in[*begin] = false, *begin++; }
  };  // struct unique_queue

  size_t size_orig, height, size_ext;
  Container data;
  unique_queue que;

  void recalc(const size_t node) {
    data[node] = data[node << 1] + data[node << 1 | 1];
  }

  void repair() {
    while (!que.empty()) {
      const size_t index = que.pop() >> 1;
      if (index && que.push(index)) recalc(index);
    }
    que.clear();
  }

  template <class Pred>
  size_t left_search_subtree(size_t index, const Pred pred, Monoid mono) const {
    assert(index);
    while (index < size_ext) {
      const Monoid tmp = data[(index <<= 1) | 1] + mono;
      if (pred(tmp))
        mono = tmp;
      else
        ++index;
    }
    return ++index -= size_ext;
  }

  template <class Pred>
  size_t right_search_subtree(size_t index, const Pred pred,
                              Monoid mono) const {
    assert(index);
    while (index < size_ext) {
      const Monoid tmp = mono + data[index <<= 1];
      if (pred(tmp)) ++index, mono = tmp;
    }
    return (index -= size_ext) < size_orig ? index : size_orig;
  }

 public:
  using value_type = Monoid;

  segment_tree(const size_t n = 0)
      : size_orig{n},
        height(n > 1 ? 32 - __builtin_clz(n - 1) : 0),
        size_ext{1u << height},
        data(size_ext << 1),
        que(size_ext << 1) {}

  segment_tree(const size_t n, const Monoid &init) : segment_tree(n) {
    std::fill(std::next(std::begin(data), size_ext), std::end(data), init);
    for (size_t i{size_ext}; --i;) recalc(i);
  }

  template <class iter_type, class value_type = typename std::iterator_traits<
                                 iter_type>::value_type>
  segment_tree(iter_type first, iter_type last)
      : size_orig(std::distance(first, last)),
        height(size_orig > 1 ? 32 - __builtin_clz(size_orig - 1) : 0),
        size_ext{1u << height},
        data(size_ext << 1),
        que(size_ext << 1) {
    static_assert(std::is_constructible<Monoid, value_type>::value,
                  "Monoid(iter_type::value_type) is not constructible.");
    for (auto iter{std::next(std::begin(data), size_ext)};
         iter != std::end(data) && first != last; ++iter, ++first)
      *iter = Monoid{*first};
    for (size_t i{size_ext}; --i;) recalc(i);
  }

  template <class Cont, typename = typename Cont::value_type>
  segment_tree(const Cont &cont)
      : segment_tree(std::begin(cont), std::end(cont)) {}

  size_t size() const { return size_orig; }
  size_t capacity() const { return size_ext; }

  // reference to the element at the index.
  Monoid &operator[](size_t index) {
    assert(index < size_orig);
    que.push(index |= size_ext);
    return data[index];
  }

  // const reference to the element at the index.
  const Monoid &operator[](size_t index) const {
    assert(index < size_orig);
    return data[index |= size_orig];
  }

  Monoid fold(size_t first, size_t last) {
    assert(last <= size_orig);
    repair();
    Monoid leftval{}, rightval{};
    first += size_ext, last += size_ext;
    while (first < last) {
      if (first & 1) leftval = leftval + data[first++];
      if (last & 1) rightval = data[--last] + rightval;
      first >>= 1, last >>= 1;
    }
    return leftval + rightval;
  }

  Monoid fold() { return fold(0, size_orig); }

  template <class Pred> size_t left_search(size_t right, Pred pred) {
    assert(right <= size_orig);
    repair();
    right += size_ext;
    Monoid mono{};
    for (size_t left{size_ext}; left != right; left >>= 1, right >>= 1) {
      if ((left & 1) != (right & 1)) {
        const Monoid tmp = data[--right] + mono;
        if (!pred(tmp)) return left_search_subtree(right, pred, mono);
        mono = tmp;
      }
    }
    return 0;
  }

  template <class Pred> size_t right_search(size_t left, Pred pred) {
    assert(left <= size_orig);
    repair();
    left += size_ext;
    Monoid mono{};
    for (size_t right{size_ext << 1}; left != right; left >>= 1, right >>= 1) {
      if ((left & 1) != (right & 1)) {
        const Monoid tmp = mono + data[left];
        if (!pred(tmp)) return right_search_subtree(left, pred, mono);
        mono = tmp;
        ++left;
      }
    }
    return size_orig;
  }
};  // class segment_tree
#line 3 "modulus/modint.hpp"
#include <iostream>

#line 6 "modulus/modint.hpp"

template <auto Mod = 0, typename Mod_type = decltype(Mod)> struct modint {
  static_assert(is_integral_ext<decltype(Mod)>::value,
                "Mod must be integral type.");
  static_assert(!(Mod < 0), "Mod must be non-negative.");

  using mod_type = typename std::conditional<
      Mod != 0, typename std::add_const<Mod_type>::type, Mod_type>::type;
  static mod_type mod;

  using value_type = typename std::decay<mod_type>::type;

  constexpr operator value_type() const noexcept { return value; }

  constexpr static modint one() noexcept { return 1; }

  constexpr modint() noexcept = default;

  template <class int_type,
            typename std::enable_if<is_integral_ext<int_type>::value>::type * =
                nullptr>
  constexpr modint(int_type n) noexcept : value((n %= mod) < 0 ? mod + n : n) {}

  constexpr modint operator++(int) noexcept {
    modint t{*this};
    return operator+=(1), t;
  }

  constexpr modint operator--(int) noexcept {
    modint t{*this};
    return operator-=(1), t;
  }

  constexpr modint &operator++() noexcept { return operator+=(1); }

  constexpr modint &operator--() noexcept { return operator-=(1); }

  constexpr modint operator-() const noexcept {
    return value ? mod - value : 0;
  }

  constexpr modint &operator+=(const modint &rhs) noexcept {
    return (value += rhs.value) < mod ? 0 : value -= mod, *this;
  }

  constexpr modint &operator-=(const modint &rhs) noexcept {
    return (value += mod - rhs.value) < mod ? 0 : value -= mod, *this;
  }

  constexpr modint &operator*=(const modint &rhs) noexcept {
    return value = (typename multiplicable_uint<value_type>::type)value *
                   rhs.value % mod,
           *this;
  }

  constexpr modint &operator/=(const modint &rhs) noexcept {
    return operator*=(rhs.inverse());
  }

  template <class int_type>
  constexpr
      typename std::enable_if<is_integral_ext<int_type>::value, modint>::type
      operator+(const int_type &rhs) const noexcept {
    return modint{*this} += rhs;
  }

  constexpr modint operator+(const modint &rhs) const noexcept {
    return modint{*this} += rhs;
  }

  template <class int_type>
  constexpr
      typename std::enable_if<is_integral_ext<int_type>::value, modint>::type
      operator-(const int_type &rhs) const noexcept {
    return modint{*this} -= rhs;
  }

  constexpr modint operator-(const modint &rhs) const noexcept {
    return modint{*this} -= rhs;
  }

  template <class int_type>
  constexpr
      typename std::enable_if<is_integral_ext<int_type>::value, modint>::type
      operator*(const int_type &rhs) const noexcept {
    return modint{*this} *= rhs;
  }

  constexpr modint operator*(const modint &rhs) const noexcept {
    return modint{*this} *= rhs;
  }

  template <class int_type>
  constexpr
      typename std::enable_if<is_integral_ext<int_type>::value, modint>::type
      operator/(const int_type &rhs) const noexcept {
    return modint{*this} /= rhs;
  }

  constexpr modint operator/(const modint &rhs) const noexcept {
    return modint{*this} /= rhs;
  }

  template <class int_type>
  constexpr friend
      typename std::enable_if<is_integral_ext<int_type>::value, modint>::type
      operator+(const int_type &lhs, const modint &rhs) noexcept {
    return modint(lhs) + rhs;
  }

  template <class int_type>
  constexpr friend
      typename std::enable_if<is_integral_ext<int_type>::value, modint>::type
      operator-(const int_type &lhs, const modint &rhs) noexcept {
    return modint(lhs) - rhs;
  }

  template <class int_type>
  constexpr friend
      typename std::enable_if<is_integral_ext<int_type>::value, modint>::type
      operator*(const int_type &lhs, const modint &rhs) noexcept {
    return modint(lhs) * rhs;
  }

  template <class int_type>
  constexpr friend
      typename std::enable_if<is_integral_ext<int_type>::value, modint>::type
      operator/(const int_type &lhs, const modint &rhs) noexcept {
    return modint(lhs) / rhs;
  }

  constexpr modint inverse() const noexcept {
    assert(value);
    value_type a{mod}, b{value}, u{}, v{1}, t{};
    while (b)
      t = a / b, a ^= b ^= (a -= t * b) ^= b, u ^= v ^= (u -= t * v) ^= v;
    return {u};
  }

  template <class int_type>
  constexpr
      typename std::enable_if<is_integral_ext<int_type>::value, modint>::type
      power(int_type e) noexcept {
    if (e < 0) e = e % (mod - 1) + mod - 1;
    modint res{1}, p{*this};
    for (modint p{value}; e; e >>= 1, p *= p) {
      if (e & 1) res *= p;
    }
    return res;
  }

  friend std::ostream &operator<<(std::ostream &os,
                                  const modint &rhs) noexcept {
    return os << rhs.value;
  }

  friend std::istream &operator>>(std::istream &is, modint &rhs) noexcept {
    intmax_t value;
    rhs = (is >> value, value);
    return is;
  }

 protected:
  value_type value = 0;
};

template <auto Mod, typename Mod_type>
typename modint<Mod, Mod_type>::mod_type modint<Mod, Mod_type>::mod = Mod;

using modint_runtime = modint<0>;
#line 4 "test/library-checker/point_set_range_composite.test.cpp"
#include <cstdio>

int main()
{
    using mint=modint<998244353>;
    int n,q;
    scanf("%d%d",&n,&q);
    struct mono
    {
        mint c=1,d;
        mono operator+(const mono& rhs)
        {
            return {rhs.c*c,rhs.c*d+rhs.d};
        }
        mint eval(mint x) const
        {
            return c*x+d;
        }
    };
    segment_tree<mono> seg(n);
    for(int i=0; i<n; i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        seg[i]={a,b};
    }
    for(int t,a,b,c; q--;)
    {
        scanf("%d%d%d%d",&t,&a,&b,&c);
        if(t)
        {
            printf("%d\n",seg.fold(a,b).eval(c));
        }
        else
        {
            seg[a]={b,c};
        }
    }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

