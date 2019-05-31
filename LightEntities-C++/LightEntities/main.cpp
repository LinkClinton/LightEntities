#include "entities.hpp"

using namespace light::entities;

struct position {
	float x, y;
};

struct direction {
	float x, y;
};

class move_system : public light::entities::system32 {
public:
	move_system(const std::vector<component_type> &list) : system32(list) {}

	void execute(const std::vector<entity32>& entities) override {
		for (auto e : entities) {
			auto& p = e.component<position>();
			auto& s = e.component<direction>();

			p.x = p.x + s.x;
			p.y = p.y + s.y;
		}
	}
};

int main() {

	entities32 entities;

	entities.add_pool({
		entities.typeof<position>(),
		entities.typeof<direction>()
		});

	
	for (int i = 0; i < 10; i++) {
		auto e = entities.pool(0).allocate();

		e.add_component<position>( { 0,0 });
		e.add_component<direction>( { 1,1 });
	}

	move_system system = move_system({
		entities.typeof<position>(),
		entities.typeof<direction>()
		});

	entities.execute(system);
}
