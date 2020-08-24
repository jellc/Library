#define PROBLEM "https://judge.yosupo.jp/problem/associative_array"
#include "utils/hash.hpp"
#include "utils/sfinae.hpp"
#include <random>

namespace workspace {
template <class int_type>
struct hash<enable_if_trait<int_type, std::is_integral>>
{
    const uint64_t seed[2], offset;
public:
    hash() : seed{std::random_device{}(), std::random_device{}()}, offset{std::random_device{}()} {}
    size_t operator()(const uint64_t &x) const { return (offset + x * seed[0] + (x >> 32) * seed[1]) >> 32; }
};
}

int main()
{
    int q; scanf("%d",&q);
    __gnu_pbds::gp_hash_table<long long, long long, workspace::hash<long long>> a;
    while(q--)
    {
        int t; long long k,v; scanf("%d%lld",&t,&k);
        if(t) printf("%lld\n",a[k]);
        else scanf("%lld",&v),a[k]=v;
    }
}
