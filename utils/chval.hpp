/*
 * @file chval.hpp
 * @brief Change less/greater
 */

#pragma once
#include <functional>

namespace workspace {

/*
 * @fn chle
 * @brief substitute y for x if comp(y, x) is true
 * @param x reference
 * @param y const reference
 * @param comp compare function
 * @return whether or not x is updated
 */
template <class Tp, class Comp = std::less<Tp>>
bool chle(Tp &x, const Tp &y, Comp comp = Comp()) {
  return comp(y, x) ? x = y, true : false;
}

/*
 * @fn chge
 * @brief substitute y for x if comp(x, y) is true
 * @param x reference
 * @param y const reference
 * @param comp compare function
 * @return whether or not x is updated
 */
template <class Tp, class Comp = std::less<Tp>>
bool chge(Tp &x, const Tp &y, Comp comp = Comp()) {
  return comp(x, y) ? x = y, true : false;
}

}  // namespace workspace
