#include <iostream>

#define dump(...) std::cerr << "[ " << __LINE__ << " : " << __FUNCTION__ << " ]\n", dump_func(#__VA_ARGS__, __VA_ARGS__)

template <class T> void dump_func(const char *ptr, const T &x)
{
    std::cerr << '\t';
    for(char c = *ptr; c != '\0'; c = *++ptr) if(c != ' ' && c != '\t') std::cerr << c;
    std::cerr << " : " << x << '\n';
}

template <class T, class... rest_t> void dump_func(const char *ptr, const T &x, rest_t... rest)
{
    std::cerr << '\t';
    for(char c = *ptr; c != ','; c = *++ptr) if(c != ' ' && c != '\t') std::cerr << c;
    std::cerr << " : " << x << ",\n"; dump_func(++ptr, rest...);
}