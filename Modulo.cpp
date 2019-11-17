#include <bits/stdc++.h>

namespace math
{
    template <int mod>
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
} // namespace math