#include <vector>

template <class expr>
struct xor_elimination
{
    std::vector<expr> base;
    bool add(expr e)
    {
        for(const expr &b : base) if((b ^ e) < e) e ^= b;
        if(e) base.emplace_back(e);
        return e;
    }
    size_t dim() const { return base.size(); }
};
