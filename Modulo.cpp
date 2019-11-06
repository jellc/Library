#include <bits/stdc++.h>

namespace math
{
    using i32 = int_least32_t; using i64 = int_least64_t;

    template <i32 mod>
    class modint
    {
        i32 dat;

      public:
        constexpr modint() : dat(0) {}
        constexpr modint(i64 y) : dat(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}
        constexpr i64 get() const { return dat; }

        constexpr modint &operator+=(const modint &p)
        {
            return (dat += p.dat) < mod ? 0 : dat -= mod, *this;
        }

        constexpr modint &operator++()
        {
            return ++dat, *this;
        }

        constexpr modint operator++(i32)
        {
            modint t = *this;
            return ++dat, t;
        }

        constexpr modint &operator-=(const modint &p)
        {
            return (dat += mod - p.dat) < mod ? 0 : dat -= mod, *this;
        }

        constexpr modint &operator--()
        {
            return --dat, *this;
        }

        constexpr modint operator--(i32)
        {
            modint t = *this;
            return --dat, t;
        }

        constexpr modint &operator*=(const modint &p)
        {
            return dat = (int_fast64_t)dat * p.dat % mod, *this;
        }

        constexpr modint &operator/=(const modint &p)
        {
            return *this *= inverse(p);
        }

        // constexpr modint &operator%=(i32 m) { return dat %= m, *this; }

        constexpr modint operator-() const
        {
            return modint(-dat);
        }

        constexpr modint operator+(const modint &p) const
        {
            return modint(*this) += p;
        }

        constexpr modint operator-(const modint &p) const
        {
            return modint(*this) -= p;
        }

        constexpr modint operator*(const modint &p) const
        {
            return modint(*this) *= p;
        }

        constexpr modint operator/(const modint &p) const
        {
            return modint(*this) /= p;
        }

        // constexpr modint operator%(i32 m) const { return modint(*this) %= m;
        // }

        constexpr bool operator==(const modint &p) const
        {
            return dat == p.dat;
        }

        constexpr bool operator!=(const modint &p) const
        {
            return dat != p.dat;
        }

        constexpr bool operator!() const
        {
            return !dat;
        }

        // constexpr bool operator>(const modint &p) const { return dat > p.dat; }

        // constexpr bool operator<(const modint &p) const { return dat <  p.dat; }

        // constexpr bool operator>=(const modint &p) const { return dat >= p.dat; }

        // constexpr bool operator<=(const modint &p) const { return dat <= p.dat; }

        constexpr friend modint<mod> inverse(const modint<mod> &p)
        {
            i32 a = p.dat, b = mod, u = 1, v = 0;
            while(b > 0)
            {
                i32 t = a / b;
                a -= t * b;
                a ^= b ^= a ^= b;
                u -= t * v;
                u ^= v ^= u ^= v;
            }
            return modint(u);
        }

        constexpr friend modint pow(modint p, i64 e)
        {
            if(e < 0) e = (e % (mod - 1) + mod - 1) % (mod - 1);
            modint ret = 1;
            while(e)
            {
                if(e & 1) ret *= p;
                p *= p;
                e >>= 1;
            }
            return ret;
        }

        friend std::ostream &operator<<(std::ostream &s, const modint &p)
        {
            return s << p.dat;
        }

        friend std::istream &operator>>(std::istream &s, modint &p)
        {
            int_least64_t dat;
            p = modint((s >> dat, dat));
            return s;
        }
    };
} // namespace math

// require modint
namespace math
{
    constexpr i32 mod = 1000000007;
    constexpr size_t N = 2.5e5, ext_N = 2.2e6;

    class fact_impl
    {
        i32 _fact[N], _invfact[N], _inv[N];
        static i32 _ext_fact[], _ext_invfact[], _ext_inv[];
        static size_t fact_itr, invfact_itr, inv_itr;

      public:
        constexpr fact_impl() : _fact(), _invfact(), _inv()
        {
            _fact[0] = 1;
            for(size_t i = 1; i < N; ++i)
                _fact[i] = (i64)_fact[i - 1] * i % mod;
            _inv[1] = 1;
            for(size_t i = 2; i < N && i < mod; ++i)
                _inv[i] = mod - (i64)_inv[mod % i] * (mod / i) % mod;
            _invfact[0] = 1;
            for(size_t i = 1; i < N && i < mod; ++i)
                _invfact[i] = (i64)_invfact[i - 1] * _inv[i] % mod;
        }

        i32 ext_fact(i32 x) const
        {
            assert(x < (i32)ext_N);
            if(x < 0) return 0;
            if(not fact_itr)
            {
                _ext_fact[N - 1] = _fact[N - 1];
                fact_itr = N;
            }
            for(size_t &i = fact_itr; (i32)i <= x; ++i)
            {
                _ext_fact[i] = (int_fast64_t)_ext_fact[i - 1] * i % mod;
            }
            return x < (i32)N ? _fact[x] : _ext_fact[x];
        }

        i32 ext_inv(i32 x) const
        {
            assert(x < (i32)ext_N and x % mod);
            for(size_t &i = inv_itr, r; (i32)i <= x; ++i)
            {
                r = mod % i,
                _ext_inv[i] = mod - (r < N ? _inv[r] : _ext_inv[r]) *
                                        int_fast64_t(mod / i) % mod;
            }
            return x < (i32)N ? _inv[x] : _ext_inv[x];
        }

        i32 ext_invfact(i32 x) const
        {
            assert(x < (i32)ext_N and x < mod);
            if(x < 0) return 0;
            if(not invfact_itr)
            {
                _ext_invfact[N - 1] = _invfact[N - 1];
                invfact_itr = N;
            }
            for(size_t &i = inv_itr, r; (i32)i <= x; ++i)
            {
                r = mod % i,
                _ext_inv[i] = mod - (r < N ? _inv[r] : _ext_inv[r]) *
                                        int_fast64_t(mod / i) % mod;
            }
            for(size_t &i = invfact_itr; (i32)i <= x; ++i)
            {
                _ext_invfact[i] = i < N
                                      ? _invfact[i]
                                      : _ext_invfact[i - 1] * _ext_inv[i] % mod;
            }
            return x < (i32)N ? _invfact[x] : _ext_invfact[x];
        }
    };
    constexpr fact_impl _fact_impl;

    i32 fact_impl::_ext_fact[ext_N], fact_impl::_ext_inv[ext_N],
        fact_impl::_ext_invfact[ext_N];
    size_t fact_impl::fact_itr, fact_impl::inv_itr = N, fact_impl::invfact_itr;

    template <>
    class modint<mod>
    {
        i32 dat;

      public:
        constexpr modint() : dat(0) {}
        constexpr modint(int_fast64_t y) : dat(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}
        constexpr i64 get() const { return dat; }

        constexpr modint &operator+=(const modint &p)
        {
            return (dat += p.dat) < mod ? 0 : dat -= mod, *this;
        }

        constexpr modint &operator++()
        {
            return ++dat, *this;
        }

        constexpr modint operator++(i32)
        {
            modint t = *this;
            return ++dat, t;
        }

        constexpr modint &operator-=(const modint &p)
        {
            return (dat += mod - p.dat) < mod ? 0 : dat -= mod, *this;
        }

        constexpr modint &operator--()
        {
            return --dat, *this;
        }

        constexpr modint operator--(i32)
        {
            modint t = *this;
            return --dat, t;
        }

        constexpr modint &operator*=(const modint &p)
        {
            return dat = (int_fast64_t)dat * p.dat % mod, *this;
        }

        friend modint inverse(const modint &p);

        modint &operator/=(const modint &p)
        {
            return *this *= inverse(p);
        }

        // constexpr modint &operator%=(i32 m) { return dat %= m, *this; }

        constexpr modint operator-() const
        {
            return modint(-dat);
        }

        constexpr modint operator+(const modint &p) const
        {
            return modint(*this) += p;
        }

        constexpr modint operator-(const modint &p) const
        {
            return modint(*this) -= p;
        }

        constexpr modint operator*(const modint &p) const
        {
            return modint(*this) *= p;
        }

        modint operator/(const modint &p) const
        {
            return modint(*this) /= p;
        }

        // constexpr modint operator%(i32 m) const
        // {
        //    return modint(*this) %= m;
        // }

        constexpr bool operator==(const modint &p) const
        {
            return dat == p.dat;
        }

        constexpr bool operator!=(const modint &p) const
        {
            return dat != p.dat;
        }

        constexpr bool operator!() const
        {
            return !dat;
        }

        // constexpr bool operator>(const modint &p) const { return dat > p.dat; }

        // constexpr bool operator<(const modint &p) const { return dat <  p.dat; }

        // constexpr bool operator>=(const modint &p) const { return dat >= p.dat; }

        // constexpr bool operator<=(const modint &p) const { return dat <= p.dat; }

        friend modint inverse(const modint &p)
        {
            if(p.dat <= (i32)ext_N) return _fact_impl.ext_inv(p.dat);
            i32 a = p.dat, b = mod, u = 1, v = 0;
            while(b > 0)
            {
                i32 t = a / b;
                a -= t * b;
                a ^= b ^= a ^= b;
                u -= t * v;
                u ^= v ^= u ^= v;
            }
            return modint(u);
        }

        friend constexpr modint pow(modint p, int_fast64_t e)
        {
            if(e < 0) e = (e % (mod - 1) + mod - 1) % (mod - 1);
            modint ret = 1;
            while(e)
            {
                if(e & 1) ret *= p;
                p *= p;
                e >>= 1;
            }
            return ret;
        }

        friend std::ostream &operator<<(std::ostream &s, const modint &p)
        {
            return s << p.dat;
        }

        friend std::istream &operator>>(std::istream &s, modint &p)
        {
            int_fast64_t dat;
            p = modint((s >> dat, dat));
            return s;
        }
    };

    modint<mod> fact(i32 x) { return modint<mod>(_fact_impl.ext_fact(x)); }

    modint<mod> invfact(i32 x) { return modint<mod>(_fact_impl.ext_invfact(x)); }

    modint<mod> binom(i32 x, i32 y) { return fact(x) * invfact(y) * invfact(x - y); }

    modint<mod> perm(i32 x, i32 y) { return binom(x, y) * fact(y); }
} // namespace math