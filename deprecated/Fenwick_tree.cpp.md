---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"deprecated/Fenwick_tree.cpp\"\ntemplate <class Abel>\n//\
    \ Abel must be an abelian group.\nclass Fenwick_tree\n{\n    using ary_t = vector<Abel>;\n\
    \    const size_t n;\n    const Abel identity;\n    ary_t data;\n\n  public:\n\
    \    explicit Fenwick_tree(size_t _n, Abel _identity = Abel()) : n(_n), identity(_identity),\
    \ data(n + 1, identity) {}\n\n    // increment data[i] by x.\n    void inc(size_t\
    \ i, Abel x) { for(++i; i <= n; i += i & -i) data[i] += x; }\n\n    // substitute\
    \ x for data[i].\n    void subs(size_t i, Abel x) { inc(i, x - (*this)[i]); }\n\
    \n    // sum of range [0, i).\n    Abel sum(size_t i) const\n    {\n        Abel\
    \ ret = identity;\n        for(; i; i &= (i - 1)) ret += data[i];\n        return\
    \ ret;\n    }\n\n    // sum of range [l, r).\n    Abel sum(size_t l, size_t r)\
    \ const { return sum(r) - sum(l); }\n\n    // get data[i]\n    Abel operator[](size_t\
    \ i) const { return sum(i + 1) - sum(i); }\n\n    // maximum i where range [0,\
    \ i) meets the condition.\n    size_t bound(const std::function<bool(Abel)> &f)\n\
    \    {\n        Abel now = identity;\n        size_t l = 0, r = n + 1;\n     \
    \   size_t bit = 1;\n        while(bit <= n)\n            bit <<= 1;\n       \
    \ while(r - l > 1)\n        {\n            while(bit >= r - l)\n             \
    \   bit >>= 1;\n            if(f(now + data[l + bit]))\n            {\n      \
    \          now += data[l + bit];\n                l += bit;\n            }\n \
    \           else\n            {\n                r = l + bit;\n            }\n\
    \        }\n        return l;\n    }\n}; // class Fenwick_tree\n\ntemplate <class\
    \ Abel>\n// class Abel must be an abelian group.\nstruct Dynamic_fenwick_tree\n\
    {\n    const size_t n;\n    const Abel identity;\n    std::unordered_map<size_t,\
    \ Abel> data;\n\n    explicit Dynamic_fenwick_tree(size_t _n, Abel _identity =\
    \ Abel())\n        : n(_n), identity(_identity)\n    {}\n\n    void inc(size_t\
    \ i, Abel x)\n    {\n        for(++i; i <= n; i += i & -i)\n        {\n      \
    \      data[i] += x;\n        }\n    }\n\n    void subs(size_t i, Abel x)\n  \
    \  {\n        inc(i, x - (*this)[i]);\n    }\n\n    // sum of range [0, i).\n\
    \    Abel sum(size_t i)\n    {\n        Abel ret = identity;\n        for(; i;\
    \ i &= i - 1)\n        {\n            ret += data[i];\n        }\n        return\
    \ ret;\n    }\n\n    // sum of range [l, r).\n    Abel sum(size_t l, size_t r)\n\
    \    {\n        return l < r ? sum(r) - sum(l) : identity;\n    }\n\n    Abel\
    \ operator[](size_t i)\n    {\n        return sum(i + 1) - sum(i);\n    }\n\n\
    \    // maximum i where range [0, i) meets the condition.\n    size_t bound(const\
    \ std::function<bool(Abel)> &f)\n    {\n        Abel now = identity;\n       \
    \ size_t l = 0, r = n + 1;\n        size_t bit = 1;\n        while(bit <= n)\n\
    \            bit <<= 1;\n        while(r - l > 1)\n        {\n            while(bit\
    \ >= r - l)\n                bit >>= 1;\n            if(f(now + data[l + bit]))\n\
    \            {\n                now += data[l + bit];\n                l += bit;\n\
    \            }\n            else\n            {\n                r = l + bit;\n\
    \            }\n        }\n        return l;\n    }\n}; // class Dynamic_fenwick_tree\n\
    \n#include <bits/stdc++.h>\ntemplate <class Abel, typename index_t = int_fast64_t>\n\
    // class Abel must be an abelian group.\nstruct Bidirectional_fenwick_tree\n{\n\
    \    std::unordered_map<uint_fast64_t, Abel> p_dat, n_dat;\n    const index_t\
    \ inf;\n    const Abel identity;\n\n    explicit Bidirectional_fenwick_tree(\n\
    \        const index_t _inf = std::numeric_limits<index_t>::max(),\n        const\
    \ Abel &_identity = Abel())\n        : inf(_inf), identity(_identity)\n    {}\n\
    \n    void inc(index_t i, Abel x)\n    {\n        if(i >= 0)\n        {\n    \
    \        for(++i; i <= inf; i += i & -i)\n            {\n                p_dat[i]\
    \ += x;\n            }\n        }\n        else\n        {\n            for(i\
    \ = -i; i <= inf; i += i & -i)\n            {\n                n_dat[i] += x;\n\
    \            }\n        }\n    }\n\n    // sum of range [l, r) if l < r, otherwise\
    \ identity.\n    Abel sum(index_t l, index_t r)\n    {\n        Abel res = identity;\n\
    \        res += l >= 0 ? -sum(l) : sum(l);\n        res += r >= 0 ? sum(r) : -sum(r);\n\
    \        return l < r ? res : identity;\n    }\n\n    // sum of range [0, i) for\
    \ i >= 0, [i, 0) for i < 0.\n    Abel sum(index_t i)\n    {\n        Abel res\
    \ = 0;\n        if(i >= 0)\n        {\n            for(; i; i &= i - 1)\n    \
    \        {\n                res += p_dat[i];\n            }\n        }\n     \
    \   else\n        {\n            for(i = -i; i; i &= i - 1)\n            {\n \
    \               res += n_dat[i];\n            }\n        }\n        return res;\n\
    \    }\n};\n"
  code: "template <class Abel>\n// Abel must be an abelian group.\nclass Fenwick_tree\n\
    {\n    using ary_t = vector<Abel>;\n    const size_t n;\n    const Abel identity;\n\
    \    ary_t data;\n\n  public:\n    explicit Fenwick_tree(size_t _n, Abel _identity\
    \ = Abel()) : n(_n), identity(_identity), data(n + 1, identity) {}\n\n    // increment\
    \ data[i] by x.\n    void inc(size_t i, Abel x) { for(++i; i <= n; i += i & -i)\
    \ data[i] += x; }\n\n    // substitute x for data[i].\n    void subs(size_t i,\
    \ Abel x) { inc(i, x - (*this)[i]); }\n\n    // sum of range [0, i).\n    Abel\
    \ sum(size_t i) const\n    {\n        Abel ret = identity;\n        for(; i; i\
    \ &= (i - 1)) ret += data[i];\n        return ret;\n    }\n\n    // sum of range\
    \ [l, r).\n    Abel sum(size_t l, size_t r) const { return sum(r) - sum(l); }\n\
    \n    // get data[i]\n    Abel operator[](size_t i) const { return sum(i + 1)\
    \ - sum(i); }\n\n    // maximum i where range [0, i) meets the condition.\n  \
    \  size_t bound(const std::function<bool(Abel)> &f)\n    {\n        Abel now =\
    \ identity;\n        size_t l = 0, r = n + 1;\n        size_t bit = 1;\n     \
    \   while(bit <= n)\n            bit <<= 1;\n        while(r - l > 1)\n      \
    \  {\n            while(bit >= r - l)\n                bit >>= 1;\n          \
    \  if(f(now + data[l + bit]))\n            {\n                now += data[l +\
    \ bit];\n                l += bit;\n            }\n            else\n        \
    \    {\n                r = l + bit;\n            }\n        }\n        return\
    \ l;\n    }\n}; // class Fenwick_tree\n\ntemplate <class Abel>\n// class Abel\
    \ must be an abelian group.\nstruct Dynamic_fenwick_tree\n{\n    const size_t\
    \ n;\n    const Abel identity;\n    std::unordered_map<size_t, Abel> data;\n\n\
    \    explicit Dynamic_fenwick_tree(size_t _n, Abel _identity = Abel())\n     \
    \   : n(_n), identity(_identity)\n    {}\n\n    void inc(size_t i, Abel x)\n \
    \   {\n        for(++i; i <= n; i += i & -i)\n        {\n            data[i] +=\
    \ x;\n        }\n    }\n\n    void subs(size_t i, Abel x)\n    {\n        inc(i,\
    \ x - (*this)[i]);\n    }\n\n    // sum of range [0, i).\n    Abel sum(size_t\
    \ i)\n    {\n        Abel ret = identity;\n        for(; i; i &= i - 1)\n    \
    \    {\n            ret += data[i];\n        }\n        return ret;\n    }\n\n\
    \    // sum of range [l, r).\n    Abel sum(size_t l, size_t r)\n    {\n      \
    \  return l < r ? sum(r) - sum(l) : identity;\n    }\n\n    Abel operator[](size_t\
    \ i)\n    {\n        return sum(i + 1) - sum(i);\n    }\n\n    // maximum i where\
    \ range [0, i) meets the condition.\n    size_t bound(const std::function<bool(Abel)>\
    \ &f)\n    {\n        Abel now = identity;\n        size_t l = 0, r = n + 1;\n\
    \        size_t bit = 1;\n        while(bit <= n)\n            bit <<= 1;\n  \
    \      while(r - l > 1)\n        {\n            while(bit >= r - l)\n        \
    \        bit >>= 1;\n            if(f(now + data[l + bit]))\n            {\n \
    \               now += data[l + bit];\n                l += bit;\n           \
    \ }\n            else\n            {\n                r = l + bit;\n         \
    \   }\n        }\n        return l;\n    }\n}; // class Dynamic_fenwick_tree\n\
    \n#include <bits/stdc++.h>\ntemplate <class Abel, typename index_t = int_fast64_t>\n\
    // class Abel must be an abelian group.\nstruct Bidirectional_fenwick_tree\n{\n\
    \    std::unordered_map<uint_fast64_t, Abel> p_dat, n_dat;\n    const index_t\
    \ inf;\n    const Abel identity;\n\n    explicit Bidirectional_fenwick_tree(\n\
    \        const index_t _inf = std::numeric_limits<index_t>::max(),\n        const\
    \ Abel &_identity = Abel())\n        : inf(_inf), identity(_identity)\n    {}\n\
    \n    void inc(index_t i, Abel x)\n    {\n        if(i >= 0)\n        {\n    \
    \        for(++i; i <= inf; i += i & -i)\n            {\n                p_dat[i]\
    \ += x;\n            }\n        }\n        else\n        {\n            for(i\
    \ = -i; i <= inf; i += i & -i)\n            {\n                n_dat[i] += x;\n\
    \            }\n        }\n    }\n\n    // sum of range [l, r) if l < r, otherwise\
    \ identity.\n    Abel sum(index_t l, index_t r)\n    {\n        Abel res = identity;\n\
    \        res += l >= 0 ? -sum(l) : sum(l);\n        res += r >= 0 ? sum(r) : -sum(r);\n\
    \        return l < r ? res : identity;\n    }\n\n    // sum of range [0, i) for\
    \ i >= 0, [i, 0) for i < 0.\n    Abel sum(index_t i)\n    {\n        Abel res\
    \ = 0;\n        if(i >= 0)\n        {\n            for(; i; i &= i - 1)\n    \
    \        {\n                res += p_dat[i];\n            }\n        }\n     \
    \   else\n        {\n            for(i = -i; i; i &= i - 1)\n            {\n \
    \               res += n_dat[i];\n            }\n        }\n        return res;\n\
    \    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: deprecated/Fenwick_tree.cpp
  requiredBy: []
  timestamp: '2020-08-08 03:26:16+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: deprecated/Fenwick_tree.cpp
layout: document
redirect_from:
- /library/deprecated/Fenwick_tree.cpp
- /library/deprecated/Fenwick_tree.cpp.html
title: deprecated/Fenwick_tree.cpp
---
