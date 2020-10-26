#pragma once
#include <cassert>

#include "sfinae.hpp"

template <typename int_type>
constexpr
    typename std::enable_if<is_integral_ext<int_type>::value, int_type>::type
    floor_div(int_type x, int_type y) {
  assert(y != 0);
  if (y < 0) x = -x, y = -y;
  return x < 0 ? (x - y + 1) / y : x / y;
}
