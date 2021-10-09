#pragma once

/**
 * @file edge.h
 * @brief Edge
 */

#include "lib/cxx17"

namespace workspace {

namespace _graph_impl {

// Default edge attribute.
struct null {};

}  // namespace _graph_impl

template <class _Weight, class _Attr = _graph_impl::null>
struct weighted_edge : _Attr {
  using attribute = _Attr;
  using value_type = _Weight;
  using node_type = size_t;

  node_type tail, head;
  value_type weight{};

  constexpr weighted_edge() = default;

  template <class... _Args>
  constexpr weighted_edge(node_type __u, node_type __v, value_type __c = 0,
                          _Args &&...__args) noexcept
      : _Attr{std::forward<_Args>(__args)...},
        tail(__u),
        head(__v),
        weight(__c) {}

  constexpr bool operator<(const weighted_edge &__e) const noexcept {
    return weight < __e.weight;
  }
  constexpr bool operator<=(const weighted_edge &__e) const noexcept {
    return weight <= __e.weight;
  }
  constexpr bool operator>(const weighted_edge &__e) const noexcept {
    return weight > __e.weight;
  }
  constexpr bool operator>=(const weighted_edge &__e) const noexcept {
    return weight >= __e.weight;
  }
};

template <class _Attr = _graph_impl::null>
struct edge : weighted_edge<int, _Attr> {
  using base_type = weighted_edge<int, _Attr>;

  using typename base_type::node_type;
  using base_type::operator<;
  using base_type::operator>;

  constexpr edge() = default;

  template <class... _Args>
  constexpr edge(node_type __u, node_type __v, _Args &&...__args) noexcept
      : base_type(__u, __v, __u != __v, std::forward<_Args>(__args)...) {}
};

template <size_t _Nm, class _Attr>
constexpr std::tuple_element_t<_Nm, edge<_Attr>> &get(
    edge<_Attr> &__e) noexcept {
  if _CXX17_CONSTEXPR (_Nm > 1)
    return __e;
  else if _CXX17_CONSTEXPR (_Nm)
    return __e.head;
  else
    return __e.tail;
}

template <size_t _Nm, class _Attr>
constexpr const std::tuple_element_t<_Nm, edge<_Attr>> &get(
    const edge<_Attr> &__e) noexcept {
  if _CXX17_CONSTEXPR (_Nm > 1)
    return __e;
  else if _CXX17_CONSTEXPR (_Nm)
    return __e.head;
  else
    return __e.tail;
}

template <size_t _Nm, class _Attr>
constexpr std::tuple_element_t<_Nm, edge<_Attr>> &&get(
    edge<_Attr> &&__e) noexcept {
  return std::move(get<_Nm>(__e));
}

template <size_t _Nm, class _Weight, class _Attr>
constexpr const std::tuple_element_t<_Nm, weighted_edge<_Weight, _Attr>> &get(
    const weighted_edge<_Weight, _Attr> &__e) noexcept {
  if _CXX17_CONSTEXPR (_Nm > 2)
    return __e;
  else if _CXX17_CONSTEXPR (_Nm > 1)
    return __e.weight;
  else if _CXX17_CONSTEXPR (_Nm)
    return __e.head;
  else
    return __e.tail;
}

template <size_t _Nm, class _Weight, class _Attr>
constexpr std::tuple_element_t<_Nm, weighted_edge<_Weight, _Attr>> &get(
    weighted_edge<_Weight, _Attr> &__e) noexcept {
  if _CXX17_CONSTEXPR (_Nm > 2)
    return __e;
  else if _CXX17_CONSTEXPR (_Nm > 1)
    return __e.weight;
  else if _CXX17_CONSTEXPR (_Nm)
    return __e.head;
  else
    return __e.tail;
}

template <size_t _Nm, class _Weight, class _Attr>
constexpr std::tuple_element_t<_Nm, weighted_edge<_Weight, _Attr>> &&get(
    weighted_edge<_Weight, _Attr> &&__e) noexcept {
  return std::move(get<_Nm>(__e));
}

}  // namespace workspace

namespace std {

template <class _Attr>
struct tuple_size<workspace::edge<_Attr>> : integral_constant<size_t, 3> {};

template <>
struct tuple_size<workspace::edge<>> : integral_constant<size_t, 2> {};

template <class _Weight, class _Attr>
struct tuple_size<workspace::weighted_edge<_Weight, _Attr>>
    : integral_constant<size_t, 4> {};

template <class _Weight>
struct tuple_size<workspace::weighted_edge<_Weight>>
    : integral_constant<size_t, 3> {};

template <size_t _Nm, class _Attr>
struct tuple_element<_Nm, workspace::edge<_Attr>> {
  using type = std::conditional_t<(_Nm < 2), size_t, _Attr>;
};

template <size_t _Nm, class _Weight, class _Attr>
struct tuple_element<_Nm, workspace::weighted_edge<_Weight, _Attr>> {
  using type = std::conditional_t<(_Nm < 2), size_t,
                                  std::conditional_t<_Nm == 2, _Weight, _Attr>>;
};

}  // namespace std
