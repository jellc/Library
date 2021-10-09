#pragma once

/**
 * @file base.h
 * @brief Base
 */

#include <algorithm>
#include <cassert>
#include <list>
#include <numeric>
#include <vector>

#include "edge.h"
#include "queue.h"

namespace workspace {

template <class _Attr = _graph_impl::null,
          class _List = std::vector<edge<_Attr>>>
class graph_base : public std::vector<_List> {
 public:
  using container_type = std::vector<_List>;
  using typename container_type::size_type;

  using container_type::size;
  using container_type::operator[];

  using node_type = size_type;
  using edge_type = typename _List::value_type;
  using weight_type = typename edge_type::value_type;

  graph_base(size_type __n = 0) : container_type(__n) {}

  /**
   * @brief Add some nodes to the graph.
   * @param __n Number of nodes added
   * @return List of indices of the nodes.
   */
  auto add_nodes(size_type __n) noexcept {
    std::vector<node_type> __ret(__n);
    std::iota(__ret.begin(), __ret.end(), size());
    container_type::resize(__n + size());
    return __ret;
  }

  node_type add_node() noexcept { return add_nodes(1).front(); }

  template <class... _Args>
  decltype(auto) add_edge(node_type __u, node_type __v,
                          _Args &&...__args) noexcept {
    assert(__u < size()), assert(__v < size());
    return operator[](__u).emplace_back(__u, __v,
                                        std::forward<_Args>(__args)...)

#if __cplusplus <= 201402L
               ,
               operator[](__u).back()
#endif
        ;
  }

  decltype(auto) add_edge(const edge_type &__e) noexcept {
    assert(__e.tail < size()), assert(__e.head < size());
    return operator[](__e.tail).emplace_back(__e)
#if __cplusplus <= 201402L
               ,
               operator[](__e.tail).back()
#endif
        ;
  }

  /**
   * @brief Single-source DFS.
   * @return Edges of DFS-tree in the search order.
   */
  decltype(auto) dfs(node_type __r) const noexcept {
    node_type __a[]{__r};
    return dfs(__a, __a + 1);
  }

  /**
   * @brief Multi-source DFS.
   * @return Edges of DFS-tree in the search order.
   */
  template <class _Iterator>
  decltype(auto) dfs(_Iterator __first, _Iterator __last) const noexcept {
    return search<std::stack<edge_type, std::vector<edge_type>>>(__first,
                                                                 __last);
  }

  /**
   * @brief Single-source DFS in the complement graph.
   * @return Edges of DFS-tree in the search order.
   */
  decltype(auto) compl_dfs(node_type __r) const noexcept {
    node_type __a[]{__r};
    return compl_dfs(__a, __a + 1);
  }

  /**
   * @brief Multi-source DFS in the complement graph.
   * @return Edges of DFS-tree in the search order.
   */
  template <class _Iterator>
  decltype(auto) compl_dfs(_Iterator __first, _Iterator __last) const noexcept {
    return compl_search<std::stack<edge_type, std::vector<edge_type>>>(__first,
                                                                       __last);
  }

  /**
   * @brief Single-source BFS.
   * @return Edges of BFS-tree in the search order.
   */
  decltype(auto) bfs(node_type __r) const noexcept {
    node_type __a[]{__r};
    return bfs(__a, __a + 1);
  }

  /**
   * @brief Multi-source BFS.
   * @return Edges of BFS-tree in the search order.
   */
  template <class _Iterator>
  decltype(auto) bfs(_Iterator __first, _Iterator __last) const noexcept {
    return search<std::queue<edge_type>>(__first, __last);
  }

  /**
   * @brief Single-source BFS in the complement graph.
   * @return Edges of BFS-tree in the search order.
   */
  decltype(auto) compl_bfs(node_type __r) const noexcept {
    node_type __a[]{__r};
    return compl_bfs(__a, __a + 1);
  }

  /**
   * @brief Multi-source BFS in the complement graph.
   * @return Edges of BFS-tree in the search order.
   */
  template <class _Iterator>
  decltype(auto) compl_bfs(_Iterator __first, _Iterator __last) const noexcept {
    return compl_search<std::queue<edge_type>>(__first, __last);
  }

  /**
   * @brief Single-source Dijkstra's algorithm.
   * @return Edges of shortest path tree in the search order.
   */
  decltype(auto) dijkstra(node_type __r) const noexcept {
    node_type __a[]{__r};
    return dijkstra(__a, __a + 1);
  }

  /**
   * @brief Multi-source Dijkstra's algorithm.
   * @return Edges of shortest path tree in the search order.
   */
  template <class _Iterator>
  decltype(auto) dijkstra(_Iterator __first, _Iterator __last) const noexcept {
    return distance_from<std::priority_queue<edge_type, std::vector<edge_type>,
                                             std::greater<edge_type>>>(__first,
                                                                       __last);
  }

  /**
   * @brief Single-source Bellman-Ford algorithm.
   * @return Edges of shortest path tree in the search order.
   */
  decltype(auto) bellman_ford() const noexcept {
    std::vector<node_type> __a(size());
    return bellman_ford(__a.begin(), __a.end());
  }

  /**
   * @brief Multi-source Bellman-Ford algorithm.
   * @return Edges of shortest path tree in the search order.
   */
  decltype(auto) bellman_ford(node_type __r) const noexcept {
    node_type __a[]{__r};
    return bellman_ford(__a, __a + 1);
  }

  template <class _Iterator>
  decltype(auto) bellman_ford(_Iterator __first,
                              _Iterator __last) const noexcept {
    return distance_from<std::queue<edge_type>>(__first, __last);
  }

  decltype(auto) warshall_floyd(node_type __r) const noexcept;

 protected:
  /**
   * @brief Search from given vertex set.
   * @tparam _Container Queue.
   */
  template <class _Container, class _Iterator>
  auto search(_Iterator __first, _Iterator __last) const noexcept {
    static std::vector<int_fast8_t> __visited;
    __visited.resize(size());

    std::vector<edge_type> __tree;
    static _graph_impl::stl_queue<_Container> __queue;

    for (auto __s = __first; __s != __last; __visited[*__s++] = true)
      for (auto &&__e : operator[](*__s)) __queue.emplace(__e);

    while (!__queue.empty()) {
      auto &&__p = __queue.pop();

      if (__visited[__p.head]) continue;
      __visited[__p.head] = true;

      for (auto &&__e : operator[](__p.head)) __queue.emplace(__e);
      __tree.emplace_back(std::move(__p));
    }

    while (__first != __last) __visited[*__first++] = false;
    for (auto &&__e : __tree) __visited[__e.head] = false;

    return __tree;
  }

  template <class _Container, class _Iterator>
  auto compl_search(_Iterator __first, _Iterator __last) const noexcept;

  /**
   * @brief Get distance from given vertex set.
   * @tparam _Container Queue.
   */
  template <class _Container, class _Iterator>
  auto distance_from(_Iterator __first, _Iterator __last) const noexcept {
    struct dist_type {
      bool nil = true;
      weight_type value;

      bool update(const weight_type &__x) noexcept {
        return nil || __x < value ? nil = false, value = __x, true : false;
      }
    };

    static _graph_impl::stl_queue<_Container> __queue;

    static std::vector<dist_type> __dist;
    __dist.resize(size());

    std::vector<edge_type> __tree;

    for (; __first != __last; ++__first) __queue.emplace(*__first, *__first);

    while (!__queue.empty()) {
      auto &&__p = __queue.pop();

      if (__dist[__p.head].update(__p.weight)) {
        for (auto __e : operator[](__p.head))
          __e.weight = __p.weight + __e.weight, __queue.emplace(std::move(__e));

        if (__p.tail != __p.head) __tree.emplace_back(std::move(__p));
      }
    }

    for (auto &&__e : __tree)
      __dist[__e.head].nil = __dist[__e.tail].nil = true;

    __tree.erase(std::remove_if(__tree.begin(), __tree.end(),
                                [&](auto &&__e) {
                                  return __dist[__e.head].value < __e.weight;
                                }),
                 __tree.end());

    return __tree;
  }
};

}  // namespace workspace
