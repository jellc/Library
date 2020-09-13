// #line 2 "Manacher.hpp"
#ifndef Manacher_hpp
#define Manacher_hpp
#include <iostream>
#include <string>
#include <vector>

template <class str_type = std::string>
class Manacher
{
    const size_t len;
    std::vector<size_t> rad;
    friend std::ostream &operator<<(std::ostream &os, const Manacher &mana)
    {
        bool is_front = true;
        for(size_t r : mana.rad)
        {
            if(is_front) is_front = false;
            else os << " ";
            os << r;
        }
        return os;
    }
  public:
    Manacher(const str_type &str) : len(str.size()), rad(str.size())
    {
        for(size_t i = 0, c = 0; i != len; ++i)
        {
            int l = c * 2 - i;
            if(l >= 0 && c + rad[c] > i + rad[l]) rad[i] = rad[l];
            else
            {
                size_t j = c + rad[c] - i;
                while(i >= j && i + j != len && str[i - j] == str[i + j]) ++j;
                rad[c = i] = j;
            }
        }
    }
    size_t size() const { return rad.size(); }
    size_t operator[](size_t i) const { return rad[i]; }
}; // class Manacher

#endif // Manacher_hpp