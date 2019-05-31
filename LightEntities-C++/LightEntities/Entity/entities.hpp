#pragma once

#include <map>

#include "../Component/component_type.hpp"
#include "../Component/component_info.hpp"
#include "../Entity/pool.hpp"
#include "../System/system.hpp"

namespace light {
	namespace entities {
		
		template<
			typename IdType, typename BitType,
			typename Limit0 = allow_unsigned_type<IdType>,
			typename Limit1 = allow_unsigned_type<BitType>>
		class entities {
		private:
			std::shared_ptr<component_info> info;

			std::vector<std::shared_ptr<pool<IdType, BitType>>> pools;
		public:
			entities();

			void add_pool(const std::vector<component_type> &components, size_t reserve = 255);

			auto pool(size_t index) -> light::entities::pool<IdType, BitType>&;

			void execute(system<IdType, BitType> &system);

			template<typename Type>
			auto typeof() -> const component_type&;
		};

		template <typename IdType, typename BitType, typename Limit0, typename Limit1>
		entities<IdType, BitType, Limit0, Limit1>::entities() {
			info = std::make_shared<component_info>();
		}

		template <typename IdType, typename BitType, typename Limit0, typename Limit1>
		void entities<IdType, BitType, Limit0, Limit1>::add_pool(const std::vector<component_type>& components,
			size_t reserve) {
			const auto pool = std::make_shared<light::entities::pool<IdType, BitType>>(
				info, components, reserve);

			pools.emplace_back(pool);
		}

		template <typename IdType, typename BitType, typename Limit0, typename Limit1>
		auto entities<IdType, BitType, Limit0, Limit1>::pool(size_t index) -> light::entities::pool<IdType, BitType>& {
			return (*pools[index]);
		}

		template <typename IdType, typename BitType, typename Limit0, typename Limit1>
		void entities<IdType, BitType, Limit0, Limit1>::execute(system<IdType, BitType> &system) {
			std::vector<entity<IdType, BitType>> entities;

			for (const auto& pool : pools) {
				auto sub_entities = pool->match(system.rule());

				entities.insert(entities.end(), sub_entities.begin(), sub_entities.end());
			}

			system.execute(entities);
		}

		template <typename IdType, typename BitType, typename Limit0, typename Limit1>
		template <typename Type>
		auto entities<IdType, BitType, Limit0, Limit1>::typeof() -> const component_type& {
			return info->typeof<Type>();
		}
	}
}
