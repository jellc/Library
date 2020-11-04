---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: config.hpp
    title: Configuration
  _extendedRequiredBy:
  - icon: ':warning:'
    path: template.cpp
    title: Code template
  - icon: ':warning:'
    path: utils.hpp
    title: utils.hpp
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Case output format
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 310, in update\n    raise BundleErrorAt(path, i + 1, \"#pragma once found\
    \ in a non-first line\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ utils/casefmt.hpp: line 6: #pragma once found in a non-first line\n"
  code: "/*\n * @file castfmt\n * @brief Case output format\n */\n\n#pragma once\n\
    #include \"../config.hpp\"\n\nnamespace workspace {\n\n/*\n * @brief printf(\"\
    Case #%u: \", config::caseid)\n * @param os reference to ostream\n * @return os\n\
    \ */\nstd::ostream& casefmt(std::ostream& os) {\n  return os << \"Case #\" <<\
    \ config::caseid << \": \";\n}\n\n}  // namespace workspace\n"
  dependsOn:
  - config.hpp
  isVerificationFile: false
  path: utils/casefmt.hpp
  requiredBy:
  - template.cpp
  - utils.hpp
  timestamp: '2020-11-04 17:56:57+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utils/casefmt.hpp
layout: document
redirect_from:
- /library/utils/casefmt.hpp
- /library/utils/casefmt.hpp.html
title: Case output format
---
