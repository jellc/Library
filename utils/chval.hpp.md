---
data:
  _extendedDependsOn: []
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
    document_title: Change less/greater
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 310, in update\n    raise BundleErrorAt(path, i + 1, \"#pragma once found\
    \ in a non-first line\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ utils/chval.hpp: line 6: #pragma once found in a non-first line\n"
  code: "/*\n * @file chval.hpp\n * @brief Change less/greater\n */\n\n#pragma once\n\
    #include <functional>\n\nnamespace workspace {\n\n/*\n * @fn chle\n * @brief substitute\
    \ y for x if comp(y, x) is true\n * @param x reference\n * @param y const reference\n\
    \ * @param comp compare function\n * @return whether or not x is updated\n */\n\
    template <class Tp, class Comp = std::less<Tp>>\nbool chle(Tp &x, const Tp &y,\
    \ Comp comp = Comp()) {\n  return comp(y, x) ? x = y, true : false;\n}\n\n/*\n\
    \ * @fn chge\n * @brief substitute y for x if comp(x, y) is true\n * @param x\
    \ reference\n * @param y const reference\n * @param comp compare function\n *\
    \ @return whether or not x is updated\n */\ntemplate <class Tp, class Comp = std::less<Tp>>\n\
    bool chge(Tp &x, const Tp &y, Comp comp = Comp()) {\n  return comp(x, y) ? x =\
    \ y, true : false;\n}\n\n}  // namespace workspace\n"
  dependsOn: []
  isVerificationFile: false
  path: utils/chval.hpp
  requiredBy:
  - template.cpp
  - utils.hpp
  timestamp: '2020-11-04 17:56:57+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utils/chval.hpp
layout: document
redirect_from:
- /library/utils/chval.hpp
- /library/utils/chval.hpp.html
title: Change less/greater
---
