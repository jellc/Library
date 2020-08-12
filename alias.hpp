#pragma once
#include <bits/stdc++.h>
using namespace std; using namespace __gnu_cxx;
using i32 = int_least32_t; using i64 = int_least64_t;
using p32 = pair<i32, i32>; using p64 = pair<i64, i64>;
template <class T, class Comp = less<T>> using heap = priority_queue<T, vector<T>, Comp>;
template <class T> using hashset = unordered_set<T>;
template <class Key, class Value> using hashmap = unordered_map<Key, Value>;
