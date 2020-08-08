#define PROBLEM "https://judge.yosupo.jp/problem/assignment"
#include "graph/directed/flow/min_cost_flow.hpp"
#include <cstdio>
#include <cstdint>
using i64=int64_t;

int main()
{
    int n; scanf("%d",&n);
    min_cost_flow<int,i64> mcf(n*2);
    for(int i=0;i<n;i++)
    {
        mcf.supply(i,1);
        mcf.supply(i+n,-1);
        for(int j=0;j<n;j++)
        {
            int a; scanf("%d",&a);
            mcf.add_edge(i,j+n,1,a);
        }
    }
    printf("%lld\n",mcf.optimal());
    for(int i=0;i<n;i++)
    {
        for(auto &e:mcf[i])
        {
            if(!e.cap) printf("%d ",e.dst-n);
        }
    }
    puts("");
}
