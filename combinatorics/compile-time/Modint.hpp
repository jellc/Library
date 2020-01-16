#ifndef Modint_hpp
#define Modint_hpp
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

template <>
class modint<2>
{
    bool val;
public:
    constexpr modint(bool x = false) noexcept : val{x} {}
    constexpr modint(int x) noexcept : val(x & 1) {}
    constexpr modint(long long x) noexcept : val(x & 1) {}
    constexpr operator bool() const noexcept { return val; }
    constexpr bool value() const noexcept { return val; }
    constexpr modint &operator+=(const modint &other) noexcept { return val ^= other.val, *this; }
    constexpr modint &operator-=(const modint &other) noexcept { return val ^= other.val, *this; }
    constexpr modint &operator*=(const modint &other) noexcept { return val &= other.val, *this; }
    constexpr modint &operator/=(const modint &other) noexcept { assert(other.val); return *this; }
    constexpr modint operator!() const noexcept { return !val; }
    constexpr modint operator-() const noexcept { return *this; }
    constexpr modint operator+(const modint &other) const noexcept { return val != other.val; }
    constexpr modint operator-(const modint &other) const noexcept { return val != other.val; }
    constexpr modint operator*(const modint &other) const noexcept { return val && other.val; }
    constexpr modint operator/(const modint &other) const noexcept { assert(other.val); return *this; }
    constexpr bool operator==(const modint &other) const noexcept { return val == other.val; }
    constexpr bool operator!=(const modint &other) const noexcept { return val != other.val; }
    friend constexpr modint operator+(long long x, modint y) noexcept { return x & 1 ? !y : y; }
    friend constexpr modint operator-(long long x, modint y) noexcept { return x & 1 ? !y : y; }
    friend constexpr modint operator*(long long x, modint y) noexcept { return x & 1 ? y : modint<2>{0}; }
    friend constexpr modint operator/(long long x, modint y) noexcept { assert(y.val); return x & 1 ? y : modint<2>{0}; }
    friend std::ostream &operator<<(std::ostream &os, const modint &other) noexcept { return os << other.val; }
    friend std::istream &operator>>(std::istream &is, modint &other) noexcept { long long val; other.val = (is >> val, val & 1); return is; }
}; // class modint specialization

#endif // Modint_hpp