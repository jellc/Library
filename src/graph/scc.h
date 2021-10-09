#pragma once

/**
 * @file scc.h
 * @brief Strongly Connected Component
 */

#include "digraph.h"

namespace workspace {

/**
 * @brief Strongly connected component algorithm.
 * @return List of all components in topological order.
 */
template <class _Attr, class _List>
auto digraph<_Attr, _List>::scc() const noexcept {
  std::vector<std::vector<node_type>> __scc;
  __scc.reserve(size());

  std::vector<node_type> __tmp;
  __tmp.reserve(size());

  std::vector<size_type> __low(size());
  std::vector<weighted_edge<size_type>> __stack;

  for (node_type __r = 0; __r != size(); ++__r) {
    if (__low[__r]) continue;

    size_type __index = 0;
    __stack.emplace_back(__r, __r);

    while (!__stack.empty()) {
      auto&& __top = __stack.back();
      auto&& __link = __low[__top.head];

      if (__link) {
        if (__link < __low[__top.tail])
          __low[__top.tail] = __link;

        else if (__link == __top.weight) {
          __scc.emplace_back();

          for (size_type __v = -1; __v != __top.head;
               __low[__v] = -1, __scc.back().emplace_back(__v))
            __v = __tmp.back(), __tmp.pop_back();
        }

        __stack.pop_back();
      }

      else {
        __link = __top.weight = ++__index;
        __tmp.emplace_back(__top.head);

        for (auto&& __e : operator[](__top.head))
          __stack.emplace_back(__e.tail, __e.head);
      }
    }
  }

  std::reverse(__scc.begin(), __scc.end());
  return __scc;
}

}  // namespace workspace
