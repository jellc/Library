#include <bits/stdc++.h>

class union_find
{
    std::vector<int> dat;
    bool *const cyc, *const clr, *const flip;
    size_t comp, isol;
    bool bipart;

  public:
    explicit union_find(const int n) : dat(n, -1), cyc(new bool[n]{}), clr(new bool[n]{}), flip(new bool[n]{}), comp(n), isol(n), bipart(true) {}
    ~union_find() { delete[] cyc; delete[] clr; delete[] flip; }

    int find(const int x)
    {
        assert(x < size());
        if(dat[x] < 0) return x;
        const int r = find(dat[x]);
        if(flip[dat[x]])
        {
            clr[x] = !clr[x];
            flip[x] = !flip[x];
        }
        return dat[x] = r;
    }

    size_t size() const { return dat.size(); }
    size_t size(const int x) { return -dat[find(x)]; }

    size_t count() const { return comp; }

    size_t isolated() const { return isol; }

    bool color(const int x) { return find(x), clr[x]; }

    bool cyclic(const int x) { return cyc[find(x)]; }

    bool same(const int x, const int y) { return find(x) == find(y); }

    bool bipartite() const { return bipart; }

    bool unite(int x, int y)
    {
        const int _x = find(x);
        const int _y = find(y);
        const bool f = clr[x] == clr[y];
        x = _x, y = _y;
        if(x == y)
        {
            bipart &= !f;
            cyc[x] = true;
            return false;
        }
        if(dat[x] > dat[y]) std::swap(x, y);
        if(dat[x] == -1) --isol;
        if(dat[y] == -1) --isol;
        dat[x] += dat[y];
        dat[y] = x;
        cyc[x] = cyc[x] || cyc[y];
        if(f)
        {
            clr[y] = !clr[y];
            flip[y] = !flip[y];
        }
        --comp;
        return true;
    }
}; // class union_find


template <class T>
class ext_union_find
{
    std::vector<int> link;
    T *const dat;
    const std::function<void(T&, T&)> merge;

  public:
    ext_union_find(const int n, const std::function<void(T&, T&)> &f) : link(n, -1), dat(new T[n]), merge(f) {}
    ext_union_find(const int n, const T &x, const std::function<void(T&, T&)> &f) : link(n, -1), dat(new T[n](x)), merge(f) {}
    ~ext_union_find() { delete[] dat; }

    int find(const int x) { assert(x < size()); return link[x] < 0 ? x : (link[x] = find(link[x])); }

    size_t size() const { return link.size(); }
    size_t size(const int x) { return -link[find(x)]; }

    bool same(const int x, const int y) { return find(x) == find(y); }

    bool unite(int x, int y)
    {
        if((x = find(x)) == (y = find(y))) return false;
        if(link[x] > link[y]) std::swap(x, y);
        link[x] += link[y], link[y] = x;
        merge(dat[x], dat[y]);
        return true;
    }

    T &operator[](const int x) { return dat[find(x)]; }
}; // class ext_union_find


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

    bool same(int x, int y)
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
}; // struct WeightedUF


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

    bool same(int x, int y, int t = inf<int> - 1)
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
}; // struct PersistentUF
