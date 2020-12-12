#pragma once

/**
 * @file rng.hpp
 * @brief Random Number Generator
 */

#include <random>

namespace workspace {

template <typename Arithmetic>
using uniform_distribution =
    typename std::conditional<std::is_integral<Arithmetic>::value,
                              std::uniform_int_distribution<Arithmetic>,
                              std::uniform_real_distribution<Arithmetic>>::type;

template <typename Arithmetic>
class random_number_generator : uniform_distribution<Arithmetic> {
  using base = uniform_distribution<Arithmetic>;

  std::mt19937 engine;

 public:
  template <class... Args>
  random_number_generator(Args&&... args)
      : base(args...), engine(std::random_device{}()) {}

  auto operator()() { return base::operator()(engine); }
};

}  // namespace workspace
