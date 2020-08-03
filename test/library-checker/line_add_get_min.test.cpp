#define PROBLEM "https://judge.yosupo.jp/problem/line_add_get_min"
#include "../../data_structure/convex_hull_trick/Li_Chao_tree.hpp"
#include <cstdio>
using i64=int64_t;

int main()
{
    int n,q;
    scanf("%d%d",&n,&q);
    Li_Chao_tree<i64> cht(-1e9,1e9+1);
    while(n--)
    {
        int a; i64 b;
        scanf("%d%lld",&a,&b);
        cht.insert(a,b);
    }
    while(q--)
    {
        int t;
        scanf("%d",&t);
        if(t)
        {
            int p;
            scanf("%d",&p);
            printf("%lld\n",cht.get(p));
        }
        else
        {
            int a; i64 b;
            scanf("%d%lld",&a,&b);
            cht.insert(a,b);
        }
    }
}
