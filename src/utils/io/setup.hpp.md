---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: I/O Setup
    links: []
  bundledCode: "#line 2 \"src/utils/io/setup.hpp\"\n\n/**\n * @file setup.hpp\n *\
    \ @brief I/O Setup\n */\n\n#include <iomanip>\n#include <iostream>\n\nnamespace\
    \ workspace {\n\n/**\n * @brief Setup I/O.\n * @param __n Standard output precision\n\
    \ */\nvoid io_setup(int __n) {\n  std::cin.tie(0)->sync_with_stdio(0);\n  std::cout\
    \ << std::fixed << std::setprecision(__n);\n\n#ifdef _buffer_check\n  atexit([]\
    \ {\n    char bufc;\n    if (std::cin >> bufc)\n      std::cerr << \"\\n\\033[43m\\\
    033[30mwarning: buffer not empty.\\033[0m\\n\\n\";\n  });\n#endif\n}\n\n}  //\
    \ namespace workspace\n"
  code: "#pragma once\n\n/**\n * @file setup.hpp\n * @brief I/O Setup\n */\n\n#include\
    \ <iomanip>\n#include <iostream>\n\nnamespace workspace {\n\n/**\n * @brief Setup\
    \ I/O.\n * @param __n Standard output precision\n */\nvoid io_setup(int __n) {\n\
    \  std::cin.tie(0)->sync_with_stdio(0);\n  std::cout << std::fixed << std::setprecision(__n);\n\
    \n#ifdef _buffer_check\n  atexit([] {\n    char bufc;\n    if (std::cin >> bufc)\n\
    \      std::cerr << \"\\n\\033[43m\\033[30mwarning: buffer not empty.\\033[0m\\\
    n\\n\";\n  });\n#endif\n}\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/utils/io/setup.hpp
  requiredBy: []
  timestamp: '2021-03-03 03:39:44+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/utils/io/setup.hpp
layout: document
redirect_from:
- /library/src/utils/io/setup.hpp
- /library/src/utils/io/setup.hpp.html
title: I/O Setup
---
