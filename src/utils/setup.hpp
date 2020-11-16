#pragma once

/*
 * @file setup.hpp
 * @brief Setup
 */

#include <chrono>
#include <iomanip>
#include <iostream>

namespace workspace {

/*
 * @fn io_setup
 * @brief Setup I/O before main process.
 */
__attribute__((constructor)) void io_setup() {
  using namespace std;
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(15);

#ifdef _buffer_check
  atexit([] {
    char bufc;
    if (cin >> bufc)
      cerr << "\n\033[43m\033[30mwarning: buffer not empty.\033[0m\n\n";
  });
#endif
}

namespace internal {
// The start time of the program.
const auto start_time{std::chrono::system_clock::now()};
}  // namespace internal

/*
 * @fn elapsed
 * @return elapsed time of the program
 */
int64_t elapsed() {
  using namespace std::chrono;
  const auto end_time{system_clock::now()};
  return duration_cast<milliseconds>(end_time - start_time).count();
}

}  // namespace workspace
