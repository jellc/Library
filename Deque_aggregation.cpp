template <class Monoid>
class ext_deque
{
    using opr_t = std::function<Monoid(const Monoid&, const Monoid&)>;
    const Monoid identity;
    const opr_t &opr;

    class ext_stack
    {
        const Monoid identity;
        const opr_t &opr;
        struct data { Monoid val, acc; };
        size_t n;
        data *stack, *end, *itr;
      public:
        ext_stack(Monoid _identity, const opr_t &_opr)
            : identity(_identity), opr(_opr), n(1), stack(new data[1]), end(std::next(stack)), itr(stack) {}
        ~ext_stack() { delete[] stack; }
        Monoid operator[](size_t i) const { assert(i < n); return stack[i].val; }
        Monoid top() const { return empty() ? identity : std::prev(itr)->val; }
        Monoid bot() const { return empty() ? identity : stack->val; }
        Monoid fold() const { return empty() ? identity : std::prev(itr)->acc; }
        bool empty() const { return stack == itr; }
        size_t size() const { return itr - stack; }
        void pop() { assert(itr != stack); --itr; }
        void push(Monoid x)
        {
            if(itr == end)
            {
                data *tmp = new data[n << 1];
                std::swap(stack, tmp);
                end = (itr = std::copy(tmp, tmp + n, stack)) + n;
                n <<= 1;
                delete[] tmp;
            }
            *itr = data{x, opr(fold(), x)}, ++itr;
        }
        friend ext_deque;
    };

    ext_stack sfront, sback;

  public:
    ext_deque(Monoid _identity, const opr_t &_opr)
        : identity(_identity), opr(_opr), sfront(identity, opr), sback(identity, opr) {}
    
    bool empty() const { return sfront.empty() && sback.empty(); }

    size_t size() const { return sfront.size() + sback.size(); }

    Monoid front() const { assert(!empty()); return sfront.empty() ? sback.bot() : sfront.top(); }

    Monoid back() const { assert(!empty()); return sback.empty() ? sfront.bot() : sback.top(); }

    Monoid operator[](size_t i) const { assert(i < sfront.size() + sback.size()); return i < sfront.size() ? sfront[i].val : sback[i - sfront.size()].val; }

    Monoid fold() const { return opr(sfront.fold(), sback.fold()); }

    void push_front(Monoid x) { sfront.push(x); }

    void push_back(Monoid x) { sback.push(x); }

    void pop_front()
    {
        assert(!empty());
        if(sfront.empty())
        {
            size_t n = sback.size();
            size_t mid = (n + 1) / 2;
            auto *itr = sback.stack + mid;
            do { sfront.push((--itr)->val); } while(itr != sback.stack);
            Monoid acc = identity;
            for(auto *p = sback.stack + mid; p != sback.itr; ++p, ++itr)
            {
                *itr = {p->val, acc = opr(acc, p->val)};
            }
            sback.itr = itr;
        }
        sfront.pop();
    }

    void pop_back()
    {
        assert(!empty());
        if(sback.empty())
        {
            size_t n = sfront.size();
            size_t mid = (n + 1) / 2;
            auto *itr = sfront.stack + mid;
            do { sback.push((--itr)->val); } while(itr != sfront.stack);
            Monoid acc = identity;
            for(auto *p = sfront.stack + mid; p != sfront.itr; ++p, ++itr)
            {
                *itr = {p->val, acc = opr(acc, p->val)};
            }
            sfront.itr = itr;
        }
        sback.pop();
    }
};