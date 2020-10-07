---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: template.cpp
    title: template.cpp
  - icon: ':warning:'
    path: utils.hpp
    title: utils.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/dont_burst_the_ballon.test.cpp
    title: test/aizu-online-judge/dont_burst_the_ballon.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/zalgorithm_2.test.cpp
    title: test/library-checker/zalgorithm_2.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"utils/binary_search.hpp\"\n#if __cplusplus >= 201703L\n\
    #include <cassert>\n#include <cmath>\n#include <vector>\nnamespace workspace {\n\
    // binary search on a discrete range.\ntemplate <class iter_type, class pred_type>\n\
    std::enable_if_t<\n    std::is_convertible_v<std::invoke_result_t<pred_type, iter_type>,\
    \ bool>,\n    iter_type>\nbinary_search(iter_type ok, iter_type ng, pred_type\
    \ pred) {\n  assert(ok != ng);\n  std::make_signed_t<decltype(ng - ok)> dist(ng\
    \ - ok);\n  while (1 < dist || dist < -1) {\n    iter_type mid(ok + dist / 2);\n\
    \    if (pred(mid))\n      ok = mid, dist -= dist / 2;\n    else\n      ng = mid,\
    \ dist /= 2;\n  }\n  return ok;\n}\n// parallel binary search on each discrete\
    \ range.\ntemplate <class iter_type, class pred_type>\nstd::enable_if_t<std::is_convertible_v<\n\
    \                     std::invoke_result_t<pred_type, std::vector<iter_type>>,\n\
    \                     std::vector<bool>>,\n                 std::vector<iter_type>>\n\
    binary_search(std::vector<std::pair<iter_type, iter_type>> ends,\n           \
    \   pred_type pred) {\n  std::vector<iter_type> mids(ends.size());\n  for (;;)\
    \ {\n    bool all_found = true;\n    for (size_t i{}; i != ends.size(); ++i) {\n\
    \      auto [ok, ng] = ends[i];\n      iter_type mid(ok + (ng - ok) / 2);\n  \
    \    if (mids[i] != mid) {\n        all_found = false;\n        mids[i] = mid;\n\
    \      }\n    }\n    if (all_found) break;\n    auto res = pred(mids);\n    for\
    \ (size_t i{}; i != ends.size(); ++i) {\n      (res[i] ? ends[i].first : ends[i].second)\
    \ = mids[i];\n    }\n  }\n  return mids;\n}\n// binary search on a real number\
    \ interval.\ntemplate <class real_type, class pred_type>\nstd::enable_if_t<\n\
    \    std::is_convertible_v<std::invoke_result_t<pred_type, real_type>, bool>,\n\
    \    real_type>\nbinary_search(real_type ok, real_type ng, const real_type eps,\
    \ pred_type pred) {\n  assert(ok != ng);\n  for (auto loops = 0; loops != std::numeric_limits<real_type>::digits\
    \ &&\n                       (ok + eps < ng || ng + eps < ok);\n       ++loops)\
    \ {\n    real_type mid{(ok + ng) / 2};\n    (pred(mid) ? ok : ng) = mid;\n  }\n\
    \  return ok;\n}\n// parallel binary search on each real interval.\ntemplate <class\
    \ real_type, class pred_type>\nstd::enable_if_t<std::is_convertible_v<\n     \
    \                std::invoke_result_t<pred_type, std::vector<real_type>>,\n  \
    \                   std::vector<bool>>,\n                 std::vector<real_type>>\n\
    binary_search(std::vector<std::pair<real_type, real_type>> ends,\n           \
    \   const real_type eps, pred_type pred) {\n  std::vector<real_type> mids(ends.size());\n\
    \  for (auto loops = 0; loops != std::numeric_limits<real_type>::digits;\n   \
    \    ++loops) {\n    bool all_found = true;\n    for (size_t i{}; i != ends.size();\
    \ ++i) {\n      auto [ok, ng] = ends[i];\n      if (ok + eps < ng || ng + eps\
    \ < ok) {\n        all_found = false;\n        mids[i] = (ok + ng) / 2;\n    \
    \  }\n    }\n    if (all_found) break;\n    auto res = pred(mids);\n    for (size_t\
    \ i{}; i != ends.size(); ++i) {\n      (res[i] ? ends[i].first : ends[i].second)\
    \ = mids[i];\n    }\n  }\n  return mids;\n}\n}  // namespace workspace\n#endif\n"
  code: "#pragma once\n#if __cplusplus >= 201703L\n#include <cassert>\n#include <cmath>\n\
    #include <vector>\nnamespace workspace {\n// binary search on a discrete range.\n\
    template <class iter_type, class pred_type>\nstd::enable_if_t<\n    std::is_convertible_v<std::invoke_result_t<pred_type,\
    \ iter_type>, bool>,\n    iter_type>\nbinary_search(iter_type ok, iter_type ng,\
    \ pred_type pred) {\n  assert(ok != ng);\n  std::make_signed_t<decltype(ng - ok)>\
    \ dist(ng - ok);\n  while (1 < dist || dist < -1) {\n    iter_type mid(ok + dist\
    \ / 2);\n    if (pred(mid))\n      ok = mid, dist -= dist / 2;\n    else\n   \
    \   ng = mid, dist /= 2;\n  }\n  return ok;\n}\n// parallel binary search on each\
    \ discrete range.\ntemplate <class iter_type, class pred_type>\nstd::enable_if_t<std::is_convertible_v<\n\
    \                     std::invoke_result_t<pred_type, std::vector<iter_type>>,\n\
    \                     std::vector<bool>>,\n                 std::vector<iter_type>>\n\
    binary_search(std::vector<std::pair<iter_type, iter_type>> ends,\n           \
    \   pred_type pred) {\n  std::vector<iter_type> mids(ends.size());\n  for (;;)\
    \ {\n    bool all_found = true;\n    for (size_t i{}; i != ends.size(); ++i) {\n\
    \      auto [ok, ng] = ends[i];\n      iter_type mid(ok + (ng - ok) / 2);\n  \
    \    if (mids[i] != mid) {\n        all_found = false;\n        mids[i] = mid;\n\
    \      }\n    }\n    if (all_found) break;\n    auto res = pred(mids);\n    for\
    \ (size_t i{}; i != ends.size(); ++i) {\n      (res[i] ? ends[i].first : ends[i].second)\
    \ = mids[i];\n    }\n  }\n  return mids;\n}\n// binary search on a real number\
    \ interval.\ntemplate <class real_type, class pred_type>\nstd::enable_if_t<\n\
    \    std::is_convertible_v<std::invoke_result_t<pred_type, real_type>, bool>,\n\
    \    real_type>\nbinary_search(real_type ok, real_type ng, const real_type eps,\
    \ pred_type pred) {\n  assert(ok != ng);\n  for (auto loops = 0; loops != std::numeric_limits<real_type>::digits\
    \ &&\n                       (ok + eps < ng || ng + eps < ok);\n       ++loops)\
    \ {\n    real_type mid{(ok + ng) / 2};\n    (pred(mid) ? ok : ng) = mid;\n  }\n\
    \  return ok;\n}\n// parallel binary search on each real interval.\ntemplate <class\
    \ real_type, class pred_type>\nstd::enable_if_t<std::is_convertible_v<\n     \
    \                std::invoke_result_t<pred_type, std::vector<real_type>>,\n  \
    \                   std::vector<bool>>,\n                 std::vector<real_type>>\n\
    binary_search(std::vector<std::pair<real_type, real_type>> ends,\n           \
    \   const real_type eps, pred_type pred) {\n  std::vector<real_type> mids(ends.size());\n\
    \  for (auto loops = 0; loops != std::numeric_limits<real_type>::digits;\n   \
    \    ++loops) {\n    bool all_found = true;\n    for (size_t i{}; i != ends.size();\
    \ ++i) {\n      auto [ok, ng] = ends[i];\n      if (ok + eps < ng || ng + eps\
    \ < ok) {\n        all_found = false;\n        mids[i] = (ok + ng) / 2;\n    \
    \  }\n    }\n    if (all_found) break;\n    auto res = pred(mids);\n    for (size_t\
    \ i{}; i != ends.size(); ++i) {\n      (res[i] ? ends[i].first : ends[i].second)\
    \ = mids[i];\n    }\n  }\n  return mids;\n}\n}  // namespace workspace\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: utils/binary_search.hpp
  requiredBy:
  - utils.hpp
  - template.cpp
  timestamp: '2020-10-06 00:55:27+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/zalgorithm_2.test.cpp
  - test/aizu-online-judge/dont_burst_the_ballon.test.cpp
documentation_of: utils/binary_search.hpp
layout: document
redirect_from:
- /library/utils/binary_search.hpp
- /library/utils/binary_search.hpp.html
title: utils/binary_search.hpp
---
