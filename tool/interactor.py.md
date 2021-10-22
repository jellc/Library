---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: py
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/python.py\"\
    , line 96, in bundle\n    raise NotImplementedError\nNotImplementedError\n"
  code: "import numpy\nimport os\nimport random\nimport subprocess\n\n\nclass interactor:\n\
    \    def __init__(self, exec):\n        self.proc = subprocess.Popen([exec], stdin=subprocess.PIPE,\
    \ stdout=subprocess.PIPE)\n\n    def __del__(self):\n        self.proc.terminate()\n\
    \n    def write(self, x):\n        self.proc.stdin.write((str(x) + '\\n').encode('utf-8'))\n\
    \        self.proc.stdin.flush()\n\n    def read(self):\n        return self.proc.stdout.readline().decode('utf-8').strip()\n"
  dependsOn: []
  isVerificationFile: false
  path: tool/interactor.py
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: tool/interactor.py
layout: document
redirect_from:
- /library/tool/interactor.py
- /library/tool/interactor.py.html
title: tool/interactor.py
---
