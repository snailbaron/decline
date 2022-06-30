#pragma once

#include <thing.hpp>

class World {
public:
    World();

    void createTestWorld();

    void update(double delta);

private:
    thing::EntityManager _entities;
};
