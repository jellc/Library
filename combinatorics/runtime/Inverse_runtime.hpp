#ifndef Modint_runtime_hpp
#define Modint_runtime_hpp
#include <cassert>
#include <iostream>

// modulo statically fixed
class modint_runtime
{
    long long val;
    friend std::ostream &operator<<(std::ostream &os, const modint_runtime &other) noexcept { return os << other.val; }
    friend std::istream &operator>>(std::istream &is, modint_runtime &other) noexcept { long long val; other = modint_runtime((is >> val, val)); return is; }
public:
    static long long &mod() noexcept { static long long mod{}; return mod; }
    modint_runtime(long long x = 0) : val{(x %= mod()) < 0 ? x + mod() : x} {}
    long long value() const noexcept { return val; }
    modint_runtime operator++(int) noexcept { modint_runtime t = *this; return ++val, t; }
    modint_runtime &operator++() noexcept { return ++val, *this; }
    modint_runtime operator--(int) noexcept { modint_runtime t = *this; return --val, t; }
    modint_runtime &operator--() noexcept { return --val, *this; }
    modint_runtime &operator=(long long other) noexcept { return val = (other %= mod()) < 0 ? other + mod() : other, *this; }
    modint_runtime &operator+=(long long other) noexcept { return (val += other % mod()) < mod() ? 0 : val -= mod(), *this; }
    modint_runtime &operator+=(const modint_runtime &other) noexcept { return (val += other.val) < mod() ? 0 : val -= mod(), *this; }
    modint_runtime &operator-=(long long other) noexcept { return (val += mod() - other % mod()) < mod() ? 0 : val -= mod(), *this; }
    modint_runtime &operator-=(const modint_runtime &other) noexcept { return (val += mod() - other.val) < mod() ? 0 : val -= mod(), *this; }
    modint_runtime &operator*=(long long other) noexcept { return (val *= other % mod()) %= mod(), *this; }
    modint_runtime &operator*=(const modint_runtime &other) noexcept { return (val *= other.val) %= mod(), *this; }
    modint_runtime &operator/=(long long other) noexcept { return *this *= inverse(other); }
    modint_runtime &operator/=(const modint_runtime &other) noexcept { return *this *= inverse(other); }
    modint_runtime operator-() const noexcept { return modint_runtime(-val); }
    modint_runtime operator+(const modint_runtime &other) const noexcept { return modint_runtime{*this} += other; }
    modint_runtime operator-(const modint_runtime &other) const noexcept { return modint_runtime{*this} -= other; }
    modint_runtime operator*(const modint_runtime &other) const noexcept { return modint_runtime{*this} *= other; }
    modint_runtime operator/(const modint_runtime &other) const noexcept { return modint_runtime{*this} /= other; }
    bool operator==(const modint_runtime &other) const noexcept { return val == other.val; }
    bool operator!=(const modint_runtime &other) const noexcept { return val != other.val; }
    bool operator!() const noexcept { return !val; }
    friend modint_runtime operator+(long long x, modint_runtime y) noexcept { return {x + y.val}; }
    friend modint_runtime operator-(long long x, modint_runtime y) noexcept { return {x - y.val}; }
    friend modint_runtime operator*(long long x, modint_runtime y) noexcept { return {x % mod() * y.val}; }
    friend modint_runtime operator/(long long x, modint_runtime y) noexcept { return {x % mod() * inverse(y).val}; }
    static modint_runtime inverse(const modint_runtime &other) noexcept
    {
        assert(mod() && other.val);
        long long a{mod()}, b{other.val}, u{}, v{1}, t{};
        while(b) t = a / b, a ^= b ^= (a -= t * b) ^= b, u ^= v ^= (u -= t * v) ^= v;
        return {u};
    }
    static modint_runtime pow(modint_runtime other, long long e) noexcept
    {
        if(e < 0) e = e % (mod() - 1) + mod() - 1;
        modint_runtime res{1};
        while(e) { if(e & 1) res *= other; other *= other, e >>= 1; }
        return res;
    }
}; // class modint_runtime
#endif // Modint_runtime_hpp

#ifndef Inverse_runtime_hpp
#define Inverse_runtime_hpp
#include <vector>

class inverse_runtime
{
    const int mod;
    int n;
    std::vector<int> inv;
public:
    inverse_runtime(int _mod) : mod{_mod}, n{2}, inv{0, 1} {}
    int modulo() const { return mod; }
    void reserve(int m)
    {
        if(m < n) return;
        m = 1 << (32 - __builtin_clz(m));
        inv.resize(m);
        for(int i = n; i < m; ++i) inv[i] = mod - (long long)mod / i * inv[mod % i] % mod;
        n = m;
    }
    // modint_runtime operator()(const int x) noexcept { assert(x), reserve(x); return {inv[x], mod}; }
    modint_runtime operator()(const int x) noexcept { assert(x), reserve(x); return {inv[x]}; }
};

#endif // Inverse_runtime_hpp
