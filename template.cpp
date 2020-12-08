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

  io_setup(15);

  /* given
  case_info.read();  //*/

  /* unspecified
  case_info.total = -1; //*/

  return case_info.iterate();
}

namespace workspace {

void main() {
  // start here!
}

}  // namespace workspace
