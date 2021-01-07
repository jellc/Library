#include "lib/bit"
#include "zeta.hpp"

namespace workspace {

template <class A> A bitor_conv(A f, A g) {
  f = fast_zeta(f);
  g = fast_zeta(g);
  for (size_t i = 0; i != __bit_floor(std::size(f)); ++i) f[i] *= g[i];
  f = fast_mobius(f);
  return f;
}

}  // namespace workspace
