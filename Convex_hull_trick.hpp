template <class K>
class Li_Chao_tree
{
    struct line
    {
        K slop, incp;
        line(K a, K b) : slop(a), incp(b) {}
        K get(K x) const { return slop * x + incp; }
    }; // struct line
    struct node
    {
        line ln;
        node *left, *right;
        node(const line &l) : ln(l), left(nullptr), right(nullptr) {}
        ~node() { delete left; delete right; }
        K get(K x) const { return ln.get(x); }
    }; // struct node

    const K x_min, x_max, eps;
    using comp_t = std::function<bool(const K &, const K &)>;
    const comp_t comp;
    const K identity;
    node *root;

    // insert a line for the interval [l, r).
    node *insert(node *const p, const K l, const K r, line ln)
    {
        if(not p) return new node(ln);
        bool lcmp = comp(ln.get(l), p->get(l));
        bool rcmp = comp(ln.get(r - eps), p->get(r - eps));
        if(lcmp == rcmp)
        {
            if(lcmp) p->ln = ln;
            return p;
        }
        if(r - l <= eps) return p;
        const K mid = (l + r) / 2;
        if(comp(ln.get(mid), p->get(mid)))
        {
            std::swap(p->ln, ln);
            lcmp = not lcmp;
        }
        if(lcmp) p->left = insert(p->left, l, mid, ln);
        else p->right = insert(p->right, mid, r, ln);
        return p;
    }

    // insert a segment for the interval [l, r).
    node *insert(node *const p, const K l, const K r, line ln, const K s, const K t)
    {
        if(t - eps < l or r - eps < s) return p;
        const K mid = (l + r) / 2;
        if(l < s or t < r)
        {
            p->left = insert(p->left, l, mid, ln, s, t);
            p->right = insert(p->right, mid, r, ln, s, t);
            return p;
        }
        if(not p) return new node(ln);
        bool lcmp = comp(ln.get(l), p->get(l));
        bool rcmp = comp(ln.get(r - eps), p->get(r - eps));
        if(lcmp == rcmp)
        {
            if(lcmp) p->ln = ln;
            return p;
        }
        if(r - l <= eps) return p;
        if(comp(ln.get(mid), p->get(mid)))
        {
            std::swap(p->ln, ln);
            lcmp = not lcmp;
        }
        if(lcmp) p->left = insert(p->left, l, mid, ln, s, t);
        else p->right = insert(p->right, mid, r, ln, s, t);
        return p;
    }

  public:
    // domain set to be the interval [x_min, x_max).
    Li_Chao_tree(const K _x_min, const K _x_max, const K _eps = K(1), const comp_t &_comp = std::less<K>(), const K _identity = std::numeric_limits<K>::max())
        : x_min(_x_min), x_max(_x_max), eps(_eps), comp(_comp), identity(_identity), root() {}
    ~Li_Chao_tree() { delete root; }

    bool empty() const { return !root; }

    // insert a line whose slope is p and inception is q.
    void insert(const K p, const K q) { root = insert(root, x_min, x_max, line(p, q)); }

    // insert a line(segment) whose slope is p, inception is q,
    // and domain is the interval [s, t).
    void insert(const K p, const K q, const K s, const K t) { if(s < t) root = insert(root, x_min, x_max, line(p, q), s, t); }

    // get the value at x.
    K query(const K x) const
    {
        node *p = root;
        K l = x_min, r = x_max;
        K res = identity;
        while(p)
        {
            if(comp(p->get(x), res)) res = p->get(x);
            if(r - l <= eps) return res;
            const K mid = (l + r) / 2;
            if(x < mid)
            {
                p = p->left;
                r = mid;
            }
            else
            {
                p = p->right;
                l = mid;
            }
        }
        return res;
    }
}; // class Li_Chao_tree
