#pragma once
#include "modint.hpp"
#include <vector>
// mod must be prime.
template <int_fast64_t mod = 0>
struct inverse
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
struct inverse<0>
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
template <int_fast64_t mod> std::vector<modint<mod>> inverse<mod>::inv = {1, 1};
std::vector<modint_runtime> inverse<0>::inv;
using inverse_runtime = inverse<0>;
