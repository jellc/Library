#pragma once

/**
 * @file queue.h
 * @brief Queue
 */

#include <queue>
#include <stack>

namespace workspace {

namespace _graph_impl {

template <class _Base, class = void> struct stl_queue : _Base {
  auto pop() noexcept {
    auto __tmp = std::move(_Base::front());
    _Base::pop();
    return __tmp;
  }
};

template <class _Base>
struct stl_queue<_Base, std::__void_t<decltype(std::declval<_Base>().top())>>
    : _Base {
  auto pop() noexcept {
    auto __tmp = std::move(_Base::top());
    _Base::pop();
    return __tmp;
  }
};

}  // namespace _graph_impl

}  // namespace workspace
