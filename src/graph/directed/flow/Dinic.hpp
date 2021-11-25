#pragma once

/**
 * @file Dinic.hpp
 * @brief Dinic's Algorithm
 */

#include <limits>

#include "base.hpp"

namespace workspace {

/**
 * @brief Compute the maximum flow.
 * @tparam _Cap Capacity type
 */
template <class _Cap> class Dinic : public flow_graph<_Cap> {
  using _Base = flow_graph<_Cap>;

 public:
  using _Base::_Base;
  using typename _Base::size_type;

 protected:
  constexpr static size_type nil = -1;

  std::vector<size_type> __level;
  std::vector<typename _Base::container_type::value_type::iterator> __iter;

  _Cap dfs(size_type __src, size_type __dst, _Cap __limit) noexcept {
    if (__src == __dst) return __limit;

    _Cap __flow(0);

    for (auto &__e{__iter[__dst]}; __e != _Base::graph[__dst].end(); ++__e)
      if (static_cast<_Cap>(0) < __e->flow &&
          __level[__e->head] < __level[__dst])
        if (_Cap achv = dfs(__src, __e->head, std::min(__limit, __e->flow));
            static_cast<_Cap>(0) < achv) {
          __e->push(-achv);
          __flow += achv, __limit -= achv;
          if (__limit == static_cast<_Cap>(0)) break;
        }

    return __flow;
  }

 public:
  /**
   * @brief Run Dinic's algorithm.
   * @param __src Source
   * @param __dst Destination
   * @return Maximum flow.
   */
  _Cap run(size_type __src, size_type __dst) noexcept {
    return run(__src, __dst, std::numeric_limits<_Cap>::max());
  }

  /**
   * @brief Run Dinic's algorithm.
   * @param __src Source
   * @param __dst Destination
   * @param __limit Flow limit
   * @return Maximum flow.
   */
  _Cap run(size_type __src, size_type __dst, _Cap __limit) noexcept {
    assert(__src < _Base::size()), assert(__dst < _Base::size()),
        assert(__src != __dst);

    __level.resize(_Base::size(), nil);
    __iter.resize(_Base::size());

    if (!(static_cast<_Cap>(0) < __limit)) return 0;
    _Cap __flow = 0;

    for (std::vector<size_type> __q(_Base::size());;
         std::fill(__level.begin(), __level.end(), nil)) {
      __level[__q.front() = __src] = 0;

      for (auto __ql{__q.begin()}, __qr{std::next(__ql)};
           __level[__dst] == nil && __ql != __qr; ++__ql)
        for (const auto &__e : _Base::graph[*__ql])
          if (static_cast<_Cap>(0) < __e.capacity && __level[__e.head] == nil)
            __level[ *__qr++ = __e.head] = __level[*__ql] + 1;

      if (__level[__dst] == nil) break;

      for (size_type __x{}; __x != _Base::size(); ++__x)
        __iter[__x] = _Base::graph[__x].begin();

      __flow += dfs(__src, __dst, __limit);
    }

    return __flow;
  }

  // Minimum Cut.
  // Call it after `run`.
  auto min_cut() const noexcept {
    std::vector<typename _Base::edge> __cut;

    for (size_type __x{}; __x != _Base::size(); ++__x)
      if (~__level[__x])
        for (const auto &__e : _Base::operator[](__x))
          if (!~__level[__e.head]) __cut.emplace_back(__e);

    return __cut;
  }
};

}  // namespace workspace
