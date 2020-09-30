---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/library-checker/range_kth_smallest.test.cpp
    title: test/library-checker/range_kth_smallest.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/static_range_inversions_query.test.cpp
    title: test/library-checker/static_range_inversions_query.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"data_structure/Mo.hpp\"\n#include <cassert>\n#include <cmath>\n\
    #include <functional>\n#include <vector>\n\ntemplate <class Add, class Del>\n\
    class Mo\n{\n    Add add; Del del;\n    std::vector<size_t> lft, rgt, ord;\n \
    \   std::vector<size_t>::iterator itr;\n    bool made;\n    size_t width, nl,\
    \ nr;\n\n    void make()\n    {\n        made = true;\n        ord.resize(size());\n\
    \        for(size_t i = 0; i != size(); ++i) ord[i] = i;\n        std::sort(ord.begin(),\
    \ ord.end(),\n        [&](size_t x, size_t y)\n        {\n            if(lft[x]\
    \ / width != lft[y] / width) return lft[x] < lft[y];\n            return rgt[x]\
    \ < rgt[y];\n        });\n        itr = ord.begin();\n    }\n\npublic:\n    Mo(size_t\
    \ n = 0, Add add = Add(), Del del = Del())\n        : add(add), del(del), made(),\
    \ width(sqrt(n)), nl(), nr() {}\n\n    size_t size() const { return lft.size();\
    \ }\n\n    void set(size_t l, size_t r)\n    {\n        assert(!made);\n     \
    \   lft.emplace_back(l), rgt.emplace_back(r);\n    }\n\n    size_t process()\n\
    \    {\n        if(!made) make();\n        if(itr == ord.end()) return ord.size();\n\
    \        const size_t id = *itr++, l = lft[id], r = rgt[id];\n        while(nl\
    \ > l) add(--nl);\n        while(nr < r) add(nr++);\n        while(nl < l) del(nl++);\n\
    \        while(nr > r) del(--nr);\n        return id;\n    }\n};\n"
  code: "#include <cassert>\n#include <cmath>\n#include <functional>\n#include <vector>\n\
    \ntemplate <class Add, class Del>\nclass Mo\n{\n    Add add; Del del;\n    std::vector<size_t>\
    \ lft, rgt, ord;\n    std::vector<size_t>::iterator itr;\n    bool made;\n   \
    \ size_t width, nl, nr;\n\n    void make()\n    {\n        made = true;\n    \
    \    ord.resize(size());\n        for(size_t i = 0; i != size(); ++i) ord[i] =\
    \ i;\n        std::sort(ord.begin(), ord.end(),\n        [&](size_t x, size_t\
    \ y)\n        {\n            if(lft[x] / width != lft[y] / width) return lft[x]\
    \ < lft[y];\n            return rgt[x] < rgt[y];\n        });\n        itr = ord.begin();\n\
    \    }\n\npublic:\n    Mo(size_t n = 0, Add add = Add(), Del del = Del())\n  \
    \      : add(add), del(del), made(), width(sqrt(n)), nl(), nr() {}\n\n    size_t\
    \ size() const { return lft.size(); }\n\n    void set(size_t l, size_t r)\n  \
    \  {\n        assert(!made);\n        lft.emplace_back(l), rgt.emplace_back(r);\n\
    \    }\n\n    size_t process()\n    {\n        if(!made) make();\n        if(itr\
    \ == ord.end()) return ord.size();\n        const size_t id = *itr++, l = lft[id],\
    \ r = rgt[id];\n        while(nl > l) add(--nl);\n        while(nr < r) add(nr++);\n\
    \        while(nl < l) del(nl++);\n        while(nr > r) del(--nr);\n        return\
    \ id;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/Mo.hpp
  requiredBy: []
  timestamp: '2020-08-03 02:47:43+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/static_range_inversions_query.test.cpp
  - test/library-checker/range_kth_smallest.test.cpp
documentation_of: data_structure/Mo.hpp
layout: document
redirect_from:
- /library/data_structure/Mo.hpp
- /library/data_structure/Mo.hpp.html
title: data_structure/Mo.hpp
---
