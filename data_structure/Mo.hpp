#include <cassert>
#include <cmath>
#include <functional>
#include <vector>

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
        ord.resize(size());
        for(size_t i = 0; i != size(); ++i) ord[i] = i;
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

    size_t size() const { return lft.size(); }

    void set(size_t l, size_t r)
    {
        assert(!made);
        lft.emplace_back(l), rgt.emplace_back(r);
    }

    size_t process()
    {
        if(!made) make();
        if(itr == ord.end()) return ord.size();
        const size_t id = *itr++, l = lft[id], r = rgt[id];
        while(nl > l) add(--nl);
        while(nr < r) add(nr++);
        while(nl < l) del(nl++);
        while(nr > r) del(--nr);
        return id;
    }
};
