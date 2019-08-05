#include <bits/stdc++.h>
using namespace std;


// verified at https://atcoder.jp/contests/dwacon5th-final/submissions/6315156

namespace trie_prep {
    constexpr size_t nodecnt_max = 1e5 * 15;
    
    struct node {
        node *par, *lft, *rgt;
        size_t cnt;
        node(node *_par = nullptr) : par(_par), lft(), rgt(), cnt() {}
    };

    size_t nodecnt = 0;
    node stock[nodecnt_max];

    template <size_t dep> 
    class trie {
        size_t _kind;
        node *root;
        int_fast64_t power[dep]; 

        node *alloc(node *_par) const {
            node *ret = stock + nodecnt++;
            ret->par = _par;
            return ret;
        }

        void binaryexpr(int_fast64_t x, bool bit[]) const {
            for(size_t i = 0; i < dep; ++i, x >>= 1) {
                bit[dep - i - 1] = x & 1;
            }
        }

    public:
        trie() : _kind(), root(alloc(nullptr))
        {
            for(int_fast64_t i = (int)dep - 1, t = 1; i >= 0; --i, t <<= 1) {
                power[i] = t;
            }
        }

        size_t size() const {
            return root->cnt;
        }

        size_t kind() const {
            return _kind;
        }

        bool insert(int_fast64_t x) {
            node *p = root;
            p->cnt++;
            bool ret = false;
            bool bit[dep];
            binaryexpr(x, bit);
            for(size_t d = 0; d < dep; ++d) {
                if(bit[d]) {
                    if(!p->rgt) p->rgt = alloc(p), ret = true;
                    p = p->rgt;
                } else {
                    if(!p->lft) p->lft = alloc(p), ret = true;
                    p = p->lft;
                }
                p->cnt++;
            }
            if(p->cnt == 1) _kind++;
            return ret;
        }

        size_t erase(int_fast64_t x, size_t y = 1) {
            node *list[dep + 1];
            node *p = root;
            list[0] = p;
            y = min(y, p->cnt);
            bool bit[dep];
            binaryexpr(x, bit);
            for(size_t d = 0; d < dep; list[++d] = p) {
                if(bit[d]) {
                    if(!p->rgt) return 0;
                    p = p->rgt;
                } else {
                    if(!p->lft) return 0;
                    p = p->lft;
                }
                y = min(y, p->cnt);
            }
            for(size_t i = 0; i <= dep; ++i) {
                p = list[i];
                p->cnt -= y;
            }
            if(!p->cnt) _kind--;
            return y;
        }

        int_fast64_t closest(int_fast64_t x) const {
            if(!root->cnt) return -1;
            node *p = root;
            bool bit[dep];
            binaryexpr(x, bit);
            int_fast64_t ret = 0;
            for(size_t d = 0; d < dep; ++d) {
                if(bit[d]) {
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



// verified at https://atcoder.jp/contests/dwacon5th-final-open/submissions/4980213

// namespace Trie_prep {
//     constexpr size_t kind_max = 2;
//     constexpr size_t nodecnt_max = 5e5 * 31 * 2;

//     struct node {
//         node *par;
//         node *child[kind_max + 1];  //The index 0 indicates terminating character.
//         int cnt;
//         node(node *_par = nullptr) : par(_par),cnt(),child() {}
//     };

//     size_t nodecnt = 0;
//     node stock[nodecnt_max];

//     template <class T, class seq_t = std::vector<T>> 
//     struct Trie {
//         node *root;
//         const size_t dep;
//         const function<int(T)> f;    //The return value must be a positive integer.
//         const function<T(int)> invf; //The argument must be a positive integer.

//         Trie(size_t _dep, const function<int(T)> &_f, const function<T(int)> &_invf) : dep(_dep),f(_f),invf(_invf),root(alloc(nullptr)) {}

//         node *alloc(node *_par) {
//             node *ret = stock + nodecnt++;
//             ret->par = _par;
//             return ret;
//         }

//         size_t size() const { return root->cnt; }

//         bool insert(const seq_t &x) {
//             node *p = root;
//             p->cnt++;
//             bool ret = false;
//             for(size_t d = 0; d <= dep; ++d) {
//                 if(x.size() == d) {
//                     if(!p->child[0]) {
//                         p->child[0] = alloc(p);
//                         ret = true;
//                     }
//                     p->child[0]->cnt++;
//                     return ret;
//                 }
//                 int i = f(x[d]);
//                 if(!p->child[i]) {
//                     p->child[i] = alloc(p);
//                     ret = true;
//                 }
//                 (p = p->child[i])->cnt++;
//             }
//             return ret;
//         } 

//         bool erase(const seq_t &x) {
//             if(!count(x)) return false;
//             node *p = root;
//             p->cnt--;
//             for(size_t d = 0; d < dep && d != x.size(); ++d) {
//                 if(!--(p->child[f(x[d])]->cnt)) {
//                     p->child[f(x[d])] = nullptr;
//                     break;
//                 }
//                 p = p->child[f(x[d])];
//             }
//             return true;
//         }

//         size_t count(const seq_t &x) const {
//             pair<seq_t,size_t> y = _closest(x);
//             return x == y.first ? y.second : 0;
//         }

//         pair<seq_t,size_t> _closest(const seq_t &x) const {
//             seq_t ret;
//             node *p = root;
//             if(!size()) return make_pair(ret,1);
//             for(size_t d = 0; d < dep; ++d) {
//                 size_t i = x.size() > d ? f(x[d]) : 0;
//                 if(i && p->child[i]) {
//                     ret.push_back(invf(i));
//                     p = p->child[i];
//                 } else {
//                     for(size_t j = 0; j <= kind_max; ++j) {
//                         if(p->child[j]) {
//                             p = p->child[j];
//                             if(!j) return make_pair(ret,p->cnt);
//                             ret.push_back(invf(j));
//                             break;
//                         }
//                     }
//                 }
//             }
//             return make_pair(ret,p->cnt);
//         }

//         seq_t closest(const seq_t &x) const {
//             return _closest(x).first;
//         }

//         seq_t operator[](int idx) const {
//             node *p = root;
//             seq_t ret;
//             for(size_t d = 0; d < dep; ++d) {
//                 for(size_t j = 0; j <= kind_max; ++j) {
//                     int tmp = p->child[j] ? p->child[j]->cnt : 0;
//                     if(idx >= tmp) {
//                         idx -= tmp;
//                         if(j == kind_max) return ret;
//                     } else {
//                         if(!j) return ret;
//                         ret.push_back(invf(j));
//                         p = p->child[j];
//                         break;
//                     }
//                 }
//             }
//             return ret;
//         }
//     };
// }
// using Trie_prep::Trie;



signed main() {
    
}
