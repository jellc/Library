#include <cassert>
#include <vector>

template <class Ring>
std::vector<Ring> subset_convolute(const std::vector<Ring> &f, const std::vector<Ring> &g)
{
    assert(!f.empty()); assert(!g.empty());
    const size_t n = __builtin_ctz(std::min(f.size(), g.size()));
    std::vector ff(n + 1, std::vector<Ring>(1 << n)), gg(ff);
    ff[0] = f, gg[0] = g;
    for(size_t k = 0; k != n; ++k)
    {
        for(size_t i = k + 1; ~i; --i)
        {
            for(size_t s = 0; s != 1u << n; ++s)
            {
                if(s >> k & 1)
                {
                    if(i)
                    {
                        ff[i][s] = ff[i - 1][s];
                        gg[i][s] = gg[i - 1][s];
                    }
                    else
                    {
                        ff[i][s] = gg[i][s] = Ring{};
                    }
                    ff[i][s] += ff[i][s ^ 1 << k];
                    gg[i][s] += gg[i][s ^ 1 << k];
                }
            }
        }
    }
    for(size_t i = n; ~i; --i)
    {
        for(size_t s = 0; s != 1u << n; ++s)
        {
            ff[i][s] *= gg[0][s];
            for(size_t j = i; j; --j)
            {
                ff[i][s] += ff[i - j][s] * gg[j][s];
            }
        }
    }
    for(size_t k = n - 1; ~k; --k)
    {
        for(size_t s = 0; s != 1u << n; ++s)
        {
            if(~s >> k & 1)
            {
                for(size_t i = n; ~i; --i)
                {
                    ff[i][s ^ 1 << k] -= ff[i][s];
                    if(i) ff[i][s] = ff[i - 1][s];
                }
            }
        }
    }
    return ff[n];
}
