#include <bits/stdc++.h>
using namespace std;


/* The snippet starts here. */
namespace Calcfn {
    constexpr int mod = 1e9 + 7;

    template <int_fast32_t mod>
    struct modint {
        int x;
        constexpr modint() : x(0) {}
        constexpr modint(int_fast64_t y) : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}

        constexpr modint &operator+=(const modint &p) {
            if((x += p.x) >= mod) x -= mod;
            return *this;
        }

        constexpr modint &operator++() { return ++x,*this; }

        constexpr modint operator++(int) {
            modint t = *this;
            return ++x,t;
        }

        constexpr modint &operator-=(const modint &p) {
            if((x += mod - p.x) >= mod) x -= mod;
            return *this;
        }

        constexpr modint &operator--() { return --x, *this; }

        constexpr modint operator--(int) {
            modint t = *this;
            return --x,t;
        }

        constexpr modint &operator*=(const modint &p) {
            x = (int) (1LL * x * p.x % mod);
            return *this;
        }

        constexpr modint &operator/=(const modint &p) {
            *this *= inverse(p);
            return *this;
        }

        constexpr modint operator-() const { return modint(-x); }

        constexpr modint operator+(const modint &p) const { return modint(*this) += p; }

        constexpr modint operator-(const modint &p) const { return modint(*this) -= p; }

        constexpr modint operator*(const modint &p) const { return modint(*this) *= p; }

        constexpr modint operator/(const modint &p) const { return modint(*this) /= p; }

        constexpr bool operator==(const modint &p) const { return x == p.x; }

        constexpr bool operator!=(const modint &p) const { return x != p.x; }

        constexpr bool operator!() const { return !x; }

        // constexpr bool operator>(const modint &p) const { return x > p.x; }

        // constexpr bool operator<(const modint &p) const { return x <  p.x; }

        // constexpr bool operator>=(const modint &p) const { return x >= p.x; }

        // constexpr bool operator<=(const modint &p) const { return x <= p.x; }

        constexpr static modint inverse(const modint &p) {
            int a = p.x, b = mod, u = 1, v = 0;
            while(b > 0) {
                int t = a / b;
                a -= t * b;
                a ^= b ^= a ^= b;
                u -= t * v;
                u ^= v ^= u ^= v;
            }
            return modint(u);
        }

        constexpr static modint pow(modint p, int_fast64_t e) {
            if(!e) return 1;
            if(e < 0) e = (e % (mod - 1) + mod - 1) % (mod - 1);
            return pow(p * p, e >> 1) * (e & 1 ? p : 1);
        }

        friend ostream &operator<<(ostream &s, const modint &p) { return s << p.x; }

        friend istream &operator>>(istream &s, modint &p) {
            int_fast64_t x;
            p = modint((s >> x, x));
            return s;
        }
    };

    constexpr static int N = 2.2e5, N_max = 2.2e6;

    struct impl {
        int_fast64_t fact_[N + 1], invfact_[N + 1], inv_[N + 1];

        constexpr impl() : fact_(),invfact_(),inv_() {
            fact_[0] = 1;
            for(int i = 1; i <= N; ++i) fact_[i] = fact_[i - 1] * i % mod;
            inv_[1] = 1;
            for(int i = 2; i <= N && i < mod; ++i) inv_[i] = mod - inv_[mod % i] * (mod / i) % mod;
            invfact_[0] = 1;
            for(int i = 1; i <= N && i < mod; ++i) invfact_[i] = invfact_[i - 1] * inv_[i] % mod;
        }
    };
    constexpr static impl impl_exe;

    int_fast64_t _dyn_fact[N_max + 1];
    int_fast64_t _dyn_inv[N_max + 1];
    int_fast64_t _dyn_invfact[N_max + 1];

    static int_fast64_t dyn_fact(int x) {
        assert(x <= N_max);
        if(x < 0) return 0;
        static int _size = 1;
        for(int &i = _size; i <= x; ++i) {
            if(i <= N) _dyn_fact[i] = impl_exe.fact_[i];
            else _dyn_fact[i] = _dyn_fact[i - 1] * i % mod;
        }
        return _dyn_fact[x];
    }

    static int_fast64_t dyn_invfact(int x) {
        assert(x <= N_max && x < mod);
        if(x < 0)  return 0;
        static int _size = 1;
        for(int &i = _size; i <= x; ++i) {
            if(i <= N) {
                _dyn_inv[i] = impl_exe.inv_[i];
                _dyn_invfact[i] = impl_exe.invfact_[i];
            } else {
                _dyn_inv[i] = mod - _dyn_inv[mod % i] * (mod / i) % mod;
                _dyn_invfact[i] = _dyn_invfact[i - 1] * _dyn_inv[i] % mod;
            }
        }
        return _dyn_invfact[x];
    }

    static modint<mod> fact(int x) {
        if(x > N) return dyn_fact(x);
        return x >= 0 ? impl_exe.fact_[x] : 0;
    }

    static modint<mod> invfact(int x) {
        assert(x < mod);
        if(x > N) return dyn_invfact(x);
        return x >= 0 ? impl_exe.invfact_[x] : 0;
    }

    static modint<mod> binom(int x, int y) {
        return fact(x) * invfact(y) * invfact(x - y);
    }

    static modint<mod> perm(int x, int y) {
        return binom(x, y) * fact(y);
    }

    constexpr static int_fast64_t gcd(int_fast64_t a, int_fast64_t b) {
        if(!b) return a > 0 ? a : -a; 
        return gcd(b, a % b);
    }

    constexpr static int_fast64_t lcm(int_fast64_t a, int_fast64_t b) {
        if(a | b) return a / gcd(a, b) * b;
        return 0;
    }

    constexpr static int_fast64_t ext_gcd(int_fast64_t a, int_fast64_t b, int_fast64_t &x, int_fast64_t &y) {
        int_fast64_t d = a;
        if (b) d = ext_gcd(b, a % b, y, x), y -= (a / b) * x;
        else x = 1, y = 0;
        return d;
    }
}
using Calcfn::mod;
using Calcfn::modint;
using Calcfn::fact;
using Calcfn::invfact;
using Calcfn::perm;
using Calcfn::binom;
/* The snippet ends here. */


template <int_fast32_t mod>
struct modint {
    int x;
    constexpr modint() : x(0) {}
    constexpr modint(int_fast64_t y) : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}

    constexpr modint &operator+=(const modint &p) {
        if((x += p.x) >= mod) x -= mod;
        return *this;
    }

    constexpr modint &operator++() { return ++x,*this; }

    constexpr modint operator++(int) {
        modint t = *this;
        return ++x,t;
    }

    constexpr modint &operator-=(const modint &p) {
        if((x += mod - p.x) >= mod) x -= mod;
        return *this;
    }

    constexpr modint &operator--() { return --x, *this; }

    constexpr modint operator--(int) {
        modint t = *this;
        return --x,t;
    }

    constexpr modint &operator*=(const modint &p) {
        x = (int) (1LL * x * p.x % mod);
        return *this;
    }

    constexpr modint &operator/=(const modint &p) {
        *this *= inverse(p);
        return *this;
    }

    constexpr modint operator-() const { return modint(-x); }

    constexpr modint operator+(const modint &p) const { return modint(*this) += p; }

    constexpr modint operator-(const modint &p) const { return modint(*this) -= p; }

    constexpr modint operator*(const modint &p) const { return modint(*this) *= p; }

    constexpr modint operator/(const modint &p) const { return modint(*this) /= p; }

    constexpr bool operator==(const modint &p) const { return x == p.x; }

    constexpr bool operator!=(const modint &p) const { return x != p.x; }

    constexpr bool operator!() const { return !x; }

    // constexpr bool operator>(const modint &p) const { return x > p.x; }

    // constexpr bool operator<(const modint &p) const { return x <  p.x; }

    // constexpr bool operator>=(const modint &p) const { return x >= p.x; }

    // constexpr bool operator<=(const modint &p) const { return x <= p.x; }

    constexpr static modint inverse(const modint &p) {
        int a = p.x, b = mod, u = 1, v = 0;
        while(b > 0) {
            int t = a / b;
            a -= t * b;
            a ^= b ^= a ^= b;
            u -= t * v;
            u ^= v ^= u ^= v;
        }
        return modint(u);
    }

    constexpr static modint pow(modint p, int_fast64_t e) {
        if(!e) return 1;
        if(e < 0) e = (e % (mod - 1) + mod - 1) % (mod - 1);
        return pow(p * p, e >> 1) * (e & 1 ? p : 1);
    }

    friend ostream &operator<<(ostream &s, const modint &p) { return s << p.x; }

    friend istream &operator>>(istream &s, modint &p) {
        int_fast64_t x;
        p = modint((s >> x, x));
        return s;
    }
};