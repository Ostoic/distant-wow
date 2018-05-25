#pragma once

#include "unit.hpp"
#include "types.hpp"
#include "detail/player_descriptors.hpp"

namespace wow::entities
{
	class player : public unit
	{
	public:
		enum class classes;

	public: // interface
		bool is_player() const override;

	public: // {ctor}
		player() = default;
		explicit player(memory::address base);

	protected:
		memory::address get_name_ptr() const override;

		void update_data() const override final;

	private: // implementation functions
		friend class object;

	private: // descriptors
		mutable memory::address descriptors_base_;
	};

} // namespace wow::entities

namespace wow
{
	using entities::player;
}