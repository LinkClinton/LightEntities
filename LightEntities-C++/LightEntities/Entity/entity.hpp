#pragma once

#include <vector>

#include "../utility.hpp"
#include "../Tool/bitset.hpp"
#include "../Component/component_type.hpp"

namespace light {
	namespace entities {
	
		template<
			typename IdType, typename BitType,
			typename Limit0 = allow_unsigned_type<IdType>,
			typename Limit1 = allow_unsigned_type<BitType>>
		class pool;

		template<
			typename IdType, typename BitType,
			typename Limit0 = allow_unsigned_type<IdType>,
			typename Limit1 = allow_unsigned_type<BitType>>
		struct entity {
		private:
			IdType pool_identity;
			pool<IdType, BitType>* from_pool;
		public:
			entity(IdType identity, light::entities::pool<IdType, BitType>* pool) :
				pool_identity(identity), from_pool(pool) {
				
			}

			template<typename Component>
			void add_component(const Component &component);

			template<typename Component>
			void remove_component();

			template<typename Component>
			auto component() -> Component&;

			auto identity() const -> IdType {
				return pool_identity;
			}
		};

		template<typename BitType, typename Limit = allow_unsigned_type<BitType>>
		class entity_solver {
		private:
			std::vector<size_t> component_address_offset;
			size_t bitset_address_offset;
			size_t element_size;
		public:
			entity_solver(const std::vector<component_type> &components);

			auto size() const -> size_t;

			template<typename Component>
			void add_component(size_t identity, void* element, const Component &component) const;

			void remove_component(size_t identity, void* element) const;

			auto component(size_t identity, void* element) -> void*;

			bool match(void* element, const bitset<BitType> &match);
		};

		template <typename BitType, typename Limit>
		entity_solver<BitType, Limit>::entity_solver(const std::vector<component_type>& components) :
			bitset_address_offset(0), element_size(1) {
			if (components.empty()) return;

			component_address_offset.emplace_back(0);

			for (const auto &component : components)
				component_address_offset.emplace_back(
					component_address_offset.back() + component.size);

			bitset_address_offset = component_address_offset.back();

			component_address_offset.pop_back();

			element_size = bitset_address_offset + (components.size() - 1) / sizeof(BitType) + 1;
		}


		template <typename BitType, typename Limit>
		auto entity_solver<BitType, Limit>::size() const -> size_t {
			return element_size;
		}

		template <typename BitType, typename Limit>
		template <typename Component>
		void entity_solver<BitType, Limit>::add_component(size_t identity, void* element, const Component &component) const {
			std::memcpy(utility::offset(element, component_address_offset[identity]), &component, sizeof(Component));

			bitset<BitType>(
				static_cast<BitType*>(utility::offset(element, bitset_address_offset)),
				component_address_offset.size()).set(identity, true);
		}


		template <typename BitType, typename Limit>
		void entity_solver<BitType, Limit>::remove_component(size_t identity, void* element) const {
			
			bitset<BitType>(
				static_cast<BitType*>(utility::offset(element, bitset_address_offset)),
				component_address_offset.size()).set(identity, false);
		}

		template <typename BitType, typename Limit>
		auto entity_solver<BitType, Limit>::component(size_t identity, void* element) -> void* {
			assert(bitset<BitType>(
				static_cast<BitType*>(utility::offset(element, bitset_address_offset)),
				component_address_offset.size()).get(identity));

			return utility::offset(element, component_address_offset[identity]);
		}

		template <typename BitType, typename Limit>
		bool entity_solver<BitType, Limit>::match(void* element, const bitset<BitType>& match) {
			auto bits = bitset<BitType>(
				static_cast<BitType*>(utility::offset(element, bitset_address_offset)),
				component_address_offset.size());

			return bits.and_equal(match);
		}


	}
}
