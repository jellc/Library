#pragma once
#include <iostream>

namespace workspace {
// print arg, then throw nullptr.
template <class Tp> void eject(Tp const &arg) {
  std::cout << arg << "\n";
  throw nullptr;
}
}
