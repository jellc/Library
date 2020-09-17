#include <bits/extc++.h>

#include "config.hpp"
#include "gcc_builtin.hpp"
#include "gcc_option.hpp"
#include "utils.hpp"
namespace workspace {
constexpr char eol = '\n';
using namespace std;
using i32 = int_least32_t;
using i64 = int_least64_t;
using i128 = __int128_t;
using u32 = uint_least32_t;
using u64 = uint_least64_t;
using u128 = __uint128_t;
template <class T, class Comp = std::less<T>>
using priority_queue = std::priority_queue<T, std::vector<T>, Comp>;
template <class T> using stack = std::stack<T, std::vector<T>>;
struct solver;
}  // namespace workspace
int main() { config::main<workspace::solver>(); }
unsigned config::cases() {
  // return -1; // not specified
  // int t; std::cin >> t; return t; // given
  return 1;
}

struct workspace::solver {
  solver() {
    // start here!
  }
};
