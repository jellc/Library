#pragma once
#include "modint.hpp"
#include <vector>
template <class> struct inverse;
// mod must be prime.
template <int_fast64_t mod>
struct inverse<modint<mod>>
{
    using value_type = modint<mod>;
    value_type operator()(int n) const
    {
        assert(n %= mod);
        if(n < 0) n += mod;
        for(int m(inv.size()); m <= n; ++m) inv.emplace_back(mod / m * -inv[mod % m]);
        return inv[n];
    }
private:
    static std::vector<value_type> inv;
};
template <>
struct inverse<modint_runtime>
{
    using value_type = modint_runtime;
    value_type operator()(int n) const
    {
        int_fast64_t mod = value_type::mod();
        assert(n %= mod);
        if(n < 0) n += mod;
        if(inv.empty()) inv = {1, mod != 1};
        for(int m(inv.size()); m <= n; ++m) inv.emplace_back(mod / m * -inv[mod % m]);
        return inv[n];
    }
private:
    static std::vector<value_type> inv;
};
template <int_fast64_t mod> std::vector<modint<mod>> inverse<modint<mod>>::inv = {1, 1};
std::vector<modint_runtime> inverse<modint_runtime>::inv;
