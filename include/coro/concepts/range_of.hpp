#pragma once

#include <concepts>

// #include <ranges>
#include <range/v3/all.hpp>

namespace coro::concepts
{
/**
 * Concept to require that the range contains a specific type of value.
 */
template<class T, class V>
concept range_of = ranges::range<T> && std::is_same_v<V, ranges::range_value_t<T>>;

/**
 * Concept to require that a sized range contains a specific type of value.
 */
template<class T, class V>
concept sized_range_of = ranges::sized_range<T> && std::is_same_v<V, ranges::range_value_t<T>>;

} // namespace coro::concepts
