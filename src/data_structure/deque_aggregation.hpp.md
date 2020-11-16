---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"src/data_structure/deque_aggregation.hpp\"\n#include <cassert>\n\
    #include <iterator>\n// implementation with dynamic memory allocation.\ntemplate\
    \ <class monoid>\nclass deque_aggregation\n{\n    template <bool left_operand_added>\n\
    \    class stack_aggregation\n    {\n        friend deque_aggregation;\n     \
    \   struct data { monoid value, acc; };\n        size_t capacity;\n        data\
    \ *stack, *end, *itr;\n        bool top_referred;\n\n        void recalc()\n \
    \       {\n            if(top_referred)\n            {\n                assert(itr\
    \ != stack);\n                top_referred = false;\n                monoid top_val{top().value};\n\
    \                pop();\n                push(top_val);\n            }\n     \
    \   }\n\n    public:\n        stack_aggregation() : capacity(1), stack(new data[1]),\
    \ end(std::next(stack)), itr(stack), top_referred() {}\n        ~stack_aggregation()\
    \ { delete[] stack; }\n\n        bool empty() const { return stack == itr; }\n\
    \        size_t size() const { return itr - stack; }\n\n        // copy of the\
    \ element at the index.\n        data operator[](size_t index) const\n       \
    \ {\n            assert(index < size());\n            recalc();\n            return\
    \ stack[index];\n        }\n\n        // reference to the last element\n     \
    \   data &top()\n        {\n            assert(itr != stack);\n            top_referred\
    \ = true;\n            return *std::prev(itr);\n        }\n\n        void pop()\n\
    \        {\n            assert(itr != stack);\n            --itr;\n          \
    \  top_referred = false;\n        }\n\n        void push(const monoid &mono)\n\
    \        {\n            recalc();\n            if(itr == end)\n            {\n\
    \                data *tmp = new data[capacity << 1];\n                std::swap(stack,\
    \ tmp);\n                end = (itr = std::copy(tmp, tmp + capacity, stack)) +\
    \ capacity;\n                capacity <<= 1;\n                delete[] tmp;\n\
    \            }\n            if(left_operand_added) *itr = data{mono, mono + fold()};\n\
    \            else *itr = data{mono, fold() + mono};\n            ++itr;\n    \
    \    }\n\n        monoid fold()\n        {\n            if(itr == stack) return\
    \ monoid();\n            recalc();\n            return std::prev(itr)->acc;\n\
    \        }\n    }; // class stack_aggregation\n\n    stack_aggregation<true> left;\n\
    \    stack_aggregation<false> right;\n\n    void balance_to_left()\n    {\n  \
    \      if(!left.empty() || right.empty()) return;\n        left.recalc(); right.recalc();\n\
    \        size_t mid = (right.size() + 1) >> 1;\n        auto *itr = right.stack\
    \ + mid;\n        do { left.push((--itr)->value); } while(itr != right.stack);\n\
    \        monoid acc;\n        for(auto *p = right.stack + mid; p != right.itr;\
    \ ++p, ++itr)\n        {\n            *itr = {p->value, acc = acc + p->value};\n\
    \        }\n        right.itr = itr;\n    }\n\n    void balance_to_right()\n \
    \   {\n        if(!right.empty() || left.empty()) return;\n        left.recalc();\
    \ right.recalc();\n        size_t mid = (left.size() + 1) >> 1;\n        auto\
    \ *itr = left.stack + mid;\n        do { right.push((--itr)->value); } while(itr\
    \ != left.stack);\n        monoid acc;\n        for(auto *p = left.stack + mid;\
    \ p != left.itr; ++p, ++itr)\n        {\n            *itr = {p->value, acc = p->value\
    \ + acc};\n        }\n        left.itr = itr;\n    }\n\npublic:\n    bool empty()\
    \ const { return left.empty() && right.empty(); }\n    size_t size() const { return\
    \ left.size() + right.size(); }\n\n    // reference to the first element.\n  \
    \  monoid &front() { assert(!empty()); balance_to_left(); return left.top().value;\
    \ }\n\n    // reference to the last element.\n    monoid &back() { assert(!empty());\
    \ balance_to_right(); return right.top().value; }\n\n    // copy of the element\
    \ at the index.\n    monoid operator[](size_t index) const\n    {\n        assert(index\
    \ < left.size() + right.size());\n        return index < left.size() ? left[index].value\
    \ : right[index - left.size()].value;\n    }\n\n    void push_front(const monoid\
    \ &mono) { left.push(mono); }\n\n    void push_back(const monoid &mono) { right.push(mono);\
    \ }\n\n    void pop_front()\n    {\n        assert(!empty());\n        balance_to_left();\n\
    \        left.pop();\n    }\n\n    void pop_back()\n    {\n        assert(!empty());\n\
    \        balance_to_right();\n        right.pop();\n    }\n\n    monoid fold()\
    \ { return left.fold() + right.fold(); }\n}; // class deque_aggregation\n"
  code: "#pragma once\n#include <cassert>\n#include <iterator>\n// implementation\
    \ with dynamic memory allocation.\ntemplate <class monoid>\nclass deque_aggregation\n\
    {\n    template <bool left_operand_added>\n    class stack_aggregation\n    {\n\
    \        friend deque_aggregation;\n        struct data { monoid value, acc; };\n\
    \        size_t capacity;\n        data *stack, *end, *itr;\n        bool top_referred;\n\
    \n        void recalc()\n        {\n            if(top_referred)\n           \
    \ {\n                assert(itr != stack);\n                top_referred = false;\n\
    \                monoid top_val{top().value};\n                pop();\n      \
    \          push(top_val);\n            }\n        }\n\n    public:\n        stack_aggregation()\
    \ : capacity(1), stack(new data[1]), end(std::next(stack)), itr(stack), top_referred()\
    \ {}\n        ~stack_aggregation() { delete[] stack; }\n\n        bool empty()\
    \ const { return stack == itr; }\n        size_t size() const { return itr - stack;\
    \ }\n\n        // copy of the element at the index.\n        data operator[](size_t\
    \ index) const\n        {\n            assert(index < size());\n            recalc();\n\
    \            return stack[index];\n        }\n\n        // reference to the last\
    \ element\n        data &top()\n        {\n            assert(itr != stack);\n\
    \            top_referred = true;\n            return *std::prev(itr);\n     \
    \   }\n\n        void pop()\n        {\n            assert(itr != stack);\n  \
    \          --itr;\n            top_referred = false;\n        }\n\n        void\
    \ push(const monoid &mono)\n        {\n            recalc();\n            if(itr\
    \ == end)\n            {\n                data *tmp = new data[capacity << 1];\n\
    \                std::swap(stack, tmp);\n                end = (itr = std::copy(tmp,\
    \ tmp + capacity, stack)) + capacity;\n                capacity <<= 1;\n     \
    \           delete[] tmp;\n            }\n            if(left_operand_added) *itr\
    \ = data{mono, mono + fold()};\n            else *itr = data{mono, fold() + mono};\n\
    \            ++itr;\n        }\n\n        monoid fold()\n        {\n         \
    \   if(itr == stack) return monoid();\n            recalc();\n            return\
    \ std::prev(itr)->acc;\n        }\n    }; // class stack_aggregation\n\n    stack_aggregation<true>\
    \ left;\n    stack_aggregation<false> right;\n\n    void balance_to_left()\n \
    \   {\n        if(!left.empty() || right.empty()) return;\n        left.recalc();\
    \ right.recalc();\n        size_t mid = (right.size() + 1) >> 1;\n        auto\
    \ *itr = right.stack + mid;\n        do { left.push((--itr)->value); } while(itr\
    \ != right.stack);\n        monoid acc;\n        for(auto *p = right.stack + mid;\
    \ p != right.itr; ++p, ++itr)\n        {\n            *itr = {p->value, acc =\
    \ acc + p->value};\n        }\n        right.itr = itr;\n    }\n\n    void balance_to_right()\n\
    \    {\n        if(!right.empty() || left.empty()) return;\n        left.recalc();\
    \ right.recalc();\n        size_t mid = (left.size() + 1) >> 1;\n        auto\
    \ *itr = left.stack + mid;\n        do { right.push((--itr)->value); } while(itr\
    \ != left.stack);\n        monoid acc;\n        for(auto *p = left.stack + mid;\
    \ p != left.itr; ++p, ++itr)\n        {\n            *itr = {p->value, acc = p->value\
    \ + acc};\n        }\n        left.itr = itr;\n    }\n\npublic:\n    bool empty()\
    \ const { return left.empty() && right.empty(); }\n    size_t size() const { return\
    \ left.size() + right.size(); }\n\n    // reference to the first element.\n  \
    \  monoid &front() { assert(!empty()); balance_to_left(); return left.top().value;\
    \ }\n\n    // reference to the last element.\n    monoid &back() { assert(!empty());\
    \ balance_to_right(); return right.top().value; }\n\n    // copy of the element\
    \ at the index.\n    monoid operator[](size_t index) const\n    {\n        assert(index\
    \ < left.size() + right.size());\n        return index < left.size() ? left[index].value\
    \ : right[index - left.size()].value;\n    }\n\n    void push_front(const monoid\
    \ &mono) { left.push(mono); }\n\n    void push_back(const monoid &mono) { right.push(mono);\
    \ }\n\n    void pop_front()\n    {\n        assert(!empty());\n        balance_to_left();\n\
    \        left.pop();\n    }\n\n    void pop_back()\n    {\n        assert(!empty());\n\
    \        balance_to_right();\n        right.pop();\n    }\n\n    monoid fold()\
    \ { return left.fold() + right.fold(); }\n}; // class deque_aggregation\n"
  dependsOn: []
  isVerificationFile: false
  path: src/data_structure/deque_aggregation.hpp
  requiredBy: []
  timestamp: '2020-11-16 21:34:32+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/data_structure/deque_aggregation.hpp
layout: document
redirect_from:
- /library/src/data_structure/deque_aggregation.hpp
- /library/src/data_structure/deque_aggregation.hpp.html
title: src/data_structure/deque_aggregation.hpp
---
