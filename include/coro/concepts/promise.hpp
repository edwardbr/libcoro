#pragma once

#include "coro/concepts/awaitable.hpp"

#include <concepts>

namespace coro::concepts
{
    
  /// [concept.convertible], concept convertible_to
  template<typename _From, typename _To>
    concept convertible_to = std::is_convertible_v<_From, _To>
      && requires { static_cast<_To>(std::declval<_From>()); };
    
// clang-format off
template<typename type, typename return_type>
concept promise = requires(type t)
{
    { t.get_return_object() } -> convertible_to<std::coroutine_handle<>>;
    { t.initial_suspend() } -> awaiter;
    { t.final_suspend() } -> awaiter;
    { t.yield_value() } -> awaitable;
}
&& requires(type t, return_type return_value)
{
    requires std::same_as<decltype(t.return_void()), void> ||
        std::same_as<decltype(t.return_value(return_value)), void> ||
        requires { t.yield_value(return_value); };
};
// clang-format on

} // namespace coro::concepts
