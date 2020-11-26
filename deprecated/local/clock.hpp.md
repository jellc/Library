---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"deprecated/local/clock.hpp\"\n#include <chrono>\n#include\
    \ <iostream>\n#include <string>\n\nclass\n{\n    std::chrono::system_clock::time_point\
    \ built_pt, last_pt;\n    int built_ln, last_ln;\n    std::string built_func,\
    \ last_func;\n    bool is_built = false;\n\npublic:\n    void build(int crt_ln,\
    \ const std::string &crt_func)\n    {\n        is_built = true, last_pt = built_pt\
    \ = std::chrono::system_clock::now(), last_ln = built_ln = crt_ln, last_func =\
    \ built_func = crt_func;\n    }\n\n    void set(int crt_ln, const std::string\
    \ &crt_func)\n    {\n        if(is_built) last_pt = std::chrono::system_clock::now(),\
    \ last_ln = crt_ln, last_func = crt_func;\n        else std::cerr << \"[ \" <<\
    \ crt_ln << \" : \" << crt_func << \" ] \" << \"myclock_t::set failed (yet to\
    \ be built!)\\n\";\n    }\n\n    void get(int crt_ln, const std::string &crt_func)\n\
    \    {\n        if(is_built)\n        {\n            std::chrono::system_clock::time_point\
    \ crt_pt(std::chrono::system_clock::now());\n            long long diff = std::chrono::duration_cast<std::chrono::milliseconds>(crt_pt\
    \ - last_pt).count();\n            std::cerr << diff << \" ms elapsed from\" <<\
    \ \" [ \" << last_ln << \" : \" << last_func << \" ]\";\n            if(last_ln\
    \ == built_ln) std::cerr << \" (when built)\";\n            std::cerr << \" to\"\
    \ << \" [ \" << crt_ln << \" : \" << crt_func << \" ]\" << \"\\n\";\n        \
    \    last_pt = built_pt, last_ln = built_ln, last_func = built_func;\n       \
    \ }\n        else\n        {\n            std::cerr << \"[ \" << crt_ln << \"\
    \ : \" << crt_func << \" ] \" << \"myclock_t::get failed (yet to be built!)\\\
    n\";\n        }\n    }\n} myclock; // unnamed class\n\n#define build_clock() myclock.build(__LINE__,\
    \ __func__)\n#define set_clock() myclock.set(__LINE__, __func__)\n#define get_clock()\
    \ myclock.get(__LINE__, __func__)\n"
  code: "#include <chrono>\n#include <iostream>\n#include <string>\n\nclass\n{\n \
    \   std::chrono::system_clock::time_point built_pt, last_pt;\n    int built_ln,\
    \ last_ln;\n    std::string built_func, last_func;\n    bool is_built = false;\n\
    \npublic:\n    void build(int crt_ln, const std::string &crt_func)\n    {\n  \
    \      is_built = true, last_pt = built_pt = std::chrono::system_clock::now(),\
    \ last_ln = built_ln = crt_ln, last_func = built_func = crt_func;\n    }\n\n \
    \   void set(int crt_ln, const std::string &crt_func)\n    {\n        if(is_built)\
    \ last_pt = std::chrono::system_clock::now(), last_ln = crt_ln, last_func = crt_func;\n\
    \        else std::cerr << \"[ \" << crt_ln << \" : \" << crt_func << \" ] \"\
    \ << \"myclock_t::set failed (yet to be built!)\\n\";\n    }\n\n    void get(int\
    \ crt_ln, const std::string &crt_func)\n    {\n        if(is_built)\n        {\n\
    \            std::chrono::system_clock::time_point crt_pt(std::chrono::system_clock::now());\n\
    \            long long diff = std::chrono::duration_cast<std::chrono::milliseconds>(crt_pt\
    \ - last_pt).count();\n            std::cerr << diff << \" ms elapsed from\" <<\
    \ \" [ \" << last_ln << \" : \" << last_func << \" ]\";\n            if(last_ln\
    \ == built_ln) std::cerr << \" (when built)\";\n            std::cerr << \" to\"\
    \ << \" [ \" << crt_ln << \" : \" << crt_func << \" ]\" << \"\\n\";\n        \
    \    last_pt = built_pt, last_ln = built_ln, last_func = built_func;\n       \
    \ }\n        else\n        {\n            std::cerr << \"[ \" << crt_ln << \"\
    \ : \" << crt_func << \" ] \" << \"myclock_t::get failed (yet to be built!)\\\
    n\";\n        }\n    }\n} myclock; // unnamed class\n\n#define build_clock() myclock.build(__LINE__,\
    \ __func__)\n#define set_clock() myclock.set(__LINE__, __func__)\n#define get_clock()\
    \ myclock.get(__LINE__, __func__)\n"
  dependsOn: []
  isVerificationFile: false
  path: deprecated/local/clock.hpp
  requiredBy: []
  timestamp: '2020-11-26 17:02:13+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: deprecated/local/clock.hpp
layout: document
redirect_from:
- /library/deprecated/local/clock.hpp
- /library/deprecated/local/clock.hpp.html
title: deprecated/local/clock.hpp
---
