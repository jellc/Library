---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: src/opt/exponential_search.hpp
    title: Exponential Search
  - icon: ':heavy_check_mark:'
    path: src/string/rolling_hash.hpp
    title: Rolling Hash
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/0323.test.cpp
    title: test/aizu-online-judge/0323.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/1342.test.cpp
    title: test/aizu-online-judge/1342.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/ALDS1_14_C.test.cpp
    title: test/aizu-online-judge/ALDS1_14_C.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/zalgorithm_2.test.cpp
    title: test/library-checker/zalgorithm_2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Binary Search
    links: []
  bundledCode: "#line 2 \"src/opt/binary_search.hpp\"\n\n/*\n * @file binary_search.hpp\n\
    \ * @brief Binary Search\n */\n\n#include <cassert>\n#include <limits>\n#include\
    \ <tuple>\n#include <vector>\n\nnamespace workspace {\n\n/*\n * @fn binary_search\n\
    \ * @brief binary search on a discrete range.\n * @param ok pred(ok) is true\n\
    \ * @param ng pred(ng) is false\n * @param pred the predicate\n * @return the\
    \ closest point to (ng) where pred is true\n */\ntemplate <class Iter, class Pred>\n\
    typename std::enable_if<\n    std::is_convertible<decltype(std::declval<Pred>()(std::declval<Iter>())),\n\
    \                        bool>::value,\n    Iter>::type\nbinary_search(Iter ok,\
    \ Iter ng, Pred pred) {\n  assert(ok != ng);\n  typename std::make_signed<decltype(ng\
    \ - ok)>::type dist(ng - ok);\n  while (1 < dist || dist < -1) {\n    const Iter\
    \ mid(ok + dist / 2);\n    if (pred(mid))\n      ok = mid, dist -= dist / 2;\n\
    \    else\n      ng = mid, dist /= 2;\n  }\n  return ok;\n}\n\n/*\n * @fn binary_search\n\
    \ * @brief binary search on the real number line.\n * @param ok pred(ok) is true\n\
    \ * @param ng pred(ng) is false\n * @param eps the error tolerance\n * @param\
    \ pred the predicate\n * @return the boundary point\n */\ntemplate <class Real,\
    \ class Pred>\ntypename std::enable_if<\n    std::is_convertible<decltype(std::declval<Pred>()(std::declval<Real>())),\n\
    \                        bool>::value,\n    Real>::type\nbinary_search(Real ok,\
    \ Real ng, const Real eps, Pred pred) {\n  assert(ok != ng);\n  for (auto loops\
    \ = 0; loops != std::numeric_limits<Real>::digits &&\n                       (ok\
    \ + eps < ng || ng + eps < ok);\n       ++loops) {\n    const Real mid{(ok + ng)\
    \ / 2};\n    (pred(mid) ? ok : ng) = mid;\n  }\n  return ok;\n}\n\n/*\n * @fn\
    \ parallel_binary_search\n * @brief parallel binary search on discrete ranges.\n\
    \ * @param ends a vector of pairs; pred(first) is true, pred(second) is false\n\
    \ * @param pred the predicate\n * @return the closest points to (second) where\
    \ pred is true\n */\ntemplate <class Array,\n          class Iter = typename std::decay<\n\
    \              decltype(std::get<0>(std::declval<Array>()[0]))>::type,\n     \
    \     class Pred>\ntypename std::enable_if<\n    std::is_convertible<\n      \
    \  decltype(std::declval<Pred>()(std::declval<std::vector<Iter>>())[0]),\n   \
    \     bool>::value,\n    std::vector<Iter>>::type\nparallel_binary_search(Array\
    \ ends, Pred pred) {\n  std::vector<Iter> mids(std::size(ends));\n  for (;;) {\n\
    \    bool all_found = true;\n    for (size_t i{}; i != std::size(ends); ++i) {\n\
    \      const Iter &ok = std::get<0>(ends[i]);\n      const Iter &ng = std::get<1>(ends[i]);\n\
    \      const Iter mid(\n          ok + typename std::make_signed<decltype(ng -\
    \ ok)>::type(ng - ok) / 2);\n      if (mids[i] != mid) {\n        all_found =\
    \ false;\n        mids[i] = mid;\n      }\n    }\n    if (all_found) break;\n\
    \    const auto res = pred(mids);\n    for (size_t i{}; i != std::size(ends);\
    \ ++i) {\n      (res[i] ? std::get<0>(ends[i]) : std::get<1>(ends[i])) = mids[i];\n\
    \    }\n  }\n  return mids;\n}\n\n/*\n * @fn parallel_binary_search\n * @brief\
    \ parallel binary search on the real number line.\n * @param ends a vector of\
    \ pairs; pred(first) is true, pred(second) is false\n * @param eps the error tolerance\n\
    \ * @param pred the predicate\n * @return the boundary points\n */\ntemplate <class\
    \ Array,\n          class Real = typename std::decay<\n              decltype(std::get<0>(std::declval<Array>()[0]))>::type,\n\
    \          class Pred>\ntypename std::enable_if<\n    std::is_convertible<\n \
    \       decltype(std::declval<Pred>()(std::declval<std::vector<Real>>())[0]),\n\
    \        bool>::value,\n    std::vector<Real>>::type\nparallel_binary_search(Array\
    \ ends, const Real eps, Pred pred) {\n  std::vector<Real> mids(std::size(ends));\n\
    \  for (auto loops = 0; loops != std::numeric_limits<Real>::digits; ++loops) {\n\
    \    bool all_found = true;\n    for (size_t i{}; i != std::size(ends); ++i) {\n\
    \      const Real ok = std::get<0>(ends[i]);\n      const Real ng = std::get<1>(ends[i]);\n\
    \      if (ok + eps < ng || ng + eps < ok) {\n        all_found = false;\n   \
    \     mids[i] = (ok + ng) / 2;\n      }\n    }\n    if (all_found) break;\n  \
    \  const auto res = pred(mids);\n    for (size_t i{}; i != std::size(ends); ++i)\
    \ {\n      (res[i] ? std::get<0>(ends[i]) : std::get<1>(ends[i])) = mids[i];\n\
    \    }\n  }\n  return mids;\n}\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/*\n * @file binary_search.hpp\n * @brief Binary Search\n\
    \ */\n\n#include <cassert>\n#include <limits>\n#include <tuple>\n#include <vector>\n\
    \nnamespace workspace {\n\n/*\n * @fn binary_search\n * @brief binary search on\
    \ a discrete range.\n * @param ok pred(ok) is true\n * @param ng pred(ng) is false\n\
    \ * @param pred the predicate\n * @return the closest point to (ng) where pred\
    \ is true\n */\ntemplate <class Iter, class Pred>\ntypename std::enable_if<\n\
    \    std::is_convertible<decltype(std::declval<Pred>()(std::declval<Iter>())),\n\
    \                        bool>::value,\n    Iter>::type\nbinary_search(Iter ok,\
    \ Iter ng, Pred pred) {\n  assert(ok != ng);\n  typename std::make_signed<decltype(ng\
    \ - ok)>::type dist(ng - ok);\n  while (1 < dist || dist < -1) {\n    const Iter\
    \ mid(ok + dist / 2);\n    if (pred(mid))\n      ok = mid, dist -= dist / 2;\n\
    \    else\n      ng = mid, dist /= 2;\n  }\n  return ok;\n}\n\n/*\n * @fn binary_search\n\
    \ * @brief binary search on the real number line.\n * @param ok pred(ok) is true\n\
    \ * @param ng pred(ng) is false\n * @param eps the error tolerance\n * @param\
    \ pred the predicate\n * @return the boundary point\n */\ntemplate <class Real,\
    \ class Pred>\ntypename std::enable_if<\n    std::is_convertible<decltype(std::declval<Pred>()(std::declval<Real>())),\n\
    \                        bool>::value,\n    Real>::type\nbinary_search(Real ok,\
    \ Real ng, const Real eps, Pred pred) {\n  assert(ok != ng);\n  for (auto loops\
    \ = 0; loops != std::numeric_limits<Real>::digits &&\n                       (ok\
    \ + eps < ng || ng + eps < ok);\n       ++loops) {\n    const Real mid{(ok + ng)\
    \ / 2};\n    (pred(mid) ? ok : ng) = mid;\n  }\n  return ok;\n}\n\n/*\n * @fn\
    \ parallel_binary_search\n * @brief parallel binary search on discrete ranges.\n\
    \ * @param ends a vector of pairs; pred(first) is true, pred(second) is false\n\
    \ * @param pred the predicate\n * @return the closest points to (second) where\
    \ pred is true\n */\ntemplate <class Array,\n          class Iter = typename std::decay<\n\
    \              decltype(std::get<0>(std::declval<Array>()[0]))>::type,\n     \
    \     class Pred>\ntypename std::enable_if<\n    std::is_convertible<\n      \
    \  decltype(std::declval<Pred>()(std::declval<std::vector<Iter>>())[0]),\n   \
    \     bool>::value,\n    std::vector<Iter>>::type\nparallel_binary_search(Array\
    \ ends, Pred pred) {\n  std::vector<Iter> mids(std::size(ends));\n  for (;;) {\n\
    \    bool all_found = true;\n    for (size_t i{}; i != std::size(ends); ++i) {\n\
    \      const Iter &ok = std::get<0>(ends[i]);\n      const Iter &ng = std::get<1>(ends[i]);\n\
    \      const Iter mid(\n          ok + typename std::make_signed<decltype(ng -\
    \ ok)>::type(ng - ok) / 2);\n      if (mids[i] != mid) {\n        all_found =\
    \ false;\n        mids[i] = mid;\n      }\n    }\n    if (all_found) break;\n\
    \    const auto res = pred(mids);\n    for (size_t i{}; i != std::size(ends);\
    \ ++i) {\n      (res[i] ? std::get<0>(ends[i]) : std::get<1>(ends[i])) = mids[i];\n\
    \    }\n  }\n  return mids;\n}\n\n/*\n * @fn parallel_binary_search\n * @brief\
    \ parallel binary search on the real number line.\n * @param ends a vector of\
    \ pairs; pred(first) is true, pred(second) is false\n * @param eps the error tolerance\n\
    \ * @param pred the predicate\n * @return the boundary points\n */\ntemplate <class\
    \ Array,\n          class Real = typename std::decay<\n              decltype(std::get<0>(std::declval<Array>()[0]))>::type,\n\
    \          class Pred>\ntypename std::enable_if<\n    std::is_convertible<\n \
    \       decltype(std::declval<Pred>()(std::declval<std::vector<Real>>())[0]),\n\
    \        bool>::value,\n    std::vector<Real>>::type\nparallel_binary_search(Array\
    \ ends, const Real eps, Pred pred) {\n  std::vector<Real> mids(std::size(ends));\n\
    \  for (auto loops = 0; loops != std::numeric_limits<Real>::digits; ++loops) {\n\
    \    bool all_found = true;\n    for (size_t i{}; i != std::size(ends); ++i) {\n\
    \      const Real ok = std::get<0>(ends[i]);\n      const Real ng = std::get<1>(ends[i]);\n\
    \      if (ok + eps < ng || ng + eps < ok) {\n        all_found = false;\n   \
    \     mids[i] = (ok + ng) / 2;\n      }\n    }\n    if (all_found) break;\n  \
    \  const auto res = pred(mids);\n    for (size_t i{}; i != std::size(ends); ++i)\
    \ {\n      (res[i] ? std::get<0>(ends[i]) : std::get<1>(ends[i])) = mids[i];\n\
    \    }\n  }\n  return mids;\n}\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/opt/binary_search.hpp
  requiredBy:
  - src/opt/exponential_search.hpp
  - src/string/rolling_hash.hpp
  timestamp: '2020-12-08 15:39:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/zalgorithm_2.test.cpp
  - test/aizu-online-judge/0323.test.cpp
  - test/aizu-online-judge/1342.test.cpp
  - test/aizu-online-judge/ALDS1_14_C.test.cpp
documentation_of: src/opt/binary_search.hpp
layout: document
redirect_from:
- /library/src/opt/binary_search.hpp
- /library/src/opt/binary_search.hpp.html
title: Binary Search
---
