#pragma once

#include <type_traits>

namespace light {
	
	namespace entities {
		
		template<typename T>
		using allow_unsigned_type = std::enable_if_t<std::is_integral<T>::value && std::is_unsigned<T>::value>;

		class utility {
		public:
			static void* offset(void* src, size_t value);
		};

		inline void* utility::offset(void* src, size_t value) {
			return reinterpret_cast<void*>(
				reinterpret_cast<size_t>(src) + value);
		}


	}
}
