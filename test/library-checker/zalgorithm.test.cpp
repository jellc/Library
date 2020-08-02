#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"
#include "../../string/Z-algorithm.hpp"
#include <bits/stdc++.h>

int main()
{
    std::string s;
    std::cin>>s;
    Z_algorithm z(s);
    for(int e: z) printf(" %d",e);
    puts("");
}
