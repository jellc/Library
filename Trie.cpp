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
    struct trie {
        size_t _kinds;
        node *root;
        int_fast64_t power[dep];

        bool bit(int_fast64_t x, size_t d) const {
            return x >> (dep - d - 1) & 1;
        }

        trie() : _kinds(), root(node::alloc(nullptr))
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
using trie_prep::trie;





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
    };

    node *root;

    explicit Trie() : root(new node) {}

    ~Trie() { delete root; }

    size_t size() const { return root->cnt; }

    size_t type() const { return root->typ; }

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
                T x; node *t; tie(x, t) = e;
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

    size_t lower_bound(const seq_t &s) const
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

    size_t upper_bound(const seq_t &s) const
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
                T x; node *t; tie(x, t) = e;
                size_t here = t ? t->cnt : 0;
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
        std::size_t idx;

        explicit iterator_t()
            : trie_ptr(), node_ptr(), s(), idx(-1)
        {}

        iterator_t(const iterator_t &itr)
            : trie_ptr(itr.trie_ptr), node_ptr(itr.node_ptr), s(itr.s), idx(itr.idx)
        {}

        explicit iterator_t(Trie *_trie_ptr, std::size_t _idx)
            : trie_ptr(_trie_ptr), node_ptr(), s(), idx(_idx)
        {
            if(idx != trie_ptr->type())
            {
                node* &p = (node_ptr = trie_ptr->root);
                while(p)
                {
                    std::size_t here = p->ter ? p->ter->cnt : 0;
                    if(_idx < here)
                    {
                        p = p->ter; break;
                    }
                    _idx -= here;
                    node *nx = nullptr;
                    for(const auto &e : p->child)
                    {
                        T x; node *t; tie(x, t) = e;
                        here = t ? t->cnt : 0;
                        if(_idx < here)
                        {
                            s.push_back(x);
                            nx = t; break;
                        }
                        _idx -= here;
                    }
                    p = nx;
                }
            }
        }

        node *operator->() const { return node_ptr; }

        seq_t operator*() const { return s; }

        bool operator==(const iterator_t &itr) const
        {
            return trie_ptr == itr.trie_ptr and idx == itr.idx;
        }

        bool operator!=(const iterator_t &itr) const { return not (*this == itr); }

        iterator_t &operator++()
        {
            node *p = node_ptr;
            while(p->par)
            {
                auto map_itr = p->par->child.begin();
                if(not p->is_ter)
                {
                    map_itr = p->par->child.upper_bound(p->tag);
                    s.pop_back();
                }
                p = p->par;
                while(map_itr != p->child.end() and (not map_itr->second or not map_itr->second->cnt)) ++map_itr;
                if(map_itr != p->child.end())
                {
                    p = map_itr->second;
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
                while(not p->ter or not p->ter->cnt)
                {
                    node *nx = nullptr;
                    for(const auto &e : p->child)
                    {
                        if(e.second and e.second->cnt)
                        {
                            s.push_back(e.first);
                            nx = e.second; break;
                        }
                    }
                    p = nx;
                }
                node_ptr = p->ter;
            }
            ++idx;
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
                if(p->cnt)
                {
                    while(true)
                    {
                        auto map_itr = p->child.rbegin();
                        while(map_itr != p->child.rend() and (not map_itr->second or not map_itr->second->cnt))
                        {
                            ++map_itr;
                        }
                        if(map_itr != p->child.rend())
                        {
                            p = map_itr->second;
                            s.push_back(p->tag);
                        }
                        else
                        {
                            p = p->ter; break;
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
                    auto map_itr = p->par->child.rend();
                    map_itr = std::reverse_iterator<typename decltype(p->par->child)::iterator>(p->par->child.lower_bound(p->tag));
                    s.pop_back();
                    p = p->par;
                    while(map_itr != p->child.rend() and (not map_itr->second or not map_itr->second->cnt)) ++map_itr;
                    if(map_itr != p->child.rend())
                    {
                        p = map_itr->second;
                        s.push_back(map_itr->first);
                        break;
                    }
                    else if(p->ter and p->ter->cnt)
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
                        while(true)
                        {
                            auto map_itr = p->child.rbegin();
                            while(map_itr != p->child.rend() and (not map_itr->second or not map_itr->second->cnt)) ++map_itr;
                            if(map_itr != p->child.rend())
                            {
                                s.push_back(map_itr->first);
                                p = map_itr->second;
                            }
                            else
                            {
                                p = p->ter; break;   
                            }
                        }
                        node_ptr = p;
                    }
                }
            }
            --idx;
            return *this;
        }

        iterator_t &operator--(int)
        {
            iterator_t ret = *this; return --(*this), ret;
        }

        std::size_t count() const { return node_ptr->cnt; }
    };

    friend iterator_t;
    iterator_t begin() { return iterator_t(this, 0); }
    iterator_t end() { return iterator_t(this, type()); }
    std::reverse_iterator<iterator_t> rbegin() { return std::reverse_iterator<iterator_t>(end()); }
    std::reverse_iterator<iterator_t> rend() { return std::reverse_iterator<iterator_t>(begin()); }
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
