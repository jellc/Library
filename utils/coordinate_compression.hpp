#include <algorithm>
#include <cassert>
#include <vector>

template <class T>
class coordinate_compression
{
    std::vector<T> uniquely;
    std::vector<size_t> compressed;

public:
    coordinate_compression(const std::vector<T> &raw) : uniquely(raw), compressed(uniquely.size())
    {
        std::sort(uniquely.begin(), uniquely.end());
        uniquely.erase(std::unique(uniquely.begin(), uniquely.end()), uniquely.end());
        for(size_t i = 0; i != raw.size(); ++i)
            compressed[i] = std::lower_bound(uniquely.begin(), uniquely.end(), raw[i]) - uniquely.begin();
    }

    size_t operator[](const size_t idx) const
    {
        assert(idx < compressed.size());
        return compressed[idx];
    }

    size_t kind() const { return uniquely.size(); }

    T restore(const size_t ord) const
    {
        assert(ord < uniquely.size());
        return uniquely[ord];
    }

    size_t order_of(const T &val) const { return std::lower_bound(uniquely.begin(), uniquely.end(), val) - uniquely.begin(); }

    std::vector<size_t>::iterator begin() { return compressed.begin(); }
    std::vector<size_t>::iterator end() { return compressed.end(); }
    std::vector<size_t>::iterator rbegin() { return compressed.rbegin(); }
    std::vector<size_t>::iterator rend() { return compressed.rend(); }
};