#pragma once

/**
 * @file ndvec.hpp
 * @brief Nd-vector
 */

#include <vector>

#include "lib/cxx17"

namespace workspace {

template <class _Tp, size_t _Dim>
class ndvec : public std::vector<ndvec<_Tp, _Dim - 1>> {
 public:
  static constexpr auto dimension = _Dim;
  using container_type = std::vector<ndvec<_Tp, _Dim - 1>>;
  using size_type = typename container_type::size_type;

  ndvec() = default;

  template <size_t _Nm>
  ndvec(const size_t (&__size)[_Nm], const _Tp& __x = {}) noexcept
      : container_type(__size[_Nm - _Dim], {__size, __x}) {}

  template <size_type _Nm = 0> size_type size() const noexcept {
    _CXX17_STATIC_ASSERT(_Nm < dimension);
    if _CXX17_CONSTEXPR (_Nm) {
      return container_type::operator[](0).template size<_Nm - 1>();
    }
    return container_type::size();
  }

  void fill(const _Tp& __x) noexcept {
    for (auto __i = container_type::begin(); __i != container_type::end();
         ++__i)
      __i->fill(__x);
  }
};

template <class _Tp> class ndvec<_Tp, 1> : public std::vector<_Tp> {
 public:
  static constexpr auto dimension = 1;
  using container_type = std::vector<_Tp>;
  using size_type = typename container_type::size_type;

  ndvec() = default;

  template <size_t _Nm>
  ndvec(const size_t (&__size)[_Nm], const _Tp& __x = {}) noexcept
      : container_type(__size[_Nm - 1], __x) {}

  template <size_type _Nm = 0> size_type size() const noexcept {
    _CXX17_STATIC_ASSERT(!_Nm);
    return container_type::size();
  }

  void fill(const _Tp& __x) noexcept {
    for (auto __i = container_type::begin(); __i != container_type::end();
         ++__i)
      *__i = __x;
  }
};

#if __cpp_deduction_guides >= 201606L

template <class _Tp, size_t _Dim>
ndvec(const size_t (&)[_Dim], const _Tp&) -> ndvec<_Tp, _Dim>;

#endif

}  // namespace workspace
