#pragma once
#include <functional>
namespace workspace {
template <class T> class hash : std::hash<T> { size_t operator()(const T&) const; };
struct std_hash_combine
{
    template <class Key>
    size_t operator()(size_t seed, const Key &key) const { return seed ^ (std::hash<Key>()(key) + 0x9e3779b9 + (seed << 6) + (seed >> 2)); }
};
template <class T1, class T2>
class hash<std::pair<T1, T2>>
{
    std_hash_combine comb;
public:
    size_t operator()(const std::pair<T1, T2> &pair) const { return comb(comb(0, pair.first), pair.second); }
};
template <class... T>
class hash<std::tuple<T...>>
{
    template <class Tuple, size_t index = std::tuple_size<Tuple>::value - 1> struct tuple_hasher { template <class Comb> static size_t apply(size_t seed, const Tuple &t, Comb comb = Comb()) { return comb(tuple_hasher<Tuple, index - 1>::apply(seed, t, comb), std::get<index>(t)); } };
    template <class Tuple> struct tuple_hasher<Tuple, 0> { template <class Comb> static size_t apply(size_t seed, const Tuple &t, Comb comb = Comb()) { return comb(seed, std::get<0>(t)); } };
    std_hash_combine comb;
public:
    size_t operator()(const std::tuple<T...> &t) const { return tuple_hasher<std::tuple<T...>>::apply(0, t, comb); }
};
} // namespace workspace
