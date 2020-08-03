
#ifndef modint_hpp
#define modint_hpp
#include <cassert>
#include <iostream>

template <int mod>
class modint
{
    int val;
public:
    static constexpr modint one() noexcept { return 1; }
    constexpr modint() noexcept : val(0) {}
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    constexpr modint(int_type _val) noexcept : val((_val %= mod) < 0 ? mod + _val : _val) {}
    constexpr long long value() const noexcept { return val; }
    constexpr modint operator++(int) noexcept { modint t = *this; return operator+=(1), t; }
    constexpr modint operator--(int) noexcept { modint t = *this; return operator-=(1), t; }
    constexpr modint &operator++() noexcept { return operator+=(1); }
    constexpr modint &operator--() noexcept { return operator-=(1); }
    constexpr modint operator-() const noexcept { return modint(-val); }
    constexpr modint &operator+=(const modint &rhs) noexcept { return (val += rhs.val) < mod ? 0 : val -= mod, *this; }
    constexpr modint &operator-=(const modint &rhs) noexcept { return (val += mod - rhs.val) < mod ? 0 : val -= mod, *this; }
    constexpr modint &operator*=(const modint &rhs) noexcept { return val = (long long)val * rhs.val % mod, *this; }
    constexpr modint &operator/=(const modint &rhs) noexcept { return *this *= inverse(rhs); }
    constexpr modint operator+(const modint &rhs) const noexcept { return modint(*this) += rhs; }
    constexpr modint operator-(const modint &rhs) const noexcept { return modint(*this) -= rhs; }
    constexpr modint operator*(const modint &rhs) const noexcept { return modint(*this) *= rhs; }
    constexpr modint operator/(const modint &rhs) const noexcept { return modint(*this) /= rhs; }
    constexpr bool operator==(const modint &rhs) const noexcept { return val == rhs.val; }
    constexpr bool operator!=(const modint &rhs) const noexcept { return val != rhs.val; }
    constexpr bool operator!() const noexcept { return !val; }
    friend constexpr modint operator+(long long lhs, modint rhs) noexcept { return modint(lhs) + rhs; }
    friend constexpr modint operator-(long long lhs, modint rhs) noexcept { return modint(lhs) - rhs; }
    friend constexpr modint operator*(long long lhs, modint rhs) noexcept { return modint(lhs) * rhs; }
    friend constexpr modint operator/(long long lhs, modint rhs) noexcept { return modint(lhs) / rhs; }
    static constexpr modint inverse(const modint &rhs) noexcept
    {
        assert(rhs != 0);
        int a{mod}, b{rhs.val}, u{}, v{1}, t{};
        while(b) t = a / b, a ^= b ^= (a -= t * b) ^= b, u ^= v ^= (u -= t * v) ^= v;
        return {u};
    }
    static constexpr modint pow(modint rhs, long long e) noexcept
    {
        if(e < 0) e = e % (mod - 1) + mod - 1;
        modint res{1};
        while(e) { if(e & 1) res *= rhs; rhs *= rhs, e >>= 1; }
        return res;
    }
    friend std::ostream &operator<<(std::ostream &os, const modint &rhs) noexcept { return os << rhs.val; }
    friend std::istream &operator>>(std::istream &is, modint &rhs) noexcept { long long val; rhs = {(is >> val, val)}; return is; }
}; // class modint

// specialization for modulo 2.
template <>
class modint<2>
{
    bool val;
public:
    static constexpr modint one() noexcept { return 1; }
    constexpr modint() noexcept : val(false) {}
    template <class int_type, std::enable_if_t<std::is_integral<int_type>::value, std::nullptr_t> = nullptr>
    constexpr modint(int_type _val) noexcept : val(_val & 1) {}
    constexpr operator bool() const noexcept { return val; }
    constexpr bool value() const noexcept { return val; }
    constexpr modint &operator+=(const modint &rhs) noexcept { return val ^= rhs.val, *this; }
    constexpr modint &operator-=(const modint &rhs) noexcept { return val ^= rhs.val, *this; }
    constexpr modint &operator*=(const modint &rhs) noexcept { return val &= rhs.val, *this; }
    constexpr modint &operator/=(const modint &rhs) noexcept { assert(rhs.val); return *this; }
    constexpr modint operator!() const noexcept { return !val; }
    constexpr modint operator-() const noexcept { return *this; }
    constexpr modint operator+(const modint &rhs) const noexcept { return val != rhs.val; }
    constexpr modint operator-(const modint &rhs) const noexcept { return val != rhs.val; }
    constexpr modint operator*(const modint &rhs) const noexcept { return val && rhs.val; }
    constexpr modint operator/(const modint &rhs) const noexcept { assert(rhs.val); return *this; }
    constexpr bool operator==(const modint &rhs) const noexcept { return val == rhs.val; }
    constexpr bool operator!=(const modint &rhs) const noexcept { return val != rhs.val; }
    friend constexpr modint operator+(long long lhs, modint rhs) noexcept { return lhs & 1 ? !rhs : rhs; }
    friend constexpr modint operator-(long long lhs, modint rhs) noexcept { return lhs & 1 ? !rhs : rhs; }
    friend constexpr modint operator*(long long lhs, modint rhs) noexcept { return lhs & 1 ? rhs : modint<2>{0}; }
    friend constexpr modint operator/(long long lhs, modint rhs) noexcept { assert(rhs.val); return lhs & 1 ? rhs : modint<2>{0}; }
    friend std::ostream &operator<<(std::ostream &os, const modint &rhs) noexcept { return os << rhs.val; }
    friend std::istream &operator>>(std::istream &is, modint &rhs) noexcept { long long val; rhs.val = (is >> val, val & 1); return is; }
}; // class modint<2>

#endif // modint_hpp