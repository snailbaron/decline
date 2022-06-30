#include "world.hpp"

#include "events.hpp"

namespace sys {

} // namespace sys

struct Body {
    float x;
    float y;
    float radius;
};

World::World()
{
}

void World::createTestWorld()
{
    {
        auto e = _entities.createEntity();
        const auto& p = _entities.add(e, Body{.x = 0, .y = 0, .radius = 1});
        events.push(event::Create{
            .id = e,
            .type = ObjectType::Human,
            .x = p.x,
            .y = p.y,
            .radius = p.radius,
        });
    }

    {
        auto e = _entities.createEntity();
        const auto& p = _entities.add(e, Body{.x = 10, .y = 5, .radius = 5});
        events.push(event::Create{
            .id = e,
            .type = ObjectType::Tree,
            .x = p.x,
            .y = p.y,
            .radius = p.radius,
        });
    }

    {
        auto e = _entities.createEntity();
        const auto& p = _entities.add(e, Body{.x = 5, .y = 8, .radius = 4});
        events.push(event::Create{
            .id = e,
            .type = ObjectType::Tree,
            .x = p.x,
            .y = p.y,
            .radius = p.radius,
        });
    }
}

void World::update(double delta)
{
    (void)delta;
}
