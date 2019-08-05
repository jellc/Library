#include <bits/stdc++.h>
using namespace std;
template <class T> constexpr T inf = numeric_limits<T>::max() / (T)2;


// minimizer of multiple linear functions
template <class K>
class CHT {
    struct line {
        K slop, incp;
        line(K a, K b) : slop(a), incp(b) {}
        K get(int_fast64_t x) const { return slop * x + incp; }
    };

    struct node {
        line ln;
        node *left, *right;
        node(line l) : ln(l), left(nullptr), right(nullptr) {}
        ~node() { delete left; delete right; }
        K get(int_fast64_t x) const { return ln.get(x); }
    };
 
    const K x_min, x_max;
    size_t node_cnt;
    node *root;
 
    node *insert(node *p, int_fast64_t low, int_fast64_t high, line l) {
        if(!p) return ++node_cnt, new node(l);
        if (p->get(low) <= l.get(low) && p->get(high) <= l.get(high)) return p;
        if (p->get(low) >= l.get(low) && p->get(high) >= l.get(high)) {
            p->ln = l;
            return p;
        }
        int_fast64_t mid = (low + high) / 2;
        if (p->get(mid) > l.get(mid)) swap(p->ln,l);
        if (p->get(low) >= l.get(low)) p->left = insert(p->left,low,mid,l);
        else p->right = insert(p->right,mid + 1,high,l);
        return p;
    }   
 
    K query(node *p, int_fast64_t low, int_fast64_t high, int_fast64_t x) {
        if(!p) return inf<K>;
        if(low == high) return p->get(x);
        int_fast64_t mid = (low + high) / 2;
        if (x <= mid) return min(p->get(x), query(p->left, low, mid, x));
        return min(p->get(x),query(p->right, mid + 1, high, x));
    }

public: 
    CHT(int_fast64_t _x_min, int_fast64_t _x_max) : x_min(_x_min), x_max(_x_max), root() {}

    ~CHT() { delete root; }

    size_t size() const { return node_cnt; }

    bool empty() const { return !root; }

    void insert(K a, K b) { root = insert(root, x_min, x_max, line(a, b)); }

    K query(int_fast64_t x) {
        assert(x_min <= x && x <= x_max);
        return query(root, x_min, x_max, x);
    }
};

