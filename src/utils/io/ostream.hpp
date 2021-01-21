#pragma once

/**
 * @file ostream.hpp
 * @brief Output Stream
 */

#include <tuple>

namespace workspace {

/**
 * @brief Stream insertion operator for std::pair.
 *
 * @param __os Output stream
 * @param __p Pair
 * @return Reference to __os.
 */
template <class Os, class T1, class T2>
Os &operator<<(Os &__os, const std::pair<T1, T2> &__p) {
  return __os << __p.first << ' ' << __p.second;
}

/**
 * @brief Stream insertion operator for std::tuple.
 *
 * @param __os Output stream
 * @param __t Tuple
 * @return Reference to __os.
 */
template <class Os, class Tp, size_t N = 0>
typename std::enable_if<bool(std::tuple_size<Tp>::value + 1), Os &>::type
operator<<(Os &__os, const Tp &__t) {
  if constexpr (N != std::tuple_size<Tp>::value) {
    if constexpr (N) __os << ' ';
    __os << std::get<N>(__t);
    operator<<<Os, Tp, N + 1>(__os, __t);
  }
  return __os;
}

template <class Os, class Container,
          typename = decltype(std::begin(std::declval<Container>()))>
typename std::enable_if<
    !std::is_same<typename std::decay<Container>::type, std::string>::value &&
        !std::is_same<typename std::decay<Container>::type, char *>::value,
    Os &>::type
operator<<(Os &__os, const Container &__cont) {
  bool __h = true;
  for (auto &&__e : __cont) __h ? __h = 0 : (__os << ' ', 0), __os << __e;
  return __os;
}

#ifdef __SIZEOF_INT128__

/**
 * @brief Stream insertion operator for __int128_t.
 *
 * @param __os Output Stream
 * @param __x 128-bit integer
 * @return Reference to __os.
 */
template <class Os> Os &operator<<(Os &__os, __int128_t __x) {
  if (__x < 0) __os << '-', __x = -__x;
  return __os << static_cast<__uint128_t>(__x);
}

/**
 * @brief Stream insertion operator for __uint128_t.
 *
 * @param __os Output Stream
 * @param __x 128-bit unsigned integer
 * @return Reference to __os.
 */
template <class Os> Os &operator<<(Os &__os, __uint128_t __x) {
  char __s[40], *__p = __s;
  if (!__x) *__p++ = '0';
  while (__x) *__p++ = '0' + __x % 10, __x /= 10;
  *__p = 0;
  for (char *__t = __s; __t < --__p; ++__t) *__t ^= *__p ^= *__t ^= *__p;
  return __os << __s;
}

#endif

}  // namespace workspace
