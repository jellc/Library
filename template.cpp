#include <bits/extc++.h>
#if __has_include(<bit>)
#include <bit>
#endif
#include "alias.hpp"
#include "config.hpp"
#include "option.hpp"
#include "utils.hpp"

namespace workspace {
void main();
}
int main() { config::loop(workspace::main); }

unsigned config::cases() {
  // return -1; // unspecified
  // int t; std::cin >> t; return t; // given
  return 1;
}

namespace workspace {
void main() {
  // start here!
}
}
