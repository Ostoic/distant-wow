#include <memory/address.hpp>

namespace memory
{
	//interface:
	constexpr address::operator wow::dword() const noexcept
	{
		return reinterpret_cast<wow::dword>(this->address_);
	}

	//operators:
	constexpr address& address::operator +=(address other) noexcept
	{
		*this = (static_cast<wow::dword>(*this) + static_cast<wow::dword>(other));
		return *this;
	}

	constexpr address& address::operator -=(address other) noexcept
	{
		*this = (static_cast<wow::dword>(*this) - static_cast<wow::dword>(other));
		return *this;
	}

	constexpr address& address::operator *=(address other) noexcept
	{
		*this = (static_cast<wow::dword>(*this) * static_cast<wow::dword>(other));
		return *this;
	}

	constexpr address& address::operator /=(address other) noexcept
	{
		*this = (static_cast<wow::dword>(*this) / static_cast<wow::dword>(other));
		return *this;
	}

	//{ctor}
	constexpr address::address() noexcept : address_(nullptr)
	{
	}

	constexpr address::address(nullptr_t) noexcept : address()
	{
	}

	template <typename T>
	constexpr address::address(T x) noexcept : address_(reinterpret_cast<void*>(x))
	{
	}

	//free:
	constexpr bool operator==(address lhs, address rhs) noexcept
	{
		return lhs.address_ == rhs.address_;
	}

	constexpr bool operator>(address lhs, address rhs) noexcept
	{
		return lhs.address_ > rhs.address_;
	}

	constexpr bool operator!=(address lhs, address rhs) noexcept
	{
		return !operator==(lhs, rhs);
	}

	constexpr bool operator<(address lhs, address rhs) noexcept
	{
		return !operator>(lhs, rhs) && !operator==(lhs, rhs);
	}

	constexpr bool operator>=(address lhs, address rhs) noexcept
	{
		return !operator>(lhs, rhs);
	}

	constexpr bool operator<=(address lhs, address rhs) noexcept
	{
		return !operator>(lhs, rhs);
	}

	constexpr address operator&(address lhs, address rhs) noexcept
	{
		return static_cast<wow::dword>(lhs) & static_cast<wow::dword>(rhs);
	}

	constexpr address operator|(address lhs, address rhs) noexcept
	{
		return static_cast<wow::dword>(lhs) | static_cast<wow::dword>(rhs);
	}

	constexpr address operator^(address lhs, address rhs) noexcept
	{
		return static_cast<wow::dword>(lhs) ^ static_cast<wow::dword>(rhs);
	}

	constexpr address operator<<(address lhs, address rhs) noexcept
	{
		return static_cast<wow::dword>(lhs) << static_cast<wow::dword>(rhs);
	}

	constexpr address operator>>(address lhs, address rhs) noexcept
	{
		return static_cast<wow::dword>(lhs) >> static_cast<wow::dword>(rhs);
	}

	constexpr address operator+(address lhs, address rhs) noexcept
	{
		return static_cast<wow::dword>(lhs) + static_cast<wow::dword>(rhs);
	}

	constexpr address operator-(address lhs, address rhs) noexcept
	{
		return static_cast<wow::dword>(lhs) - static_cast<wow::dword>(rhs);
	}

	constexpr address operator*(address lhs, address rhs) noexcept
	{
		return static_cast<wow::dword>(lhs) * static_cast<wow::dword>(rhs);
	}

	constexpr address operator/(address lhs, address rhs) noexcept
	{
		return static_cast<wow::dword>(lhs) / static_cast<wow::dword>(rhs);
	}

	inline std::ostream& operator<<(std::ostream& stream, address address)
	{
		std::ios::fmtflags f{stream.flags()};
		stream << std::hex << std::uppercase;
		stream << "0x" << static_cast<wow::dword>(address);
		stream << std::dec;
		stream.flags(f);
		return stream;
	}
}

namespace std
{
	template <>
	struct hash<memory::address>
	{
		using argument_type = memory::address;
		using result_type = std::size_t;

		result_type operator()(const argument_type& address) const noexcept
		{
			return std::hash<wow::dword>{}(static_cast<wow::dword>(address));
		}
	};
}
