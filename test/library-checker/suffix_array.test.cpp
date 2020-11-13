#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"
#include <bits/stdc++.h>

#include "string/suffix_array.hpp"
#include "utils/io.hpp"

using namespace std;

int main() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  string s;
  cin >> s;
  cout << workspace::suffix_array<string>(s) << "\n";
}
