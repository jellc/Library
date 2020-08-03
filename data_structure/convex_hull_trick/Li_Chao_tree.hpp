#include <cassert>
#include <functional>

template <class T = long long, class Comp = std::less<T>, T infty = std::numeric_limits<T>::max()>
class Li_Chao_tree
{
    struct line
    {
        T slop = 0, icpt = infty;
        line *lch = nullptr, *rch = nullptr;
        ~line() { delete lch; delete rch; }
        line *swap(line &rhs) { std::swap(slop, rhs.slop); std::swap(icpt, rhs.icpt); return this; }
        T eval(const T x) const { return slop * x + icpt; }
    }; // struct line

    T lower, upper, eps;
    Comp comp;
    line *root = nullptr;

    // // insert a line for the interval [l, r).
    line *insert(line *const p, const T l, const T r, line ln)
    {
        if(!p) return new line(ln);
        bool lcmp = comp(ln.eval(l), p->eval(l));
        bool rcmp = comp(ln.eval(r - eps), p->eval(r - eps));
        if(lcmp == rcmp) return lcmp ? p->swap(ln) : p;
        if(r - l <= eps) return p;
        T mid = (l + r) / 2;
        if(comp(ln.eval(mid), p->eval(mid)))
        {
            p->swap(ln);
            lcmp = !lcmp;
        }
        if(lcmp) p->lch = insert(p->lch, l, mid, ln);
        else p->rch = insert(p->rch, mid, r, ln);
        return p;
    }

    // // insert a segment for the interval [l, r).
    line *insert(line *const p, const T l, const T r, line ln, const T s, const T t)
    {
        if(t - eps < l || r - eps < s) return p;
        T mid = (l + r) / 2;
        if(l < s or t < r)
        {
            line *np = p ? p : new line;
            np->lch = insert(np->lch, l, mid, ln, s, t);
            np->rch = insert(np->rch, mid, r, ln, s, t);
            return np;
        }
        if(!p) return new line(ln);
        bool lcmp = comp(ln.eval(l), p->eval(l));
        bool rcmp = comp(ln.eval(r - eps), p->eval(r - eps));
        if(lcmp == rcmp) return lcmp ? p->swap(ln) : p;
        if(r - l <= eps) return p;
        if(comp(ln.eval(mid), p->eval(mid)))
        {
            p->swap(ln);
            lcmp = !lcmp;
        }
        if(lcmp) p->lch = insert(p->lch, l, mid, ln, s, t);
        else p->rch = insert(p->rch, mid, r, ln, s, t);
        return p;
    }

public:
    // domain set to be the interval [lower, upper).
    Li_Chao_tree(const T lower, const T upper, const T eps = 1, Comp comp = Comp())
        : lower(lower), upper(upper), eps(eps), comp(comp) {}

    ~Li_Chao_tree() { delete root; }

    bool empty() const { return !root; }

    // insert a line whose slope is p and inception is q.
    void insert(const T p, const T q) { root = insert(root, lower, upper, line{p, q}); }

    // insert a line(segment) whose slope is p, inception is q,
    // and domain is the interval [s, t).
    void insert(const T p, const T q, const T s, const T t) { if(s < t) root = insert(root, lower, upper, line{p, q}, s, t); }

    T get(const T x) const
    {
        line *p = root;
        T l = lower, r = upper;
        T res = infty;
        while(p)
        {
            T nval = p->eval(x);
            if(comp(nval, res)) res = nval;
            if(r - l <= eps) return res;
            T mid = (l + r) / 2;
            if(x < mid)
            {
                p = p->lch;
                r = mid;
            }
            else
            {
                p = p->rch;
                l = mid;
            }
        }
        return res;
    }
}; // class Li_Chao_tree
