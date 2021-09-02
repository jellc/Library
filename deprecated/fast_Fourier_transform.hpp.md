---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"deprecated/fast_Fourier_transform.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <complex>\n#include <iostream>\n#include\
    \ <vector>\n\nnamespace fast_Fourier_transform\n{\n    using real_t = double;\n\
    \n    class cmplx_t\n    {\n        real_t re, im;\n        friend constexpr cmplx_t\
    \ conj(cmplx_t x) { return x.im = -x.im, x; }\n        friend std::istream &operator>>(std::istream\
    \ &s, cmplx_t &x) { return s >> x.re >> x.im; }\n        friend std::ostream &operator<<(std::ostream\
    \ &s, const cmplx_t &x) { return s << x.re << ' ' << x.im; }\n      public:\n\
    \        constexpr cmplx_t() : re{real_t{}}, im{real_t{}} {}\n        constexpr\
    \ cmplx_t(real_t _re) : re{_re}, im{real_t{}} {}\n        constexpr cmplx_t(real_t\
    \ _re, real_t _im) : re{_re}, im{_im} {}\n        constexpr cmplx_t(std::complex<real_t>\
    \ x) : re{x.real()}, im{x.imag()} {}\n        constexpr real_t real() const {\
    \ return re; }\n        constexpr void real(const real_t _re) { re = _re; }\n\
    \        constexpr real_t imag() const { return im; }\n        constexpr void\
    \ imag(const real_t _im) { im = _im; }\n        constexpr cmplx_t operator-()\
    \ const { return cmplx_t(-re, -im); }\n        constexpr cmplx_t &operator+=(const\
    \ cmplx_t &x) { return re += x.re, im += x.im, *this; }\n        constexpr cmplx_t\
    \ &operator-=(const cmplx_t &x) { return *this += -x; }\n        constexpr cmplx_t\
    \ &operator*=(const cmplx_t &x) { real_t _re{re * x.re - im * x.im}; return im\
    \ = im * x.re + x.im * re, re = _re, *this; }\n        constexpr cmplx_t &operator*=(real_t\
    \ x) { return re *= x, im *= x, *this; }\n        constexpr cmplx_t &operator/=(const\
    \ cmplx_t &x) { return conj(*this) /= re * re + im * im; }\n        constexpr\
    \ cmplx_t &operator/=(real_t x) { return re /= x, im /= x, *this; }\n        constexpr\
    \ cmplx_t operator+(const cmplx_t &x) const { return cmplx_t(*this) += x; }\n\
    \        constexpr cmplx_t operator-(const cmplx_t &x) const { return cmplx_t(*this)\
    \ -= x; }\n        constexpr cmplx_t operator*(const cmplx_t &x) const { return\
    \ cmplx_t(*this) *= x; }\n        constexpr cmplx_t operator*(real_t x) const\
    \ { return cmplx_t(*this) *= x; }\n        constexpr cmplx_t operator/(const cmplx_t\
    \ &x) const { return cmplx_t(*this) /= x; }\n        constexpr cmplx_t operator/(real_t\
    \ x) const { return cmplx_t(*this) /= x; }\n    };\n\n    using poly_t = std::vector<cmplx_t>;\n\
    \n    void discrete_Fourier_transform(poly_t &f)\n    {\n        const size_t\
    \ n{f.size()}, mask{n - 1};\n        assert(__builtin_popcount(n) == 1); // degree\
    \ of f must be a power of two.\n        static poly_t g; g.resize(n);\n      \
    \  constexpr cmplx_t zeta[31] =\n        {\n            {1, 0}, {-1, 0}, {0, 1},\n\
    \            {0.70710678118654752438189403651, 0.70710678118654752443610414514},\n\
    \            {0.92387953251128675610142140795, 0.38268343236508977172325753068},\n\
    \            {0.98078528040323044911909938781, 0.19509032201612826785692544201},\n\
    \            {0.99518472667219688623102546998, 0.09801714032956060199569840382},\n\
    \            {0.99879545620517239270077028412, 0.04906767432741801425693899119},\n\
    \            {0.99969881869620422009748220149, 0.02454122852291228803212346128},\n\
    \            {0.99992470183914454093764001552, 0.01227153828571992607945510345},\n\
    \            {0.99998117528260114264494415325, 0.00613588464915447535972750246},\n\
    \            {0.99999529380957617150137498041, 0.00306795676296597627029751672},\n\
    \            {0.99999882345170190993313003025, 0.00153398018628476561237225788},\n\
    \            {0.99999970586288221914474799723, 0.00076699031874270452695124765},\n\
    \            {0.99999992646571785113833452651, 0.00038349518757139558906815188},\n\
    \            {0.99999998161642929381167504976, 0.00019174759731070330743679009},\n\
    \            {0.99999999540410731290905263501, 0.00009587379909597734587360460},\n\
    \            {0.99999999885102682753608427379, 0.00004793689960306688454884772},\n\
    \            {0.99999999971275670682981095982, 0.00002396844980841821872882467},\n\
    \            {0.99999999992818917670745273995, 0.00001198422490506970642183282},\n\
    \            {0.99999999998204729416331065783, 0.00000599211245264242784278378},\n\
    \            {0.99999999999551182356793271877, 0.00000299605622633466075058210},\n\
    \            {0.99999999999887795586487812538, 0.00000149802811316901122883643},\n\
    \            {0.99999999999971948897977205850, 0.00000074901405658471572113723},\n\
    \            {0.99999999999992987223139048746, 0.00000037450702829238412391495},\n\
    \            {0.99999999999998246807140014902, 0.00000018725351414619534486931},\n\
    \            {0.99999999999999561700429751010, 0.00000009362675707309808280024},\n\
    \            {0.99999999999999890425107437752, 0.00000004681337853654909269501},\n\
    \            {0.99999999999999972607632112153, 0.00000002340668926827455275977},\n\
    \            {0.99999999999999993153263280754, 0.00000001170334463413727718121},\n\
    \            {0.99999999999999998286960567472, 0.00000000585167231706863869077}\n\
    \        };\n        for(size_t i{n >> 1}, ii{1}; i; i >>= 1, ++ii, swap(f, g))\n\
    \        {\n            cmplx_t powzeta{1};\n            for(size_t j{}; j !=\
    \ n; powzeta *= zeta[ii])\n                for(size_t k{}, x{mask & j << 1}, y{mask\
    \ & (i + (j << 1))}; k != i; ++k, ++j, ++x, ++y)\n                    g[j] = f[x]\
    \ + powzeta * f[y];\n        }\n    }\n\n    void inverse_discrete_Fourier_transform(poly_t\
    \ &f) { discrete_Fourier_transform(f), reverse(next(f.begin()), f.end()); for(cmplx_t\
    \ &e : f) e /= f.size(); }\n\n    poly_t convolute(poly_t f, poly_t g)\n    {\n\
    \        if(f.empty() || g.empty()) return poly_t();\n        const size_t deg_f{f.size()\
    \ - 1}, deg_g{g.size() - 1}, deg_h{deg_f + deg_g}, n(1u << (32 - __builtin_clz(deg_h)));\n\
    \        static poly_t h;\n        f.resize(n, 0), g.resize(n, 0), h.resize(n);\n\
    \        discrete_Fourier_transform(f), discrete_Fourier_transform(g);\n     \
    \   for(size_t i{}; i < n; ++i) h[i] = f[i] * g[i];\n        inverse_discrete_Fourier_transform(h);\
    \ h.resize(deg_h + 1);\n        return h;\n    }\n\n    std::vector<real_t> convolute(const\
    \ std::vector<real_t> &f, const std::vector<real_t> &g)\n    {\n        if(f.empty()\
    \ || g.empty()) return std::vector<real_t>();\n        const size_t deg_f{f.size()\
    \ - 1}, deg_g{g.size() - 1}, deg_h{deg_f + deg_g}, n(1u << (32 - __builtin_clz(deg_h)));\n\
    \        static std::vector<real_t> h; h.resize(deg_h + 1);\n        static poly_t\
    \ p; p.assign(n, 0);\n        for(size_t i{}; i <= deg_f; ++i) p[i].real(f[i]);\n\
    \        for(size_t i{}; i <= deg_g; ++i) p[i].imag(g[i]);\n        discrete_Fourier_transform(p);\
    \ // perform discrete Fourier transform on p = f + i*g.\n        static poly_t\
    \ q; q.resize(n);\n        for(size_t i{}; i < n; ++i) { size_t j{i ? n - i :\
    \ 0}; q[i] = (p[i] + conj(p[j])) * (p[i] - conj(p[j])); }\n        inverse_discrete_Fourier_transform(q);\n\
    \        for(size_t i{}; i <= deg_h; ++i) h[i] = q[i].imag() / 4;\n        return\
    \ h;\n    }\n\n    std::vector<int_least64_t> convolute(const std::vector<int_least64_t>\
    \ &f, const std::vector<int_least64_t> &g)\n    {\n        if(f.empty() || g.empty())\
    \ return std::vector<int_least64_t>();\n        const size_t deg_f{f.size() -\
    \ 1}, deg_g{g.size() - 1}, deg_h{deg_f + deg_g}, n(1u << (32 - __builtin_clz(deg_h)));\n\
    \        static std::vector<int_least64_t> h; h.resize(deg_h + 1);\n        static\
    \ poly_t p; p.assign(n, 0);\n        for(size_t i{}; i <= deg_f; ++i) p[i].real(f[i]);\n\
    \        for(size_t i{}; i <= deg_g; ++i) p[i].imag(g[i]);\n        discrete_Fourier_transform(p);\
    \ // perform discrete Fourier transform on p = f + i*g.\n        static poly_t\
    \ q; q.resize(n);\n        for(size_t i{}; i < n; ++i) { size_t j{i ? n - i :\
    \ 0}; q[i] = (p[i] + conj(p[j])) * (p[i] - conj(p[j])); }\n        inverse_discrete_Fourier_transform(q);\n\
    \        for(size_t i{}; i <= deg_h; ++i) h[i] = round(q[i].imag() / 4);\n   \
    \     return h;\n    }\n\n    std::vector<int_least32_t> convolute(const std::vector<int_least32_t>\
    \ &f, const std::vector<int_least32_t> &g)\n    {\n        if(f.empty() || g.empty())\
    \ return std::vector<int_least32_t>();\n        const size_t deg_f{f.size() -\
    \ 1}, deg_g{g.size() - 1}, deg_h{deg_f + deg_g}, n(1u << (32 - __builtin_clz(deg_h)));\n\
    \        static std::vector<int_least32_t> h; h.resize(deg_h + 1);\n        static\
    \ poly_t p; p.assign(n, 0);\n        for(size_t i{}; i <= deg_f; ++i) p[i].real(f[i]);\n\
    \        for(size_t i{}; i <= deg_g; ++i) p[i].imag(g[i]);\n        discrete_Fourier_transform(p);\
    \ // perform discrete Fourier transform on p = f + i*g.\n        static poly_t\
    \ q; q.resize(n);\n        for(size_t i{}; i < n; ++i) { size_t j{i ? n - i :\
    \ 0}; q[i] = (p[i] + conj(p[j])) * (p[i] - conj(p[j])); }\n        inverse_discrete_Fourier_transform(q);\n\
    \        for(size_t i{}; i <= deg_h; ++i) h[i] = round(q[i].imag() / 4);\n   \
    \     return h;\n    }\n} // namespace fast_Fourier_transform\n\n\n"
  code: "#ifndef fast_Fourier_transform_hpp\n#define fast_Fourier_transform_hpp\n\n\
    #include <algorithm>\n#include <cassert>\n#include <complex>\n#include <iostream>\n\
    #include <vector>\n\nnamespace fast_Fourier_transform\n{\n    using real_t = double;\n\
    \n    class cmplx_t\n    {\n        real_t re, im;\n        friend constexpr cmplx_t\
    \ conj(cmplx_t x) { return x.im = -x.im, x; }\n        friend std::istream &operator>>(std::istream\
    \ &s, cmplx_t &x) { return s >> x.re >> x.im; }\n        friend std::ostream &operator<<(std::ostream\
    \ &s, const cmplx_t &x) { return s << x.re << ' ' << x.im; }\n      public:\n\
    \        constexpr cmplx_t() : re{real_t{}}, im{real_t{}} {}\n        constexpr\
    \ cmplx_t(real_t _re) : re{_re}, im{real_t{}} {}\n        constexpr cmplx_t(real_t\
    \ _re, real_t _im) : re{_re}, im{_im} {}\n        constexpr cmplx_t(std::complex<real_t>\
    \ x) : re{x.real()}, im{x.imag()} {}\n        constexpr real_t real() const {\
    \ return re; }\n        constexpr void real(const real_t _re) { re = _re; }\n\
    \        constexpr real_t imag() const { return im; }\n        constexpr void\
    \ imag(const real_t _im) { im = _im; }\n        constexpr cmplx_t operator-()\
    \ const { return cmplx_t(-re, -im); }\n        constexpr cmplx_t &operator+=(const\
    \ cmplx_t &x) { return re += x.re, im += x.im, *this; }\n        constexpr cmplx_t\
    \ &operator-=(const cmplx_t &x) { return *this += -x; }\n        constexpr cmplx_t\
    \ &operator*=(const cmplx_t &x) { real_t _re{re * x.re - im * x.im}; return im\
    \ = im * x.re + x.im * re, re = _re, *this; }\n        constexpr cmplx_t &operator*=(real_t\
    \ x) { return re *= x, im *= x, *this; }\n        constexpr cmplx_t &operator/=(const\
    \ cmplx_t &x) { return conj(*this) /= re * re + im * im; }\n        constexpr\
    \ cmplx_t &operator/=(real_t x) { return re /= x, im /= x, *this; }\n        constexpr\
    \ cmplx_t operator+(const cmplx_t &x) const { return cmplx_t(*this) += x; }\n\
    \        constexpr cmplx_t operator-(const cmplx_t &x) const { return cmplx_t(*this)\
    \ -= x; }\n        constexpr cmplx_t operator*(const cmplx_t &x) const { return\
    \ cmplx_t(*this) *= x; }\n        constexpr cmplx_t operator*(real_t x) const\
    \ { return cmplx_t(*this) *= x; }\n        constexpr cmplx_t operator/(const cmplx_t\
    \ &x) const { return cmplx_t(*this) /= x; }\n        constexpr cmplx_t operator/(real_t\
    \ x) const { return cmplx_t(*this) /= x; }\n    };\n\n    using poly_t = std::vector<cmplx_t>;\n\
    \n    void discrete_Fourier_transform(poly_t &f)\n    {\n        const size_t\
    \ n{f.size()}, mask{n - 1};\n        assert(__builtin_popcount(n) == 1); // degree\
    \ of f must be a power of two.\n        static poly_t g; g.resize(n);\n      \
    \  constexpr cmplx_t zeta[31] =\n        {\n            {1, 0}, {-1, 0}, {0, 1},\n\
    \            {0.70710678118654752438189403651, 0.70710678118654752443610414514},\n\
    \            {0.92387953251128675610142140795, 0.38268343236508977172325753068},\n\
    \            {0.98078528040323044911909938781, 0.19509032201612826785692544201},\n\
    \            {0.99518472667219688623102546998, 0.09801714032956060199569840382},\n\
    \            {0.99879545620517239270077028412, 0.04906767432741801425693899119},\n\
    \            {0.99969881869620422009748220149, 0.02454122852291228803212346128},\n\
    \            {0.99992470183914454093764001552, 0.01227153828571992607945510345},\n\
    \            {0.99998117528260114264494415325, 0.00613588464915447535972750246},\n\
    \            {0.99999529380957617150137498041, 0.00306795676296597627029751672},\n\
    \            {0.99999882345170190993313003025, 0.00153398018628476561237225788},\n\
    \            {0.99999970586288221914474799723, 0.00076699031874270452695124765},\n\
    \            {0.99999992646571785113833452651, 0.00038349518757139558906815188},\n\
    \            {0.99999998161642929381167504976, 0.00019174759731070330743679009},\n\
    \            {0.99999999540410731290905263501, 0.00009587379909597734587360460},\n\
    \            {0.99999999885102682753608427379, 0.00004793689960306688454884772},\n\
    \            {0.99999999971275670682981095982, 0.00002396844980841821872882467},\n\
    \            {0.99999999992818917670745273995, 0.00001198422490506970642183282},\n\
    \            {0.99999999998204729416331065783, 0.00000599211245264242784278378},\n\
    \            {0.99999999999551182356793271877, 0.00000299605622633466075058210},\n\
    \            {0.99999999999887795586487812538, 0.00000149802811316901122883643},\n\
    \            {0.99999999999971948897977205850, 0.00000074901405658471572113723},\n\
    \            {0.99999999999992987223139048746, 0.00000037450702829238412391495},\n\
    \            {0.99999999999998246807140014902, 0.00000018725351414619534486931},\n\
    \            {0.99999999999999561700429751010, 0.00000009362675707309808280024},\n\
    \            {0.99999999999999890425107437752, 0.00000004681337853654909269501},\n\
    \            {0.99999999999999972607632112153, 0.00000002340668926827455275977},\n\
    \            {0.99999999999999993153263280754, 0.00000001170334463413727718121},\n\
    \            {0.99999999999999998286960567472, 0.00000000585167231706863869077}\n\
    \        };\n        for(size_t i{n >> 1}, ii{1}; i; i >>= 1, ++ii, swap(f, g))\n\
    \        {\n            cmplx_t powzeta{1};\n            for(size_t j{}; j !=\
    \ n; powzeta *= zeta[ii])\n                for(size_t k{}, x{mask & j << 1}, y{mask\
    \ & (i + (j << 1))}; k != i; ++k, ++j, ++x, ++y)\n                    g[j] = f[x]\
    \ + powzeta * f[y];\n        }\n    }\n\n    void inverse_discrete_Fourier_transform(poly_t\
    \ &f) { discrete_Fourier_transform(f), reverse(next(f.begin()), f.end()); for(cmplx_t\
    \ &e : f) e /= f.size(); }\n\n    poly_t convolute(poly_t f, poly_t g)\n    {\n\
    \        if(f.empty() || g.empty()) return poly_t();\n        const size_t deg_f{f.size()\
    \ - 1}, deg_g{g.size() - 1}, deg_h{deg_f + deg_g}, n(1u << (32 - __builtin_clz(deg_h)));\n\
    \        static poly_t h;\n        f.resize(n, 0), g.resize(n, 0), h.resize(n);\n\
    \        discrete_Fourier_transform(f), discrete_Fourier_transform(g);\n     \
    \   for(size_t i{}; i < n; ++i) h[i] = f[i] * g[i];\n        inverse_discrete_Fourier_transform(h);\
    \ h.resize(deg_h + 1);\n        return h;\n    }\n\n    std::vector<real_t> convolute(const\
    \ std::vector<real_t> &f, const std::vector<real_t> &g)\n    {\n        if(f.empty()\
    \ || g.empty()) return std::vector<real_t>();\n        const size_t deg_f{f.size()\
    \ - 1}, deg_g{g.size() - 1}, deg_h{deg_f + deg_g}, n(1u << (32 - __builtin_clz(deg_h)));\n\
    \        static std::vector<real_t> h; h.resize(deg_h + 1);\n        static poly_t\
    \ p; p.assign(n, 0);\n        for(size_t i{}; i <= deg_f; ++i) p[i].real(f[i]);\n\
    \        for(size_t i{}; i <= deg_g; ++i) p[i].imag(g[i]);\n        discrete_Fourier_transform(p);\
    \ // perform discrete Fourier transform on p = f + i*g.\n        static poly_t\
    \ q; q.resize(n);\n        for(size_t i{}; i < n; ++i) { size_t j{i ? n - i :\
    \ 0}; q[i] = (p[i] + conj(p[j])) * (p[i] - conj(p[j])); }\n        inverse_discrete_Fourier_transform(q);\n\
    \        for(size_t i{}; i <= deg_h; ++i) h[i] = q[i].imag() / 4;\n        return\
    \ h;\n    }\n\n    std::vector<int_least64_t> convolute(const std::vector<int_least64_t>\
    \ &f, const std::vector<int_least64_t> &g)\n    {\n        if(f.empty() || g.empty())\
    \ return std::vector<int_least64_t>();\n        const size_t deg_f{f.size() -\
    \ 1}, deg_g{g.size() - 1}, deg_h{deg_f + deg_g}, n(1u << (32 - __builtin_clz(deg_h)));\n\
    \        static std::vector<int_least64_t> h; h.resize(deg_h + 1);\n        static\
    \ poly_t p; p.assign(n, 0);\n        for(size_t i{}; i <= deg_f; ++i) p[i].real(f[i]);\n\
    \        for(size_t i{}; i <= deg_g; ++i) p[i].imag(g[i]);\n        discrete_Fourier_transform(p);\
    \ // perform discrete Fourier transform on p = f + i*g.\n        static poly_t\
    \ q; q.resize(n);\n        for(size_t i{}; i < n; ++i) { size_t j{i ? n - i :\
    \ 0}; q[i] = (p[i] + conj(p[j])) * (p[i] - conj(p[j])); }\n        inverse_discrete_Fourier_transform(q);\n\
    \        for(size_t i{}; i <= deg_h; ++i) h[i] = round(q[i].imag() / 4);\n   \
    \     return h;\n    }\n\n    std::vector<int_least32_t> convolute(const std::vector<int_least32_t>\
    \ &f, const std::vector<int_least32_t> &g)\n    {\n        if(f.empty() || g.empty())\
    \ return std::vector<int_least32_t>();\n        const size_t deg_f{f.size() -\
    \ 1}, deg_g{g.size() - 1}, deg_h{deg_f + deg_g}, n(1u << (32 - __builtin_clz(deg_h)));\n\
    \        static std::vector<int_least32_t> h; h.resize(deg_h + 1);\n        static\
    \ poly_t p; p.assign(n, 0);\n        for(size_t i{}; i <= deg_f; ++i) p[i].real(f[i]);\n\
    \        for(size_t i{}; i <= deg_g; ++i) p[i].imag(g[i]);\n        discrete_Fourier_transform(p);\
    \ // perform discrete Fourier transform on p = f + i*g.\n        static poly_t\
    \ q; q.resize(n);\n        for(size_t i{}; i < n; ++i) { size_t j{i ? n - i :\
    \ 0}; q[i] = (p[i] + conj(p[j])) * (p[i] - conj(p[j])); }\n        inverse_discrete_Fourier_transform(q);\n\
    \        for(size_t i{}; i <= deg_h; ++i) h[i] = round(q[i].imag() / 4);\n   \
    \     return h;\n    }\n} // namespace fast_Fourier_transform\n\n#endif // fast_Fourier_transform_hpp\n"
  dependsOn: []
  isVerificationFile: false
  path: deprecated/fast_Fourier_transform.hpp
  requiredBy: []
  timestamp: '2021-09-03 02:24:16+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: deprecated/fast_Fourier_transform.hpp
layout: document
redirect_from:
- /library/deprecated/fast_Fourier_transform.hpp
- /library/deprecated/fast_Fourier_transform.hpp.html
title: deprecated/fast_Fourier_transform.hpp
---
