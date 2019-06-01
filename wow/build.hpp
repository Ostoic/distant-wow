#pragma once

#include <string_view>

#include <distant/process.hpp>

#include "utility/meta_string.hpp"

namespace distant::wow
{
	bool is_process_supported(const distant::process<distant::process_rights::vm_read>& process);

	namespace detail { constexpr auto build_text = "World of Warcraft 3.3.5 (12340)"; }

	constexpr std::string_view supported_build(detail::build_text, utility::string_length(detail::build_text));
}
