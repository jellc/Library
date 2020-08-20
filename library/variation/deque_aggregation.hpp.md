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


# :warning: variation/deque_aggregation.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#64037a31cae3aa224737c3dcdfb7bd46">variation</a>
* <a href="{{ site.github.repository_url }}/blob/master/variation/deque_aggregation.hpp">View this file on GitHub</a>
    - Last commit date: 2020-08-21 02:00:03+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <cassert>
#include <iterator>
#include <vector>
// implementation with std::vector
template <class monoid>
class deque_aggregation
{
    struct data { monoid value, acc; };

    template <bool left_operand_added>
    struct stack_aggregation : public std::vector<data>
    {
        using base = std::vector<data>;
        bool top_referred = false;

        void recalc()
        {
            if(top_referred)
            {
                assert(!base::empty());
                top_referred = false;
                monoid top_val{top().value};
                pop();
                push(top_val);
            }
        }

        // copy of the element at the index.
        data operator[](size_t index) const
        {
            assert(index < base::size());
            recalc();
            return base::operator[](index);
        }

        // reference to the last element
        data &top()
        {
            assert(!base::empty());
            top_referred = true;
            return base::back();
        }

        void pop()
        {
            assert(!base::empty());
            top_referred = false;
            base::pop_back();
        }

        void push(const monoid &mono)
        {
            recalc();
            if(left_operand_added) base::push_back({mono, mono + fold()});
            else base::push_back({mono, fold() + mono});
        }

        monoid fold()
        {
            if(base::empty()) return monoid();
            recalc();
            return base::back().acc;
        }
    }; // class stack_aggregation

    stack_aggregation<true> left;
    stack_aggregation<false> right;

    void share_right()
    {
        if(!left.empty() || right.empty()) return;
        left.recalc(); right.recalc();
        auto mid = right.begin() + (right.size() + 1) / 2;
        for(auto itr = mid; itr != right.begin(); ) left.push((--itr)->value);
        right.erase(right.begin(), mid);
        monoid nacc;
        for(auto &[value, acc] : right) nacc = acc = nacc + value;
    }

    void share_left()
    {
        if(!right.empty() || left.empty()) return;
        left.recalc(); right.recalc();
        auto mid = left.begin() + (left.size() + 1) / 2;
        for(auto itr = mid; itr != left.begin(); ) right.push((--itr)->value);
        left.erase(left.begin(), mid);
        monoid nacc;
        for(auto &[value, acc] : left) nacc = acc = nacc + value;
    }

public:
    bool empty() const { return left.empty() && right.empty(); }
    size_t size() const { return left.size() + right.size(); }

    // reference to the first element.
    monoid &front() { assert(!empty()); return share_right(), left.top().value; }

    // reference to the last element.
    monoid &back() { assert(!empty()); return share_left(), right.top().value; }

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
        share_right();
        left.pop();
    }

    void pop_back()
    {
        assert(!empty());
        share_left();
        right.pop();
    }

    monoid fold() { return left.fold() + right.fold(); }
}; // class deque_aggregation

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "variation/deque_aggregation.hpp"
#include <cassert>
#include <iterator>
#include <vector>
// implementation with std::vector
template <class monoid>
class deque_aggregation
{
    struct data { monoid value, acc; };

    template <bool left_operand_added>
    struct stack_aggregation : public std::vector<data>
    {
        using base = std::vector<data>;
        bool top_referred = false;

        void recalc()
        {
            if(top_referred)
            {
                assert(!base::empty());
                top_referred = false;
                monoid top_val{top().value};
                pop();
                push(top_val);
            }
        }

        // copy of the element at the index.
        data operator[](size_t index) const
        {
            assert(index < base::size());
            recalc();
            return base::operator[](index);
        }

        // reference to the last element
        data &top()
        {
            assert(!base::empty());
            top_referred = true;
            return base::back();
        }

        void pop()
        {
            assert(!base::empty());
            top_referred = false;
            base::pop_back();
        }

        void push(const monoid &mono)
        {
            recalc();
            if(left_operand_added) base::push_back({mono, mono + fold()});
            else base::push_back({mono, fold() + mono});
        }

        monoid fold()
        {
            if(base::empty()) return monoid();
            recalc();
            return base::back().acc;
        }
    }; // class stack_aggregation

    stack_aggregation<true> left;
    stack_aggregation<false> right;

    void share_right()
    {
        if(!left.empty() || right.empty()) return;
        left.recalc(); right.recalc();
        auto mid = right.begin() + (right.size() + 1) / 2;
        for(auto itr = mid; itr != right.begin(); ) left.push((--itr)->value);
        right.erase(right.begin(), mid);
        monoid nacc;
        for(auto &[value, acc] : right) nacc = acc = nacc + value;
    }

    void share_left()
    {
        if(!right.empty() || left.empty()) return;
        left.recalc(); right.recalc();
        auto mid = left.begin() + (left.size() + 1) / 2;
        for(auto itr = mid; itr != left.begin(); ) right.push((--itr)->value);
        left.erase(left.begin(), mid);
        monoid nacc;
        for(auto &[value, acc] : left) nacc = acc = nacc + value;
    }

public:
    bool empty() const { return left.empty() && right.empty(); }
    size_t size() const { return left.size() + right.size(); }

    // reference to the first element.
    monoid &front() { assert(!empty()); return share_right(), left.top().value; }

    // reference to the last element.
    monoid &back() { assert(!empty()); return share_left(), right.top().value; }

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
        share_right();
        left.pop();
    }

    void pop_back()
    {
        assert(!empty());
        share_left();
        right.pop();
    }

    monoid fold() { return left.fold() + right.fold(); }
}; // class deque_aggregation

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

