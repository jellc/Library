// #line 2 "Z_algorithm_hpp"
#ifndef Z_algorithm_hpp
#define Z_algorithm_hpp
#include <string>

template <class A = std::string>
class Z_algorithm
{
    const A key;
    const size_t len;
    std::vector<size_t> z;
    bool is_built;
  public:
    Z_algorithm(const A &_key) : key(_key), len(_key.size()), is_built(false) {}

    const std::vector<size_t> &build()
    {
        assert(len);
        is_built = true;
        z.assign(len, 0);
        for(size_t i{1}, j{0}; i != len; ++i)
        {
            if(z[i - j] + i < z[j] + j)
            {
                z[i] = z[i - j];
            }
            else
            {
                size_t k{z[j] + j > i ? z[j] + j - i : 0};
                while(k + i < len && key[k] == key[k + i]) ++k;
                z[i] = k;
                j = i;
            }
        }
        z.front() = len;
        return z;
    }

    size_t size() const { return len; }
    size_t operator[](size_t i) const { return build(), z[i]; }

    std::vector<size_t> pattern_search(const A &str) const
    {
        A tmp(key);
        tmp.insert(end(tmp), begin(str), end(str));
        Z_algorithm other(tmp);
        const auto &nz(other.build());
        std::vector<size_t> res(nz.begin() + len, nz.end());
        for(size_t &x : res) if(x > len) x = len;
        return res;
    }
};

#endif
