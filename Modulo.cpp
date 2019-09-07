namespace math
{
    template <int_fast32_t mod>
    struct modint
    {
        int x;

        constexpr modint() : x(0)
        {}
        constexpr modint(int_fast64_t y)
            : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod)
        {}

        constexpr modint &operator+=(const modint &p)
        {
            if((x += p.x) >= mod) x -= mod;
            return *this;
        }

        constexpr modint &operator++()
        {
            return ++x, *this;
        }

        constexpr modint operator++(int)
        {
            modint t = *this;
            return ++x, t;
        }

        constexpr modint &operator-=(const modint &p)
        {
            if((x += mod - p.x) >= mod) x -= mod;
            return *this;
        }

        constexpr modint &operator--()
        {
            return --x, *this;
        }

        constexpr modint operator--(int)
        {
            modint t = *this;
            return --x, t;
        }

        constexpr modint &operator*=(const modint &p)
        {
            return x = (int_fast64_t)x * p.x % mod, *this;
        }

        constexpr modint &operator/=(const modint &p)
        {
            return *this *= inverse(p);
        }

        // constexpr modint &operator%=(int m) { return x %= m, *this; }

        constexpr modint operator-() const
        {
            return modint(-x);
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

        // constexpr modint operator%(int m) const { return modint(*this) %= m;
        // }

        constexpr bool operator==(const modint &p) const
        {
            return x == p.x;
        }

        constexpr bool operator!=(const modint &p) const
        {
            return x != p.x;
        }

        constexpr bool operator!() const
        {
            return !x;
        }

        // constexpr bool operator>(const modint &p) const { return x > p.x; }

        // constexpr bool operator<(const modint &p) const { return x <  p.x; }

        // constexpr bool operator>=(const modint &p) const { return x >= p.x; }

        // constexpr bool operator<=(const modint &p) const { return x <= p.x; }

        constexpr friend modint inverse(const modint &p)
        {
            int a = p.x, b = mod, u = 1, v = 0;
            while(b > 0)
            {
                int t = a / b;
                a -= t * b;
                a ^= b ^= a ^= b;
                u -= t * v;
                u ^= v ^= u ^= v;
            }
            return modint(u);
        }

        constexpr friend modint pow(modint p, int_fast64_t e)
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
            return s << p.x;
        }

        friend std::istream &operator>>(std::istream &s, modint &p)
        {
            int_fast64_t x;
            p = modint((s >> x, x));
            return s;
        }
    };
} // namespace math

// require modint
namespace math
{
    constexpr int mod = 1000000007;

    constexpr int N = 2.2e5, N_max = 2.2e6;

    struct impl
    {
        int_fast64_t _fact[N + 1], _invfact[N + 1], _inv[N + 1];

        constexpr impl() : _fact(), _invfact(), _inv()
        {
            _fact[0] = 1;
            for(int i = 1; i <= N; ++i)
                _fact[i] = _fact[i - 1] * i % mod;
            _inv[1] = 1;
            for(int i = 2; i <= N && i < mod; ++i)
                _inv[i] = mod - _inv[mod % i] * (mod / i) % mod;
            _invfact[0] = 1;
            for(int i = 1; i <= N && i < mod; ++i)
                _invfact[i] = _invfact[i - 1] * _inv[i] % mod;
        }
    };
    constexpr impl _impl;

    int_fast64_t _dyn_fact[N_max + 1];
    int_fast64_t _dyn_inv[N_max + 1];
    int_fast64_t _dyn_invfact[N_max + 1];

    int_fast64_t dyn_fact(int x)
    {
        assert(x <= N_max);
        if(x < 0) return 0;
        static int _size = 1;
        for(int &i = _size; i <= x; ++i)
        {
            if(i <= N)
                _dyn_fact[i] = _impl._fact[i];
            else
                _dyn_fact[i] = _dyn_fact[i - 1] * i % mod;
        }
        return _dyn_fact[x];
    }

    int_fast64_t dyn_invfact(int x)
    {
        assert(x <= N_max && x < mod);
        if(x < 0) return 0;
        static int _size = 1;
        for(int &i = _size; i <= x; ++i)
        {
            if(i <= N)
            {
                _dyn_inv[i] = _impl._inv[i];
                _dyn_invfact[i] = _impl._invfact[i];
            }
            else
            {
                _dyn_inv[i] = mod - _dyn_inv[mod % i] * (mod / i) % mod;
                _dyn_invfact[i] = _dyn_invfact[i - 1] * _dyn_inv[i] % mod;
            }
        }
        return _dyn_invfact[x];
    }

    modint<mod> fact(int x)
    {
        return x > N ? dyn_fact(x) : x < 0 ? 0 : _impl._fact[x];
    }

    modint<mod> invfact(int x)
    {
        return x > N ? dyn_invfact(x) : x < 0 ? 0 : _impl._invfact[x];
    }

    modint<mod> binom(int x, int y)
    {
        return fact(x) * invfact(y) * invfact(x - y);
    }

    modint<mod> perm(int x, int y)
    {
        return binom(x, y) * fact(y);
    }
} // namespace math