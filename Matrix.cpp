#include <bits/stdc++.h>

template <class K>
struct matrix {
    vector<vector<K>> mat;

    matrix() {}
    matrix(size_t h, size_t w, const K v = K()) { assign(h,w,v); }

    void resize(size_t h, size_t w, const K v = K()) { mat.resize(h,vector<K>(w,v)); }

    void assign(size_t h, size_t w, const K v = K()) { mat.assign(h,vector<K>(w,v)); }

    const size_t height() const { return mat.size(); }

    const size_t width() const { return mat.empty() ? 0 : mat[0].size(); }

    vector<K>& operator[](const size_t i) { return mat[i]; }

    static matrix identity(size_t n) {
        matrix ret(n,n);
        for(size_t i = 0; i < n; ++i) ret[i][i] = 1;
        return ret;
    }

    matrix operator-() const {
        matrix ret(*this);
        for(size_t i = 0; i != height(); ++i) {
            for(size_t j = 0; j != width(); ++j) {
                ret[i][j] = -mat[i][j];
            }
        }
        return ret;
    }

    matrix operator&(matrix &x) const { return matrix(*this) &= x; }

    matrix operator|(matrix &x) const { return matrix(*this) |= x; }

    matrix operator^(matrix &x) const { return matrix(*this) ^= x; }

    matrix operator+(matrix &x) const { return matrix(*this) += x; }

    matrix operator-(matrix &x) const { return matrix(*this) -= x; }

    matrix operator*(matrix &x) const { return matrix(*this) *= x; }

    matrix operator&=(matrix &x) {
        for(size_t i = 0; i != height(); ++i) {
            for(size_t j = 0; j != width(); ++j) {
                (*this)[i][j] &= x[i][j];
            }
        }
        return *this;
    }

    matrix operator|=(matrix &x) {
        for(size_t i = 0; i != height(); ++i) {
            for(size_t j = 0; j != width(); ++j) {
                (*this)[i][j] |= x[i][j];
            }
        }
        return *this;
    }

    matrix operator^=(matrix &x) {
        for(size_t i = 0; i != height(); ++i) {
            for(size_t j = 0; j != width(); ++j) {
                (*this)[i][j] ^= x[i][j];
            }
        }
        return *this;
    }

    matrix& operator+=(matrix &x) {
        for(size_t i = 0; i != height(); ++i) {
            for(size_t j = 0; j != width(); ++j) {
                (*this)[i][j] += x[i][j];
            }
        }
        return *this;
    }

    matrix& operator-=(matrix &x) {
        for(size_t i = 0; i != height(); ++i) {
            for(size_t j = 0; j != width(); ++j) {
                (*this)[i][j] -= x[i][j];
            }
        }
        return *this;
    }

    matrix& operator*=(matrix &x) {
        matrix tmp(height(),x.width());
        for(size_t i = 0; i != height(); ++i) {
            for(size_t j = 0; j != x.height(); ++j) {
                 for(size_t k = 0; k != x.width(); ++k) {
                     tmp[i][k] += (*this)[i][j] * x.mat[j][k];
                 }
            }
        }
        return *this = tmp;
    }

    friend istream &operator>>(istream &s, matrix &x) {
        for(size_t i = 0; i != x.height(); ++i) {
            for(size_t j = 0; j != x.width(); ++j) {
                s >> x[i][j];
            }
        }
        return s;
    }

    friend ostream &operator<<(ostream &s, matrix x) {
        for(size_t i = 0; i != x.height(); ++i) {
            if(i) s << "\n";
            for(size_t j = 0; j != x.width(); ++j) {
                s << (j ? " " : "") << x[i][j];
            }
        }
        return s;
    }

    static matrix pow(matrix x, int_fast64_t n) {
        if(n < 0) n = 0;
        matrix ret = identity(x.height());
        while(n) {
            if(n & 1) ret *= x;
            x *= x;
            n >>= 1;
        }
        return ret;
    }

    vector<size_t> row_canonicalize() {
        vector<size_t> pivots;
        int rank = 0;
        for(size_t i = 0; i < width() && rank < height(); ++i) {
            bool piv = false;
            for(size_t j = rank; j < height(); ++j) {
                if(piv) {
                    if(mat[j][i]) {
                        K r = -mat[j][i] / mat[rank][i];
                        for(size_t w = i; w < width(); ++w) {
                            mat[j][w] += mat[rank][w] * r;
                        }
                    }
                } else {
                    if(mat[j][i]) {
                        swap(mat[rank], mat[j]);
                        piv = true;
                    }
                }
            }
            if(piv) {
                K r = mat[rank][i];
                for(size_t j = i; j < width(); ++j) {
                    mat[rank][j] /= r;
                }
                pivots.emplace_back(i);
                ++rank;
            }
        }
        return pivots;
    }
};

