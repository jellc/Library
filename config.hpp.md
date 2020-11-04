---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: template.cpp
    title: Code template
  - icon: ':warning:'
    path: utils.hpp
    title: utils.hpp
  - icon: ':warning:'
    path: utils/casefmt.hpp
    title: Case output format
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Configuration
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 310, in update\n    raise BundleErrorAt(path, i + 1, \"#pragma once found\
    \ in a non-first line\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ config.hpp: line 6: #pragma once found in a non-first line\n"
  code: "/*\n * @file config.hpp\n * @brief Configuration\n */\n\n#pragma once\n#include\
    \ <chrono>\n#include <iomanip>\n#include <iostream>\n\nnamespace config {\n\n\
    const auto start_time{std::chrono::system_clock::now()};\n\n/*\n * @fn elapsed\n\
    \ * @return elapsed time of the program\n */\nint64_t elapsed() {\n  using namespace\
    \ std::chrono;\n  const auto end_time{system_clock::now()};\n  return duration_cast<milliseconds>(end_time\
    \ - start_time).count();\n}\n\n/*\n * @fn setup\n * @brief setup I/O before main\
    \ process.\n */\n__attribute__((constructor)) void setup() {\n  using namespace\
    \ std;\n  ios::sync_with_stdio(false);\n  cin.tie(nullptr);\n  cout << fixed <<\
    \ setprecision(15);\n\n#ifdef _buffer_check\n  atexit([] {\n    char bufc;\n \
    \   if (cin >> bufc)\n      cerr << \"\\n\\033[43m\\033[30mwarning: buffer not\
    \ empty.\\033[0m\\n\\n\";\n  });\n#endif\n}\n\nunsigned cases(), caseid = 1; \
    \ // current case number, 1-indexed\n\n/*\n * @fn loop\n * @brief iterate cases.\n\
    \ * @param main called once per case\n */\ntemplate <class F> void loop(F main)\
    \ {\n  for (const unsigned total = cases(); caseid <= total; ++caseid) {\n   \
    \ try {\n      main();\n    } catch (std::nullptr_t) {\n    }\n  }\n}\n\n}  //\
    \ namespace config\n"
  dependsOn: []
  isVerificationFile: false
  path: config.hpp
  requiredBy:
  - template.cpp
  - utils.hpp
  - utils/casefmt.hpp
  timestamp: '2020-11-04 17:56:57+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: config.hpp
layout: document
redirect_from:
- /library/config.hpp
- /library/config.hpp.html
title: Configuration
---
