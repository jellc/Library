//verified at https://atcoder.jp/contests/atc001/submissions/5000204

#include <bits/stdc++.h>
using namespace std;

constexpr long double Pi = 3.14159265358979323;

namespace FFT {
    template <class Real>
    vector<complex<Real>> fft(vector<complex<Real>> x, bool inverse = false) {
        size_t n = x.size(),mask = n - 1;   //"n" must be a power of two.
        static vector<complex<Real>> tmp;
        tmp.resize(n);
        for(size_t i = n >> 1; i; i >>= 1) {
            Real theta = Pi * 2 * i * (inverse ? -1 : 1) / n;
            complex<Real> zeta(cos(theta),sin(theta));
            complex<Real> powzeta = 1;
            for(size_t j = 0; j < n; j += i) {
                for(size_t k = 0; k < i; ++k) {
                    tmp[j + k] = x[k + (mask & j << 1)] + powzeta * x[k + (mask & i + (j << 1))];
                }
                powzeta *= zeta;
            }
            swap(x,tmp);
        }
        if(inverse) for(size_t i = 0; i < n; ++i) x[i] /= n;
        return x;
    }

    template <class T>
    vector<T> conv(const vector<T> &a, const vector<T> &b) {
        size_t n = 1;
        while(n + 1 < a.size() + b.size()) n <<= 1;
        vector<complex<double>> x(n),y(n);
        for(size_t i = 0; i != a.size(); ++i) x[i].real(a[i]);
        for(size_t i = 0; i != b.size(); ++i) x[i].imag(b[i]);
        x = fft(x,false);
        for(int i = 0; i < n; ++i) {
            int j = i ? n - i : 0;
            y[i] = (x[i] + conj(x[j])) * (x[i] - conj(x[j])) * complex<double>(0,-.25);
        }
        y = fft(y,true);
        vector<T> c(n);
        for(size_t i = 0; i < n; ++i) c[i] = y[i].real();
        return c;
    }

    template <>
    vector<int_fast64_t> conv(const vector<int_fast64_t> &a, const vector<int_fast64_t> &b) {
        size_t n = 1;
        while(n + 1 < a.size() + b.size()) n <<= 1;
        vector<complex<double>> x(n),y(n);
        for(size_t i = 0; i != a.size(); ++i) x[i].real(a[i]);
        for(size_t i = 0; i != b.size(); ++i) x[i].imag(b[i]);
        x = fft(x,false);
        for(int i = 0; i < n; ++i) {
            int j = i ? n - i : 0;
            y[i] = (x[i] + conj(x[j])) * (x[i] - conj(x[j])) * complex<double>(0,-.25);
        }
        y = fft(y,true);
        vector<int_fast64_t> c(n);
        for(size_t i = 0; i < n; ++i) c[i] = round(y[i].real());
        return c;
    }

    template <>
    vector<int> conv(const vector<int> &a, const vector<int> &b) {
        size_t n = 1;
        while(n + 1 < a.size() + b.size()) n <<= 1;
        vector<complex<double>> x(n),y(n);
        for(size_t i = 0; i != a.size(); ++i) x[i].real(a[i]);
        for(size_t i = 0; i != b.size(); ++i) x[i].imag(b[i]);
        x = fft(x,false);
        for(int i = 0; i < n; ++i) {
            int j = i ? n - i : 0;
            y[i] = (x[i] + conj(x[j])) * (x[i] - conj(x[j])) * complex<double>(0,-.25);
        }
        y = fft(y,true);
        vector<int> c(n);
        for(size_t i = 0; i < n; ++i) c[i] = round(y[i].real());
        return c;
    }
}


