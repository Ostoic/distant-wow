#include <objects/game_object.hpp>

#include <objects/unit.hpp>
#include <memory/operations.hpp>
#include <wow/offsets.hpp>
#include <objects/detail/game_object.hpp>
#include <objects/object_manager.hpp>

namespace objects
{
//public:
	std::size_t game_object::display_id() const
	{
		this->get_ownership_descriptors();
		return this->go_descriptors_->ownership_chunk.display_id;
	}

	optional_object<unit> game_object::owner() const
	{
		this->get_ownership_descriptors();

		object_manager<unit> manager;
		const auto it = manager.find(this->go_descriptors_->ownership_chunk.created_by);

		if (it != manager.end())
			return *it;

		return {};
	}

	wow::flags game_object::flags() const
	{
		return memory::read_offset(descriptors_base_, wow::offsets::game_object_descriptors::flags);
	}

	wow::flags game_object::other_flags() const
	{
		return memory::read_offset(descriptors_base_, wow::offsets::game_object_descriptors::other_flags);
	}

	void game_object::set_flags(wow::flags flags)
	{
		memory::write(go_descriptors_->base + wow::offsets::game_object_descriptors::flags, flags);
	}

	void game_object::change_owner(const unit& new_owner)
	{
		this->get_ownership_descriptors();
		auto guid = new_owner.guid();
		
		memory::write(this->go_descriptors_->base + wow::offsets::game_object_descriptors::created_by, guid);
	}

	void game_object::change_name(const std::string& name)
	{
		memory::write(detail::get_name_ptr<game_object>(this->base_), this->name_);
		this->name_ = name;
	}

//{ctor}:
	game_object::game_object(const memory::address base)
		: object(base, *this) {}

//private:
	void game_object::check_descriptors_ptr() const
	{
		if (go_descriptors_ == nullptr)
		{
			go_descriptors_ = std::make_unique<detail::game_object_descriptors>();
			go_descriptors_->base = memory::read<wow::dword>(base_ + wow::offsets::object::object_descriptors);
		}
	}

	void game_object::get_ownership_descriptors() const
	{
		this->check_descriptors_ptr();
		memory::read_offset(go_descriptors_->base, wow::offsets::game_object_descriptors::created_by);
		go_descriptors_->ownership_chunk = memory::read<decltype(detail::game_object_descriptors::ownership_chunk)>(
			go_descriptors_->base + wow::offsets::game_object_descriptors::created_by
		);
	}

	void game_object::get_all_descriptors() const
	{
		this->get_ownership_descriptors();
		go_descriptors_->other_flags = memory::read<wow::byte>(
			go_descriptors_->base + wow::offsets::game_object_descriptors::other_flags
		);
	}

	void game_object::update_data() const
	{
		this->get_all_descriptors();
	}

	geometry::vector game_object::get_position() const
	{
		return memory::read<geometry::vector>(this->base_ + wow::offsets::object::go_x_coord);
	}

}
