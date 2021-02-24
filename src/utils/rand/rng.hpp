#pragma once

/**
 * @file rng.hpp
 * @brief Random Number Generator
 */

#include <random>

namespace workspace {

template <typename _Arithmetic>
using uniform_distribution = typename std::conditional<
    std::is_integral<_Arithmetic>::value,
    std::uniform_int_distribution<_Arithmetic>,
    std::uniform_real_distribution<_Arithmetic>>::type;

template <typename _Arithmetic>
class random_number_generator : uniform_distribution<_Arithmetic> {
  using base = uniform_distribution<_Arithmetic>;

  std::mt19937 engine;

 public:
  random_number_generator(_Arithmetic __min, _Arithmetic __max)
      : base(__min, __max), engine(std::random_device{}()) {}

  random_number_generator(_Arithmetic __max = 1)
      : base(_Arithmetic(0), __max), engine(std::random_device{}()) {}

  random_number_generator(typename base::param_type const& __param)
      : base(__param) {}

  decltype(auto) operator()() noexcept { return base::operator()(engine); }
};

}  // namespace workspace
