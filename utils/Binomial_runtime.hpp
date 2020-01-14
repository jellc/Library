// #line 2 "Binomial_runtime.hpp"
#ifndef Binomial_runtime_hpp
#define Binomial_runtime_hpp
#include <vector>

class binomial_runtime
{
    const int mod;
    int n;
    std::vector<int> _fact, _inv, _invfact;
  public:
    binomial_runtime(const int _mod) noexcept : mod(_mod), n{2}, _fact{1, 1}, _inv{0, 1}, _invfact{1, 1} {}
    void build(const int m) noexcept
    {
        if(m < n) return;
        int _n = n;
        while(m >= n) n <<= 1;
        _fact.resize(n), _inv.resize(n), _invfact.resize(n);
        for(int i = _n; i < n; ++i)
        {
            _fact[i] = (long long)_fact[i - 1] * i % mod;
            _inv[i] = mod - (long long)mod / i * _inv[mod % i] % mod;
            _invfact[i] = (long long)_invfact[i - 1] * _inv[i] % mod;
        }
    }
    long long fact(const int x) noexcept { return build(x), x < 0 ? 0 : _fact[x]; }
    long long inv(const int x) noexcept { return build(x), x < 0 ? 0 : _inv[x]; }
    long long invfact(const int x) noexcept { return build(x), x < 0 ? 0 : _invfact[x]; }
    long long binom(const int x, int y) noexcept { return fact(x) * invfact(y) % mod * invfact(x - y) % mod; }
};

#endif