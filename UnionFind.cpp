#include <bits/stdc++.h>

class Union_Find
{
    std::vector<int> dat;
    std::vector<bool> cyc, clr, flip;
    size_t comp, isol;
    bool is_bip;

  public:
    Union_Find(int n)
    {
        init(n);
    }

    void init(int n)
    {
        dat.assign(n, -1);
        cyc.assign(n, false);
        clr.assign(n, false);
        flip.assign(n, false);
        comp = isol = n;
        is_bip = true;
    }

    int find(int x)
    {
        if(dat[x] < 0) return x;
        int r = find(dat[x]);
        if(flip[dat[x]])
        {
            clr[x] = not clr[x];
            flip[x] = not flip[x];
        }
        return dat[x] = r;
    }

    size_t count() const
    {
        return comp;
    }

    size_t size(int x)
    {
        return -dat[find(x)];
    }

    size_t isolated() const
    {
        return isol;
    }

    bool color(int x)
    {
        find(x);
        return clr[x];
    }

    bool is_cyclic(int x)
    {
        return cyc[find(x)];
    }

    bool is_same(int x, int y)
    {
        return find(x) == find(y);
    }

    bool is_bipartite() const
    {
        return is_bip;
    }

    bool unite(int x, int y)
    {
        int _x = find(x);
        int _y = find(y);
        bool f = clr[x] == clr[y];
        x = _x, y = _y;
        if(x == y)
        {
            if(f)
            {
                is_bip = false;
            }
            cyc[x] = true;
            return false;
        }
        if(dat[x] > dat[y]) std::swap(x, y);
        if(dat[y] == -1)
        {
            --isol;
            if(dat[x] == -1)
            {
                --isol;
            }
        }
        dat[x] += dat[y];
        dat[y] = x;
        cyc[x] = cyc[x] || cyc[y];
        if(f)
        {
            clr[y] = not clr[y];
            flip[y] = not flip[y];
        }
        --comp;
        return true;
    }
};

template <class T>
class Union_find
{
    std::vector<int> link;
    std::vector<T> dat;
    const std::function<void(T &, T &)> merge;
 
  public:
    Union_find(int n, const std::function<void(T &, T &)> &f) : link(n, -1), dat(n), merge(f) {}
    
    Union_find(int n, const T &x, const std::function<void(T &, T &)> &f) : link(n, -1), dat(n, x), merge(f) {}
 
    int find(int x) { return link[x] < 0 ? x : (link[x] = find(link[x])); }
 
    size_t size(int x) { return -link[find(x)]; }
 
    bool is_same(int x, int y) { return find(x) == find(y); }
 
    bool unite(int x, int y)
    {
        if((x = find(x)) == (y = find(y))) return false;
        if(link[x] > link[y]) std::swap(x, y);
        link[x] += link[y], link[y] = x;
        merge(dat[x], dat[y]);
        return true;
    }
 
    T &operator[](int x) { return dat[find(x)]; }
};

template <class Abel>
struct WeightedUF
{
    vector<int> par, _size;
    vector<Abel> diff_weight;

    explicit WeightedUF(int n)
    {
        init(n);
    }

    void init(int n)
    {
        par.resize(n);
        std::iota(par.begin(), par.end(), 0);
        _size.assign(n, 1);
        diff_weight.resize(n);
    }

    int find(int x)
    {
        if(par[x]) return x;
        int r = find(par[x]);
        diff_weight[x] += diff_weight[par[x]];
        return par[x] = r;
    }

    size_t size(int x)
    {
        return _size[find(x)];
    }

    Abel weight(int x)
    {
        find(x);
        return diff_weight[x];
    }

    Abel diff(int x, int y)
    {
        return weight(y) - weight(x);
    }

    bool is_same(int x, int y)
    {
        return find(x) == find(y);
    }

    bool unite(int x, int y, Abel w = 0)
    {
        w += weight(x);
        w += weight(y);
        x = find(x);
        y = find(y);
        if(x == y) return false;
        if(_size[x] < _size[y])
        {
            std::swap(x, y);
            w = -w;
        }
        _size[x] += _size[y];
        par[y] = x;
        diff_weight[y] = w;
        return true;
    }
};

struct PersistentUF
{
    template <class T>
    static constexpr T inf = std::numeric_limits<T>::max() / T(2) - T(1123456);
    std::vector<int> par;
    std::vector<int> time;
    std::vector<std::vector<std::pair<int, int>>> _size;
    int clock;

    explicit PersistentUF(int n) : clock()
    {
        init(n);
    }

    void init(int n)
    {
        par.resize(n);
        std::iota(par.begin(), par.end(), 0);
        _size.resize(n, std::vector<std::pair<int, int>>(1, {0, 1}));
        time.assign(n, inf<int>);
    }

    std::size_t size(int x, int t = inf<int> - 1)
    {
        int p = find(x, t);
        return std::prev(std::lower_bound(_size[p].begin(), _size[p].end(),
                                          std::make_pair(t + 1, 1)))
            ->second;
    }

    int find(int x, int t = inf<int> - 1)
    {
        if(time[x] > t) return x;
        return find(par[x], t);
    }

    bool is_same(int x, int y, int t = inf<int> - 1)
    {
        return find(x, t) == find(y, t);
    }

    int unite(int x, int y)
    {
        ++clock;
        x = find(x);
        y = find(y);
        if(x != y)
        {
            std::size_t sx = _size[x].back().second;
            std::size_t sy = _size[y].back().second;
            if(sx < sy)
            {
                std::swap(x, y), std::swap(sx, sy);
            }
            _size[x].emplace_back(clock, sx + sy);
            par[y] = x;
            time[y] = clock;
        }
        return clock;
    }
};
