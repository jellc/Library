---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/aizu-online-judge/2292.test.cpp
    title: test/aizu-online-judge/2292.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"src/string/Manacher.hpp\"\n// #line 2 \"Manacher.hpp\"\n\
    #ifndef Manacher_hpp\n#define Manacher_hpp\n#include <iostream>\n#include <string>\n\
    #include <vector>\n\ntemplate <class str_type = std::string>\nclass Manacher\n\
    {\n    const size_t len;\n    std::vector<size_t> rad;\n    friend std::ostream\
    \ &operator<<(std::ostream &os, const Manacher &mana)\n    {\n        bool is_front\
    \ = true;\n        for(size_t r : mana.rad)\n        {\n            if(is_front)\
    \ is_front = false;\n            else os << \" \";\n            os << r;\n   \
    \     }\n        return os;\n    }\n  public:\n    Manacher(const str_type &str)\
    \ : len(str.size()), rad(str.size())\n    {\n        for(size_t i = 0, c = 0;\
    \ i != len; ++i)\n        {\n            int l = c * 2 - i;\n            if(l\
    \ >= 0 && c + rad[c] > i + rad[l]) rad[i] = rad[l];\n            else\n      \
    \      {\n                size_t j = c + rad[c] - i;\n                while(i\
    \ >= j && i + j != len && str[i - j] == str[i + j]) ++j;\n                rad[c\
    \ = i] = j;\n            }\n        }\n    }\n    size_t size() const { return\
    \ rad.size(); }\n    size_t operator[](size_t i) const { return rad[i]; }\n};\
    \ // class Manacher\n\n#endif // Manacher_hpp\n"
  code: "// #line 2 \"Manacher.hpp\"\n#ifndef Manacher_hpp\n#define Manacher_hpp\n\
    #include <iostream>\n#include <string>\n#include <vector>\n\ntemplate <class str_type\
    \ = std::string>\nclass Manacher\n{\n    const size_t len;\n    std::vector<size_t>\
    \ rad;\n    friend std::ostream &operator<<(std::ostream &os, const Manacher &mana)\n\
    \    {\n        bool is_front = true;\n        for(size_t r : mana.rad)\n    \
    \    {\n            if(is_front) is_front = false;\n            else os << \"\
    \ \";\n            os << r;\n        }\n        return os;\n    }\n  public:\n\
    \    Manacher(const str_type &str) : len(str.size()), rad(str.size())\n    {\n\
    \        for(size_t i = 0, c = 0; i != len; ++i)\n        {\n            int l\
    \ = c * 2 - i;\n            if(l >= 0 && c + rad[c] > i + rad[l]) rad[i] = rad[l];\n\
    \            else\n            {\n                size_t j = c + rad[c] - i;\n\
    \                while(i >= j && i + j != len && str[i - j] == str[i + j]) ++j;\n\
    \                rad[c = i] = j;\n            }\n        }\n    }\n    size_t\
    \ size() const { return rad.size(); }\n    size_t operator[](size_t i) const {\
    \ return rad[i]; }\n}; // class Manacher\n\n#endif // Manacher_hpp\n"
  dependsOn: []
  isVerificationFile: false
  path: src/string/Manacher.hpp
  requiredBy: []
  timestamp: '2020-11-16 14:21:51+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/aizu-online-judge/2292.test.cpp
documentation_of: src/string/Manacher.hpp
layout: document
redirect_from:
- /library/src/string/Manacher.hpp
- /library/src/string/Manacher.hpp.html
title: src/string/Manacher.hpp
---
