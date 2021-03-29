#pragma once

/**
 * @file make_vector.hpp
 * @brief Multi-dimensional Vector
 */

#if __cplusplus >= 201703L

#include <tuple>
#include <vector>

namespace workspace {

/**
 * @brief Make a multi-dimensional vector.
 *
 * @param __dim Dimension
 * @param __x Initial value
 */
template <typename _Tp, class _Dim, size_t _Nm>
constexpr decltype(auto) make_vector([[maybe_unused]] _Dim* __dim,
                                     const _Tp& __x = _Tp()) {
  static_assert(std::is_convertible<_Dim, size_t>::value);

  if constexpr (_Nm)
    return std::vector(*__dim,
                       make_vector<_Tp, _Dim, _Nm - 1>(std::next(__dim), __x));
  else
    return __x;
}

/**
 * @brief Make a multi-dimensional vector.
 *
 * @param __dim Dimension
 * @param __x Initial value
 */
template <typename _Tp, class _Dim, size_t _Nm>
constexpr decltype(auto) make_vector(const _Dim (&__dim)[_Nm],
                                     const _Tp& __x = _Tp()) {
  return make_vector<_Tp, _Dim, _Nm>((_Dim*)__dim, __x);
}

/**
 * @brief Make a multi-dimensional vector.
 *
 * @param __dim Dimension
 * @param __x Initial value
 */
template <typename _Tp, class _Dim, size_t _Nm = 0>
constexpr decltype(auto) make_vector([[maybe_unused]] const _Dim& __dim,
                                     const _Tp& __x = _Tp()) {
  if constexpr (_Nm == std::tuple_size<_Dim>::value)
    return __x;

  else {
    static_assert(
        std::is_convertible<std::tuple_element_t<_Nm, _Dim>, size_t>::value);

    return std::vector(std::get<_Nm>(__dim),
                       make_vector<_Tp, _Dim, _Nm + 1>(__dim, __x));
  }
}

}  // namespace workspace

#endif
