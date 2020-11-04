/*
 * @file make_vector.hpp
 * @brief Multi-dimensional vector
 */

#pragma once

#if __cplusplus >= 201703L

#include <tuple>
#include <vector>

namespace workspace {

/*
 * @brief make a multi-dimensional vector.
 * @tparam Tp type of the elements
 * @tparam S integer type
 * @tparam N dimension
 * @param sizes size of each dimension
 * @param init initial value
 */
template <typename Tp, typename S, size_t N>
constexpr auto make_vector(S* sizes, Tp const& init = Tp()) {
  static_assert(std::is_convertible_v<S, size_t>);
  if constexpr (N)
    return std::vector(*sizes,
                       make_vector<Tp, S, N - 1>(std::next(sizes), init));
  else
    return init;
}

/*
 * @brief make a multi-dimensional vector.
 * @param sizes size of each dimension
 * @param init initial value
 */
template <typename Tp, typename S, size_t N>
constexpr auto make_vector(const S (&sizes)[N], Tp const& init = Tp()) {
  return make_vector<Tp, S, N>((S*)sizes, init);
}

/*
 * @brief make a multi-dimensional vector.
 * @param sizes size of each dimension
 * @param init initial value
 */
template <typename Tp, typename S, size_t N, size_t I = 0>
constexpr auto make_vector(std::array<S, N> const& sizes,
                           Tp const& init = Tp()) {
  static_assert(std::is_convertible_v<S, size_t>);
  if constexpr (I == N)
    return init;
  else
    return std::vector(sizes[I], make_vector<Tp, S, N, I + 1>(sizes, init));
}

/*
 * @brief make a multi-dimensional vector.
 * @param sizes size of each dimension
 * @param init initial value
 */
template <typename Tp, size_t I = 0, class... Args>
constexpr auto make_vector(std::tuple<Args...> const& sizes,
                           Tp const& init = Tp()) {
  using tuple_type = std::tuple<Args...>;
  if constexpr (I == tuple_size_v<tuple_type>)
    return init;
  else {
    static_assert(
        std::is_convertible_v<tuple_element_t<I, tuple_type>, size_t>);
    return std::vector(get<I>(sizes), make_vector<Tp, I + 1>(sizes, init));
  }
}

/*
 * @brief make a multi-dimensional vector.
 * @param sizes size of each dimension
 * @param init initial value
 */
template <typename Tp, class Fst, class Snd>
constexpr auto make_vector(std::pair<Fst, Snd> const& sizes,
                           Tp const& init = Tp()) {
  static_assert(std::is_convertible_v<Fst, size_t>);
  static_assert(std::is_convertible_v<Snd, size_t>);
  return make_vector({(size_t)sizes.first, (size_t)sizes.second}, init);
}

}  // namespace workspace

#endif
