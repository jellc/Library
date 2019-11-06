#include <bits/stdc++.h>

template <uint_fast32_t N = 1 << 17>
struct PrimeSieve
{
    bool is_prime[N + 1];

    constexpr PrimeSieve() : is_prime()
    {
        for(int i = 2; i <= N; ++i)
            is_prime[i] = true;
        for(int d = 2; d * d <= N; ++d)
        {
            if(!is_prime[d]) continue;
            is_prime[d] = 0;
            int k = d;
            while((k += d) <= N)
                is_prime[d] = false;
        }
    }

    constexpr bool query(int x) const
    {
        if(x < 0 || x > N) return false;
        return is_prime[x];
    }
};
