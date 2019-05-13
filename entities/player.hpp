#pragma once

#include "unit.hpp"
#include "types.hpp"
#include "detail/player_descriptors.hpp"

namespace distant::wow::entities
{

	class player : public unit
	{
	public:
		enum class classes
		{
			warrior = 1,
			paladin = 2,
			hunter = 3,
			rogue = 4,
			priest = 5,
			shaman = 7,
			mage = 8,
			warlock = 9,
			druid = 11
		};

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

} // namespace distant::wow::entities

namespace distant::wow
{
	using entities::player;
}