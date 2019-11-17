#include <bits/stdc++.h>

namespace math
{
    namespace binomial
    {
        constexpr int mod = 998244353;
        namespace internal
        {
            constexpr size_t N = 1 << 20;
            constexpr size_t loop_limit = 1 << 17;
            struct fact_impl
            {
                int _fact[N], _inv[N], _invfact[N];
                constexpr fact_impl() : _fact{1}, _inv{0, 1}, _invfact{1}
                {
                    size_t itr = 1; while(itr < N) for(size_t j = 0; j < loop_limit && itr < N; ++itr, ++j) _fact[itr] = (long long)_fact[itr - 1] * itr % mod;
                    itr = 2; while(itr < N) for(size_t j = 0; j < loop_limit && itr < N; ++itr, ++j) _inv[itr] = mod - (long long)_inv[mod % itr] * (mod / itr) % mod;
                    itr = 1; while(itr < N) for(size_t j = 0; j < loop_limit && itr < N; ++itr, ++j) _invfact[itr] = (long long)_invfact[itr - 1] * _inv[itr] % mod;
                }
            }; // struct fact_impl
            constexpr fact_impl fact_impl_inst;
            constexpr int fact_helper(int x) { assert(x < (int)N); return x < 0 ? 0 : fact_impl_inst._fact[x]; }
            constexpr int invfact_helper(int x) { assert(x < (int)N); return x < 0 ? 0 : fact_impl_inst._invfact[x]; }
            constexpr int inv_helper(int x) { assert(x < (int)N); return x < 0 ? 0 : fact_impl_inst._inv[x]; }
        } // namespace internal
        class modint
        {
            int dat;
          public:
            constexpr modint() : dat{0} {}
            constexpr modint(long long y) : dat((y %= mod) < 0 ? mod + y : y) {}
            constexpr long long get() const { return dat; }
            constexpr modint &operator+=(const modint &other) { return (dat += other.dat) < mod ? 0 : dat -= mod, *this; }
            constexpr modint &operator++() { return ++dat, *this; }
            constexpr modint operator++(int) { modint t = *this; return ++dat, t; }
            constexpr modint &operator-=(const modint &other) { return (dat += mod - other.dat) < mod ? 0 : dat -= mod, *this; }
            constexpr modint &operator--() { return --dat, *this; }
            constexpr modint operator--(int) { modint t = *this; return --dat, t; }
            constexpr modint &operator*=(const modint &other) { return dat = (long long)dat * other.dat % mod, *this; }
            friend constexpr modint inverse(const modint &other);
            constexpr modint &operator/=(const modint &other) { return *this *= inverse(other); }
            constexpr modint operator-() const { return modint(-dat); }
            constexpr modint operator+(const modint &other) const { return modint(*this) += other; }
            constexpr modint operator-(const modint &other) const { return modint(*this) -= other; }
            constexpr modint operator*(const modint &other) const { return modint(*this) *= other; }
            constexpr modint operator/(const modint &other) const { return modint(*this) /= other; }
            constexpr bool operator==(const modint &other) const { return dat == other.dat; }
            constexpr bool operator!=(const modint &other) const { return dat != other.dat; }
            constexpr bool operator!() const { return !dat; }
            friend constexpr modint inverse(const modint &other)
            {
                if(other.dat < (int)internal::N) return internal::inv_helper(other.dat);
                int a{other.dat}, b{mod}, u{1}, v{}, t{};
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
            friend std::ostream &operator<<(std::ostream &s, const modint &other) { return s << other.dat; }
            friend std::istream &operator>>(std::istream &s, modint &other) { long long dat; other = modint{(s >> dat, dat)}; return s; }
        }; // class modint
        constexpr modint fact(int x) { return internal::fact_helper(x); }
        constexpr modint invfact(int x) { return internal::invfact_helper(x); }
        constexpr modint binom(int x, int y) { return fact(x) * invfact(y) * invfact(x - y); }
        constexpr modint fallfact(int x, int y) { return fact(x) * invfact(x - y); }
        constexpr modint risefact(int x, int y) { return fallfact(x + y - 1, y); }
    } // namespace binomial
    using namespace binomial;
    namespace internal {}
} // namespace math