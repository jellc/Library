#pragma once
#include <cassert>
#include <vector>
// the base class of flow algorithms.
template <class cap_t, class cost_t> struct flow_base {
  struct edge_t {
    size_t src, dst;
    cap_t cap;
    cost_t cost;
    edge_t *rev;
    edge_t() = default;
    edge_t(size_t src, size_t dst, const cap_t &cap, edge_t *rev)
        : src(src), dst(dst), cap(cap), rev(rev) {}
    edge_t(size_t src, size_t dst, const cap_t &cap, const cost_t &cost,
           edge_t *rev)
        : src(src), dst(dst), cap(cap), cost(cost), rev(rev) {}
    const cap_t &flow(const cap_t &f = 0) { return cap -= f, rev->cap += f; }
    bool avbl() const { return static_cast<cap_t>(0) < cap; }
  };  // class edge_t

  class adj_type {
    edge_t *fst, *lst, *clst;

   public:
    template <class... Args> edge_t *emplace(Args &&... args) {
      if (lst == clst) {
        size_t len(clst - fst);
        edge_t *nfst = lst = new edge_t[len << 1];
        for (edge_t *p{fst}; p != clst; ++p, ++lst)
          p->rev->rev = lst, *lst = *p;
        delete[] fst;
        fst = nfst;
        clst = lst + len;
      }
      *lst = edge_t(args...);
      return lst++;
    }
    adj_type() : fst(new edge_t[1]), lst(fst), clst(fst + 1) {}
    ~adj_type() { delete[] fst; }
    edge_t &operator[](size_t i) {
      assert(i < size());
      return *(fst + i);
    }
    size_t size() const { return lst - fst; }
    edge_t *begin() const { return fst; }
    edge_t *end() const { return lst; }
  };  // class adj_type

  flow_base(size_t n = 0) : adjs(n) {}

  flow_base(const flow_base &other) : adjs(other.size()) {
    for (size_t node{}; node != size(); ++node)
      for (const auto &[src, dst, cap, cost, rev] : other[node])
        if (src == node) {
          edge_t *ptr = adjs[src].emplace(src, dst, cap, cost, nullptr);
          ptr->rev = adjs[dst].emplace(dst, src, rev->cap, -cost, ptr);
          rev->src = nil;
        } else {
          rev->rev->src = node;
        }
  }

  flow_base &operator=(const flow_base &rhs) {
    if (this != &rhs) adjs.swap(flow_base(rhs).adjs);
    return *this;
  }

  size_t size() const { return adjs.size(); }

  adj_type &operator[](size_t node) {
    assert(node < size());
    return adjs[node];
  }
  const adj_type &operator[](size_t node) const {
    assert(node < size());
    return adjs[node];
  }

  virtual edge_t *add_edge(size_t src, size_t dst, const cap_t &cap,
                           const cost_t &cost) {
    assert(src < size());
    assert(dst < size());
    assert(!(cap < static_cast<cap_t>(0)));
    if (!(static_cast<cap_t>(0) < cap) || src == dst) return nullptr;
    edge_t *ptr = adjs[src].emplace(src, dst, cap, cost, nullptr);
    ptr->rev = adjs[dst].emplace(dst, src, 0, -cost, ptr);
    return ptr;
  }

 protected:
  constexpr static size_t nil = -1;
  std::vector<adj_type> adjs;
};  // class flow_base