#pragma once
#include <limits>
template <class T>
struct min_monoid
{
    using value_type = T;
    static T min, max;
    T value;
    min_monoid() : value(max) {}
    min_monoid(const T &value) : value(value) {}
    operator T() const { return value; }
    min_monoid operator+(const min_monoid &rhs) const
    {
        return value < rhs.value ? *this : rhs;
    }
};
template <class T> T min_monoid<T>::min = std::numeric_limits<T>::min();
template <class T> T min_monoid<T>::max = std::numeric_limits<T>::max();
template <class T>
struct max_monoid : min_monoid<T>
{
    using base = min_monoid<T>;
    using base::min_monoid;
    max_monoid() : base(base::min) {}
    max_monoid operator+(const max_monoid &rhs) const
    {
        return !(base::value < rhs.value) ? *this : rhs;
    }
};
