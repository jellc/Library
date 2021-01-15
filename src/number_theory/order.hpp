/**
 * @file order.hpp
 * @brief Order
 * @date 2021-01-15
 *
 *
 */

#include <unordered_map>

#include "ext_gcd.hpp"

namespace workspace {

/**
 * @brief
 *
 * @param __x Integer
 * @param __mod Modulus
 * @return The order of @p __x modulo @p __mod.
 */
template <class Tp>
constexpr typename std::enable_if<(is_integral_ext<Tp>::value), Tp>::type order(
    Tp __x, const Tp __mod) noexcept {
  assert(__mod > 0);
  using int_type = typename multiplicable_int<Tp>::type;

  __x %= __mod;
  if (__x < 0) __x += __mod;
  std::unordered_map<Tp, Tp> __ls;
  int_type __p;
  Tp __i;
  for (__i = 1, __p = __x; __i * __i < __mod; ++__i, (__p *= __x) %= __mod)
    __ls.emplace(__p, __i);

  for (int_type __q{1}, __v{1}, __j{0};;
       __v = ext_gcd((__q *= __p) %= __mod, __mod).first, __j += __i,
       __ls[1] = 0)
    if (auto __f = __ls.find(__v < 0 ? __v += __mod : __v); __f != __ls.end())
      return __j + __f->second;
};

}  // namespace workspace
