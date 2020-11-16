/*
 * @file template.cpp
 * @brief Template
 */

#include <bits/extc++.h>

#include "alias"
#include "config"
#include "cxx20"
#include "option"
#include "utils"

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
}  // namespace workspace
