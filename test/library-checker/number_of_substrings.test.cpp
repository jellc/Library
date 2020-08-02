#define PROBLEM "https://judge.yosupo.jp/problem/number_of_substrings"
#include "../../string/suffix_array.hpp"
#include <iostream>

int main()
{
    std::string s;
    std::cin>>s;
    suffix_array sa(s);
    long long ans=0;
    for(size_t i=0; i<s.size(); i++)
    {
        ans+=s.size()-sa[i]-sa.lcp_array()[i];
    }
    printf("%lld\n",ans);
}
