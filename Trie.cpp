// verified at https://codeforces.com/contest/1202/submission/59818756
#include <bits/stdc++.h>

template <class T, class seq_t = std::vector<T>>
struct Trie
{
    struct Aho_Corasick;

    struct node
    {
        const T tag;
        const bool tag_set, is_ter, is_root;
        node *const par, *ter;
        std::map<T, node *> child;
        size_t cnt, typ;

        explicit node()
            : tag(), tag_set(), is_ter(), is_root(true), par(), ter(), child(),
              cnt(), typ()
        {}

        explicit node(node *const p)
            : tag(), tag_set(), is_ter(true), is_root(), par(p), ter(), child(),
              cnt(), typ()
        {}

        explicit node(const T &_tag, node *const p)
            : tag(_tag), tag_set(true), is_ter(), is_root(), par(p), ter(),
              child(), cnt(), typ()
        {}

        ~node()
        {
            delete ter;
            for(auto &e : child)
                delete e.second;
        }

        node *add(const T &x)
        {
            node *&p = child[x];
            return p ? p : p = new node(x, this);
        }

        node *add()
        {
            return sfx_wrd++, ter ? ter : ter = new node(this);
        }

      private:
        friend bool valid(const node *const p)
        {
            return p and p->cnt and p->typ;
        }

        friend Aho_Corasick;

        node *failure = nullptr;

        size_t sfx_wrd = 0;
    };

    using dict_t = std::map<T, node *>;

    node *const root;

    explicit Trie() : root(new node)
    {}

#ifdef LOCAL
    ~Trie()
    {
        delete root;
    }
#endif

    size_t size() const
    {
        return root->cnt;
    }

    size_t type() const
    {
        return root->typ;
    }

    node *insert(const seq_t &s)
    {
        node *p = root;
        p->cnt++;
        for(const T &x : s)
        {
            (p = p->add(x))->cnt++;
        }
        node *ret = p = p->add();
        if(not p->cnt++)
        {
            while(p)
            {
                p->typ++;
                p = p->par;
            }
        }
        return ret;
    }

    size_t erase(const seq_t &s, size_t k = 1)
    {
        node *p = root;
        for(const T &x : s)
        {
            p = p->child[x];
            if(not p) return 0;
        }
        p = p->ter;
        if(not p) return 0;
        bool ext = k >= p->cnt;
        if(ext)
        {
            k = p->cnt;
            p->par->suf_wrd--;
        }
        while(p)
        {
            p->cnt -= k;
            p->typ -= ext;
            p = p->par;
        }
        return k;
    }

    size_t erase(size_t idx)
    {
        if(idx >= size()) return 0;
        node *p = root;
        while(true)
        {
            if(p->ter)
            {
                size_t here = p->ter->cnt;
                if(idx < here)
                {
                    p = p->ter;
                    break;
                }
                idx -= here;
            }
            node *nx = nullptr;
            for(const auto &e : p->child)
            {
                T x;
                node *t;
                tie(x, t) = e;
                size_t here = t ? t->cnt : 0;
                if(idx < here)
                {
                    nx = t;
                    break;
                }
                else
                {
                    idx -= here;
                }
            }
            p = nx;
        }
        bool ext = not--p->ter->cnt;
        while(p)
        {
            p->cnt--;
            p->typ -= ext;
            p = p->par;
        }
        return 1;
    }

    size_t count(const seq_t &s) const
    {
        node *p = root;
        for(const T &x : s)
        {
            p = p->child[x];
            if(!p->child[x]) return 0;
        }
        p = p->ter;
        return p ? p->cnt : 0;
    }

    // size_t lower_bound(const seq_t &s) const
    // {
    //     size_t ret = 0;
    //     node *p = root;
    //     for(const T &x : s)
    //     {
    //         if(not p) break;
    //         if(p->ter) ret += p->ter->cnt;
    //         for(const auto &e : p->child)
    //         {
    //             if(e.first == x) break;
    //             node *t = e.second;
    //             if(t) ret += t->cnt;
    //         }
    //         p = p->child[x];
    //     }
    //     return ret;
    // }
    //
    // size_t upper_bound(const seq_t &s) const
    // {
    //     size_t ret = 0;
    //     node *p = root;
    //     for(const T &x : s)
    //     {
    //         if(not p) break;
    //         if(p->ter) ret += p->ter->cnt;
    //         for(const auto &e : p->child)
    //         {
    //             if(e.first == x) break;
    //             node *t = e.second;
    //             if(t) ret += t->cnt;
    //         }
    //         p = p->child[x];
    //     }
    //     if(p and p->ter) ret += p->ter->cnt;
    //     return ret;
    // }

    seq_t operator[](size_t idx) const
    {
        assert(idx < size());
        node *p = root;
        seq_t ret = seq_t();
        while(true)
        {
            if(p->ter)
            {
                size_t here = p->ter->cnt;
                if(idx < here) break;
                idx -= here;
            }
            node *nx = nullptr;
            for(const auto &e : p->child)
            {
                T x;
                node *t;
                std::tie(x, t) = e;
                size_t here = t ? t->cnt : 0;
                if(idx < here)
                {
                    ret.push_back(x);
                    nx = t;
                    break;
                }
                idx -= here;
            }
            p = nx;
        }
        return ret;
    }

    struct iterator_t : std::iterator<std::bidirectional_iterator_tag, seq_t,
                                      std::ptrdiff_t, node *, seq_t>
    {
        Trie *const trie_ptr;
        node *node_ptr;
        seq_t s;
        size_t type_idx, size_idx;

        explicit iterator_t()
            : trie_ptr(), node_ptr(), s(), type_idx(-1), size_idx(-1)
        {}

        iterator_t(const iterator_t &itr)
            : trie_ptr(itr.trie_ptr), node_ptr(itr.node_ptr), s(itr.s),
              type_idx(itr.type_idx), size_idx(itr.size_idx)
        {}

        explicit iterator_t(Trie *_trie_ptr, size_t _type_idx)
            : trie_ptr(_trie_ptr), node_ptr(), s(), type_idx(_type_idx),
              size_idx()
        {
            if(_type_idx < trie_ptr->type())
            {
                node *&p = (node_ptr = trie_ptr->root);
                while(p)
                {
                    size_t here_typ = p->ter ? p->ter->typ : 0;
                    size_t here_cnt = p->ter ? p->ter->cnt : 0;
                    if(_type_idx < here_typ)
                    {
                        p = p->ter;
                        break;
                    }
                    _type_idx -= here_typ;
                    size_idx += here_cnt;
                    node *nx = nullptr;
                    for(const auto &e : p->child)
                    {
                        T x;
                        node *t;
                        std::tie(x, t) = e;
                        here_typ = t ? t->typ : 0;
                        here_cnt = t ? t->cnt : 0;
                        if(_type_idx < here_typ)
                        {
                            s.push_back(x);
                            nx = t;
                            break;
                        }
                        _type_idx -= here_typ;
                        size_idx += here_cnt;
                    }
                    p = nx;
                }
            }
            else
            {
                size_idx = trie_ptr->size();
            }
        }

        explicit iterator_t(Trie *_trie_ptr, node *_node_ptr, const seq_t &_s,
                            size_t _type_idx, size_t _size_idx)
            : trie_ptr(_trie_ptr), node_ptr(_node_ptr), s(_s),
              type_idx(_type_idx), size_idx(_size_idx)
        {}

        node *operator->() const
        {
            return node_ptr;
        }

        seq_t operator*() const
        {
            return s;
        }

        bool operator==(const iterator_t &itr) const
        {
            return trie_ptr == itr.trie_ptr and type_idx == itr.type_idx;
        }

        bool operator!=(const iterator_t &itr) const
        {
            return not(*this == itr);
        }

        iterator_t &operator++()
        {
            size_idx += count();
            node *p = node_ptr;
            while(p->par)
            {
                auto dict_itr = p->par->child.begin();
                if(not p->is_ter)
                {
                    dict_itr = p->par->child.upper_bound(p->tag);
                    s.pop_back();
                }
                p = p->par;
                while(dict_itr != p->child.end() and
                      not valid(dict_itr->second))
                    ++dict_itr;
                if(dict_itr != p->child.end())
                {
                    p = dict_itr->second;
                    s.push_back(p->tag);
                    break;
                }
            }
            if(p->is_root)
            {
                node_ptr = nullptr;
            }
            else
            {
                while(not valid(p->ter))
                {
                    node *nx = nullptr;
                    for(const auto &e : p->child)
                    {
                        T x;
                        node *t;
                        std::tie(x, t) = e;
                        if(valid(t))
                        {
                            s.push_back(x);
                            nx = t;
                            break;
                        }
                    }
                    p = nx;
                }
                node_ptr = p->ter;
            }
            ++type_idx;
            return *this;
        }

        iterator_t operator++(int)
        {
            iterator_t ret = *this;
            return ++(*this), ret;
        }

        iterator_t &operator--()
        {
            if(*this == trie_ptr->end())
            {
                node *p = trie_ptr->root;
                if(p->typ)
                {
                    while(not p->is_ter)
                    {
                        auto dict_itr = p->child.rbegin();
                        while(dict_itr != p->child.rend() and
                              not valid(dict_itr->second))
                        {
                            ++dict_itr;
                        }
                        if(dict_itr != p->child.rend())
                        {
                            p = dict_itr->second;
                            s.push_back(p->tag);
                        }
                        else
                        {
                            p = p->ter;
                        }
                    }
                    node_ptr = p;
                }
            }
            else
            {
                bool is_prefix = false;
                node *p = node_ptr->par;
                while(p->par)
                {
                    auto map_ritr = p->par->child.rend();
                    map_ritr = std::reverse_iterator<typename dict_t::iterator>(
                        p->par->child.lower_bound(p->tag));
                    s.pop_back();
                    p = p->par;
                    while(map_ritr != p->child.rend() and
                          not valid(map_ritr->second))
                        ++map_ritr;
                    if(map_ritr != p->child.rend())
                    {
                        p = map_ritr->second;
                        s.push_back(map_ritr->first);
                        break;
                    }
                    else if(p->ter and p->ter->typ)
                    {
                        is_prefix = true;
                        break;
                    }
                }
                if(is_prefix)
                {
                    node_ptr = p->ter;
                }
                else
                {
                    if(p->is_root)
                    {
                        node_ptr = nullptr;
                    }
                    else
                    {
                        while(not p->is_ter)
                        {
                            auto map_ritr = p->child.rbegin();
                            while(map_ritr != p->child.rend() and
                                  not valid(map_ritr->second))
                                ++map_ritr;
                            if(map_ritr != p->child.rend())
                            {
                                s.push_back(map_ritr->first);
                                p = map_ritr->second;
                            }
                            else
                            {
                                p = p->ter;
                            }
                        }
                        node_ptr = p;
                    }
                }
            }
            --type_idx;
            if(node_ptr)
                size_idx -= node_ptr->cnt;
            else
                size_idx = -1;
            return *this;
        }

        iterator_t operator--(int)
        {
            iterator_t ret = *this;
            return --(*this), ret;
        }

        size_t count() const
        {
            return node_ptr ? node_ptr->cnt : 0;
        }
    };

    friend iterator_t;

    iterator_t begin()
    {
        return iterator_t(this, 0);
    }

    iterator_t end()
    {
        return iterator_t(this, type());
    }

    std::reverse_iterator<iterator_t> rbegin()
    {
        return std::reverse_iterator<iterator_t>(end());
    }

    std::reverse_iterator<iterator_t> rend()
    {
        return std::reverse_iterator<iterator_t>(begin());
    }

    iterator_t lower_bound(const seq_t &key)
    {
        size_t size_idx = 0, type_idx = 0;
        seq_t s;
        node *p = root;
        bool go_back = false;
        for(const T &x : key)
        {
            if(p->ter)
            {
                size_idx += p->ter->cnt;
                type_idx += p->ter->typ;
            }
            node *nx = nullptr;
            for(const auto &e : p->child)
            {
                T y;
                node *t;
                std::tie(y, t) = e;
                if(valid(t))
                {
                    if(y < x)
                    {
                        size_idx += t->cnt;
                        type_idx += t->typ;
                    }
                    else if(t->typ)
                    {
                        s.push_back(y);
                        nx = t;
                        break;
                    }
                }
            }
            if(not nx)
            {
                go_back = true;
                break;
            }
            p = nx;
            if(p->tag > x) break;
        }
        if(go_back)
        {
            while(not p->is_root)
            {
                p = p->par;
                auto dict_itr = p->child.upper_bound(s.back());
                s.pop_back();
                while(dict_itr != p->child.end() and
                      not valid(dict_itr->second))
                    ++dict_itr;
                if(dict_itr != p->child.end())
                {
                    p = dict_itr->second;
                    s.push_back(dict_itr->first);
                    break;
                }
            }
            if(p->is_root) return end();
        }
        while(not p->is_ter)
        {
            if(valid(p->ter))
            {
                p = p->ter;
            }
            else
            {
                auto dict_itr = p->child.begin();
                while(dict_itr != p->child.end() and
                      not valid(dict_itr->second))
                    ++dict_itr;
                p = dict_itr->second;
                s.push_back(dict_itr->first);
            }
        }
        return iterator_t(this, p, s, type_idx, size_idx);
    }

    iterator_t upper_bound(const seq_t &key)
    {
        auto itr = lower_bound(key);
        if(*itr == key) ++itr;
        return itr;
    }

    struct Aho_Corasick
    {
        node *root;

        Aho_Corasick() : root()
        {}

        Aho_Corasick(const Trie &trie)
        {
            build(trie);
        }

        node *build(const Trie<T, seq_t> &trie)
        {
            root = trie.root;
            std::queue<node *> que;
            que.emplace(root);
            while(not que.empty())
            {
                node *const now = que.front();
                que.pop();
                for(const auto &e : now->child)
                {
                    T x;
                    node *t, *p = now;
                    std::tie(x, t) = e;
                    do
                    {
                        p = p->failure;
                    } while(p and not p->child[x]);
                    t->failure = p ? p->child[x] : root;
                    t->sfx_wrd += t->failure->sfx_wrd;
                    que.emplace(t);
                }
            }
            return root;
        }

        node *next(node *now, const T &x)
        {
            while(now and not now->child[x])
            {
                now = now->failure;
            }
            return now = now ? now->child[x] : root;
        }

        size_t query(node *now)
        {
            return now->sfx_wrd;
        }
    };
};

// verified at https://atcoder.jp/contests/dwacon5th-final/submissions/7200502

template <size_t depth, class int_t = int_fast64_t>
struct Binary_trie
{
    struct node
    {
        bool tag;
        node *par, *lft, *rgt;
        size_t digit;
        size_t cnt, typ;
        node() : tag(), par(), lft(), rgt(), digit(depth), cnt(), typ()
        {}
        node(bool _tag, node *p)
            : tag(_tag), par(p), lft(), rgt(), digit((int)p->digit - 1), cnt(),
              typ()
        {}
        // ~node() { delete lft, delete rgt; }
        friend node *alloc(bool _tag, node *p)
        {
            constexpr size_t nodemax = 1.5e6;
            static node stock[nodemax];
            static size_t nodec = 0;
            return &(stock[nodec++] = node(_tag, p));
        }
        friend bool valid(node *p)
        {
            return p and p->cnt;
        }
    };

    node *root;
    int_t power[depth];

    bool bit(int_t x, size_t i) const
    {
        return bool(x & power[i]);
    }

    Binary_trie() : root(new node)
    {
        for(int_t i = (int_t)depth - 1, t = 1; i >= 0; --i, t <<= 1)
        {
            power[i] = t;
        }
    }

#ifdef LOCAL
    ~Binary_trie()
    {
        delete root;
    }
#endif

    size_t size() const
    {
        return root->cnt;
    }

    size_t type() const
    {
        return root->typ;
    }

    bool insert(int_t x)
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

    size_t erase(int_t x, size_t k = 1)
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

    size_t count(int_t x) const
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

    int_t closest(int_t x) const
    {
        assert(size());
        node *p = root;
        int_t ret = 0;
        for(size_t i = 0; i < depth; ++i)
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

    int_t operator[](size_t idx) const
    {
        assert(idx < size());
        node *p = root;
        int_t ret = 0;
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

    struct iterator_t : std::iterator<std::bidirectional_iterator_tag, int_t,
                                      std::ptrdiff_t, node *, int_t>
    {
        Binary_trie *const trie_ptr;
        node *node_ptr;
        int_t s;
        size_t type_idx, size_idx;

        explicit iterator_t()
            : trie_ptr(), node_ptr(), s(), type_idx(-1), size_idx(-1)
        {}

        iterator_t(const iterator_t &itr)
            : trie_ptr(itr.trie_ptr), node_ptr(itr.node_ptr), s(itr.s),
              type_idx(itr.type_idx), size_idx(itr.size_idx)
        {}

        explicit iterator_t(Binary_trie *_trie_ptr, size_t _type_idx)
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

        explicit iterator_t(Binary_trie *_trie_ptr, node *_node_ptr, int_t _s,
                            size_t _type_idx, size_t _size_idx)
            : trie_ptr(_trie_ptr), node_ptr(_node_ptr), s(_s),
              type_idx(_type_idx), size_idx(_size_idx)
        {}

        node *operator->() const
        {
            return node_ptr;
        }

        int_t operator*() const
        {
            return s;
        }

        bool operator==(const iterator_t &itr) const
        {
            return trie_ptr == itr.trie_ptr and type_idx == itr.type_idx;
        }

        bool operator!=(const iterator_t &itr) const
        {
            return not(*this == itr);
        }

        iterator_t &operator++()
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

        iterator_t &operator++(int)
        {
            iterator_t ret = *this;
            return ++(*this), ret;
        }

        iterator_t &operator--()
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

        iterator_t &operator--(int)
        {
            iterator_t ret = *this;
            return --(*this), ret;
        }

        size_t count() const
        {
            return node_ptr ? node_ptr->cnt : 0;
        }
    };

    friend iterator_t;

    iterator_t begin()
    {
        return iterator_t(this, 0);
    }

    iterator_t end()
    {
        return iterator_t(this, type());
    }

    std::reverse_iterator<iterator_t> rbegin()
    {
        return std::reverse_iterator<iterator_t>(end());
    }

    std::reverse_iterator<iterator_t> rend()
    {
        return std::reverse_iterator<iterator_t>(begin());
    }

    iterator_t lower_bound(int_t key)
    {
        size_t size_idx = 0, type_idx = 0, i = 0;
        node *p = root;
        int_t s = 0;
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
        return iterator_t(this, p, s, type_idx, size_idx);
    }

    iterator_t upper_bound(int_t key)
    {
        auto itr = lower_bound(key);
        if(*itr == key) ++itr;
        return itr;
    }
};
