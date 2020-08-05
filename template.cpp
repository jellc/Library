#ifdef LOCAL
    #define _GLIBCXX_DEBUG
#else
    #pragma GCC optimize("O3")
    #pragma GCC target("avx,avx2")
    #pragma GCC optimize("unroll-loops")
#endif
// #define NDEBUG

#include <bits/stdc++.h>
#include <ext/rope>

#include "config.hpp"
#include "utils/iostream_overload.hpp"
#include "utils/fixed_point.hpp"
#include "utils/read.hpp"
#include "utils/chval.hpp"
#include "utils/binary_search.hpp"

#pragma region alias
using namespace std; using namespace __gnu_cxx;
using i32 = int_least32_t; using i64 = int_least64_t;
using p32 = pair<i32, i32>; using p64 = pair<i64, i64>;
template <class T, class Comp = less<T>> using heap = priority_queue<T, vector<T>, Comp>;
template <class T> using hashset = unordered_set<T>;
template <class Key, class Value> using hashmap = unordered_map<Key, Value>;
#pragma endregion

unsigned config::cases()
{
    unsigned t = 1;
    // t = -1;
    // cin >> t;
    return t;
}

struct solver
{
    solver()
    {
        
    }
};
