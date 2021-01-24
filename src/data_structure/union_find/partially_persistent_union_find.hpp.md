---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://atcoder.jp/contests/agc002/submissions/9514048
  bundledCode: "#line 1 \"src/data_structure/union_find/partially_persistent_union_find.hpp\"\
    \n// #line 2 \"Partially_persistent_union_find.hpp\"\n// veryfied at https://atcoder.jp/contests/agc002/submissions/9514048\n\
    #ifndef Partially_persistent_union_find_hpp\n#define Partially_persistent_union_find_hpp\n\
    #include <cstdint>\n#include <cstddef>\n#include <numeric>\n#include <vector>\n\
    \nclass partially_persistent_union_find\n{\n    using time_type = uint32_t;\n\
    \    struct log_type { time_type time; size_t size; };\n    const size_t n;\n\
    \    std::vector<size_t> parent;\n    std::vector<time_type> last;\n    std::vector<std::vector<log_type>>\
    \ size_log;\n    time_type clock;\n\npublic:\n    explicit partially_persistent_union_find(size_t\
    \ _n) : n(_n), parent(n), last(n, UINT32_MAX), size_log(n, std::vector<log_type>(1,\
    \ {0, 1})), clock()\n    {\n        std::iota(parent.begin(), parent.end(), 0);\n\
    \    }\n\n    size_t size(size_t x, time_type t = UINT32_MAX)\n    {\n       \
    \ size_t root = find(x, t);\n        auto __ok{size_log[root].begin()}, __ng{size_log[root].end()};\n\
    \        auto dist = __ng - __ok;\n        while(dist > 1)\n        {\n      \
    \      auto mid{__ok + (dist >> 1)};\n            if(mid->time > t) __ng = mid,\
    \ dist >>= 1;\n            else __ok = mid, ++dist >>= 1;\n        }\n       \
    \ return __ok->size;\n    }\n\n    size_t find(size_t x, size_t t = UINT32_MAX)\
    \ { return last[x] >= t ? x : find(parent[x], t); }\n\n    bool same(size_t x,\
    \ size_t y, time_type t = UINT32_MAX) { return find(x, t) == find(y, t); }\n\n\
    \    time_type unite(size_t x, size_t y)\n    {\n        if((x = find(x)) != (y\
    \ = find(y)))\n        {\n            size_t size_x = size_log[x].back().size;\n\
    \            size_t size_y = size_log[y].back().size;\n            if(size_x <\
    \ size_y) std::swap(x, y), std::swap(size_x, size_y);\n            size_log[x].push_back({clock\
    \ + 1, size_x + size_y});\n            parent[y] = x;\n            last[y] = clock;\n\
    \        }\n        return ++clock;\n    }\n}; // class partially_persistent_union_find\n\
    \n#endif\n"
  code: "// #line 2 \"Partially_persistent_union_find.hpp\"\n// veryfied at https://atcoder.jp/contests/agc002/submissions/9514048\n\
    #ifndef Partially_persistent_union_find_hpp\n#define Partially_persistent_union_find_hpp\n\
    #include <cstdint>\n#include <cstddef>\n#include <numeric>\n#include <vector>\n\
    \nclass partially_persistent_union_find\n{\n    using time_type = uint32_t;\n\
    \    struct log_type { time_type time; size_t size; };\n    const size_t n;\n\
    \    std::vector<size_t> parent;\n    std::vector<time_type> last;\n    std::vector<std::vector<log_type>>\
    \ size_log;\n    time_type clock;\n\npublic:\n    explicit partially_persistent_union_find(size_t\
    \ _n) : n(_n), parent(n), last(n, UINT32_MAX), size_log(n, std::vector<log_type>(1,\
    \ {0, 1})), clock()\n    {\n        std::iota(parent.begin(), parent.end(), 0);\n\
    \    }\n\n    size_t size(size_t x, time_type t = UINT32_MAX)\n    {\n       \
    \ size_t root = find(x, t);\n        auto __ok{size_log[root].begin()}, __ng{size_log[root].end()};\n\
    \        auto dist = __ng - __ok;\n        while(dist > 1)\n        {\n      \
    \      auto mid{__ok + (dist >> 1)};\n            if(mid->time > t) __ng = mid,\
    \ dist >>= 1;\n            else __ok = mid, ++dist >>= 1;\n        }\n       \
    \ return __ok->size;\n    }\n\n    size_t find(size_t x, size_t t = UINT32_MAX)\
    \ { return last[x] >= t ? x : find(parent[x], t); }\n\n    bool same(size_t x,\
    \ size_t y, time_type t = UINT32_MAX) { return find(x, t) == find(y, t); }\n\n\
    \    time_type unite(size_t x, size_t y)\n    {\n        if((x = find(x)) != (y\
    \ = find(y)))\n        {\n            size_t size_x = size_log[x].back().size;\n\
    \            size_t size_y = size_log[y].back().size;\n            if(size_x <\
    \ size_y) std::swap(x, y), std::swap(size_x, size_y);\n            size_log[x].push_back({clock\
    \ + 1, size_x + size_y});\n            parent[y] = x;\n            last[y] = clock;\n\
    \        }\n        return ++clock;\n    }\n}; // class partially_persistent_union_find\n\
    \n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: src/data_structure/union_find/partially_persistent_union_find.hpp
  requiredBy: []
  timestamp: '2020-11-16 21:34:32+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/data_structure/union_find/partially_persistent_union_find.hpp
layout: document
redirect_from:
- /library/src/data_structure/union_find/partially_persistent_union_find.hpp
- /library/src/data_structure/union_find/partially_persistent_union_find.hpp.html
title: src/data_structure/union_find/partially_persistent_union_find.hpp
---
