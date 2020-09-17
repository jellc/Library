---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 1 \"data_structure/convex_hull_trick/monotone.hpp\"\n#include\
    \ <cassert>\n#include <vector>\n\ntemplate <class T = long long>\nclass lower_convex_monotone\n\
    {\n    struct line\n    {\n        T slop, icpt;\n        T eval(const T x) const\
    \ { return slop * x + icpt; }\n    };\n\n    std::vector<line> lines;\n    typename\
    \ std::vector<line>::iterator lp, rp;\n\n    void realloc()\n    {\n        std::vector<line>\
    \ cpy((rp - lp) * 2);\n        cpy.swap(lines);\n        rp = copy(lp, rp, lines.begin());\n\
    \        lp = lines.begin();\n    }\n\npublic:\n    lower_convex_monotone() :\
    \ lines(2), lp(lines.begin()), rp(lp) {}\n\n    bool empty() const { return lp\
    \ == rp; }\n\n    void clear() { rp = lp = lines.begin(); }\n\n    void add(const\
    \ T a, const T b)\n    {\n        while(rp - lp > 1)\n        {\n            auto\
    \ [a1, b1] = *(rp - 1);\n            auto [a2, b2] = *(rp - 2);\n            if((b\
    \ - b1) * (a2 - a) > (b - b2) * (a1 - a)) break;\n            --rp;\n        }\n\
    \        if(rp == lp) rp = lp = lines.begin();\n        if(rp == lines.end())\
    \ realloc();\n        *rp++ = {a, b};\n    }\n\n    T get(const T x)\n    {\n\
    \        assert(!empty());\n        while(rp - lp > 1 && lp->eval(x) > (lp + 1)->eval(x))\
    \ ++lp;\n        return lp->eval(x);\n    }\n}; // class lower_convex_monotone\n"
  code: "#include <cassert>\n#include <vector>\n\ntemplate <class T = long long>\n\
    class lower_convex_monotone\n{\n    struct line\n    {\n        T slop, icpt;\n\
    \        T eval(const T x) const { return slop * x + icpt; }\n    };\n\n    std::vector<line>\
    \ lines;\n    typename std::vector<line>::iterator lp, rp;\n\n    void realloc()\n\
    \    {\n        std::vector<line> cpy((rp - lp) * 2);\n        cpy.swap(lines);\n\
    \        rp = copy(lp, rp, lines.begin());\n        lp = lines.begin();\n    }\n\
    \npublic:\n    lower_convex_monotone() : lines(2), lp(lines.begin()), rp(lp) {}\n\
    \n    bool empty() const { return lp == rp; }\n\n    void clear() { rp = lp =\
    \ lines.begin(); }\n\n    void add(const T a, const T b)\n    {\n        while(rp\
    \ - lp > 1)\n        {\n            auto [a1, b1] = *(rp - 1);\n            auto\
    \ [a2, b2] = *(rp - 2);\n            if((b - b1) * (a2 - a) > (b - b2) * (a1 -\
    \ a)) break;\n            --rp;\n        }\n        if(rp == lp) rp = lp = lines.begin();\n\
    \        if(rp == lines.end()) realloc();\n        *rp++ = {a, b};\n    }\n\n\
    \    T get(const T x)\n    {\n        assert(!empty());\n        while(rp - lp\
    \ > 1 && lp->eval(x) > (lp + 1)->eval(x)) ++lp;\n        return lp->eval(x);\n\
    \    }\n}; // class lower_convex_monotone\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/convex_hull_trick/monotone.hpp
  requiredBy: []
  timestamp: '2020-07-27 21:53:08+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: data_structure/convex_hull_trick/monotone.hpp
layout: document
redirect_from:
- /library/data_structure/convex_hull_trick/monotone.hpp
- /library/data_structure/convex_hull_trick/monotone.hpp.html
title: data_structure/convex_hull_trick/monotone.hpp
---
