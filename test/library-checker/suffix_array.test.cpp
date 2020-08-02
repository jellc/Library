#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"
#include "../../string/suffix_array.hpp"
#include <bits/stdc++.h>
using namespace std;

template <class Container, typename Value = typename Container::value_type, enable_if_t<!is_same<decay_t<Container>, string>::value, nullptr_t> = nullptr>
istream& operator>>(istream& is, Container &cont) { for(auto&& e : cont) is >> e; return is; }
template <class T, class... types> T read(types... args) noexcept { T obj(args...); std::cin >> obj; return obj; }
template <class Container, typename Value = typename Container::value_type, enable_if_t<!is_same<decay_t<Container>, string>::value, nullptr_t> = nullptr>
ostream& operator<<(ostream& os, const Container &cont) { bool flag = 1; for(auto&& e : cont) flag ? flag = 0 : (os << ' ', 0), os << e; return os; }

main()
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    string s; cin>>s;
    cout << suffix_array<string>(s) << "\n";
}