#pragma once

#include <unordered_map>
#include <typeindex>
#include <vector>
#include <memory>

#include "component_type.hpp"

namespace light {
	namespace entities {
		
		class component_info {
		private:
			std::unordered_map<std::type_index, std::shared_ptr<component_type>> type_table;
			std::vector<std::shared_ptr<component_type>> memory_pool;

		public:
			template<typename Type>
			auto typeof() -> const component_type&;
		};

		template <typename Type>
		auto component_info::typeof() -> const component_type& {
			const auto it = type_table.find(typeid(Type));

			if (it != type_table.end()) return *(it->second);

			const auto type = std::make_shared<component_type>(typeid(Type), memory_pool.size(), sizeof(Type));
			
			type_table.insert({ typeid(Type), type });
			memory_pool.emplace_back(type);

			return (*type);
		}


	}
}
