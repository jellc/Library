#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/1/NTL_1_E"
#include "number_theory/ext_gcd.hpp"
#include "utils/iostream_overload.hpp"

int main()
{
    int a,b;
    std::cin>>a>>b;
    auto [x,y]=ext_gcd(a,b);
    if(x>0) x-=b,y+=a;
    if((long long)(y-x)*2>a+b) x+=b,y-=a;
    std::cout<<x<<" "<<y<<"\n";
}
