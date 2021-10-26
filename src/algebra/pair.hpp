#include <tuple>

/**
 * @file pair.hpp
 * @brief Pair Operations
 */

namespace workspace {

// Pairwise addition.
template <class _T1, class _T2, class _U1, class _U2>
auto operator+(const std::pair<_T1, _T2>& __p1,
               const std::pair<_U1, _U2>& __p2) noexcept {
  return std::make_pair(__p1.first + __p2.first, __p1.second + __p2.second);
}

// Pairwise addition assignment.
template <class _T1, class _T2, class _U1, class _U2>
auto& operator+=(std::pair<_T1, _T2>& __p1,
                 const std::pair<_U1, _U2>& __p2) noexcept {
  __p1.first += __p2.first, __p1.second += __p2.second;
  return __p1;
}

// Pairwise subtraction.
template <class _T1, class _T2, class _U1, class _U2>
auto operator-(const std::pair<_T1, _T2>& __p1,
               const std::pair<_U1, _U2>& __p2) noexcept {
  return std::make_pair(__p1.first - __p2.first, __p1.second - __p2.second);
}

// Pairwise subtraction assignment.
template <class _T1, class _T2, class _U1, class _U2>
auto& operator-=(std::pair<_T1, _T2>& __p1,
                 const std::pair<_U1, _U2>& __p2) noexcept {
  __p1.first -= __p2.first, __p1.second -= __p2.second;
  return __p1;
}

// Pairwise multiplication.
template <class _T1, class _T2, class _U1, class _U2>
auto operator*(const std::pair<_T1, _T2>& __p1,
               const std::pair<_U1, _U2>& __p2) noexcept {
  return std::make_pair(__p1.first * __p2.first, __p1.second * __p2.second);
}

// Pairwise multiplication assignment.
template <class _T1, class _T2, class _U1, class _U2>
auto& operator*=(std::pair<_T1, _T2>& __p1,
                 const std::pair<_U1, _U2>& __p2) noexcept {
  __p1.first *= __p2.first, __p1.second *= __p2.second;
  return __p1;
}

// Pairwise division.
template <class _T1, class _T2, class _U1, class _U2>
auto operator/(const std::pair<_T1, _T2>& __p1,
               const std::pair<_U1, _U2>& __p2) noexcept {
  return std::make_pair(__p1.first / __p2.first, __p1.second / __p2.second);
}

// Pairwise division assignment.
template <class _T1, class _T2, class _U1, class _U2>
auto& operator/=(std::pair<_T1, _T2>& __p1,
                 const std::pair<_U1, _U2>& __p2) noexcept {
  __p1.first /= __p2.first, __p1.second /= __p2.second;
  return __p1;
}

}  // namespace workspace
