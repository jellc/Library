---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: utils/binary_search.hpp
    title: utils/binary_search.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/1342
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/1342
  bundledCode: "#line 1 \"test/aizu-online-judge/dont_burst_the_ballon.test.cpp\"\n\
    #define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/1342\"\n#include <algorithm>\n\
    #include <iostream>\n#include <vector>\n\n#line 2 \"utils/binary_search.hpp\"\n\
    #if __cplusplus >= 201703L\n#include <cassert>\n#include <cmath>\n#line 6 \"utils/binary_search.hpp\"\
    \nnamespace workspace {\n// binary search on discrete range.\ntemplate <class\
    \ iter_type, class pred_type>\nstd::enable_if_t<\n    std::is_convertible_v<std::invoke_result_t<pred_type,\
    \ iter_type>, bool>,\n    iter_type>\nbinary_search(iter_type ok, iter_type ng,\
    \ pred_type pred) {\n  assert(ok != ng);\n  __int128_t dist(ng - ok);\n  while\
    \ (dist > 1 || dist < -1) {\n    iter_type mid(ok + dist / 2);\n    if (pred(mid))\n\
    \      ok = mid, dist -= dist / 2;\n    else\n      ng = mid, dist /= 2;\n  }\n\
    \  return ok;\n}\n// parallel binary search on discrete range.\ntemplate <class\
    \ iter_type, class pred_type>\nstd::enable_if_t<std::is_convertible_v<\n     \
    \                std::invoke_result_t<pred_type, std::vector<iter_type>>,\n  \
    \                   std::vector<bool>>,\n                 std::vector<iter_type>>\n\
    binary_search(std::vector<std::pair<iter_type, iter_type>> ends,\n           \
    \   pred_type pred) {\n  std::vector<iter_type> mids(ends.size());\n  for (;;)\
    \ {\n    bool all_found = true;\n    for (size_t i{}; i != ends.size(); ++i) {\n\
    \      auto [ok, ng] = ends[i];\n      iter_type mid(ok + (ng - ok) / 2);\n  \
    \    if (mids[i] != mid) {\n        all_found = false;\n        mids[i] = mid;\n\
    \      }\n    }\n    if (all_found) break;\n    auto res = pred(mids);\n    for\
    \ (size_t i{}; i != ends.size(); ++i) {\n      (res[i] ? ends[i].first : ends[i].second)\
    \ = mids[i];\n    }\n  }\n  return mids;\n}\n// binary search on real numbers.\n\
    template <class real_type, class pred_type>\nstd::enable_if_t<\n    std::is_convertible_v<std::invoke_result_t<pred_type,\
    \ real_type>, bool>,\n    real_type>\nbinary_search(real_type ok, real_type ng,\
    \ const real_type eps, pred_type pred) {\n  assert(ok != ng);\n  while (ok + eps\
    \ < ng || ng + eps < ok) {\n    real_type mid{(ok + ng) / 2};\n    (pred(mid)\
    \ ? ok : ng) = mid;\n  }\n  return ok;\n}\n// parallel binary search on real numbers.\n\
    template <class real_type, class pred_type>\nstd::enable_if_t<std::is_convertible_v<\n\
    \                     std::invoke_result_t<pred_type, std::vector<real_type>>,\n\
    \                     std::vector<bool>>,\n                 std::vector<real_type>>\n\
    binary_search(std::vector<std::pair<real_type, real_type>> ends,\n           \
    \   const real_type eps, pred_type pred) {\n  std::vector<real_type> mids(ends.size());\n\
    \  for (;;) {\n    bool all_found = true;\n    for (size_t i{}; i != ends.size();\
    \ ++i) {\n      auto [ok, ng] = ends[i];\n      if (ok + eps < ng || ng + eps\
    \ < ok) {\n        all_found = false;\n        mids[i] = (ok + ng) / 2;\n    \
    \  }\n    }\n    if (all_found) break;\n    auto res = pred(mids);\n    for (size_t\
    \ i{}; i != ends.size(); ++i) {\n      (res[i] ? ends[i].first : ends[i].second)\
    \ = mids[i];\n    }\n  }\n  return mids;\n}\n}  // namespace workspace\n#endif\n\
    #line 7 \"test/aizu-online-judge/dont_burst_the_ballon.test.cpp\"\n\nint main()\
    \ {\n  using namespace std;\n  using namespace workspace;\n\n  static const double\
    \ eps = 1e-9;\n\n  struct point {\n    double x, y;\n    double dist(point rhs)\
    \ { return hypot(rhs.x - x, rhs.y - y); }\n    point normalized() { return {x\
    \ / hypot(x, y), y / hypot(x, y)}; }\n    point scalized(double len) {\n     \
    \ return {x / hypot(x, y) * len, y / hypot(x, y) * len};\n    }\n    point operator+(point\
    \ rhs) { return {x + rhs.x, y + rhs.y}; }\n    bool operator==(point rhs) {\n\
    \      return abs(x - rhs.x) < eps and abs(y - rhs.y) < eps;\n    }\n  };\n\n\
    \  struct line {\n    double a, b, c;\n  };\n\n  struct circle {\n    point center;\n\
    \    double radius;\n    std::pair<point, point> intersect(circle rhs) {\n   \
    \   double r1, r2;\n      auto [a, b] = center;\n      auto [c, d] = rhs.center;\n\
    \      r1 = radius;\n      r2 = rhs.radius;\n      if (a == c and b == d) return\
    \ {center, center};\n      line cln{2 * (c - a), 2 * (d - b),\n              \
    \ r1 * r1 - r2 * r2 + c * c + d * d - a * a - b * b};\n      return intersect(cln);\n\
    \    }\n    std::pair<point, point> intersect(line ln) {\n      point p1, p2;\n\
    \      auto [a, b, c] = ln;\n      double d = (c - a * center.x - b * center.y)\
    \ / hypot(a, b);\n      if (abs(d) > radius) return make_pair(p1, p2);\n     \
    \ point mid = center + point{a, b}.scalized(d);\n      d = sqrt(radius * radius\
    \ - d * d);\n      p1 = mid + point{b, -a}.scalized(d);\n      p2 = mid + point{b,\
    \ -a}.scalized(-d);\n      return make_pair(p1, p2);\n    }\n  };\n\n  struct\
    \ stick {\n    point position;\n    double height;\n  };\n\n  int n;\n  double\
    \ wall_hgt;\n  const double sqre = 100;\n\n  while (1) {\n    cin >> n;\n    cin\
    \ >> wall_hgt;\n    if (!n) break;\n    vector<stick> stks(n);\n    for (auto\
    \ &[p, h] : stks) {\n      double x, y;\n      cin >> x >> y >> h;\n      p =\
    \ {x, y};\n    }\n\n    auto check_rad = [&](const double rad) -> bool {\n   \
    \   vector<circle> crcls;\n      for (auto &[p, h] : stks) {\n        circle cir;\n\
    \        cir.center = p;\n        cir.radius = rad > h ? sqrt(rad * rad - (rad\
    \ - h) * (rad - h)) : rad;\n        crcls.emplace_back(cir);\n      }\n\n    \
    \  const double walld =\n          rad > wall_hgt ? sqrt(rad * rad - (rad - wall_hgt)\
    \ * (rad - wall_hgt))\n                         : rad;\n\n      auto check_external\
    \ = [&](point p) -> bool {\n        for (auto [c, r] : crcls) {\n          if\
    \ (p.dist(c) < r - eps) return false;\n        }\n        return min({p.x, sqre\
    \ - p.x, p.y, sqre - p.y}) > walld - eps;\n      };\n\n      vector<point> cands;\n\
    \n      // corner\n      for (auto x : {walld, sqre - walld}) {\n        for (auto\
    \ y : {walld, sqre - walld}) {\n          cands.push_back({x, y});\n        }\n\
    \      }\n\n      // between circls\n      for (auto c1 : crcls) {\n        for\
    \ (auto c2 : crcls) {\n          if (c1.center == c2.center) continue;\n     \
    \     auto [p1, p2] = c1.intersect(c2);\n          cands.emplace_back(p1);\n \
    \         cands.emplace_back(p2);\n        }\n      }\n\n      // wall and circle\n\
    \      for (auto c : crcls) {\n        for (auto ln : vector<line>{{0, 1, walld},\n\
    \                                    {1, 0, walld},\n                        \
    \            {0, 1, sqre - walld},\n                                    {1, 0,\
    \ sqre - walld}}) {\n          auto [p1, p2] = c.intersect(ln);\n          cands.emplace_back(p1);\n\
    \          cands.emplace_back(p2);\n        }\n      }\n\n      for (auto p :\
    \ cands) {\n        if (check_external(p)) return true;\n      }\n\n      return\
    \ false;\n    };\n\n    printf(\"%.5f\\n\", workspace::binary_search(0.0, 130.0,\
    \ eps, check_rad));\n  }\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/1342\"\n#include\
    \ <algorithm>\n#include <iostream>\n#include <vector>\n\n#include \"utils/binary_search.hpp\"\
    \n\nint main() {\n  using namespace std;\n  using namespace workspace;\n\n  static\
    \ const double eps = 1e-9;\n\n  struct point {\n    double x, y;\n    double dist(point\
    \ rhs) { return hypot(rhs.x - x, rhs.y - y); }\n    point normalized() { return\
    \ {x / hypot(x, y), y / hypot(x, y)}; }\n    point scalized(double len) {\n  \
    \    return {x / hypot(x, y) * len, y / hypot(x, y) * len};\n    }\n    point\
    \ operator+(point rhs) { return {x + rhs.x, y + rhs.y}; }\n    bool operator==(point\
    \ rhs) {\n      return abs(x - rhs.x) < eps and abs(y - rhs.y) < eps;\n    }\n\
    \  };\n\n  struct line {\n    double a, b, c;\n  };\n\n  struct circle {\n   \
    \ point center;\n    double radius;\n    std::pair<point, point> intersect(circle\
    \ rhs) {\n      double r1, r2;\n      auto [a, b] = center;\n      auto [c, d]\
    \ = rhs.center;\n      r1 = radius;\n      r2 = rhs.radius;\n      if (a == c\
    \ and b == d) return {center, center};\n      line cln{2 * (c - a), 2 * (d - b),\n\
    \               r1 * r1 - r2 * r2 + c * c + d * d - a * a - b * b};\n      return\
    \ intersect(cln);\n    }\n    std::pair<point, point> intersect(line ln) {\n \
    \     point p1, p2;\n      auto [a, b, c] = ln;\n      double d = (c - a * center.x\
    \ - b * center.y) / hypot(a, b);\n      if (abs(d) > radius) return make_pair(p1,\
    \ p2);\n      point mid = center + point{a, b}.scalized(d);\n      d = sqrt(radius\
    \ * radius - d * d);\n      p1 = mid + point{b, -a}.scalized(d);\n      p2 = mid\
    \ + point{b, -a}.scalized(-d);\n      return make_pair(p1, p2);\n    }\n  };\n\
    \n  struct stick {\n    point position;\n    double height;\n  };\n\n  int n;\n\
    \  double wall_hgt;\n  const double sqre = 100;\n\n  while (1) {\n    cin >> n;\n\
    \    cin >> wall_hgt;\n    if (!n) break;\n    vector<stick> stks(n);\n    for\
    \ (auto &[p, h] : stks) {\n      double x, y;\n      cin >> x >> y >> h;\n   \
    \   p = {x, y};\n    }\n\n    auto check_rad = [&](const double rad) -> bool {\n\
    \      vector<circle> crcls;\n      for (auto &[p, h] : stks) {\n        circle\
    \ cir;\n        cir.center = p;\n        cir.radius = rad > h ? sqrt(rad * rad\
    \ - (rad - h) * (rad - h)) : rad;\n        crcls.emplace_back(cir);\n      }\n\
    \n      const double walld =\n          rad > wall_hgt ? sqrt(rad * rad - (rad\
    \ - wall_hgt) * (rad - wall_hgt))\n                         : rad;\n\n      auto\
    \ check_external = [&](point p) -> bool {\n        for (auto [c, r] : crcls) {\n\
    \          if (p.dist(c) < r - eps) return false;\n        }\n        return min({p.x,\
    \ sqre - p.x, p.y, sqre - p.y}) > walld - eps;\n      };\n\n      vector<point>\
    \ cands;\n\n      // corner\n      for (auto x : {walld, sqre - walld}) {\n  \
    \      for (auto y : {walld, sqre - walld}) {\n          cands.push_back({x, y});\n\
    \        }\n      }\n\n      // between circls\n      for (auto c1 : crcls) {\n\
    \        for (auto c2 : crcls) {\n          if (c1.center == c2.center) continue;\n\
    \          auto [p1, p2] = c1.intersect(c2);\n          cands.emplace_back(p1);\n\
    \          cands.emplace_back(p2);\n        }\n      }\n\n      // wall and circle\n\
    \      for (auto c : crcls) {\n        for (auto ln : vector<line>{{0, 1, walld},\n\
    \                                    {1, 0, walld},\n                        \
    \            {0, 1, sqre - walld},\n                                    {1, 0,\
    \ sqre - walld}}) {\n          auto [p1, p2] = c.intersect(ln);\n          cands.emplace_back(p1);\n\
    \          cands.emplace_back(p2);\n        }\n      }\n\n      for (auto p :\
    \ cands) {\n        if (check_external(p)) return true;\n      }\n\n      return\
    \ false;\n    };\n\n    printf(\"%.5f\\n\", workspace::binary_search(0.0, 130.0,\
    \ eps, check_rad));\n  }\n}\n"
  dependsOn:
  - utils/binary_search.hpp
  isVerificationFile: true
  path: test/aizu-online-judge/dont_burst_the_ballon.test.cpp
  requiredBy: []
  timestamp: '2020-09-25 13:36:45+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aizu-online-judge/dont_burst_the_ballon.test.cpp
layout: document
redirect_from:
- /verify/test/aizu-online-judge/dont_burst_the_ballon.test.cpp
- /verify/test/aizu-online-judge/dont_burst_the_ballon.test.cpp.html
title: test/aizu-online-judge/dont_burst_the_ballon.test.cpp
---
