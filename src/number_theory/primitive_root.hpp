/**
 * @file primitive_root.hpp
 * @brief Primitive Root
 * @date 2020-12-28
 */

#include <type_traits>

#include "src/utils/sfinae.hpp"

namespace workspace {

/**
 * @brief Compile time primitive root
 *
 * @tparam Mod
 */
template <auto Mod>
constexpr static
    typename std::enable_if<(is_integral_ext<decltype(Mod)>::value && Mod > 0),
                            decltype(Mod)>::type primitive_root = [] {
      using result_type = decltype(Mod);
      using int_type = typename multiplicable_uint<result_type>::type;

      if constexpr (Mod == 2) return static_cast<result_type>(1);

      auto __m = Mod - 1;
      while (!(__m & 1)) __m >>= 1;

      int_type __p[16] = {2}, *__t = __p + 1;

      for (int_type __i = 3; __i <= __m / __i; __i += 2) {
        if (__m % __i) continue;
        *__t++ = __i;
        while (!(__m % __i)) __m /= __i;
      }
      if (__m != 1) *__t++ = __m;

      int_type __r = 1;
      for (bool __yet = true; __yet; ++__r) {
        __yet = false;
        for (auto __i = __p; __i != __t; ++__i) {
          int_type __w = 1, __x = __r;
          for (auto e = (Mod - 1) / *__i; e; e >>= 1, (__x *= __x) %= Mod)
            if (e & 1) (__w *= __x) %= Mod;
          if (__w == 1) {
            __yet = true;
            break;
          }
        }
      }
      return static_cast<result_type>(--__r);
    }();

}  // namespace workspace
