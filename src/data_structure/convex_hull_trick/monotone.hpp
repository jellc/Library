#include <cassert>
#include <vector>

template <class T = long long>
class lower_convex_monotone
{
    struct line
    {
        T slop, icpt;
        T eval(const T x) const { return slop * x + icpt; }
    };

    std::vector<line> lines;
    typename std::vector<line>::iterator lp, rp;

    void realloc()
    {
        std::vector<line> cpy((rp - lp) * 2);
        cpy.swap(lines);
        rp = copy(lp, rp, lines.begin());
        lp = lines.begin();
    }

public:
    lower_convex_monotone() : lines(2), lp(lines.begin()), rp(lp) {}

    bool empty() const { return lp == rp; }

    void clear() { rp = lp = lines.begin(); }

    void add(const T a, const T b)
    {
        while(rp - lp > 1)
        {
            auto [a1, b1] = *(rp - 1);
            auto [a2, b2] = *(rp - 2);
            if((b - b1) * (a2 - a) > (b - b2) * (a1 - a)) break;
            --rp;
        }
        if(rp == lp) rp = lp = lines.begin();
        if(rp == lines.end()) realloc();
        *rp++ = {a, b};
    }

    T get(const T x)
    {
        assert(!empty());
        while(rp - lp > 1 && lp->eval(x) > (lp + 1)->eval(x)) ++lp;
        return lp->eval(x);
    }
}; // class lower_convex_monotone
