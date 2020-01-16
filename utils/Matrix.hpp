#ifndef Matrix_hpp
#define Matrix_hpp
#include <iostream>
#include <valarray>
#include <vector>

template <class Field>
class matrix
{
    size_t h, w;
    using row_type = std::valarray<Field>;
    using data_type = std::valarray<std::valarray<Field>>;
    data_type data;

    friend std::istream &operator>>(std::istream &is, matrix &x)
    {
        for(size_t i = 0; i != x.h; ++i)
        {
            for(size_t j = 0; j != x.w; ++j) is >> x.data[i][j];
        }
        return is;
    }
    friend std::ostream &operator<<(std::ostream &os, const matrix &x)
    {
        for(size_t i = 0; i != x.h; ++i)
        {
            if(i) os << "\n";
            for(size_t j = 0; j != x.w; ++j) os << (j ? " " : "") << x.data[i][j];
        }
        return os;
    }

    friend matrix transpose(const matrix &x)
    {
        matrix res(x.w, x.h);
        for(size_t i = 0; i != x.w; ++i)
            for(size_t j = 0; j != x.h; ++j)
                res[i][j] = x.data[j][i];
        return res;
    }

    friend matrix pow(matrix x, long long n)
    {
        assert(x.square());
        if(n < 0) x = inverse(x), n = -n;
        matrix res{identity(x.h)};
        while(n)
        {
            if(n & 1) res *= x;
            x *= x, n >>= 1;
        }
        return res;
    }

    friend matrix inverse(const matrix &x)
    {
        assert(x.square());
        matrix ext_x(x.h, x.h * 2), res(x.h);
        for(size_t i = 0; i != x.h; ++i) ext_x.data[i][std::slice(0, x.h, 1)] = x.data[i], ext_x.data[i][i + x.h] = 1;
        if(ext_x.row_canonicalize().size() != x.h) return matrix{0};
        for(size_t i = 0; i != x.h; ++i) res[i] = ext_x.data[i][std::slice(x.h, x.h, 1)];
        return res;
    }

public:
    explicit matrix(size_t _n = 0) : h(_n), w(_n) { resize(_n, _n);}
    matrix(size_t _h, size_t _w) : h(_h), w(_w) { resize(_h, _w); }
    matrix(const data_type &_data) : h(_data.size()), w(_data.size() ? _data[0].size() : 0), data(_data) {}
    operator data_type() const { return data; }

    size_t height() const noexcept { return h; }
    size_t width() const noexcept { return w; }
    bool square() const noexcept { return h == w; }
    row_type &operator[](const size_t i) noexcept { assert(i < data.size()); return data[i]; }
    void resize(size_t h, size_t w, const Field val = Field(0)) { data.resize(h, std::valarray<Field>(val, w)); }

    static matrix identity(const size_t n) noexcept
    {
        data_type data(row_type(n), n);
        for(size_t i = 0; i != n; ++i) data[i][i] = 1;
        return data;
    }

    matrix operator-() const noexcept { return {-data}; }
    matrix &operator+=(const matrix &other) noexcept { data += other.data; return *this; }
    matrix &operator-=(const matrix &other) { data -= other.data; return *this; }
    matrix &operator*=(matrix other) noexcept
    {
        other = transpose(other);
        for(size_t i = 0; i != h; ++i)
        {
            const row_type copied{data[i]};
            for(size_t j = 0; j != other.h; ++j) data[i][j] = (copied * other.data[j]).sum();
        }
        return *this;
    }
    matrix operator+(const matrix &x) const noexcept { return matrix(*this) += x; }
    matrix operator-(const matrix &x) const noexcept { return matrix(*this) -= x; }
    matrix operator*(const matrix &x) const noexcept { return matrix(*this) *= x; }

    // return the list of pivot columns
    std::vector<size_t> row_canonicalize()
    {
        std::vector<size_t> pivots;
        for(size_t j = 0, rank = 0; j != w; ++j)
        {
            row_type *row_ptr = nullptr;
            for(size_t i = rank; i != h; ++i)
            {
                if(data[i][j] != Field{0})
                {
                    const Field f = data[i][j];
                    if(row_ptr) data[i][std::slice(j, w - j, 1)] -= *row_ptr * f;
                    else
                    {
                        swap(data[rank], data[i]);
                        std::slice_array<Field> tmp{data[rank][std::slice(j, w - j, 1)]};
                        tmp = *(row_ptr = new row_type{tmp}) /= f;
                    }
                }
            }
            if(row_ptr)
            {
                for(size_t k = 0; k != rank; ++k)
                {
                    const Field f = data[k][j];
                    data[k][std::slice(j, w - j, 1)] -= *row_ptr * f;
                }
                ++rank;
                pivots.emplace_back(j);
                delete row_ptr;
            }
        }
        return pivots;
    }

    Field determinant() const
    {
        assert(square());
        data_type copied{data};
        Field res{1};
        for(size_t j = 0; j != w; ++j)
        {
            row_type *row_ptr = nullptr;
            for(size_t i = j; i != h; ++i)
            {
                if(copied[i][j] != Field{0})
                {
                    const Field f = copied[i][j];
                    if(row_ptr) copied[i][std::slice(j, w - j, 1)] -= *row_ptr * f;
                    else
                    {
                        swap(copied[i], copied[j]);
                        if(i != j) res = -res;
                        res *= f;
                        std::slice_array<Field> tmp{copied[j][std::slice(j, w - j, 1)]};
                        tmp = *(row_ptr = new row_type{tmp}) /= f;
                    }
                }
            }
            if(!row_ptr) return 0;
        }
        return res;
    }
}; // class matrix

#endif // Matrix_hpp