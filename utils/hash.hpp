#pragma once
#include <ext/pb_ds/assoc_container.hpp>
#include <functional>
#include <random>
#include <unordered_set>
#include "sfinae.hpp"
namespace workspace {
template <class T, class = void>
struct hash : std::hash<T> {};
template <class Unique_bits_type>
struct hash<Unique_bits_type, enable_if_trait_type<Unique_bits_type, std::has_unique_object_representations>>
{
    size_t operator()(uint64_t x) const
    {
        static const uint64_t m = std::random_device{}();
        x ^= x >> 23;
        // x *= 0x2127599bf4325c37ULL;
        x ^= m;
        x ^= x >> 47;
        return x - (x >> 32);
    }
};
template <class Key>
size_t hash_combine(const size_t &seed, const Key &key)
{
    return seed ^ (hash<Key>()(key) + 0x9e3779b9 /* + (seed << 6) + (seed >> 2) */ );
}
template <class T1, class T2>
struct hash<std::pair<T1, T2>>
{
    size_t operator()(const std::pair<T1, T2> &pair) const
    {
        return hash_combine(hash<T1>()(pair.first), pair.second);
    }
};
template <class... T>
class hash<std::tuple<T...>>
{
    template <class Tuple, size_t index = std::tuple_size<Tuple>::value - 1> struct tuple_hash { static uint64_t apply(const Tuple &t) { return hash_combine(tuple_hash<Tuple, index - 1>::apply(t), std::get<index>(t)); } };
    template <class Tuple> struct tuple_hash<Tuple, size_t(-1)> { static uint64_t apply(const Tuple &t) { return 0; } };
public:
    uint64_t operator()(const std::tuple<T...> &t) const { return tuple_hash<std::tuple<T...>>::apply(t); }
};
/*
template <class Key, class Mapped>
struct hash_map : public __gnu_pbds::gp_hash_table<Key, Mapped, hash<Key>>
{
    using base = __gnu_pbds::gp_hash_table<Key, Mapped, hash<Key>>;
    size_t count(const Key &key) const { return base::find(key) != base::end(); }
    template <class... Args> auto emplace(Args&&... args) { return base::insert(typename base::value_type(args...)); }
};
template <class Key> using hash_set = hash_map<Key, __gnu_pbds::null_type>;
/*/
template <class Key, class Mapped> using hash_map = std::unordered_map<Key, Mapped, hash<Key>>;
template <class Key> using hash_set = std::unordered_set<Key, hash<Key>>;
/**/
} // namespace workspace
