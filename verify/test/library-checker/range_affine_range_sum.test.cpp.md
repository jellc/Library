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


# :heavy_check_mark: test/library-checker/range_affine_range_sum.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#8a40f8ed03f4cdb6c2fe0a2d4731a143">test/library-checker</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/library-checker/range_affine_range_sum.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-10 02:20:46+09:00


* see: <a href="https://judge.yosupo.jp/problem/range_affine_range_sum">https://judge.yosupo.jp/problem/range_affine_range_sum</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/data_structure/segment_tree/lazy.hpp.html">data_structure/segment_tree/lazy.hpp</a>
* :heavy_check_mark: <a href="../../../library/modulus/modint.hpp.html">modulus/modint.hpp</a>
* :heavy_check_mark: <a href="../../../library/utils/sfinae.hpp.html">utils/sfinae.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"
#include <cstdio>
#include <vector>

#include "data_structure/segment_tree/lazy.hpp"
#include "modulus/modint.hpp"

int main() {
  using mint = modint<998244353>;
  struct endo {
    mint a = 1, b;
    endo operator*(endo rhs) { return {a * rhs.a, b * rhs.a + rhs.b}; }
  };
  struct mono {
    mint v, c;
    mono operator+(mono rhs) { return {v + rhs.v, c + rhs.c}; }
    mono operator*(endo rhs) { return {v * rhs.a + c * rhs.b, c}; }
  };

  int n, q;
  scanf("%d%d", &n, &q);
  lazy_segment_tree<mono, endo> seg;
  {
    std::vector<mono> a(n);
    for (auto &[v, c] : a) {
      int _v;
      scanf("%d", &_v);
      v = _v;
      c = 1;
    }
    seg = a;
  }
  for (int t, l, r, a, b; q--;) {
    scanf("%d%d%d", &t, &l, &r);
    if (t) {
      printf("%d\n", seg.fold(l, r).v);
    } else {
      scanf("%d%d", &a, &b);
      seg.update(l, r, {a, b});
    }
  }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/library-checker/range_affine_range_sum.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"
#include <cstdio>
#include <vector>

#line 2 "data_structure/segment_tree/lazy.hpp"
#include <cassert>
#line 4 "data_structure/segment_tree/lazy.hpp"

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
#line 6 "data_structure/segment_tree/lazy.hpp"
template <class Monoid, class Endomorphism,
          template <class...> class Container_tmpl = std::vector>
class lazy_segment_tree {
  size_t size_orig, height, size_ext;
  Container_tmpl<Monoid> data;
  Container_tmpl<Endomorphism> lazy;

  static_assert(std::is_same<Monoid, decltype(Monoid{} + Monoid{})>::value,
                "\'Monoid\' has no proper binary operator+.");

  static_assert(std::is_same<Endomorphism,
                             decltype(Endomorphism{} * Endomorphism{})>::value,
                "\'Endomorphism\' has no proper binary operator*.");

  static_assert(
      std::is_same<Monoid, decltype(Monoid{} * Endomorphism{})>::value,
      "\'Endomorphism\' is not applicable to \'Monoid\'.");

  void pull(const size_t &node) {
    data[node] = data[node << 1] + data[node << 1 | 1];
  }

  void apply(const size_t &node, const Endomorphism &endo) {
    data[node] = data[node] * endo;
    if (node < size_ext) lazy[node] = lazy[node] * endo;
  }

  void push(const size_t &node) {
    if (node >= size_ext) return;
    apply(node << 1, lazy[node]);
    apply(node << 1 | 1, lazy[node]);
    lazy[node] = Endomorphism{};
  }

  template <class Pred>
  size_t left_search_subtree(size_t node, Pred pred, Monoid mono) {
    assert(node);
    while (node < size_ext) {
      push(node);
      const Monoid &tmp = data[(node <<= 1) | 1] + mono;
      if (pred(tmp))
        mono = tmp;
      else
        ++node;
    }
    return ++node -= size_ext;
  }

  template <class Pred>
  size_t right_search_subtree(size_t node, Pred pred, Monoid mono) {
    assert(node);
    while (node < size_ext) {
      push(node);
      const Monoid &tmp = mono + data[node <<= 1];
      if (pred(tmp)) ++node, mono = tmp;
    }
    return (node -= size_ext) < size_orig ? node : size_orig;
  }

 public:
  lazy_segment_tree(const size_t n = 0)
      : size_orig{n},
        height(n > 1 ? 32 - __builtin_clz(n - 1) : 0),
        size_ext{1u << height},
        data(size_ext << 1),
        lazy(size_ext) {}

  lazy_segment_tree(const size_t &n, const Monoid &init)
      : lazy_segment_tree(n) {
    std::fill(std::next(std::begin(data), size_ext), std::end(data), init);
    for (size_t i{size_ext}; --i;) pull(i);
  }

  template <class iter_type, class value_type = typename std::iterator_traits<
                                 iter_type>::value_type>
  lazy_segment_tree(iter_type first, iter_type last)
      : size_orig(std::distance(first, last)),
        height(size_orig > 1 ? 32 - __builtin_clz(size_orig - 1) : 0),
        size_ext{1u << height},
        data(size_ext << 1),
        lazy(size_ext) {
    static_assert(std::is_constructible<Monoid, value_type>::value,
                  "Monoid(iter_type::value_type) is not constructible.");
    for (auto iter{std::next(std::begin(data), size_ext)};
         iter != std::end(data) && first != last; ++iter, ++first)
      *iter = Monoid(*first);
    for (size_t i{size_ext}; --i;) pull(i);
  }

  template <class Container, typename = typename Container::value_type>
  lazy_segment_tree(const Container &cont)
      : lazy_segment_tree(std::begin(cont), std::end(cont)) {}

  size_t size() const { return size_orig; }
  size_t capacity() const { return size_ext; }

  Monoid operator[](const size_t &index) { return fold(index, index + 1); }

  void update(const size_t &index, const Endomorphism &endo) {
    update(index, index + 1, endo);
  }

  void update(size_t first, size_t last, const Endomorphism &endo) {
    assert(last <= size_orig);
    if (first >= last) return;
    first += size_ext, last += size_ext - 1;
    for (size_t i = height; i; --i) push(first >> i), push(last >> i);
    for (size_t l = first, r = last + 1; last; l >>= 1, r >>= 1) {
      if (l < r) {
        if (l & 1) apply(l++, endo);
        if (r & 1) apply(--r, endo);
      }
      if (first >>= 1, last >>= 1) {
        pull(first), pull(last);
      }
    }
  }

  Monoid fold() { return fold(0, size_orig); }

  Monoid fold(size_t first, size_t last) {
    assert(last <= size_orig);
    if (first >= last) return Monoid{};
    first += size_ext, last += size_ext - 1;
    Monoid left_val{}, right_val{};
    for (size_t l = first, r = last + 1; last; l >>= 1, r >>= 1) {
      if (l < r) {
        if (l & 1) left_val = left_val + data[l++];
        if (r & 1) right_val = data[--r] + right_val;
      }
      if (first >>= 1, last >>= 1) {
        left_val = left_val * lazy[first];
        right_val = right_val * lazy[last];
      }
    }
    return left_val + right_val;
  }

  template <class Pred> size_t left_search(size_t right, Pred pred) {
    assert(right <= size_orig);
    right += size_ext - 1;
    for (size_t i{height}; i; --i) push(right >> i);
    ++right;
    Monoid mono{};
    for (size_t left{size_ext}; left != right; left >>= 1, right >>= 1) {
      if ((left & 1) != (right & 1)) {
        const Monoid &tmp = data[--right] + mono;
        if (!pred(tmp)) return left_search_subtree(right, pred, mono);
        mono = tmp;
      }
    }
    return 0;
  }

  template <class Pred> size_t right_search(size_t left, Pred pred) {
    assert(left <= size_orig);
    left += size_ext;
    for (size_t i{height}; i; --i) push(left >> i);
    Monoid mono{};
    for (size_t right{size_ext << 1}; left != right; left >>= 1, right >>= 1) {
      if ((left & 1) != (right & 1)) {
        const Monoid &tmp = mono + data[left];
        if (!pred(tmp)) return right_search_subtree(left, pred, mono);
        mono = tmp;
        ++left;
      }
    }
    return size_orig;
  }
};  // class lazy_segment_tree
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

  constexpr modint(bool n) noexcept : modint(int(n)) {}

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
#line 7 "test/library-checker/range_affine_range_sum.test.cpp"

int main() {
  using mint = modint<998244353>;
  struct endo {
    mint a = 1, b;
    endo operator*(endo rhs) { return {a * rhs.a, b * rhs.a + rhs.b}; }
  };
  struct mono {
    mint v, c;
    mono operator+(mono rhs) { return {v + rhs.v, c + rhs.c}; }
    mono operator*(endo rhs) { return {v * rhs.a + c * rhs.b, c}; }
  };

  int n, q;
  scanf("%d%d", &n, &q);
  lazy_segment_tree<mono, endo> seg;
  {
    std::vector<mono> a(n);
    for (auto &[v, c] : a) {
      int _v;
      scanf("%d", &_v);
      v = _v;
      c = 1;
    }
    seg = a;
  }
  for (int t, l, r, a, b; q--;) {
    scanf("%d%d%d", &t, &l, &r);
    if (t) {
      printf("%d\n", seg.fold(l, r).v);
    } else {
      scanf("%d%d", &a, &b);
      seg.update(l, r, {a, b});
    }
  }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

