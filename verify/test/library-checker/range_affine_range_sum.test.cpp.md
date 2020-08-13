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
    - Last commit date: 2020-08-14 02:35:26+09:00


* see: <a href="https://judge.yosupo.jp/problem/range_affine_range_sum">https://judge.yosupo.jp/problem/range_affine_range_sum</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/data_structure/segment_tree/lazy_segment_tree.hpp.html">data_structure/segment_tree/lazy_segment_tree.hpp</a>
* :heavy_check_mark: <a href="../../../library/modulus/modint.hpp.html">modulus/modint.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"
#include "../../data_structure/segment_tree/lazy_segment_tree.hpp"
#include "../../modulus/modint.hpp"
#include <cstdio>

int main()
{
    using mint=modint<998244353>;
    struct mono
    {
        mint v,c;
        mono operator+(mono rhs) const
        {
            return {v+rhs.v,c+rhs.c};
        }
    };
    struct endo
    {
        mint a=1,b;
        endo &operator*=(endo rhs)
        {
            a*=rhs.a;
            b=b*rhs.a+rhs.b;
            return *this;
        }
        void apply(mono& rhs) const
        {
            rhs.v*=a;
            rhs.v+=rhs.c*b;
        }
    };
    int n,q;
    scanf("%d%d",&n,&q);
    lazy_segment_tree<mono,endo> seg;
    {
        std::vector<mono> a(n);
        for(auto &[v,c]: a)
        {
            int _v;
            scanf("%d",&_v);
            v=_v;
            c=1;
        }
        seg=a;
    }
    for(int t,l,r,a,b; q--; )
    {
        scanf("%d%d%d",&t,&l,&r);
        if(t)
        {
            printf("%d\n",seg.fold(l,r).v);
        }
        else
        {
            scanf("%d%d",&a,&b);
            seg.update(l,r,{a,b});
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
#line 1 "data_structure/segment_tree/lazy_segment_tree.hpp"
#include <cassert>
#include <vector>

template <class monoid, class endomorphism>
class lazy_segment_tree
{
    using size_type = typename std::vector<monoid>::size_type;
    template <class T> using container_type = std::vector<T>;

    size_type size_orig, height, size_ext;
    container_type<monoid> data;
    container_type<endomorphism> lazy;

    void recalc(const size_type node) { data[node] = data[node << 1] + data[node << 1 | 1]; }

    void apply(size_type index, const endomorphism &endo)
    {
        endo.apply(data[index]);
        if(index < size_ext) lazy[index] *= endo;
    }

    void push(size_type index)
    {
        if(index >= size_ext) return;
        apply(index << 1, lazy[index]);
        apply(index << 1 | 1, lazy[index]);
        lazy[index] = endomorphism{};
    }

    template <class pred_type>
    size_type left_search_subtree(size_type index, const pred_type pred, monoid mono)
    {
        assert(index);
        while(index < size_ext)
        {
            push(index);
            const monoid tmp = data[(index <<= 1) | 1] + mono;
            if(pred(tmp)) mono = tmp;
            else ++index;
        }
        return ++index -= size_ext;
    }

    template <class pred_type>
    size_type right_search_subtree(size_type index, const pred_type pred, monoid mono)
    {
        assert(index);
        while(index < size_ext)
        {
            push(index);
            const monoid tmp = mono + data[index <<= 1];
            if(pred(tmp)) ++index, mono = tmp;
        }
        return (index -= size_ext) < size_orig ? index : size_orig;
    }

public:
    lazy_segment_tree(const size_type n = 0) : size_orig{n}, height(n > 1 ? 32 - __builtin_clz(n - 1) : 0), size_ext{1u << height}, data(size_ext << 1), lazy(size_ext) {}

    lazy_segment_tree(const size_type n, const monoid &init) : lazy_segment_tree(n)
    {
        std::fill(std::next(std::begin(data), size_ext), std::end(data), init);
        for(size_type i{size_ext}; --i; ) recalc(i);
    }

    template <class iter_type, class value_type = typename std::iterator_traits<iter_type>::value_type>
    lazy_segment_tree(iter_type first, iter_type last)
        : size_orig(std::distance(first, last)), height(size_orig > 1 ? 32 - __builtin_clz(size_orig - 1) : 0), size_ext{1u << height}, data(size_ext << 1), lazy(size_ext)
    {
        static_assert(std::is_constructible<monoid, value_type>::value, "monoid(iter_type::value_type) is not constructible.");
        for(auto iter{std::next(std::begin(data), size_ext)}; iter != std::end(data) && first != last; ++iter, ++first) *iter = monoid(*first);
        for(size_type i{size_ext}; --i; ) recalc(i);
    }

    template <class container_type, typename = typename container_type::value_type>
    lazy_segment_tree(const container_type &cont) : lazy_segment_tree(std::begin(cont), std::end(cont)) {}

    size_type size() const { return size_orig; }
    size_type capacity() const { return size_ext; }

    monoid operator[](size_type index) { return fold(index, index + 1); }

    void update(const size_type index, const endomorphism &endo) { update(index, index + 1, endo); }

    void update(size_type first, size_type last, const endomorphism &endo)
    {
        assert(last <= size_orig);
        if(first >= last) return;
        first += size_ext, last += size_ext - 1;
        for(size_type i = height; i; --i) push(first >> i), push(last >> i);
        for(size_type l = first, r = last + 1; last; l >>= 1, r >>= 1)
        {
            if(l < r)
            {
                if(l & 1) apply(l++, endo);
                if(r & 1) apply(--r, endo);
            }
            if(first >>= 1, last >>= 1)
            {
                recalc(first), recalc(last);
            }
        }
    }

    monoid fold() { return fold(0, size_orig); }

    monoid fold(size_type first, size_type last)
    {
        assert(last <= size_orig);
        if(first >= last) return monoid{};
        first += size_ext, last += size_ext - 1;
        monoid left_val{}, right_val{};
        for(size_type l = first, r = last + 1; last; l >>= 1, r >>= 1)
        {
            if(l < r)
            {
                if(l & 1) left_val = left_val + data[l++];
                if(r & 1) right_val = data[--r] + right_val;
            }
            if(first >>= 1, last >>= 1)
            {
                lazy[first].apply(left_val);
                lazy[last].apply(right_val);
            }
        }
        return left_val + right_val;
    }

    template <class pred_type>
    size_type left_search(size_type right, const pred_type pred)
    {
        assert(right <= size_orig);
        right += size_ext - 1;
        for(size_type i{height}; i; --i) push(right >> i);
        ++right;
        monoid mono{};
        for(size_type left{size_ext}; left != right; left >>= 1, right >>= 1)
        {
            if((left & 1) != (right & 1))
            {
                const monoid tmp = data[--right] + mono;
                if(!pred(tmp)) return left_search_subtree(right, pred, mono);
                mono = tmp;
            }
        }
        return 0;
    }

    template <class pred_type>
    size_type right_search(size_type left, const pred_type pred)
    {
        assert(left <= size_orig);
        left += size_ext;
        for(size_type i{height}; i; --i) push(left >> i);
        monoid mono{};
        for(size_type right{size_ext << 1}; left != right; left >>= 1, right >>= 1)
        {
            if((left & 1) != (right & 1))
            {
                const monoid tmp = mono + data[left];
                if(!pred(tmp)) return right_search_subtree(left, pred, mono);
                mono = tmp;
                ++left;
            }
        }
        return size_orig;
    }
}; //class lazy_segment_tree
#line 3 "modulus/modint.hpp"
#include <iostream>
template <int_fast64_t mod = 0> // compile-time defined modulo.
struct modint
{
    static_assert(mod > 0);
    template <bool i32, class = void> struct modif { using value_type = int_least32_t; };
    template <class void_t> struct modif<false, void_t> { using value_type = int_least64_t; };
    using value_type = typename modif<mod < (1 << 30)>::value_type;
    constexpr static modint one() noexcept { return 1; }
    constexpr operator value_type() const noexcept { return value; }
    constexpr modint() noexcept = default;
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    constexpr modint(int_type n) noexcept : value((n %= mod) < 0 ? mod + n : n) {}
    constexpr modint operator++(int) noexcept { modint t{*this}; return operator+=(1), t; }
    constexpr modint operator--(int) noexcept { modint t{*this}; return operator-=(1), t; }
    constexpr modint &operator++() noexcept { return operator+=(1); }
    constexpr modint &operator--() noexcept { return operator-=(1); }
    constexpr modint operator-() const noexcept { return value ? mod - value : 0; }
    constexpr modint &operator+=(const modint &rhs) noexcept { return (value += rhs.value) < mod ? 0 : value -= mod, *this; }
    constexpr modint &operator-=(const modint &rhs) noexcept { return (value += mod - rhs.value) < mod ? 0 : value -= mod, *this; }
    constexpr modint &operator*=(const modint &rhs) noexcept { return value = (int_fast64_t)value * rhs.value % mod, *this; }
    constexpr modint &operator/=(const modint &rhs) noexcept { return operator*=(rhs.inverse()); }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    constexpr modint operator+(const int_type &rhs) const noexcept { return modint{*this} += rhs; }
    constexpr modint operator+(const modint &rhs) const noexcept { return modint{*this} += rhs; }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    constexpr modint operator-(const int_type &rhs) const noexcept { return modint{*this} -= rhs; }
    constexpr modint operator-(const modint &rhs) const noexcept { return modint{*this} -= rhs; }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    constexpr modint operator*(const int_type &rhs) const noexcept { return modint{*this} *= rhs; }
    constexpr modint operator*(const modint &rhs) const noexcept { return modint{*this} *= rhs; }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    constexpr modint operator/(const int_type &rhs) const noexcept { return modint{*this} /= rhs; }
    constexpr modint operator/(const modint &rhs) const noexcept { return modint{*this} /= rhs; }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    constexpr friend modint operator+(const int_type &lhs, const modint &rhs) noexcept { return modint(lhs) + rhs; }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    constexpr friend modint operator-(const int_type &lhs, const modint &rhs) noexcept { return modint(lhs) - rhs; }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    constexpr friend modint operator*(const int_type &lhs, const modint &rhs) noexcept { return modint(lhs) * rhs; }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    constexpr friend modint operator/(const int_type &lhs, const modint &rhs) noexcept { return modint(lhs) / rhs; }
    constexpr modint inverse() const noexcept
    {
        assert(value);
        value_type a{mod}, b{value}, u{}, v{1}, t{};
        while(b) t = a / b, a ^= b ^= (a -= t * b) ^= b, u ^= v ^= (u -= t * v) ^= v;
        return {u};
    }
    constexpr static modint pow(modint rhs, int_fast64_t e) noexcept
    {
        if(e < 0) e = e % (mod - 1) + mod - 1;
        modint res{1};
        while(e) { if(e & 1) res *= rhs; rhs *= rhs, e >>= 1; }
        return res;
    }
    friend std::ostream &operator<<(std::ostream &os, const modint &rhs) noexcept { return os << rhs.value; }
    friend std::istream &operator>>(std::istream &is, modint &rhs) noexcept { value_type value; rhs = (is >> value, value); return is; }
protected:
    value_type value = 0;
}; // class modint
template <> // runtime defined modulo as default(mod = 0).
struct modint<0>
{
    using value_type = int_fast64_t;
    static value_type &mod() noexcept { static value_type mod{}; return mod; }
    static modint one() noexcept { return 1; }
    operator value_type() const noexcept { return value; }
    modint() noexcept = default;
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    modint(int_type n) noexcept : value{ (assert(mod()), n %= mod()) < 0 ? n + mod() : n} {}
    modint operator++(int) noexcept { modint t{*this}; return operator+=(1), t; }
    modint operator--(int) noexcept { modint t{*this}; return operator-=(1), t; }
    modint &operator++() noexcept { return operator+=(1); }
    modint &operator--() noexcept { return operator-=(1); }
    modint operator-() const noexcept { return value ? mod() - value : 0; }
    modint &operator+=(const modint &rhs) noexcept { return (value += rhs.value) < mod() ? 0 : value -= mod(), *this; }
    modint &operator-=(const modint &rhs) noexcept { return (value += mod() - rhs.value) < mod() ? 0 : value -= mod(), *this; }
    modint &operator*=(const modint &rhs) noexcept { return (value *= rhs.value) %= mod(), *this; }
    modint &operator/=(const modint &rhs) noexcept { return operator*=(rhs.inverse()); }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    modint operator+(const int_type &rhs) const noexcept { return modint{*this} += rhs; }
    modint operator+(const modint &rhs) const noexcept { return modint{*this} += rhs; }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    modint operator-(const int_type &rhs) const noexcept { return modint{*this} -= rhs; }
    modint operator-(const modint &rhs) const noexcept { return modint{*this} -= rhs; }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    modint operator*(const int_type &rhs) const noexcept { return modint{*this} *= rhs; }
    modint operator*(const modint &rhs) const noexcept { return modint{*this} *= rhs; }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    modint operator/(const int_type &rhs) const noexcept { return modint{*this} /= rhs; }
    modint operator/(const modint &rhs) const noexcept { return modint{*this} /= rhs; }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    friend modint operator+(const int_type &lhs, const modint &rhs) noexcept { return modint(lhs) + rhs; }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    friend modint operator-(const int_type &lhs, const modint &rhs) noexcept { return modint(lhs) - rhs; }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    friend modint operator*(const int_type &lhs, const modint &rhs) noexcept { return modint(lhs) * rhs; }
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    friend modint operator/(const int_type &lhs, const modint &rhs) noexcept { return modint(lhs) / rhs; }
    modint inverse() const noexcept
    {
        assert(mod() && value);
        long long a{mod()}, b{value}, u{}, v{1}, t{};
        while(b) t = a / b, a ^= b ^= (a -= t * b) ^= b, u ^= v ^= (u -= t * v) ^= v;
        return {u};
    }
    static modint pow(modint rhs, int_fast64_t e) noexcept
    {
        if(e < 0) e = e % (mod() - 1) + mod() - 1;
        modint res{1};
        while(e) { if(e & 1) res *= rhs; rhs *= rhs, e >>= 1; }
        return res;
    }
    friend std::ostream &operator<<(std::ostream &os, const modint &rhs) noexcept { return os << rhs.value; }
    friend std::istream &operator>>(std::istream &is, modint &rhs) noexcept { long long value; rhs = modint((is >> value, value)); return is; }
protected:
    value_type value = 0;
}; // class modint<0>
using modint_runtime = modint<0>;
#line 4 "test/library-checker/range_affine_range_sum.test.cpp"
#include <cstdio>

int main()
{
    using mint=modint<998244353>;
    struct mono
    {
        mint v,c;
        mono operator+(mono rhs) const
        {
            return {v+rhs.v,c+rhs.c};
        }
    };
    struct endo
    {
        mint a=1,b;
        endo &operator*=(endo rhs)
        {
            a*=rhs.a;
            b=b*rhs.a+rhs.b;
            return *this;
        }
        void apply(mono& rhs) const
        {
            rhs.v*=a;
            rhs.v+=rhs.c*b;
        }
    };
    int n,q;
    scanf("%d%d",&n,&q);
    lazy_segment_tree<mono,endo> seg;
    {
        std::vector<mono> a(n);
        for(auto &[v,c]: a)
        {
            int _v;
            scanf("%d",&_v);
            v=_v;
            c=1;
        }
        seg=a;
    }
    for(int t,l,r,a,b; q--; )
    {
        scanf("%d%d%d",&t,&l,&r);
        if(t)
        {
            printf("%d\n",seg.fold(l,r).v);
        }
        else
        {
            scanf("%d%d",&a,&b);
            seg.update(l,r,{a,b});
        }
    }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

