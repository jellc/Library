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


# :heavy_check_mark: data_structure/segment_tree/basic.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#fba856dbe1aaa5374a50a27f6dcea717">data_structure/segment_tree</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/segment_tree/basic.hpp">View this file on GitHub</a>
    - Last commit date: 2020-09-07 04:18:33+09:00




## Depends on

* :heavy_check_mark: <a href="../../algebra/system/monoid.hpp.html">algebra/system/monoid.hpp</a>
* :heavy_check_mark: <a href="../../utils/sfinae.hpp.html">utils/sfinae.hpp</a>


## Verified with

* :heavy_check_mark: <a href="../../../verify/test/library-checker/point_set_range_composite.test.cpp.html">test/library-checker/point_set_range_composite.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/test/library-checker/static_range_inversions_query.test.cpp.html">test/library-checker/static_range_inversions_query.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <cassert>
#include <vector>

#include "algebra/system/monoid.hpp"
#include "utils/sfinae.hpp"
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

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
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
#include <type_traits>
template <class type, template <class> class trait>
using enable_if_trait_type = typename std::enable_if<trait<type>::value>::type;
template <class Container>
using element_type = typename std::decay<decltype(
    *std::begin(std::declval<Container&>()))>::type;
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

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

