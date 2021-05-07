#pragma once

/**
 * @file operation.hpp
 * @brief Operation Traits
 */

#include <type_traits>

namespace workspace {

// Unary `+`
template <class _Tp>
using require_unary_plus = std::enable_if_t<
    std::is_convertible<decltype(+std::declval<const _Tp &>()), _Tp>::value>;

template <class _Tp, class = void> struct has_unary_plus : std::false_type {};

template <class _Tp>
struct has_unary_plus<_Tp, require_unary_plus<_Tp>> : std::true_type {};

// Unary `-`
template <class _Tp>
using require_unary_minus = std::enable_if_t<
    std::is_convertible<decltype(-std::declval<const _Tp &>()), _Tp>::value>;

template <class _Tp, class = void> struct has_unary_minus : std::false_type {};

template <class _Tp>
struct has_unary_minus<_Tp, require_unary_minus<_Tp>> : std::true_type {};

// Binary `+`
template <class _Tp1, class _Tp2 = _Tp1>
using require_binary_plus =
    std::enable_if_t<std::is_convertible<decltype(std::declval<const _Tp1 &>() +
                                                  std::declval<const _Tp2 &>()),
                                         _Tp1>::value>;

template <class _Tp1, class _Tp2 = _Tp1, class = void>
struct has_binary_plus : std::false_type {};

template <class _Tp1, class _Tp2>
struct has_binary_plus<_Tp1, _Tp2, require_binary_plus<_Tp1, _Tp2>>
    : std::true_type {};

// Binary `-`
template <class _Tp1, class _Tp2 = _Tp1>
using require_binary_minus =
    std::enable_if_t<std::is_convertible<decltype(std::declval<const _Tp1 &>() -
                                                  std::declval<const _Tp2 &>()),
                                         _Tp1>::value>;

template <class _Tp1, class _Tp2 = _Tp1, class = void>
struct has_binary_minus : std::false_type {};

template <class _Tp1, class _Tp2>
struct has_binary_minus<_Tp1, _Tp2, require_binary_minus<_Tp1, _Tp2>>
    : std::true_type {};

// Binary `*`
template <class _Tp1, class _Tp2 = _Tp1>
using require_binary_multiplies =
    std::enable_if_t<std::is_convertible<decltype(std::declval<const _Tp1 &>() *
                                                  std::declval<const _Tp2 &>()),
                                         _Tp1>::value>;

template <class _Tp1, class _Tp2 = _Tp1, class = void>
struct has_binary_multiplies : std::false_type {};

template <class _Tp1, class _Tp2>
struct has_binary_multiplies<_Tp1, _Tp2, require_binary_multiplies<_Tp1, _Tp2>>
    : std::true_type {};

// Binary `/`
template <class _Tp1, class _Tp2 = _Tp1>
using require_binary_divides =
    std::enable_if_t<std::is_convertible<decltype(std::declval<const _Tp1 &>() /
                                                  std::declval<const _Tp2 &>()),
                                         _Tp1>::value>;

template <class _Tp1, class _Tp2 = _Tp1, class = void>
struct has_binary_divides : std::false_type {};

template <class _Tp1, class _Tp2>
struct has_binary_divides<_Tp1, _Tp2, require_binary_divides<_Tp1, _Tp2>>
    : std::true_type {};

// Binary `%`
template <class _Tp1, class _Tp2 = _Tp1>
using require_binary_modulus =
    std::enable_if_t<std::is_convertible<decltype(std::declval<const _Tp1 &>() %
                                                  std::declval<const _Tp2 &>()),
                                         _Tp1>::value>;

template <class _Tp1, class _Tp2 = _Tp1, class = void>
struct has_binary_modulus : std::false_type {};

template <class _Tp1, class _Tp2>
struct has_binary_modulus<_Tp1, _Tp2, require_binary_modulus<_Tp1, _Tp2>>
    : std::true_type {};

}  // namespace workspace
