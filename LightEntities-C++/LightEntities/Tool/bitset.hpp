#pragma once

#include <cassert>

#include "../Component/component_type.hpp"
#include <cstring>

namespace light {
	namespace entities {
		
		template<typename BitType, typename Limit = allow_unsigned_type<BitType>>
		class bitset {
		private:
			BitType* bits;
			size_t length;

			bool reference;
		public:
			bitset(const std::vector<bool> &list);

			bitset(BitType* bits, size_t length);

			~bitset();

			void set(size_t location, bool value);

			auto get(size_t location) -> bool;
	
			bool and_equal(const bitset &other);
		};

		template <typename BitType, typename Limit>
		bitset<BitType, Limit>::bitset(const std::vector<bool> &list) :
			bits(nullptr), length(list.size()), reference(false) {

			if (length == 0) return;

			const auto array_size = (length - 1) / (sizeof(BitType) << 2) + 1;

			bits = new BitType[array_size];

			std::memset(bits, 0, sizeof(BitType) * array_size);

			size_t location = 0;
			
			for (const auto &value : list) set(location++, value);
		}

		template <typename BitType, typename Limit>
		bitset<BitType, Limit>::bitset(BitType* bits, size_t length) : 
			bits(bits), length(length), reference(true) {}

		template <typename BitType, typename Limit>
		bitset<BitType, Limit>::~bitset() {
			if (!reference) delete bits;
		}

		template <typename BitType, typename Limit>
		void bitset<BitType, Limit>::set(size_t location, bool value) {
			const auto arr_index = location / (sizeof(BitType) << 2);
			const auto bit_index = location - (arr_index * (sizeof(BitType) << 2));

			const auto mask = static_cast<BitType>(1) << bit_index;

			bits[arr_index] = value ?
				bits[arr_index] | mask :
				bits[arr_index] & (~mask);
		}

		template <typename BitType, typename Limit>
		auto bitset<BitType, Limit>::get(size_t location) -> bool {
			const auto arr_index = location / (sizeof(BitType) << 2);
			const auto bit_index = location - (arr_index * (sizeof(BitType) << 2));

			return (bits[arr_index] >> bit_index) & static_cast<BitType>(1);
		}

		template <typename BitType, typename Limit>
		bool bitset<BitType, Limit>::and_equal(const bitset& other) {
			assert(length == other.length);

			if (length == 0) return true;

			const auto array_size = (length - 1) / (sizeof(BitType) << 2) + 1;

			for (size_t index = 0; index < array_size; index++)
				if ((bits[index] & other.bits[index]) != other.bits[index]) return false;

			return true;
		}


	}
}
