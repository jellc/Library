#pragma once

/**
 * @file Mo.hpp
 * @brief Mo's Algorithm
 */

#include <cassert>
#include <cmath>
#include <functional>
#include <vector>

namespace workspace {

/**
 * @brief Mo's Alorithm. Process queries about contiguous subarrays.
 *
 * @tparam _Push_back
 * @tparam _Pop_back
 * @tparam _Push_front Use `_Push_back` as default
 * @tparam _Pop_front Use `_Pop_back` as default
 */
template <class _Push_back, class _Pop_back, class _Push_front = _Push_back,
          class _Pop_front = _Pop_back>
class Mo {
 public:
  using size_type = std::size_t;

  struct query {
    size_type index;
    size_type left, right;
  };

  using value_type = query;
  using reference = query&;
  using container_type = std::vector<query>;

 protected:
  _Push_front push_front;
  _Pop_front pop_front;
  _Push_back push_back;
  _Pop_back pop_back;

  container_type queries;

 public:
  /**
   * @brief Construct a new Mo object.
   *
   * @param push_back
   * @param pop_back
   */
  Mo(_Push_back push_back, _Pop_back pop_back) noexcept
      : Mo(push_back, pop_back, push_back, pop_back) {}

  /**
   * @brief Construct a new Mo object.
   *
   * @param push_front
   * @param pop_front
   * @param push_back
   * @param pop_back
   */
  Mo(_Push_front push_front, _Pop_front pop_front, _Push_back push_back,
     _Pop_back pop_back) noexcept
      : push_front(push_front),
        pop_front(pop_front),
        push_back(push_back),
        pop_back(pop_back) {}

  /**
   * @return Number of queries.
   */
  size_type size() const noexcept { return queries.size(); }

  /**
   * @brief Add a query for the interval [l, r).
   *
   * @param __l Left end, inclusive
   * @param __r Right end, exclusive
   * @return Index of the query.
   */
  reference insert(size_type __l, size_type __r) noexcept {
    assert(__l <= __r);
    queries.push_back({queries.size(), __l, __r});
    return queries.back();
  }

  /**
   * @brief Sort all queries.
   */
  void make() noexcept {
    assert(size());
    size_type __n = 0;
    for (const auto& __q : queries) __n = std::max(__n, __q.right);
    size_type __width = ceil(__n / sqrt(size()));
    std::sort(queries.begin(), queries.end(), [&](auto __x, auto __y) {
      if (__x.left / __width != __y.left / __width) return __x.left < __y.left;
      return __x.right < __y.right;
    });
  }

  class iterator : public container_type::iterator {
    using base = typename container_type::iterator;
    Mo* __mo;

    void fit(size_type __l1, size_type __r1, size_type __l2,
             size_type __r2) const noexcept {
      while (__l1 > __l2) __mo->push_front(--__l1);
      while (__r1 < __r2) __mo->push_back(__r1++);
      while (__l1 < __l2) __mo->pop_front(__l1++);
      while (__r1 > __r2) __mo->pop_back(--__r1);
    }

    void fit_from_empty(size_type __l, size_type __r) const noexcept {
      while (__l < __r) __mo->push_back(__l++);
    }

    void fit_to_empty(size_type __l, size_type __r) const noexcept {
      while (__l < __r) __mo->push_back(--__r);
    }

    bool at_end() const noexcept { return __mo->queries.end() == *this; }

   public:
    iterator() = default;

    iterator(Mo* __mo, base __i) noexcept : base(__i), __mo(__mo) {
      if (__i != __mo->queries.end()) fit_from_empty(__i->left, __i->right);
    }

    iterator& operator++() noexcept {
      auto __l = (*this)->left, __r = (*this)->right;
      base::operator++();
      if (at_end())
        fit_to_empty(__l, __r);
      else
        fit(__l, __r, (*this)->left, (*this)->right);
      return *this;
    }

    iterator& operator--() noexcept {
      if (at_end()) {
        base::operator--();
        fit_from_empty((*this)->left, (*this)->right);
      } else {
        size_type __l = (*this)->left, __r = (*this)->right;
        base::operator--();
        fit(__l, __r, (*this)->left, (*this)->right);
      }
      return *this;
    }

    iterator operator++(int) noexcept {
      auto __tmp = *this;
      operator++();
      return __tmp;
    }

    iterator operator--(int) noexcept {
      auto __tmp = *this;
      operator--();
      return __tmp;
    }
  };

  iterator begin() noexcept { return {this, queries.begin()}; }

  iterator end() noexcept { return {this, queries.end()}; }
};

}  // namespace workspace
