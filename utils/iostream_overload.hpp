#pragma once
#include <iostream>
namespace std
{
    template <class T, class U> istream &operator>>(istream &is, pair<T, U> &p) { return is >> p.first >> p.second; }
    template <class T, class U> ostream &operator<<(ostream &os, const pair<T, U> &p) { return os << p.first << ' ' << p.second; }
    template <class tuple_t, size_t index> struct tuple_is { static istream &apply(istream &is, tuple_t &t) { tuple_is<tuple_t, index - 1>::apply(is, t); return is >> get<index>(t); } };
    template <class tuple_t> struct tuple_is<tuple_t, SIZE_MAX> { static istream &apply(istream &is, tuple_t &t) { return is; } };
    template <class... T> istream &operator>>(istream &is, tuple<T...> &t) { return tuple_is<tuple<T...>, tuple_size<tuple<T...>>::value - 1>::apply(is, t); }
    template <class tuple_t, size_t index> struct tuple_os { static ostream &apply(ostream &os, const tuple_t &t) { tuple_os<tuple_t, index - 1>::apply(os, t); return os << ' ' << get<index>(t); } };
    template <class tuple_t> struct tuple_os<tuple_t, 0> { static ostream &apply(ostream &os, const tuple_t &t) { return os << get<0>(t); } };
    template <class tuple_t> struct tuple_os<tuple_t, SIZE_MAX> { static ostream &apply(ostream &os, const tuple_t &t) { return os; } };
    template <class... T> ostream &operator<<(ostream &os, const tuple<T...> &t) { return tuple_os<tuple<T...>, tuple_size<tuple<T...>>::value - 1>::apply(os, t); }
    template <class Container, typename Value = typename Container::value_type, enable_if_t<!is_same<decay_t<Container>, string>::value, nullptr_t> = nullptr>
    istream& operator>>(istream& is, Container &cont) { for(auto&& e : cont) is >> e; return is; }
    template <class Container, typename Value = typename Container::value_type, enable_if_t<!is_same<decay_t<Container>, string>::value, nullptr_t> = nullptr>
    ostream& operator<<(ostream& os, const Container &cont) { bool flag = 1; for(auto&& e : cont) flag ? flag = 0 : (os << ' ', 0), os << e; return os; }
} // namespace std
