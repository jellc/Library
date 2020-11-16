---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: src/utils/iterate_case.hpp
    title: Iterate Testcases
  _extendedRequiredBy:
  - icon: ':warning:'
    path: src/utils/io.hpp
    title: src/utils/io.hpp
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Case Output Format
    links: []
  bundledCode: "#line 2 \"src/utils/io/casefmt.hpp\"\n\n/*\n * @file castfmt\n * @brief\
    \ Case Output Format\n */\n\n#line 2 \"src/utils/iterate_case.hpp\"\n\n/*\n *\
    \ @file iterate_case.hpp\n * @brief Iterate Testcases\n */\n\nnamespace workspace\
    \ {\n\nnamespace internal {\n// The 1-based index of the current testcase.\nunsigned\
    \ caseid;\n}  // namespace internal\n\nvoid main();\nunsigned case_number();\n\
    \n/*\n * @fn iterate_main\n * @brief Iterate main function.\n */\nvoid iterate_main()\
    \ {\n  for (unsigned total = case_number(), &counter = (internal::caseid = 1);\n\
    \       counter <= total; ++counter) {\n    try {\n      main();\n    } catch\
    \ (std::nullptr_t) {\n    }\n  }\n}\n\n}  // namespace workspace\n#line 9 \"src/utils/io/casefmt.hpp\"\
    \n\nnamespace workspace {\n\n/*\n * @fn casefmt\n * @brief printf(\"Case #%u:\
    \ \", internal::caseid)\n * @param os Reference to ostream\n * @return os\n */\n\
    std::ostream& casefmt(std::ostream& os) {\n  return os << \"Case #\" << internal::caseid\
    \ << \": \";\n}\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/*\n * @file castfmt\n * @brief Case Output Format\n */\n\
    \n#include \"../iterate_case.hpp\"\n\nnamespace workspace {\n\n/*\n * @fn casefmt\n\
    \ * @brief printf(\"Case #%u: \", internal::caseid)\n * @param os Reference to\
    \ ostream\n * @return os\n */\nstd::ostream& casefmt(std::ostream& os) {\n  return\
    \ os << \"Case #\" << internal::caseid << \": \";\n}\n\n}  // namespace workspace\n"
  dependsOn:
  - src/utils/iterate_case.hpp
  isVerificationFile: false
  path: src/utils/io/casefmt.hpp
  requiredBy:
  - src/utils/io.hpp
  timestamp: '2020-11-16 17:12:47+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/utils/io/casefmt.hpp
layout: document
redirect_from:
- /library/src/utils/io/casefmt.hpp
- /library/src/utils/io/casefmt.hpp.html
title: Case Output Format
---
