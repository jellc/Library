---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/opt/binary_search.hpp
    title: Binary Search
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Exponential Search
    links: []
  bundledCode: "#line 2 \"src/opt/exponential_search.hpp\"\n\n/*\n * @file exponential_search.hpp\n\
    \ * @brief Exponential Search\n */\n\n#line 2 \"src/opt/binary_search.hpp\"\n\n\
    /*\n * @file binary_search.hpp\n * @brief Binary Search\n */\n\n#include <cassert>\n\
    #include <limits>\n#include <tuple>\n#include <vector>\n\nnamespace workspace\
    \ {\n\n/*\n * @fn binary_search\n * @brief binary search on a discrete range.\n\
    \ * @param ok pred(ok) is true\n * @param ng pred(ng) is false\n * @param pred\
    \ the predicate\n * @return the closest point to (ng) where pred is true\n */\n\
    template <class Iter, class Pred>\ntypename std::enable_if<\n    std::is_convertible<decltype(std::declval<Pred>()(std::declval<Iter>())),\n\
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
    \    }\n  }\n  return mids;\n}\n\n}  // namespace workspace\n#line 9 \"src/opt/exponential_search.hpp\"\
    \n\nnamespace workspace {\n\n/*\n * @fn exponential_search\n * @brief Exponential\
    \ search on a discrete range.\n * @param range Range of search, exclusive\n *\
    \ @param pred Predicate\n * @return Minimum non-negative integer where pred is\
    \ false.\n */\ntemplate <class Index, class Pred>\ntypename std::enable_if<\n\
    \    std::is_convertible<decltype(std::declval<Pred>()(std::declval<Index>())),\n\
    \                        bool>::value,\n    Index>::type\nexponential_search(Index\
    \ range, Pred pred) {\n  Index step(1);\n  while (step < range && pred(step))\
    \ step <<= 1;\n  if (range < step) step = range;\n  return binary_search(Index(0),\
    \ step, pred);\n}\n\n/*\n * @fn exponential_search\n * @brief Exponential search\
    \ on the real number line.\n * @param range Range of search\n * @param eps Error\
    \ tolerance\n * @param pred Predicate\n * @return Boundary point.\n */\ntemplate\
    \ <class Real, class Pred>\ntypename std::enable_if<\n    std::is_convertible<decltype(std::declval<Pred>()(std::declval<Real>())),\n\
    \                        bool>::value,\n    Real>::type\nexponential_search(Real\
    \ range, Real const &eps, Pred pred) {\n  Real step(1);\n  while (step < range\
    \ && pred(step)) step += step;\n  if (range < step) step = range;\n  return binary_search(Real(0),\
    \ step, eps, pred);\n}\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/*\n * @file exponential_search.hpp\n * @brief Exponential\
    \ Search\n */\n\n#include \"binary_search.hpp\"\n\nnamespace workspace {\n\n/*\n\
    \ * @fn exponential_search\n * @brief Exponential search on a discrete range.\n\
    \ * @param range Range of search, exclusive\n * @param pred Predicate\n * @return\
    \ Minimum non-negative integer where pred is false.\n */\ntemplate <class Index,\
    \ class Pred>\ntypename std::enable_if<\n    std::is_convertible<decltype(std::declval<Pred>()(std::declval<Index>())),\n\
    \                        bool>::value,\n    Index>::type\nexponential_search(Index\
    \ range, Pred pred) {\n  Index step(1);\n  while (step < range && pred(step))\
    \ step <<= 1;\n  if (range < step) step = range;\n  return binary_search(Index(0),\
    \ step, pred);\n}\n\n/*\n * @fn exponential_search\n * @brief Exponential search\
    \ on the real number line.\n * @param range Range of search\n * @param eps Error\
    \ tolerance\n * @param pred Predicate\n * @return Boundary point.\n */\ntemplate\
    \ <class Real, class Pred>\ntypename std::enable_if<\n    std::is_convertible<decltype(std::declval<Pred>()(std::declval<Real>())),\n\
    \                        bool>::value,\n    Real>::type\nexponential_search(Real\
    \ range, Real const &eps, Pred pred) {\n  Real step(1);\n  while (step < range\
    \ && pred(step)) step += step;\n  if (range < step) step = range;\n  return binary_search(Real(0),\
    \ step, eps, pred);\n}\n\n}  // namespace workspace\n"
  dependsOn:
  - src/opt/binary_search.hpp
  isVerificationFile: false
  path: src/opt/exponential_search.hpp
  requiredBy: []
  timestamp: '2020-12-08 15:39:54+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/opt/exponential_search.hpp
layout: document
redirect_from:
- /library/src/opt/exponential_search.hpp
- /library/src/opt/exponential_search.hpp.html
title: Exponential Search
---
