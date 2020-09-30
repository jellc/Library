---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"local/dump.hpp\"\n#include <iostream>\n\n#define dump(...)\
    \ std::cerr << \"[ \" << __LINE__ << \" : \" << __FUNCTION__ << \" ]\\n\", dump_func(#__VA_ARGS__,\
    \ __VA_ARGS__)\n\ntemplate <class T> void dump_func(const char *ptr, const T &x)\n\
    {\n    std::cerr << '\\t';\n    for(char c = *ptr; c != '\\0'; c = *++ptr) if(c\
    \ != ' ' && c != '\\t') std::cerr << c;\n    std::cerr << \" : \" << x << '\\\
    n';\n}\n\ntemplate <class T, class... types> void dump_func(const char *ptr, const\
    \ T &x, types... rest)\n{\n    std::cerr << '\\t';\n    for(char c = *ptr; c !=\
    \ ','; c = *++ptr) if(c != ' ' && c != '\\t') std::cerr << c;\n    std::cerr <<\
    \ \" : \" << x << \",\\n\"; dump_func(++ptr, rest...);\n}\n"
  code: "#include <iostream>\n\n#define dump(...) std::cerr << \"[ \" << __LINE__\
    \ << \" : \" << __FUNCTION__ << \" ]\\n\", dump_func(#__VA_ARGS__, __VA_ARGS__)\n\
    \ntemplate <class T> void dump_func(const char *ptr, const T &x)\n{\n    std::cerr\
    \ << '\\t';\n    for(char c = *ptr; c != '\\0'; c = *++ptr) if(c != ' ' && c !=\
    \ '\\t') std::cerr << c;\n    std::cerr << \" : \" << x << '\\n';\n}\n\ntemplate\
    \ <class T, class... types> void dump_func(const char *ptr, const T &x, types...\
    \ rest)\n{\n    std::cerr << '\\t';\n    for(char c = *ptr; c != ','; c = *++ptr)\
    \ if(c != ' ' && c != '\\t') std::cerr << c;\n    std::cerr << \" : \" << x <<\
    \ \",\\n\"; dump_func(++ptr, rest...);\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: local/dump.hpp
  requiredBy: []
  timestamp: '2020-02-10 09:12:50+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: local/dump.hpp
layout: document
redirect_from:
- /library/local/dump.hpp
- /library/local/dump.hpp.html
title: local/dump.hpp
---
