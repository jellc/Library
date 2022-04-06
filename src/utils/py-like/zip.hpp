#pragma once

/**
 * @file zip.hpp
 * @brief Zip
 */

#include <cstddef>
#include <tuple>
#include <vector>

#include "../iterator/category.hpp"
#include "../iterator/reverse.hpp"
#include "lib/cxx17"

namespace workspace {

template <class _Tuple> class zipped : protected _Tuple {
 public:
  zipped(const _Tuple &__x) : _Tuple(__x) {}

  template <std::size_t _Nm> constexpr decltype(auto) get() const &noexcept {
    return *std::get<_Nm>(*this);
  }

  template <std::size_t _Nm> constexpr decltype(auto) get() &&noexcept {
    auto __tmp = *std::get<_Nm>(*this);
    return __tmp;
  }
};

template <class... _Containers> class zip {
  std::tuple<_Containers...> __c;

  template <std::size_t _Nm = 0>
  constexpr decltype(auto) begin_cat() const noexcept {
    if _CXX17_CONSTEXPR (_Nm != sizeof...(_Containers)) {
      return std::tuple_cat(std::tuple(std::begin(std::get<_Nm>(__c))),
                            begin_cat<_Nm + 1>());
    } else
      return std::tuple<>();
  }

  template <std::size_t _Nm = 0>
  constexpr decltype(auto) end_cat() const noexcept {
    if _CXX17_CONSTEXPR (_Nm != sizeof...(_Containers)) {
      return std::tuple_cat(std::tuple(std::end(std::get<_Nm>(__c))),
                            end_cat<_Nm + 1>());
    } else
      return std::tuple<>();
  }

  using _Iterator_tuple =
      std::tuple<decltype(std::begin(std::declval<_Containers>()))...>;

 public:
  using size_type = std::size_t;

  class iterator : public zipped<_Iterator_tuple> {
    using _Base = zipped<_Iterator_tuple>;

   public:
    using difference_type = std::ptrdiff_t;
    using value_type = _Base;
    using pointer = void;
    using reference = value_type &;
    using iterator_category =
        typename common_iterator_category<_Iterator_tuple>::type;

   protected:
    template <std::size_t _Nm = 0>
    constexpr bool equal(const iterator &__x) const noexcept {
      if _CXX17_CONSTEXPR (_Nm != sizeof...(_Containers)) {
        return std::get<_Nm>(*this) == std::get<_Nm>(__x) ||
               equal<_Nm + 1>(__x);
      } else
        return false;
    }

    template <std::size_t _Nm = 0> constexpr void increment() noexcept {
      if _CXX17_CONSTEXPR (_Nm != sizeof...(_Containers))
        ++std::get<_Nm>(*this), increment<_Nm + 1>();
    }

    template <std::size_t _Nm = 0> constexpr void decrement() noexcept {
      if _CXX17_CONSTEXPR (_Nm != sizeof...(_Containers))
        --std::get<_Nm>(*this), decrement<_Nm + 1>();
    }

    template <std::size_t _Nm = 0>
    constexpr void advance(difference_type __d) noexcept {
      if _CXX17_CONSTEXPR (_Nm != sizeof...(_Containers))
        std::get<_Nm>(*this) += __d, advance<_Nm + 1>(__d);
    }

   public:
    iterator(const _Iterator_tuple &__x) : _Base(__x) {}

    constexpr bool operator==(const iterator &__x) const noexcept {
      return equal(__x);
    }
    constexpr bool operator!=(const iterator &__x) const noexcept {
      return !equal(__x);
    }

    constexpr iterator &operator++() noexcept {
      increment();
      return *this;
    }
    constexpr iterator operator++(int) noexcept {
      auto __tmp = *this;
      increment();
      return __tmp;
    }

    constexpr iterator &operator--() noexcept {
      decrement();
      return *this;
    }
    constexpr iterator operator--(int) noexcept {
      auto __tmp = *this;
      decrement();
      return __tmp;
    }

    constexpr bool operator<(const iterator &__x) const noexcept {
      return std::get<0>(*this) < std::get<0>(__x);
    }
    constexpr bool operator<=(const iterator &__x) const noexcept {
      return std::get<0>(*this) <= std::get<0>(__x);
    }
    constexpr bool operator>(const iterator &__x) const noexcept {
      return !operator<=(__x);
    }
    constexpr bool operator>=(const iterator &__x) const noexcept {
      return !operator>(__x);
    }

    constexpr iterator &operator+=(difference_type __d) noexcept {
      advance(__d);
      return *this;
    }
    constexpr iterator &operator-=(difference_type __d) noexcept {
      advance(-__d);
      return *this;
    }
    constexpr iterator operator+(difference_type __d) const noexcept {
      return iterator{*this} += __d;
    }
    constexpr iterator operator-(difference_type __d) const noexcept {
      return iterator{*this} -= __d;
    }

    constexpr difference_type operator-(const iterator &__x) const noexcept {
      return std::get<0>(*this) - std::get<0>(__x);
    }

    constexpr reference operator*() noexcept { return {*this}; }
  };

  using const_iterator = iterator;

  template <class... _Args>
  constexpr zip(_Args &&...__args) noexcept
      : __c(std::forward<_Args>(__args)...) {}

  template <class... _Args>
  constexpr zip(std::initializer_list<_Args>... __args) noexcept
      : __c(std::forward<_Args>(__args)...) {}

  constexpr iterator begin() const noexcept { return {begin_cat()}; }

  constexpr iterator end() const noexcept { return {end_cat()}; }

  constexpr reverse_iterator<iterator> rbegin() const noexcept {
    return reverse_iterator<iterator>{end()};
  }

  constexpr reverse_iterator<iterator> rend() const noexcept {
    return reverse_iterator<iterator>{begin()};
  }

#if __cplusplus >= 201703L
  constexpr size_type size() const noexcept {
    size_type __n = -1;
    std::apply(
        [&__n](auto &&__x) {
          if (__n < __x.size()) __n = __x.size();
        },
        __c);
    return __n;
  }
#endif
};

#if __cpp_deduction_guides >= 201606L

template <class... _Args> zip(_Args &&...) -> zip<_Args...>;

// For gcc version < 10
// https://gcc.gnu.org/bugzilla/show_bug.cgi?id=80438
template <class _Tp, class... _Args>
zip(_Tp &&, _Args &&...) -> zip<_Tp, _Args...>;

template <class... _Args>
zip(std::initializer_list<_Args>...) -> zip<std::initializer_list<_Args>...>;

#endif

}  // namespace workspace

namespace std {

template <size_t _Nm, class _Tuple>
struct tuple_element<_Nm, workspace::zipped<_Tuple>> {
  using type = remove_reference_t<
      typename iterator_traits<tuple_element_t<_Nm, _Tuple>>::reference>;
};

template <class _Tuple>
struct tuple_size<workspace::zipped<_Tuple>> : tuple_size<_Tuple> {};

}  // namespace std
