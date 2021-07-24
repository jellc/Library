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

  template <class _Op>
  void point(size_type __i,
             _Op &&__op) noexcept(noexcept(__op(std::declval<_Tp &>()))) {
    assert(__i < __len);
    for (__i += size_ext(); __i; __i >>= 1) __op(__data[__i]);
  }

  template <class _Op>
  void range(size_type __l, size_type __r,
             _Op &&__op) noexcept(noexcept(__op(std::declval<_Tp &>()))) {
    assert(__l <= __r), assert(__r <= __len);
    for (__l += size_ext(), __r += size_ext(); __l != __r;
         __l >>= 1, __r >>= 1) {
      if (__l & 1) __op(__data[__l++]);
      if (__r & 1) __op(__data[--__r]);
    }
  }

  template <class _Predicate>
  size_type left_partition(size_type __r, _Predicate &&__pred) noexcept(
      noexcept(__pred(std::declval<_Tp &>()))) {
    assert(__r <= __len);
    __r += size_ext();
    for (auto __l = size_ext(); __l != __r; __l >>= 1, __r >>= 1)
      if ((__l & 1) != (__r & 1))
        if (!__pred(__data[--__r])) return left_partition_subtree(__r, __pred);
    return 0;
  }

  template <class _Predicate>
  size_type right_partition(size_type __l, _Predicate &&__pred) noexcept(
      noexcept(__pred(std::declval<_Tp &>()))) {
    assert(__l <= __len);
    __l += size_ext();
    for (auto __r = __data.size(); __l != __r; ++__l >>= 1, __r >>= 1)
      if ((__l & 1) != (__r & 1))
        if (!__pred(__data[__l])) return right_partition_subtree(__l, __pred);
    return __len;
  }

 private:
  template <class _Predicate>
  size_type left_partition_subtree(size_type __i, _Predicate &&__pred) noexcept(
      noexcept(__pred(std::declval<_Tp &>()))) {
    while (__i < size_ext())
      if (!__pred(__data[(__i <<= 1) | 1])) __i |= 1;
    return ++__i -= size_ext();
  }

  template <class _Predicate>
  size_type right_partition_subtree(
      size_type __i,
      _Predicate &&__pred) noexcept(noexcept(__pred(std::declval<_Tp &>()))) {
    while (__i < size_ext())
      if (__pred(__data[__i <<= 1])) __i |= 1;
    return std::min(__i -= size_ext(), __len);
  }

  size_type size_ext() const noexcept { return __data.size() >> 1; }

  size_type __len;
  container_type __data;
};

}  // namespace workspace
