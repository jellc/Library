#ifndef suffix_array_hpp
#define suffix_array_hpp

#include <algorithm>
#include <vector>
#include <numeric>

template <class str_type>
class suffix_array
{
    static constexpr size_t npos = -1;
    str_type str;
    std::vector<size_t> sa, rank;

    void construct_sa()
    {
        std::iota(sa.begin(), sa.end(), 0);
        std::sort(sa.begin(), sa.end(), [&](size_t i, size_t j){return str[i] < str[j];});

        for(size_t r{1}, c{}, *ptr{&sa.front()}, *tmp{ptr}; c != size(); ++r, ptr = tmp)
            while(c != size() && str[*ptr] == str[*tmp])
                ++c, rank[*tmp++] = r;

        for(size_t k{1}; k < size(); k <<= 1)
        {
            auto comp = [&](size_t i, size_t j) -> bool
            {
                if(rank[i] != rank[j]) return rank[i] < rank[j];
                return (i + k < size() ? rank[i + k] : 0) < (j + k < size() ? rank[j + k] : 0);
            };
            std::sort(sa.begin(), sa.end(), comp);

            std::vector<size_t> next_rank(size());
            for(size_t r{1}, c{}, *ptr{&sa.front()}, *tmp{ptr}; c != size(); ++r, ptr = tmp)
                while(c != size() && !comp(*ptr, *tmp))
                    ++c, next_rank[*tmp++] = r;
            rank.swap(next_rank);
        }

        sa.emplace(sa.begin(), size());
        rank.emplace_back(0);
    }

public:
    // using value_type = typename str_type::value_type;

    operator std::vector<size_t>() const { return sa; }

    std::vector<size_t>::const_iterator begin() const { return sa.begin(); }
    std::vector<size_t>::const_iterator end() const { return sa.end(); }

    size_t operator[](size_t i) const { return sa[i + 1]; }

    const str_type &string() const { return str; }

    size_t size() const { return std::size(str); }

    template <class type = str_type, typename = typename type::value_type>
    suffix_array(const str_type &_str) : str(_str), sa(size()), rank(size())
    {
        construct_sa();
    }

    template <class type = str_type, enable_if_t<std::is_array<type>::value, nullptr_t> = nullptr>
    suffix_array(const str_type &_str) : sa(size()), rank(size())
    {
        std::copy(std::begin(_str), std::end(_str), str);
        construct_sa();
    }

    size_t find(const str_type &key) const
    {
        using std::begin; using std::end;

        size_t lower{npos}, upper{size()};
        while(upper - lower > 1)
        {
            size_t mid{(lower + upper) >> 1};
            bool less{};
            for(auto i{begin(str) + sa[mid]}, j{begin(key)}; j != end(key); ++i, ++j)
            {
                if(i == end(str) || *i < *j)
                {
                    less = true;
                    break;
                }
                if(*i > *j) break;
            }
            (less ? lower : upper) = mid;
        }

        if(upper == size()) return npos;
        for(auto i{begin(str) + sa[upper]}, j{begin(key)}; j != end(key); ++i, ++j)
            if(i == end(str) || *i != *j)
                return npos;
        return sa[upper];
    }

    std::vector<size_t> lcp_array() const
    {
        static std::vector<size_t> lcp;
        if(!lcp.empty()) return lcp;
        lcp.resize(size());
        for(size_t i{}, h{}; i != size(); ++i, h = h ? h - 1 : 0)
        {
            for(size_t j{sa[rank[i] - 1] + h}; i + h != size() && j != size(); ++j, ++h)
                if(str[i + h] != str[j]) break;
            lcp[rank[i] - 1] = h;
        }
        return lcp;
    }
}; // class suffix_array

#endif // suffix_array_hpp