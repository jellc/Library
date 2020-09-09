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


# :x: data_structure/deque_aggregation.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/deque_aggregation.hpp">View this file on GitHub</a>
    - Last commit date: 2020-08-21 02:00:03+09:00




## Verified with

* :x: <a href="../../verify/test/library-checker/queue_operate_all_composite.test.cpp.html">test/library-checker/queue_operate_all_composite.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
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

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

