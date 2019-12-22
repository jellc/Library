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
template <>
class modint<2>
{
    bool val;
    public:
    constexpr modint(bool x = false) : val{x} {}
    constexpr modint(int x) : val(x & 1) {}
    constexpr modint(long long x) : val(x & 1) {}
    constexpr bool get() const { return val; }
    constexpr modint &operator+=(const modint &other) { return val ^= other.val, *this; }
    constexpr modint &operator++() { return val = !val, *this; }
    constexpr modint operator++(int) { modint t = *this; return val = !val, t; }
    constexpr modint &operator-=(const modint &other) { return val ^= other.val, *this; }
    constexpr modint &operator--() { return val = !val, *this; }
    constexpr modint operator--(int) { modint t = *this; return val = !val, t; }
    constexpr modint &operator*=(const modint &other) { return val &= other.val, *this; }
    constexpr modint &operator/=(const modint &other) { return *this; }
    constexpr modint operator-() const { return *this; }
    constexpr modint operator+(const modint &other) const { return val != other.val; }
    constexpr modint operator-(const modint &other) const { return val != other.val; }
    constexpr modint operator*(const modint &other) const { return val && other.val; }
    constexpr modint operator/(const modint &other) const { return *this; }
    constexpr bool operator==(const modint &other) const { return val == other.val; }
    constexpr bool operator!=(const modint &other) const { return val != other.val; }
    constexpr bool operator!() const { return !val; }
    operator bool() const { return val; }
    template <class T> friend constexpr modint operator+(T x, modint y) { return modint(x) + y; }
    template <class T> friend constexpr modint operator-(T x, modint y) { return modint(x) - y; }
    template <class T> friend constexpr modint operator*(T x, modint y) { return modint(x) * y; }
    template <class T> friend constexpr modint operator/(T x, modint y) { return modint(x) / y; }
    friend constexpr modint inverse(const modint &other) { return other; }
    friend constexpr modint pow(const modint &other, long long exp) { return other; }
    friend std::ostream &operator<<(std::ostream &os, const modint &other) { return os << other.val; }
    friend std::istream &operator>>(std::istream &is, modint &other) { long long val; other.val = (is >> val, val & 1); return is; }
}; // class modint specialization
#endif