#ifndef Suffix_array_hpp
#define Suffix_array_hpp

#include <algorithm>
#include <vector>
#include <numeric>

template <class str_type>
class suffix_array
{
    const str_type str;
    const size_t len;
    std::vector<size_t> ary, rank;

public:
    using value_type = typename str_type::value_type;
    operator std::vector<size_t>() const { return ary; }
    std::vector<size_t>::const_iterator begin() const { return std::begin(ary); }
    std::vector<size_t>::const_iterator end() const { return std::end(ary); }

    suffix_array(const str_type &_str) : str(_str), len(str.size()), ary(len), rank(len)
    {
        std::iota(std::begin(ary), std::end(ary), 0);
        std::sort(std::begin(ary), std::end(ary), [&](size_t i, size_t j){return str[i] < str[j];});

        for(size_t r{1}, c{}, *ptr{&ary.front()}, *tmp{ptr}; c != len; ++r, ptr = tmp)
            while(c != len && str[*ptr] == str[*tmp])
                ++c, rank[*tmp++] = r;

        for(size_t k = 1; k < len; k <<= 1)
        {
            auto comp = [&](size_t i, size_t j) -> bool
            {
                if(rank[i] != rank[j]) return rank[i] < rank[j];
                return (i + k < len ? rank[i + k] : 0) < (j + k < len ? rank[j + k] : 0);
            };
            std::sort(std::begin(ary), std::end(ary), comp);

            std::vector<size_t> next_rank(len);
            for(size_t r{1}, c{}, *ptr{&ary.front()}, *tmp{ptr}; c != len; ++r, ptr = tmp)
                while(c != len && !comp(*ptr, *tmp))
                    ++c, next_rank[*tmp++] = r;
            rank.swap(next_rank);
        }
    }

    size_t operator[](size_t i) const { return ary[i]; }

    const str_type &string() const { return str; }

    size_t find(const str_type &key) const
    {
        const size_t m{key.size()};
        int low = -1, up = len;
        while(up - low > 1)
        {
            size_t mid = (low + up) >> 1;
            bool less = false;
            for(size_t i{mid}, j{}; i != len && j != m; ++i, ++j)
            {
                if(str[i] != key[j])
                {
                    if(str[i] < key[j]) less = true;
                    break;
                }
            }
            (less ? low : up) = mid;
        }
        for(size_t i{low}, j{}; j != m; ++i, ++j)
            if(i >= len || str[i] != key[j])
                return -1;
        return low;
    }
}; // class suffix_array

#endif // Suffix_array_hpp