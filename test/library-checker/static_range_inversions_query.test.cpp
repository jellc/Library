#define PROBLEM "https://judge.yosupo.jp/problem/static_range_inversions_query"
#include "../../data_structure/Mo.hpp"
#include "../../utils/coordinate_compression.hpp"
#include "../../data_structure/segment_tree/segment_tree.hpp"
#include <cstdio>
using i64=int64_t;

int main()
{
    int n,q;
    scanf("%d%d",&n,&q);
    std::vector<int> a(n);
    for(int &x: a) scanf("%d",&x);
    coordinate_compression ccmp(a);
    std::vector<int> cnt(ccmp.count());
    segment_tree<int> seg(n);
    int nl=0,nr=0;
    i64 invs=0;
    auto add=[&](int i)
    {
        int nv=ccmp[i];
        if(i<nl) // left end
        {
            invs+=seg.fold(0,nv);
            nl--;
        }
        else // right end
        {
            invs+=seg.fold(nv+1,n);
            nr++;
        }
        seg[nv]++;
    };
    auto del=[&](int i)
    {
        int nv=ccmp[i];
        if(i==nl) // left end
        {
            invs-=seg.fold(0,nv);
            nl++;
        }
        else // right end
        {
            assert(nr==i+1);
            invs-=seg.fold(nv+1,n);
            nr--;
        }
        seg[nv]--;
    };
    Mo mo(n,add,del);
    for(int i=0; i<q; i++)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        mo.set(l,r);
    }
    std::vector<i64> ans(q);
    for(int i=0; i<q; i++)
    {
        int id=mo.process();
        ans[id]=invs;
    }
    for(i64 x: ans) printf("%lld\n",x);
}