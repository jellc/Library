#pragma once
#include <chrono>
#include <iomanip>
#include <iostream>

namespace config {

const auto start_time{std::chrono::system_clock::now()};

/*
 * @fn elapsed
 * @return elapsed time of the program
 */
int64_t elapsed() {
  using namespace std::chrono;
  const auto end_time{system_clock::now()};
  return duration_cast<milliseconds>(end_time - start_time).count();
}

/*
 * @fn setup
 * @brief setup I/O before main process.
 */
__attribute__((constructor)) void setup() {
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

unsigned cases(), caseid = 1;  // current case number, 1-indexed

/*
 * @fn loop
 * @brief iterate cases.
 * @param main called once per case
 */
template <class F> void loop(F main) {
  for (const unsigned total = cases(); caseid <= total; ++caseid) {
    try {
      main();
    } catch (std::nullptr_t) {
    }
  }
}

}  // namespace config
