#ifndef Suffix_array_hpp
#define Suffix_array_hpp

#include <algorithm>
#include <vector>
#include <numeric>

template <class str_type>
class suffix_array
{
    static constexpr size_t npos = -1;
    const str_type str;
    std::vector<size_t> ary, rank;

public:
    using value_type = typename str_type::value_type;

    operator std::vector<size_t>() const { return ary; }

    std::vector<size_t>::const_iterator begin() const { return ary.begin(); }
    std::vector<size_t>::const_iterator end() const { return ary.end(); }

    size_t operator[](size_t i) const { return ary[i]; }

    const str_type &string() const { return str; }

    size_t size() const { return str.size(); }

    suffix_array(const str_type &_str) : str(_str), ary(str.size()), rank(str.size())
    {
        std::iota(ary.begin(), ary.end(), 0);
        std::sort(ary.begin(), ary.end(), [&](size_t i, size_t j){return str[i] < str[j];});

        for(size_t r{1}, c{}, *ptr{&ary.front()}, *tmp{ptr}; c != str.size(); ++r, ptr = tmp)
            while(c != str.size() && str[*ptr] == str[*tmp])
                ++c, rank[*tmp++] = r;

        for(size_t k{1}; k < str.size(); k <<= 1)
        {
            auto comp = [&](size_t i, size_t j) -> bool
            {
                if(rank[i] != rank[j]) return rank[i] < rank[j];
                return (i + k < str.size() ? rank[i + k] : 0) < (j + k < str.size() ? rank[j + k] : 0);
            };
            std::sort(ary.begin(), ary.end(), comp);

            std::vector<size_t> next_rank(str.size());
            for(size_t r{1}, c{}, *ptr{&ary.front()}, *tmp{ptr}; c != str.size(); ++r, ptr = tmp)
                while(c != str.size() && !comp(*ptr, *tmp))
                    ++c, next_rank[*tmp++] = r;
            rank.swap(next_rank);
        }
    }

    size_t find(const str_type &key) const
    {
        size_t lower{npos}, upper{str.size()};
        while(upper - lower > 1)
        {
            size_t mid{(lower + upper) >> 1};
            bool less{};
            for(auto i{std::begin(str) + ary[mid]}, j{std::begin(key)}; j != std::end(key); ++i, ++j)
            {
                if(i == std::end(str) || *i < *j)
                {
                    less = true;
                    break;
                }
                if(*i > *j) break;
            }
            (less ? lower : upper) = mid;
        }
        if(upper == str.size()) return npos;
        for(auto i{std::begin(str) + ary[upper]}, j{std::begin(key)}; j != std::end(key); ++i, ++j)
            if(i == std::end(str) || *i != *j)
                return npos;
        return ary[upper];
    }
}; // class suffix_array

#endif // Suffix_array_hpp