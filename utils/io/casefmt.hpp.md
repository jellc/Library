---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Case Output Format
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: ../config.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n\n/*\n * @file castfmt\n * @brief Case Output Format\n */\n\
    \n#include \"../config.hpp\"\n\nnamespace workspace {\n\n/*\n * @brief printf(\"\
    Case #%u: \", config::caseid)\n * @param os reference to ostream\n * @return os\n\
    \ */\nstd::ostream& casefmt(std::ostream& os) {\n  return os << \"Case #\" <<\
    \ config::caseid << \": \";\n}\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: utils/io/casefmt.hpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utils/io/casefmt.hpp
layout: document
redirect_from:
- /library/utils/io/casefmt.hpp
- /library/utils/io/casefmt.hpp.html
title: Case Output Format
---
