#include <cassert>
#include <list>
#include <vector>

// Base class of flow algorithms
template <class cap_t, class cost_t>
struct flow_base
{
    class adj_type;

    class edge_t
    {
        friend class adj_type;
        edge_t *link;
    public:
        size_t src, dst;
        cap_t cap; cost_t cost;
        edge_t *rev;
        edge_t() : link() {}
        edge_t(edge_t *link, size_t src, size_t dst, cap_t cap, cost_t cost, edge_t *rev)
            : link(link), src(src), dst(dst), cap(cap), cost(cost), rev(rev) {}
    }; // class edge_t

    class adj_type
    {
        friend flow_base;
        edge_t *_head, *_next, *_last;
        size_t _len;

        template <class ...Args>
        edge_t *emplace(Args&&... args)
        {
            if(_next == _last)
            {
                _len <<= 1;
                _next = new edge_t[_len];
                _last = _next + _len;
            }
            *_next = edge_t(_head, args...);
            _head = _next;
            ++_next;
            return _head;
        }

    public:
        adj_type() : _head(), _next(new edge_t[1]), _last(_next + 1), _len(1) {}
        ~adj_type()
        {
            --_last, --_len;
            for(edge_t *_p; _len; _last = _p, _len >>= 1)
            {
                _last -= _len;
                _p = _last->link;
                delete[] _last;
            }
        }

        class iterator
        {
            edge_t *ptr;
        public:
            iterator(edge_t *ptr = nullptr) : ptr(ptr) {}
            iterator operator++() { ptr = ptr->link; return *this; }
            bool operator!=(const iterator &other) const { return ptr != other.ptr; }
            edge_t &operator*() const { return *ptr; }
        };

        iterator begin() const { return iterator(_head); }
        iterator end() const { return iterator(); }
    }; // class adj_type

protected:
    std::vector<adj_type> adjs;

public:
    flow_base(size_t _n = 0) : adjs(_n) {}

    flow_base(const flow_base& other) : adjs(other.size())
    {
        for(size_t node{}; node != size(); ++node)
        {
            for(const edge_t &e : other[node])
            {
                if(e.src == node)
                {
                    edge_t *ptr = adjs[e.src].emplace(e.src, e.dst, e.cap, e.cost, nullptr);
                    ptr->rev = adjs[e.dst].emplace(e.dst, e.src, e.rev->cap, -e.cost, ptr);
                    e.rev->src = -1;
                }
                else
                {
                    e.rev->rev->src = node;
                }
            }
        }
    }

    flow_base &operator=(const flow_base &other)
    {
        if(this != &other)
        {
            flow_base cop(other);
            std::swap(adjs, cop.adjs);
        }
        return *this;
    }

    size_t size() const { return adjs.size(); }

    typename decltype(adjs)::reference operator[](size_t node) { assert(node < size()); return adjs[node]; }
    typename decltype(adjs)::const_reference operator[](size_t node) const { assert(node < size()); return adjs[node]; }

    void add_edge(size_t src, size_t dst, cap_t cap, cost_t cost)
    {
        assert(src < size()); assert(dst < size());
        if(!(cap > 0)) return;
        edge_t *ptr = adjs[src].emplace(src, dst, cap, cost, nullptr);
        ptr->rev = adjs[dst].emplace(dst, src, 0, -cost, ptr);
    }
}; // struct flow_base
