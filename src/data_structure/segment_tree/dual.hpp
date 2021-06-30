#pragma once

/**
 * @file dual.hpp
 * @brief Dual Segment Tree
 */

namespace workspace {

template <class _Tp> class dual_segment_tree {
 public:
  using container_type = std::vector<_Tp>;
  using size_type = typename container_type::size_type;

  dual_segment_tree() noexcept = default;

  dual_segment_tree(size_type __n) noexcept
      : __len(__n),
        __data(2 << (__n > 1 ? 64 - __builtin_clzll(__n - 1) : 0)) {}

  dual_segment_tree(size_type __n, const _Tp &__x) noexcept
      : __len(__n),
        __data(2 << (__n > 1 ? 64 - __builtin_clzll(__n - 1) : 0), __x) {}

  template <class _Op> void point(size_type __i, _Op &&__op) {
    assert(__i < __len);
    for (__i += __data.size() >> 1; __i; __i >>= 1) __op(__data[__i]);
  }

  template <class _Op> void range(size_type __l, size_type __r, _Op &&__op) {
    assert(__l <= __r), assert(__r <= __len);
    for (__l += __data.size() >> 1, __r += __data.size() >> 1; __l != __r;
         __l >>= 1, __r >>= 1) {
      if (__l & 1) __op(__data[__l++]);
      if (__r & 1) __op(__data[--__r]);
    }
  }

 private:
  size_type __len;
  container_type __data;
};

}  // namespace workspace
