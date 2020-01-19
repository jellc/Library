// verified at https://codeforces.com/contest/1202/submission/59818756
#ifndef Trie_hpp
#define Trie_hpp
#include <map>
#include <vector>

template <class T, class seq_type = std::vector<T>>
struct trie
{
    struct Aho_Corasick;
    struct node
    {
        const T tag;
        const bool tag_set, is_ter, is_root;
        node *const par, *ter;
        std::map<T, node*> child;
        size_t cnt, typ;

        node() : tag(), tag_set(), is_ter(), is_root(true), par(), ter(), child(), cnt(), typ() {}

        node(node *const p) : tag(), tag_set(), is_ter(true), is_root(), par(p), ter(), child(), cnt(), typ() {}

        node(const T &_tag, node *const p) : tag(_tag), tag_set(true), is_ter(), is_root(), par(p), ter(), child(), cnt(), typ() {}

        ~node() { delete ter; for(auto &e : child) delete e.second; }

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
        friend Aho_Corasick;
        friend bool valid(const node *const p)
        {
            return p and p->cnt and p->typ;
        }

        node *failure = nullptr;

        size_t sfx_wrd = 0;
    };

    using dict_t = std::map<T, node *>;

    node *const root;

    trie() : root(new node) {}
    ~trie() { delete root; }

    size_t size() const { return root->cnt; }
    size_t type() const { return root->typ; }

    node *insert(const seq_type &s)
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

    size_t erase(const seq_type &s, size_t k = 1)
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

    size_t count(const seq_type &s) const
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

    /*
    size_t lower_bound(const seq_type &s) const
    {
        size_t ret = 0;
        node *p = root;
        for(const T &x : s)
        {
            if(not p) break;
            if(p->ter) ret += p->ter->cnt;
            for(const auto &e : p->child)
            {
                if(e.first == x) break;
                node *t = e.second;
                if(t) ret += t->cnt;
            }
            p = p->child[x];
        }
        return ret;
    }

    size_t upper_bound(const seq_type &s) const
    {
        size_t ret = 0;
        node *p = root;
        for(const T &x : s)
        {
            if(not p) break;
            if(p->ter) ret += p->ter->cnt;
            for(const auto &e : p->child)
            {
                if(e.first == x) break;
                node *t = e.second;
                if(t) ret += t->cnt;
            }
            p = p->child[x];
        }
        if(p and p->ter) ret += p->ter->cnt;
        return ret;
    }
    //*/

    seq_type operator[](size_t idx) const
    {
        assert(idx < size());
        node *p = root;
        seq_type ret = seq_type();
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

    struct iterator_type : std::iterator<std::bidirectional_iterator_tag, seq_type,
                                      std::ptrdiff_t, node *, seq_type>
    {
        trie *const trie_ptr;
        node *node_ptr;
        seq_type s;
        size_t type_idx, size_idx;

        iterator_type() : trie_ptr(), node_ptr(), s(), type_idx(-1), size_idx(-1) {}
        iterator_type(const iterator_type &itr) : trie_ptr(itr.trie_ptr), node_ptr(itr.node_ptr), s(itr.s), type_idx(itr.type_idx), size_idx(itr.size_idx) {}
        iterator_type(trie *_trie_ptr, size_t _type_idx) : trie_ptr(_trie_ptr), node_ptr(), s(), type_idx(_type_idx), size_idx()
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

        iterator_type(trie *_trie_ptr, node *_node_ptr, const seq_type &_s, size_t _type_idx, size_t _size_idx) : trie_ptr(_trie_ptr), node_ptr(_node_ptr), s(_s), type_idx(_type_idx), size_idx(_size_idx) {}

        node *operator->() const { return node_ptr; }

        seq_type operator*() const { return s; }

        bool operator==(const iterator_type &itr) const { return trie_ptr == itr.trie_ptr and type_idx == itr.type_idx; }

        bool operator!=(const iterator_type &itr) const { return not(*this == itr); }

        iterator_type &operator++()
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

        iterator_type operator++(int)
        {
            iterator_type ret = *this;
            return ++(*this), ret;
        }

        iterator_type &operator--()
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

        iterator_type operator--(int)
        {
            iterator_type ret = *this;
            return --(*this), ret;
        }

        size_t count() const
        {
            return node_ptr ? node_ptr->cnt : 0;
        }
    }; // class iterator_type
    friend iterator_type;

    iterator_type begin() { return iterator_type(this, 0); }
    iterator_type end() { return iterator_type(this, type()); }
    std::reverse_iterator<iterator_type> rbegin() { return std::reverse_iterator<iterator_type>(end()); }
    std::reverse_iterator<iterator_type> rend() { return std::reverse_iterator<iterator_type>(begin()); }

    iterator_type lower_bound(const seq_type &key)
    {
        size_t size_idx = 0, type_idx = 0;
        seq_type s;
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
        return iterator_type(this, p, s, type_idx, size_idx);
    }

    iterator_type upper_bound(const seq_type &key)
    {
        auto itr = lower_bound(key);
        if(*itr == key) ++itr;
        return itr;
    }

    struct Aho_Corasick
    {
        node *root;

        Aho_Corasick() : root() {}
        Aho_Corasick(const trie &trie) { build(trie); }

        node *build(const trie<T, seq_type> &trie)
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

        size_t query(node *now) { return now->sfx_wrd; }
    };
}; // struct trie

#endif // Trie_hpp