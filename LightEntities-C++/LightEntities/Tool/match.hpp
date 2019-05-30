#pragma once

#include <vector>

#include "../Component/component_type.hpp"

namespace light {
	namespace entities {

		struct match {
		public:
			std::vector<component_type> components;

			match(const std::vector<component_type> &components)
				: components(components) {}
		};

	}
}
