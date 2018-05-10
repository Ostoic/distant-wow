#pragma once

#include <objects/unit.hpp>
#include <objects/types.hpp>
#include <objects/detail/player_descriptors.hpp>
#include <optional>

namespace objects
{
	class player : public unit
	{
	public:
		enum class classes;

	public: // interface
		std::size_t display_id() const override final;

		bool is_player() const override;

		void change_name(const std::string& name) override final;

	public: // {ctor}
		player() = default;
		explicit player(memory::address base);

	protected:
		void update_data() const override final;

	private: // implementation functions
		friend class object;

		void get_descriptors() const;

	private: // data
		mutable std::shared_ptr<detail::player_descriptors> player_descriptors_;
	};
} // namespace objects
