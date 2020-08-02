#define PROBLEM "https://judge.yosupo.jp/problem/scc"
#include "../../graph/directed/strongly_connected_components.hpp"
#include <cstdio>

int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    strongly_connected_components scc(n);
    for(int a,b; m--; )
    {
        scanf("%d%d",&a,&b);
        scc.add_edge(a,b);
    }
    printf("%d\n",scc.count());
    for(size_t i=0; i<scc.count(); i++)
    {
        printf("%d",scc.size(i));
        for(int v: scc.component(i)) printf(" %d",v);
        puts("");
    }
}