#include <cassert>
#include <iostream>
// modulo individually set
class modular
{
    long long val;
    int mod;
public:
    friend constexpr bool mod_same(const modular &x, const modular &y) { return x.mod == y.mod; }
    constexpr modular(long long x) : val(x), mod{} {}
    constexpr modular(long long x, int _mod) noexcept : val((x %= _mod) < 0 ? x + _mod : x), mod(_mod) {}
    constexpr bool mod_set() const noexcept { return mod; }
    constexpr long long value() const noexcept { return val; }
    constexpr int modulo() const noexcept { return mod; }
    constexpr modular operator++(int) noexcept { modular t = *this; return ++val, t; }
    constexpr modular &operator++() noexcept { return ++val, *this; }
    constexpr modular operator--(int) noexcept { modular t = *this; return --val, t; }
    constexpr modular &operator--() noexcept { return --val, *this; }
    constexpr modular &operator=(long long other) noexcept { return val = (other %= mod) < 0 ? other + mod : other, *this; }
    constexpr modular &operator+=(long long other) noexcept { return (val += other % mod) < mod ? 0 : val -= mod, *this; }
    constexpr modular &operator+=(const modular &other) noexcept { assert(mod_same(*this, other)); return (val += other.val) < mod ? 0 : val -= mod, *this; }
    constexpr modular &operator-=(long long other) noexcept { return (val += mod - other % mod) < mod ? 0 : val -= mod, *this; }
    constexpr modular &operator-=(const modular &other) noexcept { assert(mod_same(*this, other)); return (val += mod - other.val) < mod ? 0 : val -= mod, *this; }
    constexpr modular &operator*=(long long other) noexcept { return (val *= other % mod) %= mod, *this; }
    constexpr modular &operator*=(const modular &other) noexcept { assert(mod_same(*this, other)); return (val *= other.val) %= mod, *this; }
    constexpr modular &operator/=(long long other) noexcept { return *this *= inverse(modular{other, mod}); }
    constexpr modular &operator/=(const modular &other) noexcept { assert(mod_same(*this, other)); return *this *= inverse(other); }
    constexpr modular operator-() const noexcept { return modular(-val); }
    template <typename T> constexpr modular operator+(const T &other) const noexcept { return modular(*this) += other; }
    template <typename T> constexpr modular operator-(const T &other) const noexcept { return modular(*this) -= other; }
    template <typename T> constexpr modular operator*(const T &other) const noexcept { return modular(*this) *= other; }
    template <typename T> constexpr modular operator/(const T &other) const noexcept { return modular(*this) /= other; }
    constexpr bool operator==(const modular &other) const noexcept { assert(mod_same(*this, other)); return val == other.val; }
    constexpr bool operator!=(const modular &other) const noexcept { assert(mod_same(*this, other)); return val != other.val; }
    constexpr bool operator!() const noexcept { return !val; }
    friend constexpr modular operator+(long long x, modular y) noexcept { return modular(x + y.val, y.mod); }
    friend constexpr modular operator-(long long x, modular y) noexcept { return modular(x - y.val, y.mod); }
    friend constexpr modular operator*(long long x, modular y) noexcept { return modular(x % y.mod * y.val, y.mod); }
    friend constexpr modular operator/(long long x, modular y) noexcept { return modular(x % y.mod * inverse(y).val, y.mod); }
    friend constexpr modular inverse(const modular &other) noexcept
    {
        assert(other.mod && other.val);
        long long a{other.mod}, b{other.val}, u{}, v{1}, t{};
        while(b) t = a / b, a ^= b ^= (a -= t * b) ^= b, u ^= v ^= (u -= t * v) ^= v;
        return {u, other.mod};
    }
    friend constexpr modular pow(modular other, long long e) noexcept
    {
        if(e < 0) e = e % (other.mod - 1) + other.mod - 1;
        modular res{1, other.mod};
        while(e) { if(e & 1) res *= other; other *= other, e >>= 1; }
        return res;
    }
    friend std::ostream &operator<<(std::ostream &os, const modular &other) noexcept { return os << other.val; }
    friend std::istream &operator>>(std::istream &is, modular &other) noexcept { long long val; other = modular((is >> val, val)); return is; }
}; // class modular
