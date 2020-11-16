#pragma once

/*
 * @file Manacher.hpp
 * @brief Manacher's Algorithm
 */

#include <iostream>
#include <string>
#include <vector>

namespace workspace {

/*
 * @class Manacher
 * @brief Manacher's Algorithm.
 * @tparam str_type the type of string
 */
template <class str_type = std::string> class Manacher {
  const size_t len;
  std::vector<size_t> rad;

 public:
  Manacher(const str_type &str) : len(str.size()), rad(str.size()) {
    for (size_t i = 0, c = 0; i != len; ++i) {
      int l = c * 2 - i;
      if (l >= 0 && c + rad[c] > i + rad[l])
        rad[i] = rad[l];
      else {
        size_t j = c + rad[c] - i;
        while (i >= j && i + j != len && str[i - j] == str[i + j]) ++j;
        rad[c = i] = j;
      }
    }
  }

  std::vector<size_t>::const_iterator begin() const { return rad.begin(); }

  std::vector<size_t>::const_iterator end() const { return rad.end(); }

  /*
   * @fn size
   * @return length of the string
   */
  size_t size() const { return rad.size(); }

  /*
   * @fn operator[]
   * @param i index
   * @return the maximum radius L s.t. the substring (i - L, i + L) is
   * palindrome
   */
  size_t operator[](size_t i) const { return rad[i]; }

  /*
   * @fn operator<<
   * @brief print a Manacher object.
   * @param os ostream
   * @param manacher a Manacher object
   * @return os
   */
  friend std::ostream &operator<<(std::ostream &os, const Manacher &manacher) {
    bool is_front = true;
    for (size_t r : manacher.rad) {
      if (is_front)
        is_front = false;
      else
        os << " ";
      os << r;
    }
    return os;
  }
};

}  // namespace workspace
