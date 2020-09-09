#pragma once
template <class Container> class reversed {
  Container &ref, copy;

 public:
  reversed(Container &ref) : ref(ref) {}
  reversed(Container &&ref = Container()) : ref(copy), copy(ref) {}
  auto begin() const { return ref.rbegin(); }
  auto end() const { return ref.rend(); }
};
