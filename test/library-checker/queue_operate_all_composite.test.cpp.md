---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/data_structure/deque_aggregation.hpp
    title: src/data_structure/deque_aggregation.hpp
  - icon: ':heavy_check_mark:'
    path: src/modular/modint.hpp
    title: Modular Arithmetic
  - icon: ':heavy_check_mark:'
    path: src/utils/sfinae.hpp
    title: SFINAE
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
    \n\n#include <cstdio>\n\n#line 2 \"src/data_structure/deque_aggregation.hpp\"\n\
    #include <cassert>\n#include <iterator>\n// implementation with dynamic memory\
    \ allocation.\ntemplate <class monoid>\nclass deque_aggregation\n{\n    template\
    \ <bool left_operand_added>\n    class stack_aggregation\n    {\n        friend\
    \ deque_aggregation;\n        struct data { monoid value, acc; };\n        size_t\
    \ capacity;\n        data *stack, *end, *itr;\n        bool top_referred;\n\n\
    \        void recalc()\n        {\n            if(top_referred)\n            {\n\
    \                assert(itr != stack);\n                top_referred = false;\n\
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
    \ { return left.fold() + right.fold(); }\n}; // class deque_aggregation\n#line\
    \ 2 \"src/modular/modint.hpp\"\n\n/*\n * @file modint.hpp\n * @brief Modular Arithmetic\n\
    \ */\n\n#line 9 \"src/modular/modint.hpp\"\n#include <iostream>\n\n#line 2 \"\
    src/utils/sfinae.hpp\"\n\n/*\n * @file sfinae.hpp\n * @brief SFINAE\n */\n\n#include\
    \ <cstdint>\n#line 10 \"src/utils/sfinae.hpp\"\n#include <type_traits>\n\n#ifdef\
    \ __SIZEOF_INT128__\n#define __INT128_DEFINED__ 1\n#else\n#define __INT128_DEFINED__\
    \ 0\n#endif\n\nnamespace std {\n\n#if __INT128_DEFINED__\n\ntemplate <> struct\
    \ make_signed<__uint128_t> { using type = __int128_t; };\ntemplate <> struct make_signed<__int128_t>\
    \ { using type = __int128_t; };\n\ntemplate <> struct make_unsigned<__uint128_t>\
    \ { using type = __uint128_t; };\ntemplate <> struct make_unsigned<__int128_t>\
    \ { using type = __uint128_t; };\n\n#endif\n\n}  // namespace std\n\nnamespace\
    \ workspace {\n\ntemplate <class type, template <class> class trait>\nusing enable_if_trait_type\
    \ = typename std::enable_if<trait<type>::value>::type;\n\ntemplate <class Container>\n\
    using element_type = typename std::decay<decltype(\n    *std::begin(std::declval<Container&>()))>::type;\n\
    \ntemplate <class T, class = std::nullptr_t>\nstruct has_begin : std::false_type\
    \ {};\n\ntemplate <class T>\nstruct has_begin<T, decltype(std::begin(std::declval<T>()),\
    \ nullptr)>\n    : std::true_type {};\n\ntemplate <class T, class = int> struct\
    \ mapped_of {\n  using type = element_type<T>;\n};\ntemplate <class T>\nstruct\
    \ mapped_of<T,\n                 typename std::pair<int, typename T::mapped_type>::first_type>\
    \ {\n  using type = typename T::mapped_type;\n};\ntemplate <class T> using mapped_type\
    \ = typename mapped_of<T>::type;\n\ntemplate <class T, class = void> struct is_integral_ext\
    \ : std::false_type {};\ntemplate <class T>\nstruct is_integral_ext<\n    T, typename\
    \ std::enable_if<std::is_integral<T>::value>::type>\n    : std::true_type {};\n\
    \n#if __INT128_DEFINED__\n\ntemplate <> struct is_integral_ext<__int128_t> : std::true_type\
    \ {};\ntemplate <> struct is_integral_ext<__uint128_t> : std::true_type {};\n\n\
    #endif\n\n#if __cplusplus >= 201402\n\ntemplate <class T>\nconstexpr static bool\
    \ is_integral_ext_v = is_integral_ext<T>::value;\n\n#endif\n\ntemplate <typename\
    \ T, typename = void> struct multiplicable_uint {\n  using type = uint_least32_t;\n\
    };\ntemplate <typename T>\nstruct multiplicable_uint<\n    T, typename std::enable_if<(2\
    \ < sizeof(T)) &&\n                               (!__INT128_DEFINED__ || sizeof(T)\
    \ <= 4)>::type> {\n  using type = uint_least64_t;\n};\n\n#if __INT128_DEFINED__\n\
    \ntemplate <typename T>\nstruct multiplicable_uint<T, typename std::enable_if<(4\
    \ < sizeof(T))>::type> {\n  using type = __uint128_t;\n};\n\n#endif\n\n}  // namespace\
    \ workspace\n#line 12 \"src/modular/modint.hpp\"\n\nnamespace workspace {\n\n\
    namespace internal {\n\n/*\n * @struct modint_base\n * @brief base of modular\
    \ arithmetic.\n * @tparam Mod identifier, which represents modulus if positive\n\
    \ */\ntemplate <auto Mod> struct modint_base {\n  static_assert(is_integral_ext<decltype(Mod)>::value,\n\
    \                \"Mod must be integral type.\");\n\n  using mod_type =\n    \
    \  typename std::conditional<0 < Mod,\n                                typename\
    \ std::add_const<decltype(Mod)>::type,\n                                decltype(Mod)>::type;\n\
    \  static mod_type mod;\n\n  using value_type = typename std::decay<mod_type>::type;\n\
    \n  constexpr operator value_type() const noexcept { return value; }\n\n  constexpr\
    \ static modint_base one() noexcept { return 1; }\n\n  constexpr modint_base()\
    \ noexcept = default;\n\n  template <class int_type,\n            typename std::enable_if<is_integral_ext<int_type>::value>::type\
    \ * =\n                nullptr>\n  constexpr modint_base(int_type n) noexcept\n\
    \      : value((n %= mod) < 0 ? mod + n : n) {}\n\n  constexpr modint_base(bool\
    \ n) noexcept : modint_base(int(n)) {}\n\n  constexpr modint_base operator++(int)\
    \ noexcept {\n    modint_base t{*this};\n    return operator+=(1), t;\n  }\n\n\
    \  constexpr modint_base operator--(int) noexcept {\n    modint_base t{*this};\n\
    \    return operator-=(1), t;\n  }\n\n  constexpr modint_base &operator++() noexcept\
    \ { return operator+=(1); }\n\n  constexpr modint_base &operator--() noexcept\
    \ { return operator-=(1); }\n\n  constexpr modint_base operator-() const noexcept\
    \ {\n    return value ? mod - value : 0;\n  }\n\n  constexpr modint_base &operator+=(const\
    \ modint_base &rhs) noexcept {\n    return (value += rhs.value) < mod ? 0 : value\
    \ -= mod, *this;\n  }\n\n  constexpr modint_base &operator-=(const modint_base\
    \ &rhs) noexcept {\n    return (value += mod - rhs.value) < mod ? 0 : value -=\
    \ mod, *this;\n  }\n\n  constexpr modint_base &operator*=(const modint_base &rhs)\
    \ noexcept {\n    return value = (typename multiplicable_uint<value_type>::type)value\
    \ *\n                   rhs.value % mod,\n           *this;\n  }\n\n  constexpr\
    \ modint_base &operator/=(const modint_base &rhs) noexcept {\n    return operator*=(rhs.inverse());\n\
    \  }\n\n  template <class int_type>\n  constexpr typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                    modint_base>::type\n  operator+(const int_type\
    \ &rhs) const noexcept {\n    return modint_base{*this} += rhs;\n  }\n\n  constexpr\
    \ modint_base operator+(const modint_base &rhs) const noexcept {\n    return modint_base{*this}\
    \ += rhs;\n  }\n\n  template <class int_type>\n  constexpr typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                    modint_base>::type\n  operator-(const int_type\
    \ &rhs) const noexcept {\n    return modint_base{*this} -= rhs;\n  }\n\n  constexpr\
    \ modint_base operator-(const modint_base &rhs) const noexcept {\n    return modint_base{*this}\
    \ -= rhs;\n  }\n\n  template <class int_type>\n  constexpr typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                    modint_base>::type\n  operator*(const int_type\
    \ &rhs) const noexcept {\n    return modint_base{*this} *= rhs;\n  }\n\n  constexpr\
    \ modint_base operator*(const modint_base &rhs) const noexcept {\n    return modint_base{*this}\
    \ *= rhs;\n  }\n\n  template <class int_type>\n  constexpr typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                    modint_base>::type\n  operator/(const int_type\
    \ &rhs) const noexcept {\n    return modint_base{*this} /= rhs;\n  }\n\n  constexpr\
    \ modint_base operator/(const modint_base &rhs) const noexcept {\n    return modint_base{*this}\
    \ /= rhs;\n  }\n\n  template <class int_type>\n  constexpr friend typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                           modint_base>::type\n  operator+(const\
    \ int_type &lhs, const modint_base &rhs) noexcept {\n    return modint_base(lhs)\
    \ + rhs;\n  }\n\n  template <class int_type>\n  constexpr friend typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                           modint_base>::type\n  operator-(const\
    \ int_type &lhs, const modint_base &rhs) noexcept {\n    return modint_base(lhs)\
    \ - rhs;\n  }\n\n  template <class int_type>\n  constexpr friend typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                           modint_base>::type\n  operator*(const\
    \ int_type &lhs, const modint_base &rhs) noexcept {\n    return modint_base(lhs)\
    \ * rhs;\n  }\n\n  template <class int_type>\n  constexpr friend typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                           modint_base>::type\n  operator/(const\
    \ int_type &lhs, const modint_base &rhs) noexcept {\n    return modint_base(lhs)\
    \ / rhs;\n  }\n\n  constexpr modint_base inverse() const noexcept {\n    assert(value);\n\
    \    value_type a{mod}, b{value}, u{}, v{1}, t{};\n    while (b)\n      t = a\
    \ / b, a ^= b ^= (a -= t * b) ^= b, u ^= v ^= (u -= t * v) ^= v;\n    return {u};\n\
    \  }\n\n  template <class int_type>\n  constexpr typename std::enable_if<is_integral_ext<int_type>::value,\n\
    \                                    modint_base>::type\n  power(int_type e) noexcept\
    \ {\n    return pow(*this, e);\n  }\n\n  template <class int_type>\n  friend constexpr\
    \ typename std::enable_if<is_integral_ext<int_type>::value,\n                \
    \                           modint_base>::type\n  pow(modint_base b, int_type\
    \ e) noexcept {\n    modint_base res{1};\n    for (e < 0 ? b = b.inverse(), e\
    \ = -e : 0; e; e >>= 1, b *= b)\n      if (e & 1) res *= b;\n    return res;\n\
    \  }\n\n  friend std::ostream &operator<<(std::ostream &os,\n                \
    \                  const modint_base &rhs) noexcept {\n    return os << rhs.value;\n\
    \  }\n\n  friend std::istream &operator>>(std::istream &is, modint_base &rhs)\
    \ noexcept {\n    intmax_t value;\n    rhs = (is >> value, value);\n    return\
    \ is;\n  }\n\n protected:\n  value_type value = 0;\n};\n\ntemplate <auto Mod>\n\
    typename modint_base<Mod>::mod_type modint_base<Mod>::mod = Mod;\n\n}  // namespace\
    \ internal\n\n/*\n * @typedef modint\n * @brief modular arithmetic.\n * @tparam\
    \ Mod modulus\n */\ntemplate <auto Mod, typename std::enable_if<(Mod > 0)>::type\
    \ * = nullptr>\nusing modint = internal::modint_base<Mod>;\n\n/*\n * @typedef\
    \ modint_runtime\n * @brief runtime modular arithmetic.\n * @tparam type_id uniquely\
    \ assigned\n */\ntemplate <unsigned type_id = 0>\nusing modint_runtime = internal::modint_base<-(signed)type_id>;\n\
    \n// #define modint_newtype modint_runtime<__COUNTER__>\n\n}  // namespace workspace\n\
    #line 7 \"test/library-checker/queue_operate_all_composite.test.cpp\"\n\nint main()\
    \ {\n  using mint = workspace::modint<998244353>;\n  struct mono {\n    mint a\
    \ = 1, b;\n    mono operator+(const mono& rhs) const {\n      auto [c, d] = rhs;\n\
    \      return {a * c, b * c + d};\n    }\n  };\n  deque_aggregation<mono> deq;\n\
    \  int q;\n  scanf(\"%d\", &q);\n  while (q--) {\n    int t;\n    scanf(\"%d\"\
    , &t);\n    if (t == 0) {\n      int a, b;\n      scanf(\"%d%d\", &a, &b);\n \
    \     deq.push_back({a, b});\n    } else if (t == 1) {\n      deq.pop_front();\n\
    \    } else {\n      int x;\n      scanf(\"%d\", &x);\n      auto [a, b] = deq.fold();\n\
    \      printf(\"%d\\n\", a * x + b);\n    }\n  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/queue_operate_all_composite\"\
    \n\n#include <cstdio>\n\n#include \"src/data_structure/deque_aggregation.hpp\"\
    \n#include \"src/modular/modint.hpp\"\n\nint main() {\n  using mint = workspace::modint<998244353>;\n\
    \  struct mono {\n    mint a = 1, b;\n    mono operator+(const mono& rhs) const\
    \ {\n      auto [c, d] = rhs;\n      return {a * c, b * c + d};\n    }\n  };\n\
    \  deque_aggregation<mono> deq;\n  int q;\n  scanf(\"%d\", &q);\n  while (q--)\
    \ {\n    int t;\n    scanf(\"%d\", &t);\n    if (t == 0) {\n      int a, b;\n\
    \      scanf(\"%d%d\", &a, &b);\n      deq.push_back({a, b});\n    } else if (t\
    \ == 1) {\n      deq.pop_front();\n    } else {\n      int x;\n      scanf(\"\
    %d\", &x);\n      auto [a, b] = deq.fold();\n      printf(\"%d\\n\", a * x + b);\n\
    \    }\n  }\n}\n"
  dependsOn:
  - src/data_structure/deque_aggregation.hpp
  - src/modular/modint.hpp
  - src/utils/sfinae.hpp
  isVerificationFile: true
  path: test/library-checker/queue_operate_all_composite.test.cpp
  requiredBy: []
  timestamp: '2020-12-21 17:31:55+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/library-checker/queue_operate_all_composite.test.cpp
layout: document
redirect_from:
- /verify/test/library-checker/queue_operate_all_composite.test.cpp
- /verify/test/library-checker/queue_operate_all_composite.test.cpp.html
title: test/library-checker/queue_operate_all_composite.test.cpp
---
