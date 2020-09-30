---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"string/Manacher.hpp\"\n// #line 2 \"Manacher.hpp\"\n#ifndef\
    \ Manacher_hpp\n#define Manacher_hpp\n#include <iostream>\n#include <string>\n\
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
  path: string/Manacher.hpp
  requiredBy: []
  timestamp: '2020-01-15 19:03:28+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: string/Manacher.hpp
layout: document
redirect_from:
- /library/string/Manacher.hpp
- /library/string/Manacher.hpp.html
title: string/Manacher.hpp
---
