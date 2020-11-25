---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: I/O Setup
    links: []
  bundledCode: "#line 2 \"src/utils/io/setup.hpp\"\n\n/*\n * @file setup.hpp\n * @brief\
    \ I/O Setup\n */\n\n#include <iomanip>\n#include <iostream>\n\nnamespace workspace\
    \ {\n\n/*\n * @fn io_setup\n * @brief Setup I/O before main process.\n */\n__attribute__((constructor))\
    \ void io_setup() {\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(nullptr);\n\
    \  std::cout << std::fixed << std::setprecision(15);\n\n#ifdef _buffer_check\n\
    \  atexit([] {\n    char bufc;\n    if (std::cin >> bufc)\n      std::cerr <<\
    \ \"\\n\\033[43m\\033[30mwarning: buffer not empty.\\033[0m\\n\\n\";\n  });\n\
    #endif\n}\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/*\n * @file setup.hpp\n * @brief I/O Setup\n */\n\n#include\
    \ <iomanip>\n#include <iostream>\n\nnamespace workspace {\n\n/*\n * @fn io_setup\n\
    \ * @brief Setup I/O before main process.\n */\n__attribute__((constructor)) void\
    \ io_setup() {\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(nullptr);\n\
    \  std::cout << std::fixed << std::setprecision(15);\n\n#ifdef _buffer_check\n\
    \  atexit([] {\n    char bufc;\n    if (std::cin >> bufc)\n      std::cerr <<\
    \ \"\\n\\033[43m\\033[30mwarning: buffer not empty.\\033[0m\\n\\n\";\n  });\n\
    #endif\n}\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/utils/io/setup.hpp
  requiredBy: []
  timestamp: '2020-11-20 23:57:58+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/utils/io/setup.hpp
layout: document
redirect_from:
- /library/src/utils/io/setup.hpp
- /library/src/utils/io/setup.hpp.html
title: I/O Setup
---
