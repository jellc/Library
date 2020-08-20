#pragma once
#include "factorial.hpp"
#include "modulus/modint.hpp"
#include "modulus/inverse.hpp"
template <int_fast64_t mod>
struct binomial
{
    using value_type = modint<mod>;
    struct mulinv_Op
    {
        inverse<mod> &inv;
        value_type operator()(value_type f, size_t n) const { return f * inv(n); }
    };
    static inverse<mod> inv;
    static factorial<value_type, mulinv_Op> invfact;
    static factorial<value_type> fact;
    value_type operator()(int n, int k) { return invfact(k) * invfact(n - k) * fact(n); }
};
template <int_fast64_t mod> inverse<mod> binomial<mod>::inv;
template <int_fast64_t mod> factorial<modint<mod>, class binomial<mod>::mulinv_Op> binomial<mod>::invfact{1, mulinv_Op{binomial<mod>::inv}};
template <int_fast64_t mod> factorial<modint<mod>> binomial<mod>::fact;
