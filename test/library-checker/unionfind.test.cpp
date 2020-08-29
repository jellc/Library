#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"
#include "data_structure/union_find/unbalanced.hpp"
#include <cstdio>

int main()
{
    int n,q; scanf("%d%d",&n,&q);
    union_find uf(n);
    union_find_unbalanced ufu(n);
    while(q--)
    {
        int t,l,r; scanf("%d%d%d",&t,&l,&r);
        if(t)
        {
            printf("%d\n",uf.same(l,r));
            assert(uf.same(l,r)==ufu.same(l,r));
        }
        else
        {
            uf.unite(l,r);
            ufu.unite(l,r);
        }
    }
}
