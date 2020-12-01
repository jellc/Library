---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/utils/sfinae.hpp
    title: SFINAE
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aizu-online-judge/2450.test.cpp
    title: test/aizu-online-judge/2450.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Input Stream
    links: []
  bundledCode: "#line 2 \"src/utils/io/istream.hpp\"\n\n/*\n * @file stream.hpp\n\
    \ * @brief Input Stream\n */\n\n#include <cxxabi.h>\n\n#include <cassert>\n#include\
    \ <iostream>\n#include <tuple>\n\n#line 2 \"src/utils/sfinae.hpp\"\n\n/*\n * @file\
    \ sfinae.hpp\n * @brief SFINAE\n */\n\n#include <cstdint>\n#include <iterator>\n\
    #include <type_traits>\n\nnamespace workspace {\n\ntemplate <class type, template\
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
    template <> struct is_integral_ext<__int128_t> : std::true_type {};\ntemplate\
    \ <> struct is_integral_ext<__uint128_t> : std::true_type {};\n#if __cplusplus\
    \ >= 201402\ntemplate <class T>\nconstexpr static bool is_integral_ext_v = is_integral_ext<T>::value;\n\
    #endif\n\ntemplate <typename T, typename = void> struct multiplicable_uint {\n\
    \  using type = uint_least32_t;\n};\ntemplate <typename T>\nstruct multiplicable_uint<T,\
    \ typename std::enable_if<(2 < sizeof(T))>::type> {\n  using type = uint_least64_t;\n\
    };\ntemplate <typename T>\nstruct multiplicable_uint<T, typename std::enable_if<(4\
    \ < sizeof(T))>::type> {\n  using type = __uint128_t;\n};\n\n}  // namespace workspace\n\
    #line 15 \"src/utils/io/istream.hpp\"\n\nnamespace workspace {\n\n/*\n * @class\
    \ istream\n * @brief A wrapper class for std::istream.\n */\nclass istream : public\
    \ std::istream {\n  template <class Tp, typename = std::nullptr_t> struct helper\
    \ {\n    helper(std::istream &is, Tp &x) {\n      if constexpr (has_begin<Tp>::value)\n\
    \        for (auto &&e : x)\n          helper<typename std::decay<decltype(e)>::type>(is,\
    \ e);\n      else\n        static_assert(has_begin<Tp>::value, \"istream unsupported\
    \ type.\");\n    }\n  };\n\n  template <class Tp>\n  struct helper<\n      Tp,\n\
    \      decltype(std::declval<std::decay<decltype(\n                   std::declval<std::istream\
    \ &>() >> std::declval<Tp &>())>>(),\n               nullptr)> {\n    helper(std::istream\
    \ &is, Tp &x) { is >> x; }\n  };\n\n  template <class T1, class T2> struct helper<std::pair<T1,\
    \ T2>> {\n    helper(std::istream &is, std::pair<T1, T2> &x) {\n      helper<T1>(is,\
    \ x.first), helper<T2>(is, x.second);\n    }\n  };\n\n  template <class... Tps>\
    \ struct helper<std::tuple<Tps...>> {\n    helper(std::istream &is, std::tuple<Tps...>\
    \ &x) { iterate(is, x); }\n\n   private:\n    template <class Tp, size_t N = 0>\
    \ void iterate(std::istream &is, Tp &x) {\n      if constexpr (N == std::tuple_size<Tp>::value)\n\
    \        return;\n      else\n        helper<typename std::tuple_element<N, Tp>::type>(is,\
    \ std::get<N>(x)),\n            iterate<Tp, N + 1>(is, x);\n    }\n  };\n\n public:\n\
    \  template <typename Tp> istream &operator>>(Tp &x) {\n    helper<Tp>(*this,\
    \ x);\n    if (std::istream::fail()) {\n      static auto once = atexit([] {\n\
    \        std::cerr << \"\\n\\033[43m\\033[30mwarning: failed to read \\'\"\n \
    \                 << abi::__cxa_demangle(typeid(Tp).name(), 0, 0, 0)\n       \
    \           << \"\\'.\\033[0m\\n\\n\";\n      });\n      assert(!once);\n    }\n\
    \    return *this;\n  }\n};\n\nnamespace internal {\nauto *const cin_ptr = (istream\
    \ *)&std::cin;\n}\nauto &cin = *internal::cin_ptr;\n\n}  // namespace workspace\n"
  code: "#pragma once\n\n/*\n * @file stream.hpp\n * @brief Input Stream\n */\n\n\
    #include <cxxabi.h>\n\n#include <cassert>\n#include <iostream>\n#include <tuple>\n\
    \n#include \"src/utils/sfinae.hpp\"\n\nnamespace workspace {\n\n/*\n * @class\
    \ istream\n * @brief A wrapper class for std::istream.\n */\nclass istream : public\
    \ std::istream {\n  template <class Tp, typename = std::nullptr_t> struct helper\
    \ {\n    helper(std::istream &is, Tp &x) {\n      if constexpr (has_begin<Tp>::value)\n\
    \        for (auto &&e : x)\n          helper<typename std::decay<decltype(e)>::type>(is,\
    \ e);\n      else\n        static_assert(has_begin<Tp>::value, \"istream unsupported\
    \ type.\");\n    }\n  };\n\n  template <class Tp>\n  struct helper<\n      Tp,\n\
    \      decltype(std::declval<std::decay<decltype(\n                   std::declval<std::istream\
    \ &>() >> std::declval<Tp &>())>>(),\n               nullptr)> {\n    helper(std::istream\
    \ &is, Tp &x) { is >> x; }\n  };\n\n  template <class T1, class T2> struct helper<std::pair<T1,\
    \ T2>> {\n    helper(std::istream &is, std::pair<T1, T2> &x) {\n      helper<T1>(is,\
    \ x.first), helper<T2>(is, x.second);\n    }\n  };\n\n  template <class... Tps>\
    \ struct helper<std::tuple<Tps...>> {\n    helper(std::istream &is, std::tuple<Tps...>\
    \ &x) { iterate(is, x); }\n\n   private:\n    template <class Tp, size_t N = 0>\
    \ void iterate(std::istream &is, Tp &x) {\n      if constexpr (N == std::tuple_size<Tp>::value)\n\
    \        return;\n      else\n        helper<typename std::tuple_element<N, Tp>::type>(is,\
    \ std::get<N>(x)),\n            iterate<Tp, N + 1>(is, x);\n    }\n  };\n\n public:\n\
    \  template <typename Tp> istream &operator>>(Tp &x) {\n    helper<Tp>(*this,\
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
  timestamp: '2020-12-01 15:41:27+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aizu-online-judge/2450.test.cpp
documentation_of: src/utils/io/istream.hpp
layout: document
redirect_from:
- /library/src/utils/io/istream.hpp
- /library/src/utils/io/istream.hpp.html
title: Input Stream
---
