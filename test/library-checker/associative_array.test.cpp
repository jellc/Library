#define PROBLEM "https://judge.yosupo.jp/problem/associative_array"
#include "utils/hash.hpp"

int main()
{
    int q; scanf("%d",&q);
    workspace::hashmap<long long, long long> a;
    while(q--)
    {
        int t; long long k,v; scanf("%d%lld",&t,&k);
        if(t) printf("%lld\n",a[k]);
        else scanf("%lld",&v),a[k]=v;
    }
}
