#ifndef NUMBER_THEORETIC_TRANSFORM_HPP
#define NUMBER_THEORETIC_TRANSFORM_HPP

#include <bits/stdc++.h>

namespace number_theoretic_transform
{
    constexpr int mod = 998244353;
    constexpr int primitive = 3;

    class modint
    {
        int dat;
      public:
        constexpr modint() : dat{0} {}
        constexpr modint(long long y) : dat{(y %= mod) < 0 ? mod - y : y} {}
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
            int a{other.dat}, b{mod}, u{1}, v{}, t{};
            while(b > 0) t = a / b, a ^= b ^= (a -= t * b) ^= b, u ^= v ^= (u -= t * v) ^= v;
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

    class zeta_calc
    {
        static constexpr size_t n = __builtin_ctz(mod - 1);
        modint _zeta[n + 1];
      public:
        constexpr zeta_calc() : _zeta{}
        {
            _zeta[n] = pow(modint(primitive), (mod - 1) / (1 << n));
            for(size_t i{n}; i; --i) _zeta[i - 1] = _zeta[i] * _zeta[i];
        }
        constexpr modint operator[](size_t k) const { return _zeta[k]; }
    }; // class zeta_calc
    constexpr zeta_calc zeta;

    class inv_calc
    {
        static constexpr size_t n = __builtin_ctz(mod - 1);
        modint _inv[n + 1];
      public:
        constexpr inv_calc() : _inv{1, (mod + 1) / 2} { for(size_t i{1}; i < n; ++i) _inv[i + 1] = _inv[i] * _inv[1]; }
        constexpr modint operator[](size_t k) const { return _inv[k]; }
    }; // class inv_calc
    constexpr inv_calc inv;

    using poly_t = std::vector<modint>;

    void dft(poly_t &f)
    {
        const size_t n{f.size()}, mask{n - 1};
        assert(__builtin_popcount(n) == 1); // degree of f must be a power of two.
        static poly_t g; g.resize(n);
        for(size_t i{n >> 1}, ii{1}; i; i >>= 1, ++ii, swap(f, g))
        {
            modint powzeta{1};
            for(size_t j{}; j < n; powzeta *= zeta[ii])
            {
                for(size_t k{}, x{mask & j << 1}, y{mask & (i + (j << 1))}; k < i; ++k, ++j, ++x, ++y)
                {
                    g[j] = f[x] + powzeta * f[y];
                }
            }
        }
    }

    void idft(poly_t &f)
    {
        dft(f), reverse(next(f.begin()), f.end());
        const size_t k = __builtin_ctz(f.size()); for(modint &e : f) e *= inv[k];
    }

    poly_t convolute(poly_t f, poly_t g)
    {
        if(f.empty() || g.empty()) return poly_t();
        const size_t deg_f{f.size() - 1}, deg_g{g.size() - 1}, deg_h{deg_f + deg_g}, n(1u << (32 - __builtin_clz(deg_h)));
        static poly_t h;
        f.resize(n, 0), g.resize(n, 0), h.resize(n);
        dft(f), dft(g);
        for(size_t i{}; i < n; ++i) h[i] = f[i] * g[i];
        idft(h); h.resize(deg_h + 1);
        return h;
    }
} // namespace fast_Fourier_transform

#endif