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


# :heavy_check_mark: test/library-checker/queue_operate_all_composite.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#8a40f8ed03f4cdb6c2fe0a2d4731a143">test/library-checker</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/library-checker/queue_operate_all_composite.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-08-24 22:40:12+09:00


* see: <a href="https://judge.yosupo.jp/problem/queue_operate_all_composite">https://judge.yosupo.jp/problem/queue_operate_all_composite</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/data_structure/deque_aggregation.hpp.html">data_structure/deque_aggregation.hpp</a>
* :heavy_check_mark: <a href="../../../library/modulus/modint.hpp.html">modulus/modint.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/queue_operate_all_composite"
#include "data_structure/deque_aggregation.hpp"
#include "modulus/modint.hpp"
#include <cstdio>

int main()
{
    using mint=modint<998244353>;
    struct mono
    {
        mint a=1,b;
        mono operator+(const mono& rhs) const
        {
            auto [c,d]=rhs;
            return {a*c,b*c+d};
        }
    };
    deque_aggregation<mono> deq;
    int q; scanf("%d",&q);
    while(q--)
    {
        int t; scanf("%d",&t);
        if(t==0)
        {
            int a,b; scanf("%d%d",&a,&b);
            deq.push_back({a,b});
        }
        else if(t==1)
        {
            deq.pop_front();
        }
        else
        {
            int x; scanf("%d",&x);
            auto [a,b]=deq.fold();
            printf("%d\n",a*x+b);
        }
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/library-checker/queue_operate_all_composite.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/queue_operate_all_composite"
#line 2 "data_structure/deque_aggregation.hpp"
#include <cassert>
#include <iterator>
// implementation with dynamic memory allocation.
template <class monoid>
class deque_aggregation
{
    template <bool left_operand_added>
    class stack_aggregation
    {
        friend deque_aggregation;
        struct data { monoid value, acc; };
        size_t capacity;
        data *stack, *end, *itr;
        bool top_referred;

        void recalc()
        {
            if(top_referred)
            {
                assert(itr != stack);
                top_referred = false;
                monoid top_val{top().value};
                pop();
                push(top_val);
            }
        }

    public:
        stack_aggregation() : capacity(1), stack(new data[1]), end(std::next(stack)), itr(stack), top_referred() {}
        ~stack_aggregation() { delete[] stack; }

        bool empty() const { return stack == itr; }
        size_t size() const { return itr - stack; }

        // copy of the element at the index.
        data operator[](size_t index) const
        {
            assert(index < size());
            recalc();
            return stack[index];
        }

        // reference to the last element
        data &top()
        {
            assert(itr != stack);
            top_referred = true;
            return *std::prev(itr);
        }

        void pop()
        {
            assert(itr != stack);
            --itr;
            top_referred = false;
        }

        void push(const monoid &mono)
        {
            recalc();
            if(itr == end)
            {
                data *tmp = new data[capacity << 1];
                std::swap(stack, tmp);
                end = (itr = std::copy(tmp, tmp + capacity, stack)) + capacity;
                capacity <<= 1;
                delete[] tmp;
            }
            if(left_operand_added) *itr = data{mono, mono + fold()};
            else *itr = data{mono, fold() + mono};
            ++itr;
        }

        monoid fold()
        {
            if(itr == stack) return monoid();
            recalc();
            return std::prev(itr)->acc;
        }
    }; // class stack_aggregation

    stack_aggregation<true> left;
    stack_aggregation<false> right;

    void balance_to_left()
    {
        if(!left.empty() || right.empty()) return;
        left.recalc(); right.recalc();
        size_t mid = (right.size() + 1) >> 1;
        auto *itr = right.stack + mid;
        do { left.push((--itr)->value); } while(itr != right.stack);
        monoid acc;
        for(auto *p = right.stack + mid; p != right.itr; ++p, ++itr)
        {
            *itr = {p->value, acc = acc + p->value};
        }
        right.itr = itr;
    }

    void balance_to_right()
    {
        if(!right.empty() || left.empty()) return;
        left.recalc(); right.recalc();
        size_t mid = (left.size() + 1) >> 1;
        auto *itr = left.stack + mid;
        do { right.push((--itr)->value); } while(itr != left.stack);
        monoid acc;
        for(auto *p = left.stack + mid; p != left.itr; ++p, ++itr)
        {
            *itr = {p->value, acc = p->value + acc};
        }
        left.itr = itr;
    }

public:
    bool empty() const { return left.empty() && right.empty(); }
    size_t size() const { return left.size() + right.size(); }

    // reference to the first element.
    monoid &front() { assert(!empty()); balance_to_left(); return left.top().value; }

    // reference to the last element.
    monoid &back() { assert(!empty()); balance_to_right(); return right.top().value; }

    // copy of the element at the index.
    monoid operator[](size_t index) const
    {
        assert(index < left.size() + right.size());
        return index < left.size() ? left[index].value : right[index - left.size()].value;
    }

    void push_front(const monoid &mono) { left.push(mono); }

    void push_back(const monoid &mono) { right.push(mono); }

    void pop_front()
    {
        assert(!empty());
        balance_to_left();
        left.pop();
    }

    void pop_back()
    {
        assert(!empty());
        balance_to_right();
        right.pop();
    }

    monoid fold() { return left.fold() + right.fold(); }
}; // class deque_aggregation
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
    friend std::istream &operator>>(std::istream &is, modint &rhs) noexcept { int_fast64_t value; rhs = (is >> value, value); return is; }
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
    modint(int_type n) noexcept : value{ (assert(mod()), n %= mod() < 0 ? n + mod() : n) } {}
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
        value_type a{mod()}, b{value}, u{}, v{1}, t{};
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
    friend std::istream &operator>>(std::istream &is, modint &rhs) noexcept { int_fast64_t value; rhs = modint((is >> value, value)); return is; }
protected:
    value_type value = 0;
}; // class modint<0>
using modint_runtime = modint<0>;
#line 4 "test/library-checker/queue_operate_all_composite.test.cpp"
#include <cstdio>

int main()
{
    using mint=modint<998244353>;
    struct mono
    {
        mint a=1,b;
        mono operator+(const mono& rhs) const
        {
            auto [c,d]=rhs;
            return {a*c,b*c+d};
        }
    };
    deque_aggregation<mono> deq;
    int q; scanf("%d",&q);
    while(q--)
    {
        int t; scanf("%d",&t);
        if(t==0)
        {
            int a,b; scanf("%d%d",&a,&b);
            deq.push_back({a,b});
        }
        else if(t==1)
        {
            deq.pop_front();
        }
        else
        {
            int x; scanf("%d",&x);
            auto [a,b]=deq.fold();
            printf("%d\n",a*x+b);
        }
    }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

