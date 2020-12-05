#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ITP1_3_B"

#include "src/utils/sys/iteration.hpp"

namespace workspace {

void main() {
  int x;
  std::cin >> x;
  if (!x) exit();
  std::cout << "Case " << case_info.current << ": " << x << std::endl;
}

}  // namespace workspace

int main() {
  workspace::case_info.total = -1;
  return workspace::case_info.iterate();
}
