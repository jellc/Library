#pragma once
#if __cplusplus >= 201703L
#include <vector>
namespace workspace {
template <typename T, size_t N>
constexpr auto make_vector(size_t* sizes, T const& init = T()) {
  if constexpr (N)
    return std::vector(*sizes, make_vector<T, N - 1>(std::next(sizes), init));
  else
    return init;
}
template <typename T, size_t N>
constexpr auto make_vector(const size_t (&sizes)[N], T const& init = T()) {
  return make_vector<T, N>((size_t*)sizes, init);
}
}  // namespace workspace
#endif
