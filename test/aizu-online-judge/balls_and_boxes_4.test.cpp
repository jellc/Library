#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/5/DPL_5_D"
#include "combinatorics/binomial.hpp"
#include <cstdio>

int main()
{
    using modint = modint<1000000007>;
    int n,k; scanf("%d%d",&n,&k);
    printf("%d\n",binomial<modint>()(n+k-1,n));
}
