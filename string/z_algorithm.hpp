/*
 * @file z_algorith.hpp
 * @brief Z-algorithm
 */

#pragma once
#include <string>
#include <vector>

namespace workspace {

/*
 * @class z_algorithm
 * @brief construct Z-array in linear time.
 * @tparam str_type the type of string
 */
template <class str_type = std::string> class z_algorithm {
  str_type key;
  std::vector<size_t> z;

  void make() {
    if (z.empty()) return;
    for (size_t i{1}, j{0}; i != size(); ++i) {
      if (z[i - j] + i < z[j] + j) {
        z[i] = z[i - j];
      } else {
        size_t k{z[j] + j > i ? z[j] + j - i : 0};
        while (k + i < size() && key[k] == key[k + i]) ++k;
        z[i] = k;
        j = i;
      }
    }
    z.front() = size();
  }

 public:
  z_algorithm(const str_type &key) : key(key), z(size()) { make(); }

  std::vector<size_t>::const_iterator begin() const { return z.begin(); }

  std::vector<size_t>::const_iterator end() const { return z.end(); }

  /*
   * @fn size
   * @return length of the string
   */
  size_t size() const { return key.size(); }

  /*
   * @fn operator[]
   * @param i index
   * @return LCP of (i)-th suffix and the whole string
   */
  size_t operator[](size_t i) const {
    assert(i < size());
    return z[i];
  }

  /*
   * @fn pattern_search
   * @param str
   * @return length of the string
   */
  std::vector<size_t> pattern_search(const str_type &str) const {
    str_type ccat(key);
    ccat.insert(end(ccat), begin(str), end(str));
    z_algorithm z(ccat);
    std::vector<size_t> res(z.begin() + size(), z.end());
    for (size_t &x : res)
      if (x > size()) x = size();
    return res;
  }
};

}  // namespace workspace
