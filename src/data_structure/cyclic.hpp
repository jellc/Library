#pragma once

/**
 * @file cyclic.hpp
 * @brief Cyclic Array
 */

#include <vector>

#include "src/utils/sfinae.hpp"

namespace workspace {

/**
 * @brief Cyclic array.
 */
template <class _Tp> class cyclic : public std::vector<_Tp> {
 public:
  using container_type = std::vector<_Tp>;

  using typename container_type::difference_type;

  using container_type::vector;

  cyclic(std::initializer_list<_Tp> __x) noexcept : container_type(__x) {}

  template <class _Index> decltype(auto) operator[](_Index __i) noexcept {
    return container_type::operator[](locate(__i));
  }
  template <class _Index> decltype(auto) operator[](_Index __i) const noexcept {
    return container_type::operator[](locate(__i));
  }

  template <class _Index> decltype(auto) at(_Index __i) {
    return container_type::at(locate(__i));
  }
  template <class _Index> decltype(auto) at(_Index __i) const {
    return container_type::at(locate(__i));
  }

 private:
  template <class _Index>
  std::enable_if_t<is_integral_ext<_Index>::value,
                   typename container_type::size_type>
  locate(_Index __i) const noexcept {
    return (__i %= (_Index)container_type::size()) < 0
               ? __i + container_type::size()
               : __i;
  }
};

template <class _Tp>
cyclic(typename cyclic<_Tp>::size_type, const _Tp &) -> cyclic<_Tp>;

template <class _InputIterator>
cyclic(_InputIterator, _InputIterator)
    -> cyclic<typename std::iterator_traits<_InputIterator>::value_type>;

}  // namespace workspace
