#pragma once

#include <typeinfo>

#include "../utility.hpp"

namespace light {
	namespace entities {
		
		struct component_type {
			const std::type_info &info;
			
			const size_t identity;
			const size_t size;
			
			component_type(std::type_info const &info, size_t identity, size_t size)
				: info(info), identity(identity), size(size) {}
		};

	}

}