#include <cmath>
#include <functional>
#include <vector>
#include <numeric>

class Mo
{
    using updater = std::function<void(size_t)>;
    updater add, rmv;
    std::vector<size_t> lft, rgt, ord;
    bool is_built;
    const size_t width;
    size_t nl, nr;
    std::vector<size_t>::iterator itr;

public:
    Mo(size_t _n, updater _add, updater _rmv)
        : add(_add), rmv(_rmv), is_built(), width(std::sqrt(_n)), nl(0), nr(0)
    {}

    size_t left() const { return nl; }
    size_t right() const { return nr; }

    void insert(size_t l, size_t r)
    {
        lft.emplace_back(l), rgt.emplace_back(r);
        is_built = false;
    }

    void build()
    {
        is_built = true;
        ord.resize(lft.size());
        std::iota(ord.begin(), ord.end(), 0);
        std::sort(ord.begin(), ord.end(),
        [&](size_t x, size_t y)
        {
            if(lft[x] / width != lft[y] / width) return lft[x] < lft[y];
            return rgt[x] < rgt[y];
        });
        itr = ord.begin();
    }

    size_t process()
    {
        if(!is_built) build();
        if(itr == ord.end()) return ord.size();
        const size_t now = *itr;
        while(nl > lft[now]) add(--nl);
        while(nr < rgt[now]) add(nr++);
        while(nl < lft[now]) rmv(nl++);
        while(nr > rgt[now]) rmv(--nr);
        return *itr++;
    }
};
