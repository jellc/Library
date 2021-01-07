/**
 * @file template.cpp
 * @brief Template
 */

// #undef _GLIBCXX_DEBUG
// #define NDEBUG
#include <bits/extc++.h>

#include "lib/alias"
#include "lib/cxx20"
#include "lib/direct"
#include "lib/opt"
#include "lib/sys"
#include "lib/utils"

signed main() {
  using namespace workspace;

  io_setup(15);

  /* given
    case_info.read();  //*/

  /* unspecified
    case_info.total = -1;//*/

  return case_info.iterate();
}

namespace workspace {

void main() {  //
  /* start here! */
}

}  // namespace workspace
