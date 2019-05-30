#pragma once
#include "../Tool/match.hpp"
#include "../Entity/entity.hpp"

namespace light {
	namespace entities {
	
		template<
			typename IdType, typename BitType,
			typename Limit0 = allow_unsigned_type<IdType>,
			typename Limit1 = allow_unsigned_type<BitType>>
		class system {
		private:
			match match;	
		public:
			system();

			system(const std::vector<component_type> &components);

			virtual void execute(const std::vector<entity<IdType, BitType>> &entities) const {}

			auto rule() const -> light::entities::match;
		};

		template<
			typename IdType, typename BitType,
			typename Limit0, typename Limit1>
		system<IdType, BitType, Limit0, Limit1>::system() :
			match({}) {

		}

		template<
			typename IdType, typename BitType,
			typename Limit0, typename Limit1>
		system<IdType, BitType, Limit0, Limit1>::system(const std::vector<component_type>& components) :
			match(components) {
		}

		template<
			typename IdType, typename BitType,
			typename Limit0, typename Limit1>
		auto system<IdType, BitType, Limit0, Limit1>::rule() const -> light::entities::match {
			return match;
		}
	}
}
