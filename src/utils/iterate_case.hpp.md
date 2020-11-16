---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: src/utils/io/casefmt.hpp
    title: Case Output Format
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Iterate Testcases
    links: []
  bundledCode: "#line 2 \"src/utils/iterate_case.hpp\"\n\n/*\n * @file iterate_case.hpp\n\
    \ * @brief Iterate Testcases\n */\n\nnamespace workspace {\n\nnamespace internal\
    \ {\n// The 1-based index of the current testcase.\nunsigned caseid;\n}  // namespace\
    \ internal\n\nvoid main();\nunsigned case_number();\n\n/*\n * @fn iterate_main\n\
    \ * @brief Iterate main function.\n */\nvoid iterate_main() {\n  for (unsigned\
    \ total = case_number(), &counter = (internal::caseid = 1);\n       counter <=\
    \ total; ++counter) {\n    try {\n      main();\n    } catch (std::nullptr_t)\
    \ {\n    }\n  }\n}\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/*\n * @file iterate_case.hpp\n * @brief Iterate Testcases\n\
    \ */\n\nnamespace workspace {\n\nnamespace internal {\n// The 1-based index of\
    \ the current testcase.\nunsigned caseid;\n}  // namespace internal\n\nvoid main();\n\
    unsigned case_number();\n\n/*\n * @fn iterate_main\n * @brief Iterate main function.\n\
    \ */\nvoid iterate_main() {\n  for (unsigned total = case_number(), &counter =\
    \ (internal::caseid = 1);\n       counter <= total; ++counter) {\n    try {\n\
    \      main();\n    } catch (std::nullptr_t) {\n    }\n  }\n}\n\n}  // namespace\
    \ workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: src/utils/iterate_case.hpp
  requiredBy:
  - src/utils/io/casefmt.hpp
  timestamp: '2020-11-16 17:12:47+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/utils/iterate_case.hpp
layout: document
redirect_from:
- /library/src/utils/iterate_case.hpp
- /library/src/utils/iterate_case.hpp.html
title: Iterate Testcases
---
