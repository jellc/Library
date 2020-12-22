#pragma once

/**
 * @file cat.hpp
 * @brief Cat
 */

#include <iterator>

namespace workspace {

template <class C1, class C2>
constexpr C1 &&cat(C1 &&__c1, C2 const &__c2) noexcept {
  __c1.insert(__c1.end(), std::begin(__c2), std::end(__c2));
  return __c1;
}

}  // namespace workspace
