#define PROBLEM "https://judge.yosupo.jp/problem/associative_array"
#include "utils/hash.hpp"

using namespace workspace;

int main() {
  int q;
  scanf("%d", &q);
  unordered_map<long long, long long> a;
  gp_hash_table<long long, long long> b;
  cc_hash_table<long long, long long> c;

  while (q--) {
    int t;
    long long k, v;
    scanf("%d%lld", &t, &k);
    if (t) {
      printf("%lld\n", a[k]);
      assert(a[k] == b[k] && a[k] == c[k]);
    } else {
      scanf("%lld", &v);
      a[k] = b[k] = c[k] = v;
    }
  }
}
