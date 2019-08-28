#include <bits/stdc++.h>

// verified at https://atcoder.jp/contests/dwacon5th-final/submissions/6905246

namespace trie_prep {
    constexpr size_t nodecnt_max = 1.5e6;
    
    struct node {
        node *par, *lft, *rgt;
        size_t cnt;
        node(node *p = nullptr) : par(p), lft(), rgt(), cnt() {}
        static node *alloc(node *p) {
            static size_t nodecnt = 0;
            static node stock[nodecnt_max];
            node *ret = stock + nodecnt++;
            ret->par = p;
            return ret;
        }
    };

    template <size_t dep> 
    struct Binary_trie {
        size_t _kinds;
        node *root;
        int_fast64_t power[dep];

        bool bit(int_fast64_t x, size_t d) const {
            return x >> (dep - d - 1) & 1;
        }

        Binary_trie() : _kinds(), root(node::alloc(nullptr))
        {
            for(int_fast64_t i = (int)dep - 1, t = 1; i >= 0; --i, t <<= 1) {
                power[i] = t;
            }
        }

        size_t size() const { return root->cnt; }

        size_t kinds() const { return _kinds; }

        bool insert(int_fast64_t x) {
            node *p = root;
            p->cnt++;
            bool ret = false;
            for(size_t d = 0; d < dep; ++d) {
                if(bit(x, d)) {
                    if(!p->rgt) p->rgt = node::alloc(p), ret = true;
                    p = p->rgt;
                } else {
                    if(!p->lft) p->lft = node::alloc(p), ret = true;
                    p = p->lft;
                }
                p->cnt++;
            }
            if(p->cnt == 1) _kinds++;
            return ret;
        }

        size_t erase(int_fast64_t x, size_t y = 1) {
            node *p = root;
            y = min(y, p->cnt);
            for(size_t d = 0; d < dep; ++d) {
                if(bit(x, d)) {
                    if(!p->rgt) return 0;
                    p = p->rgt;
                } else {
                    if(!p->lft) return 0;
                    p = p->lft;
                }
                y = min(y, p->cnt);
            }
            if(p->cnt == y) _kinds--;
            while(p) {
                p->cnt -= y;
                p = p->par;
            }
            return y;
        }

        size_t count(int_fast64_t x) const {
            node *p = root;
            for(size_t d = 0; d < dep; ++d) {
                if(bit(x, d)) {
                    if(!p->rgt) return 0;
                    p = p->rgt;
                } else {
                    if(!p->lft) return 0;
                    p = p->lft;
                }
            }
            return p->cnt;
        }

        int_fast64_t closest(int_fast64_t x) const {
            if(!root->cnt) return -1;
            node *p = root;
            int_fast64_t ret = 0;
            for(size_t d = 0; d < dep; ++d) {
                if(bit(x, d)) {
                    if(p->rgt && p->rgt->cnt) p = p->rgt, ret += power[d];
                    else p = p->lft;
                } else {
                    if(p->lft && p->lft->cnt) p = p->lft;
                    else p = p->rgt, ret += power[d];
                }
            }
            return ret;
        }

        int_fast64_t operator[](size_t idx) const {
            if(idx >= size()) return -1;
            node *p = root;
            int_fast64_t ret = 0;
            for(size_t d = 0; d < dep; ++d) {
                size_t lsz = p->lft ? p->lft->cnt : 0;
                if(idx < lsz) {
                    p = p->lft;
                } else {
                    idx -= lsz;
                    p = p->rgt;
                    ret += power[d];
                }
            }
            return ret;
        }
    };
}
using trie_prep::Binary_trie;




template <class T, class seq_t = std::vector<T>>
struct Trie
{
    struct node
    {
        T tag;
        bool tag_set, is_ter, is_root;
        node *par, *ter;
        std::map<T, node*> child;
        std::size_t cnt, typ;

        explicit node() : tag(), tag_set(), is_ter(), is_root(true), par(), ter(), child(), cnt(), typ() {}

        explicit node(node *p) : tag(), tag_set(), is_ter(true), is_root(), par(p), ter(), child(), cnt(), typ() {}

        explicit node(T _tag, node *p) : tag(_tag), tag_set(true), is_ter(), is_root(), par(p), ter(), child(), cnt(), typ() {}

        ~node()
        {
            delete ter;
            for(auto &e : child) delete e.second;
        }

        friend bool valid(node *p) { return p and p->cnt and p->typ; }
    };

    using dict_t = std::map<T, node*>;

    node* const root;

    explicit Trie() : root(new node) {}

#if defined(LOCAL) or defined(DEBUG)
    ~Trie() { delete root; }
#endif

    std::size_t size() const { return root->cnt; }

    std::size_t type() const { return root->typ; }

    bool insert(const seq_t &s)
    {
        node *p = root;
        p->cnt++;
        for(const T &x : s)
        {
            if(not p->child[x])
            {
                p->child[x] = new node(x, p);
            }
            (p = p->child[x])->cnt++;
        }
        if(not p->ter)
        {
            p->ter = new node(p);
        }
        p = p->ter;
        if(p->cnt++) return false;
        while(p)
        {
            p->typ++;
            p = p->par;
        }
        return true;
    }

    std::size_t erase(const seq_t &s, std::size_t k = 1)
    {
        node *p = root;
        for(const T &x : s)
        {
            p = p->child[x];
            if(not p) return 0;
        }
        p = p->ter;
        if(not p) return 0;
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

    std::size_t erase(std::size_t idx)
    {
        if(idx >= size()) return 0;
        node *p = root;
        while(true)
        {
            if(p->ter)
            {
                std::size_t here = p->ter->cnt;
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
                T x; node *t; tie(x, t) = e;
                std::size_t here = t ? t->cnt : 0;
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
        bool uni_typ = not --p->ter->cnt;
        while(p) {
            p->cnt--;
            p->typ -= uni_typ;
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

    // std::size_t lower_bound(const seq_t &s) const
    // {
    //     std::size_t ret = 0;
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
    // std::size_t upper_bound(const seq_t &s) const
    // {
    //     std::size_t ret = 0;
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

    seq_t operator[](std::size_t idx) const
    {
        assert(idx < size());
        node *p = root;
        seq_t ret = seq_t();
        while(true)
        {
            if(p->ter)
            {
                std::size_t here = p->ter->cnt;
                if(idx < here) break;
                idx -= here;
            }
            node *nx = nullptr;
            for(const auto &e : p->child)
            {
                T x; node *t; std::tie(x, t) = e;
                std::size_t here = t ? t->cnt : 0;
                if(idx < here)
                {
                    ret.push_back(x);
                    nx = t; break;
                }
                idx -= here;
            }
            p = nx;
        }
        return ret;
    }

    struct iterator_t : std::iterator<std::bidirectional_iterator_tag, seq_t, std::ptrdiff_t, node*, seq_t>
    {
        Trie *trie_ptr;
        node *node_ptr;
        seq_t s;
        std::size_t type_idx, size_idx;

        explicit iterator_t()
            : trie_ptr(), node_ptr(), s(), type_idx(-1), size_idx(-1)
        {}

        iterator_t(const iterator_t &itr)
            : trie_ptr(itr.trie_ptr), node_ptr(itr.node_ptr), s(itr.s), type_idx(itr.type_idx), size_idx(itr.size_idx)
        {}

        explicit iterator_t(Trie *_trie_ptr, std::size_t _type_idx)
            : trie_ptr(_trie_ptr), node_ptr(), s(), type_idx(_type_idx), size_idx()
        {
            if(_type_idx != trie_ptr->type())
            {
                node* &p = (node_ptr = trie_ptr->root);
                while(p)
                {
                    std::size_t here_typ = p->ter ? p->ter->typ : 0;
                    std::size_t here_cnt = p->ter ? p->ter->cnt : 0;
                    if(_type_idx < here_typ)
                    {
                        p = p->ter; break;
                    }
                    _type_idx -= here_typ;
                    size_idx += here_cnt;
                    node *nx = nullptr;
                    for(const auto &e : p->child)
                    {
                        T x; node *t; std::tie(x, t) = e;
                        here_typ = t ? t->typ : 0;
                        here_cnt = t ? t->cnt : 0;
                        if(_type_idx < here_typ)
                        {
                            s.push_back(x);
                            nx = t; break;
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

        explicit iterator_t(Trie *_trie_ptr, node *_node_ptr, const seq_t &_s, std::size_t _type_idx, std::size_t _size_idx)
            : trie_ptr(_trie_ptr), node_ptr(_node_ptr), s(_s), type_idx(_type_idx), size_idx(_size_idx)
        {}

        node *operator->() const { return node_ptr; }

        seq_t operator*() const { return s; }

        bool operator==(const iterator_t &itr) const
        {
            return trie_ptr == itr.trie_ptr and type_idx == itr.type_idx;
        }

        bool operator!=(const iterator_t &itr) const { return not (*this == itr); }

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
                while(dict_itr != p->child.end() and not valid(dict_itr->second)) ++dict_itr;
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
                        T x; node *t; std::tie(x, t) = e;
                        if(valid(t))
                        {
                            s.push_back(x);
                            nx = t; break;
                        }
                    }
                    p = nx;
                }
                node_ptr = p->ter;
            }
            ++type_idx;
            return *this;
        }

        iterator_t &operator++(int)
        {
            iterator_t ret = *this; return ++(*this), ret;
        }

        iterator_t &operator--()
        {
            node *p = trie_ptr->root;
            if(*this == trie_ptr->end())
            {
                if(p->typ)
                {
                    while(not p->is_ter)
                    {
                        auto dict_itr = p->child.rbegin();
                        while(dict_itr != p->child.rend() and not valid(dict_itr->second))
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
                p = node_ptr->par;
                while(p->par)
                {
                    auto map_ritr = p->par->child.rend();
                    map_ritr = std::reverse_iterator<typename dict_t::iterator>(p->par->child.lower_bound(p->tag));
                    s.pop_back();
                    p = p->par;
                    while(map_ritr != p->child.rend() and not valid(map_ritr->second)) ++map_ritr;
                    if(map_ritr != p->child.rend())
                    {
                        p = map_ritr->second;
                        s.push_back(map_ritr->first);
                        break;
                    }
                    else if(p->ter and p->ter->typ)
                    {
                        is_prefix = true; break;
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
                            while(map_ritr != p->child.rend() and not valid(map_ritr->second)) ++map_ritr;
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
            if(node_ptr) size_idx -= node_ptr->cnt;
            else size_idx = -1;
            return *this;
        }

        iterator_t &operator--(int)
        {
            iterator_t ret = *this; return --(*this), ret;
        }

        std::size_t count() const { return node_ptr ? node_ptr->cnt : 0; }
    };

    friend iterator_t;

    iterator_t begin() { return iterator_t(this, 0); }

    iterator_t end() { return iterator_t(this, type()); }

    std::reverse_iterator<iterator_t> rbegin() { return std::reverse_iterator<iterator_t>(end()); }

    std::reverse_iterator<iterator_t> rend() { return std::reverse_iterator<iterator_t>(begin()); }

    iterator_t lower_bound(const seq_t &key)
    {
        std::size_t size_idx = 0, type_idx = 0;
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
                T y; node *t; std::tie(y, t) = e;
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
                        nx = t; break;
                    }
                }
            }
            if(not nx)
            {
                go_back = true; break;
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
                while(dict_itr != p->child.end() and not valid(dict_itr->second)) ++dict_itr;
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
                while(dict_itr != p->child.end() and not valid(dict_itr->second)) ++dict_itr;
                p = dict_itr->second; s.push_back(dict_itr->first);
            }
        }
        return iterator_t(this, p, s, type_idx, size_idx);
    }

    iterator_t upper_bound(const seq_t &s)
    {
        auto itr = lower_bound(s);
        if(*itr == s) ++itr;
        return itr;
    }
};



#define alloc(p) new node(p)
namespace Trie_prep {
    constexpr size_t units = 26;
    constexpr size_t nodecnt_max = 1e6;

    struct node {
        node *par;
        node *child[units];
        node *ter;
        size_t cnt;
        node(node *p = nullptr) : par(p), child(), ter(), cnt() {}
        friend node *alaloc(node *p) {
            static size_t nodecnt = 0;
            static node stock[nodecnt_max];
            node *ret = stock + nodecnt++;
            *ret = node(p);
            return ret;
        }
        ~node() {
            delete ter;
            for(int i=0; i<units; ++i)
            {
                delete child[i];
            }
        }
    };

    template <size_t dep, class T, class seq_t = std::vector<T>> 
    struct Trie {
        node *root;
        const function<size_t(T)> f;
        const function<T(size_t)> invf;

        Trie(const function<size_t(T)> &_f, const function<T(size_t)> &_invf) : root(alloc((node*)nullptr)), f(_f), invf(_invf) {}

        size_t size() const { return root->cnt; }

        bool insert(const seq_t &s) {
            node *p = root;
            bool ret = false;
            for(size_t d = 0; d <= dep; ++d) {
                p->cnt++;
                if(s.size() == d) {
                    if(!p->ter) {
                        p->ter = alloc(p);
                        ret = true;
                    }
                    p->ter->cnt++;
                    break;
                }
                if(d == dep) break;
                int x = f(s[d]);
                if(!p->child[x]) {
                    p->child[x] = alloc(p);
                    ret = true;
                }
                p = p->child[x];
            }
            return ret;
        } 

        size_t erase(const seq_t &s, size_t k = 1) {
            node *p = root;
            k = min(k, p->cnt);
            for(size_t d = 0; d <= dep && d <= s.size(); ++d) {
                if(s.size() == d) {
                    if(!p->ter) return 0;
                    p = p->ter;
                } else {
                    size_t x = f(s[d]);
                    if(!p->child[x]) return 0;
                    p = p->child[x];
                }
                k = min(k, p->cnt);
            }
            while(p) {
                p->cnt -= k;
                p = p->par;
            }
            return k;
        }

        size_t erase(size_t idx) {
            if(idx >= size()) return 0;
            node *p = root;
            for(size_t d = 0; d < dep; ++d) {
                if(p->ter) {
                    if(idx < p->ter->cnt) {
                        p = p->ter;
                        break;
                    }
                    idx -= p->ter->cnt;
                }
                for(size_t i = 0; i < units; ++i) {
                    size_t now = p->child[i] ? p->child[i]->cnt : 0;
                    if(idx < now) {
                        p = p->child[i];
                        break;
                    } else {
                        idx -= now;
                    }
                }
            }
            while(p) {
                p->cnt--;
                p = p->par;
            }
            return 1;
        }

        size_t count(const seq_t &s) const {
            node *p = root;
            for(size_t d = 0; d <= dep && d <= s.size(); ++d) {
                if(s.size() == d) return p->ter ? p->ter->cnt : 0;
                size_t x = f(s[d]);
                if(!p->child[x]) return 0;
                p = p->child[x];
            }
            return 0;
        }

        size_t lower_bound(const seq_t &s) const {
            size_t ret = 0;
            node *p = root;
            for(size_t d = 0; d < dep && d < s.size() && p; ++d) {
                ret += p->ter ? p->ter->cnt : 0;
                for(size_t x = 0; x < f(s[d]); ++x) {
                    ret += p->child[x] ? p->child[x]->cnt : 0;
                }
                p = p->child[f(s[d])];
            }
            return ret;
        }

        size_t upper_bound(const seq_t &s) const {
            size_t ret = 0;
            node *p = root;
            for(size_t d = 0; d < dep && d < s.size() && p; ++d) {
                ret += p->ter ? p->ter->cnt : 0;
                for(size_t x = 0; x < f(s[d]); ++x) {
                    ret += p->child[x] ? p->child[x]->cnt : 0;
                }
                p = p->child[f(s[d])];
            }
            if(p && s.size() <= dep) {
                ret += p->ter ? p->ter->cnt : 0;
            }
            return ret;
        }

        seq_t operator[](size_t idx) const {
            assert(idx < size());
            node *p = root;
            seq_t ret = seq_t();
            for(size_t d = 0; d < dep; ++d) {
                if(p->ter) {
                    if(idx < p->ter->cnt) return ret;
                    idx -= p->ter->cnt;
                }
                for(size_t x = 0; x < units; ++x) {
                    size_t now = p->child[x] ? p->child[x]->cnt : 0;
                    if(idx < now) {
                        ret.push_back(invf(x));
                        p = p->child[x];
                        break;
                    } else {
                        idx -= now;
                    }
                }
            }
            return ret;
        }
    };
}
using Trie_prep::Trie;
