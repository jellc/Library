---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.2/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.2/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.2/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.2/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: lib/opt: line\
    \ -1: no such header\n"
  code: "// #undef _GLIBCXX_DEBUG\n// #define NDEBUG\n#include <bits/extc++.h>\n\n\
    #include \"lib/alias\"\n#include \"lib/cxx20\"\n#include \"lib/direct\"\n#include\
    \ \"lib/opt\"\n#include \"lib/sys\"\n#include \"lib/utils\"\n\nsigned main() {\n\
    \  using namespace workspace;\n\n  io_setup(15);\n\n  /* given\n    case_info.read();\
    \  //*/\n\n  /* unspecified\n    case_info.total = -1;  //*/\n\n  return case_info.iterate();\n\
    }\n\nnamespace workspace {\n\nvoid main() {\n  // start here!\n}\n\n}  // namespace\
    \ workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: template.cpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: template.cpp
layout: document
redirect_from:
- /library/template.cpp
- /library/template.cpp.html
title: template.cpp
---
