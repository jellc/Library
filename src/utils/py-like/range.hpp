#pragma once

/*
 * @file range.hpp
 * @brief Range
 */

#include <iterator>

namespace workspace {

template <class Index> class range {
  Index first, last;

 public:
  class iterator {
    Index iter;

   public:
    using difference_type = std::ptrdiff_t;
    using value_type = Index;
    using reference = typename std::add_const<Index>::type &;
    using pointer = iterator;
    using iterator_category = std::bidirectional_iterator_tag;

    constexpr iterator(Index iter = Index()) : iter(iter) {}

    constexpr bool operator==(iterator const &rhs) const {
      return iter == rhs.iter;
    }
    constexpr bool operator!=(iterator const &rhs) const {
      return iter != rhs.iter;
    }

    constexpr iterator &operator++() {
      ++iter;
      return *this;
    }
    constexpr iterator &operator--() {
      --iter;
      return *this;
    }

    constexpr reference operator*() const { return iter; }
  };

  constexpr range(Index first, Index last) : first(first), last(last) {}
  constexpr range(Index last) : first(), last(last) {}

  constexpr iterator begin() const { return iterator{first}; }
  constexpr iterator end() const { return iterator{last}; }

  constexpr std::reverse_iterator<iterator> rbegin() const {
    return std::make_reverse_iterator(end());
  }
  constexpr std::reverse_iterator<iterator> rend() const {
    return std::make_reverse_iterator(begin());
  }
};

}  // namespace workspace
