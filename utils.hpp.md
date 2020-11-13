---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: ../config.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n\n/*\n * @file utils.hpp\n */\n\n#include \"utils/binary_search.hpp\"\
    \n#include \"utils/io/casefmt.hpp\"\n#include \"utils/chval.hpp\"\n#include \"\
    utils/coordinate_compression.hpp\"\n#include \"utils/ejection.hpp\"\n#include\
    \ \"utils/fixed_point.hpp\"\n#include \"utils/hash.hpp\"\n#include \"utils/make_vector.hpp\"\
    \n#include \"utils/random_number_generator.hpp\"\n#include \"utils/io/read.hpp\"\
    \n#include \"utils/round_div.hpp\"\n#include \"utils/sfinae.hpp\"\n#include \"\
    utils/io/stream.hpp\"\n#include \"utils/trinary_search.hpp\"\n#include \"utils/wrapper.hpp\"\
    \n"
  dependsOn: []
  isVerificationFile: false
  path: utils.hpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utils.hpp
layout: document
redirect_from:
- /library/utils.hpp
- /library/utils.hpp.html
title: utils.hpp
---
