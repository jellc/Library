#ifndef BINOMIAL_HPP
#define BINOMIAL_HPP
#ifndef MODULO_HPP
#define MODULO_HPP
#include <iostream>
#include <cassert>
template <int mod>
class modint
{
    int val;
  public:
    constexpr modint() : val{0} {}
    constexpr modint(long long x) : val((x %= mod) < 0 ? mod + x : x) {}
    constexpr long long get() const { return val; }
    constexpr modint &operator+=(const modint &other) { return (val += other.val) < mod ? 0 : val -= mod, *this; }
    constexpr modint &operator++() { return ++val, *this; }
    constexpr modint operator++(int) { modint t = *this; return ++val, t; }
    constexpr modint &operator-=(const modint &other) { return (val += mod - other.val) < mod ? 0 : val -= mod, *this; }
    constexpr modint &operator--() { return --val, *this; }
    constexpr modint operator--(int) { modint t = *this; return --val, t; }
    constexpr modint &operator*=(const modint &other) { return val = (long long)val * other.val % mod, *this; }
    constexpr modint &operator/=(const modint &other) { return *this *= inverse(other); }
    constexpr modint operator-() const { return modint(-val); }
    constexpr modint operator+(const modint &other) const { return modint(*this) += other; }
    constexpr modint operator-(const modint &other) const { return modint(*this) -= other; }
    constexpr modint operator*(const modint &other) const { return modint(*this) *= other; }
    constexpr modint operator/(const modint &other) const { return modint(*this) /= other; }
    constexpr bool operator==(const modint &other) const { return val == other.val; }
    constexpr bool operator!=(const modint &other) const { return val != other.val; }
    constexpr bool operator!() const { return !val; }
    template <class T> friend constexpr modint operator+(T x, modint y) { return modint(x) + y; }
    template <class T> friend constexpr modint operator-(T x, modint y) { return modint(x) - y; }
    template <class T> friend constexpr modint operator*(T x, modint y) { return modint(x) * y; }
    template <class T> friend constexpr modint operator/(T x, modint y) { return modint(x) / y; }
    friend constexpr modint inverse(const modint &other)
    {
        assert(other != 0);
        int a{mod}, b{other.val}, u{}, v{1}, t{};
        while(b) t = a / b, a ^= b ^= (a -= t * b) ^= b, u ^= v ^= (u -= t * v) ^= v;
        return modint{u};
    }
    friend constexpr modint pow(modint other, long long e)
    {
        if(e < 0) e = e % (mod - 1) + mod - 1;
        modint res{1};
        while(e) { if(e & 1) res *= other; other *= other, e >>= 1; }
        return res;
    }
    friend std::ostream &operator<<(std::ostream &s, const modint &other) { return s << other.val; }
    friend std::istream &operator>>(std::istream &s, modint &other) { long long val; other = modint{(s >> val, val)}; return s; }
}; // class modint
#endif
namespace binomial
{
    constexpr int mod = 1000000007;
    using binomint = modint<mod>;
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
            constexpr int fact_helper(int x) { assert(x < (int)N); return x < 0 ? 0 : fact_impl_inst._fact[x]; }
            constexpr int invfact_helper(int x) { assert(x < (int)N); return x < 0 ? 0 : fact_impl_inst._invfact[x]; }
            constexpr int inv_helper(int x) { assert(x < (int)N); return x < 0 ? 0 : fact_impl_inst._inv[x]; }
        } // namespace internal_helper
        constexpr binomint fact(int x) { return internal_helper::fact_helper(x); }
        constexpr binomint invfact(int x) { return internal_helper::invfact_helper(x); }
    } // unnamed namespace
    constexpr binomint binom(int x, int y) { return fact(x) * invfact(y) * invfact(x - y); }
    constexpr binomint fallfact(int x, int y) { return fact(x) * invfact(x - y); }
    constexpr binomint risefact(int x, int y) { return fallfact(x + y - 1, y); }
    namespace internal_helper {} // namespace internal_helper
} // namespace binomial
#endif