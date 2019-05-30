#pragma once

#include "../Component/component_type.hpp"
#include "../Tool/allocator.hpp"
#include "../Entity/entity.hpp"
#include "../Tool/match.hpp"

namespace light {
	namespace entities {

		template<
			typename IdType, typename BitType,
			typename Limit0, typename Limit1>	
		class pool {
		private:
			entity_solver<BitType> solver;
			allocator<IdType> allocator;

			std::shared_ptr<component_info> info;

			std::vector<IdType> components_mapped;
			std::vector<bool> components_existed;

			size_t components_count;

			template<typename Component>
			void add_component(IdType identity, const Component &component);

			template<typename Component>
			void remove_component(IdType identity);

			template<typename Component>
			auto component(IdType identity)->Component&;

			friend struct entity<IdType, BitType, Limit0, Limit1>;
		public:
			pool(const std::shared_ptr<component_info> &info, const std::vector<component_type> &components, size_t reserve = 255);

			template<typename Component>
			void add_component(const entity<IdType, BitType> &entity, const Component &component);

			template<typename Component>
			void remove_component(const entity<IdType, BitType> &entity);

			template<typename Component>
			auto component(const entity<IdType, BitType> &entity) -> Component&;

			auto allocate() -> entity<IdType, BitType>;

			void free(const entity<IdType, BitType> &entity);

			auto match(const match &match) -> std::vector<entity<IdType, BitType>>;
		};

		template <typename IdType, typename BitType, typename Limit0, typename Limit1>
		template <typename Component>
		void pool<IdType, BitType, Limit0, Limit1>::add_component(IdType identity, const Component& component) {
			assert(components_existed[info->typeof<Component>().identity]);

			const component_type& type_info_ = info->typeof<Component>();
			const auto mapped_identity = components_mapped[type_info_.identity];

			solver.add_component(
				mapped_identity,
				allocator[identity],
				component);
		}

		template <typename IdType, typename BitType, typename Limit0, typename Limit1>
		template <typename Component>
		void pool<IdType, BitType, Limit0, Limit1>::remove_component(IdType identity) {
			assert(components_existed[info->typeof<Component>()].identity);

			const component_type& type_info_ = info->typeof<Component>();
			const auto mapped_identity = components_mapped[type_info_.identity];

			solver.remove_component(mapped_identity, allocator[identity]);
		}

		template <typename IdType, typename BitType, typename Limit0, typename Limit1>
		template <typename Component>
		auto pool<IdType, BitType, Limit0, Limit1>::component(IdType identity) -> Component& {
			assert(components_existed[info->typeof<Component>().identity]);

			const component_type& type_info_ = info->typeof<Component>();
			const auto mapped_identity = components_mapped[type_info_.identity];

			return (*static_cast<Component*>(solver.component(mapped_identity, allocator[identity])));
		}

		template <typename IdType, typename BitType, typename Limit0, typename Limit1>
		pool<IdType, BitType, Limit0, Limit1>::pool(
			const std::shared_ptr<component_info> &info,
			const std::vector<component_type> &components, size_t reserve) :
			solver(components), allocator(solver.size(), static_cast<IdType>(reserve), 0),
			info(info), components_count(components.size()) {

			size_t max_count = 0;

			for (const auto &component : components)
				max_count = std::max(max_count, component.identity);

			components_mapped.resize(max_count + 1);
			components_existed.resize(max_count + 1);

			for (IdType index = 0; index < components_count; ++index) {
				components_mapped[components[index].identity] = index;
				components_existed[components[index].identity] = true;
			}
		}

		template <typename IdType, typename BitType, typename Limit0, typename Limit1>
		template <typename Component>
		void pool<IdType, BitType, Limit0, Limit1>::add_component(const entity<IdType, BitType>& entity, const Component &component) {
			add_component(entity.identity(), component);
		}

		template <typename IdType, typename BitType, typename Limit0, typename Limit1>
		template <typename Component>
		void pool<IdType, BitType, Limit0, Limit1>::remove_component(const entity<IdType, BitType>& entity) {
			remove_component<Component>(entity.identity());
		}

		template <typename IdType, typename BitType, typename Limit0, typename Limit1>
		template <typename Component>
		auto pool<IdType, BitType, Limit0, Limit1>::component(const entity<IdType, BitType>& entity) -> Component& {
			return component<Component>(entity.identity());
		}

		template <typename IdType, typename BitType, typename Limit0, typename Limit1>
		auto pool<IdType, BitType, Limit0, Limit1>::allocate() -> entity<IdType, BitType> {
			return entity<IdType, BitType>(allocator.allocate(), this);
		}

		template <typename IdType, typename BitType, typename Limit0, typename Limit1>
		void pool<IdType, BitType, Limit0, Limit1>::free(const entity<IdType, BitType>& entity) {
			allocator.free(entity.identity);
		}

		template <typename IdType, typename BitType, typename Limit0, typename Limit1>
		auto pool<IdType, BitType, Limit0, Limit1>::match(const light::entities::match& match) -> std::vector<entity<IdType, BitType>> {
			std::vector<entity<IdType, BitType>> entities;

			bitset<BitType> match_rule = bitset<BitType>(std::vector<bool>(components_count));

			for (const auto &component : match.components) {
				if (component.identity >= components_count ||
					!components_existed[component.identity]) return entities;

				match_rule.set(components_mapped[component.identity], true);
			}

			for (IdType index = 0; index < allocator.location(); ++index) {
				if (!allocator.exist(index)) continue;;

				if (solver.match(allocator[index], match_rule)) entities.emplace_back(entity<IdType, BitType>(index, this));
			}

			return entities;
		}

		template <typename IdType, typename BitType, typename Limit0, typename Limit1>
		template <typename Component>
		void entity<IdType, BitType, Limit0, Limit1>::add_component(const Component& component) {
			pool->add_component(pool_identity, component);
		}

		template <typename IdType, typename BitType, typename Limit0, typename Limit1>
		template <typename Component>
		void entity<IdType, BitType, Limit0, Limit1>::remove_component() {
			pool->template remove_component<Component>(pool_identity);
		}

		template <typename IdType, typename BitType, typename Limit0, typename Limit1>
		template <typename Component>
		auto entity<IdType, BitType, Limit0, Limit1>::component() -> Component& {
			return pool->template component<Component>(pool_identity);
		}



	}
}
