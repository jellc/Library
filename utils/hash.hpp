#pragma once
#include <ext/pb_ds/assoc_container.hpp>
#include <functional>
#include <random>
#include "sfinae.hpp"
namespace workspace {
template <class T, class = void>
struct hash : std::hash<T> {};
template <class int_type>
struct hash<int_type, enable_if_trait_type<int_type, std::is_integral>>
{
    const uint64_t seed[3];
public:
    template <class URBG = std::random_device> hash(URBG urbg = URBG()) : seed{urbg(), urbg(), urbg()} {}
    size_t operator()(const uint64_t &x) const { return (x * seed[0] + (x >> 32) * seed[1] + seed[2]) >> 32; }
};
template <class T1, class T2>
class hash<std::pair<T1, T2>>
{
    hash<T1> gen1; hash<T2> gen2;
public:
    size_t operator()(const std::pair<T1, T2> &pair) const
    {
        size_t seed = gen1(pair.first);
        return seed ^= gen2(pair.second) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
};
template <class... T>
class hash<std::tuple<T...>>
{
    template <class Key>
    static size_t join(const size_t &seed, const Key &key)
    {
        static hash<Key> gen;
        return seed ^ (gen(key) + 0x9e3779b9 + (seed << 6) + (seed >> 2));
    }
    template <class Tuple, size_t index = std::tuple_size<Tuple>::value - 1> struct tuple_hash { static size_t apply(const Tuple &t) { return join(tuple_hash<Tuple, index - 1>::apply(t), std::get<index>(t)); } };
    template <class Tuple> struct tuple_hash<Tuple, size_t(-1)> { static size_t apply(const Tuple &t) { return 0; } };
public:
    size_t operator()(const std::tuple<T...> &t) const { return tuple_hash<std::tuple<T...>>::apply(t); }
};
template <class Key, class Mapped>
struct hash_map : public __gnu_pbds::gp_hash_table<Key, Mapped, hash<Key>>
{
    using base = __gnu_pbds::gp_hash_table<Key, Mapped, hash<Key>>;
    size_t count(const Key &key) const { return base::find(key) != base::end(); }
    template <class... Args> auto emplace(Args&&... args) { return base::insert(typename base::value_type(args...)); }
};
template <class Key> using hash_set = hash_map<Key, __gnu_pbds::null_type>;
} // namespace workspace
