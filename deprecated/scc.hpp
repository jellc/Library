#pragma once

/**
 * @file strongly_connected_component.hpp
 * @brief Strongly Connected Component Algorithm
 */

#include <algorithm>
#include <cassert>
#include <numeric>
#include <vector>

namespace workspace {

class strongly_connected_component {
 public:
  using size_type = std::size_t;

 protected:
  std::vector<std::vector<size_type>> __graph, __dag;
  std::vector<size_type> __low;

  bool made() const { return !__low.empty(); }

  /**
   * @param src Vertex
   * @param c Counter
   * @param ptr Pointer to a stack
   * @param used Negative indexed
   * @return Low-link number of the vertex.
   */
  size_type affix(size_type src, size_type &c, size_type *&ptr,
                  bool *const used) {
    if (__low[src]) return __low[src];
    const size_type idx = ++c;
    __low[src] = idx;
    *ptr++ = src;
    for (const size_type dst : __graph[src])
      __low[src] = std::min(__low[src], affix(dst, c, ptr, used));
    if (__low[src] == idx) {
      __dag.push_back({});
      const size_type ccnt = __dag.size();
      used[-ccnt] = true;
      size_type *srcp = ptr;
      do __low[*--srcp] = -ccnt;
      while (*srcp != src);
      while (ptr != srcp) {
        const size_type now = *--ptr;
        for (const size_type dst : __graph[now]) {
          if (!used[(int)__low[dst]]) {
            __dag.back().emplace_back(__low[dst]);
            used[(int)__low[dst]] = true;
          }
        }
      }
      for (const size_type dst : __dag.back()) used[dst] = false;
      used[-ccnt] = false;
      return idx;
    }
    return __low[src];
  }

 public:
  strongly_connected_component() = default;

  strongly_connected_component(size_type __n) : __graph(__n) {}

  size_type add_node() {
    __graph.emplace_back();
    return __graph.size() - 1;
  }

  std::vector<size_type> add_nodes(size_type __n) {
    std::vector<size_type> __nds(__n);
    std::iota(__nds.begin(), __nds.end(), size());
    __graph.resize(size() + __n);
    return __nds;
  }

  /**
   * @brief Add an edge.
   * @param src Source
   * @param dst Destination
   */
  void add_edge(size_type src, size_type dst) {
    assert(src < size());
    assert(dst < size());
    __graph[src].emplace_back(dst);
  }

  /**
   * @return Number of components.
   */
  size_type count() {
    assert(made());
    return __dag.size();
  }

  /**
   * @return Number of vertices.
   */
  size_type size() const { return __graph.size(); }

  /**
   * @param v Vertex
   * @return Component including given vertex.
   */
  size_type operator[](size_type v) {
    assert(made());
    return __low[v];
  }

  const auto &graph() const { return __graph; }

  /**
   * @return Directed Acyclic Graph consisting of components.
   */
  const auto &shrinked_dag() {
    assert(made());
    return __dag;
  }

  /**
   * @brief Run SCC decomposition in linear time.
   */
  void make() {
    __low.assign(size(), 0);
    __dag.clear();
    size_type *ptr = new size_type[size()];
    bool *const used = new bool[size()];
    for (size_type v{}, c{}; v != size(); ++v) affix(v, c, ptr, used + size());
    delete[] ptr;
    delete[] used;
    for (auto &e : __low) e += __dag.size();
    reverse(begin(__dag), end(__dag));
    for (auto &arcs : __dag)
      for (auto &dst : arcs) dst += __dag.size();
  }
};

}  // namespace workspace
