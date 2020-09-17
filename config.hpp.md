---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: template.cpp
    title: template.cpp
  - icon: ':warning:'
    path: utils/casefmt.hpp
    title: utils/casefmt.hpp
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 2 \"config.hpp\"\n#include <chrono>\n#include <iomanip>\n#include\
    \ <iostream>\nnamespace config {\nconst auto start_time{std::chrono::system_clock::now()};\n\
    int64_t elapsed() {\n  using namespace std::chrono;\n  const auto end_time{system_clock::now()};\n\
    \  return duration_cast<milliseconds>(end_time - start_time).count();\n}\n__attribute__((constructor))\
    \ void setup() {\n  using namespace std;\n  ios::sync_with_stdio(false);\n  cin.tie(nullptr);\n\
    \  cout << fixed << setprecision(15);\n#ifdef _buffer_check\n  atexit([] {\n \
    \   char bufc;\n    if (cin >> bufc)\n      cerr << \"\\n\\033[43m\\033[30mwarning:\
    \ buffer not empty.\\033[0m\\n\\n\";\n  });\n#endif\n}\nunsigned cases(void),\
    \ caseid = 1;\ntemplate <class C> void main() {\n  for (const unsigned total =\
    \ cases(); caseid <= total; ++caseid) C();\n}\n}  // namespace config\n"
  code: "#pragma once\n#include <chrono>\n#include <iomanip>\n#include <iostream>\n\
    namespace config {\nconst auto start_time{std::chrono::system_clock::now()};\n\
    int64_t elapsed() {\n  using namespace std::chrono;\n  const auto end_time{system_clock::now()};\n\
    \  return duration_cast<milliseconds>(end_time - start_time).count();\n}\n__attribute__((constructor))\
    \ void setup() {\n  using namespace std;\n  ios::sync_with_stdio(false);\n  cin.tie(nullptr);\n\
    \  cout << fixed << setprecision(15);\n#ifdef _buffer_check\n  atexit([] {\n \
    \   char bufc;\n    if (cin >> bufc)\n      cerr << \"\\n\\033[43m\\033[30mwarning:\
    \ buffer not empty.\\033[0m\\n\\n\";\n  });\n#endif\n}\nunsigned cases(void),\
    \ caseid = 1;\ntemplate <class C> void main() {\n  for (const unsigned total =\
    \ cases(); caseid <= total; ++caseid) C();\n}\n}  // namespace config\n"
  dependsOn: []
  isVerificationFile: false
  path: config.hpp
  requiredBy:
  - template.cpp
  - utils/casefmt.hpp
  timestamp: '2020-09-07 03:02:26+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: config.hpp
layout: document
redirect_from:
- /library/config.hpp
- /library/config.hpp.html
title: config.hpp
---
