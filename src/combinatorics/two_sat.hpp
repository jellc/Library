#pragma once

/**
 * @file two_sat.hpp
 * @brief 2-SAT
 */

#include <cassert>
#include <cstdint>
#include <vector>

namespace workspace {

// Linear time 2-SAT solver.
class two_sat : std::vector<std::vector<uint_least32_t>> {
 public:
  using size_type = uint_least32_t;

 private:
  using container_type = std::vector<std::vector<size_type>>;

  size_type *__tag = nullptr, *__top = nullptr;

  size_type node_size() const noexcept { return container_type::size(); }

  size_type index(size_type __x) const noexcept {
    return __x < ~__x ? __x << 1 : ~__x << 1 | 1;
  }

  bool dfs(size_type __s, size_type __d) noexcept {
    if (~__tag[__s]) return __tag[__s];

    __tag[ *__top++ = __s] = --__d;
    bool __ret = true;

    for (size_type __t : container_type::operator[](__s)) {
      if (!dfs(__t, __d)) __ret = false;
      if (__tag[__s] < __tag[__t]) __tag[__s] = __tag[__t];
    }

    if (__tag[__s ^ 1] == 1) __ret = false;

    if (__tag[__s] == __d) do
        __tag[*--__top] = __ret;
      while (*__top != __s);

    return __ret;
  }

 public:
  two_sat() noexcept {}

  two_sat(size_type __n) noexcept : container_type(__n << 1) {}

  ~two_sat() {
    delete[] __tag;
    delete[] __top;
  }

  using container_type::empty;

  size_type size() const noexcept { return node_size() >> 1; }

  size_type add_variable() noexcept {
    container_type::emplace_back(), container_type::emplace_back();
    return size() - 1;
  }

  auto add_variables(size_type __n) noexcept {
    container_type::reserve(node_size() + __n);
    typename container_type::value_type __vs(__n);

    for (auto &__v : __vs) __v = add_variable();
    return __vs;
  }

  void add_clause(size_type __x) noexcept {
    __x = index(__x);
    assert(__x < node_size());

    container_type::operator[](__x ^ 1).emplace_back(__x);
  }

  void add_clause(size_type __x, size_type __y) noexcept {
    __x = index(__x), __y = index(__y);
    assert(__x < node_size()), assert(__y < node_size());

    container_type::operator[](__x ^ 1).emplace_back(__y),
        container_type::operator[](__y ^ 1).emplace_back(__x);
  }

  template <class _Iterator>
  size_type atmost_one(_Iterator __first, _Iterator __last) noexcept {
    container_type::reserve(node_size() + std::distance(__first, __last) + 1);
    auto __any = add_variable();

    for (add_clause(~__any); __first != __last; ++__first) {
      auto __next = add_variable();
      add_clause(~__any, ~*__first), add_clause(~__any, __next),
          add_clause(~*__first, __next), __any = __next;
    }

    return __any;
  }

  template <class _Iterator>
  size_type exactly_one(_Iterator __first, _Iterator __last) noexcept {
    auto __any = atmost_one(__first, __last);
    add_clause(__any);
    return __any;
  }

  bool run() noexcept {
    delete[] __tag;
    delete[] __top;
    __tag = new size_type[node_size()], __top = new size_type[node_size()];

    std::fill_n(__tag, node_size(), -1);
    for (size_type __s = 0; __s != node_size(); ++__s) dfs(__s, -1);

    for (size_type __i = 0; __i != node_size(); __i += 2)
      if (__tag[__i] == __tag[__i ^ 1]) return false;

    return true;
  }

  bool operator[](size_type __i) const noexcept {
    __i = index(__i);
    assert(__i < node_size());

    return __tag[__i];
  }
};

}  // namespace workspace
