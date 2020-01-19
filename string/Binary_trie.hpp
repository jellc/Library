// verified at https://atcoder.jp/contests/dwacon5th-final/submissions/7200502
#ifdef Binary_trie_hpp
#define Binary_trie_hpp
#include <cassert>
#include <iterator>

template <size_t depth, class int_type = int_least64_t>
class binary_trie
{
    struct node
    {
        bool tag;
        node *par, *lft, *rgt;
        size_t digit;
        size_t cnt, typ;
        node() : tag(), par(), lft(), rgt(), digit(depth), cnt(), typ() {}
        node(bool _tag, node *p) : tag(_tag), par(p), lft(), rgt(), digit((int)p->digit - 1), cnt(), typ() {}
    /*/
        ~node() { delete lft, delete rgt; }
        friend node *alloc(bool _tag, node *p)
        {
            return new node(_tag, p);
        }
    /*/
        friend node *alloc(bool _tag, node *p)
        {
            constexpr size_t nodemax = 1.5e6;
            static node stock[nodemax];
            static size_t node_cnt = 0;
            return &(stock[node_cnt++] = node(_tag, p));
        }
    //*/
        friend bool valid(node *p) { return p and p->cnt; }
    } *const root;

    // node *root;
    static_assert(depth != 0, "depth must be a positive integer.");
    int_type power[depth];
    bool bit(int_type x, size_t i) const { return x & power[i]; }

public:
    binary_trie() : root(new node) { power[depth - 1] = 1; for(size_t i = depth - 1; i--; ) power[i] = power[i + 1] << 1; }
    ~binary_trie() { delete root; }

    size_t size() const { return root->cnt; }
    size_t type() const { return root->typ; }

    bool insert(int_type x)
    {
        node *p = root;
        for(size_t i = 0; i < depth; ++i)
        {
            p->cnt++;
            if(bit(x, i))
            {
                if(not p->rgt) p->rgt = alloc(1, p);
                p = p->rgt;
            }
            else
            {
                if(not p->lft) p->lft = alloc(0, p);
                p = p->lft;
            }
        }
        if(p->cnt++) return false;
        while(p)
        {
            p->typ++;
            p = p->par;
        }
        return true;
    }

    size_t erase(int_type x, size_t k = 1)
    {
        node *p = root;
        for(size_t i = 0; i < depth; ++i)
        {
            if(bit(x, i))
            {
                if(not p->rgt) return 0;
                p = p->rgt;
            }
            else
            {
                if(not p->lft) return 0;
                p = p->lft;
            }
        }
        bool uni_typ = k >= p->cnt;
        if(uni_typ) k = p->cnt;
        while(p)
        {
            p->cnt -= k;
            p->typ -= uni_typ;
            p = p->par;
        }
        return k;
    }

    size_t count(int_type x) const
    {
        node *p = root;
        for(size_t i = 0; i < depth; ++i)
        {
            if(bit(x, i))
            {
                if(not p->rgt) return 0;
                p = p->rgt;
            }
            else
            {
                if(not p->lft) return 0;
                p = p->lft;
            }
        }
        return p->cnt;
    }

    int_type closest(int_type x) const
    {
        assert(size());
        node *p = root;
        int_type ret = 0;
        for(size_t i = 0; i != depth; ++i)
        {
            if(bit(x, i))
            {
                if(valid(p->rgt))
                {
                    p = p->rgt;
                    ret += power[i];
                }
                else
                {
                    p = p->lft;
                }
            }
            else
            {
                if(p->lft && p->lft->cnt)
                {
                    p = p->lft;
                }
                else
                {
                    p = p->rgt;
                    ret += power[i];
                }
            }
        }
        return ret;
    }

    int_type operator[](size_t idx) const
    {
        assert(idx < size());
        node *p = root;
        int_type ret = 0;
        for(size_t i = 0; i < depth; ++i)
        {
            size_t thr = p->lft ? p->lft->cnt : 0;
            if(idx < thr)
            {
                p = p->lft;
            }
            else
            {
                idx -= thr;
                p = p->rgt;
                ret += power[i];
            }
        }
        return ret;
    }

    struct iterator_type : std::iterator<std::bidirectional_iterator_tag, int_type, std::ptrdiff_t, node *, int_type>
    {
        binary_trie *const trie_ptr;
        node *node_ptr;
        int_type s;
        size_t type_idx, size_idx;

        iterator_type()
            : trie_ptr(), node_ptr(), s(), type_idx(-1), size_idx(-1)
        {}

        iterator_type(const iterator_type &itr)
            : trie_ptr(itr.trie_ptr), node_ptr(itr.node_ptr), s(itr.s),
            type_idx(itr.type_idx), size_idx(itr.size_idx)
        {}

        iterator_type(binary_trie *_trie_ptr, size_t _type_idx)
            : trie_ptr(_trie_ptr), node_ptr(), s(), type_idx(_type_idx),
            size_idx()
        {
            if(_type_idx < trie_ptr->type())
            {
                node *&p = (node_ptr = trie_ptr->root);
                for(size_t i = 0; i < depth; ++i)
                {
                    if(valid(p->lft))
                    {
                        if(_type_idx < p->lft->typ)
                        {
                            p = p->lft;
                        }
                        else
                        {
                            _type_idx -= p->lft->typ;
                            size_idx += p->lft->cnt;
                            p = p->rgt;
                            s += trie_ptr->power[i];
                        }
                    }
                    else
                    {
                        p = p->rgt;
                        s += trie_ptr->power[i];
                    }
                }
            }
            else
            {
                size_idx = trie_ptr->size();
            }
        }

        iterator_type(binary_trie *_trie_ptr, node *_node_ptr, int_type _s,
                            size_t _type_idx, size_t _size_idx)
            : trie_ptr(_trie_ptr), node_ptr(_node_ptr), s(_s),
            type_idx(_type_idx), size_idx(_size_idx)
        {}

        node *operator->() const { return node_ptr; }

        int_type operator*() const { return s; }

        bool operator==(const iterator_type &itr) const
        {
            return trie_ptr == itr.trie_ptr and type_idx == itr.type_idx;
        }

        bool operator!=(const iterator_type &itr) const { return not(*this == itr); }

        iterator_type &operator++()
        {
            size_idx += count();
            node *p = node_ptr;
            size_t i = depth;
            while(i--)
            {
                bool t = p->tag;
                p = p->par;
                if(t)
                {
                    s -= trie_ptr->power[i];
                }
                else if(valid(p->rgt))
                {
                    s += trie_ptr->power[i];
                    p = p->rgt;
                    break;
                }
            }
            if(p->digit == depth)
            {
                node_ptr = nullptr;
            }
            else
            {
                while(++i < depth)
                {
                    if(valid(p->lft))
                    {
                        p = p->lft;
                    }
                    else
                    {
                        p = p->rgt;
                        s += trie_ptr->power[i];
                    }
                }
                node_ptr = p;
            }
            ++type_idx;
            return *this;
        }

        iterator_type &operator++(int)
        {
            iterator_type ret = *this;
            return ++(*this), ret;
        }

        iterator_type &operator--()
        {
            if(*this == trie_ptr->end())
            {
                node *p = trie_ptr->root;
                if(valid(p))
                {
                    for(size_t i = 0; i < depth; ++i)
                    {
                        if(valid(p->rgt))
                        {
                            p = p->rgt;
                            s += trie_ptr->power[i];
                        }
                        else
                        {
                            p = p->lft;
                        }
                    }
                    node_ptr = p;
                }
            }
            else
            {
                node *p = node_ptr;
                size_t i = depth;
                while(i--)
                {
                    bool t = p->tag;
                    p = p->par;
                    if(t)
                    {
                        s -= trie_ptr->power[i];
                        if(valid(p->lft))
                        {
                            p = p->lft;
                            break;
                        }
                    }
                }

                if(p->digit == depth)
                {
                    node_ptr = nullptr;
                }
                else
                {
                    while(++i < depth)
                    {
                        if(valid(p->rgt))
                        {
                            p = p->rgt;
                            s += trie_ptr->power[i];
                        }
                        else
                        {
                            p = p->lft;
                        }
                    }
                    node_ptr = p;
                }
            }
            --type_idx;
            if(node_ptr)
                size_idx -= node_ptr->cnt;
            else
                size_idx = -1;
            return *this;
        }

        iterator_type &operator--(int)
        {
            iterator_type ret = *this;
            return --(*this), ret;
        }

        size_t count() const
        {
            return node_ptr ? node_ptr->cnt : 0;
        }
    }; // struct iterator_type

    friend iterator_type;

    iterator_type begin() { return iterator_type(this, 0); }
    iterator_type end() { return iterator_type(this, type()); }
    std::reverse_iterator<iterator_type> rbegin() { return std::reverse_iterator<iterator_type>(end()); }
    std::reverse_iterator<iterator_type> rend() { return std::reverse_iterator<iterator_type>(begin()); }

    iterator_type lower_bound(int_type key)
    {
        size_t size_idx = 0, type_idx = 0, i = 0;
        node *p = root;
        int_type s = 0;
        bool go_back = false;
        for(; i < depth; ++i)
        {
            if(bit(key, i))
            {
                if(valid(p->lft))
                {
                    size_idx += p->lft->cnt;
                    type_idx += p->lft->typ;
                }
                if(valid(p->rgt))
                {
                    p = p->rgt;
                    s += power[i];
                }
                else
                {
                    go_back = true;
                    break;
                }
            }
            else
            {
                if(valid(p->lft))
                {
                    p = p->lft;
                }
                else
                {
                    if(valid(p->rgt))
                    {
                        s += power[i];
                        p = p->rgt;
                        break;
                    }
                    else
                    {
                        go_back = true;
                        break;
                    }
                }
            }
        }
        if(go_back)
        {
            while(i--)
            {
                bool t = p->tag;
                p = p->par;
                if(t)
                {
                    s -= power[i];
                }
                else if(valid(p->rgt))
                {
                    s += power[i];
                    p = p->rgt;
                    break;
                }
            }
            if(p->digit == depth) return end();
        }
        while(++i < depth)
        {
            if(valid(p->lft))
            {
                p = p->lft;
            }
            else
            {
                p = p->rgt;
                s += power[i];
            }
        }
        return iterator_type(this, p, s, type_idx, size_idx);
    }

    iterator_type upper_bound(int_type key)
    {
        auto itr = lower_bound(key);
        if(*itr == key) ++itr;
        return itr;
    }
}; // class binary_trie

#endif // Binary_trie_hpp