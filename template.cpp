#include <bits/extc++.h>

#include "alias.hpp"
#include "config.hpp"
#include "cxx20.hpp"
#include "option.hpp"
#include "utils.hpp"

namespace workspace {
void main();
}
int main() { config::loop(workspace::main); }

unsigned config::cases() {
  // return -1; // unspecified
  // int t; std::cin >> t; std::cin.ignore(); return t; // given
  return 1;
}

namespace workspace {
void main() {
  // start here!
}
}
