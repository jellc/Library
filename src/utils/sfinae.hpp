#pragma once

/**
 * @file sfinae.hpp
 * @brief SFINAE
 */

#include <cstdint>
#include <iterator>
#include <type_traits>

#ifdef __SIZEOF_INT128__
#define __INT128_DEFINED__ 1
#else
#define __INT128_DEFINED__ 0
#endif

namespace std {

#if __INT128_DEFINED__

template <> struct make_signed<__uint128_t> { using type = __int128_t; };
template <> struct make_signed<__int128_t> { using type = __int128_t; };

template <> struct make_unsigned<__uint128_t> { using type = __uint128_t; };
template <> struct make_unsigned<__int128_t> { using type = __uint128_t; };

#endif

}  // namespace std

namespace workspace {

template <class type, template <class> class trait>
using enable_if_trait_type = typename std::enable_if<trait<type>::value>::type;

template <class Container>
using element_type = typename std::decay<decltype(
    *std::begin(std::declval<Container&>()))>::type;

template <class T, class = std::nullptr_t>
struct has_begin : std::false_type {};

template <class T>
struct has_begin<T, decltype(std::begin(std::declval<T>()), nullptr)>
    : std::true_type {};

template <class T, class = int> struct mapped_of {
  using type = element_type<T>;
};
template <class T>
struct mapped_of<T,
                 typename std::pair<int, typename T::mapped_type>::first_type> {
  using type = typename T::mapped_type;
};
template <class T> using mapped_type = typename mapped_of<T>::type;

template <class T, class = void> struct is_integral_ext : std::false_type {};
template <class T>
struct is_integral_ext<
    T, typename std::enable_if<std::is_integral<T>::value>::type>
    : std::true_type {};

#if __INT128_DEFINED__

template <> struct is_integral_ext<__int128_t> : std::true_type {};
template <> struct is_integral_ext<__uint128_t> : std::true_type {};

#endif

#if __cplusplus >= 201402

template <class T>
constexpr static bool is_integral_ext_v = is_integral_ext<T>::value;

#endif

template <typename T, typename = void> struct multiplicable_uint {
  using type = uint_least32_t;
};
template <typename T>
struct multiplicable_uint<
    T, typename std::enable_if<(2 < sizeof(T)) &&
                               (!__INT128_DEFINED__ || sizeof(T) <= 4)>::type> {
  using type = uint_least64_t;
};

#if __INT128_DEFINED__

template <typename T>
struct multiplicable_uint<T, typename std::enable_if<(4 < sizeof(T))>::type> {
  using type = __uint128_t;
};

#endif

template <typename T> struct multiplicable_int {
  using type =
      typename std::make_signed<typename multiplicable_uint<T>::type>::type;
};

}  // namespace workspace
