// verified at https://judge.yosupo.jp/submission/2812.
#ifndef DEQUE_AGGREGATION_HPP
#define DEQUE_AGGREGATION_HPP

template <class Monoid>
class deque_aggregation
{
    using value_type = typename Monoid::value_type;
    Monoid *const monoid_ptr, &monoid;

    template <bool left_operand_added>
    class stack_aggregation
    {
        friend deque_aggregation;
        Monoid &monoid;
        struct data { value_type value, acc; };
        size_t capacity;
        data *stack, *end, *itr;
        bool top_referred;
        void recalc()
        {
            if(top_referred)
            {
                assert(itr != stack);
                top_referred = false;
                value_type top_val(top().value);
                pop();
                push(top_val);
            }
        }
      public:
        stack_aggregation(Monoid &_monoid) : monoid(_monoid), capacity(1), stack(new data[1]), end(std::next(stack)), itr(stack), top_referred() {}
        ~stack_aggregation() { delete[] stack; }
        bool empty() const { return stack == itr; }
        size_t size() const { return itr - stack; }
        // copy of the element at position i.
        data operator[](size_t i) const
        {
            assert(i < size());
            recalc();
            return stack[i];
        }
        // reference to the last element
        data &top()
        {
            assert(itr != stack);
            top_referred = true;
            return *std::prev(itr);
        }
        value_type fold()
        {
            if(itr == stack) return monoid.identity();
            recalc();
            return std::prev(itr)->acc;
        }
        void pop()
        {
            assert(itr != stack);
            --itr;
            top_referred = false;
        }
        void push(const value_type &x)
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
            if(left_operand_added) *itr = data{x, monoid(x, fold())};
            else *itr = data{x, monoid(fold(), x)};
            ++itr;
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
        value_type acc = monoid.identity();
        for(auto *p = right.stack + mid; p != right.itr; ++p, ++itr)
        {
            *itr = {p->value, acc = monoid(acc, p->value)};
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
        value_type acc = monoid.identity();
        for(auto *p = left.stack + mid; p != left.itr; ++p, ++itr)
        {
            *itr = {p->value, acc = monoid(p->value, acc)};
        }
        left.itr = itr;
    }

  public:
    deque_aggregation() : monoid_ptr(new Monoid), monoid(*monoid_ptr), left(monoid), right(monoid) {}
    deque_aggregation(Monoid &_monoid) : monoid_ptr(), monoid(_monoid), left(monoid), right(monoid) {}
    ~deque_aggregation() { delete monoid_ptr; }

    bool empty() const { return left.empty() && right.empty(); }
    size_t size() const { return left.size() + right.size(); }

    // reference to the first element.
    value_type &front() { assert(!empty()); return balance_to_left(), left.top().value; }
    // reference to the last element.
    value_type &back() { assert(!empty()); return balance_to_right(), right.top().value; }

    // copy of the element at position i.
    value_type operator[](size_t i) const
    {
        assert(i < left.size() + right.size());
        return i < left.size() ? left[i].value : right[i - left.size()].value;
    }

    value_type fold() { return monoid(left.fold(), right.fold()); }

    void push_front(const value_type &x) { left.push(x); }
    void push_back(const value_type &x) { right.push(x); }

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
}; // class deque_aggregation

#endif