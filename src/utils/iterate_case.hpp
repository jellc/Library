#pragma once

/*
 * @file iterate_case.hpp
 * @brief Iterate Testcases
 */

namespace workspace {

namespace internal {
// The 1-based index of the current testcase.
unsigned caseid;
}  // namespace internal

void main();
unsigned case_number();

/*
 * @fn iterate_main
 * @brief Iterate main function.
 */
void iterate_main() {
  for (unsigned total = case_number(), &counter = (internal::caseid = 1);
       counter <= total; ++counter) {
    try {
      main();
    } catch (std::nullptr_t) {
    }
  }
}

}  // namespace workspace
