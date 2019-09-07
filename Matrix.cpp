template <class K>
// K must be a field.
struct matrix
{
    std::vector<std::vector<K>> mat;

    matrix()
    {}
    matrix(std::size_t n)
    {
        assign(n, n);
    }
    matrix(std::size_t h, std::size_t w)
    {
        assign(h, w);
    }
    matrix(const matrix &x) : mat(x.mat)
    {}

    void resize(std::size_t h, std::size_t w, const K v = K())
    {
        mat.resize(h, std::vector<K>(w, v));
    }

    void assign(std::size_t h, std::size_t w, const K v = K())
    {
        mat.assign(h, std::vector<K>(w, v));
    }

    std::size_t height() const
    {
        return mat.size();
    }

    std::size_t width() const
    {
        return mat.empty() ? 0 : mat[0].size();
    }

    bool is_square() const
    {
        return height() == width();
    }

    std::vector<K> &operator[](const std::size_t i)
    {
        return mat[i];
    }

    static matrix identity(std::size_t n)
    {
        matrix ret(n, n);
        for(std::size_t i = 0; i < n; ++i)
            ret[i][i] = K(1);
        return ret;
    }

    matrix operator-() const
    {
        std::size_t h = height(), w = width();
        matrix res(*this);
        for(std::size_t i = 0; i < h; ++i)
        {
            for(std::size_t j = 0; j < w; ++j)
            {
                res[i][j] = -mat[i][j];
            }
        }
        return res;
    }

    matrix operator&(const matrix &x) const
    {
        return matrix(*this) &= x;
    }

    matrix operator|(const matrix &x) const
    {
        return matrix(*this) |= x;
    }

    matrix operator^(const matrix &x) const
    {
        return matrix(*this) ^= x;
    }

    matrix operator+(const matrix &x) const
    {
        return matrix(*this) += x;
    }

    matrix operator-(const matrix &x) const
    {
        return matrix(*this) -= x;
    }

    matrix operator*(const matrix &x) const
    {
        return matrix(*this) *= x;
    }

    matrix &operator&=(const matrix &x)
    {
        std::size_t h = height(), w = width();
        assert(h == x.height() and w == x.width());
        for(std::size_t i = 0; i < h; ++i)
        {
            for(std::size_t j = 0; j < w; ++j)
            {
                mat[i][j] &= x.mat[i][j];
            }
        }
        return *this;
    }

    matrix &operator|=(const matrix &x)
    {
        std::size_t h = height(), w = width();
        assert(h == x.height() and w == x.width());
        for(std::size_t i = 0; i < h; ++i)
        {
            for(std::size_t j = 0; j < w; ++j)
            {
                mat[i][j] |= x.mat[i][j];
            }
        }
        return *this;
    }

    matrix &operator^=(const matrix &x)
    {
        std::size_t h = height(), w = width();
        assert(h == x.height() and w == x.width());
        for(std::size_t i = 0; i < h; ++i)
        {
            for(std::size_t j = 0; j < w; ++j)
            {
                mat[i][j] ^= x.mat[i][j];
            }
        }
        return *this;
    }

    matrix &operator+=(const matrix &x)
    {
        std::size_t h = height(), w = width();
        assert(h == x.height() and w == x.width());
        for(std::size_t i = 0; i < h; ++i)
        {
            for(std::size_t j = 0; j < w; ++j)
            {
                mat[i][j] += x.mat[i][j];
            }
        }
        return *this;
    }

    matrix &operator-=(const matrix &x)
    {
        std::size_t h = height(), w = width();
        assert(h == x.height() and w == x.width());
        for(std::size_t i = 0; i < h; ++i)
        {
            for(std::size_t j = 0; j < w; ++j)
            {
                mat[i][j] -= x.mat[i][j];
            }
        }
        return *this;
    }

    matrix &operator*=(const matrix &x)
    {
        std::size_t l = height(), m = width(), n = x.width();
        assert(m == x.height());
        matrix res(l, n);
        for(std::size_t i = 0; i < l; ++i)
        {
            for(std::size_t j = 0; j < m; ++j)
            {
                for(std::size_t k = 0; k < n; ++k)
                {
                    res[i][k] += mat[i][j] * x.mat[j][k];
                }
            }
        }
        return *this = res;
    }

    friend matrix pow(matrix x, int_fast64_t n)
    {
        assert(x.is_square());
        matrix res = identity(x.height());
        while(n)
        {
            if(n & 1) res *= x;
            x *= x;
            n >>= 1;
        }
        return res;
    }

    friend matrix inverse(const matrix &x)
    {
        assert(x.is_square());
        std::size_t n = x.height();
        matrix<K> ext_x(x), idn(identity(n)), ret;
        for(std::size_t i = 0; i < n; ++i)
            ext_x[i].insert(end(ext_x[i]), begin(idn[i]), end(idn[i]));
        std::vector<std::size_t> piv = ext_x.row_canonicalize();
        if(piv.size() < n) return matrix<K>();
        ret.mat.resize(n);
        for(std::size_t i = 0; i < n; ++i)
        {
            ret[i] = std::vector<K>(begin(ext_x[i]) + n, end(ext_x[i]));
        }
        return ret;
    }

    std::vector<std::size_t> row_canonicalize()
    {
        std::vector<std::size_t> pivots;
        std::size_t h = height(), w = width(), rank = 0;
        for(std::size_t j = 0; j < w; ++j)
        {
            bool piv = false;
            for(std::size_t i = rank; i < h; ++i)
            {
                if(mat[i][j])
                {
                    if(piv)
                    {
                        K r = -mat[i][j];
                        for(std::size_t k = j; k < w; ++k)
                        {
                            mat[i][k] += mat[rank][k] * r;
                        }
                    }
                    else
                    {
                        swap(mat[rank], mat[i]);
                        K r = mat[rank][j];
                        for(std::size_t k = j; k < w; ++k)
                        {
                            mat[rank][k] /= r;
                        }
                        for(std::size_t k = 0; k < rank; ++k)
                        {
                            r = -mat[k][j];
                            for(std::size_t l = j; l < w; ++l)
                            {
                                mat[k][l] += mat[rank][l] * r;
                            }
                        }
                        piv = true;
                    }
                }
            }
            if(piv)
            {
                pivots.emplace_back(j);
                ++rank;
            }
        }
        return pivots;
    }

    K det() const
    {
        matrix<K> x(*this);
        assert(is_square());
        std::size_t n = height();
        K res(1);
        for(std::size_t j = 0; j < n; ++j)
        {
            bool piv = false;
            for(std::size_t i = j; i < n; ++i)
            {
                if(x[i][j])
                {
                    if(piv)
                    {
                        const K r = -x[i][j];
                        for(std::size_t k = j; k < n; ++k)
                        {
                            x[i][k] += x[j][k] * r;
                        }
                    }
                    else
                    {
                        swap(x[i], x[j]);
                        if(i != j) res = -res;
                        const K r = x[j][j];
                        res *= r;
                        for(std::size_t k = j; k < n; ++k)
                        {
                            x[j][k] /= r;
                        }
                        piv = true;
                    }
                }
            }
            if(not piv)
            {
                return K(0);
            }
        }
        return res;
    }

    friend std::istream &operator>>(std::istream &s, matrix &x)
    {
        std::size_t h = x.height(), w = x.width();
        for(std::size_t i = 0; i < h; ++i)
        {
            for(std::size_t j = 0; j < w; ++j)
            {
                s >> x[i][j];
            }
        }
        return s;
    }

    friend std::ostream &operator<<(std::ostream &s, const matrix &x)
    {
        std::size_t h = x.height(), w = x.width();
        for(std::size_t i = 0; i < h; ++i)
        {
            if(i) s << "\n";
            for(std::size_t j = 0; j < w; ++j)
            {
                s << (j ? " " : "") << x.mat[i][j];
            }
        }
        return s;
    }
};