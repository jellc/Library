#include <iterator>

#include "lib/bit"

namespace workspace {

template <class A> A bitwise_fft(A f) {
  size_t len = std::__bit_floor(std::size(f));
  for (size_t p = 1; p < len; p <<= 1) {
    for (size_t i = 0; i < len; i += p << 1) {
      for (size_t j = 0; j < p; ++j) {
        auto t = f[i + j + p];
        f[i + j + p] = f[i + j] - t;
        f[i + j] += t;
      }
    }
  }
  return f;
}

template <class A> A bitwise_ifft(A f) {
  size_t len = std::__bit_floor(std::size(f));
  for (size_t p = len; p != 1; p >>= 1) {
    for (size_t i = 0; i < len; i += p) {
      for (size_t j = 0; j << 1 < p; ++j) {
        auto t = f[i + j + (p >> 1)];
        f[i + j + (p >> 1)] = (f[i + j] - t) / 2;
        (f[i + j] += t) /= 2;
      }
    }
  }
  return f;
}

template <class A> A bitxor_conv(A f, A g) {
  f = bitwise_fft(f);
  g = bitwise_fft(g);
  for (size_t i = 0; i != std::size(f); ++i) f[i] *= g[i];
  f = bitwise_ifft(f);
  return f;
}

}  // namespace workspace
