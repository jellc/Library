#pragma once
#include <cassert>
#include <cmath>
#include <vector>
namespace workspace {
// binary search on discrete range.
template <class iter_type, class pred_type>
std::enable_if_t<
    std::is_convertible_v<std::invoke_result_t<pred_type, iter_type>, bool>,
    iter_type>
binary_search(iter_type ok, iter_type ng, pred_type pred) {
  assert(ok != ng);
  __int128_t dist(ng - ok);
  while (std::abs(dist) > 1) {
    iter_type mid(ok + dist / 2);
    if (pred(mid))
      ok = mid, dist -= dist / 2;
    else
      ng = mid, dist /= 2;
  }
  return ok;
}
// parallel binary search on discrete range.
template <class iter_type, class pred_type>
std::enable_if_t<std::is_convertible_v<
                     std::invoke_result_t<pred_type, std::vector<iter_type>>,
                     std::vector<bool>>,
                 std::vector<iter_type>>
binary_search(std::vector<std::pair<iter_type, iter_type>> ends,
              pred_type pred) {
  std::vector<iter_type> mids(ends.size());
  for (;;) {
    bool solved = true;
    for (size_t i{}; i != ends.size(); ++i) {
      auto [ok, ng] = ends[i];
      iter_type mid(ok + (ng - ok) / 2);
      if (mids[i] != mid) {
        solved = false;
        mids[i] = mid;
      }
    }
    if (solved) break;
    auto res = pred(mids);
    for (size_t i{}; i != ends.size(); ++i) {
      (res[i] ? ends[i].first : ends[i].second) = mids[i];
    }
  }
  return mids;
}
// binary search on real numbers.
template <class real_type, class pred_type>
std::enable_if_t<
    std::is_convertible_v<std::invoke_result_t<pred_type, real_type>, bool>,
    real_type>
binary_search(real_type ok, real_type ng, const real_type eps, pred_type pred) {
  assert(ok != ng);
  while (eps < std::abs(ok - ng)) {
    real_type mid{(ok + ng) / 2};
    (pred(mid) ? ok : ng) = mid;
  }
  return ok;
}
// parallel binary search on real numbers.
template <class real_type, class pred_type>
std::enable_if_t<std::is_convertible_v<
                     std::invoke_result_t<pred_type, std::vector<real_type>>,
                     std::vector<bool>>,
                 std::vector<real_type>>
binary_search(std::vector<std::pair<real_type, real_type>> ends,
              const real_type eps, pred_type pred) {
  std::vector<real_type> mids(ends.size());
  for (;;) {
    bool solved = true;
    for (size_t i{}; i != ends.size(); ++i) {
      auto [ok, ng] = ends[i];
      real_type mid(ok + (ng - ok) / 2);
      if (mids[i] + eps < mid || mid + eps < mids[i]) {
        solved = false;
        mids[i] = mid;
      }
    }
    if (solved) break;
    auto res = pred(mids);
    for (size_t i{}; i != ends.size(); ++i) {
      (res[i] ? ends[i].first : ends[i].second) = mids[i];
    }
  }
  return mids;
}
}  // namespace workspace
