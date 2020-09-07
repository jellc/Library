---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :heavy_check_mark: test/aizu-online-judge/dont_burst_the_ballon.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#8067ffd948dddbb51ecccf5f861740e7">test/aizu-online-judge</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/aizu-online-judge/dont_burst_the_ballon.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-08 01:03:56+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/problems/1342">https://onlinejudge.u-aizu.ac.jp/problems/1342</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/utils/binary_search.hpp.html">utils/binary_search.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/1342"
#include <algorithm>
#include <iostream>
#include <vector>

#include "utils/binary_search.hpp"

int main() {
  using namespace std;
  using namespace workspace;

  static const double eps = 1e-9;

  struct point {
    double x, y;
    double dist(point rhs) { return hypot(rhs.x - x, rhs.y - y); }
    point normalized() { return {x / hypot(x, y), y / hypot(x, y)}; }
    point scalized(double len) {
      return {x / hypot(x, y) * len, y / hypot(x, y) * len};
    }
    point operator+(point rhs) { return {x + rhs.x, y + rhs.y}; }
    bool operator==(point rhs) {
      return abs(x - rhs.x) < eps and abs(y - rhs.y) < eps;
    }
  };

  struct line {
    double a, b, c;
  };

  struct circle {
    point center;
    double radius;
    std::pair<point, point> intersect(circle rhs) {
      double r1, r2;
      auto [a, b] = center;
      auto [c, d] = rhs.center;
      r1 = radius;
      r2 = rhs.radius;
      if (a == c and b == d) return {center, center};
      line cln{2 * (c - a), 2 * (d - b),
               r1 * r1 - r2 * r2 + c * c + d * d - a * a - b * b};
      return intersect(cln);
    }
    std::pair<point, point> intersect(line ln) {
      point p1, p2;
      auto [a, b, c] = ln;
      double d = (c - a * center.x - b * center.y) / hypot(a, b);
      if (abs(d) > radius) return make_pair(p1, p2);
      point mid = center + point{a, b}.scalized(d);
      d = sqrt(radius * radius - d * d);
      p1 = mid + point{b, -a}.scalized(d);
      p2 = mid + point{b, -a}.scalized(-d);
      return make_pair(p1, p2);
    }
  };

  struct stick {
    point position;
    double height;
  };

  int n;
  double wall_hgt;
  const double sqre = 100;

  while (1) {
    cin >> n;
    cin >> wall_hgt;
    if (!n) break;
    vector<stick> stks(n);
    for (auto &[p, h] : stks) {
      double x, y;
      cin >> x >> y >> h;
      p = {x, y};
    }

    auto check_rad = [&](const double rad) -> bool {
      vector<circle> crcls;
      for (auto &[p, h] : stks) {
        circle cir;
        cir.center = p;
        cir.radius = rad > h ? sqrt(rad * rad - (rad - h) * (rad - h)) : rad;
        crcls.emplace_back(cir);
      }

      const double walld =
          rad > wall_hgt ? sqrt(rad * rad - (rad - wall_hgt) * (rad - wall_hgt))
                         : rad;

      auto check_external = [&](point p) -> bool {
        for (auto [c, r] : crcls) {
          if (p.dist(c) < r - eps) return false;
        }
        return min({p.x, sqre - p.x, p.y, sqre - p.y}) > walld - eps;
      };

      vector<point> cands;

      // corner
      for (auto x : {walld, sqre - walld}) {
        for (auto y : {walld, sqre - walld}) {
          cands.push_back({x, y});
        }
      }

      // between circls
      for (auto c1 : crcls) {
        for (auto c2 : crcls) {
          if (c1.center == c2.center) continue;
          auto [p1, p2] = c1.intersect(c2);
          cands.emplace_back(p1);
          cands.emplace_back(p2);
        }
      }

      // wall and circle
      for (auto c : crcls) {
        for (auto ln : vector<line>{{0, 1, walld},
                                    {1, 0, walld},
                                    {0, 1, sqre - walld},
                                    {1, 0, sqre - walld}}) {
          auto [p1, p2] = c.intersect(ln);
          cands.emplace_back(p1);
          cands.emplace_back(p2);
        }
      }

      for (auto p : cands) {
        if (check_external(p)) return true;
      }

      return false;
    };

    printf("%.5f\n", workspace::binary_search(0.0, 130.0, eps, check_rad));
  }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aizu-online-judge/dont_burst_the_ballon.test.cpp"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/1342"
#include <algorithm>
#include <iostream>
#include <vector>

#line 2 "utils/binary_search.hpp"
#include <cassert>
#include <cmath>
#line 5 "utils/binary_search.hpp"
namespace workspace {
// binary search on discrete range.
template <class iter_type, class pred_type>
std::enable_if_t<
    std::is_convertible_v<std::invoke_result_t<pred_type, iter_type>, bool>,
    iter_type>
binary_search(iter_type ok, iter_type ng, pred_type pred) {
  assert(ok != ng);
  __int128_t dist(ng - ok);
  while (dist > 1 || dist < -1) {
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
    bool all_found = true;
    for (size_t i{}; i != ends.size(); ++i) {
      auto [ok, ng] = ends[i];
      iter_type mid(ok + (ng - ok) / 2);
      if (mids[i] != mid) {
        all_found = false;
        mids[i] = mid;
      }
    }
    if (all_found) break;
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
  while (ok + eps < ng || ng + eps < ok) {
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
    bool all_found = true;
    for (size_t i{}; i != ends.size(); ++i) {
      auto [ok, ng] = ends[i];
      if (ok + eps < ng || ng + eps < ok) {
        all_found = false;
        mids[i] = (ok + ng) / 2;
      }
    }
    if (all_found) break;
    auto res = pred(mids);
    for (size_t i{}; i != ends.size(); ++i) {
      (res[i] ? ends[i].first : ends[i].second) = mids[i];
    }
  }
  return mids;
}
}  // namespace workspace
#line 7 "test/aizu-online-judge/dont_burst_the_ballon.test.cpp"

int main() {
  using namespace std;
  using namespace workspace;

  static const double eps = 1e-9;

  struct point {
    double x, y;
    double dist(point rhs) { return hypot(rhs.x - x, rhs.y - y); }
    point normalized() { return {x / hypot(x, y), y / hypot(x, y)}; }
    point scalized(double len) {
      return {x / hypot(x, y) * len, y / hypot(x, y) * len};
    }
    point operator+(point rhs) { return {x + rhs.x, y + rhs.y}; }
    bool operator==(point rhs) {
      return abs(x - rhs.x) < eps and abs(y - rhs.y) < eps;
    }
  };

  struct line {
    double a, b, c;
  };

  struct circle {
    point center;
    double radius;
    std::pair<point, point> intersect(circle rhs) {
      double r1, r2;
      auto [a, b] = center;
      auto [c, d] = rhs.center;
      r1 = radius;
      r2 = rhs.radius;
      if (a == c and b == d) return {center, center};
      line cln{2 * (c - a), 2 * (d - b),
               r1 * r1 - r2 * r2 + c * c + d * d - a * a - b * b};
      return intersect(cln);
    }
    std::pair<point, point> intersect(line ln) {
      point p1, p2;
      auto [a, b, c] = ln;
      double d = (c - a * center.x - b * center.y) / hypot(a, b);
      if (abs(d) > radius) return make_pair(p1, p2);
      point mid = center + point{a, b}.scalized(d);
      d = sqrt(radius * radius - d * d);
      p1 = mid + point{b, -a}.scalized(d);
      p2 = mid + point{b, -a}.scalized(-d);
      return make_pair(p1, p2);
    }
  };

  struct stick {
    point position;
    double height;
  };

  int n;
  double wall_hgt;
  const double sqre = 100;

  while (1) {
    cin >> n;
    cin >> wall_hgt;
    if (!n) break;
    vector<stick> stks(n);
    for (auto &[p, h] : stks) {
      double x, y;
      cin >> x >> y >> h;
      p = {x, y};
    }

    auto check_rad = [&](const double rad) -> bool {
      vector<circle> crcls;
      for (auto &[p, h] : stks) {
        circle cir;
        cir.center = p;
        cir.radius = rad > h ? sqrt(rad * rad - (rad - h) * (rad - h)) : rad;
        crcls.emplace_back(cir);
      }

      const double walld =
          rad > wall_hgt ? sqrt(rad * rad - (rad - wall_hgt) * (rad - wall_hgt))
                         : rad;

      auto check_external = [&](point p) -> bool {
        for (auto [c, r] : crcls) {
          if (p.dist(c) < r - eps) return false;
        }
        return min({p.x, sqre - p.x, p.y, sqre - p.y}) > walld - eps;
      };

      vector<point> cands;

      // corner
      for (auto x : {walld, sqre - walld}) {
        for (auto y : {walld, sqre - walld}) {
          cands.push_back({x, y});
        }
      }

      // between circls
      for (auto c1 : crcls) {
        for (auto c2 : crcls) {
          if (c1.center == c2.center) continue;
          auto [p1, p2] = c1.intersect(c2);
          cands.emplace_back(p1);
          cands.emplace_back(p2);
        }
      }

      // wall and circle
      for (auto c : crcls) {
        for (auto ln : vector<line>{{0, 1, walld},
                                    {1, 0, walld},
                                    {0, 1, sqre - walld},
                                    {1, 0, sqre - walld}}) {
          auto [p1, p2] = c.intersect(ln);
          cands.emplace_back(p1);
          cands.emplace_back(p2);
        }
      }

      for (auto p : cands) {
        if (check_external(p)) return true;
      }

      return false;
    };

    printf("%.5f\n", workspace::binary_search(0.0, 130.0, eps, check_rad));
  }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

