#define PROBLEM "https://judge.yosupo.jp/problem/subset_convolution"
#include "../../algebra/convolution/subset.hpp"
#include "../../modulus/modint.hpp"
#include <iostream>

int main()
{
    using mint=modint_runtime;
    mint::mod()=998244353;
    using std::cin;
    int n; cin>>n;
    std::vector<mint> a(1<<n),b(1<<n);
    for(auto &x: a) cin>>x;
    for(auto &x: b) cin>>x;
    a=subset_convolute(a,b);
    for(auto x: a) printf("%d ",x);
    puts("");
}
