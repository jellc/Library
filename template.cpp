/*
 * @file template.cpp
 * @brief Template
 */

#include <bits/extc++.h>

#include "lib/alias"
#include "lib/cxx20"
#include "lib/option"
#include "lib/sys"
#include "lib/utils"

int main() {
  using namespace workspace;

#define __precision__ 15

  /* given
  std::cin >> case_info.total, std::cin.ignore(); //*/

  /* unspecified
  case_info.total = -1; //*/

  io_setup(__precision__);
  case_info.iterate();
}

namespace workspace {

void main() {
  // start here!
}

}  // namespace workspace
