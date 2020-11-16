#pragma once

/*
 * @file castfmt
 * @brief Case Output Format
 */

#include "../iterate_case.hpp"

namespace workspace {

/*
 * @fn casefmt
 * @brief printf("Case #%u: ", internal::caseid)
 * @param os Reference to ostream
 * @return os
 */
std::ostream& casefmt(std::ostream& os) {
  return os << "Case #" << internal::caseid << ": ";
}

}  // namespace workspace
