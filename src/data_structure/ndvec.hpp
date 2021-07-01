#pragma once

/**
 * @file ndvec.hpp
 * @brief Nd-vector
 */

#include <vector>

namespace workspace {

template <class _Tp, size_t _Nm>
class ndvec : public std::vector<ndvec<_Tp, _Nm - 1>> {
 public:
  static constexpr auto dimension = _Nm;
  using container_type = std::vector<ndvec<_Tp, _Nm - 1>>;

  template <class _Dim, size_t _Size>
  ndvec(const _Dim (&__dim)[_Size], const _Tp& __x = {})
      : container_type(__dim[_Size - _Nm], {__dim, __x}) {}
};

template <class _Tp> class ndvec<_Tp, 1> : public std::vector<_Tp> {
 public:
  static constexpr auto dimension = 1;
  using container_type = std::vector<_Tp>;

  template <class _Dim, size_t _Size>
  ndvec(const _Dim (&__dim)[_Size], const _Tp& __x = {})
      : container_type(__dim[_Size - 1], __x) {}
};

#if __cplusplus >= 201703L

template <class _Tp, class _Dim, size_t _Nm>
ndvec(const _Dim (&)[_Nm], const _Tp&) -> ndvec<_Tp, _Nm>;

#endif

}  // namespace workspace
