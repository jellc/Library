#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/1342"

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

#include "src/utils/binary_search.hpp"

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
