---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: src/utils/sfinae.hpp
    title: SFINAE
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/2450.test.cpp
    title: test/aizu-online-judge/2450.test.cpp
  - icon: ':x:'
    path: test/library-checker/bitwise_xor_convolution.test.cpp
    title: test/library-checker/bitwise_xor_convolution.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    document_title: Input Stream
    links: []
  bundledCode: "#line 2 \"src/utils/io/istream.hpp\"\n\n/*\n * @file stream.hpp\n\
    \ * @brief Input Stream\n */\n\n#include <cxxabi.h>\n\n#include <cassert>\n#include\
    \ <iostream>\n#include <tuple>\n\n#line 2 \"src/utils/sfinae.hpp\"\n\n/*\n * @file\
    \ sfinae.hpp\n * @brief SFINAE\n */\n\n#include <cstdint>\n#include <iterator>\n\
    #include <type_traits>\n\n#ifdef __SIZEOF_INT128__\n#define __INT128_DEFINED__\
    \ 1\n#else\n#define __INT128_DEFINED__ 0\n#endif\n\nnamespace std {\n\n#if __INT128_DEFINED__\n\
    \ntemplate <> struct make_signed<__uint128_t> { using type = __int128_t; };\n\
    template <> struct make_signed<__int128_t> { using type = __int128_t; };\n\ntemplate\
    \ <> struct make_unsigned<__uint128_t> { using type = __uint128_t; };\ntemplate\
    \ <> struct make_unsigned<__int128_t> { using type = __uint128_t; };\n\n#endif\n\
    \n}  // namespace std\n\nnamespace workspace {\n\ntemplate <class type, template\
    \ <class> class trait>\nusing enable_if_trait_type = typename std::enable_if<trait<type>::value>::type;\n\
    \ntemplate <class Container>\nusing element_type = typename std::decay<decltype(\n\
    \    *std::begin(std::declval<Container&>()))>::type;\n\ntemplate <class T, class\
    \ = std::nullptr_t>\nstruct has_begin : std::false_type {};\n\ntemplate <class\
    \ T>\nstruct has_begin<T, decltype(std::begin(std::declval<T>()), nullptr)>\n\
    \    : std::true_type {};\n\ntemplate <class T, class = int> struct mapped_of\
    \ {\n  using type = element_type<T>;\n};\ntemplate <class T>\nstruct mapped_of<T,\n\
    \                 typename std::pair<int, typename T::mapped_type>::first_type>\
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
    \ workspace\n#line 15 \"src/utils/io/istream.hpp\"\n\nnamespace workspace {\n\n\
    namespace internal {\n\ntemplate <class Tp, typename = std::nullptr_t> struct\
    \ istream_helper {\n  istream_helper(std::istream &is, Tp &x) {\n    if constexpr\
    \ (has_begin<Tp>::value)\n      for (auto &&e : x)\n        istream_helper<typename\
    \ std::decay<decltype(e)>::type>(is, e);\n    else\n      static_assert(has_begin<Tp>::value,\
    \ \"istream unsupported type.\");\n  }\n};\n\ntemplate <class Tp>\nstruct istream_helper<\n\
    \    Tp,\n    decltype(std::declval<std::decay<decltype(std::declval<std::istream\
    \ &>() >>\n                                              std::declval<Tp &>())>>(),\n\
    \             nullptr)> {\n  istream_helper(std::istream &is, Tp &x) { is >> x;\
    \ }\n};\n\n#ifdef __SIZEOF_INT128__\n\ntemplate <> struct istream_helper<__int128_t,\
    \ std::nullptr_t> {\n  istream_helper(std::istream &is, __int128_t &x) {\n   \
    \ std::string s;\n    is >> s;\n    bool negative = s.front() == '-' ? s.erase(s.begin()),\
    \ true : false;\n    x = 0;\n    for (char e : s) x = x * 10 + e - '0';\n    if\
    \ (negative) x = -x;\n  }\n};\n\ntemplate <> struct istream_helper<__uint128_t,\
    \ std::nullptr_t> {\n  istream_helper(std::istream &is, __uint128_t &x) {\n  \
    \  std::string s;\n    is >> s;\n    bool negative = s.front() == '-' ? s.erase(s.begin()),\
    \ true : false;\n    x = 0;\n    for (char e : s) x = x * 10 + e - '0';\n    if\
    \ (negative) x = -x;\n  }\n};\n\n#endif  // INT128\n\ntemplate <class T1, class\
    \ T2> struct istream_helper<std::pair<T1, T2>> {\n  istream_helper(std::istream\
    \ &is, std::pair<T1, T2> &x) {\n    istream_helper<T1>(is, x.first), istream_helper<T2>(is,\
    \ x.second);\n  }\n};\n\ntemplate <class... Tps> struct istream_helper<std::tuple<Tps...>>\
    \ {\n  istream_helper(std::istream &is, std::tuple<Tps...> &x) { iterate(is, x);\
    \ }\n\n private:\n  template <class Tp, size_t N = 0> void iterate(std::istream\
    \ &is, Tp &x) {\n    if constexpr (N == std::tuple_size<Tp>::value)\n      return;\n\
    \    else\n      istream_helper<typename std::tuple_element<N, Tp>::type>(is,\n\
    \                                                               std::get<N>(x)),\n\
    \          iterate<Tp, N + 1>(is, x);\n  }\n};\n\n}  // namespace internal\n\n\
    /**\n * @brief A wrapper class for std::istream.\n */\nclass istream : public\
    \ std::istream {\n public:\n  /**\n   * @brief Wrapped operator.\n   */\n  template\
    \ <typename Tp> istream &operator>>(Tp &x) {\n    internal::istream_helper<Tp>(*this,\
    \ x);\n    if (std::istream::fail()) {\n      static auto once = atexit([] {\n\
    \        std::cerr << \"\\n\\033[43m\\033[30mwarning: failed to read \\'\"\n \
    \                 << abi::__cxa_demangle(typeid(Tp).name(), 0, 0, 0)\n       \
    \           << \"\\'.\\033[0m\\n\\n\";\n      });\n      assert(!once);\n    }\n\
    \    return *this;\n  }\n};\n\nnamespace internal {\nauto *const cin_ptr = (istream\
    \ *)&std::cin;\n}\nauto &cin = *internal::cin_ptr;\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/*\n * @file stream.hpp\n * @brief Input Stream\n */\n\n\
    #include <cxxabi.h>\n\n#include <cassert>\n#include <iostream>\n#include <tuple>\n\
    \n#include \"src/utils/sfinae.hpp\"\n\nnamespace workspace {\n\nnamespace internal\
    \ {\n\ntemplate <class Tp, typename = std::nullptr_t> struct istream_helper {\n\
    \  istream_helper(std::istream &is, Tp &x) {\n    if constexpr (has_begin<Tp>::value)\n\
    \      for (auto &&e : x)\n        istream_helper<typename std::decay<decltype(e)>::type>(is,\
    \ e);\n    else\n      static_assert(has_begin<Tp>::value, \"istream unsupported\
    \ type.\");\n  }\n};\n\ntemplate <class Tp>\nstruct istream_helper<\n    Tp,\n\
    \    decltype(std::declval<std::decay<decltype(std::declval<std::istream &>()\
    \ >>\n                                              std::declval<Tp &>())>>(),\n\
    \             nullptr)> {\n  istream_helper(std::istream &is, Tp &x) { is >> x;\
    \ }\n};\n\n#ifdef __SIZEOF_INT128__\n\ntemplate <> struct istream_helper<__int128_t,\
    \ std::nullptr_t> {\n  istream_helper(std::istream &is, __int128_t &x) {\n   \
    \ std::string s;\n    is >> s;\n    bool negative = s.front() == '-' ? s.erase(s.begin()),\
    \ true : false;\n    x = 0;\n    for (char e : s) x = x * 10 + e - '0';\n    if\
    \ (negative) x = -x;\n  }\n};\n\ntemplate <> struct istream_helper<__uint128_t,\
    \ std::nullptr_t> {\n  istream_helper(std::istream &is, __uint128_t &x) {\n  \
    \  std::string s;\n    is >> s;\n    bool negative = s.front() == '-' ? s.erase(s.begin()),\
    \ true : false;\n    x = 0;\n    for (char e : s) x = x * 10 + e - '0';\n    if\
    \ (negative) x = -x;\n  }\n};\n\n#endif  // INT128\n\ntemplate <class T1, class\
    \ T2> struct istream_helper<std::pair<T1, T2>> {\n  istream_helper(std::istream\
    \ &is, std::pair<T1, T2> &x) {\n    istream_helper<T1>(is, x.first), istream_helper<T2>(is,\
    \ x.second);\n  }\n};\n\ntemplate <class... Tps> struct istream_helper<std::tuple<Tps...>>\
    \ {\n  istream_helper(std::istream &is, std::tuple<Tps...> &x) { iterate(is, x);\
    \ }\n\n private:\n  template <class Tp, size_t N = 0> void iterate(std::istream\
    \ &is, Tp &x) {\n    if constexpr (N == std::tuple_size<Tp>::value)\n      return;\n\
    \    else\n      istream_helper<typename std::tuple_element<N, Tp>::type>(is,\n\
    \                                                               std::get<N>(x)),\n\
    \          iterate<Tp, N + 1>(is, x);\n  }\n};\n\n}  // namespace internal\n\n\
    /**\n * @brief A wrapper class for std::istream.\n */\nclass istream : public\
    \ std::istream {\n public:\n  /**\n   * @brief Wrapped operator.\n   */\n  template\
    \ <typename Tp> istream &operator>>(Tp &x) {\n    internal::istream_helper<Tp>(*this,\
    \ x);\n    if (std::istream::fail()) {\n      static auto once = atexit([] {\n\
    \        std::cerr << \"\\n\\033[43m\\033[30mwarning: failed to read \\'\"\n \
    \                 << abi::__cxa_demangle(typeid(Tp).name(), 0, 0, 0)\n       \
    \           << \"\\'.\\033[0m\\n\\n\";\n      });\n      assert(!once);\n    }\n\
    \    return *this;\n  }\n};\n\nnamespace internal {\nauto *const cin_ptr = (istream\
    \ *)&std::cin;\n}\nauto &cin = *internal::cin_ptr;\n\n}  // namespace workspace\n"
  dependsOn:
  - src/utils/sfinae.hpp
  isVerificationFile: false
  path: src/utils/io/istream.hpp
  requiredBy: []
  timestamp: '2020-12-21 17:31:55+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/library-checker/bitwise_xor_convolution.test.cpp
  - test/aizu-online-judge/2450.test.cpp
documentation_of: src/utils/io/istream.hpp
layout: document
redirect_from:
- /library/src/utils/io/istream.hpp
- /library/src/utils/io/istream.hpp.html
title: Input Stream
---
