---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: config.hpp
    title: Configuration
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
  _extendedRequiredBy:
  - icon: ':warning:'
    path: template.cpp
    title: Code template
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
    , line 310, in update\n    raise BundleErrorAt(path, i + 1, \"#pragma once found\
    \ in a non-first line\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ utils/binary_search.hpp: line 6: #pragma once found in a non-first line\n"
  code: '#pragma once

    #include "utils/binary_search.hpp"

    #include "utils/casefmt.hpp"

    #include "utils/chval.hpp"

    #include "utils/coordinate_compression.hpp"

    #include "utils/ejection.hpp"

    #include "utils/fixed_point.hpp"

    #include "utils/hash.hpp"

    #include "utils/make_vector.hpp"

    #include "utils/random_number_generator.hpp"

    #include "utils/read.hpp"

    #include "utils/round_div.hpp"

    #include "utils/sfinae.hpp"

    #include "utils/stream.hpp"

    #include "utils/trinary_search.hpp"

    #include "utils/wrapper.hpp"

    '
  dependsOn:
  - utils/binary_search.hpp
  - utils/casefmt.hpp
  - config.hpp
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
  path: utils.hpp
  requiredBy:
  - template.cpp
  timestamp: '2020-11-04 17:56:57+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utils.hpp
layout: document
redirect_from:
- /library/utils.hpp
- /library/utils.hpp.html
title: utils.hpp
---
