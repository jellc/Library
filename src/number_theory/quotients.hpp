#pragma once

#include <vector>

#include "src/utils/round_div.hpp"

namespace workspace {

template <class _Tp> auto quotients(_Tp __n) {
  assert(__n >= 0);
  std::vector<std::pair<_Tp, _Tp>> res;
  for (_Tp q = __n + 1; q;) {
    _Tp k = __n / q + 1;
    q = __n / k;
    res.emplace_back(k, q);
  }
  return res;
}

}  // namespace workspace
