#pragma once

#include <type_traits>
#include <tuple>

namespace distant::wow::utility
{
	template <typename Fn>
	struct function_traits;

	template <typename R, typename... Args>
	struct function_traits<R(Args...)>
	{
		using return_type = R;

		template <std::size_t Index>
		using argument_type = std::tuple_element_t<Index, std::tuple<Args...>>;

		static constexpr auto arity = sizeof...(Args);
	};

	template <typename Fn>
	struct function_ptr_decay;

	template <typename R, typename... Args>
	struct function_ptr_decay<R(*)(Args...)>
	{
		using type = R(Args...);
	};

	template <typename R, typename... Args>
	struct function_ptr_decay<R(&)(Args...)>
	{
		using type = R(Args...);
	};

	template <typename Fn>
	using function_ptr_decay_t = typename function_ptr_decay<Fn>::type;

	template <typename Fn>
	constexpr auto arity()
	{
		return function_traits<function_ptr_decay_t<Fn>>::arity;
	}
}
