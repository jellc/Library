---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/deque_aggregation.hpp
    title: data_structure/deque_aggregation.hpp
  - icon: ':heavy_check_mark:'
    path: modulus/modint.hpp
    title: modulus/modint.hpp
  - icon: ':question:'
    path: utils/sfinae.hpp
    title: utils/sfinae.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/queue_operate_all_composite
    links:
    - https://judge.yosupo.jp/problem/queue_operate_all_composite
  bundledCode: "#line 1 \"test/library-checker/queue_operate_all_composite.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/queue_operate_all_composite\"\
    \n#include <cstdio>\n\n#line 2 \"data_structure/deque_aggregation.hpp\"\n#include\
    \ <cassert>\n#include <iterator>\n// implementation with dynamic memory allocation.\n\
    template <class monoid>\nclass deque_aggregation\n{\n    template <bool left_operand_added>\n\
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
    \ { return left.fold() + right.fold(); }\n}; // class deque_aggregation\n#line\
    \ 3 \"modulus/modint.hpp\"\n#include <iostream>\n\n#line 2 \"utils/sfinae.hpp\"\
    \n#include <cstdint>\n#include <type_traits>\n\ntemplate <class type, template\
    \ <class> class trait>\nusing enable_if_trait_type = typename std::enable_if<trait<type>::value>::type;\n\
    \ntemplate <class Container>\nusing element_type = typename std::decay<decltype(\n\
    \    *std::begin(std::declval<Container&>()))>::type;\n\ntemplate <class T, class\
    \ = int> struct mapped_of {\n  using type = element_type<T>;\n};\ntemplate <class\
    \ T>\nstruct mapped_of<T,\n                 typename std::pair<int, typename T::mapped_type>::first_type>\
    \ {\n  using type = typename T::mapped_type;\n};\ntemplate <class T> using mapped_type\
    \ = typename mapped_of<T>::type;\n\ntemplate <class T, class = void> struct is_integral_ext\
    \ : std::false_type {};\ntemplate <class T>\nstruct is_integral_ext<\n    T, typename\
    \ std::enable_if<std::is_integral<T>::value>::type>\n    : std::true_type {};\n\
    template <> struct is_integral_ext<__int128_t> : std::true_type {};\ntemplate\
    \ <> struct is_integral_ext<__uint128_t> : std::true_type {};\n#if __cplusplus\
    \ >= 201402\ntemplate <class T>\nconstexpr static bool is_integral_ext_v = is_integral_ext<T>::value;\n\
    #endif\n\ntemplate <typename T, typename = void> struct multiplicable_uint {\n\
    \  using type = uint_least32_t;\n};\ntemplate <typename T>\nstruct multiplicable_uint<T,\
    \ typename std::enable_if<(2 < sizeof(T))>::type> {\n  using type = uint_least64_t;\n\
    };\ntemplate <typename T>\nstruct multiplicable_uint<T, typename std::enable_if<(4\
    \ < sizeof(T))>::type> {\n  using type = __uint128_t;\n};\n#line 6 \"modulus/modint.hpp\"\
    \n\ntemplate <auto Mod = 0, typename Mod_type = decltype(Mod)> struct modint {\n\
    \  static_assert(is_integral_ext<decltype(Mod)>::value,\n                \"Mod\
    \ must be integral type.\");\n  static_assert(!(Mod < 0), \"Mod must be non-negative.\"\
    );\n\n  using mod_type = typename std::conditional<\n      Mod != 0, typename\
    \ std::add_const<Mod_type>::type, Mod_type>::type;\n  static mod_type mod;\n\n\
    \  using value_type = typename std::decay<mod_type>::type;\n\n  constexpr operator\
    \ value_type() const noexcept { return value; }\n\n  constexpr static modint one()\
    \ noexcept { return 1; }\n\n  constexpr modint() noexcept = default;\n\n  template\
    \ <class int_type,\n            typename std::enable_if<is_integral_ext<int_type>::value>::type\
    \ * =\n                nullptr>\n  constexpr modint(int_type n) noexcept : value((n\
    \ %= mod) < 0 ? mod + n : n) {}\n\n  constexpr modint(bool n) noexcept : modint(int(n))\
    \ {}\n\n  constexpr modint operator++(int) noexcept {\n    modint t{*this};\n\
    \    return operator+=(1), t;\n  }\n\n  constexpr modint operator--(int) noexcept\
    \ {\n    modint t{*this};\n    return operator-=(1), t;\n  }\n\n  constexpr modint\
    \ &operator++() noexcept { return operator+=(1); }\n\n  constexpr modint &operator--()\
    \ noexcept { return operator-=(1); }\n\n  constexpr modint operator-() const noexcept\
    \ {\n    return value ? mod - value : 0;\n  }\n\n  constexpr modint &operator+=(const\
    \ modint &rhs) noexcept {\n    return (value += rhs.value) < mod ? 0 : value -=\
    \ mod, *this;\n  }\n\n  constexpr modint &operator-=(const modint &rhs) noexcept\
    \ {\n    return (value += mod - rhs.value) < mod ? 0 : value -= mod, *this;\n\
    \  }\n\n  constexpr modint &operator*=(const modint &rhs) noexcept {\n    return\
    \ value = (typename multiplicable_uint<value_type>::type)value *\n           \
    \        rhs.value % mod,\n           *this;\n  }\n\n  constexpr modint &operator/=(const\
    \ modint &rhs) noexcept {\n    return operator*=(rhs.inverse());\n  }\n\n  template\
    \ <class int_type>\n  constexpr\n      typename std::enable_if<is_integral_ext<int_type>::value,\
    \ modint>::type\n      operator+(const int_type &rhs) const noexcept {\n    return\
    \ modint{*this} += rhs;\n  }\n\n  constexpr modint operator+(const modint &rhs)\
    \ const noexcept {\n    return modint{*this} += rhs;\n  }\n\n  template <class\
    \ int_type>\n  constexpr\n      typename std::enable_if<is_integral_ext<int_type>::value,\
    \ modint>::type\n      operator-(const int_type &rhs) const noexcept {\n    return\
    \ modint{*this} -= rhs;\n  }\n\n  constexpr modint operator-(const modint &rhs)\
    \ const noexcept {\n    return modint{*this} -= rhs;\n  }\n\n  template <class\
    \ int_type>\n  constexpr\n      typename std::enable_if<is_integral_ext<int_type>::value,\
    \ modint>::type\n      operator*(const int_type &rhs) const noexcept {\n    return\
    \ modint{*this} *= rhs;\n  }\n\n  constexpr modint operator*(const modint &rhs)\
    \ const noexcept {\n    return modint{*this} *= rhs;\n  }\n\n  template <class\
    \ int_type>\n  constexpr\n      typename std::enable_if<is_integral_ext<int_type>::value,\
    \ modint>::type\n      operator/(const int_type &rhs) const noexcept {\n    return\
    \ modint{*this} /= rhs;\n  }\n\n  constexpr modint operator/(const modint &rhs)\
    \ const noexcept {\n    return modint{*this} /= rhs;\n  }\n\n  template <class\
    \ int_type>\n  constexpr friend\n      typename std::enable_if<is_integral_ext<int_type>::value,\
    \ modint>::type\n      operator+(const int_type &lhs, const modint &rhs) noexcept\
    \ {\n    return modint(lhs) + rhs;\n  }\n\n  template <class int_type>\n  constexpr\
    \ friend\n      typename std::enable_if<is_integral_ext<int_type>::value, modint>::type\n\
    \      operator-(const int_type &lhs, const modint &rhs) noexcept {\n    return\
    \ modint(lhs) - rhs;\n  }\n\n  template <class int_type>\n  constexpr friend\n\
    \      typename std::enable_if<is_integral_ext<int_type>::value, modint>::type\n\
    \      operator*(const int_type &lhs, const modint &rhs) noexcept {\n    return\
    \ modint(lhs) * rhs;\n  }\n\n  template <class int_type>\n  constexpr friend\n\
    \      typename std::enable_if<is_integral_ext<int_type>::value, modint>::type\n\
    \      operator/(const int_type &lhs, const modint &rhs) noexcept {\n    return\
    \ modint(lhs) / rhs;\n  }\n\n  constexpr modint inverse() const noexcept {\n \
    \   assert(value);\n    value_type a{mod}, b{value}, u{}, v{1}, t{};\n    while\
    \ (b)\n      t = a / b, a ^= b ^= (a -= t * b) ^= b, u ^= v ^= (u -= t * v) ^=\
    \ v;\n    return {u};\n  }\n\n  template <class int_type>\n  constexpr\n     \
    \ typename std::enable_if<is_integral_ext<int_type>::value, modint>::type\n  \
    \    power(int_type e) noexcept {\n    if (e < 0) e = e % (mod - 1) + mod - 1;\n\
    \    modint res{1};\n    for (modint p{value}; e; e >>= 1, p *= p) {\n      if\
    \ (e & 1) res *= p;\n    }\n    return res;\n  }\n\n  template <class int_type>\n\
    \  friend constexpr\n      typename std::enable_if<is_integral_ext<int_type>::value,\
    \ modint>::type\n      pow(modint b, int_type e) noexcept {\n    modint res{1};\n\
    \    for ((e %= mod - 1) < 0 ? e += mod - 1 : 0; e; e >>= 1, b *= b)\n      if\
    \ (e & 1) res *= b;\n    return res;\n  }\n\n  friend std::ostream &operator<<(std::ostream\
    \ &os,\n                                  const modint &rhs) noexcept {\n    return\
    \ os << rhs.value;\n  }\n\n  friend std::istream &operator>>(std::istream &is,\
    \ modint &rhs) noexcept {\n    intmax_t value;\n    rhs = (is >> value, value);\n\
    \    return is;\n  }\n\n protected:\n  value_type value = 0;\n};\n\ntemplate <auto\
    \ Mod, typename Mod_type>\ntypename modint<Mod, Mod_type>::mod_type modint<Mod,\
    \ Mod_type>::mod = Mod;\n\nusing modint_runtime = modint<0>;\n#line 6 \"test/library-checker/queue_operate_all_composite.test.cpp\"\
    \n\nint main() {\n  using mint = modint<998244353>;\n  struct mono {\n    mint\
    \ a = 1, b;\n    mono operator+(const mono& rhs) const {\n      auto [c, d] =\
    \ rhs;\n      return {a * c, b * c + d};\n    }\n  };\n  deque_aggregation<mono>\
    \ deq;\n  int q;\n  scanf(\"%d\", &q);\n  while (q--) {\n    int t;\n    scanf(\"\
    %d\", &t);\n    if (t == 0) {\n      int a, b;\n      scanf(\"%d%d\", &a, &b);\n\
    \      deq.push_back({a, b});\n    } else if (t == 1) {\n      deq.pop_front();\n\
    \    } else {\n      int x;\n      scanf(\"%d\", &x);\n      auto [a, b] = deq.fold();\n\
    \      printf(\"%d\\n\", a * x + b);\n    }\n  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/queue_operate_all_composite\"\
    \n#include <cstdio>\n\n#include \"data_structure/deque_aggregation.hpp\"\n#include\
    \ \"modulus/modint.hpp\"\n\nint main() {\n  using mint = modint<998244353>;\n\
    \  struct mono {\n    mint a = 1, b;\n    mono operator+(const mono& rhs) const\
    \ {\n      auto [c, d] = rhs;\n      return {a * c, b * c + d};\n    }\n  };\n\
    \  deque_aggregation<mono> deq;\n  int q;\n  scanf(\"%d\", &q);\n  while (q--)\
    \ {\n    int t;\n    scanf(\"%d\", &t);\n    if (t == 0) {\n      int a, b;\n\
    \      scanf(\"%d%d\", &a, &b);\n      deq.push_back({a, b});\n    } else if (t\
    \ == 1) {\n      deq.pop_front();\n    } else {\n      int x;\n      scanf(\"\
    %d\", &x);\n      auto [a, b] = deq.fold();\n      printf(\"%d\\n\", a * x + b);\n\
    \    }\n  }\n}\n"
  dependsOn:
  - data_structure/deque_aggregation.hpp
  - modulus/modint.hpp
  - utils/sfinae.hpp
  isVerificationFile: true
  path: test/library-checker/queue_operate_all_composite.test.cpp
  requiredBy: []
  timestamp: '2020-09-21 02:49:05+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/library-checker/queue_operate_all_composite.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/queue_operate_all_composite.test.cpp
- /verify/test/library-checker/queue_operate_all_composite.test.cpp.html
title: test/library-checker/queue_operate_all_composite.test.cpp
---
