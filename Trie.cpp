#include <bits/stdc++.h>
using namespace std;


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




namespace Trie_prep {
    constexpr size_t units = 26;
    constexpr size_t nodecnt_max = 1e6;

    struct node {
        node *par;
        node *child[units];
        node *ter;
        size_t cnt;
        node(node *p = nullptr) : par(p), child(), ter(), cnt() {}
        static node *alloc(node *p) {
            static size_t nodecnt = 0;
            static node stock[nodecnt_max];
            node *ret = stock + nodecnt++;
            *ret = node(p);
            return ret;
        }
    };

    template <size_t dep, class T, class seq_t = std::vector<T>> 
    struct Trie {
        node *root;
        const function<size_t(T)> f;
        const function<T(size_t)> invf;

        Trie(const function<size_t(T)> &_f, const function<T(size_t)> &_invf) : root(node::alloc(nullptr)), f(_f), invf(_invf) {}

        size_t size() const { return root->cnt; }

        bool insert(const seq_t &s) {
            node *p = root;
            bool ret = false;
            for(size_t d = 0; d <= dep; ++d) {
                p->cnt++;
                if(s.size() == d) {
                    if(!p->ter) {
                        p->ter = node::alloc(p);
                        ret = true;
                    }
                    p->ter->cnt++;
                    break;
                }
                if(d == dep) break;
                int x = f(s[d]);
                if(!p->child[x]) {
                    p->child[x] = node::alloc(p);
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