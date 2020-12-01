#pragma once

/*
 * @file stream.hpp
 * @brief Input Stream
 */

#include <cxxabi.h>

#include <cassert>
#include <iostream>
#include <tuple>

#include "src/utils/sfinae.hpp"

namespace workspace {

/*
 * @class istream
 * @brief A wrapper class for std::istream.
 */
class istream : public std::istream {
  template <class Tp, typename = std::nullptr_t> struct helper {
    helper(std::istream &is, Tp &x) {
      if constexpr (has_begin<Tp>::value)
        for (auto &&e : x)
          helper<typename std::decay<decltype(e)>::type>(is, e);
      else
        static_assert(has_begin<Tp>::value, "istream unsupported type.");
    }
  };

  template <class Tp>
  struct helper<
      Tp,
      decltype(std::declval<std::decay<decltype(
                   std::declval<std::istream &>() >> std::declval<Tp &>())>>(),
               nullptr)> {
    helper(std::istream &is, Tp &x) { is >> x; }
  };

  template <class T1, class T2> struct helper<std::pair<T1, T2>> {
    helper(std::istream &is, std::pair<T1, T2> &x) {
      helper<T1>(is, x.first), helper<T2>(is, x.second);
    }
  };

  template <class... Tps> struct helper<std::tuple<Tps...>> {
    helper(std::istream &is, std::tuple<Tps...> &x) { iterate(is, x); }

   private:
    template <class Tp, size_t N = 0> void iterate(std::istream &is, Tp &x) {
      if constexpr (N == std::tuple_size<Tp>::value)
        return;
      else
        helper<typename std::tuple_element<N, Tp>::type>(is, std::get<N>(x)),
            iterate<Tp, N + 1>(is, x);
    }
  };

 public:
  template <typename Tp> istream &operator>>(Tp &x) {
    helper<Tp>(*this, x);
    if (std::istream::fail()) {
      static auto once = atexit([] {
        std::cerr << "\n\033[43m\033[30mwarning: failed to read \'"
                  << abi::__cxa_demangle(typeid(Tp).name(), 0, 0, 0)
                  << "\'.\033[0m\n\n";
      });
      assert(!once);
    }
    return *this;
  }
};

namespace internal {
auto *const cin_ptr = (istream *)&std::cin;
}
auto &cin = *internal::cin_ptr;

}  // namespace workspace
