#include "gcc_option.hpp"
#include <bits/extc++.h>
#include "config.hpp"
#include "utils/binary_search.hpp"
#include "utils/casefmt.hpp"
#include "utils/chval.hpp"
#include "utils/fixed_point.hpp"
#include "utils/hash.hpp"
#include "utils/iostream_overload.hpp"
#include "utils/read.hpp"
namespace workspace {
    using namespace std; using namespace __gnu_pbds; using namespace __gnu_cxx;
    using i64 = int_least64_t; using p32 = pair<int, int>; using p64 = pair<i64, i64>;
    template <class T, class Comp = less<T>> using heap = std::priority_queue<T, vector<T>, Comp>;
    struct solver;
}
int main() { config::main<workspace::solver>(); }
unsigned config::cases() {
    // return -1; // not specify
    // int t; std::cin >> t; return t; // given
    return 1;
}

struct workspace::solver { // start here!

solver()
{
    
}};
