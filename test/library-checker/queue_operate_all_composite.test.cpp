#define PROBLEM "https://judge.yosupo.jp/problem/queue_operate_all_composite"
#include <cstdio>

#include "data_structure/deque_aggregation.hpp"
#include "modulus/modint.hpp"

int main() {
  using mint = workspace::modint<998244353>;
  struct mono {
    mint a = 1, b;
    mono operator+(const mono& rhs) const {
      auto [c, d] = rhs;
      return {a * c, b * c + d};
    }
  };
  deque_aggregation<mono> deq;
  int q;
  scanf("%d", &q);
  while (q--) {
    int t;
    scanf("%d", &t);
    if (t == 0) {
      int a, b;
      scanf("%d%d", &a, &b);
      deq.push_back({a, b});
    } else if (t == 1) {
      deq.pop_front();
    } else {
      int x;
      scanf("%d", &x);
      auto [a, b] = deq.fold();
      printf("%d\n", a * x + b);
    }
  }
}
