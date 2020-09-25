#include <bits/extc++.h>
#if __has_include(<bit>)
#include <bit>
#endif
#include "alias.hpp"
#include "config.hpp"
#include "option.hpp"
#include "utils.hpp"
namespace workspace {
struct solver;
}  // namespace workspace
int main() { config::main<workspace::solver>(); }
unsigned config::cases() {
  // return -1; // unspecified
  // int t; std::cin >> t; return t; // given
  return 1;
}

struct workspace::solver {
  solver() {
    // start here!
  }
};
