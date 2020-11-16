---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Setup
    links: []
  bundledCode: "#line 2 \"src/utils/setup.hpp\"\n\n/*\n * @file setup.hpp\n * @brief\
    \ Setup\n */\n\n#include <chrono>\n#include <iomanip>\n#include <iostream>\n\n\
    namespace workspace {\n\n/*\n * @fn io_setup\n * @brief Setup I/O before main\
    \ process.\n */\n__attribute__((constructor)) void io_setup() {\n  using namespace\
    \ std;\n  ios::sync_with_stdio(false);\n  cin.tie(nullptr);\n  cout << fixed <<\
    \ setprecision(15);\n\n#ifdef _buffer_check\n  atexit([] {\n    char bufc;\n \
    \   if (cin >> bufc)\n      cerr << \"\\n\\033[43m\\033[30mwarning: buffer not\
    \ empty.\\033[0m\\n\\n\";\n  });\n#endif\n}\n\nnamespace internal {\n// The start\
    \ time of the program.\nconst auto start_time{std::chrono::system_clock::now()};\n\
    }  // namespace internal\n\n/*\n * @fn elapsed\n * @return elapsed time of the\
    \ program\n */\nint64_t elapsed() {\n  using namespace std::chrono;\n  const auto\
    \ end_time{system_clock::now()};\n  return duration_cast<milliseconds>(end_time\
    \ - internal::start_time).count();\n}\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/*\n * @file setup.hpp\n * @brief Setup\n */\n\n#include\
    \ <chrono>\n#include <iomanip>\n#include <iostream>\n\nnamespace workspace {\n\
    \n/*\n * @fn io_setup\n * @brief Setup I/O before main process.\n */\n__attribute__((constructor))\
    \ void io_setup() {\n  using namespace std;\n  ios::sync_with_stdio(false);\n\
    \  cin.tie(nullptr);\n  cout << fixed << setprecision(15);\n\n#ifdef _buffer_check\n\
    \  atexit([] {\n    char bufc;\n    if (cin >> bufc)\n      cerr << \"\\n\\033[43m\\\
    033[30mwarning: buffer not empty.\\033[0m\\n\\n\";\n  });\n#endif\n}\n\nnamespace\
    \ internal {\n// The start time of the program.\nconst auto start_time{std::chrono::system_clock::now()};\n\
    }  // namespace internal\n\n/*\n * @fn elapsed\n * @return elapsed time of the\
    \ program\n */\nint64_t elapsed() {\n  using namespace std::chrono;\n  const auto\
    \ end_time{system_clock::now()};\n  return duration_cast<milliseconds>(end_time\
    \ - internal::start_time).count();\n}\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/utils/setup.hpp
  requiredBy: []
  timestamp: '2020-11-16 17:30:04+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/utils/setup.hpp
layout: document
redirect_from:
- /library/src/utils/setup.hpp
- /library/src/utils/setup.hpp.html
title: Setup
---
