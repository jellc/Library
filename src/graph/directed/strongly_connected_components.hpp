#pragma once

/*
 * @file strongly_connected_components.hpp
 * @brief Strongly Connected Components
 */

#include <algorithm>
#include <cassert>
#include <vector>

namespace workspace {

struct strongly_connected_components {
  strongly_connected_components(size_t n) : graph(n) {}

  /*
   * @fn add_edge
   * @brief Add an edge.
   * @param src Source
   * @param dst Destination
   */
  void add_edge(size_t src, size_t dst) {
    assert(src < size());
    assert(dst < size());
    graph[src].emplace_back(dst);
  }

  /*
   * @fn count
   * @return The number of components.
   */
  size_t count() {
    assert(made());
    return dag.size();
  }

  /*
   * @fn size
   * @return The number of vertices.
   */
  size_t size() const { return graph.size(); }

  /*
   * @fn operator[]
   * @param v Vertex
   * @return The component including given vertex.
   */
  size_t operator[](size_t v) {
    assert(made());
    return low[v];
  }

  /*
   * @fn shrinked_dag
   * @return Directed Acyclic Graph consisting of components.
   */
  const std::vector<std::vector<size_t>> &shrinked_dag() {
    assert(made());
    return dag;
  }

  /*
   * @fn make
   * @brief Run SCC decomposition in linear time.
   */
  void make() {
    low.assign(size(), 0);
    dag.clear();
    size_t *itr = new size_t[size()];
    bool *const used = new bool[size()];
    for (size_t v{}, c{}; v != size(); ++v) affix(v, c, itr, used + size());
    delete[] itr;
    delete[] used;
    for (auto &e : low) e += dag.size();
    reverse(begin(dag), end(dag));
    for (auto &arcs : dag)
      for (auto &dst : arcs) dst += dag.size();
  }

 protected:
  std::vector<std::vector<size_t>> graph, dag;
  std::vector<size_t> low;

  bool made() const { return !low.empty(); }

  /*
   * @fn affix
   * @param src Vertex
   * @param c Counter
   * @param itr Pointer to a stack
   * @param used Negative indexed
   * @return Low-link number of the vertex.
   */
  size_t affix(size_t src, size_t &c, size_t *&itr, bool *const used) {
    if (low[src]) return low[src];
    size_t idx = ++c;
    low[src] = idx;
    *itr++ = src;
    for (size_t dst : graph[src])
      low[src] = std::min(low[src], affix(dst, c, itr, used));
    if (low[src] == idx) {
      dag.push_back({});
      auto ccnt = dag.size();
      used[-ccnt] = true;
      auto srcp = itr;
      do
        low[*--srcp] = -ccnt;
      while (*srcp != src);
      while (itr != srcp) {
        const size_t now = *--itr;
        for (size_t dst : graph[now]) {
          if (!used[(int)low[dst]]) {
            dag.back().emplace_back(low[dst]);
            used[(int)low[dst]] = true;
          }
        }
      }
      for (size_t dst : dag.back()) used[dst] = false;
      used[-ccnt] = false;
      return idx;
    }
    return low[src];
  }
};

}  // namespace workspace
