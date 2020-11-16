---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: config.hpp
    title: Configuration
  _extendedRequiredBy:
  - icon: ':warning:'
    path: utils.hpp
    title: utils.hpp
  - icon: ':heavy_check_mark:'
    path: utils/io.hpp
    title: utils/io.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/aors_score.test.cpp
    title: test/aizu-online-judge/aors_score.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/do_use_segment_tree.test.cpp
    title: test/aizu-online-judge/do_use_segment_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/extended_euclid_algorithm.test.cpp
    title: test/aizu-online-judge/extended_euclid_algorithm.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/pattern_search.test.cpp
    title: test/aizu-online-judge/pattern_search.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/range_minimum_query.test.cpp
    title: test/aizu-online-judge/range_minimum_query.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/suffix_array.test.cpp
    title: test/library-checker/suffix_array.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/library-checker/zalgorithm.test.cpp
    title: test/library-checker/zalgorithm.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Case Output Format
    links: []
  bundledCode: "#line 2 \"utils/io/casefmt.hpp\"\n\n/*\n * @file castfmt\n * @brief\
    \ Case Output Format\n */\n\n#line 2 \"config.hpp\"\n\n/*\n * @file config.hpp\n\
    \ * @brief Configuration\n */\n\n#include <chrono>\n#include <iomanip>\n#include\
    \ <iostream>\n\nnamespace config {\n\nconst auto start_time{std::chrono::system_clock::now()};\n\
    \n/*\n * @fn elapsed\n * @return elapsed time of the program\n */\nint64_t elapsed()\
    \ {\n  using namespace std::chrono;\n  const auto end_time{system_clock::now()};\n\
    \  return duration_cast<milliseconds>(end_time - start_time).count();\n}\n\n/*\n\
    \ * @fn setup\n * @brief setup I/O before main process.\n */\n__attribute__((constructor))\
    \ void setup() {\n  using namespace std;\n  ios::sync_with_stdio(false);\n  cin.tie(nullptr);\n\
    \  cout << fixed << setprecision(15);\n\n#ifdef _buffer_check\n  atexit([] {\n\
    \    char bufc;\n    if (cin >> bufc)\n      cerr << \"\\n\\033[43m\\033[30mwarning:\
    \ buffer not empty.\\033[0m\\n\\n\";\n  });\n#endif\n}\n\nunsigned cases(), caseid\
    \ = 1;  // current case number, 1-indexed\n\n/*\n * @fn loop\n * @brief iterate\
    \ cases.\n * @param main called once per case\n */\ntemplate <class F> void loop(F\
    \ main) {\n  for (const unsigned total = cases(); caseid <= total; ++caseid) {\n\
    \    try {\n      main();\n    } catch (std::nullptr_t) {\n    }\n  }\n}\n\n}\
    \  // namespace config\n#line 9 \"utils/io/casefmt.hpp\"\n\nnamespace workspace\
    \ {\n\n/*\n * @brief printf(\"Case #%u: \", config::caseid)\n * @param os reference\
    \ to ostream\n * @return os\n */\nstd::ostream& casefmt(std::ostream& os) {\n\
    \  return os << \"Case #\" << config::caseid << \": \";\n}\n\n}  // namespace\
    \ workspace\n"
  code: "#pragma once\n\n/*\n * @file castfmt\n * @brief Case Output Format\n */\n\
    \n#include \"../../config.hpp\"\n\nnamespace workspace {\n\n/*\n * @brief printf(\"\
    Case #%u: \", config::caseid)\n * @param os reference to ostream\n * @return os\n\
    \ */\nstd::ostream& casefmt(std::ostream& os) {\n  return os << \"Case #\" <<\
    \ config::caseid << \": \";\n}\n\n}  // namespace workspace\n"
  dependsOn:
  - config.hpp
  isVerificationFile: false
  path: utils/io/casefmt.hpp
  requiredBy:
  - utils.hpp
  - utils/io.hpp
  timestamp: '2020-11-14 01:34:43+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library-checker/zalgorithm.test.cpp
  - test/library-checker/suffix_array.test.cpp
  - test/aizu-online-judge/aors_score.test.cpp
  - test/aizu-online-judge/range_minimum_query.test.cpp
  - test/aizu-online-judge/pattern_search.test.cpp
  - test/aizu-online-judge/extended_euclid_algorithm.test.cpp
  - test/aizu-online-judge/do_use_segment_tree.test.cpp
documentation_of: utils/io/casefmt.hpp
layout: document
redirect_from:
- /library/utils/io/casefmt.hpp
- /library/utils/io/casefmt.hpp.html
title: Case Output Format
---
