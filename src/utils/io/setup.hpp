#pragma once

/*
 * @file setup.hpp
 * @brief I/O Setup
 */

#include <iomanip>
#include <iostream>

namespace workspace {

/*
 * @fn io_setup
 * @brief Setup I/O before main process.
 */
__attribute__((constructor)) void io_setup() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << std::fixed << std::setprecision(15);

#ifdef _buffer_check
  atexit([] {
    char bufc;
    if (std::cin >> bufc)
      std::cerr << "\n\033[43m\033[30mwarning: buffer not empty.\033[0m\n\n";
  });
#endif
}

}  // namespace workspace
