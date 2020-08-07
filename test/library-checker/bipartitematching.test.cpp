#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"
#include "graph/directed/flow/Dinic.hpp"
#include "utils/read.hpp"
#include <cstdio>

int main()
{
    const int l=read<int>(), r=read<int>(), m=read<int>();
    Dinic<int> dinic(l+r+2);
    const int s=l+r,t=s+1;

    for(int i = 0; i < m; ++i)
    {
        int a=read<int>(),b=read<int>()+l;
        dinic.add_edge(a,b,1);
    }
    for(int i = 0; i < l; ++i)
    {
        dinic.add_edge(s,i,1);
    }
    for(int i = 0; i < r; ++i)
    {
        dinic.add_edge(i+l,t,1);
    }

    printf("%d\n",dinic.max_flow(s,t));

    for(int i = 0; i < l; ++i)
    {
        for(const auto &e: dinic[i])
        {
            if(!e.cap and e.dst<l+r)
            {
                printf("%d %d\n", i, e.dst-l);
            }
        }
    }
}
