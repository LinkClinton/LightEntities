#pragma once

#include "utility.hpp"
#include "Entity/entities.hpp"
#include "Component/component_info.hpp"
#include "System/system.hpp"

namespace light {
	namespace entities {
		
		using entity16 = entity<unsigned short, unsigned int>;
		using entity32 = entity<unsigned int, unsigned int>;
		using entity64 = entity<unsigned long long, unsigned int>;

		using pool16 = pool<unsigned short, unsigned int>;
		using pool32 = pool<unsigned int, unsigned int>;
		using pool64 = pool<unsigned long long, unsigned int>;

		using entities16 = entities<unsigned short, unsigned int>;
		using entities32 = entities<unsigned int, unsigned int>;
		using entities64 = entities<unsigned long long, unsigned int>;

		using system16 = system<unsigned short, unsigned int>;
		using system32 = system<unsigned int, unsigned int>;
		using system64 = system<unsigned long long, unsigned int>;

	}
}