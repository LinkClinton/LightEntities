#pragma once

#include <queue>
#include <memory>

#include "../utility.hpp"
#include <cassert>

namespace light {
	namespace entities {

		template<
			typename IdType,
			typename Limit = allow_unsigned_type<IdType>>
		class allocator {
		private:
			std::queue<IdType> remain_locations;

			const IdType expand_space;
			const size_t element_size;

			IdType reserve_space;
			IdType max_location;

			void* elements;
			bool* existed;
		public:
			allocator(size_t element_size, IdType reserve, IdType expand) :
				expand_space(expand), element_size(element_size),
				reserve_space(reserve), max_location(0) {

				assert(reserve != 0 && element_size != 0);

				elements = std::malloc(element_size * reserve);
				existed = static_cast<bool*>(std::malloc(sizeof(bool) * reserve));
				
				std::memset(elements, 0, element_size * reserve);
				std::memset(existed, 0, sizeof(bool) * reserve);
			}

			auto operator[](IdType identity) -> void*;

			auto allocate() -> IdType;

			void free(IdType identity);

			bool exist(IdType identity) const;

			auto location() const -> IdType;
		};

		template <typename IdType, typename Limit>
		auto allocator<IdType, Limit>::operator[](IdType identity) -> void* {
			return utility::offset(elements, element_size * identity);
		}

		template <typename IdType, typename Limit>
		auto allocator<IdType, Limit>::allocate() -> IdType {
			if (!remain_locations.empty()) {
				const auto identity = remain_locations.front(); remain_locations.pop();

				std::memset((*this)[identity], 0, element_size);
				existed[identity] = true;

				return identity;
			}

			if (max_location == reserve_space) {
				const auto new_space = reserve_space + (expand_space == 0 ? reserve_space : expand_space);
				const auto new_elements = std::malloc(element_size * new_space);
				const auto new_existed = std::malloc(sizeof(bool) * new_space);

				std::memset(new_elements, 0, element_size * new_space);
				std::memset(new_existed, 0, sizeof(bool) * new_space);

				std::memcpy(new_elements, elements, reserve_space * element_size);
				std::memcpy(new_existed, existed, reserve_space * sizeof(bool));

				std::free(elements);
				std::free(existed);

				reserve_space = new_space;
				elements = new_elements;
				existed = static_cast<bool*>(new_existed);
			}

			existed[max_location] = true;

			return max_location++;
		}

		template <typename IdType, typename Limit>
		void allocator<IdType, Limit>::free(IdType identity) {
			remain_locations.push(identity);
			existed[identity] = false;
		}

		template <typename IdType, typename Limit>
		bool allocator<IdType, Limit>::exist(IdType identity) const {
			return existed[identity];
		}

		template <typename IdType, typename Limit>
		auto allocator<IdType, Limit>::location() const -> IdType {
			return max_location;
		}


	}
}
