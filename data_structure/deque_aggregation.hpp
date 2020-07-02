#include <cassert>
#include <iterator>

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
    monoid &front() { assert(!empty()); return balance_to_left(), left.top().value; }

    // reference to the last element.
    monoid &back() { assert(!empty()); return balance_to_right(), right.top().value; }

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
