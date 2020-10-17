#pragma once
#if __cplusplus >= 201703L
#include <tuple>
#include <vector>
namespace workspace {
template <typename T, size_t N>
constexpr auto make_vector(size_t* sizes, T const& init = T()) {
  if constexpr (N)
    return std::vector(*sizes, make_vector<T, N - 1>(sizes + 1, init));
  else
    return init;
}
template <typename T, typename S, size_t N,
          std::enable_if_t<std::is_convertible_v<S, size_t>>* = nullptr>
constexpr auto make_vector(const S (&sizes)[N], T const& init = T()) {
  return make_vector<T, N>((size_t*)sizes, init);
}
template <typename T, size_t N, size_t I = 0>
constexpr auto make_vector(std::array<size_t, N> const& array,
                           T const& init = T()) {
  if constexpr (I == N)
    return init;
  else
    return std::vector(array[I], make_vector<T, N, I + 1>(array, init));
}
template <typename T, size_t I = 0, class... Args>
constexpr auto make_vector(std::tuple<Args...> const& tuple,
                           T const& init = T()) {
  using tuple_type = std::tuple<Args...>;
  if constexpr (I == tuple_size_v<tuple_type>)
    return init;
  else {
    static_assert(
        std::is_convertible_v<tuple_element_t<I, tuple_type>, size_t>);
    return std::vector(get<I>(tuple), make_vector<T, I + 1>(tuple, init));
  }
}
template <typename T, class Fst, class Snd>
constexpr auto make_vector(std::pair<Fst, Snd> const& pair,
                           T const& init = T()) {
  return make_vector((size_t[2]){pair.first, pair.second}, init);
}
}  // namespace workspace
#endif
