# LightEntities

[`English`](./readme.md) [`中文`](./readme_cn.md) 

LightEntities是一个简单轻量的[ECS](https://en.wikipedia.org/wiki/Entity_component_system)。

## Basic Idea and Feature

- 内存友好：使用一个简单的内存分配器来分配实体(`entity`)使用的内存。当实体被移除的时候，其内存块不会被清除，而是保留下来，并且当新的实体需要被分配的时候重新使用。
- 隐式组件: 任何结构体或者类都可以当作组件(`Component`)使用，**LightEntities将会直接复制其使用的内存到组件的内存池中**。
- 位运算匹配：为了加速判断一个组件是否含有一些组件，LightEntities通过位运算来加快匹配过程，以提高组件过多时的匹配性能。
- 轻量：只有小部分代码并且只包含头文件，易于拓展以及并行处理。

## Requirement

- 至少支持C++14的编译器。

## Example

```C++
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

```