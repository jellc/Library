#define PROBLEM "https://judge.yosupo.jp/problem/two_edge_connected_components"
#include "../graph/undirected/two_edge_connected_components.hpp"
#include <cstdio>
#include <algorithm>

main()
{
    int v,e;
    scanf("%d%d",&v,&e);
    two_edge_connected_component becc(v);
    for(int a,b; e--;)
    {
        scanf("%d%d",&a,&b);
        becc.add_edge(a,b);
    }
    becc.make();
    printf("%d\n",becc.count());
    for(size_t i=0; i<becc.count(); i++)
    {
        const auto &lst=becc.component(i);
        printf("%d",lst.size());
        for(int v: lst)
        {
            printf(" %d",v);
        }
        puts("");
    }
}