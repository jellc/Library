---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: alias.hpp
    title: Alias
  - icon: ':warning:'
    path: config.hpp
    title: Configuration
  - icon: ':warning:'
    path: cxx20.hpp
    title: cxx20.hpp
  - icon: ':warning:'
    path: option.hpp
    title: Optimize options
  - icon: ':warning:'
    path: utils.hpp
    title: utils.hpp
  - icon: ':heavy_check_mark:'
    path: utils/binary_search.hpp
    title: Binary_search
  - icon: ':warning:'
    path: utils/casefmt.hpp
    title: Case output format
  - icon: ':warning:'
    path: utils/chval.hpp
    title: Change less/greater
  - icon: ':heavy_check_mark:'
    path: utils/coordinate_compression.hpp
    title: utils/coordinate_compression.hpp
  - icon: ':warning:'
    path: utils/ejection.hpp
    title: Ejection from try block
  - icon: ':warning:'
    path: utils/fixed_point.hpp
    title: Fixed point combinator
  - icon: ':heavy_check_mark:'
    path: utils/hash.hpp
    title: utils/hash.hpp
  - icon: ':warning:'
    path: utils/make_vector.hpp
    title: Multi-dimensional vector
  - icon: ':heavy_check_mark:'
    path: utils/random_number_generator.hpp
    title: utils/random_number_generator.hpp
  - icon: ':heavy_check_mark:'
    path: utils/read.hpp
    title: utils/read.hpp
  - icon: ':warning:'
    path: utils/round_div.hpp
    title: Round integer division
  - icon: ':heavy_check_mark:'
    path: utils/sfinae.hpp
    title: utils/sfinae.hpp
  - icon: ':heavy_check_mark:'
    path: utils/stream.hpp
    title: utils/stream.hpp
  - icon: ':warning:'
    path: utils/trinary_search.hpp
    title: utils/trinary_search.hpp
  - icon: ':warning:'
    path: utils/wrapper.hpp
    title: utils/wrapper.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Code template
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 310, in update\n    raise BundleErrorAt(path, i + 1, \"#pragma once found\
    \ in a non-first line\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ alias.hpp: line 6: #pragma once found in a non-first line\n"
  code: "/* @file template.cpp\n * @brief Code template\n */\n\n#include <bits/extc++.h>\n\
    \n#include \"alias.hpp\"\n#include \"config.hpp\"\n#include \"cxx20.hpp\"\n#include\
    \ \"option.hpp\"\n#include \"utils.hpp\"\n\nnamespace workspace {\nvoid main();\n\
    }\nint main() { config::loop(workspace::main); }\n\nunsigned config::cases() {\n\
    \  // return -1; // unspecified\n  // int t; std::cin >> t; std::cin.ignore();\
    \ return t; // given\n  return 1;\n}\n\nnamespace workspace {\nvoid main() {\n\
    \  // start here!\n}\n}\n"
  dependsOn:
  - alias.hpp
  - config.hpp
  - cxx20.hpp
  - option.hpp
  - utils.hpp
  - utils/binary_search.hpp
  - utils/casefmt.hpp
  - utils/chval.hpp
  - utils/coordinate_compression.hpp
  - utils/ejection.hpp
  - utils/fixed_point.hpp
  - utils/hash.hpp
  - utils/sfinae.hpp
  - utils/make_vector.hpp
  - utils/random_number_generator.hpp
  - utils/read.hpp
  - utils/round_div.hpp
  - utils/stream.hpp
  - utils/trinary_search.hpp
  - utils/wrapper.hpp
  isVerificationFile: false
  path: template.cpp
  requiredBy: []
  timestamp: '2020-11-04 17:56:57+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: template.cpp
layout: document
redirect_from:
- /library/template.cpp
- /library/template.cpp.html
title: Code template
---
