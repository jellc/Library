#pragma once
#include <functional>
#include <vector>
template <class T, class Op = std::multiplies<T>>
class factorial
{
    std::vector<T> fact;
    Op op;
public:
    factorial(T init = 1, Op op = Op()) : fact{init}, op{op} {}
    T operator()(const int &n)
    {
        if(n < 0) return 0;
        for(int m(fact.size()); m <= n; ++m) fact.emplace_back(op(fact.back(), m));
        return fact[n];
    }
}; // class factorial
