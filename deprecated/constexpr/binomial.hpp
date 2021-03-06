#ifndef modint_hpp
#define modint_hpp
#include <cassert>
#include <iostream>

template <int mod>
class modint
{
    int val;
public:
    constexpr modint() noexcept : val{0} {}
    constexpr modint(long long x) noexcept : val((x %= mod) < 0 ? mod + x : x) {}
    constexpr long long value() const noexcept { return val; }
    constexpr modint operator++(int) noexcept { modint t = *this; return ++val, t; }
    constexpr modint operator--(int) noexcept { modint t = *this; return --val, t; }
    constexpr modint &operator++() noexcept { return ++val, *this; }
    constexpr modint &operator--() noexcept { return --val, *this; }
    constexpr modint operator-() const noexcept { return modint(-val); }
    constexpr modint &operator+=(const modint &other) noexcept { return (val += other.val) < mod ? 0 : val -= mod, *this; }
    constexpr modint &operator-=(const modint &other) noexcept { return (val += mod - other.val) < mod ? 0 : val -= mod, *this; }
    constexpr modint &operator*=(const modint &other) noexcept { return val = (long long)val * other.val % mod, *this; }
    constexpr modint &operator/=(const modint &other) noexcept { return *this *= inverse(other); }
    constexpr modint operator+(const modint &other) const noexcept { return modint(*this) += other; }
    constexpr modint operator-(const modint &other) const noexcept { return modint(*this) -= other; }
    constexpr modint operator*(const modint &other) const noexcept { return modint(*this) *= other; }
    constexpr modint operator/(const modint &other) const noexcept { return modint(*this) /= other; }
    constexpr bool operator==(const modint &other) const noexcept { return val == other.val; }
    constexpr bool operator!=(const modint &other) const noexcept { return val != other.val; }
    constexpr bool operator!() const noexcept { return !val; }
    friend constexpr modint operator+(long long x, modint y) noexcept { return modint(x) + y; }
    friend constexpr modint operator-(long long x, modint y) noexcept { return modint(x) - y; }
    friend constexpr modint operator*(long long x, modint y) noexcept { return modint(x) * y; }
    friend constexpr modint operator/(long long x, modint y) noexcept { return modint(x) / y; }
    static constexpr modint inverse(const modint &other) noexcept
    {
        assert(other != 0);
        int a{mod}, b{other.val}, u{}, v{1}, t{};
        while(b) t = a / b, a ^= b ^= (a -= t * b) ^= b, u ^= v ^= (u -= t * v) ^= v;
        return {u};
    }
    static constexpr modint pow(modint other, long long e) noexcept
    {
        if(e < 0) e = e % (mod - 1) + mod - 1;
        modint res{1};
        while(e) { if(e & 1) res *= other; other *= other, e >>= 1; }
        return res;
    }
    friend std::ostream &operator<<(std::ostream &os, const modint &other) noexcept { return os << other.val; }
    friend std::istream &operator>>(std::istream &is, modint &other) noexcept { long long val; other = {(is >> val, val)}; return is; }
}; // class modint

#endif // modint_hpp

#ifndef binomial_hpp
#define binomial_hpp

namespace binomial
{
    constexpr int mod = 1000000007;
    using mint = modint<mod>;
    namespace
    {
        namespace internal_helper
        {
            constexpr int N = 1 << 20;
            constexpr int loop_limit = 1 << 17;
            struct fact_impl
            {
                int _fact[N], _inv[N], _invfact[N];
                constexpr fact_impl() : _fact{1}, _inv{0, 1}, _invfact{1}
                {
                    int itr = 1; while(itr < N) for(int j = 0; j < loop_limit && itr < N; ++itr, ++j) _fact[itr] = (long long)_fact[itr - 1] * itr % mod;
                    itr = 2; while(itr < N) for(int j = 0; j < loop_limit && itr < N; ++itr, ++j) _inv[itr] = mod - (long long)_inv[mod % itr] * (mod / itr) % mod;
                    itr = 1; while(itr < N) for(int j = 0; j < loop_limit && itr < N; ++itr, ++j) _invfact[itr] = (long long)_invfact[itr - 1] * _inv[itr] % mod;
                }
            }; // struct fact_impl
            constexpr fact_impl fact_impl_inst;
            constexpr int fact_helper(int x) noexcept { assert(x < (int)N); return x < 0 ? 0 : fact_impl_inst._fact[x]; }
            constexpr int invfact_helper(int x) noexcept { assert(x < (int)N); return x < 0 ? 0 : fact_impl_inst._invfact[x]; }
            constexpr int inv_helper(int x) noexcept { assert(x < (int)N); return x < 0 ? 0 : fact_impl_inst._inv[x]; }
        } // namespace internal_helper
        constexpr mint fact(int x) noexcept { return internal_helper::fact_helper(x); }
        constexpr mint invfact(int x) noexcept { return internal_helper::invfact_helper(x); }
    } // unnamed namespace
    constexpr mint binom(int n, int k) noexcept { return fact(n) * invfact(k) * invfact(n - k); }
    constexpr mint fallfact(int n, int k) noexcept { return fact(n) * invfact(n - k); }
    constexpr mint risefact(int n, int k) noexcept { return fallfact(n + k - 1, k); }
    // time complexity: O(min(n, k) * log(n))
    constexpr mint stirling_2nd(int n, int k) noexcept
    {
        if(n < k) return 0;
        mint res{};
        for(int i{}, j{k}; j >= 0; ++i, --j)
            if(i & 1) res -= mint::pow(j, n) * invfact(j) * invfact(i);
            else res += mint::pow(j, n) * invfact(j) * invfact(i);
        return res;
    };
    // time complexity: O(min(n, k) * log(n))
    constexpr mint bell(int n, int k) noexcept
    {
        if(n < k) k = n;
        mint res{}, alt{};
        for(int i{}, j{k}; j >= 0; ++i, --j)
        {
            if(i & 1) alt -= invfact(i);
            else alt += invfact(i);
            res += alt * mint::pow(j, n) * invfact(j);
        }
        return res;
    }
    namespace internal_helper {} // namespace internal_helper
} // namespace binomial

#endif // binomial_hpp
