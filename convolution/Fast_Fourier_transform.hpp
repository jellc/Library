#ifndef Fast_Fourier_transform_hpp
#define Fast_Fourier_transform_hpp

#include <algorithm>
#include <cassert>
#include <complex>
#include <iostream>
#include <vector>

namespace fast_Fourier_transform
{
    using real_t = double;

    class cmplx_t
    {
        real_t re, im;
        friend constexpr cmplx_t conj(cmplx_t x) { return x.im = -x.im, x; }
        friend std::istream &operator>>(std::istream &s, cmplx_t &x) { return s >> x.re >> x.im; }
        friend std::ostream &operator<<(std::ostream &s, const cmplx_t &x) { return s << x.re << ' ' << x.im; }
      public:
        constexpr cmplx_t() : re{real_t{}}, im{real_t{}} {}
        constexpr cmplx_t(real_t _re) : re{_re}, im{real_t{}} {}
        constexpr cmplx_t(real_t _re, real_t _im) : re{_re}, im{_im} {}
        constexpr cmplx_t(std::complex<real_t> x) : re{x.real()}, im{x.imag()} {}
        constexpr real_t real() const { return re; }
        constexpr void real(const real_t _re) { re = _re; }
        constexpr real_t imag() const { return im; }
        constexpr void imag(const real_t _im) { im = _im; }
        constexpr cmplx_t operator-() const { return cmplx_t(-re, -im); }
        constexpr cmplx_t &operator+=(const cmplx_t &x) { return re += x.re, im += x.im, *this; }
        constexpr cmplx_t &operator-=(const cmplx_t &x) { return *this += -x; }
        constexpr cmplx_t &operator*=(const cmplx_t &x) { real_t _re{re * x.re - im * x.im}; return im = im * x.re + x.im * re, re = _re, *this; }
        constexpr cmplx_t &operator*=(real_t x) { return re *= x, im *= x, *this; }
        constexpr cmplx_t &operator/=(const cmplx_t &x) { return conj(*this) /= re * re + im * im; }
        constexpr cmplx_t &operator/=(real_t x) { return re /= x, im /= x, *this; }
        constexpr cmplx_t operator+(const cmplx_t &x) const { return cmplx_t(*this) += x; }
        constexpr cmplx_t operator-(const cmplx_t &x) const { return cmplx_t(*this) -= x; }
        constexpr cmplx_t operator*(const cmplx_t &x) const { return cmplx_t(*this) *= x; }
        constexpr cmplx_t operator*(real_t x) const { return cmplx_t(*this) *= x; }
        constexpr cmplx_t operator/(const cmplx_t &x) const { return cmplx_t(*this) /= x; }
        constexpr cmplx_t operator/(real_t x) const { return cmplx_t(*this) /= x; }
    };

    using poly_t = std::vector<cmplx_t>;

    void discrete_Fourier_transform(poly_t &f)
    {
        const size_t n{f.size()}, mask{n - 1};
        assert(__builtin_popcount(n) == 1); // degree of f must be a power of two.
        static poly_t g; g.resize(n);
        constexpr cmplx_t zeta[31] =
        {
            {1, 0}, {-1, 0}, {0, 1},
            {0.70710678118654752438189403651, 0.70710678118654752443610414514},
            {0.92387953251128675610142140795, 0.38268343236508977172325753068},
            {0.98078528040323044911909938781, 0.19509032201612826785692544201},
            {0.99518472667219688623102546998, 0.09801714032956060199569840382},
            {0.99879545620517239270077028412, 0.04906767432741801425693899119},
            {0.99969881869620422009748220149, 0.02454122852291228803212346128},
            {0.99992470183914454093764001552, 0.01227153828571992607945510345},
            {0.99998117528260114264494415325, 0.00613588464915447535972750246},
            {0.99999529380957617150137498041, 0.00306795676296597627029751672},
            {0.99999882345170190993313003025, 0.00153398018628476561237225788},
            {0.99999970586288221914474799723, 0.00076699031874270452695124765},
            {0.99999992646571785113833452651, 0.00038349518757139558906815188},
            {0.99999998161642929381167504976, 0.00019174759731070330743679009},
            {0.99999999540410731290905263501, 0.00009587379909597734587360460},
            {0.99999999885102682753608427379, 0.00004793689960306688454884772},
            {0.99999999971275670682981095982, 0.00002396844980841821872882467},
            {0.99999999992818917670745273995, 0.00001198422490506970642183282},
            {0.99999999998204729416331065783, 0.00000599211245264242784278378},
            {0.99999999999551182356793271877, 0.00000299605622633466075058210},
            {0.99999999999887795586487812538, 0.00000149802811316901122883643},
            {0.99999999999971948897977205850, 0.00000074901405658471572113723},
            {0.99999999999992987223139048746, 0.00000037450702829238412391495},
            {0.99999999999998246807140014902, 0.00000018725351414619534486931},
            {0.99999999999999561700429751010, 0.00000009362675707309808280024},
            {0.99999999999999890425107437752, 0.00000004681337853654909269501},
            {0.99999999999999972607632112153, 0.00000002340668926827455275977},
            {0.99999999999999993153263280754, 0.00000001170334463413727718121},
            {0.99999999999999998286960567472, 0.00000000585167231706863869077}
        };
        for(size_t i{n >> 1}, ii{1}; i; i >>= 1, ++ii, swap(f, g))
        {
            cmplx_t powzeta{1};
            for(size_t j{}; j != n; powzeta *= zeta[ii])
                for(size_t k{}, x{mask & j << 1}, y{mask & (i + (j << 1))}; k != i; ++k, ++j, ++x, ++y)
                    g[j] = f[x] + powzeta * f[y];
        }
    }

    void inverse_discrete_Fourier_transform(poly_t &f) { discrete_Fourier_transform(f), reverse(next(f.begin()), f.end()); for(cmplx_t &e : f) e /= f.size(); }

    poly_t convolute(poly_t f, poly_t g)
    {
        if(f.empty() || g.empty()) return poly_t();
        const size_t deg_f{f.size() - 1}, deg_g{g.size() - 1}, deg_h{deg_f + deg_g}, n(1u << (32 - __builtin_clz(deg_h)));
        static poly_t h;
        f.resize(n, 0), g.resize(n, 0), h.resize(n);
        discrete_Fourier_transform(f), discrete_Fourier_transform(g);
        for(size_t i{}; i < n; ++i) h[i] = f[i] * g[i];
        inverse_discrete_Fourier_transform(h); h.resize(deg_h + 1);
        return h;
    }

    std::vector<real_t> convolute(const std::vector<real_t> &f, const std::vector<real_t> &g)
    {
        if(f.empty() || g.empty()) return std::vector<real_t>();
        const size_t deg_f{f.size() - 1}, deg_g{g.size() - 1}, deg_h{deg_f + deg_g}, n(1u << (32 - __builtin_clz(deg_h)));
        static std::vector<real_t> h; h.resize(deg_h + 1);
        static poly_t p; p.assign(n, 0);
        for(size_t i{}; i <= deg_f; ++i) p[i].real(f[i]);
        for(size_t i{}; i <= deg_g; ++i) p[i].imag(g[i]);
        discrete_Fourier_transform(p); // perform discrete Fourier transform on p = f + i*g.
        static poly_t q; q.resize(n);
        for(size_t i{}; i < n; ++i) { size_t j{i ? n - i : 0}; q[i] = (p[i] + conj(p[j])) * (p[i] - conj(p[j])); }
        inverse_discrete_Fourier_transform(q);
        for(size_t i{}; i <= deg_h; ++i) h[i] = q[i].imag() / 4;
        return h;
    }

    std::vector<int_least64_t> convolute(const std::vector<int_least64_t> &f, const std::vector<int_least64_t> &g)
    {
        if(f.empty() || g.empty()) return std::vector<int_least64_t>();
        const size_t deg_f{f.size() - 1}, deg_g{g.size() - 1}, deg_h{deg_f + deg_g}, n(1u << (32 - __builtin_clz(deg_h)));
        static std::vector<int_least64_t> h; h.resize(deg_h + 1);
        static poly_t p; p.assign(n, 0);
        for(size_t i{}; i <= deg_f; ++i) p[i].real(f[i]);
        for(size_t i{}; i <= deg_g; ++i) p[i].imag(g[i]);
        discrete_Fourier_transform(p); // perform discrete Fourier transform on p = f + i*g.
        static poly_t q; q.resize(n);
        for(size_t i{}; i < n; ++i) { size_t j{i ? n - i : 0}; q[i] = (p[i] + conj(p[j])) * (p[i] - conj(p[j])); }
        inverse_discrete_Fourier_transform(q);
        for(size_t i{}; i <= deg_h; ++i) h[i] = round(q[i].imag() / 4);
        return h;
    }

    std::vector<int_least32_t> convolute(const std::vector<int_least32_t> &f, const std::vector<int_least32_t> &g)
    {
        if(f.empty() || g.empty()) return std::vector<int_least32_t>();
        const size_t deg_f{f.size() - 1}, deg_g{g.size() - 1}, deg_h{deg_f + deg_g}, n(1u << (32 - __builtin_clz(deg_h)));
        static std::vector<int_least32_t> h; h.resize(deg_h + 1);
        static poly_t p; p.assign(n, 0);
        for(size_t i{}; i <= deg_f; ++i) p[i].real(f[i]);
        for(size_t i{}; i <= deg_g; ++i) p[i].imag(g[i]);
        discrete_Fourier_transform(p); // perform discrete Fourier transform on p = f + i*g.
        static poly_t q; q.resize(n);
        for(size_t i{}; i < n; ++i) { size_t j{i ? n - i : 0}; q[i] = (p[i] + conj(p[j])) * (p[i] - conj(p[j])); }
        inverse_discrete_Fourier_transform(q);
        for(size_t i{}; i <= deg_h; ++i) h[i] = round(q[i].imag() / 4);
        return h;
    }
} // namespace fast_Fourier_transform

#endif // Fast_Fourier_transform_hpp
