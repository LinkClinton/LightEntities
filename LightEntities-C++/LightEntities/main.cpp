#include <iostream>
#include <chrono>

#include "Component/component_info.hpp"
#include "System/system.hpp"
#include "Entity/entities.hpp"

typedef std::chrono::high_resolution_clock Time;

using namespace light::entities;

struct position {
	float x, y;
};

struct speed {
	float vx, vy;
};

class move_system : public light::entities::system<unsigned, unsigned> {
public:
	move_system(const std::vector<component_type> &list) : system<unsigned, unsigned>(list) {}

	void execute(const std::vector<entity<unsigned, unsigned>>& entities) const override {
		for (auto e : entities) {
			auto& p = e.component<position>();
			auto& s = e.component<speed>();

			p.x = p.x + s.vx;
			p.y = p.y + s.vy;
		}
	}
};

int main() {
	
	const auto size = 1000000;

	entities<unsigned, unsigned> entities;

	entities.add_pool({
		entities.typeof<position>(),
		entities.typeof<speed>()
		});

	
	for (int i = 0; i < size; i++) {
		auto e = entities.pool(0).allocate();

		e.add_component<position>( { 0,0 });
		e.add_component<speed>( { 1,1 });
	}

	auto start = Time::now();
	
	move_system system = move_system({
		entities.typeof<position>(),
		entities.typeof<speed>()
		});

	entities.execute(system);

	auto end = Time::now();

	std::cout << std::chrono::duration_cast<std::chrono::duration<float>>(end - start).count() << std::endl;

	::system("pause");
}
