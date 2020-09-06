#pragma once
#include <chrono>
#include <iomanip>
#include <iostream>
namespace config {
const auto start_time{std::chrono::system_clock::now()};
int64_t elapsed() {
  using namespace std::chrono;
  const auto end_time{system_clock::now()};
  return duration_cast<milliseconds>(end_time - start_time).count();
}
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
unsigned cases(void), caseid = 1;
template <class C> void main() {
  for (const unsigned total = cases(); caseid <= total; ++caseid) C();
}
}  // namespace config
