#include <cassert>
#include <cmath>
#include <functional>
#include <vector>
#include <numeric>

template <class Add, class Del>
class Mo
{
    Add add; Del del;
    std::vector<size_t> lft, rgt, ord;
    std::vector<size_t>::iterator itr;
    bool made;
    size_t width, nl, nr;

    void make()
    {
        made = true;
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

public:
    Mo(size_t n = 0, Add add = Add(), Del del = Del())
        : add(add), del(del), made(), width(sqrt(n)), nl(), nr() {}

    void set(size_t l, size_t r)
    {
        assert(!made);
        lft.emplace_back(l), rgt.emplace_back(r);
    }

    size_t process()
    {
        if(!made) make();
        if(itr == ord.end()) return ord.size();
        size_t now = *itr++;
        while(nl > lft[now]) add(--nl);
        while(nr < rgt[now]) add(nr++);
        while(nl < lft[now]) del(nl++);
        while(nr > rgt[now]) del(--nr);
        return now;
    }
};
