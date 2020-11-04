#pragma once
#include "config.hpp"

namespace workspace {

/*
 * @brief printf("Case #%u: ", config::caseid)
 * @param os reference to ostream
 * @return os
 */
std::ostream& casefmt(std::ostream& os) {
  return os << "Case #" << config::caseid << ": ";
}

}  // namespace workspace
