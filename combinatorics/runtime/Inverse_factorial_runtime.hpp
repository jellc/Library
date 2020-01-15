#ifndef Modint_runtime_hpp
#define Modint_runtime_hpp
#include <cassert>
#include <iostream>

class modint_runtime
{
    long long val;
    int mod;
    friend constexpr bool mod_same(const modint_runtime &x, const modint_runtime &y) { return x.mod == y.mod; }
public:
    constexpr modint_runtime(long long x) : val(x), mod{} {}
    constexpr modint_runtime(long long x, int _mod) noexcept : val((x %= _mod) < 0 ? x + _mod : x), mod(_mod) {}
    constexpr bool mod_set() const noexcept { return mod; }
    constexpr long long value() const noexcept { return val; }
    constexpr int modulo() const noexcept { return mod; }
    constexpr modint_runtime operator++(int) noexcept { modint_runtime t = *this; return ++val, t; }
    constexpr modint_runtime &operator++() noexcept { return ++val, *this; }
    constexpr modint_runtime operator--(int) noexcept { modint_runtime t = *this; return --val, t; }
    constexpr modint_runtime &operator--() noexcept { return --val, *this; }
    constexpr modint_runtime &operator=(long long other) noexcept { return val = (other %= mod) < 0 ? other + mod : other, *this; }
    constexpr modint_runtime &operator+=(long long other) noexcept { return (val += other % mod) < mod ? 0 : val -= mod, *this; }
    constexpr modint_runtime &operator+=(const modint_runtime &other) noexcept { assert(mod_same(*this, other)); return (val += other.val) < mod ? 0 : val -= mod, *this; }
    constexpr modint_runtime &operator-=(long long other) noexcept { return (val += mod - other % mod) < mod ? 0 : val -= mod, *this; }
    constexpr modint_runtime &operator-=(const modint_runtime &other) noexcept { assert(mod_same(*this, other)); return (val += mod - other.val) < mod ? 0 : val -= mod, *this; }
    constexpr modint_runtime &operator*=(long long other) noexcept { return (val *= other % mod) %= mod, *this; }
    constexpr modint_runtime &operator*=(const modint_runtime &other) noexcept { assert(mod_same(*this, other)); return (val *= other.val) %= mod, *this; }
    constexpr modint_runtime &operator/=(long long other) noexcept { return *this *= inverse(modint_runtime{other, mod}); }
    constexpr modint_runtime &operator/=(const modint_runtime &other) noexcept { assert(mod_same(*this, other)); return *this *= inverse(other); }
    constexpr modint_runtime operator-() const noexcept { return modint_runtime(-val); }
    template <typename T> constexpr modint_runtime operator+(const T &other) const noexcept { return modint_runtime(*this) += other; }
    template <typename T> constexpr modint_runtime operator-(const T &other) const noexcept { return modint_runtime(*this) -= other; }
    template <typename T> constexpr modint_runtime operator*(const T &other) const noexcept { return modint_runtime(*this) *= other; }
    template <typename T> constexpr modint_runtime operator/(const T &other) const noexcept { return modint_runtime(*this) /= other; }
    constexpr bool operator==(const modint_runtime &other) const noexcept { assert(mod_same(*this, other)); return val == other.val; }
    constexpr bool operator!=(const modint_runtime &other) const noexcept { assert(mod_same(*this, other)); return val != other.val; }
    constexpr bool operator!() const noexcept { return !val; }
    friend constexpr modint_runtime operator+(long long x, modint_runtime y) noexcept { return modint_runtime(x + y.val, y.mod); }
    friend constexpr modint_runtime operator-(long long x, modint_runtime y) noexcept { return modint_runtime(x - y.val, y.mod); }
    friend constexpr modint_runtime operator*(long long x, modint_runtime y) noexcept { return modint_runtime(x % y.mod * y.val, y.mod); }
    friend constexpr modint_runtime operator/(long long x, modint_runtime y) noexcept { return modint_runtime(x % y.mod * inverse(y).val, y.mod); }
    friend constexpr modint_runtime inverse(const modint_runtime &other) noexcept
    {
        assert(other.mod && other.val);
        long long a{other.mod}, b{other.val}, u{}, v{1}, t{};
        while(b) t = a / b, a ^= b ^= (a -= t * b) ^= b, u ^= v ^= (u -= t * v) ^= v;
        return {u, other.mod};
    }
    friend constexpr modint_runtime pow(modint_runtime other, long long e) noexcept
    {
        if(e < 0) e = e % (other.mod - 1) + other.mod - 1;
        modint_runtime res{1, other.mod};
        while(e) { if(e & 1) res *= other; other *= other, e >>= 1; }
        return res;
    }
    friend std::ostream &operator<<(std::ostream &os, const modint_runtime &other) noexcept { return os << other.val; }
    friend std::istream &operator>>(std::istream &is, modint_runtime &other) noexcept { long long val; other = modint_runtime((is >> val, val)); return is; }
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
    modint_runtime operator()(const int x) noexcept { assert(x), reserve(x); return {inv[x], mod}; }
};

#endif // Inverse_runtime_hpp

#ifndef Inverse_factorial_runtime_hpp
#define Inverse_factorial_runtime_hpp
#include <cassert>
#include <vector>

class inverse_factorial_runtime
{
    inverse_runtime &inv_gen;
    const int mod;
    int n;
    std::vector<int> inv_fact;
public:
    inverse_factorial_runtime(inverse_runtime &_inv_gen) : inv_gen{_inv_gen}, mod{_inv_gen.modulo()}, n{1}, inv_fact{1} {}
    void reserve(int m)
    {
        if(m < n) return;
        m = 1 << (32 - __builtin_clz(m));
        inv_fact.resize(m);
        for(int i = n; i < m; ++i) inv_fact[i] = inv_fact[i - 1] * inv_gen(i).value() % mod;
        n = m;
    }
    modint_runtime operator()(const int x) noexcept { reserve(x); return {x < 0 ? 0 : inv_fact[x], mod}; }
};

#endif // Inverse_factorial_runtime_hpp