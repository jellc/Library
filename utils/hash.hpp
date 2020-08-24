#pragma once
#include <ext/pb_ds/assoc_container.hpp>
#include <functional>
#include <random>
#include "sfinae.hpp"
namespace workspace {
template <class T, class = void>
struct hash : std::hash<T> {};
struct std_hash_combine
{
    template <class Key>
    size_t operator()(size_t seed, const Key &key) const { return seed ^ (std::hash<Key>()(key) + 0x9e3779b9 + (seed << 6) + (seed >> 2)); }
};
template <class int_type>
struct hash<int_type, enable_if_trait_type<int_type, std::is_integral>>
{
    const uint64_t seed[2], offset;
public:
    hash() : seed{std::random_device{}(), std::random_device{}()}, offset{std::random_device{}()} {}
    size_t operator()(const uint64_t &x) const { return (offset + x * seed[0] + (x >> 32) * seed[1]) >> 32; }
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
template <class Key, class Mapped>
struct hashmap : public __gnu_pbds::gp_hash_table<Key, Mapped, hash<Key>>
{
    using base = __gnu_pbds::gp_hash_table<Key, Mapped, hash<Key>>;
    size_t count(const Key &key) const { return base::find(key) != base::end(); }
    template <class... Args> auto emplace(Args&&... args) { return base::insert(typename base::value_type(args...)); }
};
template <class Key> using hashset = hashmap<Key, __gnu_pbds::null_type>;
} // namespace workspace
