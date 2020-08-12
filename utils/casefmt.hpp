#pragma once
#include "config.hpp"
std::ostream &casefmt(std::ostream& os) { return os << "Case #" << config::caseid << ": "; }
