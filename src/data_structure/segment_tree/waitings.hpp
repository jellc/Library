#pragma once

#include <cstdint>
#include <queue>

namespace workspace {

namespace internal {

struct waitings : std::queue<size_t> {
  waitings(size_t n) : in(n) {}

  bool push(size_t index) {
    assert(index < in.size());
    if (in[index]) return false;
    emplace(index);
    return (in[index] = true);
  }

  size_t pop() {
    assert(!empty());
    auto index = front();
    std::queue<size_t>::pop();
    in[index] = false;
    return index;
  }

 private:
  std::vector<int_least8_t> in;
};

}  // namespace internal

}  // namespace workspace
