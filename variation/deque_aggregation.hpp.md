---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 2 \"variation/deque_aggregation.hpp\"\n#include <cassert>\n\
    #include <iterator>\n#include <vector>\n// implementation with std::vector\ntemplate\
    \ <class monoid>\nclass deque_aggregation\n{\n    struct data { monoid value,\
    \ acc; };\n\n    template <bool left_operand_added>\n    struct stack_aggregation\
    \ : public std::vector<data>\n    {\n        using base = std::vector<data>;\n\
    \        bool top_referred = false;\n\n        void recalc()\n        {\n    \
    \        if(top_referred)\n            {\n                assert(!base::empty());\n\
    \                top_referred = false;\n                monoid top_val{top().value};\n\
    \                pop();\n                push(top_val);\n            }\n     \
    \   }\n\n        // copy of the element at the index.\n        data operator[](size_t\
    \ index) const\n        {\n            assert(index < base::size());\n       \
    \     recalc();\n            return base::operator[](index);\n        }\n\n  \
    \      // reference to the last element\n        data &top()\n        {\n    \
    \        assert(!base::empty());\n            top_referred = true;\n         \
    \   return base::back();\n        }\n\n        void pop()\n        {\n       \
    \     assert(!base::empty());\n            top_referred = false;\n           \
    \ base::pop_back();\n        }\n\n        void push(const monoid &mono)\n    \
    \    {\n            recalc();\n            if(left_operand_added) base::push_back({mono,\
    \ mono + fold()});\n            else base::push_back({mono, fold() + mono});\n\
    \        }\n\n        monoid fold()\n        {\n            if(base::empty())\
    \ return monoid();\n            recalc();\n            return base::back().acc;\n\
    \        }\n    }; // class stack_aggregation\n\n    stack_aggregation<true> left;\n\
    \    stack_aggregation<false> right;\n\n    void share_right()\n    {\n      \
    \  if(!left.empty() || right.empty()) return;\n        left.recalc(); right.recalc();\n\
    \        auto mid = right.begin() + (right.size() + 1) / 2;\n        for(auto\
    \ itr = mid; itr != right.begin(); ) left.push((--itr)->value);\n        right.erase(right.begin(),\
    \ mid);\n        monoid nacc;\n        for(auto &[value, acc] : right) nacc =\
    \ acc = nacc + value;\n    }\n\n    void share_left()\n    {\n        if(!right.empty()\
    \ || left.empty()) return;\n        left.recalc(); right.recalc();\n        auto\
    \ mid = left.begin() + (left.size() + 1) / 2;\n        for(auto itr = mid; itr\
    \ != left.begin(); ) right.push((--itr)->value);\n        left.erase(left.begin(),\
    \ mid);\n        monoid nacc;\n        for(auto &[value, acc] : left) nacc = acc\
    \ = nacc + value;\n    }\n\npublic:\n    bool empty() const { return left.empty()\
    \ && right.empty(); }\n    size_t size() const { return left.size() + right.size();\
    \ }\n\n    // reference to the first element.\n    monoid &front() { assert(!empty());\
    \ return share_right(), left.top().value; }\n\n    // reference to the last element.\n\
    \    monoid &back() { assert(!empty()); return share_left(), right.top().value;\
    \ }\n\n    // copy of the element at the index.\n    monoid operator[](size_t\
    \ index) const\n    {\n        assert(index < left.size() + right.size());\n \
    \       return index < left.size() ? left[index].value : right[index - left.size()].value;\n\
    \    }\n\n    void push_front(const monoid &mono) { left.push(mono); }\n\n   \
    \ void push_back(const monoid &mono) { right.push(mono); }\n\n    void pop_front()\n\
    \    {\n        assert(!empty());\n        share_right();\n        left.pop();\n\
    \    }\n\n    void pop_back()\n    {\n        assert(!empty());\n        share_left();\n\
    \        right.pop();\n    }\n\n    monoid fold() { return left.fold() + right.fold();\
    \ }\n}; // class deque_aggregation\n"
  code: "#pragma once\n#include <cassert>\n#include <iterator>\n#include <vector>\n\
    // implementation with std::vector\ntemplate <class monoid>\nclass deque_aggregation\n\
    {\n    struct data { monoid value, acc; };\n\n    template <bool left_operand_added>\n\
    \    struct stack_aggregation : public std::vector<data>\n    {\n        using\
    \ base = std::vector<data>;\n        bool top_referred = false;\n\n        void\
    \ recalc()\n        {\n            if(top_referred)\n            {\n         \
    \       assert(!base::empty());\n                top_referred = false;\n     \
    \           monoid top_val{top().value};\n                pop();\n           \
    \     push(top_val);\n            }\n        }\n\n        // copy of the element\
    \ at the index.\n        data operator[](size_t index) const\n        {\n    \
    \        assert(index < base::size());\n            recalc();\n            return\
    \ base::operator[](index);\n        }\n\n        // reference to the last element\n\
    \        data &top()\n        {\n            assert(!base::empty());\n       \
    \     top_referred = true;\n            return base::back();\n        }\n\n  \
    \      void pop()\n        {\n            assert(!base::empty());\n          \
    \  top_referred = false;\n            base::pop_back();\n        }\n\n       \
    \ void push(const monoid &mono)\n        {\n            recalc();\n          \
    \  if(left_operand_added) base::push_back({mono, mono + fold()});\n          \
    \  else base::push_back({mono, fold() + mono});\n        }\n\n        monoid fold()\n\
    \        {\n            if(base::empty()) return monoid();\n            recalc();\n\
    \            return base::back().acc;\n        }\n    }; // class stack_aggregation\n\
    \n    stack_aggregation<true> left;\n    stack_aggregation<false> right;\n\n \
    \   void share_right()\n    {\n        if(!left.empty() || right.empty()) return;\n\
    \        left.recalc(); right.recalc();\n        auto mid = right.begin() + (right.size()\
    \ + 1) / 2;\n        for(auto itr = mid; itr != right.begin(); ) left.push((--itr)->value);\n\
    \        right.erase(right.begin(), mid);\n        monoid nacc;\n        for(auto\
    \ &[value, acc] : right) nacc = acc = nacc + value;\n    }\n\n    void share_left()\n\
    \    {\n        if(!right.empty() || left.empty()) return;\n        left.recalc();\
    \ right.recalc();\n        auto mid = left.begin() + (left.size() + 1) / 2;\n\
    \        for(auto itr = mid; itr != left.begin(); ) right.push((--itr)->value);\n\
    \        left.erase(left.begin(), mid);\n        monoid nacc;\n        for(auto\
    \ &[value, acc] : left) nacc = acc = nacc + value;\n    }\n\npublic:\n    bool\
    \ empty() const { return left.empty() && right.empty(); }\n    size_t size() const\
    \ { return left.size() + right.size(); }\n\n    // reference to the first element.\n\
    \    monoid &front() { assert(!empty()); return share_right(), left.top().value;\
    \ }\n\n    // reference to the last element.\n    monoid &back() { assert(!empty());\
    \ return share_left(), right.top().value; }\n\n    // copy of the element at the\
    \ index.\n    monoid operator[](size_t index) const\n    {\n        assert(index\
    \ < left.size() + right.size());\n        return index < left.size() ? left[index].value\
    \ : right[index - left.size()].value;\n    }\n\n    void push_front(const monoid\
    \ &mono) { left.push(mono); }\n\n    void push_back(const monoid &mono) { right.push(mono);\
    \ }\n\n    void pop_front()\n    {\n        assert(!empty());\n        share_right();\n\
    \        left.pop();\n    }\n\n    void pop_back()\n    {\n        assert(!empty());\n\
    \        share_left();\n        right.pop();\n    }\n\n    monoid fold() { return\
    \ left.fold() + right.fold(); }\n}; // class deque_aggregation\n"
  dependsOn: []
  isVerificationFile: false
  path: variation/deque_aggregation.hpp
  requiredBy: []
  timestamp: '2020-08-21 02:00:03+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: variation/deque_aggregation.hpp
layout: document
redirect_from:
- /library/variation/deque_aggregation.hpp
- /library/variation/deque_aggregation.hpp.html
title: variation/deque_aggregation.hpp
---
