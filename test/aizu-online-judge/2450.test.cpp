#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/2450"

#include <algorithm>
#include <iostream>

#include "src/data_structure/segment_tree/lazy.hpp"
#include "src/graph/undirected/tree/heavy_light_decomposition.hpp"
#include "src/utils/io/stream.hpp"

int main() {
  struct endo {
    bool assign = false;
    int value;
    endo() = default;
    endo(int v) : assign(true), value(v) {}
    endo operator*(endo rhs) {
      if (rhs.assign) return rhs;
      return *this;
    }
  };
  struct mono {
    int cnt = 0;
    int sum = 0;
    int left = 0;
    int right = 0;
    int max = 0;
    int best = -10000;
    mono operator+(mono rhs) {
      return {cnt + rhs.cnt,
              sum + rhs.sum,
              std::max(left, sum + rhs.left),
              std::max(right + rhs.sum, rhs.right),
              std::max({max, rhs.max, right + rhs.left}),
              std::max(best, rhs.best)};
    }
    mono operator*(endo rhs) {
      mono ret = *this;
      if (rhs.assign) {
        if (rhs.value < 0) {
          ret.sum = rhs.value * cnt;
          ret.left = ret.right = ret.max = 0;
        } else {
          ret.sum = ret.left = ret.right = ret.max = cnt * rhs.value;
        }
        ret.best = rhs.value;
      }
      return ret;
    }
  };

  int n, q;
  std::cin >> n >> q;
  std::vector<int> w(n);
  workspace::cin >> w;
  heavy_light_decomposition hld(n);
  for (auto e = 1; e != n; ++e) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    hld.add_edge(u, v);
  }
  hld.make(0);
  lazy_segment_tree<mono, endo> seg(n);
  for (auto v = 0; v != n; ++v) {
    auto &now = seg[hld.index(v)];
    now.cnt = 1;
    now = now * endo{w[v]};
  }
  while (q--) {
    int tp, a, b, c;
    std::cin >> tp >> a >> b >> c;
    --a, --b;
    auto [left, right] = hld.path_decomposition(a, b);
    if (tp == 1) {
      for (auto &&[l, r] : left) {
        seg.update(l, r, c);
      }
      for (auto &&[l, r] : right) {
        seg.update(l, r, c);
      }
    } else {
      mono lv;
      for (auto &&[l, r] : left) {
        lv = seg.fold(l, r) + lv;
      }
      mono rv;
      for (auto &&[l, r] : right) {
        rv = seg.fold(l, r) + rv;
      }
      std::swap(lv.left, lv.right);
      auto all = lv + rv;
      if (all.max)
        std::cout << all.max << '\n';
      else
        std::cout << all.best << '\n';
    }
  }
}
