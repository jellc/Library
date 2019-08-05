#include <bits/stdc++.h>
using namespace std;
template <class T> constexpr T inf = numeric_limits<T>::max() / (T)2;


struct UnionFind {
    vector<int> par,siz;
    vector<bool> cyc;
 
    UnionFind(int n) { init(n); }
 
    void init(int n) {
        par.resize(n);
        iota(begin(par), end(par), 0);
        siz.assign(n, 1);
        cyc.assign(n, false);
    }
 
    int find(int x) {
        if(par[x] == x) return x;
        int r = find(par[x]);
        return par[x] = r;
    }
 
    size_t size(int x) { return siz[find(x)]; }

    bool is_cyclic(int x) { return cyc[find(x)]; }
 
    bool is_same(int x, int y) { return find(x) == find(y); }
 
    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if(x == y) {
            cyc[x] = true;
            return false;
        }
        if(siz[x] < siz[y]) swap(x,y);
        siz[x] += siz[y];
        par[y] = x;
        cyc[x] = cyc[x] || cyc[y];
        return true;
    }
};



template <class Abel>
struct WeightedUF {
    vector<int> par, siz;
    vector<Abel> diff_weight;

    WeightedUF(int n) { init(n); }

    void init(int n) {
        par.resize(n);
        iota(begin(par), end(par), 0);
        siz.assign(n, 1);
        diff_weight.resize(n);
    }

    int find(int x) {
        if(par[x]) return x;
        int r = find(par[x]);
        diff_weight[x] += diff_weight[par[x]];
        return par[x] = r;
    }

    size_t size(int x) { return siz[find(x)]; }

    Abel weight(int x) {
        find(x);
        return diff_weight[x];
    }

    Abel diff(int x, int y) { return weight(y) - weight(x); }

    bool is_same(int x, int y) { return find(x) == find(y); }

    bool unite(int x, int y, Abel w = 0) {
        w += weight(x);
        w += weight(y);
        x = find(x);
        y = find(y);
        if(x == y) return false;
        if(size[x] < size[y]) {
            swap(x,y);
            w = -w;
        }
        size[x] += size[y];
        par[y] = x;
        diff_weight[y] = w;
        return true;
    }
};



struct PersistentUF {
    vector<int> par;
    vector<int> time;
    vector<vector<pair<int,int>>> siz;
    int clock;

    PersistentUF(int n) : clock() { init(n); }

    void init(int n) {
        par.resize(n);
        iota(begin(par), end(par), 0);
        siz.resize(n, vector<pair<int,int>>(1, {0, 1}));
        time.assign(n, inf<int>);
    }

    size_t size(int x, int t = inf<int> - 1) {
        int p = find(x,t);
        return prev(lower_bound(begin(siz[p]),end(siz[p]),make_pair(t + 1,1)))->second;
    }

    int find(int x, int t = inf<int> - 1) {
        if(time[x] > t) return x;
        return find(par[x],t);
    }

    bool is_same(int x, int y, int t = inf<int> - 1) { return find(x,t) == find(y,t); }

    int unite(int x, int y) {
        ++clock;
        x = find(x);
        y = find(y);
        if(x != y) {
            size_t sx = siz[x].back().second;
            size_t sy = siz[y].back().second;
            if(sx < sy) {
                swap(x,y), swap(sx,sy);
            }
            siz[x].emplace_back(clock,sx + sy);
            par[y] = x;
            time[y] = clock;
        }
        return clock;
    }
};

