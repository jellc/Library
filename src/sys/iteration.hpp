#pragma once

/*
 * @file iteration.hpp
 * @brief Case Iteration
 */

#include <cassert>

#include "ejection.hpp"

namespace workspace {

void main();

struct {
  unsigned current{0}, total{1};

  void read() { (std::cin >> total).ignore(); }

  int iterate() {
    static bool once = false;
    assert(!once);
    once = true;
    while (current++ < total) {
      try {
        main();
      } catch (ejection const& status) {
        if (status.exit) break;
      }
    }
    return 0;
  }
} case_info;

}  // namespace workspace
