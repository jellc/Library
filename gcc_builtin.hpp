#pragma once
#include <cstdint>
namespace workspace {
constexpr int clz32(const uint32_t &n) noexcept { return __builtin_clz(n); }
constexpr int clz64(const uint64_t &n) noexcept{ return __builtin_clzll(n); }
constexpr int ctz(const uint64_t &n) noexcept { return __builtin_ctzll(n); }
constexpr int popcnt(const uint64_t &n) noexcept { return __builtin_popcountll(n); }
} // namespace workspace
