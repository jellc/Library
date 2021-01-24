---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Clock
    links: []
  bundledCode: "#line 2 \"src/sys/clock.hpp\"\n\n/*\n * @fn clock.hpp\n * @brief Clock\n\
    \ */\n\n#include <chrono>\n\nnamespace workspace {\n\nusing namespace std::chrono;\n\
    \nnamespace internal {\n// The start time of the program.\nconst auto start_time{system_clock::now()};\n\
    }  // namespace internal\n\n/*\n * @fn elapsed\n * @return elapsed time of the\
    \ program\n */\nint64_t elapsed() {\n  const auto end_time{system_clock::now()};\n\
    \  return duration_cast<milliseconds>(end_time - internal::start_time).count();\n\
    }\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/*\n * @fn clock.hpp\n * @brief Clock\n */\n\n#include <chrono>\n\
    \nnamespace workspace {\n\nusing namespace std::chrono;\n\nnamespace internal\
    \ {\n// The start time of the program.\nconst auto start_time{system_clock::now()};\n\
    }  // namespace internal\n\n/*\n * @fn elapsed\n * @return elapsed time of the\
    \ program\n */\nint64_t elapsed() {\n  const auto end_time{system_clock::now()};\n\
    \  return duration_cast<milliseconds>(end_time - internal::start_time).count();\n\
    }\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/sys/clock.hpp
  requiredBy: []
  timestamp: '2020-12-12 22:46:38+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/sys/clock.hpp
layout: document
redirect_from:
- /library/src/sys/clock.hpp
- /library/src/sys/clock.hpp.html
title: Clock
---
