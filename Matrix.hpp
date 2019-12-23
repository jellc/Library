#ifndef MATRIX_HPP
#define MATRIX_HPP
// #include <iostream>
// K must be a field.
template <class K>
class matrix
{
    std::vector<std::vector<K>> mat;
    friend std::istream &operator>>(std::istream &is, matrix &x)
    {
        size_t h = x.height(), w = x.width();
        for(size_t i = 0; i < h; ++i)
        {
            for(size_t j = 0; j < w; ++j) is >> x[i][j];
        }
        return is;
    }
    friend std::ostream &operator<<(std::ostream &os, const matrix &x)
    {
        size_t h = x.height(), w = x.width();
        for(size_t i = 0; i < h; ++i)
        {
            if(i) os << "\n";
            for(size_t j = 0; j < w; ++j) os << (j ? " " : "") << x.mat[i][j];
        }
        return os;
    }
    friend matrix pow(matrix x, long long n)
    {
        assert(x.is_square());
        matrix res = identity(x.height());
        while(n)
        {
            if(n & 1) res *= x;
            x *= x, n >>= 1;
        }
        return res;
    }
    friend matrix inverse(const matrix &x)
    {
        assert(x.is_square());
        size_t n = x.height();
        matrix ext_x(x), e(identity(n)), res(n);
        for(size_t i = 0; i < n; ++i)
            ext_x[i].insert(end(ext_x[i]), begin(e[i]), end(e[i]));
        ext_x = ext_x.row_canonical_form();
        for(size_t i = 0; i < n; ++i)
        {
            if(std::vector<K>(begin(ext_x[i]), begin(ext_x[i]) + n) != e[i]) return matrix();
            res[i] = std::vector<K>(begin(ext_x[i]) + n, end(ext_x[i]));
        }
        return res;
    }
  public:
    matrix() {}
    matrix(size_t n) { assign(n, n);}
    matrix(size_t h, size_t w) { assign(h, w); }
    matrix(const matrix &x) : mat(x.mat) {}
    matrix(const std::vector<std::vector<K>> _mat) : mat(_mat) {}
    size_t height() const { return mat.size(); }
    size_t width() const { return mat.empty() ? 0 : mat[0].size(); }
    bool is_square() const { return height() == width(); }
    void resize(size_t h, size_t w, const K v = K(0)) { mat.resize(h, std::vector<K>(w, v)); }
    void assign(size_t h, size_t w, const K v = K()) { mat.assign(h, std::vector<K>(w, v)); }
    std::vector<K> &operator[](const size_t i) { return mat[i]; }
    static matrix identity(size_t n)
    {
        matrix ret(n, n);
        for(size_t i = 0; i < n; ++i) ret[i][i] = K(1);
        return ret;
    }
    matrix operator-() const
    {
        size_t h = height(), w = width();
        matrix res(*this);
        for(size_t i = 0; i < h; ++i)
        {
            for(size_t j = 0; j < w; ++j)
            {
                res[i][j] = -mat[i][j];
            }
        }
        return res;
    }
    matrix operator&(const matrix &x) const { return matrix(*this) &= x; }
    matrix operator|(const matrix &x) const { return matrix(*this) |= x; }
    matrix operator^(const matrix &x) const { return matrix(*this) ^= x; }
    matrix operator+(const matrix &x) const { return matrix(*this) += x; }
    matrix operator-(const matrix &x) const { return matrix(*this) -= x; }
    matrix operator*(const matrix &x) const { return matrix(*this) *= x; }
    matrix &operator&=(const matrix &x)
    {
        size_t h = height(), w = width();
        assert(h == x.height() and w == x.width());
        for(size_t i = 0; i < h; ++i)
        {
            for(size_t j = 0; j < w; ++j)
            {
                mat[i][j] &= x.mat[i][j];
            }
        }
        return *this;
    }
    matrix &operator|=(const matrix &x)
    {
        size_t h = height(), w = width();
        assert(h == x.height() and w == x.width());
        for(size_t i = 0; i < h; ++i)
        {
            for(size_t j = 0; j < w; ++j)
            {
                mat[i][j] |= x.mat[i][j];
            }
        }
        return *this;
    }
    matrix &operator^=(const matrix &x)
    {
        size_t h = height(), w = width();
        assert(h == x.height() and w == x.width());
        for(size_t i = 0; i < h; ++i)
        {
            for(size_t j = 0; j < w; ++j)
            {
                mat[i][j] ^= x.mat[i][j];
            }
        }
        return *this;
    }
    matrix &operator+=(const matrix &x)
    {
        size_t h = height(), w = width();
        assert(h == x.height() and w == x.width());
        for(size_t i = 0; i < h; ++i)
        {
            for(size_t j = 0; j < w; ++j)
            {
                mat[i][j] += x.mat[i][j];
            }
        }
        return *this;
    }
    matrix &operator-=(const matrix &x)
    {
        size_t h = height(), w = width();
        assert(h == x.height() and w == x.width());
        for(size_t i = 0; i < h; ++i)
        {
            for(size_t j = 0; j < w; ++j)
            {
                mat[i][j] -= x.mat[i][j];
            }
        }
        return *this;
    }
    matrix &operator*=(const matrix &x)
    {
        size_t l = height(), m = width(), n = x.width();
        assert(m == x.height());
        matrix res(l, n);
        for(size_t i = 0; i < l; ++i)
        {
            for(size_t j = 0; j < m; ++j)
            {
                for(size_t k = 0; k < n; ++k)
                {
                    res[i][k] += mat[i][j] * x.mat[j][k];
                }
            }
        }
        return *this = res;
    }
    std::vector<size_t> row_canonicalize()
    {
        std::vector<size_t> pivots;
        const size_t h = height(), w = width();
        for(size_t j = 0, rank = 0; j != w; ++j)
        {
            bool ispiv = false;
            for(size_t i = rank; i != h; ++i)
            {
                if(mat[i][j] != K{})
                {
                    if(ispiv)
                    {
                        const K r = -mat[i][j];
                        for(size_t k = j; k != w; ++k) mat[i][k] += mat[rank][k] * r;
                    }
                    else
                    {
                        swap(mat[rank], mat[i]);
                        K r = mat[rank][j];
                        for(size_t k = j; k != w; ++k) mat[rank][k] /= r;
                        for(size_t k = 0; k != rank; ++k)
                        {
                            r = -mat[k][j];
                            for(size_t l = j; l != w; ++l) mat[k][l] += mat[rank][l] * r;
                        }
                        ispiv = true;
                    }
                }
            }
            if(ispiv)
            {
                ++rank;
                pivots.emplace_back(j);
            }
        }
        return pivots;
    }
    K determinant() const
    {
        matrix<K> x(*this);
        assert(is_square());
        size_t n = height();
        K res(1);
        for(size_t j = 0; j < n; ++j)
        {
            bool ispiv = false;
            for(size_t i = j; i < n; ++i)
            {
                if(x[i][j] != K{})
                {
                    if(ispiv)
                    {
                        const K r = -x[i][j];
                        for(size_t k = j; k < n; ++k) x[i][k] += x[j][k] * r;
                    }
                    else
                    {
                        swap(x[i], x[j]);
                        if(i != j) res = -res;
                        const K r = x[j][j];
                        res *= r;
                        for(size_t k = j; k < n; ++k) x[j][k] /= r;
                        ispiv = true;
                    }
                }
            }
            if(!ispiv) return K(0);
        }
        return res;
    }
};
#endif