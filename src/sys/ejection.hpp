#pragma once

/*
 * @file ejection.hpp
 * @brief Ejection
 */

#include <iostream>

namespace workspace {

struct ejection {
  bool exit = 0;
};

/*
 * @brief eject from a try block, throw nullptr
 * @param arg output
 */
template <class Tp> void eject(Tp const &arg) {
  std::cout << arg << "\n";
  throw ejection{};
}

void exit() { throw ejection{true}; }

}  // namespace workspace
