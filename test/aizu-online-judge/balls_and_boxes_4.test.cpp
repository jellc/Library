#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/5/DPL_5_D"
#include "combinatorics/binomial.hpp"
#include <cstdio>

int main()
{
    int n,k; scanf("%d%d",&n,&k);
    printf("%d\n",binomial<1000000007>()(n+k-1,n));
}
