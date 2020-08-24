#pragma once
#include <type_traits>
template <class type, template <class> class trait, typename = std::enable_if_t<trait<type>::value, void>>
using enable_if_trait = type;
