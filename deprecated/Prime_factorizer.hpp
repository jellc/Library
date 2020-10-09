#ifndef Prime_factorizer_hpp
#define Prime_factorizer_hpp

// calculate the least prime factor for positive integers less than N in compile time.
template <int N>
class prime_factorizer
{
    constexpr static int loop_limit = 1 << 17;
    int least[N], primes[N >> 3];
    int n = 0;

  public:
    constexpr prime_factorizer() : least{1}, primes{}, n{}
    {
        for(int i = 2; i < N; )
        {
            for(int j = 0; j < loop_limit && i < N; ++j, ++i)
            {
                if(!least[i]) primes[n++] = least[i] = i;
                int *p = primes;

                while(*p && *p <= least[i] && *p * i < N)
                {
                    for(int k = 0; k < loop_limit && *p && *p <= least[i] && *p * i < N; ++k, ++p)
                    {
                        least[*p * i] = *p;
                    }
                }
            }
        }
    }

    constexpr bool prime(int x) const { assert(0 <= x && x < N); return least[x] == x; }

    constexpr int least_prime_factor(int x) const { assert(0 < x && x < N); return least[x]; }
}; // class prime_factorizer

#endif // Prime_factorizer_hpp
