#pragma once

namespace distant::wow::utility
{
	class attorney
	{
	public:
		template <typename Target, typename F>
		static void execute(Target& t, F f)
		{
			f(t);
		}
	};
}
