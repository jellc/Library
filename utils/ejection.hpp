#pragma once

/*
 * @file ejection.hpp
 * @brief Ejection from try block
 */

#include <iostream>

namespace workspace {

/*
 * @brief eject from a try block, throw nullptr
 * @param arg output
 */
template <class Tp> void eject(Tp const &arg) {
  std::cout << arg << "\n";
  throw nullptr;
}

}  // namespace workspace
